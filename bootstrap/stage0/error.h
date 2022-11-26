#pragma once
#include "__unified_forward.h"
#include "utility.h"
namespace Jakt {
namespace error {
namespace MessageSeverity_Details {
struct Hint {
};
struct Error {
};
}
struct MessageSeverity : public Variant<MessageSeverity_Details::Hint, MessageSeverity_Details::Error> {
using Variant<MessageSeverity_Details::Hint, MessageSeverity_Details::Error>::Variant;
    using Hint = MessageSeverity_Details::Hint;
    using Error = MessageSeverity_Details::Error;
ErrorOr<String> debug_description() const;
ErrorOr<String> ansi_color_code() const;
ErrorOr<String> name() const;
};
namespace JaktError_Details {
struct Message {
String message;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Message(_MemberT0&& member_0, _MemberT1&& member_1):
message{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct MessageWithHint {
String message;
utility::Span span;
String hint;
utility::Span hint_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
MessageWithHint(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
message{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
hint{ forward<_MemberT2>(member_2)},
hint_span{ forward<_MemberT3>(member_3)}
{}
};
}
struct JaktError : public Variant<JaktError_Details::Message, JaktError_Details::MessageWithHint> {
using Variant<JaktError_Details::Message, JaktError_Details::MessageWithHint>::Variant;
    using Message = JaktError_Details::Message;
    using MessageWithHint = JaktError_Details::MessageWithHint;
ErrorOr<String> debug_description() const;
utility::Span span() const;
};
}
template<>struct Formatter<error::MessageSeverity> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, error::MessageSeverity const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<error::JaktError> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, error::JaktError const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
