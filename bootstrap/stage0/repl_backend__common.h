#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace repl_backend__common {
struct LineResult {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString value;
} Line;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static LineResult Line(ByteString value);
[[nodiscard]] static LineResult Eof();
~LineResult();
LineResult& operator=(LineResult const &);
LineResult& operator=(LineResult &&);
LineResult(LineResult const&);
LineResult(LineResult &&);
private: void __jakt_destroy_variant();
public:
private:
LineResult() {};
};
struct XTermColor {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static XTermColor Default();
[[nodiscard]] static XTermColor Black();
[[nodiscard]] static XTermColor Red();
[[nodiscard]] static XTermColor Green();
[[nodiscard]] static XTermColor Yellow();
[[nodiscard]] static XTermColor Blue();
[[nodiscard]] static XTermColor Magenta();
[[nodiscard]] static XTermColor Cyan();
[[nodiscard]] static XTermColor White();
[[nodiscard]] static XTermColor Unchanged();
~XTermColor();
XTermColor& operator=(XTermColor const &);
XTermColor& operator=(XTermColor &&);
XTermColor(XTermColor const&);
XTermColor(XTermColor &&);
private: void __jakt_destroy_variant();
public:
private:
XTermColor() {};
};
struct Color {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
u8 red;
u8 green;
u8 blue;
} Components;
struct {
repl_backend__common::XTermColor value;
} XTerm;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Color Components(u8 red, u8 green, u8 blue);
[[nodiscard]] static Color XTerm(repl_backend__common::XTermColor value);
~Color();
Color& operator=(Color const &);
Color& operator=(Color &&);
Color(Color const&);
Color(Color &&);
private: void __jakt_destroy_variant();
public:
private:
Color() {};
};
struct Style {
  public:
public: JaktInternal::Optional<repl_backend__common::Color> foreground;public: JaktInternal::Optional<repl_backend__common::Color> background;public: Style(JaktInternal::Optional<repl_backend__common::Color> a_foreground, JaktInternal::Optional<repl_backend__common::Color> a_background);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::LineResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::LineResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::XTermColor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::XTermColor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::Color> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::Color const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::Style> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::Style const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
