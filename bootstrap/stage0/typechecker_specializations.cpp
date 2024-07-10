#include "typechecker.h"
namespace Jakt {
namespace typechecker {

/* specialisation 0 of function create_internal_dictionary_product: ["ByteString", "JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>"] */
template<> Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> create_internal_dictionary_product<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const dict);
template<>
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> create_internal_dictionary_product<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const dict) {
{
JaktInternal::Dictionary<ByteString,size_t> current_index = Dictionary<ByteString, size_t>::create_with_entries({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> _magic = ((dict).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> key_____ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const jakt__key_____ = key_____;
ByteString const key = ((jakt__key_____).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> const _ = ((jakt__key_____).template get<1>());

current_index.set(key, static_cast<size_t>(0ULL));
}

}
}

JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> const current = Dictionary<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create_with_entries({});
return Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>(dict,current,current_index,false);
}
}
}
} // namespace Jakt
