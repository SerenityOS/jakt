#include "main.h"
namespace Jakt {

/* specialisation 0 of function value_or_throw: ["u32"] */
template<> ErrorOr<u32> value_or_throw<u32>(JaktInternal::Optional<u32> const maybe);
template<>
ErrorOr<u32> value_or_throw<u32>(JaktInternal::Optional<u32> const maybe) {
{
if (((maybe).has_value())){
return (maybe.value());
}
return Error::__jakt_from_string_literal((StringView::from_string_literal("Expected value but found none"sv)));
}
}
} // namespace Jakt
