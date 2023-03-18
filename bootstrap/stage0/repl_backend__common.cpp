#include "repl_backend__common.h"
namespace Jakt {
namespace repl_backend__common {
ErrorOr<DeprecatedString> repl_backend__common::Style::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Style("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("foreground: {}, ", foreground));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("background: {}", background));
}
TRY(builder.append(")"sv));return builder.to_string(); }
repl_backend__common::Style::Style(JaktInternal::Optional<repl_backend__common::Color> a_foreground, JaktInternal::Optional<repl_backend__common::Color> a_background) :foreground(move(a_foreground)), background(move(a_background)){}

ErrorOr<DeprecatedString> repl_backend__common::LineResult::debug_description() const {
auto builder = TRY(DeprecatedStringBuilder::create());
switch (this->index()) {case 0 /* Line */: {
TRY(builder.append("LineResult::Line"sv));
[[maybe_unused]] auto const& that = this->template get<LineResult::Line>();
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 1 /* Eof */: {
return DeprecatedString("LineResult::Eof"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> repl_backend__common::XTermColor::debug_description() const {
auto builder = TRY(DeprecatedStringBuilder::create());
switch (this->index()) {case 0 /* Default */: {
return DeprecatedString("XTermColor::Default"sv);
break;}
case 1 /* Black */: {
return DeprecatedString("XTermColor::Black"sv);
break;}
case 2 /* Red */: {
return DeprecatedString("XTermColor::Red"sv);
break;}
case 3 /* Green */: {
return DeprecatedString("XTermColor::Green"sv);
break;}
case 4 /* Yellow */: {
return DeprecatedString("XTermColor::Yellow"sv);
break;}
case 5 /* Blue */: {
return DeprecatedString("XTermColor::Blue"sv);
break;}
case 6 /* Magenta */: {
return DeprecatedString("XTermColor::Magenta"sv);
break;}
case 7 /* Cyan */: {
return DeprecatedString("XTermColor::Cyan"sv);
break;}
case 8 /* White */: {
return DeprecatedString("XTermColor::White"sv);
break;}
case 9 /* Unchanged */: {
return DeprecatedString("XTermColor::Unchanged"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> repl_backend__common::Color::debug_description() const {
auto builder = TRY(DeprecatedStringBuilder::create());
switch (this->index()) {case 0 /* RGB */: {
TRY(builder.append("Color::RGB"sv));
[[maybe_unused]] auto const& that = this->template get<Color::RGB>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("red: {}, ", that.red));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("green: {}, ", that.green));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("blue: {}", that.blue));
}
TRY(builder.append(")"sv));
break;}
case 1 /* XTerm */: {
TRY(builder.append("Color::XTerm"sv));
[[maybe_unused]] auto const& that = this->template get<Color::XTerm>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
