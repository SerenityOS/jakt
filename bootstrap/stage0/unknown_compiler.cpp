#include "unknown_compiler.h"
namespace Jakt {
namespace unknown_compiler {
ErrorOr<JaktInternal::Array<String>> run_compiler(String const cxx_compiler_path,String const cpp_filename,String const output_filename,String const runtime_path,JaktInternal::Array<String> const extra_include_paths,JaktInternal::Array<String> const extra_lib_paths,JaktInternal::Array<String> const extra_link_libs,bool const optimize,JaktInternal::Array<String> const extra_compiler_flags) {
{
warnln(Jakt::String("UNIMPLEMENTED: run_compiler(cxx_compiler_path: {}, cpp_filename: {}, output_filename: {}, runtime_path: {}, extra_include_paths: {}, extra_lib_paths: {}, extra_link_libs: {}, optimize: {}, extra_compiler_flags: {})"),cxx_compiler_path,cpp_filename,output_filename,runtime_path,extra_include_paths,extra_lib_paths,extra_link_libs,optimize,extra_compiler_flags);
return Error::from_errno(static_cast<i32>(38));
}
}

}
} // namespace Jakt
