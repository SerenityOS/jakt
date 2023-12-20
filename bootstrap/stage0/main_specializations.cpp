#include "main.h"
#include "main.h"
#include "platform__unknown_compiler.h"
#include "git.h"
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
#include "jakt__prelude__class_name.h"
#include "jakt__prelude__hash.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__iteration.h"
#include "jakt__prelude__static_array.h"
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
