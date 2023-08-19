#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace repl_backend__common {
namespace LineResult_Details {
struct Line{
DeprecatedString value;
template<typename _MemberT0>
Line(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Eof {
};
}
struct LineResult : public Variant<LineResult_Details::Line, LineResult_Details::Eof> {
using Variant<LineResult_Details::Line, LineResult_Details::Eof>::Variant;
    using Line = LineResult_Details::Line;
    using Eof = LineResult_Details::Eof;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace XTermColor_Details {
struct Default {
};
struct Black {
};
struct Red {
};
struct Green {
};
struct Yellow {
};
struct Blue {
};
struct Magenta {
};
struct Cyan {
};
struct White {
};
struct Unchanged {
};
}
struct XTermColor : public Variant<XTermColor_Details::Default, XTermColor_Details::Black, XTermColor_Details::Red, XTermColor_Details::Green, XTermColor_Details::Yellow, XTermColor_Details::Blue, XTermColor_Details::Magenta, XTermColor_Details::Cyan, XTermColor_Details::White, XTermColor_Details::Unchanged> {
using Variant<XTermColor_Details::Default, XTermColor_Details::Black, XTermColor_Details::Red, XTermColor_Details::Green, XTermColor_Details::Yellow, XTermColor_Details::Blue, XTermColor_Details::Magenta, XTermColor_Details::Cyan, XTermColor_Details::White, XTermColor_Details::Unchanged>::Variant;
    using Default = XTermColor_Details::Default;
    using Black = XTermColor_Details::Black;
    using Red = XTermColor_Details::Red;
    using Green = XTermColor_Details::Green;
    using Yellow = XTermColor_Details::Yellow;
    using Blue = XTermColor_Details::Blue;
    using Magenta = XTermColor_Details::Magenta;
    using Cyan = XTermColor_Details::Cyan;
    using White = XTermColor_Details::White;
    using Unchanged = XTermColor_Details::Unchanged;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace Color_Details {
struct Components {
u8 red;
u8 green;
u8 blue;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Components(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
red{ forward<_MemberT0>(member_0)},
green{ forward<_MemberT1>(member_1)},
blue{ forward<_MemberT2>(member_2)}
{}
};
struct XTerm{
repl_backend__common::XTermColor value;
template<typename _MemberT0>
XTerm(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct Color : public Variant<Color_Details::Components, Color_Details::XTerm> {
using Variant<Color_Details::Components, Color_Details::XTerm>::Variant;
    using Components = Color_Details::Components;
    using XTerm = Color_Details::XTerm;
ErrorOr<DeprecatedString> debug_description() const;
};
struct Style {
  public:
public: JaktInternal::Optional<repl_backend__common::Color> foreground;public: JaktInternal::Optional<repl_backend__common::Color> background;public: Style(JaktInternal::Optional<repl_backend__common::Color> a_foreground, JaktInternal::Optional<repl_backend__common::Color> a_background);

public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::LineResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::LineResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::XTermColor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::XTermColor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::Color> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::Color const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl_backend__common::Style> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl_backend__common::Style const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
