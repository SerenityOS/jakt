#include "utility.h"
#include "typechecker.h"
#include "parser.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace utility {

/* specialisation 0 of function map: ["ByteString", "ByteString"] */
template<> JaktInternal::DynamicArray<ByteString> map<ByteString, ByteString>(JaktInternal::DynamicArray<ByteString> const input,Function<ByteString(ByteString)> const& mapper);

/* specialisation 1 of function map: ["Jakt::parser::ParsedField", "JaktInternal::Tuple<ByteString,Jakt::utility::Span>"] */
template<> JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> map<Jakt::parser::ParsedField, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(JaktInternal::DynamicArray<Jakt::parser::ParsedField> const input,Function<JaktInternal::Tuple<ByteString,Jakt::utility::Span>(Jakt::parser::ParsedField)> const& mapper);

/* specialisation 2 of function map: ["Jakt::parser::ParsedMethod", "JaktInternal::Tuple<ByteString,Jakt::utility::Span>"] */
template<> JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> map<Jakt::parser::ParsedMethod, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(JaktInternal::DynamicArray<Jakt::parser::ParsedMethod> const input,Function<JaktInternal::Tuple<ByteString,Jakt::utility::Span>(Jakt::parser::ParsedMethod)> const& mapper);
template<>
JaktInternal::DynamicArray<ByteString> map<ByteString, ByteString>(JaktInternal::DynamicArray<ByteString> const input,Function<ByteString(ByteString)> const& mapper) {
{
JaktInternal::DynamicArray<ByteString> us = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = ((input).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString t = (_magic_value.value());
{
((us).push(mapper(t)));
}

}
}

return us;
}
}
template<>
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> map<Jakt::parser::ParsedField, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(JaktInternal::DynamicArray<Jakt::parser::ParsedField> const input,Function<JaktInternal::Tuple<ByteString,Jakt::utility::Span>(Jakt::parser::ParsedField)> const& mapper) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> us = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedField> _magic = ((input).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedField t = (_magic_value.value());
{
((us).push(mapper(t)));
}

}
}

return us;
}
}
template<>
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> map<Jakt::parser::ParsedMethod, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(JaktInternal::DynamicArray<Jakt::parser::ParsedMethod> const input,Function<JaktInternal::Tuple<ByteString,Jakt::utility::Span>(Jakt::parser::ParsedMethod)> const& mapper) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> us = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = ((input).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedMethod t = (_magic_value.value());
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
