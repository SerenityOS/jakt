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
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> ansi_color_code() const;
ErrorOr<DeprecatedString> name() const;
};
namespace JaktError_Details {
struct Message {
DeprecatedString message;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Message(_MemberT0&& member_0, _MemberT1&& member_1):
message{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct MessageWithHint {
DeprecatedString message;
utility::Span span;
DeprecatedString hint;
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
ErrorOr<DeprecatedString> debug_description() const;
utility::Span span() const;
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
