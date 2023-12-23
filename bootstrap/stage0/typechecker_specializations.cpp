#include "typechecker.h"
#include "typechecker.h"
#include "cpp_import__none.h"
#include "cpp_import__common.h"
#include "interpreter.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform.h"
namespace Jakt {
namespace typechecker {

/* specialisation 0 of function create_internal_dictionary_product: ["ByteString", "JaktInternal::Tuple<utility::Span,ids::TypeId>"] */
template<> typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<utility::Span,ids::TypeId>> create_internal_dictionary_product<ByteString, JaktInternal::Tuple<utility::Span,ids::TypeId>>(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> const dict);
template<>
typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<utility::Span,ids::TypeId>> create_internal_dictionary_product<ByteString, JaktInternal::Tuple<utility::Span,ids::TypeId>>(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> const dict) {
{
JaktInternal::Dictionary<ByteString,size_t> current_index = Dictionary<ByteString, size_t>::create_with_entries({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> _magic = ((dict).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> key_____ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> const jakt__key_____ = key_____;
ByteString const key = ((jakt__key_____).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>> const _ = ((jakt__key_____).template get<1>());

current_index.set(key, static_cast<size_t>(0ULL));
}

}
}

JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<utility::Span,ids::TypeId>> const current = Dictionary<ByteString, JaktInternal::Tuple<utility::Span,ids::TypeId>>::create_with_entries({});
return typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<utility::Span,ids::TypeId>>(dict,current,current_index,false);
}
}
}
} // namespace Jakt
