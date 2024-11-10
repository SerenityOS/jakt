#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "platform.h"
namespace Jakt {
namespace platform {
ErrorOr<ByteString> library_name_for_target(ByteString const name,Jakt::jakt__platform::Target const target) {
{
ByteString const target_name = TRY((target.name(false)));
return __jakt_format(StringView::from_string_literal("{}/{}"sv),target_name,[&]() -> ByteString { auto __jakt_enum_value = target.os;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("windows"sv)) {return __jakt_format(StringView::from_string_literal("jakt_{}_{}.lib"sv),name,target_name);}else {return __jakt_format(StringView::from_string_literal("libjakt_{}_{}.a"sv),name,target_name);} 
}());
}
}

}
} // namespace Jakt
