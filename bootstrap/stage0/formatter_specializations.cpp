#include "formatter.h"
namespace Jakt {
namespace formatter {

/* specialisation 0 of function collapse: ["Jakt::lexer::Token"] */
template<> JaktInternal::Optional<Jakt::lexer::Token> collapse<Jakt::lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<Jakt::lexer::Token>> const x);
template<>
JaktInternal::Optional<Jakt::lexer::Token> collapse<Jakt::lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<Jakt::lexer::Token>> const x) {
{
{auto __jakt_enum_value = x.has_value();
if (__jakt_enum_value) {return x.value();}else if (!__jakt_enum_value) {return JaktInternal::OptionalNone();}VERIFY_NOT_REACHED();
}
}
}
}
} // namespace Jakt
