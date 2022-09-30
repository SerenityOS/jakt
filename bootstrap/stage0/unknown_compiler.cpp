#include "unknown_compiler.h"
namespace Jakt {
namespace unknown_compiler {
ErrorOr<JaktInternal::Array<String>> run_compiler(const String cxx_compiler_path,const String cpp_filename,const String output_filename,const String runtime_path,const JaktInternal::Array<String> extra_include_paths,const JaktInternal::Array<String> extra_lib_paths,const JaktInternal::Array<String> extra_link_libs,const bool optimize,const JaktInternal::Array<String> extra_compiler_flags) {
{
warnln(String("UNIMPLEMENTED: run_compiler(cxx_compiler_path: {}, cpp_filename: {}, output_filename: {}, runtime_path: {}, extra_include_paths: {}, extra_lib_paths: {}, extra_link_libs: {}, optimize: {}, extra_compiler_flags: {})"),cxx_compiler_path,cpp_filename,output_filename,runtime_path,extra_include_paths,extra_lib_paths,extra_link_libs,optimize,extra_compiler_flags);
return Error::from_errno(static_cast<i32>(38));
}
}

}
} // namespace Jakt
