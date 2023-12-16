#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__platform {
struct Target {
  public:
public: ByteString arch;public: ByteString platform;public: ByteString os;public: ByteString abi;public: Target(ByteString a_arch, ByteString a_platform, ByteString a_os, ByteString a_abi);

public: static ErrorOr<jakt__platform::Target> from_triple(ByteString const triple);
public: ErrorOr<size_t> int_alignment() const;
public: ErrorOr<size_t> pointer_size() const;
public: ErrorOr<ByteString> name(bool const abbreviate) const;
public: static ErrorOr<jakt__platform::Target> active();
public: ErrorOr<size_t> size_t_alignment() const;
public: ErrorOr<size_t> size_t_size() const;
public: ErrorOr<size_t> int_size() const;
public: ErrorOr<size_t> pointer_alignment() const;
public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform::Target> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform::Target const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
