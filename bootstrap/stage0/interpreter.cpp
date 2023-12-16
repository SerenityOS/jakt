#include "interpreter.h"
namespace Jakt {
namespace interpreter {
ErrorOr<size_t> align_of_impl(ids::TypeId const type_id,NonnullRefPtr<interpreter::Interpreter> const interpreter) {
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
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).size_t_alignment()))));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).int_alignment()))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_166; {
types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&struct_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_167([&] {
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
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
size_t const field_alignment = TRY((interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(((field).variable_id))))->type_id)),interpreter)));
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
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

__jakt_var_166 = align; goto __jakt_label_160;

}
__jakt_label_160:; __jakt_var_166.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_168; {
types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&struct_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_169([&] {
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
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
size_t const field_alignment = TRY((interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(((field).variable_id))))->type_id)),interpreter)));
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
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

__jakt_var_168 = align; goto __jakt_label_161;

}
__jakt_label_161:; __jakt_var_168.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_170; {
types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&enum_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_171([&] {
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
__jakt_var_170 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(types::void_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_172; {
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_align = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((interpreter::align_of_impl(resolve_type_id(type_id),interpreter))));
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_173; {
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
size_t const field_alignment = TRY((interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id)),interpreter)));
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
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

__jakt_var_173 = align; goto __jakt_label_164;

}
__jakt_label_164:; __jakt_var_173.release_value(); }));
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
(variant_align,align)){
(align = variant_align);
}
}

}
}

types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BuiltinType,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((interpreter::align_of_impl(types::builtin(index_type),interpreter)));
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
(index_align,align)){
(align = index_align);
}
__jakt_var_172 = align; goto __jakt_label_163;

}
__jakt_label_163:; __jakt_var_172.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_162;

}
__jakt_label_162:; __jakt_var_170.release_value(); }));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_174; {
types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&enum_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_175([&] {
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
__jakt_var_174 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(types::void_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_176; {
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_align = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((interpreter::align_of_impl(resolve_type_id(type_id),interpreter))));
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_177; {
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
size_t const field_alignment = TRY((interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id)),interpreter)));
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
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

__jakt_var_177 = align; goto __jakt_label_167;

}
__jakt_label_167:; __jakt_var_177.release_value(); }));
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
(variant_align,align)){
(align = variant_align);
}
}

}
}

types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BuiltinType,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((interpreter::align_of_impl(types::builtin(index_type),interpreter)));
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
(index_align,align)){
(align = index_align);
}
__jakt_var_176 = align; goto __jakt_label_166;

}
__jakt_label_166:; __jakt_var_176.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_165;

}
__jakt_label_165:; __jakt_var_174.release_value(); }));
};/*case end*/
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 27 /* Trait */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 28 /* Reference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 29 /* MutableReference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_alignment()))));
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

ErrorOr<size_t> size_of_impl(ids::TypeId const type_id,NonnullRefPtr<interpreter::Interpreter> const interpreter) {
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
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).size_t_size()))));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).int_size()))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_178; {
types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&struct_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_179([&] {
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
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
ids::TypeId type_id = resolve_type_id(((((((interpreter)->program))->get_variable(((field).variable_id))))->type_id));
size_t const field_size = TRY((interpreter::size_of_impl(type_id,interpreter)));
size_t const field_align = TRY((interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_align,slack)));
}
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

__jakt_var_178 = size; goto __jakt_label_168;

}
__jakt_label_168:; __jakt_var_178.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_180; {
types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&struct_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_181([&] {
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
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
ids::TypeId type_id = resolve_type_id(((((((interpreter)->program))->get_variable(((field).variable_id))))->type_id));
size_t const field_size = TRY((interpreter::size_of_impl(type_id,interpreter)));
size_t const field_align = TRY((interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_align,slack)));
}
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

__jakt_var_180 = size; goto __jakt_label_169;

}
__jakt_label_169:; __jakt_var_180.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_182; {
types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&enum_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_183([&] {
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
__jakt_var_182 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(types::void_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_184; {
size_t size = static_cast<size_t>(0ULL);
size_t container_align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_size = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_185; {
size_t const align = TRY((interpreter::align_of_impl(resolve_type_id(type_id),interpreter)));
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
(align,container_align)){
(container_align = align);
}
__jakt_var_185 = TRY((interpreter::size_of_impl(type_id,interpreter))); goto __jakt_label_172;

}
__jakt_label_172:; __jakt_var_185.release_value(); }));
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_186; {
size_t size = static_cast<size_t>(0ULL);
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
ids::TypeId const type_id = resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id));
size_t const field_size = TRY((interpreter::size_of_impl(type_id,interpreter)));
size_t const field_alignment = TRY((interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_alignment);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_alignment,slack)));
}
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
(align,container_align)){
(container_align = align);
}
__jakt_var_186 = size; goto __jakt_label_173;

}
__jakt_label_173:; __jakt_var_186.release_value(); }));
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
(variant_size,size)){
(size = variant_size);
}
}

}
}

types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BuiltinType,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((interpreter::align_of_impl(types::builtin(index_type),interpreter)));
size_t const index_size = TRY((interpreter::size_of_impl(types::builtin(index_type),interpreter)));
size_t const index_slack = JaktInternal::checked_mod(size,index_align);
if (((index_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(index_align,index_slack)));
}
((size) += (index_size));
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
(container_align,index_align)){
size_t const slack = JaktInternal::checked_mod(size,container_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(container_align,slack)));
}
}
__jakt_var_184 = size; goto __jakt_label_171;

}
__jakt_label_171:; __jakt_var_184.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_170;

}
__jakt_label_170:; __jakt_var_182.release_value(); }));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_187; {
types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<ids::TypeId(ids::TypeId)> const resolve_type_id = [&enum_, &args](ids::TypeId type_id) -> ids::TypeId {
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_188([&] {
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
__jakt_var_187 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(types::void_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_189; {
size_t size = static_cast<size_t>(0ULL);
size_t container_align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_size = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_190; {
size_t const align = TRY((interpreter::align_of_impl(resolve_type_id(type_id),interpreter)));
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
(align,container_align)){
(container_align = align);
}
__jakt_var_190 = TRY((interpreter::size_of_impl(type_id,interpreter))); goto __jakt_label_176;

}
__jakt_label_176:; __jakt_var_190.release_value(); }));
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_191; {
size_t size = static_cast<size_t>(0ULL);
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
ids::TypeId const type_id = resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id));
size_t const field_size = TRY((interpreter::size_of_impl(type_id,interpreter)));
size_t const field_alignment = TRY((interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_alignment);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_alignment,slack)));
}
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
(align,container_align)){
(container_align = align);
}
__jakt_var_191 = size; goto __jakt_label_177;

}
__jakt_label_177:; __jakt_var_191.release_value(); }));
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
(variant_size,size)){
(size = variant_size);
}
}

}
}

types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BuiltinType,ErrorOr<size_t>>{
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((interpreter::align_of_impl(types::builtin(index_type),interpreter)));
size_t const index_size = TRY((interpreter::size_of_impl(types::builtin(index_type),interpreter)));
size_t const index_slack = JaktInternal::checked_mod(size,index_align);
if (((index_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(index_align,index_slack)));
}
((size) += (index_size));
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
(container_align,index_align)){
size_t const slack = JaktInternal::checked_mod(size,container_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(container_align,slack)));
}
}
__jakt_var_189 = size; goto __jakt_label_175;

}
__jakt_label_175:; __jakt_var_189.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_174;

}
__jakt_label_174:; __jakt_var_187.release_value(); }));
};/*case end*/
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 27 /* Trait */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 28 /* Reference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 29 /* MutableReference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((jakt__platform::Target::active()))).pointer_size()))));
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

ErrorOr<types::Value> cast_value_to_type(types::Value const this_value,ids::TypeId const type_id,NonnullRefPtr<interpreter::Interpreter> const interpreter,bool const saturating) {
{
NonnullRefPtr<typename types::Type> const type = ((((interpreter)->program))->get_type(type_id));
bool const is_optional = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((id).equals(TRY((((((interpreter)->program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Optional"sv)))))))));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>((value)))))),((this_value).span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>((value)))))),((this_value).span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>((value)))))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>((value)))))),((this_value).span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>((value)))))),((this_value).span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>((value)))))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U32((infallible_integer_cast<u32>((value)))))),((this_value).span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U32((infallible_integer_cast<u32>((value)))))),((this_value).span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U32((infallible_integer_cast<u32>((value)))))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U32((infallible_integer_cast<u32>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U64((infallible_integer_cast<u64>((value)))))),((this_value).span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U64((infallible_integer_cast<u64>((value)))))),((this_value).span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U64((infallible_integer_cast<u64>((value)))))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U64((infallible_integer_cast<u64>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>((value)))))),((this_value).span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>((value)))))),((this_value).span)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>((value)))))),((this_value).span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>((value)))))),((this_value).span)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I32((infallible_integer_cast<i32>((value)))))),((this_value).span)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I32((infallible_integer_cast<i32>((value)))))),((this_value).span)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I32((infallible_integer_cast<i32>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I64((infallible_integer_cast<i64>((value)))))),((this_value).span)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I64((infallible_integer_cast<i64>((value)))))),((this_value).span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I64((infallible_integer_cast<i64>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue(this_value);
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(this_value);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(this_value))),((this_value).span)));
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

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> value_to_checked_expression(types::Value const this_value,NonnullRefPtr<interpreter::Interpreter> interpreter) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
{
TRY((((interpreter)->error(TRY(ByteString::from_utf8("Cannot convert void to expression"sv)),((this_value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::Boolean(JaktInternal::OptionalNone(),x,((this_value).span)))));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::U8(x),((this_value).span),types::builtin(types::BuiltinType::U8())))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::U16(x),((this_value).span),types::builtin(types::BuiltinType::U16())))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::U32(x),((this_value).span),types::builtin(types::BuiltinType::U32())))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::U64(x),((this_value).span),types::builtin(types::BuiltinType::U64())))));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::I8(x),((this_value).span),types::builtin(types::BuiltinType::I8())))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::I16(x),((this_value).span),types::builtin(types::BuiltinType::I16())))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::I32(x),((this_value).span),types::builtin(types::BuiltinType::I32())))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::I64(x),((this_value).span),types::builtin(types::BuiltinType::I64())))));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::F32(x),((this_value).span),types::builtin(types::BuiltinType::F32())))));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::F64(x),((this_value).span),types::builtin(types::BuiltinType::F64())))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((x)))),((this_value).span),types::builtin(types::BuiltinType::Usize())))));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::QuotedString(JaktInternal::OptionalNone(),types::CheckedStringLiteral(types::StringLiteral::Static(TRY((utility::escape_for_quotes(x)))),TRY((((((interpreter)->program))->find_or_add_type_id(TRY((types::Type::Struct(parser::CheckedQualifiers(false),TRY((((((interpreter)->program))->find_struct_in_prelude(TRY(ByteString::from_utf8("String"sv))))))))),((((interpreter)->program))->prelude_module_id()),false)))),true),((this_value).span)))));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::QuotedString(JaktInternal::OptionalNone(),types::CheckedStringLiteral(types::StringLiteral::Static(TRY((utility::escape_for_quotes(x)))),TRY((((((interpreter)->program))->find_or_add_type_id(TRY((types::Type::Struct(parser::CheckedQualifiers(false),TRY((((((interpreter)->program))->find_struct_in_prelude(TRY(ByteString::from_utf8("StringView"sv))))))))),((((interpreter)->program))->prelude_module_id()),false)))),true),((this_value).span)))));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::CCharacterConstant(JaktInternal::OptionalNone(),TRY((__jakt_format((StringView::from_string_literal("{}"sv)),x))),((this_value).span)))));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((x)))),((this_value).span),types::builtin(types::BuiltinType::CInt())))));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::OptionalNone(JaktInternal::OptionalNone(),((this_value).span),types::unknown_type_id()))));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_192; {
NonnullRefPtr<typename types::CheckedExpression> const expr = TRY((interpreter::value_to_checked_expression(value,interpreter)));
ids::TypeId const inner_type_id = ((expr)->type());
ids::StructId const optional_struct_id = TRY((((((interpreter)->program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Optional"sv))))));
NonnullRefPtr<typename types::Type> const type = TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),optional_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({inner_type_id})))))));
ids::TypeId const type_id = TRY((((interpreter)->find_or_add_type_id(type))));
__jakt_var_192 = TRY((types::CheckedExpression::OptionalSome(JaktInternal::OptionalNone(),expr,((this_value).span),type_id))); goto __jakt_label_178;

}
__jakt_label_178:; __jakt_var_192.release_value(); }));
};/*case end*/
case 26 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_193; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
TRY((((vals).push(TRY((interpreter::value_to_checked_expression(field,interpreter)))))));
}

}
}

__jakt_var_193 = TRY((types::CheckedExpression::JaktTuple(JaktInternal::OptionalNone(),vals,((this_value).span),type_id))); goto __jakt_label_179;

}
__jakt_label_179:; __jakt_var_193.release_value(); }));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_194; {
if ((!(((constructor).has_value())))){
TRY((((interpreter)->error_with_hint(TRY(ByteString::from_utf8("Cannot convert struct to expression without constructor"sv)),((this_value).span),TRY(ByteString::from_utf8("Given struct cannot be created from its contents in any known way"sv)),((this_value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> materialised_fields = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
TRY((((materialised_fields).push(TRY((interpreter::value_to_checked_expression(field,interpreter)))))));
}

}
}

types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
JaktInternal::DynamicArray<types::ResolvedNamespace> reversed_namespace = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
JaktInternal::Optional<ids::ScopeId> scope_id = ((struct_).scope_id);
while (((scope_id).has_value())){
NonnullRefPtr<types::Scope> const scope = TRY((((((interpreter)->program))->get_scope((scope_id.value())))));
if (((((scope)->namespace_name)).has_value())){
TRY((((reversed_namespace).push(types::ResolvedNamespace((((scope)->namespace_name).value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
}
(scope_id = ((scope)->parent));
}
JaktInternal::DynamicArray<types::ResolvedNamespace> namespace_ = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((reversed_namespace).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((namespace_).push(((reversed_namespace)[JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))])))));
}

}
}

NonnullRefPtr<types::CheckedFunction> const callee = ((((interpreter)->program))->get_function((constructor.value())));
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
(((materialised_fields).size()),((((callee)->params)).size()))){
TRY((((interpreter)->error_with_hint(TRY(ByteString::from_utf8("Too many arguments for constructor"sv)),((this_value).span),TRY((__jakt_format((StringView::from_string_literal("Expected at most {} arguments, got {}"sv)),((((callee)->params)).size()),((materialised_fields).size())))),((this_value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ByteString const name = ((struct_).name);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> args = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((materialised_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const arg = ((materialised_fields)[i]);
ByteString const label = ((((((((callee)->params))[i])).variable))->name);
TRY((((args).push((Tuple{label, arg})))));
}

}
}

types::CheckedCall const call = types::CheckedCall(namespace_,name,args,(TRY((DynamicArray<ids::TypeId>::create_with({})))),constructor,((struct_).type_id),((callee)->can_throw),JaktInternal::OptionalNone(),parser::InlineState::Default());
__jakt_var_194 = TRY((types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,((this_value).span),((struct_).type_id)))); goto __jakt_label_180;

}
__jakt_label_180:; __jakt_var_194.release_value(); }));
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_195; {
if ((!(((constructor).has_value())))){
TRY((((interpreter)->error_with_hint(TRY(ByteString::from_utf8("Cannot convert struct to expression without constructor"sv)),((this_value).span),TRY(ByteString::from_utf8("Given struct cannot be created from its contents in any known way"sv)),((this_value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> materialised_fields = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
TRY((((materialised_fields).push(TRY((interpreter::value_to_checked_expression(field,interpreter)))))));
}

}
}

types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
JaktInternal::DynamicArray<types::ResolvedNamespace> reversed_namespace = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
JaktInternal::Optional<ids::ScopeId> scope_id = ((struct_).scope_id);
while (((scope_id).has_value())){
NonnullRefPtr<types::Scope> const scope = TRY((((((interpreter)->program))->get_scope((scope_id.value())))));
if (((((scope)->namespace_name)).has_value())){
TRY((((reversed_namespace).push(types::ResolvedNamespace((((scope)->namespace_name).value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
}
(scope_id = ((scope)->parent));
}
JaktInternal::DynamicArray<types::ResolvedNamespace> namespace_ = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((reversed_namespace).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((namespace_).push(((reversed_namespace)[JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))])))));
}

}
}

NonnullRefPtr<types::CheckedFunction> const callee = ((((interpreter)->program))->get_function((constructor.value())));
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
(((materialised_fields).size()),((((callee)->params)).size()))){
TRY((((interpreter)->error_with_hint(TRY(ByteString::from_utf8("Too many arguments for constructor"sv)),((this_value).span),TRY((__jakt_format((StringView::from_string_literal("Expected at most {} arguments, got {}"sv)),((((callee)->params)).size()),((materialised_fields).size())))),((this_value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ByteString const name = ((struct_).name);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> args = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((materialised_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const arg = ((materialised_fields)[i]);
ByteString const label = ((((((((callee)->params))[i])).variable))->name);
TRY((((args).push((Tuple{label, arg})))));
}

}
}

types::CheckedCall const call = types::CheckedCall(namespace_,name,args,(TRY((DynamicArray<ids::TypeId>::create_with({})))),constructor,((struct_).type_id),((callee)->can_throw),JaktInternal::OptionalNone(),parser::InlineState::Default());
__jakt_var_195 = TRY((types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,((this_value).span),((struct_).type_id)))); goto __jakt_label_181;

}
__jakt_label_181:; __jakt_var_195.release_value(); }));
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_196; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> materialised_fields = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
TRY((((materialised_fields).push(TRY((interpreter::value_to_checked_expression(field,interpreter)))))));
}

}
}

types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
JaktInternal::DynamicArray<types::ResolvedNamespace> reversed_namespace = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
JaktInternal::Optional<ids::ScopeId> scope_id = ((enum_).scope_id);
while (((scope_id).has_value())){
NonnullRefPtr<types::Scope> const scope = TRY((((((interpreter)->program))->get_scope((scope_id.value())))));
if (((((scope)->namespace_name)).has_value())){
TRY((((reversed_namespace).push(types::ResolvedNamespace((((scope)->namespace_name).value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
}
(scope_id = ((scope)->parent));
}
JaktInternal::DynamicArray<types::ResolvedNamespace> namespace_ = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((reversed_namespace).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((namespace_).push(((reversed_namespace)[JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))])))));
}

}
}

TRY((((namespace_).push(types::ResolvedNamespace(((enum_).name),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
ByteString const name = ((enum_).name);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> args = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((materialised_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const arg = ((materialised_fields)[i]);
TRY((((args).push((Tuple{TRY(ByteString::from_utf8(""sv)), arg})))));
}

}
}

NonnullRefPtr<types::CheckedFunction> const callee = ((((interpreter)->program))->get_function(constructor));
types::CheckedCall const call = types::CheckedCall(namespace_,((callee)->name),args,(TRY((DynamicArray<ids::TypeId>::create_with({})))),constructor,((enum_).type_id),((callee)->can_throw),JaktInternal::OptionalNone(),parser::InlineState::Default());
__jakt_var_196 = TRY((types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,((this_value).span),((enum_).type_id)))); goto __jakt_label_182;

}
__jakt_label_182:; __jakt_var_196.release_value(); }));
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_197; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
TRY((((vals).push(TRY((interpreter::value_to_checked_expression(value,interpreter)))))));
}

}
}

ids::TypeId const inner_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected generic instance of Array while materialising an array"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_197 = TRY((types::CheckedExpression::JaktArray(JaktInternal::OptionalNone(),vals,JaktInternal::OptionalNone(),((this_value).span),type_id,inner_type_id))); goto __jakt_label_183;

}
__jakt_label_183:; __jakt_var_197.release_value(); }));
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_198; {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> vals = (TRY((DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((vals).push((Tuple{TRY((interpreter::value_to_checked_expression(((keys)[i]),interpreter))), TRY((interpreter::value_to_checked_expression(((values)[i]),interpreter)))})))));
}

}
}

JaktInternal::Tuple<ids::TypeId,ids::TypeId> const key_type_id_value_type_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<ids::TypeId,ids::TypeId>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue((Tuple{((args)[static_cast<i64>(0LL)]), ((args)[static_cast<i64>(1LL)])}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected generic instance of Dictionary while materialising an array"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::TypeId const key_type_id = ((key_type_id_value_type_id_).template get<0>());
ids::TypeId const value_type_id = ((key_type_id_value_type_id_).template get<1>());

__jakt_var_198 = TRY((types::CheckedExpression::JaktDictionary(JaktInternal::OptionalNone(),vals,((this_value).span),type_id,key_type_id,value_type_id))); goto __jakt_label_184;

}
__jakt_label_184:; __jakt_var_198.release_value(); }));
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_199; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((vals).push(TRY((interpreter::value_to_checked_expression(((values)[i]),interpreter)))))));
}

}
}

ids::TypeId const value_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected generic instance of Set while materialising an array"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_199 = TRY((types::CheckedExpression::JaktSet(JaktInternal::OptionalNone(),vals,((this_value).span),type_id,value_type_id))); goto __jakt_label_185;

}
__jakt_label_185:; __jakt_var_199.release_value(); }));
};/*case end*/
case 27 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::Dictionary<ByteString,types::Value> const& captures = __jakt_match_value.captures;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::TypeId const& type_id = __jakt_match_value.type_id;
types::CheckedBlock const& block = __jakt_match_value.block;
JaktInternal::DynamicArray<types::CheckedParameter> const& checked_params = __jakt_match_value.checked_params;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_200; {
NonnullRefPtr<types::Scope> const parent_scope = TRY((((((interpreter)->program))->get_scope(((block).scope_id)))));
ids::ScopeId const inherited_scope_id = TRY((((((interpreter)->program))->create_scope(((block).scope_id),((parent_scope)->can_throw),TRY((__jakt_format((StringView::from_string_literal("synthetic({})"sv)),((parent_scope)->debug_name)))),((type_id).module),true))));
NonnullRefPtr<types::Scope> inherited_scope = TRY((((((interpreter)->program))->get_scope(inherited_scope_id))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::DictionaryIterator<ByteString,types::Value> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,types::Value> capture = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const value = TRY((interpreter::value_to_checked_expression(((capture).template get<1>()),interpreter)));
ids::VarId const var_id = TRY((((((((interpreter)->program))->get_module(((type_id).module))))->add_variable(TRY((types::CheckedVariable::__jakt_create(((capture).template get<0>()),((value)->type()),false,((this_value).span),JaktInternal::OptionalNone(),types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY((((statements).push(TRY((types::CheckedStatement::VarDecl(var_id,value,((this_value).span))))))));
TRY((((((inherited_scope)->comptime_bindings)).set(((capture).template get<0>()),((capture).template get<1>())))));
}

}
}

TRY((((statements).push_values(((((block).statements)))))));
types::CheckedBlock const new_block = types::CheckedBlock(statements,inherited_scope_id,((block).control_flow),((block).yielded_type),((block).yielded_none));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::__jakt_create(TRY(ByteString::from_utf8("synthetic_lambda"sv)),((this_value).span),types::CheckedVisibility::Public(),return_type_id,JaktInternal::OptionalNone(),checked_params,TRY((types::FunctionGenerics::__jakt_create(inherited_scope_id,checked_params,(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<ids::TypeId>>::create_with({}))))))),new_block,can_throw,parser::FunctionType::Expression(),parser::FunctionLinkage::Internal(),inherited_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),parser::InlineState::Default())));
Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> const& register_function = ((((((interpreter)->typecheck_functions))->register_function)));
ids::FunctionId const pseudo_function_id = TRY((register_function(checked_function)));
__jakt_var_200 = TRY((types::CheckedExpression::Function(JaktInternal::OptionalNone(),(TRY((DynamicArray<types::CheckedCapture>::create_with({})))),checked_params,can_throw,return_type_id,new_block,((this_value).span),type_id,pseudo_function_id,scope_id))); goto __jakt_label_186;

}
__jakt_label_186:; __jakt_var_200.release_value(); }));
};/*case end*/
default: {
{
TRY((((interpreter)->error(TRY((__jakt_format((StringView::from_string_literal("Cannot materialise the type {}"sv)),((this_value).impl)))),((this_value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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

ErrorOr<ByteString> interpreter::InterpreterScope::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("InterpreterScope("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("bindings: {}, ", bindings));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("parent: {}, ", parent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_bindings: {}, ", type_bindings));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("defers: {}", defers));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> interpreter::InterpreterScope::set(ByteString const name,types::Value const value) {
{
if (((((*this).bindings)).contains(name))){
TRY(((*this).bindings).set(name, value));
return {};
}
JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> scope = ((*this).parent);
while (((scope).has_value())){
if ((((((scope.value()))->bindings)).contains(name))){
TRY((((scope.value()))->bindings).set(name, value));
return {};
}
(scope = (((scope.value()))->parent));
}
return Error::__jakt_from_string_literal((StringView::from_string_literal("Could not find binding"sv)));
}
return {};
}

ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> interpreter::InterpreterScope::create(JaktInternal::Dictionary<ByteString,types::Value> const bindings,JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent,JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const type_bindings) {
{
return TRY((interpreter::InterpreterScope::__jakt_create(bindings,parent,type_bindings,(TRY((DynamicArray<interpreter::Deferred>::create_with({})))))));
}
}

ErrorOr<void> interpreter::InterpreterScope::defer_statement(NonnullRefPtr<typename types::CheckedStatement> const statement) {
{
TRY((((((*this).defers)).push(interpreter::Deferred::Statement(statement)))));
}
return {};
}

ErrorOr<void> interpreter::InterpreterScope::perform_defers(NonnullRefPtr<interpreter::Interpreter> interpreter,utility::Span const span) {
{
while ((!(((((*this).defers)).is_empty())))){
JaktInternal::Optional<interpreter::Deferred> const deferred = ((((*this).defers)).pop());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<void>>{
auto&& __jakt_match_variant = (deferred.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((interpreter)->execute_expression(expr,*this)))));
};/*case end*/
case 1 /* Statement */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Statement;NonnullRefPtr<typename types::CheckedStatement> const& statement = __jakt_match_value.value;
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

ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> interpreter::InterpreterScope::from_runtime_scope(ids::ScopeId const scope_id,NonnullRefPtr<types::CheckedProgram> const program,JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent) {
{
JaktInternal::Dictionary<ByteString,types::Value> bindings = (TRY((Dictionary<ByteString, types::Value>::create_with_entries({}))));
JaktInternal::Optional<ids::ScopeId> current_id = scope_id;
while (((current_id).has_value())){
NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope((current_id.value())))));
{
JaktInternal::DictionaryIterator<ByteString,types::Value> _magic = ((((scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,types::Value> pair = (_magic_value.value());
{
if (((bindings).contains(((pair).template get<0>())))){
continue;
}
TRY((((bindings).set(((pair).template get<0>()),((pair).template get<1>())))));
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
ids::ScopeId mixin = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const mixin_scope = TRY((((program)->get_scope(mixin))));
{
JaktInternal::DictionaryIterator<ByteString,types::Value> _magic = ((((mixin_scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,types::Value> pair = (_magic_value.value());
{
if (((bindings).contains(((pair).template get<0>())))){
continue;
}
TRY((((bindings).set(((pair).template get<0>()),((pair).template get<1>())))));
}

}
}

}

}
}

(current_id = ((scope)->parent));
}
return TRY((interpreter::InterpreterScope::__jakt_create(bindings,parent,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))),(TRY((DynamicArray<interpreter::Deferred>::create_with({})))))));
}
}

ErrorOr<JaktInternal::Dictionary<ByteString,types::Value>> interpreter::InterpreterScope::all_bindings() const {
{
JaktInternal::Dictionary<ByteString,types::Value> bindings = (TRY((Dictionary<ByteString, types::Value>::create_with_entries({}))));
JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> scope = static_cast<JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>>>(*this);
while (((scope).has_value())){
{
JaktInternal::DictionaryIterator<ByteString,types::Value> _magic = (((((scope.value()))->bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,types::Value> pair = (_magic_value.value());
{
if (((bindings).contains(((pair).template get<0>())))){
continue;
}
TRY((((bindings).set(((pair).template get<0>()),((pair).template get<1>())))));
}

}
}

(scope = (((scope.value()))->parent));
}
return bindings;
}
}

ErrorOr<void> interpreter::InterpreterScope::type_map_for_substitution_helper(JaktInternal::Dictionary<ids::TypeId,ids::TypeId>& map) const {
{
if (((((*this).parent)).has_value())){
TRY(((((((*this).parent).value()))->type_map_for_substitution_helper(map))));
}
{
JaktInternal::DictionaryIterator<ids::TypeId,ids::TypeId> _magic = ((((*this).type_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ids::TypeId,ids::TypeId> pair = (_magic_value.value());
{
TRY((((((map))).set(((pair).template get<0>()),((pair).template get<1>())))));
}

}
}

}
return {};
}

ErrorOr<types::GenericInferences> interpreter::InterpreterScope::type_map_for_substitution() const {
{
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> map = (TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))));
TRY((((*this).type_map_for_substitution_helper(((map))))));
return types::GenericInferences(map);
}
}

interpreter::InterpreterScope::InterpreterScope(JaktInternal::Dictionary<ByteString,types::Value> a_bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> a_parent, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> a_type_bindings, JaktInternal::DynamicArray<interpreter::Deferred> a_defers): bindings(move(a_bindings)), parent(move(a_parent)), type_bindings(move(a_type_bindings)), defers(move(a_defers)){}
ErrorOr<NonnullRefPtr<InterpreterScope>> interpreter::InterpreterScope::__jakt_create(JaktInternal::Dictionary<ByteString,types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> type_bindings, JaktInternal::DynamicArray<interpreter::Deferred> defers) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) InterpreterScope (move(bindings), move(parent), move(type_bindings), move(defers)))); return o; }
ErrorOr<void> interpreter::InterpreterScope::defer_expression(NonnullRefPtr<typename types::CheckedExpression> const expr) {
{
TRY((((((*this).defers)).push(interpreter::Deferred::Expression(expr)))));
}
return {};
}

ErrorOr<types::Value> interpreter::InterpreterScope::must_get(ByteString const name) const {
{
if (((((*this).bindings)).contains(name))){
return ((((*this).bindings))[name]);
}
JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> scope = ((*this).parent);
while (((scope).has_value())){
if ((((((scope.value()))->bindings)).contains(name))){
return (((((scope.value()))->bindings))[name]);
}
(scope = (((scope.value()))->parent));
}
return Error::__jakt_from_string_literal((StringView::from_string_literal("Could not find binding"sv)));
}
}

ErrorOr<ids::TypeId> interpreter::InterpreterScope::map_type(ids::TypeId const id) const {
{
if (((((*this).type_bindings)).contains(id))){
return ((((*this).type_bindings))[id]);
}
JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> scope = ((*this).parent);
while (((scope).has_value())){
if ((((((scope.value()))->type_bindings)).contains(id))){
return (((((scope.value()))->type_bindings))[id]);
}
(scope = (((scope.value()))->parent));
}
return id;
}
}

ErrorOr<ByteString> interpreter::Interpreter::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("Interpreter("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("program: {}, ", *program));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("spans: {}, ", spans));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("reflected_type_cache: {}, ", reflected_type_cache));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("seen_reflected_types: {}, ", seen_reflected_types));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_function_id: {}, ", current_function_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("typecheck_functions: {}", *typecheck_functions));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<ByteString> interpreter::Interpreter::string_from_value(types::Value const value) {
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
TRY((((*this).error(TRY(ByteString::from_utf8("Expected string value"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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

ErrorOr<void> interpreter::Interpreter::update_binding(NonnullRefPtr<typename types::CheckedExpression> const binding,NonnullRefPtr<interpreter::InterpreterScope> scope,types::Value const value,utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *binding;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
{
TRY((((scope)->set(((var)->name),value))));
if (((((value).impl))->__jakt_init_index() == 27 /* Function */)){
types::CheckedBlock const block = (((value).impl))->as.Function.block;
JaktInternal::Optional<ids::FunctionId> const pseudo_function_id = (((value).impl))->as.Function.pseudo_function_id;
if (((pseudo_function_id).has_value())){
ids::FunctionId const id = (pseudo_function_id.value());
(((((((*this).program))->get_function(id)))->block) = block);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
{
JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ids::StructId> fields_struct_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ids::StructId>, ErrorOr<void>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ids::StructId>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue((Tuple{fields, struct_id}));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue((Tuple{fields, struct_id}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid left-hand side in assignment"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Should not be happening here"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> fields = ((fields_struct_id_).template get<0>());
ids::StructId struct_id = ((fields_struct_id_).template get<1>());

JaktInternal::DynamicArray<types::CheckedField> const field_decls = ((((((*this).program))->get_struct(struct_id))).fields);
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
if (((((((((*this).program))->get_variable(((((field_decls)[i])).variable_id))))->name)) == (name))){
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
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& index = __jakt_match_value.index;
{
JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ids::EnumId> fields_enum_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ids::EnumId>, ErrorOr<void>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ids::EnumId>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue((Tuple{fields, enum_id}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid left-hand side in assignment"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Should not be happening here"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> fields = ((fields_enum_id_).template get<0>());
ids::EnumId enum_id = ((fields_enum_id_).template get<1>());

JaktInternal::DynamicArray<types::CheckedField> const field_decls = ((((((*this).program))->get_enum(enum_id))).fields);
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
if (((((((((*this).program))->get_variable(((((field_decls)[i])).variable_id))))->name)) == (index))){
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid left-hand side of assignment {}"sv)),binding))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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

interpreter::Interpreter::Interpreter(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, JaktInternal::DynamicArray<utility::Span> a_spans, JaktInternal::Dictionary<ids::TypeId,types::Value> a_reflected_type_cache, JaktInternal::Set<ids::TypeId> a_seen_reflected_types, JaktInternal::Optional<ids::FunctionId> a_current_function_id, NonnullRefPtr<types::TypecheckFunctions> a_typecheck_functions): compiler(move(a_compiler)), program(move(a_program)), spans(move(a_spans)), reflected_type_cache(move(a_reflected_type_cache)), seen_reflected_types(move(a_seen_reflected_types)), current_function_id(move(a_current_function_id)), typecheck_functions(move(a_typecheck_functions)){}
ErrorOr<NonnullRefPtr<Interpreter>> interpreter::Interpreter::__jakt_create(NonnullRefPtr<compiler::Compiler> compiler, NonnullRefPtr<types::CheckedProgram> program, JaktInternal::DynamicArray<utility::Span> spans, JaktInternal::Dictionary<ids::TypeId,types::Value> reflected_type_cache, JaktInternal::Set<ids::TypeId> seen_reflected_types, JaktInternal::Optional<ids::FunctionId> current_function_id, NonnullRefPtr<types::TypecheckFunctions> typecheck_functions) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Interpreter (move(compiler), move(program), move(spans), move(reflected_type_cache), move(seen_reflected_types), move(current_function_id), move(typecheck_functions)))); return o; }
ErrorOr<types::CheckedBlock> interpreter::Interpreter::typecheck_block(parser::ParsedBlock const block,ids::ScopeId const scope,JaktInternal::Optional<ids::FunctionId> const function_id) {
{
return TRY((interpreter::Interpreter::invoke_typecheck_block(((((((*this).typecheck_functions))->block))),block,scope,function_id)));
}
}

ErrorOr<types::Value> interpreter::Interpreter::reflect_methods(ids::ScopeId const scope_id,utility::Span const span,NonnullRefPtr<interpreter::InterpreterScope> const interpreter_scope) {
{
ids::StructId const method_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Method"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Method to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::StructId const function_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Function"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Function to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const method_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(method_struct_id))).scope_id),TRY(ByteString::from_utf8("Method"sv)),JaktInternal::OptionalNone())))).value());
ids::FunctionId const function_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(function_struct_id))).scope_id),TRY(ByteString::from_utf8("Function"sv)),JaktInternal::OptionalNone())))).value());
ids::TypeId const type_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Type"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((*this).program))->get_enum(id))).type_id));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Type to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> method_values = (TRY((DynamicArray<types::Value>::create_with({}))));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(scope_id))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> name__ids__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt__name__ids__ = name__ids__;
ByteString const name = ((jakt__name__ids__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const ids = ((jakt__name__ids__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((ids).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(id));
types::Value const value = types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).array_value_of_type((TRY((DynamicArray<types::Value>::create_with({})))),type_type_id,span)))), TRY((((*this).reflect_type(((function)->return_type_id),span,interpreter_scope)))), TRY((((*this).bool_value(((function)->can_throw),span)))), TRY((((*this).bool_value(((function)->is_comptime),span))))})))),function_struct_id,function_struct_constructor))),span);
TRY((((method_values).push(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({value})))),method_struct_id,method_struct_constructor))),span)))));
}

}
}

}

}
}

return types::Value(TRY((types::ValueImpl::JaktArray(method_values,TRY((((*this).array_type_of_struct(method_struct_id))))))),span);
}
}

ErrorOr<types::Value> interpreter::Interpreter::bool_value(bool const value,utility::Span const span) {
{
return types::Value(TRY((types::ValueImpl::Bool(value))),span);
}
}

ErrorOr<types::Value> interpreter::Interpreter::string_value(ByteString const string,utility::Span const span) {
{
return types::Value(TRY((types::ValueImpl::JaktString(string))),span);
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> interpreter::Interpreter::perform_final_interpretation_expr_pass(NonnullRefPtr<typename types::CheckedExpression> const expr,NonnullRefPtr<interpreter::InterpreterScope> const scope,JaktInternal::Optional<ids::FunctionId> const function_id) {
{
if (((expr)->__jakt_init_index() == 6 /* UnaryOp */)){
types::CheckedUnaryOperator const op = (expr)->as.UnaryOp.op;
if (((op).__jakt_init_index() == 11 /* TypeCast */)){
warnln((StringView::from_string_literal("{0:c}[31mFixup{0:c}[0m {1}"sv)),static_cast<i64>(27LL),expr);
}
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
utility::Span const& span = __jakt_match_value.span;
{
interpreter::StatementResult const index_result = TRY((((*this).execute_expression(index,scope))));
types::NumericOrStringValue const index_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::StringValue(val));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Index expression evaluation failed: expected numeric or string type, found {}"sv)),((value).impl)))),span))));
return TRY((types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,types::builtin(types::BuiltinType::Void()))));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Index expression evaluation returned an invalid object {}"sv)),index_result))),span))));
return TRY((types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,types::builtin(types::BuiltinType::Void()))));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_constant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* StringValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringValue;ByteString const& field = __jakt_match_value.value;
{
ids::TypeId const checked_expr_type_id = TRY((((scope)->map_type(((expr)->type())))));
NonnullRefPtr<typename types::Type> const checked_expr_type = ((((*this).program))->get_type(checked_expr_type_id));
ids::StructId const optional_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Optional"sv))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_expr_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
ids::TypeId type_id = checked_expr_type_id;
if (is_optional){
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error(TRY(ByteString::from_utf8("Optional chaining is only allowed on optional types"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
}
(type_id = ((args)[static_cast<i64>(0LL)]));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField member_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((((*this).program))->get_variable(((member_id).variable_id)));
if (((((member)->name)) == (field))){
ids::TypeId resolved_type_id = TRY((((scope)->map_type(((member)->type_id)))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),optional_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({resolved_type_id}))))))))))));
}
return TRY((types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),expr,field,((member_id).variable_id),span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField member_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((((*this).program))->get_variable(((member_id).variable_id)));
if (((((member)->name)) == (field))){
ids::TypeId resolved_type_id = TRY((((scope)->map_type(((member)->type_id)))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),optional_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({resolved_type_id}))))))))))));
}
return TRY((types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),expr,field,((member_id).variable_id),span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv)),TRY((((((*this).program))->type_name(checked_expr_type_id,false))))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
if (is_optional){
TRY((((*this).error(TRY(ByteString::from_utf8("Optional chaining is not allowed on non-optional types"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
}
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField member_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((((*this).program))->get_variable(((member_id).variable_id)));
if (((((member)->name)) == (field))){
ids::TypeId const resolved_type_id = TRY((((scope)->map_type(((member)->type_id)))));
return TRY((types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),expr,field,((member_id).variable_id),span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv)),TRY((((((*this).program))->type_name(checked_expr_type_id,false))))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid operation"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("Unimplemented expression"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* SignedNumericValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SignedNumericValue;i64 const& val = __jakt_match_value.value;
{
TRY((((*this).error(TRY(ByteString::from_utf8("Unimplemented expression"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedUnaryOperator, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;types::CheckedTypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::CheckedUnaryOperator::TypeCast(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedTypeCast, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::CheckedTypeCast::Fallible(TRY((((scope)->map_type(type_id))))));
};/*case end*/
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::CheckedTypeCast::Infallible(TRY((((scope)->map_type(type_id))))));
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
}),span,TRY((((scope)->map_type(type_id))))))));
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
types::CheckedBinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::BinaryOp(JaktInternal::OptionalNone(),TRY((((*this).perform_final_interpretation_expr_pass(lhs,scope,function_id)))),op,TRY((((*this).perform_final_interpretation_expr_pass(rhs,scope,function_id)))),span,TRY((((scope)->map_type(type_id))))))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_201; {
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> new_args = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((new_args).push((Tuple{((arg).template get<0>()), TRY((((*this).perform_final_interpretation_expr_pass(((arg).template get<1>()),scope,function_id))))})))));
}

}
}

__jakt_var_201 = TRY((types::CheckedExpression::Call(JaktInternal::OptionalNone(),types::CheckedCall(((call).namespace_),((call).name),new_args,((call).type_args),((call).function_id),((call).return_type),((call).callee_throws),JaktInternal::OptionalNone(),parser::InlineState::Default()),span,type_id))); goto __jakt_label_187;

}
__jakt_label_187:; __jakt_var_201.release_value(); }));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_202; {
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> new_args = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((new_args).push((Tuple{((arg).template get<0>()), TRY((((*this).perform_final_interpretation_expr_pass(((arg).template get<1>()),scope,function_id))))})))));
}

}
}

__jakt_var_202 = TRY((types::CheckedExpression::MethodCall(JaktInternal::OptionalNone(),TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),types::CheckedCall(((call).namespace_),((call).name),new_args,((call).type_args),((call).function_id),((call).return_type),((call).callee_throws),JaktInternal::OptionalNone(),parser::InlineState::Default()),span,is_optional,type_id))); goto __jakt_label_188;

}
__jakt_label_188:; __jakt_var_202.release_value(); }));
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

ErrorOr<types::CheckedBlock> interpreter::Interpreter::perform_final_interpretation_pass(types::CheckedBlock const block,JaktInternal::Optional<ids::ScopeId> const runtime_scope,NonnullRefPtr<interpreter::InterpreterScope> const scope,JaktInternal::Optional<ids::FunctionId> const function_id) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedStatement> const new_statement = TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))));
TRY((((statements).push(new_statement))));
}

}
}

return types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
}
}

ErrorOr<types::CheckedBlock> interpreter::Interpreter::perform_final_interpretation_pass(parser::ParsedBlock const block,ids::ScopeId const runtime_scope,NonnullRefPtr<interpreter::InterpreterScope> const scope,JaktInternal::Optional<ids::FunctionId> const function_id) {
{
NonnullRefPtr<types::Scope> rscope = TRY((((((*this).program))->get_scope(runtime_scope))));
{
JaktInternal::DictionaryIterator<ByteString,types::Value> _magic = ((TRY((((scope)->all_bindings())))).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,types::Value> name__value__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,types::Value> const jakt__name__value__ = name__value__;
ByteString const name = ((jakt__name__value__).template get<0>());
types::Value const value = ((jakt__name__value__).template get<1>());

TRY((((((rscope)->comptime_bindings)).set(name,value))));
}

}
}

return TRY((((*this).perform_final_interpretation_pass(TRY((((*this).typecheck_block(block,runtime_scope,function_id)))),runtime_scope,scope,function_id))));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> interpreter::Interpreter::perform_final_interpretation_pass(NonnullRefPtr<typename types::CheckedStatement> const statement,NonnullRefPtr<interpreter::InterpreterScope> const scope,JaktInternal::Optional<ids::FunctionId> const function_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedStatement>, ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::Expression(TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),span))));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename types::CheckedStatement> const& statement = __jakt_match_value.statement;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::Defer(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id)))),span))));
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::DestructuringAssignment(vars,TRY((((*this).perform_final_interpretation_pass(var_decl,scope,function_id)))),span))));
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename types::CheckedExpression> const& init = __jakt_match_value.init;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::VarDecl(var_id,TRY((((*this).perform_final_interpretation_expr_pass(init,scope,function_id)))),span))));
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedStatement>> __jakt_var_203; {
NonnullRefPtr<typename types::CheckedExpression> const new_condition = TRY((((*this).perform_final_interpretation_expr_pass(condition,scope,function_id))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> then_statements = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((then_block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
TRY((((then_statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))))));
}

}
}

types::CheckedBlock const new_then_block = types::CheckedBlock(then_statements,((then_block).scope_id),((then_block).control_flow),((then_block).yielded_type),((then_block).yielded_none));
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const new_else_statement = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>>,ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>>>(TRY((((*this).perform_final_interpretation_pass((else_statement.value()),scope,function_id))))));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_203 = TRY((types::CheckedStatement::If(new_condition,new_then_block,new_else_statement,span))); goto __jakt_label_189;

}
__jakt_label_189:; __jakt_var_203.release_value(); }));
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedStatement>> __jakt_var_204; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
TRY((((statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))))));
}

}
}

types::CheckedBlock const new_block = types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
__jakt_var_204 = TRY((types::CheckedStatement::Block(new_block,span))); goto __jakt_label_190;

}
__jakt_label_190:; __jakt_var_204.release_value(); }));
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedStatement>> __jakt_var_205; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
TRY((((statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))))));
}

}
}

types::CheckedBlock const new_block = types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
__jakt_var_205 = TRY((types::CheckedStatement::Loop(new_block,span))); goto __jakt_label_191;

}
__jakt_label_191:; __jakt_var_205.release_value(); }));
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedStatement>> __jakt_var_206; {
NonnullRefPtr<typename types::CheckedExpression> const new_condition = TRY((((*this).perform_final_interpretation_expr_pass(condition,scope,function_id))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
TRY((((statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))))));
}

}
}

types::CheckedBlock const new_block = types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
__jakt_var_206 = TRY((types::CheckedStatement::While(new_condition,new_block,span))); goto __jakt_label_192;

}
__jakt_label_192:; __jakt_var_206.release_value(); }));
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& val = __jakt_match_value.val;
JaktInternal::Optional<utility::Span> const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedStatement>,ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::Return(TRY((((*this).perform_final_interpretation_expr_pass((val.value()),scope,function_id)))),span))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::Throw(TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),span))));
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::Yield(TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),span))));
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

ErrorOr<types::Value> interpreter::Interpreter::array_value_of_type(JaktInternal::DynamicArray<types::Value> const values,ids::TypeId const type,utility::Span const span) {
{
ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Array"sv))))));
NonnullRefPtr<typename types::Type> const array_type = TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),array_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({type})))))));
ids::TypeId const array_type_id = TRY((((*this).find_or_add_type_id(array_type))));
return types::Value(TRY((types::ValueImpl::JaktArray(values,array_type_id))),span);
}
}

ErrorOr<ids::TypeId> interpreter::Interpreter::string_type() {
{
ids::StructId const string_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("String"sv))))));
NonnullRefPtr<typename types::Type> const type = TRY((types::Type::Struct(parser::CheckedQualifiers(false),string_struct_id)));
return TRY((((*this).find_or_add_type_id(type))));
}
}

ErrorOr<void> interpreter::Interpreter::error_with_hint(ByteString const message,utility::Span const span,ByteString const hint_message,utility::Span const hint_span) {
{
TRY((((((((*this).compiler))->errors)).push(error::JaktError::MessageWithHint(message,span,hint_message,hint_span)))));
TRY((((((*this).compiler))->print_errors())));
}
return {};
}

ErrorOr<interpreter::StatementResult> interpreter::Interpreter::call_prelude_function(ByteString const prelude_function,JaktInternal::DynamicArray<types::ResolvedNamespace> const namespace_,JaktInternal::Optional<types::Value> const this_argument,JaktInternal::DynamicArray<types::Value> const arguments,utility::Span const call_span,JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const type_bindings) {
{
if (((((namespace_).size())) != (static_cast<size_t>(1ULL)))){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_207; {
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Expected string as first argument to format, got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_207 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(TRY((types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))))))),call_span)); goto __jakt_label_193;

}
__jakt_label_193:; __jakt_var_207.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_208; {
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return (outln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return (warnln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return (out((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else {
return (warn((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_208 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_194;

}
__jakt_label_194:; __jakt_var_208.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_209; {
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return (outln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return (warnln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return (out((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else {
return (warn((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_209 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_195;

}
__jakt_label_195:; __jakt_var_209.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_210; {
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return (outln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return (warnln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return (out((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else {
return (warn((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_210 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_196;

}
__jakt_label_196:; __jakt_var_210.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_211; {
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return (outln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return (warnln((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return (out((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
else {
return (warn((StringView::from_string_literal("{}"sv)),formatted_string)), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_211 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_197;

}
__jakt_label_197:; __jakt_var_211.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("as_saturated"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_212; {
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function((((TRY((((((*this).program))->find_functions_with_name_in_scope(((((*this).program))->prelude_scope_id()),TRY(ByteString::from_utf8("as_saturated"sv)),false,JaktInternal::OptionalNone())))).value()))[static_cast<i64>(0LL)])));
JaktInternal::Optional<ids::TypeId> const output_type_id = ((type_bindings).get(((((((((function)->generics))->params))[static_cast<i64>(0LL)])).type_id())));
__jakt_var_212 = interpreter::StatementResult::JustValue(TRY((interpreter::cast_value_to_type(((arguments)[static_cast<i64>(0LL)]),(output_type_id.value()),*this,true)))); goto __jakt_label_198;

}
__jakt_label_198:; __jakt_var_212.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("unchecked_mul"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_213; {
types::Value const lhs_value = ((arguments)[static_cast<i64>(0LL)]);
types::Value const rhs_value = ((arguments)[static_cast<i64>(1LL)]);
utility::Span const span = call_span;
__jakt_var_213 = interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(unchecked_mul<u8>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(unchecked_mul<u16>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(unchecked_mul<u32>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(unchecked_mul<u64>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(unchecked_mul<i8>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(unchecked_mul<i16>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(unchecked_mul<i32>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(unchecked_mul<i64>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F32(unchecked_mul<f32>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F64(unchecked_mul<f64>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(unchecked_mul<size_t>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)); goto __jakt_label_199;

}
__jakt_label_199:; __jakt_var_213.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("unchecked_add"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_214; {
types::Value const lhs_value = ((arguments)[static_cast<i64>(0LL)]);
types::Value const rhs_value = ((arguments)[static_cast<i64>(1LL)]);
utility::Span const span = call_span;
__jakt_var_214 = interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(unchecked_add<u8>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(unchecked_add<u16>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(unchecked_add<u32>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(unchecked_add<u64>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(unchecked_add<i8>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(unchecked_add<i16>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(unchecked_add<i32>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(unchecked_add<i64>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F32(unchecked_add<f32>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F64(unchecked_add<f64>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(unchecked_add<size_t>(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)); goto __jakt_label_200;

}
__jakt_label_200:; __jakt_var_214.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("___jakt_get_target_triple_string"sv))) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(TRY((((((*this).compiler))->target_triple).try_value_or_lazy_evaluated([&]() -> ErrorOr<ByteString> { return TRY((___jakt_get_target_triple_string())); })))))),call_span)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("___jakt_get_user_configuration_value"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_215; {
NonnullRefPtr<typename types::ValueImpl> impl = TRY((types::ValueImpl::OptionalNone()));
JaktInternal::Optional<ByteString> const value = ((((((*this).compiler))->user_configuration)).get(TRY((((*this).string_from_value(((arguments)[static_cast<i64>(0LL)])))))));
if (((value).has_value())){
(impl = TRY((types::ValueImpl::OptionalSome(TRY((((*this).string_value((value.value()),call_span))))))));
}
__jakt_var_215 = interpreter::StatementResult::JustValue(types::Value(impl,call_span)); goto __jakt_label_201;

}
__jakt_label_201:; __jakt_var_215.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("abort"sv))) {
{
abort();
}
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Set"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_216; {
if (((((type_bindings).size())) != (static_cast<size_t>(1ULL)))){
TRY((((*this).error(TRY(ByteString::from_utf8("Set constructor expects one generic argument"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const set_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Set"sv))))));
ids::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),set_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({(((type_bindings).get(((TRY((((type_bindings).keys()))))[static_cast<i64>(0LL)]))).value())})))))))))));
__jakt_var_216 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktSet((TRY((DynamicArray<types::Value>::create_with({})))),type_id))),call_span)); goto __jakt_label_202;

}
__jakt_label_202:; __jakt_var_216.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Dictionary"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_217; {
if (((((type_bindings).size())) != (static_cast<size_t>(2ULL)))){
TRY((((*this).error(TRY(ByteString::from_utf8("Dictionary constructor expects two generic argumenst"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const dictionary_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Dictionary"sv))))));
ids::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),dictionary_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({(((type_bindings).get(((TRY((((type_bindings).keys()))))[static_cast<i64>(0LL)]))).value()), (((type_bindings).get(((TRY((((type_bindings).keys()))))[static_cast<i64>(1LL)]))).value())})))))))))));
__jakt_var_217 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktDictionary((TRY((DynamicArray<types::Value>::create_with({})))),(TRY((DynamicArray<types::Value>::create_with({})))),type_id))),call_span)); goto __jakt_label_203;

}
__jakt_label_203:; __jakt_var_217.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("from_string_literal"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_218; {
__jakt_var_218 = interpreter::StatementResult::JustValue(((arguments)[static_cast<i64>(0LL)])); goto __jakt_label_204;

}
__jakt_label_204:; __jakt_var_218.release_value(); }));
}
else {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function {}::{} is not implemented yet"sv)),namespace_,prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((((namespace_)[static_cast<i64>(0LL)])).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("Error"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("from_errno"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_219; {
types::Value const err = ((arguments)[static_cast<i64>(0LL)]);
ids::StructId const error_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Error"sv))))));
types::CheckedStruct const error_struct = ((((*this).program))->get_struct(error_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((error_struct).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const constructors = ((((scope)->functions)).get(TRY(ByteString::from_utf8("from_errno"sv))));
__jakt_var_219 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({err})))),error_struct_id,(((constructors.value()))[static_cast<i64>(0LL)])))),call_span)); goto __jakt_label_205;

}
__jakt_label_205:; __jakt_var_219.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("from_string_literal"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_220; {
types::Value const err = ((arguments)[static_cast<i64>(0LL)]);
ids::StructId const error_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Error"sv))))));
types::CheckedStruct const error_struct = ((((*this).program))->get_struct(error_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((error_struct).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const constructors = ((((scope)->functions)).get(TRY(ByteString::from_utf8("from_string_literal"sv))));
__jakt_var_220 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({err})))),error_struct_id,(((constructors.value()))[static_cast<i64>(0LL)])))),call_span)); goto __jakt_label_206;

}
__jakt_label_206:; __jakt_var_220.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("code"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& code = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::I32(code))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Error should have `i32` as its code, but got {}"sv)),((((fields)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Error::code` expects an Error as its this argument, but got {}"sv)),(((this_argument.value())).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Error::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("File"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("open_for_reading"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_221; {
ByteString const requested_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::{}` expects a string as its first argument, but got {}"sv)),prelude_function,((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
jakt__path::Path const path = TRY((((TRY(((((TRY((((((((*this).program))->compiler))->get_file_path(((call_span).file_id))))).value())).parent())))).join(requested_path))));
types::Value const path_value = types::Value(TRY((types::ValueImpl::JaktString(((path).to_string())))),call_span);
if ((!(((path).exists())))){
return interpreter::StatementResult::Throw(TRY((((*this).error_value(TRY((__jakt_format((StringView::from_string_literal("Could not find file at path {}"sv)),((path).to_string())))),call_span)))));
}
ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("File"sv))))));
types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((file_struct).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const constructors = ((((scope)->functions)).get(TRY(ByteString::from_utf8("open_for_reading"sv))));
__jakt_var_221 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({path_value})))),file_struct_id,(((constructors.value()))[static_cast<i64>(0LL)])))),call_span)); goto __jakt_label_207;

}
__jakt_label_207:; __jakt_var_221.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("open_for_writing"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_222; {
ByteString const requested_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::{}` expects a string as its first argument, but got {}"sv)),prelude_function,((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
jakt__path::Path const path = TRY((((TRY(((((TRY((((((((*this).program))->compiler))->get_file_path(((call_span).file_id))))).value())).parent())))).join(requested_path))));
types::Value const path_value = types::Value(TRY((types::ValueImpl::JaktString(((path).to_string())))),call_span);
if ((!(((path).exists())))){
return interpreter::StatementResult::Throw(TRY((((*this).error_value(TRY((__jakt_format((StringView::from_string_literal("Could not find file at path {}"sv)),((path).to_string())))),call_span)))));
}
ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("File"sv))))));
types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((file_struct).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const constructor = ((((scope)->functions)).get(TRY(ByteString::from_utf8("open_for_writing"sv))));
__jakt_var_222 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({path_value})))),file_struct_id,(((constructor.value()))[static_cast<i64>(0LL)])))),call_span)); goto __jakt_label_208;

}
__jakt_label_208:; __jakt_var_222.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("read_all"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_223; {
ByteString const path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("invalid type for File::read_all"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::read_all` expects a `File` as its this argument, but got {}"sv)),(((this_argument.value())).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("File"sv))))));
types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((file_struct).scope_id)))));
ids::FunctionId const open_for_reading = (((((((scope)->functions)).get(TRY(ByteString::from_utf8("open_for_reading"sv)))).value()))[static_cast<i64>(0LL)]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if (((!(((constructor).has_value()))) || (!((((constructor.value())).equals(open_for_reading)))))){
TRY((((*this).error(TRY(ByteString::from_utf8("Cannot read from a file not opened for reading"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("expected struct as this argument"sv)));
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
JaktInternal::DynamicArray<types::Value> result_values = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<u8> _magic = ((TRY((((file)->read_all())))).iterator());
for (;;){
JaktInternal::Optional<u8> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 byte = (_magic_value.value());
{
TRY((((result_values).push(types::Value(TRY((types::ValueImpl::U8(byte))),call_span)))));
}

}
}

ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Array"sv))))));
__jakt_var_223 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktArray(result_values,TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),array_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({types::builtin(types::BuiltinType::U8())})))))))))))))),call_span)); goto __jakt_label_209;

}
__jakt_label_209:; __jakt_var_223.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("read"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_224; {
ByteString const path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("invalid type for File::read"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::read` expects a `File` as its this argument, but got {}"sv)),(((this_argument.value())).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("File"sv))))));
types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((file_struct).scope_id)))));
ids::FunctionId const open_for_reading = (((((((scope)->functions)).get(TRY(ByteString::from_utf8("open_for_reading"sv)))).value()))[static_cast<i64>(0LL)]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if (((!(((constructor).has_value()))) || (!((((constructor.value())).equals(open_for_reading)))))){
TRY((((*this).error(TRY(ByteString::from_utf8("Cannot read from a file not opened for reading"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("expected struct as this argument"sv)));
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
JaktInternal::DynamicArray<types::Value> values_buffer = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(values);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::read` expects a `[u8]` as its argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<u8> byte_buffer = (TRY((DynamicArray<u8>::filled(((values_buffer).size()), static_cast<u8>(0)))));
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
(((values_buffer)[i]) = types::Value(TRY((types::ValueImpl::U8(((byte_buffer)[i])))),call_span));
}

}
}

__jakt_var_224 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(bytes_read))),call_span)); goto __jakt_label_210;

}
__jakt_label_210:; __jakt_var_224.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("exists"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_225; {
ByteString const requested_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::{}` expects a string as its first argument, but got {}"sv)),prelude_function,((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
jakt__path::Path const path = TRY((((TRY(((((TRY((((((((*this).program))->compiler))->get_file_path(((call_span).file_id))))).value())).parent())))).join(requested_path))));
__jakt_var_225 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((path).exists())))),call_span)); goto __jakt_label_211;

}
__jakt_label_211:; __jakt_var_225.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("write"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_226; {
ByteString const path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("invalid type for File::write"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::write` expects a `File` as its this argument, but got {}"sv)),(((this_argument.value())).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("File"sv))))));
types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((file_struct).scope_id)))));
ids::FunctionId const open_for_writing = (((((((scope)->functions)).get(TRY(ByteString::from_utf8("open_for_writing"sv)))).value()))[static_cast<i64>(0LL)]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if (((!(((constructor).has_value()))) || (!((((constructor.value())).equals(open_for_writing)))))){
TRY((((*this).error(TRY(ByteString::from_utf8("Cannot write to a file not opened for writing"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("expected struct as this argument"sv)));
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
JaktInternal::DynamicArray<types::Value> data_values = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(values);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::write` expects a `[u8]` as its argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<u8> data = (TRY((DynamicArray<u8>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((data_values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value val = (_magic_value.value());
{
TRY((((data).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u8, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((val).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("expected byte"sv)));
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
})))));
}

}
}

size_t const bytes_written = TRY((((file)->write(data))));
__jakt_var_226 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(bytes_written))),call_span)); goto __jakt_label_212;

}
__jakt_label_212:; __jakt_var_226.release_value(); }));
}
else {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `File::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("StringBuilder"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("create"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_227; {
ids::StructId const string_builder_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("StringBuilder"sv))))));
__jakt_var_227 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::JaktString(TRY(ByteString::from_utf8(""sv))))),call_span)})))),string_builder_struct_id,JaktInternal::OptionalNone()))),call_span)); goto __jakt_label_213;

}
__jakt_label_213:; __jakt_var_227.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_228; {
JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of prelude StringBuilder"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string(current_string))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("append"sv))) {
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_string"sv))) {
return (TRY((((builder).append_string(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_string()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_escaped_for_json"sv))) {
return (TRY((((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_code_point"sv))) {
return (TRY((((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else {
{
abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = types::Value(TRY((types::ValueImpl::JaktString(TRY((((builder).to_string())))))),call_span));
__jakt_var_228 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_214;

}
__jakt_label_214:; __jakt_var_228.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_string"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_229; {
JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of prelude StringBuilder"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string(current_string))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("append"sv))) {
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_string"sv))) {
return (TRY((((builder).append_string(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_string()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_escaped_for_json"sv))) {
return (TRY((((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_code_point"sv))) {
return (TRY((((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else {
{
abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = types::Value(TRY((types::ValueImpl::JaktString(TRY((((builder).to_string())))))),call_span));
__jakt_var_229 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_215;

}
__jakt_label_215:; __jakt_var_229.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_code_point"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_230; {
JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of prelude StringBuilder"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string(current_string))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("append"sv))) {
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_string"sv))) {
return (TRY((((builder).append_string(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_string()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_escaped_for_json"sv))) {
return (TRY((((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_code_point"sv))) {
return (TRY((((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else {
{
abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = types::Value(TRY((types::ValueImpl::JaktString(TRY((((builder).to_string())))))),call_span));
__jakt_var_230 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_216;

}
__jakt_label_216:; __jakt_var_230.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_escaped_for_json"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_231; {
JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<types::Value>,ByteString>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of prelude StringBuilder"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string(current_string))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("append"sv))) {
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return (TRY((((builder).append(value))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_string"sv))) {
return (TRY((((builder).append_string(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_string()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_escaped_for_json"sv))) {
return (TRY((((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("append_code_point"sv))) {
return (TRY((((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))), JaktInternal::ExplicitValue<void>();
}
else {
{
abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = types::Value(TRY((types::ValueImpl::JaktString(TRY((((builder).to_string())))))),call_span));
__jakt_var_231 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_217;

}
__jakt_label_217:; __jakt_var_231.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("to_string"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(((fields)[static_cast<i64>(0LL)])));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("is_empty"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((value).is_empty())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of prelude StringBuilder"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("length"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((value).length())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of prelude StringBuilder"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("clear"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_232; {
JaktInternal::DynamicArray<types::Value> mutable_fields = fields;
(((((mutable_fields)[static_cast<i64>(0LL)])).impl) = TRY((types::ValueImpl::JaktString(TRY(ByteString::from_utf8(""sv))))));
__jakt_var_232 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_218;

}
__jakt_label_218:; __jakt_var_232.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Dictionary"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("Dictionary"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_233; {
if (((((type_bindings).size())) != (static_cast<size_t>(2ULL)))){
TRY((((*this).error(TRY(ByteString::from_utf8("Dictionary constructor expects two generic argumenst"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const dictionary_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Dictionary"sv))))));
ids::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),dictionary_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({(((type_bindings).get(((TRY((((type_bindings).keys()))))[static_cast<i64>(0LL)]))).value()), (((type_bindings).get(((TRY((((type_bindings).keys()))))[static_cast<i64>(1LL)]))).value())})))))))))));
__jakt_var_233 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktDictionary((TRY((DynamicArray<types::Value>::create_with({})))),(TRY((DynamicArray<types::Value>::create_with({})))),type_id))),call_span)); goto __jakt_label_219;

}
__jakt_label_219:; __jakt_var_233.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("get"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_234; {
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

__jakt_var_234 = interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((found_index).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalSome(((values)[(found_index.value())])))),call_span));
}
else {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})); goto __jakt_label_220;

}
__jakt_label_220:; __jakt_var_234.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::get()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("set"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_235; {
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

JaktInternal::DynamicArray<types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<types::Value> mutable_values = values;
if (((found_index).has_value())){
(((mutable_values)[(found_index.value())]) = ((arguments)[static_cast<i64>(1LL)]));
}
else {
TRY((((mutable_keys).push(((arguments)[static_cast<i64>(0LL)])))));
TRY((((mutable_values).push(((arguments)[static_cast<i64>(1LL)])))));
}

__jakt_var_235 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_221;

}
__jakt_label_221:; __jakt_var_235.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::set()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("is_empty"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool((((keys).is_empty()) && ((values).is_empty()))))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::is_empty()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("contains"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_236; {
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

__jakt_var_236 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(found))),call_span)); goto __jakt_label_222;

}
__jakt_label_222:; __jakt_var_236.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::contains()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("remove"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_237; {
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
JaktInternal::DynamicArray<types::Value> keys_without = (TRY((DynamicArray<types::Value>::create_with({}))));
JaktInternal::DynamicArray<types::Value> values_without = (TRY((DynamicArray<types::Value>::create_with({}))));
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
TRY((((keys_without).push(((keys)[i])))));
TRY((((values_without).push(((values)[i])))));
}

}
}

JaktInternal::DynamicArray<types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<types::Value> mutable_values = values;
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
TRY((((mutable_keys).push(((keys_without)[i])))));
TRY((((mutable_values).push(((values_without)[i])))));
}

}
}

}
__jakt_var_237 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((found_index).has_value())))),call_span)); goto __jakt_label_223;

}
__jakt_label_223:; __jakt_var_237.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::remove()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("ensure_capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_238; {
JaktInternal::DynamicArray<types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<types::Value> mutable_values = values;
TRY((((mutable_keys).ensure_capacity(capacity))));
TRY((((mutable_values).ensure_capacity(capacity))));
__jakt_var_238 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_224;

}
__jakt_label_224:; __jakt_var_238.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Dictionary::ensure_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::ensure_capacity()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((keys).capacity())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::capacity()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("clear"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_239; {
JaktInternal::DynamicArray<types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<types::Value> mutable_values = values;
((mutable_keys).shrink(static_cast<size_t>(0ULL)));
((mutable_values).shrink(static_cast<size_t>(0ULL)));
__jakt_var_239 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_225;

}
__jakt_label_225:; __jakt_var_239.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::clear()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("size"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((keys).size())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::size()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("keys"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_240; {
JaktInternal::DynamicArray<ids::TypeId> const generics = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("expected generic instance"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_240 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((((generics).size())) == (static_cast<size_t>(2ULL))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_241; {
ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Array"sv))))));
ids::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),array_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({((generics)[static_cast<i64>(0LL)])})))))))))));
__jakt_var_241 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktArray(keys,type_id))),call_span)); goto __jakt_label_227;

}
__jakt_label_227:; __jakt_var_241.release_value(); }));
}
else {
{
utility::panic(TRY(ByteString::from_utf8("dictionary should have 2 generic args. one for keys, one for values"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_226;

}
__jakt_label_226:; __jakt_var_240.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::keys()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("iterator"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_242; {
ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("DictionaryIterator"sv))))));
__jakt_var_242 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({(this_argument.value()), types::Value(TRY((types::ValueImpl::USize(static_cast<size_t>(0ULL)))),call_span)})))),struct_id,JaktInternal::OptionalNone()))),call_span)); goto __jakt_label_228;

}
__jakt_label_228:; __jakt_var_242.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Dictionary::iterator()"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Dictionary::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Array"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("iterator"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_243; {
ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("ArrayIterator"sv))))));
__jakt_var_243 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({(this_argument.value()), types::Value(TRY((types::ValueImpl::USize(static_cast<size_t>(0ULL)))),call_span)})))),struct_id,JaktInternal::OptionalNone()))),call_span)); goto __jakt_label_229;

}
__jakt_label_229:; __jakt_var_243.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::iterator()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("size"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_244; {
__jakt_var_244 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((values).size())))),call_span)); goto __jakt_label_230;

}
__jakt_label_230:; __jakt_var_244.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::size()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("push"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_245; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
TRY((((mutable_values).push(((arguments)[static_cast<i64>(0LL)])))));
__jakt_var_245 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_231;

}
__jakt_label_231:; __jakt_var_245.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::push()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("push_values"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_246; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
{
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
TRY((((mutable_values).push(value))));
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return (TRY((((*this).error(TRY(ByteString::from_utf8("Only argument to push_values needs to be another Array"sv)),call_span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_246 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_232;

}
__jakt_label_232:; __jakt_var_246.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::push_values()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("pop"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_247; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
JaktInternal::Optional<types::Value> const value = ((mutable_values).pop());
__jakt_var_247 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((value).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue((value.value())));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_233;

}
__jakt_label_233:; __jakt_var_247.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::push()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("first"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_248; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
JaktInternal::Optional<types::Value> const value = ((mutable_values).first());
__jakt_var_248 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((value).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue((value.value())));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_234;

}
__jakt_label_234:; __jakt_var_248.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::push()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("last"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_249; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
JaktInternal::Optional<types::Value> const value = ((mutable_values).last());
__jakt_var_249 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((value).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue((value.value())));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_235;

}
__jakt_label_235:; __jakt_var_249.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::push()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("contains"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_250; {
bool found = false;
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
if (((((value).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found = true);
break;
}
}

}
}

__jakt_var_250 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(found))),call_span)); goto __jakt_label_236;

}
__jakt_label_236:; __jakt_var_250.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::contains()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("is_empty"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((values).is_empty())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::is_empty()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_251; {
__jakt_var_251 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((values).capacity())))),call_span)); goto __jakt_label_237;

}
__jakt_label_237:; __jakt_var_251.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::capacity()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("ensure_capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_252; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
TRY((((mutable_values).ensure_capacity(capacity))));
__jakt_var_252 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_238;

}
__jakt_label_238:; __jakt_var_252.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Array::ensure_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::ensure_capacity()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("add_capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_253; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
TRY((((mutable_values).add_capacity(capacity))));
__jakt_var_253 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_239;

}
__jakt_label_239:; __jakt_var_253.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Array::add_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::add_capacity()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("shrink"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& size = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_254; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
((mutable_values).shrink(size));
__jakt_var_254 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_240;

}
__jakt_label_240:; __jakt_var_254.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Array::shrink must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid use of Array::shrink()"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Array::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("ArrayIterator"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("next"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_255; {
size_t const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid ArrayIterator index configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> mutable_fields = fields;
__jakt_var_255 = interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((values).size()),index));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_256; {
(((mutable_fields)[static_cast<i64>(1LL)]) = types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_add(index,static_cast<size_t>(1ULL))))),call_span));
__jakt_var_256 = types::Value(TRY((types::ValueImpl::OptionalSome(((values)[index])))),call_span); goto __jakt_label_242;

}
__jakt_label_242:; __jakt_var_256.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid ArrayIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})); goto __jakt_label_241;

}
__jakt_label_241:; __jakt_var_255.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid ArrayIterator configuration"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `ArrayIterator::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Range"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("next"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_257; {
JaktInternal::DynamicArray<types::Value> fields = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Range::next()"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<interpreter::StatementResult>>{
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
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid type for comptime range"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<interpreter::StatementResult>>{
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
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid type for comptime range"sv)));
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
return interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span));
}
if ([](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(start,end)){
(((fields)[static_cast<i64>(0LL)]) = types::Value(TRY((types::ValueImpl::U64(JaktInternal::checked_sub(start,static_cast<u64>(1ULL))))),call_span));
}
else {
(((fields)[static_cast<i64>(0LL)]) = types::Value(TRY((types::ValueImpl::U64(JaktInternal::checked_add(start,static_cast<u64>(1ULL))))),call_span));
}

__jakt_var_257 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalSome(types::Value(TRY((types::ValueImpl::U64(start))),call_span)))),call_span)); goto __jakt_label_243;

}
__jakt_label_243:; __jakt_var_257.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("inclusive"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_258; {
JaktInternal::DynamicArray<types::Value> mutable_fields = fields;
u64 const end = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<interpreter::StatementResult>>{
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
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid type for comptime range"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((((mutable_fields)[static_cast<i64>(1LL)])).impl) = TRY((types::ValueImpl::U64(JaktInternal::checked_add(end,static_cast<u64>(1ULL))))));
__jakt_var_258 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct(fields,struct_id,constructor))),(((this_argument.value())).span))); goto __jakt_label_244;

}
__jakt_label_244:; __jakt_var_258.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Range::inclusive()"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("exclusive"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue((this_argument.value())));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Range::exclusive()"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Range::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("String"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("is_empty"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((value).is_empty())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("length"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((value).length())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("hash"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U32(((value).hash())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("substring"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& start = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_259; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_259 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_245;

}
__jakt_label_245:; __jakt_var_259.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_260; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_260 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_246;

}
__jakt_label_246:; __jakt_var_260.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_261; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_261 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_247;

}
__jakt_label_247:; __jakt_var_261.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_262; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_262 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_248;

}
__jakt_label_248:; __jakt_var_262.release_value(); }));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_263; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_263 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_249;

}
__jakt_label_249:; __jakt_var_263.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_264; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_264 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_250;

}
__jakt_label_250:; __jakt_var_264.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_265; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_265 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_251;

}
__jakt_label_251:; __jakt_var_265.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_266; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_266 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_252;

}
__jakt_label_252:; __jakt_var_266.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_267; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_267 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_253;

}
__jakt_label_253:; __jakt_var_267.release_value(); }));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_268; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_268 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_254;

}
__jakt_label_254:; __jakt_var_268.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_269; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_269 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_255;

}
__jakt_label_255:; __jakt_var_269.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_270; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_270 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_256;

}
__jakt_label_256:; __jakt_var_270.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_271; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_271 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_257;

}
__jakt_label_257:; __jakt_var_271.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_272; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_272 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_258;

}
__jakt_label_258:; __jakt_var_272.release_value(); }));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_273; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_273 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_259;

}
__jakt_label_259:; __jakt_var_273.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_274; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_274 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_260;

}
__jakt_label_260:; __jakt_var_274.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_275; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_275 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_261;

}
__jakt_label_261:; __jakt_var_275.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_276; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_276 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_262;

}
__jakt_label_262:; __jakt_var_276.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_277; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_277 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_263;

}
__jakt_label_263:; __jakt_var_277.release_value(); }));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_278; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_278 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_264;

}
__jakt_label_264:; __jakt_var_278.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_279; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_279 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_265;

}
__jakt_label_265:; __jakt_var_279.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_280; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_280 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_266;

}
__jakt_label_266:; __jakt_var_280.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_281; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_281 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_267;

}
__jakt_label_267:; __jakt_var_281.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_282; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_282 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_268;

}
__jakt_label_268:; __jakt_var_282.release_value(); }));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_283; {
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
__jakt_var_283 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(result))),call_span)); goto __jakt_label_269;

}
__jakt_label_269:; __jakt_var_283.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("number"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))))),call_span)));
};/*case end*/
case 12 /* USize */: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::number must not be called with a usize or u64"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
case 5 /* U64 */: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::number must not be called with a usize or u64"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::number must be called with an integer"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("to_uint"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_284; {
JaktInternal::Optional<u32> const result = ((value).to_uint());
__jakt_var_284 = interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((result).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::OptionalSome(types::Value(TRY((types::ValueImpl::U32((result.value())))),call_span)))));
}
else {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::OptionalNone())));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),call_span)); goto __jakt_label_270;

}
__jakt_label_270:; __jakt_var_284.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("to_int"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_285; {
JaktInternal::Optional<i32> const result = ((value).to_int());
__jakt_var_285 = interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((result).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::OptionalSome(types::Value(TRY((types::ValueImpl::I32((result.value())))),call_span)))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::OptionalNone())));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),call_span)); goto __jakt_label_271;

}
__jakt_label_271:; __jakt_var_285.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("is_whitespace"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((value).is_whitespace())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("contains"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((value).contains(arg))))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::contains must be called with a string"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("replace"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& replace = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& with = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(((value).replace(replace,with))))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::replace must be called with strings"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("String::replace must be called with strings"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("byte_at"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))))),call_span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))))),call_span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))))),call_span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))))),call_span)));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::byte_at must be called with an unsigned integer"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("split"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& c = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_286; {
JaktInternal::DynamicArray<ByteString> const values = ((value).split(c));
JaktInternal::DynamicArray<types::Value> result = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString value = (_magic_value.value());
{
TRY((((result).push(types::Value(TRY((types::ValueImpl::JaktString(value))),call_span)))));
}

}
}

ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Array"sv))))));
__jakt_var_286 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktArray(result,TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),array_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({TRY((((*this).string_type())))})))))))))))))),call_span)); goto __jakt_label_272;

}
__jakt_label_272:; __jakt_var_286.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::split must be called with a c_char"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("starts_with"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((value).starts_with(arg))))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::starts_with must be called with a string"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("ends_with"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((value).ends_with(arg))))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::ends_with must be called with a string"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid String"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("repeated"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_287; {
if (((((arguments).size())) != (static_cast<size_t>(2ULL)))){
TRY((((*this).error(TRY(ByteString::from_utf8("String::repeated must be called with a c_char and a usize"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
JaktInternal::Tuple<char,size_t> const character_count_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<char,size_t>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<char,size_t>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& c = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{arg, c}));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("String::repeated must be called with a usize"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("String::repeated must be called with a c_char"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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

__jakt_var_287 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(ByteString::repeated(character,count)))),call_span)); goto __jakt_label_273;

}
__jakt_label_273:; __jakt_var_287.release_value(); }));
}
else {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `String::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Set"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("Set"sv))) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_288; {
if (((((type_bindings).size())) != (static_cast<size_t>(1ULL)))){
TRY((((*this).error(TRY(ByteString::from_utf8("Set constructor expects one generic argument"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const set_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Set"sv))))));
ids::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),set_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({(((type_bindings).get(((TRY((((type_bindings).keys()))))[static_cast<i64>(0LL)]))).value())})))))))))));
__jakt_var_288 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktSet((TRY((DynamicArray<types::Value>::create_with({})))),type_id))),call_span)); goto __jakt_label_274;

}
__jakt_label_274:; __jakt_var_288.release_value(); }));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("is_empty"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(((values).is_empty())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("contains"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_289; {
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

__jakt_var_289 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(found))),call_span)); goto __jakt_label_275;

}
__jakt_label_275:; __jakt_var_289.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("add"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_290; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
TRY((((mutable_values).push(((arguments)[static_cast<i64>(0LL)])))));
__jakt_var_290 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_276;

}
__jakt_label_276:; __jakt_var_290.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("remove"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_291; {
bool found = false;
JaktInternal::DynamicArray<types::Value> values_without = (TRY((DynamicArray<types::Value>::create_with({}))));
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
TRY((((values_without).push(((values)[i])))));
}

}
}

JaktInternal::DynamicArray<types::Value> mutable_values = values;
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
TRY((((mutable_values).push(((values_without)[i])))));
}

}
}

__jakt_var_291 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(found))),call_span)); goto __jakt_label_277;

}
__jakt_label_277:; __jakt_var_291.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("clear"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_292; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
((mutable_values).shrink(static_cast<size_t>(0ULL)));
__jakt_var_292 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_278;

}
__jakt_label_278:; __jakt_var_292.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("size"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((values).size())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(((values).capacity())))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("ensure_capacity"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_293; {
JaktInternal::DynamicArray<types::Value> mutable_values = values;
TRY((((mutable_values).ensure_capacity(capacity))));
__jakt_var_293 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span)); goto __jakt_label_279;

}
__jakt_label_279:; __jakt_var_293.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Set::ensure_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
utility::panic(TRY(ByteString::from_utf8("Invalid Set"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("iterator"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_294; {
ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("SetIterator"sv))))));
__jakt_var_294 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({(this_argument.value()), types::Value(TRY((types::ValueImpl::USize(static_cast<size_t>(0ULL)))),call_span)})))),struct_id,JaktInternal::OptionalNone()))),call_span)); goto __jakt_label_280;

}
__jakt_label_280:; __jakt_var_294.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid use of Set::iterator()"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Set::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("SetIterator"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("next"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_295; {
size_t const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid SetIterator index configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> mutable_fields = fields;
__jakt_var_295 = interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((values).size()),index));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_296; {
(((mutable_fields)[static_cast<i64>(1LL)]) = types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_add(index,static_cast<size_t>(1ULL))))),call_span));
__jakt_var_296 = types::Value(TRY((types::ValueImpl::OptionalSome(((values)[index])))),call_span); goto __jakt_label_282;

}
__jakt_label_282:; __jakt_var_296.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid SetIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})); goto __jakt_label_281;

}
__jakt_label_281:; __jakt_var_295.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid SetIterator configuration"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `ArrayIterator::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("DictionaryIterator"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("next"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_297; {
size_t const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid DictionaryIterator index configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> mutable_fields = fields;
__jakt_var_297 = interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((keys).size()),index) && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((values).size()),index)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_298; {
(((mutable_fields)[static_cast<i64>(1LL)]) = types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_add(index,static_cast<size_t>(1ULL))))),call_span));
JaktInternal::DynamicArray<ids::TypeId> const generics = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("expected generic instance"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::StructId const tuple_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Tuple"sv))))));
ids::TypeId const tuple_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),tuple_struct_id,generics)))))));
__jakt_var_298 = types::Value(TRY((types::ValueImpl::OptionalSome(types::Value(TRY((types::ValueImpl::JaktTuple((TRY((DynamicArray<types::Value>::create_with({((keys)[index]), ((values)[index])})))),tuple_type_id))),call_span)))),call_span); goto __jakt_label_284;

}
__jakt_label_284:; __jakt_var_298.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::OptionalNone())),call_span));
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
utility::panic(TRY(ByteString::from_utf8("Invalid DictionaryIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})); goto __jakt_label_283;

}
__jakt_label_283:; __jakt_var_297.release_value(); }));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid DictionaryIterator configuration"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `DictionaryIterator::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("Optional"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == TRY(ByteString::from_utf8("has_value"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(true))),call_span)));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(false))),call_span)));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Optional configuration"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("value"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
};/*case end*/
case 25 /* OptionalNone */: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot unwrap optional none"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Attempt to unwrap None"sv)));
}
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Optional configuration"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("map"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_299; {
types::Value const mapper_value = ((arguments)[static_cast<i64>(0LL)]);
__jakt_var_299 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((((mapper_value).impl))->__jakt_init_index() == 27 /* Function */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_300; {
types::CheckedBlock const block = (((mapper_value).impl))->as.Function.block;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> const params = (((mapper_value).impl))->as.Function.params;
ids::TypeId const return_type_id = (((mapper_value).impl))->as.Function.return_type_id;
JaktInternal::DynamicArray<types::CheckedParameter> const checked_params = (((mapper_value).impl))->as.Function.checked_params;
NonnullRefPtr<interpreter::InterpreterScope> scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((checked_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter declared_param = (_magic_value.value());
{
ByteString const name = ((((declared_param).variable))->name);
JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>> const param_type_id___ = ((params)[name]);
ids::TypeId const param_type_id = ((param_type_id___).template get<0>());
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> const _ = ((param_type_id___).template get<1>());

if (first){
(first = false);
TRY((((((scope)->bindings)).set(name,TRY((interpreter::cast_value_to_type(value,param_type_id,*this,false)))))));
}
else {
break;
}

}

}
}

interpreter::StatementResult const result = TRY((((*this).execute_block(block,scope,call_span))));
__jakt_var_300 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((result).__jakt_init_index() == 5 /* JustValue */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_301; {
types::Value const blk = (result).as.JustValue.value;
__jakt_var_301 = interpreter::StatementResult::JustValue(blk); goto __jakt_label_287;

}
__jakt_label_287:; __jakt_var_301.release_value(); }));
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
}); goto __jakt_label_286;

}
__jakt_label_286:; __jakt_var_300.release_value(); }));
}
else {
{
utility::panic(TRY(ByteString::from_utf8("Invalid mapper type in Optional::map"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_285;

}
__jakt_label_285:; __jakt_var_299.release_value(); }));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue((this_argument.value())));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Optional configuration"sv)));
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
else if (__jakt_enum_value == TRY(ByteString::from_utf8("value_or"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(((arguments)[static_cast<i64>(0LL)])));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid Optional configuration"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `Optional::{}` is not implemented"sv)),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Prelude function `{}::{}` is not implemented"sv)),((((namespace_)[static_cast<i64>(0LL)])).name),prelude_function))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<void> interpreter::Interpreter::enter_span(utility::Span const span) {
{
TRY((((((*this).spans)).push(span))));
}
return {};
}

ErrorOr<bool> interpreter::Interpreter::get_prelude_function(ids::ScopeId const scope_id) const {
{
ids::ScopeId current_scope_id = scope_id;
ids::ScopeId const prelude_scope_id = ((((*this).program))->prelude_scope_id());
for (;;){
if (((current_scope_id).equals(prelude_scope_id))){
return true;
}
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(current_scope_id))));
if (((((scope)->parent)).has_value())){
(current_scope_id = (((scope)->parent).value()));
continue;
}
return false;
}
}
}

ErrorOr<ids::TypeId> interpreter::Interpreter::find_or_add_type_id(NonnullRefPtr<typename types::Type> const type) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((((*this).program))->modules)).iterator());
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

TRY((((((((((((*this).program))->modules))[static_cast<i64>(0LL)]))->types)).push(type))));
return ids::TypeId(ids::ModuleId(static_cast<size_t>(0ULL)),JaktInternal::checked_sub(((((((((((*this).program))->modules))[static_cast<i64>(0LL)]))->types)).size()),static_cast<size_t>(1ULL)));
}
}

ErrorOr<interpreter::StatementResult> interpreter::Interpreter::execute_expression_without_cast(NonnullRefPtr<typename types::CheckedExpression> const expr,NonnullRefPtr<interpreter::InterpreterScope> scope) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
types::CheckedBinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_302; {
types::Value const lhs_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(lhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
interpreter::StatementResult const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = ((op).op);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* NoneCoalescing */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid left-hand side of NoneCoalescing"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid left-hand side of NoneCoalescing"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (x);
if (__jakt_enum_value == ((((op).op)).__jakt_init_index() == 18 /* LogicalAnd */)) {
return JaktInternal::ExplicitValue(TRY((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})).cast(lhs_value,span)))));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operand '{}' to binary operation"sv)),TRY((((lhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (x);
if (__jakt_enum_value == ((((op).op)).__jakt_init_index() == 18 /* LogicalAnd */)) {
return JaktInternal::ExplicitValue(TRY((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})).cast(lhs_value,span)))));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operand '{}' to binary operation"sv)),TRY((((lhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_303; {
types::Value const rhs_value = TRY((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})).cast(lhs_value,span))));
__jakt_var_303 = TRY((((*this).execute_binary_operator(lhs_value,rhs_value,((op).op),span,scope)))); goto __jakt_label_289;

}
__jakt_label_289:; __jakt_var_303.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = value;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
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
})), JaktInternal::ExplicitValue<void>();
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
__jakt_var_302 = value; goto __jakt_label_288;

}
__jakt_label_288:; __jakt_var_302.release_value(); }));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::USize(TRY((interpreter::size_of_impl(type_id,*this)))))),span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_304; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_304 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LogicalNot */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool((!(value))))),span)));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_305; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U8(JaktInternal::checked_add(x,static_cast<u8>(1))))),span),span))));
__jakt_var_305 = value; goto __jakt_label_291;

}
__jakt_label_291:; __jakt_var_305.release_value(); }));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_306; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I8(JaktInternal::checked_add(x,static_cast<i8>(1))))),span),span))));
__jakt_var_306 = value; goto __jakt_label_292;

}
__jakt_label_292:; __jakt_var_306.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_307; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U16(JaktInternal::checked_add(x,static_cast<u16>(1))))),span),span))));
__jakt_var_307 = value; goto __jakt_label_293;

}
__jakt_label_293:; __jakt_var_307.release_value(); }));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_308; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I16(JaktInternal::checked_add(x,static_cast<i16>(1))))),span),span))));
__jakt_var_308 = value; goto __jakt_label_294;

}
__jakt_label_294:; __jakt_var_308.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_309; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U32(JaktInternal::checked_add(x,static_cast<u32>(1))))),span),span))));
__jakt_var_309 = value; goto __jakt_label_295;

}
__jakt_label_295:; __jakt_var_309.release_value(); }));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_310; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I32(JaktInternal::checked_add(x,static_cast<i32>(1))))),span),span))));
__jakt_var_310 = value; goto __jakt_label_296;

}
__jakt_label_296:; __jakt_var_310.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_311; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U64(JaktInternal::checked_add(x,static_cast<u64>(1ULL))))),span),span))));
__jakt_var_311 = value; goto __jakt_label_297;

}
__jakt_label_297:; __jakt_var_311.release_value(); }));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_312; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I64(JaktInternal::checked_add(x,static_cast<i64>(1LL))))),span),span))));
__jakt_var_312 = value; goto __jakt_label_298;

}
__jakt_label_298:; __jakt_var_312.release_value(); }));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_313; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::CChar(JaktInternal::checked_add(x,static_cast<char>(1))))),span),span))));
__jakt_var_313 = value; goto __jakt_label_299;

}
__jakt_label_299:; __jakt_var_313.release_value(); }));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_314; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::CInt(JaktInternal::checked_add(x,static_cast<int>(1))))),span),span))));
__jakt_var_314 = value; goto __jakt_label_300;

}
__jakt_label_300:; __jakt_var_314.release_value(); }));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_315; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_add(x,static_cast<size_t>(1ULL))))),span),span))));
__jakt_var_315 = value; goto __jakt_label_301;

}
__jakt_label_301:; __jakt_var_315.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_316; {
types::Value const value = types::Value(TRY((types::ValueImpl::U8(JaktInternal::checked_add(x,static_cast<u8>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_316 = value; goto __jakt_label_302;

}
__jakt_label_302:; __jakt_var_316.release_value(); }));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_317; {
types::Value const value = types::Value(TRY((types::ValueImpl::I8(JaktInternal::checked_add(x,static_cast<i8>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_317 = value; goto __jakt_label_303;

}
__jakt_label_303:; __jakt_var_317.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_318; {
types::Value const value = types::Value(TRY((types::ValueImpl::U16(JaktInternal::checked_add(x,static_cast<u16>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_318 = value; goto __jakt_label_304;

}
__jakt_label_304:; __jakt_var_318.release_value(); }));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_319; {
types::Value const value = types::Value(TRY((types::ValueImpl::I16(JaktInternal::checked_add(x,static_cast<i16>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_319 = value; goto __jakt_label_305;

}
__jakt_label_305:; __jakt_var_319.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_320; {
types::Value const value = types::Value(TRY((types::ValueImpl::U32(JaktInternal::checked_add(x,static_cast<u32>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_320 = value; goto __jakt_label_306;

}
__jakt_label_306:; __jakt_var_320.release_value(); }));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_321; {
types::Value const value = types::Value(TRY((types::ValueImpl::I32(JaktInternal::checked_add(x,static_cast<i32>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_321 = value; goto __jakt_label_307;

}
__jakt_label_307:; __jakt_var_321.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_322; {
types::Value const value = types::Value(TRY((types::ValueImpl::U64(JaktInternal::checked_add(x,static_cast<u64>(1ULL))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_322 = value; goto __jakt_label_308;

}
__jakt_label_308:; __jakt_var_322.release_value(); }));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_323; {
types::Value const value = types::Value(TRY((types::ValueImpl::I64(JaktInternal::checked_add(x,static_cast<i64>(1LL))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_323 = value; goto __jakt_label_309;

}
__jakt_label_309:; __jakt_var_323.release_value(); }));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_324; {
types::Value const value = types::Value(TRY((types::ValueImpl::CChar(JaktInternal::checked_add(x,static_cast<char>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_324 = value; goto __jakt_label_310;

}
__jakt_label_310:; __jakt_var_324.release_value(); }));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_325; {
types::Value const value = types::Value(TRY((types::ValueImpl::CInt(JaktInternal::checked_add(x,static_cast<int>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_325 = value; goto __jakt_label_311;

}
__jakt_label_311:; __jakt_var_325.release_value(); }));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_326; {
types::Value const value = types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_add(x,static_cast<size_t>(1ULL))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_326 = value; goto __jakt_label_312;

}
__jakt_label_312:; __jakt_var_326.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_327; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U8(JaktInternal::checked_sub(x,static_cast<u8>(1))))),span),span))));
__jakt_var_327 = value; goto __jakt_label_313;

}
__jakt_label_313:; __jakt_var_327.release_value(); }));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_328; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I8(JaktInternal::checked_sub(x,static_cast<i8>(1))))),span),span))));
__jakt_var_328 = value; goto __jakt_label_314;

}
__jakt_label_314:; __jakt_var_328.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_329; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U16(JaktInternal::checked_sub(x,static_cast<u16>(1))))),span),span))));
__jakt_var_329 = value; goto __jakt_label_315;

}
__jakt_label_315:; __jakt_var_329.release_value(); }));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_330; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I16(JaktInternal::checked_sub(x,static_cast<i16>(1))))),span),span))));
__jakt_var_330 = value; goto __jakt_label_316;

}
__jakt_label_316:; __jakt_var_330.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_331; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U32(JaktInternal::checked_sub(x,static_cast<u32>(1))))),span),span))));
__jakt_var_331 = value; goto __jakt_label_317;

}
__jakt_label_317:; __jakt_var_331.release_value(); }));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_332; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I32(JaktInternal::checked_sub(x,static_cast<i32>(1))))),span),span))));
__jakt_var_332 = value; goto __jakt_label_318;

}
__jakt_label_318:; __jakt_var_332.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_333; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::U64(JaktInternal::checked_sub(x,static_cast<u64>(1ULL))))),span),span))));
__jakt_var_333 = value; goto __jakt_label_319;

}
__jakt_label_319:; __jakt_var_333.release_value(); }));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_334; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::I64(JaktInternal::checked_sub(x,static_cast<i64>(1LL))))),span),span))));
__jakt_var_334 = value; goto __jakt_label_320;

}
__jakt_label_320:; __jakt_var_334.release_value(); }));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_335; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::CChar(JaktInternal::checked_sub(x,static_cast<char>(1))))),span),span))));
__jakt_var_335 = value; goto __jakt_label_321;

}
__jakt_label_321:; __jakt_var_335.release_value(); }));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_336; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::CInt(JaktInternal::checked_sub(x,static_cast<int>(1))))),span),span))));
__jakt_var_336 = value; goto __jakt_label_322;

}
__jakt_label_322:; __jakt_var_336.release_value(); }));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_337; {
TRY((((*this).update_binding(expr,scope,types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_sub(x,static_cast<size_t>(1ULL))))),span),span))));
__jakt_var_337 = value; goto __jakt_label_323;

}
__jakt_label_323:; __jakt_var_337.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_338; {
types::Value const value = types::Value(TRY((types::ValueImpl::U8(JaktInternal::checked_sub(x,static_cast<u8>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_338 = value; goto __jakt_label_324;

}
__jakt_label_324:; __jakt_var_338.release_value(); }));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_339; {
types::Value const value = types::Value(TRY((types::ValueImpl::I8(JaktInternal::checked_sub(x,static_cast<i8>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_339 = value; goto __jakt_label_325;

}
__jakt_label_325:; __jakt_var_339.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_340; {
types::Value const value = types::Value(TRY((types::ValueImpl::U16(JaktInternal::checked_sub(x,static_cast<u16>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_340 = value; goto __jakt_label_326;

}
__jakt_label_326:; __jakt_var_340.release_value(); }));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_341; {
types::Value const value = types::Value(TRY((types::ValueImpl::I16(JaktInternal::checked_sub(x,static_cast<i16>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_341 = value; goto __jakt_label_327;

}
__jakt_label_327:; __jakt_var_341.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_342; {
types::Value const value = types::Value(TRY((types::ValueImpl::U32(JaktInternal::checked_sub(x,static_cast<u32>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_342 = value; goto __jakt_label_328;

}
__jakt_label_328:; __jakt_var_342.release_value(); }));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_343; {
types::Value const value = types::Value(TRY((types::ValueImpl::I32(JaktInternal::checked_sub(x,static_cast<i32>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_343 = value; goto __jakt_label_329;

}
__jakt_label_329:; __jakt_var_343.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_344; {
types::Value const value = types::Value(TRY((types::ValueImpl::U64(JaktInternal::checked_sub(x,static_cast<u64>(1ULL))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_344 = value; goto __jakt_label_330;

}
__jakt_label_330:; __jakt_var_344.release_value(); }));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_345; {
types::Value const value = types::Value(TRY((types::ValueImpl::I64(JaktInternal::checked_sub(x,static_cast<i64>(1LL))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_345 = value; goto __jakt_label_331;

}
__jakt_label_331:; __jakt_var_345.release_value(); }));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_346; {
types::Value const value = types::Value(TRY((types::ValueImpl::CChar(JaktInternal::checked_sub(x,static_cast<char>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_346 = value; goto __jakt_label_332;

}
__jakt_label_332:; __jakt_var_346.release_value(); }));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_347; {
types::Value const value = types::Value(TRY((types::ValueImpl::CInt(JaktInternal::checked_sub(x,static_cast<int>(1))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_347 = value; goto __jakt_label_333;

}
__jakt_label_333:; __jakt_var_347.release_value(); }));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::Value> __jakt_var_348; {
types::Value const value = types::Value(TRY((types::ValueImpl::USize(JaktInternal::checked_sub(x,static_cast<size_t>(1ULL))))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
__jakt_var_348 = value; goto __jakt_label_334;

}
__jakt_label_334:; __jakt_var_348.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;types::CheckedTypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(TRY((interpreter::cast_value_to_type(value,type_id,*this,false)))));
};/*case end*/
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_349; {
__jakt_var_349 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalSome(TRY((interpreter::cast_value_to_type(value,type_id,*this,false)))))),span)); goto __jakt_label_335;

}
__jakt_label_335:; __jakt_var_349.release_value(); }));
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
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> const& bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_350; {
ByteString const constructor_name = ((((((*this).program))->get_function(constructor)))->name);
if ([](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(((enum_variant).name()),constructor_name)){
return interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(false))),span));
}
__jakt_var_350 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(true))),span)); goto __jakt_label_336;

}
__jakt_label_336:; __jakt_var_350.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid value for unary operator '{}'"sv)),op))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unimplemented unary operator '{}'"sv)),op))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_290;

}
__jakt_label_290:; __jakt_var_304.release_value(); }));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& to = __jakt_match_value.to;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_351; {
types::Value const start = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((from).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((from.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("Partial ranges are not implemented"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::Value const end = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((to).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((to.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("Partial ranges are not implemented"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::StructId const range_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Range"sv))))));
JaktInternal::DynamicArray<ids::FunctionId> const range_constructors = (TRY((((((*this).program))->find_functions_with_name_in_scope(((((((*this).program))->get_struct(range_struct_id))).scope_id),TRY(ByteString::from_utf8("Range"sv)),false,JaktInternal::OptionalNone())))).value());
__jakt_var_351 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({start, end})))),range_struct_id,((range_constructors)[static_cast<i64>(0LL)])))),span)); goto __jakt_label_337;

}
__jakt_label_337:; __jakt_var_351.release_value(); }));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_352; {
if ((!(((((call).function_id)).has_value())))){
JaktInternal::DynamicArray<types::Value> arguments = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
})))));
}

}
}

return TRY((((*this).call_prelude_function(((call).name),(TRY((DynamicArray<types::ResolvedNamespace>::create_with({})))),JaktInternal::OptionalNone(),arguments,span,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))))))));
}
NonnullRefPtr<types::CheckedFunction> const function_to_run = ((((*this).program))->get_function((((call).function_id).value())));
if (((((function_to_run)->type)).__jakt_init_index() == 6 /* Closure */)){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot call a closure (nyi)"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
JaktInternal::Optional<types::Value> this_argument = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<types::Value> arguments = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
})))));
}

}
}

JaktInternal::Dictionary<ids::TypeId,ids::TypeId> type_bindings = (TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((((function_to_run)->generics))->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::FunctionGenericParameter const param = ((((((function_to_run)->generics))->params))[i]);
TRY((((type_bindings).set(((param).type_id()),((((call).type_args))[i])))));
}

}
}

JaktInternal::Dictionary<ByteString,types::Value> const empty_bindings = (TRY((Dictionary<ByteString, types::Value>::create_with_entries({}))));
__jakt_var_352 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute((((call).function_id).value()),static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>>>(((call).namespace_)),this_argument,arguments,span,TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),type_bindings)))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Throw(value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_338;

}
__jakt_label_338:; __jakt_var_352.release_value(); }));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_353; {
types::Value const this_argument = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::ResolvedNamespace> effective_namespace = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((this_argument).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("String"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call a prelude function  on a non-generic array"sv)),((this_argument).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Array"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call a prelude function  on a non-generic dictionary"sv)),((this_argument).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Dictionary"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
if (((((((*this).program))->get_type(type_id)))->__jakt_init_index() == 20 /* GenericInstance */)){
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (((((*this).program))->get_type(type_id)))->as.GenericInstance.args;
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Set"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
else {
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call a prelude function  on a non-generic set"sv)),((this_argument).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(((((((*this).program))->get_enum(enum_id))).name),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* OptionalNone */: {
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* OptionalSome */: {
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call an instance method on a non-struct/enum type"sv)),((this_argument).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
JaktInternal::DynamicArray<types::Value> arguments = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
})))));
}

}
}

return TRY((((*this).call_prelude_function(((call).name),effective_namespace,this_argument,arguments,span,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))))))));
}
NonnullRefPtr<types::CheckedFunction> const function_to_run = ((((*this).program))->get_function((((call).function_id).value())));
JaktInternal::DynamicArray<types::Value> arguments = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
})))));
}

}
}

__jakt_var_353 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute((((call).function_id).value()),static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>>>(((call).namespace_)),this_argument,arguments,span,JaktInternal::OptionalNone()))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Throw(value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_339;

}
__jakt_label_339:; __jakt_var_353.release_value(); }));
};/*case end*/
case 25 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalNone())),span)));
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
{
interpreter::StatementResult const result = TRY((((*this).execute_expression(expr,scope))));
if (((result).__jakt_init_index() == 5 /* JustValue */)){
types::Value const value = (result).as.JustValue.value;
return interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::OptionalSome(value))),span));
}
return result;
}
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_354; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to unwrap an optional value that was None"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_354 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid type for unwrap"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_340;

}
__jakt_label_340:; __jakt_var_354.release_value(); }));
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).execute_block(block,scope,span)))));
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;ByteString const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U8(((val).byte_at(static_cast<size_t>(0ULL)))))),span)));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(TRY((((scope)->must_get(((var)->name)))))));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index_expr = __jakt_match_value.index;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_355; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::Value const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(index_expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_355 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_356; {
u64 const numeric_index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<interpreter::StatementResult>>{
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
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid type for repeat"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ([](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(numeric_index,(infallible_integer_cast<u64>((((values).size())))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Index {} out of bounds (max={})"sv)),numeric_index,((values).size())))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_356 = interpreter::StatementResult::JustValue(((values)[numeric_index])); goto __jakt_label_342;

}
__jakt_label_342:; __jakt_var_356.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid or unsupported indexed expression"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_341;

}
__jakt_label_341:; __jakt_var_355.release_value(); }));
};/*case end*/
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Bool(val))),span)));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_357; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_357 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_358; {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
i64 idx = static_cast<i64>(0LL);
JaktInternal::Optional<i64> found_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((field).variable_id))))->name)) == (name))){
(found_index = idx);
break;
}
((idx) += (static_cast<i64>(1LL)));
}

}
}

if ((!(((found_index).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a field that does not exist"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_358 = interpreter::StatementResult::JustValue(((fields)[(found_index.value())])); goto __jakt_label_344;

}
__jakt_label_344:; __jakt_var_358.release_value(); }));
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_359; {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
i64 idx = static_cast<i64>(0LL);
JaktInternal::Optional<i64> found_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((field).variable_id))))->name)) == (name))){
(found_index = idx);
break;
}
((idx) += (static_cast<i64>(1LL)));
}

}
}

if ((!(((found_index).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a field that does not exist"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_359 = interpreter::StatementResult::JustValue(((fields)[(found_index.value())])); goto __jakt_label_345;

}
__jakt_label_345:; __jakt_var_359.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a field on a non-struct/enum type"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_343;

}
__jakt_label_343:; __jakt_var_357.release_value(); }));
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_360; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_360 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_361; {
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
i64 idx = static_cast<i64>(0LL);
JaktInternal::Optional<i64> found_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((field).variable_id))))->name)) == (index))){
(found_index = idx);
break;
}
((idx) += (static_cast<i64>(1LL)));
}

}
}

if ((!(((found_index).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a field that does not exist"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_361 = interpreter::StatementResult::JustValue(((fields)[(found_index.value())])); goto __jakt_label_347;

}
__jakt_label_347:; __jakt_var_361.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a field on a non-struct/enum type"sv)),((value).span)))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_346;

}
__jakt_label_346:; __jakt_var_360.release_value(); }));
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_362; {
JaktInternal::DynamicArray<types::Value> keys = (TRY((DynamicArray<types::Value>::create_with({}))));
JaktInternal::DynamicArray<types::Value> values = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> k__v__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> const jakt__k__v__ = k__v__;
NonnullRefPtr<typename types::CheckedExpression> const k = ((jakt__k__v__).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const v = ((jakt__k__v__).template get<1>());

types::Value const key = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(k,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
types::Value const val = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(v,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((keys).push(key))));
TRY((((values).push(val))));
}

}
}

__jakt_var_362 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktDictionary(keys,values,type_id))),span)); goto __jakt_label_348;

}
__jakt_label_348:; __jakt_var_362.release_value(); }));
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;types::CheckedNumericConstant const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I8(x))),span));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I16(x))),span));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I32(x))),span));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::I64(x))),span));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U8(x))),span));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U16(x))),span));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U32(x))),span));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::U64(x))),span));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::USize((infallible_integer_cast<size_t>((x)))))),span));
};/*case end*/
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::F32(x))),span));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::F64(x))),span));
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
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;types::CheckedStringLiteral const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((((val).type_id)).equals(types::builtin(types::BuiltinType::JaktString()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktString(TRY((utility::interpret_escapes(((val).to_string()))))))),span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_363; {
ids::FunctionId const function_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::FunctionId, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((val).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_364; {
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((((((*this).program))->get_struct(struct_id))).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const overloads = ((((scope)->functions)).get(TRY(ByteString::from_utf8("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Failed to find a from_string_literal overload in {}"sv)),TRY((((((*this).program))->type_name(((val).type_id),false))))))));
}
__jakt_var_364 = ((((overloads.value())).first()).value()); goto __jakt_label_350;

}
__jakt_label_350:; __jakt_var_364.release_value(); }));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_365; {
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((((((*this).program))->get_struct(struct_id))).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const overloads = ((((scope)->functions)).get(TRY(ByteString::from_utf8("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Failed to find a from_string_literal overload in {}"sv)),TRY((((((*this).program))->type_name(((val).type_id),false))))))));
}
__jakt_var_365 = ((((overloads.value())).first()).value()); goto __jakt_label_351;

}
__jakt_label_351:; __jakt_var_365.release_value(); }));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_366; {
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((((((*this).program))->get_enum(enum_id))).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const overloads = ((((scope)->functions)).get(TRY(ByteString::from_utf8("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
utility::panic(TRY(ByteString::from_utf8("Failed to find a from_string_literal overload"sv)));
}
__jakt_var_366 = ((((overloads.value())).first()).value()); goto __jakt_label_352;

}
__jakt_label_352:; __jakt_var_366.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_367; {
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((((((*this).program))->get_enum(enum_id))).scope_id)))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const overloads = ((((scope)->functions)).get(TRY(ByteString::from_utf8("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
utility::panic(TRY(ByteString::from_utf8("Failed to find a from_string_literal overload"sv)));
}
__jakt_var_367 = ((((overloads.value())).first()).value()); goto __jakt_label_353;

}
__jakt_label_353:; __jakt_var_367.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid type {} for string literal"sv)),((((*this).program))->get_type(((val).type_id)))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::ResolvedNamespace> const ns = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
__jakt_var_363 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute(function_id,static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>>>(ns),JaktInternal::OptionalNone(),(TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::JaktString(TRY((utility::interpret_escapes(((val).to_string()))))))),span)})))),span,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Throw(value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_349;

}
__jakt_label_349:; __jakt_var_363.release_value(); }));
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
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::CChar((infallible_integer_cast<char>((((val).byte_at(static_cast<size_t>(0ULL))))))))),span)));
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;ByteString const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_368; {
DeprecatedStringCodePointIterator code_points = ((val).code_points());
JaktInternal::Optional<u32> const code_point = ((code_points).next());
if ((!(((code_point).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Invalid character constant"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid character constant"sv)));
}
__jakt_var_368 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::U32((code_point.value())))),span)); goto __jakt_label_354;

}
__jakt_label_354:; __jakt_var_368.release_value(); }));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((repeat).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_369; {
size_t const count = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((repeat.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<interpreter::StatementResult>>{
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
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid type for repeat"sv)));
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
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::Value const value_to_repeat = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((vals)[static_cast<i64>(0LL)]),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_369 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktArray((TRY((DynamicArray<types::Value>::filled(count, value_to_repeat)))),TRY((((((*this).program))->substitute_typevars_in_type(type_id,TRY((((scope)->type_map_for_substitution()))),((type_id).module)))))))),span)); goto __jakt_label_355;

}
__jakt_label_355:; __jakt_var_369.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_370; {
JaktInternal::DynamicArray<types::Value> values = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> value = (_magic_value.value());
{
types::Value const val = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(value,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((values).push(val))));
}

}
}

__jakt_var_370 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktArray(values,TRY((((((*this).program))->substitute_typevars_in_type(type_id,TRY((((scope)->type_map_for_substitution()))),((type_id).module)))))))),span)); goto __jakt_label_356;

}
__jakt_label_356:; __jakt_var_370.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_371; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_371 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((((value).impl))->__jakt_init_index() == 26 /* JaktTuple */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_372; {
JaktInternal::DynamicArray<types::Value> const fields = (((value).impl))->as.JaktTuple.fields;
__jakt_var_372 = interpreter::StatementResult::JustValue(((fields)[index])); goto __jakt_label_358;

}
__jakt_label_358:; __jakt_var_372.release_value(); }));
}
else {
{
utility::panic(TRY(ByteString::from_utf8("expected tuple"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_357;

}
__jakt_label_357:; __jakt_var_371.release_value(); }));
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_373; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_373 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_374; {
ByteString const constructor_name = ((((((*this).program))->get_function(constructor)))->name);
JaktInternal::Optional<types::CheckedMatchBody> catch_all_case = JaktInternal::OptionalNone();
JaktInternal::Optional<types::CheckedMatchBody> found_body = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<parser::EnumVariantPatternArgument>> found_args = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> found_variant_index = JaktInternal::OptionalNone();
JaktInternal::Optional<utility::Span> span = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
size_t const& index = __jakt_match_value.index;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if ([](ByteString const& self, ByteString rhs) -> bool {
{
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
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error(TRY(ByteString::from_utf8("Value matches are not allowed on enums"sv)),marker_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error(TRY(ByteString::from_utf8("Value matches are not allowed on enums"sv)),marker_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
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
TRY((((*this).error(TRY(ByteString::from_utf8("Match is not exhaustive"sv)),(span.value())))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
(found_body = found_body.value_or_lazy_evaluated([&] { return (catch_all_case.value()); }));
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const empty_args = (TRY((DynamicArray<parser::EnumVariantPatternArgument>::create_with({}))));
(found_args = found_args.value_or_lazy_evaluated([&] { return empty_args; }));
NonnullRefPtr<interpreter::InterpreterScope> new_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_375([&] {
MUST((((new_scope)->perform_defers(*this,(span.value())))));
});
if ((((found_variant_index).has_value()) && (!((((found_args.value())).is_empty()))))){
types::CheckedEnumVariant const variant = ((((((((*this).program))->get_enum(enum_id))).variants))[(found_variant_index.value())]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
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
((((found_args.value())).size()),static_cast<size_t>(0ULL))){
TRY((((((new_scope)->bindings)).set((((((found_args.value()))[static_cast<i64>(0LL)])).binding),((fields)[static_cast<i64>(0LL)])))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& variant_fields = __jakt_match_value.fields;
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((variant_fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId var_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const field = ((((*this).program))->get_variable(var_id));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = (((found_args.value())).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
ByteString const matched_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
if (((matched_name) == (((field)->name)))){
TRY((((((new_scope)->bindings)).set(((arg).binding),((fields)[i])))));
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
__jakt_var_374 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = (found_body.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_376; {
interpreter::StatementResult const result = TRY((((*this).execute_expression(expr,new_scope))));
__jakt_var_376 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
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
}); goto __jakt_label_361;

}
__jakt_label_361:; __jakt_var_376.release_value(); }));
};/*case end*/
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_377; {
interpreter::StatementResult const result = TRY((((*this).execute_block(block,new_scope,(span.value())))));
__jakt_var_377 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
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
}); goto __jakt_label_362;

}
__jakt_label_362:; __jakt_var_377.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_360;

}
__jakt_label_360:; __jakt_var_374.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_378; {
JaktInternal::Optional<types::CheckedMatchBody> catch_all_case = JaktInternal::OptionalNone();
JaktInternal::Optional<types::CheckedMatchBody> found_body = JaktInternal::OptionalNone();
JaktInternal::Optional<utility::Span> span = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;types::CheckedMatchBody const& body = __jakt_match_value.body;
NonnullRefPtr<typename types::CheckedExpression> const& expression = __jakt_match_value.expression;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
types::Value const value_to_match_against = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expression,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
(found_body = static_cast<JaktInternal::Optional<types::CheckedMatchBody>>(body));
(span = static_cast<JaktInternal::Optional<utility::Span>>(marker_span));
return JaktInternal::LoopBreak{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
(catch_all_case = body);
(span = marker_span);
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error(TRY(ByteString::from_utf8("Class instance matches are not implemented yet"sv)),marker_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Value matches cannot have enum variant arms (matching on {})"sv)),TRY((((value).type_name())))))),marker_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("No match found for value of type {}"sv)),TRY((((value).type_name())))))),(((((*this).spans)).last()).value())))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
(found_body = found_body.value_or_lazy_evaluated([&] { return (catch_all_case.value()); }));
NonnullRefPtr<interpreter::InterpreterScope> new_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_379([&] {
MUST((((new_scope)->perform_defers(*this,(span.value())))));
});
__jakt_var_378 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = (found_body.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_380; {
interpreter::StatementResult const result = TRY((((*this).execute_expression(expr,new_scope))));
__jakt_var_380 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
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
}); goto __jakt_label_364;

}
__jakt_label_364:; __jakt_var_380.release_value(); }));
};/*case end*/
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_381; {
interpreter::StatementResult const result = TRY((((*this).execute_block(block,new_scope,(span.value())))));
__jakt_var_381 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(value));
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
}); goto __jakt_label_365;

}
__jakt_label_365:; __jakt_var_381.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_363;

}
__jakt_label_363:; __jakt_var_378.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_359;

}
__jakt_label_359:; __jakt_var_373.release_value(); }));
};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_382; {
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_382 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_383; {
JaktInternal::Optional<types::CheckedEnumVariant> found_variant = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((((((*this).program))->get_enum(enum_id))).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if (((((variant).name())) == (((enum_variant).name())))){
(found_variant = variant);
break;
}
}

}
}

__jakt_var_383 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = (found_variant.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Typed */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(((fields)[static_cast<i64>(0LL)])));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& variant_fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_384; {
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((variant_fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId var_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const field = ((((*this).program))->get_variable(var_id));
ByteString const matched_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
if (((matched_name) == (((field)->name)))){
break;
}
((i) += (static_cast<i64>(1LL)));
}

}
}

__jakt_var_384 = interpreter::StatementResult::JustValue(((fields)[i])); goto __jakt_label_368;

}
__jakt_label_368:; __jakt_var_384.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),span)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_367;

}
__jakt_label_367:; __jakt_var_383.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Value matches cannot have enum variant arms (matching on {})"sv)),TRY((((value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_366;

}
__jakt_label_366:; __jakt_var_382.release_value(); }));
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_385; {
JaktInternal::DynamicArray<types::Value> fields = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(val,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((fields).push(value))));
}

}
}

__jakt_var_385 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktTuple(fields,type_id))),span)); goto __jakt_label_369;

}
__jakt_label_369:; __jakt_var_385.release_value(); }));
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_386; {
JaktInternal::DynamicArray<types::Value> values = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> v = (_magic_value.value());
{
types::Value const val = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(v,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& expr = __jakt_match_value.value;
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
TRY((((values).push(val))));
}

}
}

__jakt_var_386 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::JaktSet(values,type_id))),span)); goto __jakt_label_370;

}
__jakt_label_370:; __jakt_var_386.release_value(); }));
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;JaktInternal::DynamicArray<types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<types::CheckedParameter> const& params = __jakt_match_value.params;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::TypeId const& type_id = __jakt_match_value.type_id;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
bool const& can_throw = __jakt_match_value.can_throw;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_387; {
JaktInternal::Dictionary<ByteString,types::Value> resolved_captures = (TRY((Dictionary<ByteString, types::Value>::create_with_entries({}))));
{
JaktInternal::ArrayIterator<types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedCapture capture = (_magic_value.value());
{
ByteString const name = ((capture).common.init_common.name);
if ((((capture).__jakt_init_index() == 0 /* ByValue */) || ((capture).__jakt_init_index() == 3 /* ByComptimeDependency */))){
TRY((((resolved_captures).set(name,TRY((((scope)->must_get(name))))))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot capture by reference in a comptime function (nyi)"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}

}

}
}

types::GenericInferences const type_map = TRY((((scope)->type_map_for_substitution())));
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> resolved_params = (TRY((Dictionary<ByteString, JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>>::create_with_entries({}))));
JaktInternal::DynamicArray<types::CheckedParameter> checked_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
ids::TypeId const param_type_id = TRY((((((*this).program))->substitute_typevars_in_type(((((param).variable))->type_id),type_map,((((((param).variable))->type_id)).module)))));
TRY((((resolved_params).set(((((param).variable))->name),(Tuple{param_type_id, ((param).default_value_expression)})))));
TRY((((checked_params).push(types::CheckedParameter(((param).requires_label),TRY((types::CheckedVariable::__jakt_create(((((param).variable))->name),param_type_id,((((param).variable))->is_mutable),((((param).variable))->definition_span),((((param).variable))->type_span),((((param).variable))->visibility),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),((param).default_value_expression))))));
}

}
}

types::CheckedBlock const fixed_block = TRY((((*this).perform_final_interpretation_pass(block,scope_id,TRY((interpreter::InterpreterScope::create(resolved_captures,scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))))))),pseudo_function_id))));
__jakt_var_387 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Function(resolved_captures,resolved_params,TRY((((((*this).program))->substitute_typevars_in_type(return_type_id,type_map,((return_type_id).module))))),TRY((((((*this).program))->substitute_typevars_in_type(type_id,type_map,((type_id).module))))),fixed_block,can_throw,checked_params,scope_id,pseudo_function_id))),span)); goto __jakt_label_371;

}
__jakt_label_371:; __jakt_var_387.release_value(); }));
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<types::CheckedParameter> const& params = __jakt_match_value.params;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::TypeId const& type_id = __jakt_match_value.type_id;
types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
bool const& can_throw = __jakt_match_value.can_throw;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_388; {
JaktInternal::Dictionary<ByteString,types::Value> resolved_captures = (TRY((Dictionary<ByteString, types::Value>::create_with_entries({}))));
{
JaktInternal::ArrayIterator<types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedCapture capture = (_magic_value.value());
{
ByteString const name = ((capture).common.init_common.name);
if ((((capture).__jakt_init_index() == 0 /* ByValue */) || ((capture).__jakt_init_index() == 3 /* ByComptimeDependency */))){
TRY((((resolved_captures).set(name,TRY((((scope)->must_get(name))))))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot capture by reference in a comptime function (nyi)"sv))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}

}

}
}

types::GenericInferences const type_map = TRY((((scope)->type_map_for_substitution())));
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> resolved_params = (TRY((Dictionary<ByteString, JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>>::create_with_entries({}))));
JaktInternal::DynamicArray<types::CheckedParameter> checked_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
ids::TypeId const param_type_id = TRY((((((*this).program))->substitute_typevars_in_type(((((param).variable))->type_id),type_map,((((((param).variable))->type_id)).module)))));
TRY((((resolved_params).set(((((param).variable))->name),(Tuple{param_type_id, ((param).default_value_expression)})))));
TRY((((checked_params).push(types::CheckedParameter(((param).requires_label),TRY((types::CheckedVariable::__jakt_create(((((param).variable))->name),param_type_id,((((param).variable))->is_mutable),((((param).variable))->definition_span),((((param).variable))->type_span),((((param).variable))->visibility),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),((param).default_value_expression))))));
}

}
}

types::CheckedBlock const fixed_block = TRY((((*this).perform_final_interpretation_pass(block,scope_id,TRY((interpreter::InterpreterScope::create(resolved_captures,scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))))))),pseudo_function_id))));
__jakt_var_388 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Function(resolved_captures,resolved_params,TRY((((((*this).program))->substitute_typevars_in_type(return_type_id,type_map,((return_type_id).module))))),TRY((((((*this).program))->substitute_typevars_in_type(type_id,type_map,((type_id).module))))),fixed_block,can_throw,checked_params,scope_id,pseudo_function_id))),span)); goto __jakt_label_372;

}
__jakt_label_372:; __jakt_var_388.release_value(); }));
};/*case end*/
case 32 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
ByteString const& error_name = __jakt_match_value.error_name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<interpreter::StatementResult> __jakt_var_389; {
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_statement(stmt,scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
NonnullRefPtr<interpreter::InterpreterScope> catch_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_390([&] {
MUST((((catch_scope)->perform_defers(*this,span))));
});
TRY((((((catch_scope)->bindings)).set(error_name,value))));
interpreter::StatementResult const result = TRY((((*this).execute_block(catch_block,catch_scope,span))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
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
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
__jakt_var_389 = interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),span)); goto __jakt_label_373;

}
__jakt_label_373:; __jakt_var_389.release_value(); }));
};/*case end*/
case 33 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;ids::TypeId const& type_id = __jakt_match_value.type;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(TRY((((*this).reflect_type(type_id,span,scope))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("expression not implemented: {}"sv)),expr))),((expr)->span())))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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

ErrorOr<interpreter::StatementResult> interpreter::Interpreter::execute_expression(NonnullRefPtr<typename types::CheckedExpression> const expr,NonnullRefPtr<interpreter::InterpreterScope> scope) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((((*this).current_function_id)).has_value()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).execute_expression_without_cast(expr,scope)))));
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression_without_cast(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Return(TRY((interpreter::cast_value_to_type(value,((((((*this).program))->get_function((((*this).current_function_id).value()))))->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(TRY((interpreter::cast_value_to_type(value,((expr)->type()),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Throw(value));
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Yield(value));
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::Break());
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::Continue());
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

ErrorOr<interpreter::StatementResult> interpreter::Interpreter::execute_binary_operator(types::Value const lhs_value,types::Value const rhs_value,parser::BinaryOperator const op,utility::Span const span,NonnullRefPtr<interpreter::InterpreterScope> const scope) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F32(((x) + (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F64(((x) + (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(JaktInternal::checked_add(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::JaktString(TRY((((x) + (y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F32(((x) - (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F64(((x) - (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(JaktInternal::checked_sub(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F32(((x) * (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F64(((x) * (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(JaktInternal::checked_mul(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F32(((x) / (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::F64(((x) / (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(JaktInternal::checked_div(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) == (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) != (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) < (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) <= (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) > (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool(((x) >= (y))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>(((x & y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>(((x & y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32((x & y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64((x & y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>(((x & y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>(((x & y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32((x & y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64((x & y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize((x & y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>(((x | y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>(((x | y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32((x | y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64((x | y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>(((x | y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>(((x | y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32((x | y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64((x | y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize((x | y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>(((x ^ y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>(((x ^ y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32((x ^ y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64((x ^ y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>(((x ^ y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>(((x ^ y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32((x ^ y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64((x ^ y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize((x ^ y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>(((x >> y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>(((x >> y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32((x >> y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64((x >> y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>(((x >> y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>(((x >> y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32((x >> y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64((x >> y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize((x >> y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8((infallible_integer_cast<u8>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16((infallible_integer_cast<u16>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8((infallible_integer_cast<i8>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16((infallible_integer_cast<i16>(((x << y))))))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize((x << y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U8(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U16(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U32(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::U64(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I8(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I16(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I32(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::I64(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::USize(JaktInternal::arithmetic_shift_right(x,y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool((x || y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Bool((x && y)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),TRY((((lhs_value).type_name()))),TRY((((rhs_value).type_name())))))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(rhs_value));
};/*case end*/
case 22 /* BitwiseAndAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::BitwiseAnd(),span,scope)))));
};/*case end*/
case 23 /* BitwiseOrAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::BitwiseOr(),span,scope)))));
};/*case end*/
case 24 /* BitwiseXorAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::BitwiseXor(),span,scope)))));
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::BitwiseLeftShift(),span,scope)))));
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::BitwiseRightShift(),span,scope)))));
};/*case end*/
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::Add(),span,scope)))));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::Subtract(),span,scope)))));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::Multiply(),span,scope)))));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::Modulo(),span,scope)))));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,parser::BinaryOperator::Divide(),span,scope)))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unimplemented binary operator '{}'"sv)),op))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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

ErrorOr<ids::TypeId> interpreter::Interpreter::array_type_of_struct(ids::StructId const struct_id) {
{
ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Array"sv))))));
NonnullRefPtr<typename types::Type> const type = TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),array_struct_id,(TRY((DynamicArray<ids::TypeId>::create_with({((((((*this).program))->get_struct(struct_id))).type_id)})))))));
return TRY((((*this).find_or_add_type_id(type))));
}
}

void interpreter::Interpreter::leave_span() {
{
JaktInternal::Optional<utility::Span> const dummy = ((((*this).spans)).pop());
}
}

ErrorOr<JaktInternal::DynamicArray<types::Value>> interpreter::Interpreter::reflect_fields(JaktInternal::DynamicArray<ids::VarId> const fields,utility::Span const span,NonnullRefPtr<interpreter::InterpreterScope> const scope) {
{
ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const field_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(field_struct_id))).scope_id),TRY(ByteString::from_utf8("Field"sv)),JaktInternal::OptionalNone())))).value());
ids::EnumId const visibility_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Visibility"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Visibility to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const visibility_public_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(visibility_enum_id))).scope_id),TRY(ByteString::from_utf8("Public"sv)),JaktInternal::OptionalNone())))).value());
ids::FunctionId const visibility_private_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(visibility_enum_id))).scope_id),TRY(ByteString::from_utf8("Private"sv)),JaktInternal::OptionalNone())))).value());
ids::StructId const variable_declaration_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("VariableDeclaration"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected VariableDeclaration to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const variable_declaration_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(variable_declaration_struct_id))).scope_id),TRY(ByteString::from_utf8("VariableDeclaration"sv)),JaktInternal::OptionalNone())))).value());
JaktInternal::DynamicArray<types::Value> record_type_fields = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId var_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const field = ((((*this).program))->get_variable(var_id));
types::Value const variable = types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::JaktString(((field)->name)))),span), TRY((((*this).reflect_type(((field)->type_id),span,scope)))), types::Value(TRY((types::ValueImpl::Bool(((field)->is_mutable)))),span)})))),variable_declaration_struct_id,variable_declaration_struct_constructor))),span);
types::Value const field_value = types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({variable, types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({})))),visibility_enum_id,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::FunctionId, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
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
utility::panic(TRY(ByteString::from_utf8("Not implemented"sv)));
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
})))),span)})))),field_struct_id,field_struct_constructor))),span);
TRY((((record_type_fields).push(field_value))));
}

}
}

return record_type_fields;
}
}

ErrorOr<types::Value> interpreter::Interpreter::tuple_value(JaktInternal::DynamicArray<types::Value> const members,ids::TypeId const type,utility::Span const span) {
{
return types::Value(TRY((types::ValueImpl::JaktTuple(members,type))),span);
}
}

ErrorOr<void> interpreter::Interpreter::error(ByteString const message,utility::Span const span) {
{
TRY((((((((*this).compiler))->errors)).push(error::JaktError::Message(message,span)))));
TRY((((((*this).compiler))->print_errors())));
}
return {};
}

ErrorOr<NonnullRefPtr<interpreter::Interpreter>> interpreter::Interpreter::create(NonnullRefPtr<compiler::Compiler> const compiler,NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::TypecheckFunctions> const typecheck_functions,JaktInternal::DynamicArray<utility::Span> const spans) {
{
return TRY((interpreter::Interpreter::__jakt_create(compiler,program,spans,(TRY((Dictionary<ids::TypeId, types::Value>::create_with_entries({})))),(TRY((Set<ids::TypeId>::create_with_values({})))),JaktInternal::OptionalNone(),typecheck_functions)));
}
}

ErrorOr<interpreter::StatementResult> interpreter::Interpreter::execute_statement(NonnullRefPtr<typename types::CheckedStatement> const statement,NonnullRefPtr<interpreter::InterpreterScope> scope,utility::Span const call_span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
{
return TRY((((*this).execute_expression(expr,scope))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename types::CheckedStatement> const& statement = __jakt_match_value.statement;
{
TRY((((scope)->defer_statement(statement))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
{
if (((var_decl)->__jakt_init_index() == 3 /* VarDecl */)){
ids::VarId const var_id = (var_decl)->as.VarDecl.var_id;
NonnullRefPtr<typename types::CheckedExpression> const init = (var_decl)->as.VarDecl.init;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(init,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& var_value = __jakt_match_value.value;
{
TRY(((scope)->bindings).set(((((((*this).program))->get_variable(var_id)))->name), var_value));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> var = (_magic_value.value());
{
if (((var)->__jakt_init_index() == 3 /* VarDecl */)){
ids::VarId const var_id = (var)->as.VarDecl.var_id;
NonnullRefPtr<typename types::CheckedExpression> const init = (var)->as.VarDecl.init;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(init,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& var_value = __jakt_match_value.value;
{
TRY(((scope)->bindings).set(((((((*this).program))->get_variable(var_id)))->name), var_value));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
utility::panic(TRY(ByteString::from_utf8("expected vardecl"sv)));
}

}

}
}

}
else {
utility::panic(TRY(ByteString::from_utf8("expected vardecl"sv)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename types::CheckedExpression> const& init = __jakt_match_value.init;
utility::Span const& span = __jakt_match_value.span;
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(init,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& var_value = __jakt_match_value.value;
{
TRY(((scope)->bindings).set(((((((*this).program))->get_variable(var_id)))->name), var_value));
if (((((var_value).impl))->__jakt_init_index() == 27 /* Function */)){
types::CheckedBlock const block = (((var_value).impl))->as.Function.block;
JaktInternal::Optional<ids::FunctionId> const pseudo_function_id = (((var_value).impl))->as.Function.pseudo_function_id;
if (((pseudo_function_id).has_value())){
ids::FunctionId const id = (pseudo_function_id.value());
(((((((*this).program))->get_function(id)))->block) = block);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
utility::Span const& span = __jakt_match_value.span;
{
bool const cond = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(condition,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("if condition must be a boolean, but got {}"sv)),((value).impl)))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<types::CheckedBlock> const block = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::CheckedBlock>,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (cond);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::CheckedBlock>>(then_block));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::CheckedBlock>,ErrorOr<interpreter::StatementResult>>{
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::CheckedBlock>>(types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({(else_statement.value())})))),((then_block).scope_id),types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block((block.value()),scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Throw(value));
};/*case end*/
case 5 /* JustValue */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),span)));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::Continue());
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::Break());
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<interpreter::InterpreterScope> new_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_391([&] {
MUST((((new_scope)->perform_defers(*this,span))));
});
return TRY((((*this).execute_block(block,new_scope,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
{
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(block,scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
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
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
{
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(condition,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& x = __jakt_match_value.value;
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
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(block,scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
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
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& val = __jakt_match_value.val;
{
if (((val).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::StatementResult, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((val.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Throw(value));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::StatementResult::Return(value));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::Continue());
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(interpreter::StatementResult::Break());
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
return interpreter::StatementResult::Return(types::Value(TRY((types::ValueImpl::Void())),call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Yield(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;utility::Span const& span = __jakt_match_value.span;
return (TRY((((*this).error(TRY(ByteString::from_utf8("Cannot run inline cpp at compile time"sv)),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.value;
return (TRY((((*this).error(TRY(ByteString::from_utf8("Cannot run invalid statements at compile time"sv)),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span));
}
}

ErrorOr<JaktInternal::DynamicArray<types::Value>> interpreter::Interpreter::reflect_sum_enum_variants(types::CheckedEnum const subject_enum,utility::Span const span,NonnullRefPtr<interpreter::InterpreterScope> const scope) {
{
ids::EnumId const sum_enum_variant_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("SumEnumVariant"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected SumEnumVariant to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const typed_variant_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(sum_enum_variant_enum_id))).scope_id),TRY(ByteString::from_utf8("Typed"sv)),JaktInternal::OptionalNone())))).value());
ids::FunctionId const struct_like_variant_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(sum_enum_variant_enum_id))).scope_id),TRY(ByteString::from_utf8("StructLike"sv)),JaktInternal::OptionalNone())))).value());
ids::FunctionId const untyped_variant_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(sum_enum_variant_enum_id))).scope_id),TRY(ByteString::from_utf8("Untyped"sv)),JaktInternal::OptionalNone())))).value());
ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::Value> result = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((subject_enum).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<types::Value>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
ids::TypeId const& type_id = __jakt_match_value.type_id;
{
types::Value const type_value = TRY((((*this).reflect_type(type_id,span,scope))));
types::Value const variant_value = types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), type_value})))),sum_enum_variant_enum_id,typed_variant_constructor))),span);
TRY((((result).push(variant_value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
{
types::Value const variant_value = types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span))))})))),sum_enum_variant_enum_id,untyped_variant_constructor))),span);
TRY((((result).push(variant_value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<types::Value> const reflected_fields = TRY((((*this).reflect_fields(fields,span,scope))));
types::Value const variant_value = types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).array_value_of_type(reflected_fields,TRY((((*this).array_type_of_struct(field_struct_id)))),span))))})))),sum_enum_variant_enum_id,struct_like_variant_constructor))),span);
TRY((((result).push(variant_value))));
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

ErrorOr<interpreter::ExecutionResult> interpreter::Interpreter::execute(ids::FunctionId const function_to_run_id,JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> namespace_,JaktInternal::Optional<types::Value> const this_argument,JaktInternal::DynamicArray<types::Value> const arguments,utility::Span const call_span,JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const invocation_scope) {
{
NonnullRefPtr<types::CheckedFunction> const function_to_run = ((((*this).program))->get_function(function_to_run_id));
TRY((((*this).enter_span(call_span))));
JaktInternal::Optional<ids::FunctionId> const old_function_id = ((*this).current_function_id);
(((*this).current_function_id) = function_to_run_id);
ScopeGuard __jakt_var_392([&] {
{
(((*this).current_function_id) = old_function_id);
((*this).leave_span());
}

});
bool is_prelude_function = false;
if (((((function_to_run)->linkage)).__jakt_init_index() == 1 /* External */)){
NonnullRefPtr<types::Scope> const function_scope = TRY((((((*this).program))->get_scope(((function_to_run)->function_scope_id)))));
if ((!(TRY((((*this).get_prelude_function(((function_to_run)->function_scope_id)))))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot call external function '{}'"sv)),((function_to_run)->name)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Attempt to call external function"sv)));
}
(is_prelude_function = true);
}
if (((TRY((((function_to_run)->is_static())))) == (((this_argument).has_value())))){
ByteString expected = TRY(ByteString::from_utf8("did not expect"sv));
if ((!(TRY((((function_to_run)->is_static())))))){
(expected = TRY(ByteString::from_utf8("expected"sv)));
}
ByteString not_provided = TRY(ByteString::from_utf8(" not"sv));
if (((this_argument).has_value())){
(not_provided = TRY(ByteString::from_utf8(""sv)));
}
TRY((((((((*this).compiler))->errors)).push(error::JaktError::Message(TRY((__jakt_format((StringView::from_string_literal("function call {} a this argument, yet one was{} provided"sv)),expected,not_provided))),((function_to_run)->name_span))))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid this argument"sv)));
}
size_t this_offset = static_cast<size_t>(0ULL);
if (((this_argument).has_value())){
(this_offset = static_cast<size_t>(1ULL));
}
if (((JaktInternal::checked_sub(((((function_to_run)->params)).size()),this_offset)) != (((arguments).size())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Function called with wrong number of arguments, expected {} but got {}"sv)),((((function_to_run)->params)).size()),((arguments).size())))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Mismatching arguments"sv)));
}
if (is_prelude_function){
if ((((this_argument).has_value()) && ((!(((namespace_).has_value()))) || (((namespace_.value())).is_empty())))){
JaktInternal::DynamicArray<types::ResolvedNamespace> effective_namespace = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("String"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call a prelude function  on a non-generic array"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Array"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call a prelude function  on a non-generic dictionary"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Dictionary"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
if (((((((*this).program))->get_type(type_id)))->__jakt_init_index() == 20 /* GenericInstance */)){
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (((((*this).program))->get_type(type_id)))->as.GenericInstance.args;
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Set"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
else {
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call a prelude function  on a non-generic set"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(((((((*this).program))->get_enum(enum_id))).name),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* OptionalNone */: {
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* OptionalSome */: {
{
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((effective_namespace).push(types::ResolvedNamespace(TRY(ByteString::from_utf8("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to call an instance method on a non-struct/enum type"sv)),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> type_bindings = (TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))));
if (((invocation_scope).has_value())){
(type_bindings = (((invocation_scope.value()))->type_bindings));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::ExecutionResult, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).call_prelude_function(((function_to_run)->name),(namespace_.value()),this_argument,arguments,call_span,type_bindings))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(value));
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = ((function_to_run)->type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Normal */: {
{
NonnullRefPtr<interpreter::InterpreterScope> scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),invocation_scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_393([&] {
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
types::Value const param_value = ((arguments)[JaktInternal::checked_sub(i,this_offset)]);
TRY(((scope)->bindings).set(param_name, param_value));
}

}
}

if (((this_argument).has_value())){
TRY((((((scope)->bindings)).set(TRY(ByteString::from_utf8("this"sv)),(this_argument.value())))));
}
interpreter::StatementResult const blk = TRY((((*this).execute_block(((function_to_run)->block),scope,call_span))));
if (((blk).__jakt_init_index() == 5 /* JustValue */)){
types::Value const x = (blk).as.JustValue.value;
if (((((x).impl))->__jakt_init_index() == 0 /* Void */)){
warnln((StringView::from_string_literal("Comptime function returned void, scope: {}"sv)),((TRY((((((*this).program))->get_scope(((function_to_run)->function_scope_id))))))->debug_name));
abort();
}
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::ExecutionResult, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = blk;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(TRY((interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(TRY((interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
case 6 /* Closure */: {
{
NonnullRefPtr<interpreter::InterpreterScope> scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),invocation_scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_394([&] {
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
types::Value const param_value = ((arguments)[JaktInternal::checked_sub(i,this_offset)]);
TRY(((scope)->bindings).set(param_name, param_value));
}

}
}

if (((this_argument).has_value())){
TRY((((((scope)->bindings)).set(TRY(ByteString::from_utf8("this"sv)),(this_argument.value())))));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::ExecutionResult, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(((function_to_run)->block),scope,call_span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(TRY((interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(TRY((interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
case 5 /* Expression */: {
{
NonnullRefPtr<interpreter::InterpreterScope> scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),invocation_scope,(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
ScopeGuard __jakt_var_395([&] {
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
types::Value const param_value = ((arguments)[JaktInternal::checked_sub(i,this_offset)]);
TRY(((scope)->bindings).set(param_name, param_value));
}

}
}

if (((this_argument).has_value())){
TRY((((((scope)->bindings)).set(TRY(ByteString::from_utf8("this"sv)),(this_argument.value())))));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<interpreter::ExecutionResult, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(((function_to_run)->block),scope,call_span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(TRY((interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Return(TRY((interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
utility::panic(TRY(ByteString::from_utf8("Invalid control flow"sv)));
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
case 2 /* ImplicitConstructor */: {
{
NonnullRefPtr<typename types::Type> const result_type = ((((*this).program))->get_type(((function_to_run)->return_type_id)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *result_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename types::ValueImpl> const impl = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Struct(arguments,struct_id,constructor))));
};/*case end*/
case 1 /* Class */: {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Class(arguments,struct_id,constructor))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot create instance of non-struct type {}"sv)),((struct_).name)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return interpreter::ExecutionResult::Return(types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename types::ValueImpl> const impl = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Struct(arguments,struct_id,constructor))));
};/*case end*/
case 1 /* Class */: {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::Class(arguments,struct_id,constructor))));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot create instance of non-struct type {}"sv)),((struct_).name)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return interpreter::ExecutionResult::Return(types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Implicit constructor can only return a struct or a generic instance"sv))))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
case 3 /* ImplicitEnumConstructor */: {
{
NonnullRefPtr<typename types::Type> const result_type = ((((*this).program))->get_type(((function_to_run)->return_type_id)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *result_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename types::ValueImpl> const impl = TRY((types::ValueImpl::Enum(arguments,enum_id,constructor)));
return interpreter::ExecutionResult::Return(types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename types::ValueImpl> const impl = TRY((types::ValueImpl::Enum(arguments,enum_id,constructor)));
return interpreter::ExecutionResult::Return(types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Implicit enum constructor can only return an enum or a generic instance of one"sv))))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Function type {} is not implemented"sv)),((function_to_run)->type)))),call_span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
}

ErrorOr<types::CheckedBlock> interpreter::Interpreter::invoke_typecheck_block(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> const& function,parser::ParsedBlock const block,ids::ScopeId const parent_scope_id,JaktInternal::Optional<ids::FunctionId> const function_id) {
{
return TRY((function(block,parent_scope_id,types::SafetyMode::Safe(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
}
}

ErrorOr<ids::TypeId> interpreter::Interpreter::tuple_type(JaktInternal::DynamicArray<ids::TypeId> const members) {
{
ids::StructId const tuple_struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Tuple"sv))))));
NonnullRefPtr<typename types::Type> const type = TRY((types::Type::GenericInstance(parser::CheckedQualifiers(false),tuple_struct_id,members)));
return TRY((((*this).find_or_add_type_id(type))));
}
}

ErrorOr<types::Value> interpreter::Interpreter::error_value(ByteString const string,utility::Span const span) {
{
ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude(TRY(ByteString::from_utf8("Error"sv))))));
ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(struct_id))).scope_id),TRY(ByteString::from_utf8("from_string_literal"sv)),JaktInternal::OptionalNone())))).value());
return types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(string,span))))})))),struct_id,constructor))),span);
}
}

ErrorOr<interpreter::StatementResult> interpreter::Interpreter::execute_block(types::CheckedBlock const block,NonnullRefPtr<interpreter::InterpreterScope> scope,utility::Span const call_span) {
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
TRY((((*this).enter_span(((statement)->span()).value_or_lazy_evaluated([&] { return call_span; })))));
ScopeGuard __jakt_var_396([&] {
((*this).leave_span());
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_statement(statement,scope,call_span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;types::Value const& value = __jakt_match_value.value;
{
return interpreter::StatementResult::Yield(value);
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

return interpreter::StatementResult::JustValue(types::Value(TRY((types::ValueImpl::Void())),call_span));
}
}

ErrorOr<types::Value> interpreter::Interpreter::reflect_type(ids::TypeId const type_id,utility::Span const span,NonnullRefPtr<interpreter::InterpreterScope> const scope) {
{
ids::TypeId const mapped_type_id = TRY((((scope)->map_type(type_id))));
if (((((*this).reflected_type_cache)).contains(mapped_type_id))){
return (((((*this).reflected_type_cache)).get(mapped_type_id)).value());
}
TRY((((((*this).seen_reflected_types)).add(mapped_type_id))));
ScopeGuard __jakt_var_397([&] {
((((*this).seen_reflected_types)).remove(mapped_type_id));
});
NonnullRefPtr<typename types::Type> const type = ((((*this).program))->get_type(mapped_type_id));
ids::EnumId const reflected_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Type"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Reflect::Type to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::CheckedEnum const reflected_enum = ((((*this).program))->get_enum(reflected_enum_id));
types::Value result = types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({})))),reflected_enum_id,ids::FunctionId(((type_id).module),static_cast<size_t>(0ULL))))),span);
TRY((((((*this).reflected_type_cache)).set(mapped_type_id,result))));
JaktInternal::DynamicArray<types::Value> fields = (TRY((DynamicArray<types::Value>::create_with({}))));
ids::FunctionId const found_constructor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::FunctionId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_398; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_398 = (constructor.value()); goto __jakt_label_374;

}
__jakt_label_374:; __jakt_var_398.release_value(); }));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_399; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_399 = (constructor.value()); goto __jakt_label_375;

}
__jakt_label_375:; __jakt_var_399.release_value(); }));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_400; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_400 = (constructor.value()); goto __jakt_label_376;

}
__jakt_label_376:; __jakt_var_400.release_value(); }));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_401; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_401 = (constructor.value()); goto __jakt_label_377;

}
__jakt_label_377:; __jakt_var_401.release_value(); }));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_402; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_402 = (constructor.value()); goto __jakt_label_378;

}
__jakt_label_378:; __jakt_var_402.release_value(); }));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_403; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_403 = (constructor.value()); goto __jakt_label_379;

}
__jakt_label_379:; __jakt_var_403.release_value(); }));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_404; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_404 = (constructor.value()); goto __jakt_label_380;

}
__jakt_label_380:; __jakt_var_404.release_value(); }));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_405; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_405 = (constructor.value()); goto __jakt_label_381;

}
__jakt_label_381:; __jakt_var_405.release_value(); }));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_406; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_406 = (constructor.value()); goto __jakt_label_382;

}
__jakt_label_382:; __jakt_var_406.release_value(); }));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_407; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_407 = (constructor.value()); goto __jakt_label_383;

}
__jakt_label_383:; __jakt_var_407.release_value(); }));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_408; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_408 = (constructor.value()); goto __jakt_label_384;

}
__jakt_label_384:; __jakt_var_408.release_value(); }));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_409; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_409 = (constructor.value()); goto __jakt_label_385;

}
__jakt_label_385:; __jakt_var_409.release_value(); }));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_410; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_410 = (constructor.value()); goto __jakt_label_386;

}
__jakt_label_386:; __jakt_var_410.release_value(); }));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_411; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_411 = (constructor.value()); goto __jakt_label_387;

}
__jakt_label_387:; __jakt_var_411.release_value(); }));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_412; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_412 = (constructor.value()); goto __jakt_label_388;

}
__jakt_label_388:; __jakt_var_412.release_value(); }));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_413; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_413 = (constructor.value()); goto __jakt_label_389;

}
__jakt_label_389:; __jakt_var_413.release_value(); }));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_414; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_414 = (constructor.value()); goto __jakt_label_390;

}
__jakt_label_390:; __jakt_var_414.release_value(); }));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_415; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
__jakt_var_415 = (constructor.value()); goto __jakt_label_391;

}
__jakt_label_391:; __jakt_var_415.release_value(); }));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_416; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY(ByteString::from_utf8("TypeVariable"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
(fields = (TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span))))})))));
__jakt_var_416 = (constructor.value()); goto __jakt_label_392;

}
__jakt_label_392:; __jakt_var_416.release_value(); }));
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_417; {
ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone())))).value());
(fields = (TRY((DynamicArray<types::Value>::create_with({TRY((((*this).reflect_type(type_id,span,scope))))})))));
__jakt_var_417 = constructor; goto __jakt_label_393;

}
__jakt_label_393:; __jakt_var_417.release_value(); }));
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_418; {
ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone())))).value());
(fields = (TRY((DynamicArray<types::Value>::create_with({TRY((((*this).reflect_type(type_id,span,scope))))})))));
__jakt_var_418 = constructor; goto __jakt_label_394;

}
__jakt_label_394:; __jakt_var_418.release_value(); }));
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_419; {
ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY((((type)->constructor_name()))),JaktInternal::OptionalNone())))).value());
(fields = (TRY((DynamicArray<types::Value>::create_with({TRY((((*this).reflect_type(type_id,span,scope))))})))));
__jakt_var_419 = constructor; goto __jakt_label_395;

}
__jakt_label_395:; __jakt_var_419.release_value(); }));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_420; {
types::CheckedStruct const subject_struct = ((((*this).program))->get_struct(struct_id));
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY(ByteString::from_utf8("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),TRY(ByteString::from_utf8("Record"sv)),JaktInternal::OptionalNone())))).value());
ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const record_type_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),TRY(ByteString::from_utf8("Struct"sv)),JaktInternal::OptionalNone())))).value());
types::Value const methods = TRY((((*this).reflect_methods(((subject_struct).scope_id),span,scope))));
ids::TypeId const tuple_type = TRY((((*this).tuple_type((TRY((DynamicArray<ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)}))))))));
types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<types::Value>> __jakt_var_421; {
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<types::Value> result = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((subject_struct).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Unknown kind of generic parameter in struct definition"sv)));
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
ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId,ErrorOr<types::Value>>{
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Unknown()));
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
TRY((((result).push(TRY((((*this).tuple_value((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))})))),tuple_type,span))))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

__jakt_var_421 = result; goto __jakt_label_397;

}
__jakt_label_397:; __jakt_var_421.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<types::Value>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<ids::VarId> reflected_fields = (TRY((DynamicArray<ids::VarId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((subject_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
TRY((((reflected_fields).push(((field).variable_id)))));
}

}
}

JaktInternal::DynamicArray<types::Value> const record_type_fields = TRY((((*this).reflect_fields(reflected_fields,span,scope))));
ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = (TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(((subject_struct).name),span)))), methods, generic_parameters, types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))))),span)})))),record_type_enum_id,record_type_struct_constructor))),span)})))),record_struct_id,record_struct_constructor))),span)})))));
__jakt_var_420 = (constructor.value()); goto __jakt_label_396;

}
__jakt_label_396:; __jakt_var_420.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_422; {
types::CheckedStruct const subject_struct = ((((*this).program))->get_struct(struct_id));
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY(ByteString::from_utf8("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),TRY(ByteString::from_utf8("Record"sv)),JaktInternal::OptionalNone())))).value());
ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const record_type_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),TRY(ByteString::from_utf8("Struct"sv)),JaktInternal::OptionalNone())))).value());
types::Value const methods = TRY((((*this).reflect_methods(((subject_struct).scope_id),span,scope))));
ids::TypeId const tuple_type = TRY((((*this).tuple_type((TRY((DynamicArray<ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)}))))))));
types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<types::Value>> __jakt_var_423; {
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<types::Value> result = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((subject_struct).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Unknown kind of generic parameter in struct definition"sv)));
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
ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId,ErrorOr<types::Value>>{
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Unknown()));
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
TRY((((result).push(TRY((((*this).tuple_value((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))})))),tuple_type,span))))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

__jakt_var_423 = result; goto __jakt_label_399;

}
__jakt_label_399:; __jakt_var_423.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<types::Value>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<ids::VarId> reflected_fields = (TRY((DynamicArray<ids::VarId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((subject_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
TRY((((reflected_fields).push(((field).variable_id)))));
}

}
}

JaktInternal::DynamicArray<types::Value> const record_type_fields = TRY((((*this).reflect_fields(reflected_fields,span,scope))));
ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = (TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(((subject_struct).name),span)))), methods, generic_parameters, types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))))),span)})))),record_type_enum_id,record_type_struct_constructor))),span)})))),record_struct_id,record_struct_constructor))),span)})))));
__jakt_var_422 = (constructor.value()); goto __jakt_label_398;

}
__jakt_label_398:; __jakt_var_422.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_424; {
types::CheckedEnum const subject_enum = ((((*this).program))->get_enum(enum_id));
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY(ByteString::from_utf8("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),TRY(ByteString::from_utf8("Record"sv)),JaktInternal::OptionalNone())))).value());
ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_value_enum = ((((subject_enum).underlying_type_id)).equals(types::unknown_type_id()));
ids::FunctionId const record_type_struct_constructor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::FunctionId,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_value_enum);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),TRY(ByteString::from_utf8("ValueEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
else {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),TRY(ByteString::from_utf8("SumEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::Value const methods = TRY((((*this).reflect_methods(((subject_enum).scope_id),span,scope))));
ids::TypeId const tuple_type = TRY((((*this).tuple_type((TRY((DynamicArray<ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)}))))))));
types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<types::Value>> __jakt_var_425; {
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<types::Value> result = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((subject_enum).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Unknown kind of generic parameter in struct definition"sv)));
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
ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId,ErrorOr<types::Value>>{
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Unknown()));
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
TRY((((result).push(TRY((((*this).tuple_value((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))})))),tuple_type,span))))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

__jakt_var_425 = result; goto __jakt_label_401;

}
__jakt_label_401:; __jakt_var_425.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<types::Value>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<types::Value> record_type_fields = (TRY((DynamicArray<types::Value>::create_with({}))));
if (is_value_enum){
TRY((((*this).error(TRY(ByteString::from_utf8("Unimplemented reflected type: value enum"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
else {
(record_type_fields = TRY((((*this).reflect_sum_enum_variants(subject_enum,span,scope)))));
}

ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = (TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(((subject_enum).name),span)))), methods, generic_parameters, types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).bool_value(((subject_enum).is_boxed),span)))), types::Value(TRY((types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))))),span)})))),record_type_enum_id,record_type_struct_constructor))),span)})))),record_struct_id,record_struct_constructor))),span)})))));
__jakt_var_424 = (constructor.value()); goto __jakt_label_400;

}
__jakt_label_400:; __jakt_var_424.release_value(); }));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_426; {
types::CheckedEnum const subject_enum = ((((*this).program))->get_enum(enum_id));
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY(ByteString::from_utf8("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),TRY(ByteString::from_utf8("Record"sv)),JaktInternal::OptionalNone())))).value());
ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_value_enum = ((((subject_enum).underlying_type_id)).equals(types::unknown_type_id()));
ids::FunctionId const record_type_struct_constructor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::FunctionId,ErrorOr<types::Value>>{
auto __jakt_enum_value = (is_value_enum);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),TRY(ByteString::from_utf8("ValueEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
else {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),TRY(ByteString::from_utf8("SumEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::Value const methods = TRY((((*this).reflect_methods(((subject_enum).scope_id),span,scope))));
ids::TypeId const tuple_type = TRY((((*this).tuple_type((TRY((DynamicArray<ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)}))))))));
types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::Value>, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<types::Value>> __jakt_var_427; {
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<types::Value> result = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((subject_enum).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Unknown kind of generic parameter in struct definition"sv)));
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
ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId,ErrorOr<types::Value>>{
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Unknown()));
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
TRY((((result).push(TRY((((*this).tuple_value((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))})))),tuple_type,span))))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

__jakt_var_427 = result; goto __jakt_label_403;

}
__jakt_label_403:; __jakt_var_427.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<types::Value>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<types::Value> record_type_fields = (TRY((DynamicArray<types::Value>::create_with({}))));
if (is_value_enum){
TRY((((*this).error(TRY(ByteString::from_utf8("Unimplemented reflected type: value enum"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
}
else {
(record_type_fields = TRY((((*this).reflect_sum_enum_variants(subject_enum,span,scope)))));
}

ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::StructId, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(ByteString::from_utf8("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = (TRY((DynamicArray<types::Value>::create_with({types::Value(TRY((types::ValueImpl::Struct((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).string_value(((subject_enum).name),span)))), methods, generic_parameters, types::Value(TRY((types::ValueImpl::Enum((TRY((DynamicArray<types::Value>::create_with({TRY((((*this).bool_value(((subject_enum).is_boxed),span)))), types::Value(TRY((types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))))),span)})))),record_type_enum_id,record_type_struct_constructor))),span)})))),record_struct_id,record_struct_constructor))),span)})))));
__jakt_var_426 = (constructor.value()); goto __jakt_label_402;

}
__jakt_label_402:; __jakt_var_426.release_value(); }));
};/*case end*/
case 30 /* Function */: {
return JaktInternal::ExplicitValue(({ Optional<ids::FunctionId> __jakt_var_428; {
JaktInternal::Optional<ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),TRY(ByteString::from_utf8("Function"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error(TRY(ByteString::from_utf8("Attempted to access a variant that does not exist"sv)),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Invalid type"sv)));
}
(fields = (TRY((DynamicArray<types::Value>::create_with({})))));
__jakt_var_428 = (constructor.value()); goto __jakt_label_404;

}
__jakt_label_404:; __jakt_var_428.release_value(); }));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type reflection not implemented: {}"sv)),type))),span))));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not yet implemented"sv)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((result).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value>& x = __jakt_match_value.fields;
ids::FunctionId& constructor = __jakt_match_value.constructor;
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

ErrorOr<ByteString> interpreter::ExecutionResult::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Return */: {
TRY(builder.append("ExecutionResult::Return"sv));
[[maybe_unused]] auto const& that = this->as.Return;
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Throw */: {
TRY(builder.append("ExecutionResult::Throw"sv));
[[maybe_unused]] auto const& that = this->as.Throw;
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
[[nodiscard]] ExecutionResult ExecutionResult::Return(types::Value value){
ExecutionResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Return.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ExecutionResult ExecutionResult::Throw(types::Value value){
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
ExecutionResult::~ExecutionResult(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void ExecutionResult::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Return */:this->as.Return.value.~Value();
break;
case 1 /* Throw */:this->as.Throw.value.~Value();
break;
}
}
ErrorOr<ByteString> interpreter::Deferred::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Expression */: {
TRY(builder.append("Deferred::Expression"sv));
[[maybe_unused]] auto const& that = this->as.Expression;
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Statement */: {
TRY(builder.append("Deferred::Statement"sv));
[[maybe_unused]] auto const& that = this->as.Statement;
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
[[nodiscard]] Deferred Deferred::Expression(NonnullRefPtr<typename types::CheckedExpression> value){
Deferred __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Expression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Deferred Deferred::Statement(NonnullRefPtr<typename types::CheckedStatement> value){
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
Deferred::~Deferred(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void Deferred::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Expression */:this->as.Expression.value.~NonnullRefPtr();
break;
case 1 /* Statement */:this->as.Statement.value.~NonnullRefPtr();
break;
}
}
ErrorOr<ByteString> interpreter::StatementResult::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Return */: {
TRY(builder.append("StatementResult::Return"sv));
[[maybe_unused]] auto const& that = this->as.Return;
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Throw */: {
TRY(builder.append("StatementResult::Throw"sv));
[[maybe_unused]] auto const& that = this->as.Throw;
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* Yield */: {
TRY(builder.append("StatementResult::Yield"sv));
[[maybe_unused]] auto const& that = this->as.Yield;
TRY(builder.appendff("({})", that.value));
break;}
case 3 /* Continue */: {
return ByteString("StatementResult::Continue"sv);
break;}
case 4 /* Break */: {
return ByteString("StatementResult::Break"sv);
break;}
case 5 /* JustValue */: {
TRY(builder.append("StatementResult::JustValue"sv));
[[maybe_unused]] auto const& that = this->as.JustValue;
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
[[nodiscard]] StatementResult StatementResult::Return(types::Value value){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Return.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::Throw(types::Value value){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Throw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::Yield(types::Value value){
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
[[nodiscard]] StatementResult StatementResult::JustValue(types::Value value){
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
StatementResult::~StatementResult(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
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
