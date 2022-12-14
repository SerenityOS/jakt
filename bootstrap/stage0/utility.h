#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace utility {
struct FileId {
  public:
size_t id;bool equals(utility::FileId const rhs) const;
FileId(size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct Span {
  public:
utility::FileId file_id;size_t start;size_t end;bool contains(utility::Span const span) const;
bool is_in_offset_range(size_t const start, size_t const end) const;
Span(utility::FileId a_file_id, size_t a_start, size_t a_end);

ErrorOr<DeprecatedString> debug_description() const;
};template <typename T>
ErrorOr<JaktInternal::DynamicArray<T>> add_arrays(JaktInternal::DynamicArray<T> const a,JaktInternal::DynamicArray<T> const b) {
{
JaktInternal::DynamicArray<T> result = (TRY((DynamicArray<T>::create_with({}))));
{
JaktInternal::ArrayIterator<T> _magic = ((a).iterator());
for (;;){
JaktInternal::Optional<T> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
T x = (_magic_value.value());
{
TRY((((result).push(x))));
}

}
}

{
JaktInternal::ArrayIterator<T> _magic = ((b).iterator());
for (;;){
JaktInternal::Optional<T> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
T x = (_magic_value.value());
{
TRY((((result).push(x))));
}

}
}

return (result);
}
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
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::utility::FileId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::utility::FileId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::utility::Span> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::utility::Span const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
namespace Jakt {
} // namespace Jakt
