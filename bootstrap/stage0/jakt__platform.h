#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__platform {
struct Target {
  public:
public: DeprecatedString arch;public: DeprecatedString platform;public: DeprecatedString os;public: DeprecatedString abi;public: Target(DeprecatedString a_arch, DeprecatedString a_platform, DeprecatedString a_os, DeprecatedString a_abi);

public: static ErrorOr<jakt__platform::Target> from_triple(DeprecatedString const triple);
public: ErrorOr<size_t> int_alignment() const;
public: ErrorOr<size_t> pointer_size() const;
public: ErrorOr<DeprecatedString> name(bool const abbreviate) const;
public: static ErrorOr<jakt__platform::Target> active();
public: ErrorOr<size_t> size_t_alignment() const;
public: ErrorOr<size_t> size_t_size() const;
public: ErrorOr<size_t> int_size() const;
public: ErrorOr<size_t> pointer_alignment() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform::Target> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform::Target const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
