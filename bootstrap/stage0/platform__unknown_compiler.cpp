#include "platform__unknown_compiler.h"
namespace Jakt {
namespace platform__unknown_compiler {
ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> run_compiler(DeprecatedString const cxx_compiler_path,DeprecatedString const cpp_filename,DeprecatedString const output_filename,DeprecatedString const runtime_path,JaktInternal::DynamicArray<DeprecatedString> const extra_include_paths,JaktInternal::DynamicArray<DeprecatedString> const extra_lib_paths,JaktInternal::DynamicArray<DeprecatedString> const extra_link_libs,bool const optimize,JaktInternal::DynamicArray<DeprecatedString> const extra_compiler_flags) {
{
warnln(Jakt::DeprecatedString("UNIMPLEMENTED: run_compiler(cxx_compiler_path: {}, cpp_filename: {}, output_filename: {}, runtime_path: {}, extra_include_paths: {}, extra_lib_paths: {}, extra_link_libs: {}, optimize: {}, extra_compiler_flags: {})"sv),cxx_compiler_path,cpp_filename,output_filename,runtime_path,extra_include_paths,extra_lib_paths,extra_link_libs,optimize,extra_compiler_flags);
return Error::from_errno(static_cast<i32>(38));
}
}

}
} // namespace Jakt
