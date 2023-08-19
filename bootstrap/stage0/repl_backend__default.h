#pragma once
#include "__unified_forward.h"
#include "utility.h"
#include "jakt__libc__io.h"
#include "repl_backend__common.h"
namespace Jakt {
namespace repl_backend__default {
struct Editor {
  public:
public: FILE* standard_input_file;public: char* line_pointer;public: DeprecatedString prompt;public: void destroy();
public: static ErrorOr<repl_backend__default::Editor> create(DeprecatedString const prompt, Function<ErrorOr<void>(repl_backend__default::Editor&)> const& syntax_highlight_handler);
public: ErrorOr<DeprecatedString> get_active_buffer();
public: Editor(FILE* a_standard_input_file, char* a_line_pointer, DeprecatedString a_prompt);

public: ErrorOr<repl_backend__common::LineResult> get_line(JaktInternal::Optional<DeprecatedString> const prompt);
public: ErrorOr<void> highlight(utility::Span const span, repl_backend__common::Style const style);
public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__default::Editor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__default::Editor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
