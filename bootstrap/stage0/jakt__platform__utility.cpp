#include "jakt__platform__utility.h"
namespace Jakt {
namespace jakt__platform__utility {
ErrorOr<ByteString> join(JaktInternal::DynamicArray<ByteString> const strings,ByteString const separator) {
{
ByteString output = (ByteString::from_utf8_without_validation(""sv));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ByteString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString s = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,s);
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,JaktInternal::checked_sub(((strings).size()),static_cast<size_t>(1ULL)))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,separator);
}
((i++));
}

}
}

return output;
}
}

}
} // namespace Jakt
