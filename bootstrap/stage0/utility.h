#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace utility {
struct FileId {
  public:
size_t id;bool equals(utility::FileId const rhs) const;
FileId(size_t a_id);

ErrorOr<String> debug_description() const;
};struct Span {
  public:
utility::FileId file_id;size_t start;size_t end;bool contains(utility::Span const span) const;
bool is_in_offset_range(size_t const start, size_t const end) const;
Span(utility::FileId a_file_id, size_t a_start, size_t a_end);

ErrorOr<String> debug_description() const;
};template <typename T>
ErrorOr<void> extend_array(JaktInternal::Array<T> target,JaktInternal::Array<T> const extend_with) {
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
T* allocate(size_t const count) {
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
} // namespace Jakt
