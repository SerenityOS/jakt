#include "jakt__platform.h"
namespace Jakt {
namespace jakt__platform {
ErrorOr<JaktInternal::DynamicArray<ByteString>> platform_import_names() {
{
jakt__platform::Target const target = TRY((jakt__platform::Target::active()));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ByteString>,ErrorOr<JaktInternal::DynamicArray<ByteString>>>{
auto __jakt_enum_value = (((target).os));
if (__jakt_enum_value == (ByteString::must_from_utf8("windows"sv))) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ByteString>,ErrorOr<JaktInternal::DynamicArray<ByteString>>>{
auto __jakt_enum_value = (((target).arch));
if (__jakt_enum_value == (ByteString::must_from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({(ByteString::must_from_utf8("win64"sv)), (ByteString::must_from_utf8("windows"sv))})));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("i686"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({(ByteString::must_from_utf8("win32"sv)), (ByteString::must_from_utf8("windows"sv))})));
}
else {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({(ByteString::must_from_utf8("windows"sv))})));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("darwin"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({(ByteString::must_from_utf8("darwin"sv)), (ByteString::must_from_utf8("posix"sv))})));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("linux"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({((target).os), (ByteString::must_from_utf8("posix"sv))})));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("openbsd"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({((target).os), (ByteString::must_from_utf8("posix"sv))})));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("serenityos"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({((target).os), (ByteString::must_from_utf8("posix"sv))})));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("serenity"sv))) {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({((target).os), (ByteString::must_from_utf8("posix"sv))})));
}
else {
return JaktInternal::ExplicitValue((DynamicArray<ByteString>::create_with({((target).os), (ByteString::must_from_utf8("unknown"sv))})));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> add_to_each(JaktInternal::DynamicArray<ByteString> const strings,ByteString const prefix,ByteString const suffix) {
{
JaktInternal::DynamicArray<ByteString> output = (DynamicArray<ByteString>::create_with({}));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString str = (_magic_value.value());
{
((output).push(((((prefix) + (str))) + (suffix))));
}

}
}

return output;
}
}

JaktInternal::Optional<size_t> last_namespace_separator(ByteString const name) {
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

ErrorOr<ByteString> jakt__platform::Target::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Target("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arch: \"{}\", ", arch);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("platform: \"{}\", ", platform);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("os: \"{}\", ", os);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("abi: \"{}\"", abi);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<jakt__platform::Target> jakt__platform::Target::from_triple(ByteString const triple) {
{
JaktInternal::DynamicArray<ByteString> const parts = ((triple).split('-'));
if (((((parts).size())) != (static_cast<size_t>(4ULL)))){
warnln((StringView::from_string_literal("Invalid target triple '{}'"sv)),triple);
return Error::from_errno(static_cast<i32>(22));
}
return jakt__platform::Target(((parts)[static_cast<i64>(0LL)]),((parts)[static_cast<i64>(1LL)]),((parts)[static_cast<i64>(2LL)]),((parts)[static_cast<i64>(3LL)]));
}
}

ErrorOr<jakt__platform::Target> jakt__platform::Target::active() {
{
ByteString const triple = TRY((___jakt_get_target_triple_string()));
return TRY((jakt__platform::Target::from_triple(triple)));
}
}

ErrorOr<ByteString> jakt__platform::Target::name(bool const abbreviate) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (abbreviate);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}-{}-{}"sv)),((*this).arch),((*this).platform),((*this).os)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}-{}-{}-{}"sv)),((*this).arch),((*this).platform),((*this).os),((*this).abi)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

jakt__platform::Target::Target(ByteString a_arch, ByteString a_platform, ByteString a_os, ByteString a_abi): arch(move(a_arch)), platform(move(a_platform)), os(move(a_os)), abi(move(a_abi)){}

ErrorOr<size_t> jakt__platform::Target::size_t_size() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((*this).arch));
if (__jakt_enum_value == (ByteString::must_from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("x86"sv))) {
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

ErrorOr<size_t> jakt__platform::Target::pointer_size() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((*this).arch));
if (__jakt_enum_value == (ByteString::must_from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("x86"sv))) {
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

ErrorOr<size_t> jakt__platform::Target::int_size() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (((*this).arch));
if (__jakt_enum_value == (ByteString::must_from_utf8("x86_64"sv))) {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
}
else if (__jakt_enum_value == (ByteString::must_from_utf8("x86"sv))) {
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

ErrorOr<size_t> jakt__platform::Target::size_t_alignment() const {
{
return TRY((((*this).size_t_size())));
}
}

ErrorOr<size_t> jakt__platform::Target::pointer_alignment() const {
{
return TRY((((*this).pointer_size())));
}
}

ErrorOr<size_t> jakt__platform::Target::int_alignment() const {
{
return TRY((((*this).int_size())));
}
}

}
} // namespace Jakt
