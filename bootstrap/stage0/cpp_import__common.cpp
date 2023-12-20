#include "cpp_import__common.h"
namespace Jakt {
namespace cpp_import__common {
ErrorOr<ByteString> read_all(ByteString const filename) {
{
NonnullRefPtr<File> file = TRY((File::open_for_reading(filename)));
JaktInternal::DynamicArray<u8> const buf = TRY((((file)->read_all())));
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<u8> _magic = ((buf).iterator());
for (;;){
JaktInternal::Optional<u8> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 b = (_magic_value.value());
{
((builder).append(b));
}

}
}

return ((builder).to_string());
}
}

ByteString cpp_import__common::CppImportErrors::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CppImportErrors("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
builder.append(")"sv);return builder.to_string(); }
StringView cpp_import__common::CppImportErrors::path_not_found() {
{
return (StringView::from_string_literal("Could not find import path"sv));
}
}

StringView cpp_import__common::CppImportErrors::no_this_type() {
{
return (StringView::from_string_literal("No 'this' type when compiling a function"sv));
}
}

cpp_import__common::CppImportErrors::CppImportErrors(){}

}
} // namespace Jakt
