#pragma once
#include "__unified_forward.h"
#include "jakt__prelude__prelude.h"
#include "jakt__libc__io.h"
#include "jakt__arguments.h"
#include "jakt__file_iterator.h"
#include "compiler.h"
#include "codegen.h"
#include "error.h"
#include "formatter.h"
#include "utility.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "typechecker.h"
#include "types.h"
#include "repl.h"
#include "project.h"
#include "ide.h"
#include "path.h"
#include "os.h"
#include "build.h"
#include "unknown_fs.h"
#include "unknown_compiler.h"
namespace Jakt {
struct FormatRange {
  public:
size_t start;size_t end;FormatRange(size_t a_start, size_t a_end);

ErrorOr<DeprecatedString> debug_description() const;
};template <typename T>
ErrorOr<T> value_or_throw(JaktInternal::Optional<T> const maybe) {
{
if (((maybe).has_value())){
return ((maybe.value()));
}
return Error::from_errno(static_cast<i32>(1));
}
}

} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::FormatRange> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::FormatRange const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
namespace Jakt {
} // namespace Jakt
