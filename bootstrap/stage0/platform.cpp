#include "platform.h"
namespace Jakt {
namespace platform {
ErrorOr<ByteString> library_name_for_target(ByteString const name,jakt__platform::Target const target) {
{
ByteString const target_name = TRY((((target).name(false))));
return __jakt_format((StringView::from_string_literal("{}/{}"sv)),target_name,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((target).os));
if (__jakt_enum_value == (ByteString::from_utf8_without_validation("windows"sv))) {
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("jakt_{}_{}.lib"sv)),name,target_name));
}
else {
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("libjakt_{}_{}.a"sv)),name,target_name));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
}

}
} // namespace Jakt
