#include "formatter.h"
#include "main.h"
#include "jakt__platform__unknown_compiler.h"
#include "build.h"
#include "jakt__platform__unknown_process.h"
#include "ide.h"
#include "project.h"
#include "repl.h"
#include "jakt__libc__io.h"
#include "formatter.h"
#include "codegen.h"
#include "typechecker.h"
#include "interpreter.h"
#include "types.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__file_iterator.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform__unknown_path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
#include "jakt__prelude__prelude.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__iteration.h"
namespace Jakt {
namespace formatter {

/* specialisation 0 of function collapse: ["lexer::Token"] */
template<> JaktInternal::Optional<lexer::Token> collapse<lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<lexer::Token>> const x);
template<>
JaktInternal::Optional<lexer::Token> collapse<lexer::Token>(JaktInternal::Optional<JaktInternal::Optional<lexer::Token>> const x) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<lexer::Token>,JaktInternal::Optional<lexer::Token>>{
auto __jakt_enum_value = (((x).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((x.value()));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}()))
);
}
}
}
} // namespace Jakt
