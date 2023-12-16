#include "repl_backend__default.h"
namespace Jakt {
namespace repl_backend__default {
ErrorOr<ByteString> repl_backend__default::Editor::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("Editor("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("standard_input_file: {}, ", standard_input_file));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("line_pointer: {}, ", line_pointer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("prompt: \"{}\"", prompt));
}
TRY(builder.append(")"sv));return builder.to_string(); }
void repl_backend__default::Editor::destroy() {
{
fclose(((*this).standard_input_file));
{
free(line_pointer);
}

}
}

ErrorOr<repl_backend__default::Editor> repl_backend__default::Editor::create(ByteString const prompt,Function<ErrorOr<void>(repl_backend__default::Editor&)> const& syntax_highlight_handler) {
{
FILE* std_in = fopen(((TRY(ByteString::from_utf8("/dev/stdin"sv))).characters()),((TRY(ByteString::from_utf8("r"sv))).characters()));
if ((std_in == jakt__platform__utility::null<FILE*>())){
warnln((StringView::from_string_literal("Could not open /dev/stdin for reading"sv)));
return Error::from_errno(static_cast<i32>(42));
}
repl_backend__default::Editor const editor = repl_backend__default::Editor(std_in,jakt__platform__utility::allocate<char>(static_cast<size_t>(4096ULL)),prompt);
return editor;
}
}

ErrorOr<ByteString> repl_backend__default::Editor::get_active_buffer() {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("Active buffer not supported"sv)));
}
}

repl_backend__default::Editor::Editor(FILE* a_standard_input_file, char* a_line_pointer, ByteString a_prompt): standard_input_file(move(a_standard_input_file)), line_pointer(move(a_line_pointer)), prompt(move(a_prompt)){}

ErrorOr<repl_backend__common::LineResult> repl_backend__default::Editor::get_line(JaktInternal::Optional<ByteString> const prompt) {
{
warn((StringView::from_string_literal("{}"sv)),prompt.value_or_lazy_evaluated([&] { return ((*this).prompt); }));
ByteStringBuilder builder = ByteStringBuilder::create();
{
char* const c_string = fgets(((*this).line_pointer),static_cast<size_t>(4096ULL),((*this).standard_input_file));
if ((c_string == jakt__platform__utility::null<char*>())){
return repl_backend__common::LineResult::Eof();
}
TRY((((builder).append_c_string(c_string))));
}

return repl_backend__common::LineResult::Line(TRY((((builder).to_string()))));
}
}

ErrorOr<void> repl_backend__default::Editor::highlight(utility::Span const span,repl_backend__common::Style const style) {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("Highlighting not supported"sv)));
}
return {};
}

}
} // namespace Jakt
