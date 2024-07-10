#pragma once
#include <lib.h>
#include "jakt__compiler.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace jakt__platform {
struct Target;





ErrorOr<JaktInternal::DynamicArray<ByteString>> platform_import_names();

ErrorOr<JaktInternal::DynamicArray<ByteString>> add_to_each(JaktInternal::DynamicArray<ByteString> const strings, ByteString const prefix, ByteString const suffix);

JaktInternal::Optional<size_t> last_namespace_separator(ByteString const name);

}
namespace jakt__platform {
struct Target {
  public:
public: ByteString arch;public: ByteString platform;public: ByteString os;public: ByteString abi;public: static ErrorOr<Jakt::jakt__platform::Target> from_triple(ByteString const triple);
public: static ErrorOr<Jakt::jakt__platform::Target> active();
public: ErrorOr<ByteString> name(bool const abbreviate) const;
public: Target(ByteString a_arch, ByteString a_platform, ByteString a_os, ByteString a_abi);

public: ErrorOr<size_t> size_t_size() const;
public: ErrorOr<size_t> pointer_size() const;
public: ErrorOr<size_t> int_size() const;
public: ErrorOr<size_t> size_t_alignment() const;
public: ErrorOr<size_t> pointer_alignment() const;
public: ErrorOr<size_t> int_alignment() const;
public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform::Target> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform::Target const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
