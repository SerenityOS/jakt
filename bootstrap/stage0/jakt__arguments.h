#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__arguments {
struct ArgsParser {
  public:
JaktInternal::Array<String> args;JaktInternal::Array<size_t> removed_indices;JaktInternal::Array<String> definitely_positional_args;static ErrorOr<jakt__arguments::ArgsParser> from_args(const JaktInternal::Array<String> args);
ErrorOr<JaktInternal::Array<String>> option_multiple(const JaktInternal::Array<String> names);
ErrorOr<bool> flag(const JaktInternal::Array<String> names);
ArgsParser(JaktInternal::Array<String> a_args, JaktInternal::Array<size_t> a_removed_indices, JaktInternal::Array<String> a_definitely_positional_args);

ErrorOr<JaktInternal::Array<String>> remaining_arguments() const;
ErrorOr<JaktInternal::Optional<String>> option(const JaktInternal::Array<String> names);
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<jakt__arguments::ArgsParser> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, jakt__arguments::ArgsParser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
