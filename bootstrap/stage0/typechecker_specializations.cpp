#include "typechecker.h"
#include "main.h"
#include "platform__unknown_compiler.h"
#include "repl.h"
#include "repl_backend__default.h"
#include "repl_backend__common.h"
#include "jakt__libc__io.h"
#include "platform.h"
#include "jakt__prelude__configuration.h"
#include "project.h"
#include "ide.h"
#include "git_revision.h"
#include "formatter.h"
#include "codegen.h"
#include "typechecker.h"
#include "interpreter.h"
#include "types.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "build.h"
#include "jakt__platform__unknown_process.h"
#include "jakt__file_iterator.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform__unknown_path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
#include "jakt__prelude__prelude.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__iteration.h"
namespace Jakt {
namespace typechecker {

/* specialisation 0 of function create_internal_dictionary_product: ["DeprecatedString", "JaktInternal::Tuple<utility::Span,types::TypeId>"] */
template<> ErrorOr<typechecker::InternalDictionaryProduct<DeprecatedString,JaktInternal::Tuple<utility::Span,types::TypeId>>> create_internal_dictionary_product<DeprecatedString, JaktInternal::Tuple<utility::Span,types::TypeId>>(JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>>> const dict);
template<>
ErrorOr<typechecker::InternalDictionaryProduct<DeprecatedString,JaktInternal::Tuple<utility::Span,types::TypeId>>> create_internal_dictionary_product<DeprecatedString, JaktInternal::Tuple<utility::Span,types::TypeId>>(JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>>> const dict) {
{
JaktInternal::Dictionary<DeprecatedString,size_t> current_index = (TRY((Dictionary<DeprecatedString, size_t>::create_with_entries({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>>> _magic = ((dict).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>>> key_____ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>>> const jakt__key_____ = key_____;
DeprecatedString const key = ((jakt__key_____).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,types::TypeId>> const _ = ((jakt__key_____).template get<1>());

TRY(current_index.set(key, static_cast<size_t>(0ULL)));
}

}
}

JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<utility::Span,types::TypeId>> const current = (TRY((Dictionary<DeprecatedString, JaktInternal::Tuple<utility::Span,types::TypeId>>::create_with_entries({}))));
return typechecker::InternalDictionaryProduct<DeprecatedString, JaktInternal::Tuple<utility::Span,types::TypeId>>(dict,current,current_index,false);
}
}
}
} // namespace Jakt
