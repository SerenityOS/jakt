#include "main.h"
#include "main.h"
#include "platform__unknown_compiler.h"
#include "repl.h"
#include "repl_backend__default.h"
#include "repl_backend__common.h"
#include "jakt__libc__io.h"
#include "platform.h"
#include "jakt__prelude__configuration.h"
#include "project.h"
#include "ide.h"
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
#include "build.h"
#include "jakt__platform__unknown_process.h"
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

/* specialisation 0 of function value_or_throw: ["u32"] */
template<> ErrorOr<u32> value_or_throw<u32>(JaktInternal::Optional<u32> const maybe);
template<>
ErrorOr<u32> value_or_throw<u32>(JaktInternal::Optional<u32> const maybe) {
{
if (((maybe).has_value())){
return ((maybe.value()));
}
return Error::from_errno(static_cast<i32>(1));
}
}
} // namespace Jakt
