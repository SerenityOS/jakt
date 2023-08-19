#pragma once
#include "__unified_forward.h"
#include "jakt__prelude__prelude.h"
#include "jakt__libc__io.h"
#include "jakt__arguments.h"
#include "jakt__file_iterator.h"
#include "jakt__path.h"
#include "jakt__platform.h"
#include "build.h"
#include "compiler.h"
#include "codegen.h"
#include "error.h"
#include "formatter.h"
#include "ide.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include "platform.h"
#include "project.h"
#include "repl.h"
#include "typechecker.h"
#include "types.h"
#include "utility.h"
#include "jakt__platform__unknown_fs.h"
#include "platform__unknown_compiler.h"
namespace Jakt {
struct FormatRange {
  public:
public: size_t start;public: size_t end;public: FormatRange(size_t a_start, size_t a_end);

public: ErrorOr<DeprecatedString> debug_description() const;
};template <typename T>
ErrorOr<T> value_or_throw(JaktInternal::Optional<T> const maybe);
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::FormatRange> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::FormatRange const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
