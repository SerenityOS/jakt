#include "platform.h"
namespace Jakt {
namespace platform {
ErrorOr<DeprecatedString> library_name_for_target(DeprecatedString const name,jakt__platform::Target const target) {
{
DeprecatedString const target_name = TRY((((target).name(false))));
return TRY((__jakt_format((StringView::from_string_literal("{}/{}"sv)),target_name,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (((target).os));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("windows"sv))) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("jakt_{}_{}.lib"sv)),name,target_name))));
}
else {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("libjakt_{}_{}.a"sv)),name,target_name))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
}

}
} // namespace Jakt
