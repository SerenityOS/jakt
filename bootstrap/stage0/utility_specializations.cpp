#include "utility.h"
#include "typechecker.h"
#include "parser.h"
#include "utility.h"
#include "jakt__platform__utility.h"
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
