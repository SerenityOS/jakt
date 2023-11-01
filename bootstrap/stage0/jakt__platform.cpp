#include "jakt__platform.h"
namespace Jakt {
namespace jakt__platform {
JaktInternal::Optional<size_t> last_namespace_separator(DeprecatedString const name) {
{
size_t i = JaktInternal::checked_sub(((name).length()),static_cast<size_t>(1ULL));
while ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(i,static_cast<size_t>(2ULL))){
if ((((((name).byte_at(i))) == (static_cast<u8>(u8':'))) && ((((name).byte_at(JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))))) == (static_cast<u8>(u8':'))))){
return JaktInternal::checked_add(i,static_cast<size_t>(1ULL));
}
((i--));
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> add_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings,DeprecatedString const prefix,DeprecatedString const suffix) {
{
JaktInternal::DynamicArray<DeprecatedString> output = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString str = (_magic_value.value());
{
TRY((((output).push(TRY((((TRY((((prefix) + (str))))) + (suffix))))))));
}

}
}

return output;
}
}

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> platform_import_names() {
{
jakt__platform::Target const target = TRY((jakt__platform::Target::active()));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<DeprecatedString>,ErrorOr<JaktInternal::DynamicArray<DeprecatedString>>>{
auto __jakt_enum_value = (((target).os));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("windows"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<DeprecatedString>,ErrorOr<JaktInternal::DynamicArray<DeprecatedString>>>{
auto __jakt_enum_value = (((target).arch));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("win64"sv)), TRY(DeprecatedString::from_utf8("windows"sv))})))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("i686"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("win32"sv)), TRY(DeprecatedString::from_utf8("windows"sv))})))));
}
else {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("windows"sv))})))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("darwin"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("darwin"sv)), TRY(DeprecatedString::from_utf8("posix"sv))})))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("linux"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), TRY(DeprecatedString::from_utf8("posix"sv))})))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("openbsd"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), TRY(DeprecatedString::from_utf8("posix"sv))})))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("serenityos"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), TRY(DeprecatedString::from_utf8("posix"sv))})))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("serenity"sv))) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), TRY(DeprecatedString::from_utf8("posix"sv))})))));
}
else {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), TRY(DeprecatedString::from_utf8("unknown"sv))})))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> jakt__platform::Target::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Target("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("arch: \"{}\", ", arch));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("platform: \"{}\", ", platform));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("os: \"{}\", ", os));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("abi: \"{}\"", abi));
}
TRY(builder.append(")"sv));return builder.to_string(); }
jakt__platform::Target::Target(DeprecatedString a_arch, DeprecatedString a_platform, DeprecatedString a_os, DeprecatedString a_abi): arch(move(a_arch)), platform(move(a_platform)), os(move(a_os)), abi(move(a_abi)){}

ErrorOr<jakt__platform::Target> jakt__platform::Target::from_triple(DeprecatedString const triple) {
{
JaktInternal::DynamicArray<DeprecatedString> const parts = ((triple).split('-'));
if (((((parts).size())) != (static_cast<size_t>(4ULL)))){
warnln((StringView::from_string_literal("Invalid target triple '{}'"sv)),triple);
return Error::from_errno(static_cast<i32>(22));
}
return jakt__platform::Target(((parts)[static_cast<i64>(0LL)]),((parts)[static_cast<i64>(1LL)]),((parts)[static_cast<i64>(2LL)]),((parts)[static_cast<i64>(3LL)]));
}
}

ErrorOr<size_t> jakt__platform::Target::int_alignment() const {
{
return TRY((((*this).int_size())));
}
}

ErrorOr<size_t> jakt__platform::Target::pointer_size() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((*this).arch));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
}
else {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("pointer size is unknown for this architecture"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> jakt__platform::Target::name(bool const abbreviate) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (abbreviate);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}-{}-{}"sv)),((*this).arch),((*this).platform),((*this).os)))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}-{}-{}-{}"sv)),((*this).arch),((*this).platform),((*this).os),((*this).abi)))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<jakt__platform::Target> jakt__platform::Target::active() {
{
DeprecatedString const triple = TRY((___jakt_get_target_triple_string()));
return TRY((jakt__platform::Target::from_triple(triple)));
}
}

ErrorOr<size_t> jakt__platform::Target::size_t_alignment() const {
{
return TRY((((*this).size_t_size())));
}
}

ErrorOr<size_t> jakt__platform::Target::size_t_size() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((*this).arch));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
}
else {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("size_t size is unknown for this architecture"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<size_t> jakt__platform::Target::int_size() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((*this).arch));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("x86"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
}
else {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("int size is unknown for this architecture"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<size_t> jakt__platform::Target::pointer_alignment() const {
{
return TRY((((*this).pointer_size())));
}
}

}
} // namespace Jakt
