#include "jakt__platform__utility.h"
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
namespace jakt__platform__utility {

/* specialisation 0 of function null: ["FILE*"] */
template<> FILE* null<FILE*>();

/* specialisation 1 of function null: ["char*"] */
template<> char* null<char*>();

/* specialisation 0 of function allocate: ["char"] */
template<> char* allocate<char>(size_t const count);
template<>
FILE* null<FILE*>() {
{
Function<FILE*()> const make_null = []() -> FILE* {{
bool const dep = true;
{
return nullptr;
}

abort();
}
}
;
return make_null();
}
}
template<>
char* null<char*>() {
{
Function<char*()> const make_null = []() -> char* {{
bool const dep = true;
{
return nullptr;
}

abort();
}
}
;
return make_null();
}
}
template<>
char* allocate<char>(size_t const count) {
{
Function<void(char*&)> const alloc_impl = [count](char*& ptr) -> void {{
{
ptr = static_cast<RemoveReference<decltype(ptr)>>(calloc(count, sizeof(*ptr)));
}

}
}
;
char* ptr = jakt__platform__utility::null<char*>();
alloc_impl(((ptr)));
return ptr;
}
}
}
} // namespace Jakt
