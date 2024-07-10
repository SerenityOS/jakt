#pragma once
#include <lib.h>
#include "utility.h"
namespace Jakt {
namespace error {
struct JaktError;

struct MessageSeverity;

void print_error_json(ByteString const file_name, Jakt::error::JaktError const error);

ErrorOr<void> print_error(ByteString const file_name, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const file_contents, Jakt::error::JaktError const error);

void display_message_with_span_json(Jakt::error::MessageSeverity const severity, ByteString const file_name, ByteString const message, Jakt::utility::Span const span);

void display_message_with_span(Jakt::error::MessageSeverity const severity, ByteString const file_name, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const contents, ByteString const message, Jakt::utility::Span const span);

void print_source_line(Jakt::error::MessageSeverity const severity, JaktInternal::DynamicArray<u8> const file_contents, JaktInternal::Tuple<size_t,size_t> const file_span, Jakt::utility::Span const error_span, size_t const line_number, size_t const largest_line_number);

void print_underline(Jakt::error::MessageSeverity const severity, size_t const width, JaktInternal::Tuple<size_t,size_t> const file_span, Jakt::utility::Span const error_span, size_t const line_number, size_t const largest_line_number);

JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,size_t>> gather_line_spans(JaktInternal::DynamicArray<u8> const file_contents);

}
namespace error {
struct JaktError {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString message;
Jakt::utility::Span span;
} Message;
struct {
ByteString message;
Jakt::utility::Span span;
ByteString hint;
Jakt::utility::Span hint_span;
} MessageWithHint;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static JaktError Message(ByteString message, Jakt::utility::Span span);
[[nodiscard]] static JaktError MessageWithHint(ByteString message, Jakt::utility::Span span, ByteString hint, Jakt::utility::Span hint_span);
~JaktError();
JaktError& operator=(JaktError const &);
JaktError& operator=(JaktError &&);
JaktError(JaktError const&);
JaktError(JaktError &&);
private: void __jakt_destroy_variant();
public:
Jakt::utility::Span span() const;
private:
JaktError() {};
};
struct MessageSeverity {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static MessageSeverity Hint();
[[nodiscard]] static MessageSeverity Error();
~MessageSeverity();
MessageSeverity& operator=(MessageSeverity const &);
MessageSeverity& operator=(MessageSeverity &&);
MessageSeverity(MessageSeverity const&);
MessageSeverity(MessageSeverity &&);
private: void __jakt_destroy_variant();
public:
ByteString name() const;
ByteString ansi_color_code() const;
private:
MessageSeverity() {};
};
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::error::JaktError> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::error::JaktError const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::error::MessageSeverity> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::error::MessageSeverity const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
