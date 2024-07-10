#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "platform__unknown_compiler.h"
namespace Jakt {
namespace platform__unknown_compiler {
ErrorOr<JaktInternal::DynamicArray<ByteString>> run_compiler(ByteString const cxx_compiler_path,ByteString const cpp_filename,ByteString const output_filename,ByteString const runtime_path,JaktInternal::DynamicArray<ByteString> const extra_include_paths,JaktInternal::DynamicArray<ByteString> const extra_lib_paths,JaktInternal::DynamicArray<ByteString> const extra_link_libs,bool const optimize,JaktInternal::DynamicArray<ByteString> const extra_compiler_flags,bool const use_ccache) {
{
warnln((StringView::from_string_literal("UNIMPLEMENTED: run_compiler(cxx_compiler_path: {}, cpp_filename: {}, output_filename: {}, runtime_path: {}, extra_include_paths: {}, extra_lib_paths: {}, extra_link_libs: {}, optimize: {}, extra_compiler_flags: {})"sv)),cxx_compiler_path,cpp_filename,output_filename,runtime_path,extra_include_paths,extra_lib_paths,extra_link_libs,optimize,extra_compiler_flags);
return Error::from_errno(static_cast<i32>(38));
}
}

}
} // namespace Jakt
