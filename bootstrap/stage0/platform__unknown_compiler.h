#pragma once
#include <lib.h>
namespace Jakt {
namespace platform__unknown_compiler {
ErrorOr<JaktInternal::DynamicArray<ByteString>> run_compiler(ByteString const cxx_compiler_path, ByteString const cpp_filename, ByteString const output_filename, ByteString const runtime_path, JaktInternal::DynamicArray<ByteString> const extra_include_paths, JaktInternal::DynamicArray<ByteString> const extra_lib_paths, JaktInternal::DynamicArray<ByteString> const extra_link_libs, bool const optimize, JaktInternal::DynamicArray<ByteString> const extra_compiler_flags, bool const use_ccache);

}
} // namespace Jakt
