#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "jakt__file_iterator.h"
#include "jakt__prelude__operators.h"
namespace Jakt {
namespace jakt__file_iterator {
ByteString Jakt::jakt__file_iterator::RecursiveFileIterator::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("RecursiveFileIterator("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("extension: \"{}\", ", extension);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("directory_list: {}, ", directory_list);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_directory: {}", current_directory);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<NonnullRefPtr<Jakt::jakt__file_iterator::RecursiveFileIterator>> Jakt::jakt__file_iterator::RecursiveFileIterator::make(Jakt::jakt__path::Path const directory,ByteString const extension) {
{
return Jakt::jakt__file_iterator::RecursiveFileIterator::__jakt_create(extension,DynamicArray<Jakt::jakt__path::Path>::create_with({directory}),JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Optional<Jakt::jakt__path::Path>> Jakt::jakt__file_iterator::RecursiveFileIterator::next() {
{
if ((!(((((*this).current_directory)).has_value())))){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((*this).directory_list)).size()),static_cast<size_t>(0ULL))){
Jakt::jakt__path::Path const path = (((((*this).directory_list)).pop()).value());
(((*this).current_directory) = TRY((Jakt::jakt__platform__unknown_fs::DirectoryIterator::from_path(path))));
if ((!(((((*this).current_directory)).has_value())))){
return path;
}
}
else {
return JaktInternal::OptionalNone();
}

}
JaktInternal::Optional<JaktInternal::Tuple<Jakt::jakt__path::Path,bool>> const next = TRY(((((((*this).current_directory).value()))->next())));
if (((next).has_value())){
Jakt::jakt__path::Path new_path = ((TRY(((((((*this).current_directory).value()))->get_path())))).join((((((next.value())).template get<0>())).to_string())));
if ((((next.value())).template get<1>())){
((((*this).directory_list)).push(new_path));
return ((((*this).next())));
}
if (((((new_path).extension())) == (((*this).extension)))){
return new_path;
}
else {
return ((((*this).next())));
}

}
else if ((!(((((*this).directory_list)).is_empty())))){
(((*this).current_directory) = TRY((Jakt::jakt__platform__unknown_fs::DirectoryIterator::from_path((((((*this).directory_list)).pop()).value())))));
return ((((*this).next())));
}
return JaktInternal::OptionalNone();
}
}

Jakt::jakt__file_iterator::RecursiveFileIterator::RecursiveFileIterator(ByteString a_extension, JaktInternal::DynamicArray<Jakt::jakt__path::Path> a_directory_list, JaktInternal::Optional<NonnullRefPtr<Jakt::jakt__platform__unknown_fs::DirectoryIterator>> a_current_directory): extension(move(a_extension)), directory_list(move(a_directory_list)), current_directory(move(a_current_directory)){}
NonnullRefPtr<RecursiveFileIterator> Jakt::jakt__file_iterator::RecursiveFileIterator::__jakt_create(ByteString extension, JaktInternal::DynamicArray<Jakt::jakt__path::Path> directory_list, JaktInternal::Optional<NonnullRefPtr<Jakt::jakt__platform__unknown_fs::DirectoryIterator>> current_directory) { auto o = adopt_ref(*new RecursiveFileIterator (move(extension), move(directory_list), move(current_directory))); return o; }
}
} // namespace Jakt
