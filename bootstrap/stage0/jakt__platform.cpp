#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "jakt__platform.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace jakt__platform {
ErrorOr<JaktInternal::DynamicArray<ByteString>> platform_import_names() {
{
Jakt::jakt__platform::Target const target = TRY((Jakt::jakt__platform::Target::active()));
{auto __jakt_enum_value = target.os;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("windows"sv)) {{auto __jakt_enum_value = target.arch;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86_64"sv)) {return DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("win64"sv), ByteString::from_utf8_without_validation("windows"sv)});}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("i686"sv)) {return DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("win32"sv), ByteString::from_utf8_without_validation("windows"sv)});}else {return DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("windows"sv)});}}}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("darwin"sv)) {return DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("darwin"sv), ByteString::from_utf8_without_validation("posix"sv)});}else if ((__jakt_enum_value == ByteString::from_utf8_without_validation("linux"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("openbsd"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("serenityos"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("serenity"sv))) {return DynamicArray<ByteString>::create_with({target.os, ByteString::from_utf8_without_validation("posix"sv)});}else {return DynamicArray<ByteString>::create_with({target.os, ByteString::from_utf8_without_validation("unknown"sv)});}}
}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> add_to_each(JaktInternal::DynamicArray<ByteString> const strings,ByteString const prefix,ByteString const suffix) {
{
JaktInternal::DynamicArray<ByteString> output = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = strings.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString str = _magic_value.value();
{
output.push((prefix + str) + suffix);
}

}
}

return output;
}
}

JaktInternal::Optional<size_t> last_namespace_separator(ByteString const name) {
{
size_t i = JaktInternal::checked_sub(name.length(),static_cast<size_t>(1ULL));
while (i >= static_cast<size_t>(2ULL)){
if ((name.byte_at(i) == static_cast<u8>(u8':')) && (name.byte_at(JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))) == static_cast<u8>(u8':'))){
return JaktInternal::checked_add(i,static_cast<size_t>(1ULL));
}
i--;
}
return JaktInternal::OptionalNone();
}
}

ByteString Jakt::jakt__platform::Target::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Target("sv);{
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
ErrorOr<Jakt::jakt__platform::Target> Jakt::jakt__platform::Target::from_triple(ByteString const triple) {
{
JaktInternal::DynamicArray<ByteString> const parts = triple.split('-');
if (parts.size() != static_cast<size_t>(4ULL)){
warnln(StringView::from_string_literal("Invalid target triple '{}'"sv),triple);
return Error::from_errno(static_cast<i32>(22));
}
return Jakt::jakt__platform::Target(parts[static_cast<i64>(0LL)],parts[static_cast<i64>(1LL)],parts[static_cast<i64>(2LL)],parts[static_cast<i64>(3LL)]);
}
}

ErrorOr<Jakt::jakt__platform::Target> Jakt::jakt__platform::Target::active() {
{
ByteString const triple = TRY((Jakt::jakt__compiler::target_triple_string()));
return Jakt::jakt__platform::Target::from_triple(triple);
}
}

ErrorOr<ByteString> Jakt::jakt__platform::Target::name(bool const abbreviate) const {
{
{auto __jakt_enum_value = abbreviate;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("{}-{}-{}"sv),this->arch,this->platform,this->os);}else if (!__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("{}-{}-{}-{}"sv),this->arch,this->platform,this->os,this->abi);}VERIFY_NOT_REACHED();
}
}
}

Jakt::jakt__platform::Target::Target(ByteString a_arch, ByteString a_platform, ByteString a_os, ByteString a_abi): arch(move(a_arch)), platform(move(a_platform)), os(move(a_os)), abi(move(a_abi)){}

ErrorOr<size_t> Jakt::jakt__platform::Target::size_t_size() const {
{
{auto __jakt_enum_value = this->arch;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86_64"sv)) {return static_cast<size_t>(8ULL);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86"sv)) {return static_cast<size_t>(4ULL);}else {{
return Error::__jakt_from_string_literal(StringView::from_string_literal("size_t size is unknown for this architecture"sv));
}
}}
}
}

ErrorOr<size_t> Jakt::jakt__platform::Target::pointer_size() const {
{
{auto __jakt_enum_value = this->arch;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86_64"sv)) {return static_cast<size_t>(8ULL);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86"sv)) {return static_cast<size_t>(4ULL);}else {{
return Error::__jakt_from_string_literal(StringView::from_string_literal("pointer size is unknown for this architecture"sv));
}
}}
}
}

ErrorOr<size_t> Jakt::jakt__platform::Target::int_size() const {
{
{auto __jakt_enum_value = this->arch;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86_64"sv)) {return static_cast<size_t>(4ULL);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("x86"sv)) {return static_cast<size_t>(4ULL);}else {{
return Error::__jakt_from_string_literal(StringView::from_string_literal("int size is unknown for this architecture"sv));
}
}}
}
}

ErrorOr<size_t> Jakt::jakt__platform::Target::size_t_alignment() const {
{
return this->size_t_size();
}
}

ErrorOr<size_t> Jakt::jakt__platform::Target::pointer_alignment() const {
{
return this->pointer_size();
}
}

ErrorOr<size_t> Jakt::jakt__platform::Target::int_alignment() const {
{
return this->int_size();
}
}

}
} // namespace Jakt
