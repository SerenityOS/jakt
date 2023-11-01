#include "formatter.h"
#include "main.h"
#include "platform__unknown_compiler.h"
#include "repl.h"
#include "repl_backend__default.h"
#include "repl_backend__common.h"
#include "jakt__libc__io.h"
#include "platform.h"
#include "project.h"
#include "ide.h"
#include "formatter.h"
#include "codegen.h"
#include "typechecker.h"
#include "cpp_import__none.h"
#include "cpp_import__common.h"
#include "jakt__prelude__configuration.h"
#include "interpreter.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__platform__utility.h"
#include "build.h"
#include "jakt__platform__unknown_process.h"
#include "jakt__file_iterator.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform__unknown_path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
#include "jakt__prelude__prelude.h"
#include "jakt__prelude__hash.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__iteration.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace formatter {

/* specialisation 0 of function collapse: ["lexer::Token"] */
template<> JaktInternal::Optional<lexer::Token> collapse<lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<lexer::Token>> const x);
template<>
JaktInternal::Optional<lexer::Token> collapse<lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<lexer::Token>> const x) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<lexer::Token>,JaktInternal::Optional<lexer::Token>>{
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
