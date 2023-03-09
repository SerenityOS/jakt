#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace utility {
struct FileId {
  public:
size_t id;FileId(size_t a_id);

bool equals(utility::FileId const rhs) const;
ErrorOr<DeprecatedString> debug_description() const;
};struct Span {
  public:
utility::FileId file_id;size_t start;size_t end;bool contains(utility::Span const span) const;
Span(utility::FileId a_file_id, size_t a_start, size_t a_end);

bool is_in_offset_range(size_t const start, size_t const end) const;
ErrorOr<DeprecatedString> debug_description() const;
};namespace IterationDecision_Details {
template<typename T>
struct Break {
T value;
template<typename _MemberT0>
Break(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
template<typename T>
struct Continue {
};
}
template<typename T>
struct IterationDecision : public Variant<IterationDecision_Details::Break<T>, IterationDecision_Details::Continue<T>> {
using Variant<IterationDecision_Details::Break<T>, IterationDecision_Details::Continue<T>>::Variant;
    using Break = IterationDecision_Details::Break<T>;
    using Continue = IterationDecision_Details::Continue<T>;
ErrorOr<DeprecatedString> debug_description() const {
auto builder = TRY(DeprecatedStringBuilder::create());
switch (this->index()) {case 0 /* Break */: {
TRY(builder.append("IterationDecision::Break"sv));
[[maybe_unused]] auto const& that = this->template get<IterationDecision::Break>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("value: {}", that.value));
}
TRY(builder.append(")"sv));
break;}
case 1 /* Continue */: {
return DeprecatedString("IterationDecision::Continue"sv);
break;}
}
return builder.to_string();
}
};
template <typename T>
T* allocate(size_t const count);
template <typename T>
T* null();
template <typename T>
ErrorOr<JaktInternal::DynamicArray<T>> add_arrays(JaktInternal::DynamicArray<T> const a, JaktInternal::DynamicArray<T> const b);
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::utility::FileId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::utility::FileId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::utility::Span> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::utility::Span const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<typename T>struct Jakt::Formatter<Jakt::utility::IterationDecision<T>
> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::utility::IterationDecision<T>
 const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
