#include "utility.h"
#include "main.h"
#include "platform__unknown_compiler.h"
#include "git.h"
#include "repl.h"
#include "repl_backend__default.h"
#include "repl_backend__common.h"
#include "jakt__libc__io.h"
#include "platform.h"
#include "project.h"
#include "ide.h"
#include "formatter.h"
#include "codegen.h"
#include "typechecker.h"
#include "cpp_import__none.h"
#include "cpp_import__common.h"
#include "jakt__prelude__configuration.h"
#include "interpreter.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__platform__utility.h"
#include "build.h"
#include "jakt__platform__unknown_process.h"
#include "jakt__file_iterator.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform__unknown_path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
#include "jakt__prelude__prelude.h"
#include "jakt__prelude__class_name.h"
#include "jakt__prelude__hash.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__iteration.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace utility {

/* specialisation 0 of function map: ["parser::ParsedField", "JaktInternal::Tuple<ByteString,utility::Span>"] */
template<> JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> map<parser::ParsedField, JaktInternal::Tuple<ByteString,utility::Span>>(JaktInternal::DynamicArray<parser::ParsedField> const input,Function<JaktInternal::Tuple<ByteString,utility::Span>(parser::ParsedField)> const& mapper);

/* specialisation 1 of function map: ["parser::ParsedMethod", "JaktInternal::Tuple<ByteString,utility::Span>"] */
template<> JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> map<parser::ParsedMethod, JaktInternal::Tuple<ByteString,utility::Span>>(JaktInternal::DynamicArray<parser::ParsedMethod> const input,Function<JaktInternal::Tuple<ByteString,utility::Span>(parser::ParsedMethod)> const& mapper);
template<>
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> map<parser::ParsedField, JaktInternal::Tuple<ByteString,utility::Span>>(JaktInternal::DynamicArray<parser::ParsedField> const input,Function<JaktInternal::Tuple<ByteString,utility::Span>(parser::ParsedField)> const& mapper) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> us = DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>>::create_with({});
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((input).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField t = (_magic_value.value());
{
((us).push(mapper(t)));
}

}
}

return us;
}
}
template<>
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> map<parser::ParsedMethod, JaktInternal::Tuple<ByteString,utility::Span>>(JaktInternal::DynamicArray<parser::ParsedMethod> const input,Function<JaktInternal::Tuple<ByteString,utility::Span>(parser::ParsedMethod)> const& mapper) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> us = DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>>::create_with({});
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((input).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod t = (_magic_value.value());
{
((us).push(mapper(t)));
}

}
}

return us;
}
}
}
} // namespace Jakt
