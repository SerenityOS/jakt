#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace utility {
struct FileId {
  public:
size_t id;bool equals(const utility::FileId rhs) const;
FileId(size_t a_id);

ErrorOr<String> debug_description() const;
};struct Span {
  public:
utility::FileId file_id;size_t start;size_t end;bool contains(const utility::Span span) const;
bool is_in_offset_range(const size_t start, const size_t end) const;
Span(utility::FileId a_file_id, size_t a_start, size_t a_end);

ErrorOr<String> debug_description() const;
};struct ArgsParser {
  public:
JaktInternal::Array<String> args;JaktInternal::Array<size_t> removed_indices;JaktInternal::Array<String> definitely_positional_args;static ErrorOr<utility::ArgsParser> from_args(const JaktInternal::Array<String> args);
ErrorOr<JaktInternal::Array<String>> option_multiple(const JaktInternal::Array<String> names);
ErrorOr<bool> flag(const JaktInternal::Array<String> names);
ArgsParser(JaktInternal::Array<String> a_args, JaktInternal::Array<size_t> a_removed_indices, JaktInternal::Array<String> a_definitely_positional_args);

ErrorOr<JaktInternal::Array<String>> remaining_arguments() const;
ErrorOr<JaktInternal::Optional<String>> option(const JaktInternal::Array<String> names);
ErrorOr<String> debug_description() const;
};template <typename T>
ErrorOr<void> extend_array(JaktInternal::Array<T> target,const JaktInternal::Array<T> extend_with) {
{
TRY((((target).add_capacity(((extend_with).size())))));
{
JaktInternal::ArrayIterator<T> _magic = ((extend_with).iterator());
for (;;){
JaktInternal::Optional<T> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
T v = (_magic_value.value());
{
TRY((((target).push(v))));
}

}
}

}
return {};
}

template <typename T>
T* null() {
{
{
return nullptr;
}

abort();
}
}

template <typename T>
T* allocate(const size_t count) {
{
{
return static_cast<T*>(malloc(count * sizeof(T)));
}

abort();
}
}

}
template<>struct Formatter<utility::FileId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, utility::FileId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<utility::Span> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, utility::Span const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<utility::ArgsParser> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, utility::ArgsParser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
