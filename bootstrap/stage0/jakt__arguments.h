#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__arguments {
struct ArgsParser {
  public:
public: JaktInternal::DynamicArray<ByteString> args;public: JaktInternal::DynamicArray<size_t> removed_indices;public: JaktInternal::DynamicArray<ByteString> definitely_positional_args;public: ErrorOr<bool> flag(JaktInternal::DynamicArray<ByteString> const names);
public: ErrorOr<JaktInternal::Optional<ByteString>> option(JaktInternal::DynamicArray<ByteString> const names);
public: ErrorOr<JaktInternal::DynamicArray<ByteString>> option_multiple(JaktInternal::DynamicArray<ByteString> const names);
public: static jakt__arguments::ArgsParser from_args(JaktInternal::DynamicArray<ByteString> const args);
public: JaktInternal::DynamicArray<ByteString> remaining_arguments() const;
public: ArgsParser(JaktInternal::DynamicArray<ByteString> a_args, JaktInternal::DynamicArray<size_t> a_removed_indices, JaktInternal::DynamicArray<ByteString> a_definitely_positional_args);

public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__arguments::ArgsParser> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__arguments::ArgsParser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
