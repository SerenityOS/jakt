#include "formatter.h"
#include "formatter.h"
#include "lexer.h"
#include "compiler.h"
namespace Jakt {
namespace formatter {

/* specialisation 0 of function collapse: ["lexer::Token"] */
template<> JaktInternal::Optional<lexer::Token> collapse<lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<lexer::Token>> const x);
template<>
JaktInternal::Optional<lexer::Token> collapse<lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<lexer::Token>> const x) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<lexer::Token>,JaktInternal::Optional<lexer::Token>> {
auto __jakt_enum_value = (((x).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((x.value()));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
}
} // namespace Jakt
