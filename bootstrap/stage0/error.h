#pragma once
#include "__unified_forward.h"
#include "utility.h"
namespace Jakt {
namespace error {
struct MessageSeverity {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static MessageSeverity Hint();
[[nodiscard]] static MessageSeverity Error();
~MessageSeverity();
MessageSeverity& operator=(MessageSeverity const &);
MessageSeverity& operator=(MessageSeverity &&);
MessageSeverity(MessageSeverity const&);
MessageSeverity(MessageSeverity &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<DeprecatedString> ansi_color_code() const;
ErrorOr<DeprecatedString> name() const;
private:
MessageSeverity() {};
};
struct JaktError {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
DeprecatedString message;
utility::Span span;
} Message;
struct {
DeprecatedString message;
utility::Span span;
DeprecatedString hint;
utility::Span hint_span;
} MessageWithHint;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static JaktError Message(DeprecatedString message, utility::Span span);
[[nodiscard]] static JaktError MessageWithHint(DeprecatedString message, utility::Span span, DeprecatedString hint, utility::Span hint_span);
~JaktError();
JaktError& operator=(JaktError const &);
JaktError& operator=(JaktError &&);
JaktError(JaktError const&);
JaktError(JaktError &&);
private: void __jakt_destroy_variant();
public:
utility::Span span() const;
private:
JaktError() {};
};
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::error::MessageSeverity> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::error::MessageSeverity const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::error::JaktError> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::error::JaktError const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
