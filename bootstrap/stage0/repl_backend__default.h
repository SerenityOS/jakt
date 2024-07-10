#pragma once
#include <lib.h>
#include "repl_backend__common.h"
#include "jakt__libc__io.h"
#include "utility.h"
#include "jakt__platform__utility.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace repl_backend__default {
struct Editor;
}
namespace repl_backend__default {
struct Editor {
  public:
public: FILE* standard_input_file;public: char* line_pointer;public: ByteString prompt;public: static ErrorOr<Jakt::repl_backend__default::Editor> create(ByteString const prompt, Function<ErrorOr<void>(Jakt::repl_backend__default::Editor&)> const& syntax_highlight_handler);
public: ErrorOr<Jakt::repl_backend__common::LineResult> get_line(JaktInternal::Optional<ByteString> const prompt);
public: ErrorOr<ByteString> get_active_buffer();
public: ErrorOr<void> highlight(Jakt::utility::Span const span, Jakt::repl_backend__common::Style const style);
public: void destroy();
public: Editor(FILE* a_standard_input_file, char* a_line_pointer, ByteString a_prompt);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__default::Editor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__default::Editor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
