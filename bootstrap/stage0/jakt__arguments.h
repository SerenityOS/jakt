#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__arguments {
struct ArgsParser {
  public:
JaktInternal::DynamicArray<DeprecatedString> args;JaktInternal::DynamicArray<size_t> removed_indices;JaktInternal::DynamicArray<DeprecatedString> definitely_positional_args;static ErrorOr<jakt__arguments::ArgsParser> from_args(JaktInternal::DynamicArray<DeprecatedString> const args);
ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> option_multiple(JaktInternal::DynamicArray<DeprecatedString> const names);
ErrorOr<bool> flag(JaktInternal::DynamicArray<DeprecatedString> const names);
ArgsParser(JaktInternal::DynamicArray<DeprecatedString> a_args, JaktInternal::DynamicArray<size_t> a_removed_indices, JaktInternal::DynamicArray<DeprecatedString> a_definitely_positional_args);

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> remaining_arguments() const;
ErrorOr<JaktInternal::Optional<DeprecatedString>> option(JaktInternal::DynamicArray<DeprecatedString> const names);
ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__arguments::ArgsParser> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__arguments::ArgsParser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
