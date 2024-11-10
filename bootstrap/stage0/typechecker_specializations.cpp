#include "typechecker.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace typechecker {

/* specialisation 0 of function build_correct_set: ["JaktInternal::Range<size_t>"] */
template<> JaktInternal::Set<size_t> Jakt::typechecker::BindingKeyBuilder::build_correct_set<JaktInternal::Range<size_t>>(JaktInternal::Range<size_t> const src,ByteString const name,Jakt::ids::VarId const var_id,JaktInternal::ArraySlice<Jakt::types::CheckedMatchCase> const cases,NonnullRefPtr<Jakt::types::CheckedProgram> const program);

/* specialisation 1 of function build_correct_set: ["JaktInternal::SetIterator<size_t>"] */
template<> JaktInternal::Set<size_t> Jakt::typechecker::BindingKeyBuilder::build_correct_set<JaktInternal::SetIterator<size_t>>(JaktInternal::SetIterator<size_t> const src,ByteString const name,Jakt::ids::VarId const var_id,JaktInternal::ArraySlice<Jakt::types::CheckedMatchCase> const cases,NonnullRefPtr<Jakt::types::CheckedProgram> const program);
template<>
JaktInternal::Set<size_t> Jakt::typechecker::BindingKeyBuilder::build_correct_set<JaktInternal::Range<size_t>>(JaktInternal::Range<size_t> const src,ByteString const name,Jakt::ids::VarId const var_id,JaktInternal::ArraySlice<Jakt::types::CheckedMatchCase> const cases,NonnullRefPtr<Jakt::types::CheckedProgram> const program) {
{
JaktInternal::Set<size_t> correct = Set<size_t>::create_with_values({});
Jakt::ids::TypeId const wanted_type = program->get_variable(var_id)->type_id;
{
JaktInternal::Range<size_t> _magic = src;
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t idx = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::VarId> __jakt_tmp242 = cases[idx].bindings.get(name);
if (__jakt_tmp242.has_value()){
Jakt::ids::VarId const var = __jakt_tmp242.value();
if (program->get_variable(var)->type_id.equals(wanted_type)){
correct.add(idx);
}
}
}

}
}

return correct;
}
}
template<>
JaktInternal::Set<size_t> Jakt::typechecker::BindingKeyBuilder::build_correct_set<JaktInternal::SetIterator<size_t>>(JaktInternal::SetIterator<size_t> const src,ByteString const name,Jakt::ids::VarId const var_id,JaktInternal::ArraySlice<Jakt::types::CheckedMatchCase> const cases,NonnullRefPtr<Jakt::types::CheckedProgram> const program) {
{
JaktInternal::Set<size_t> correct = Set<size_t>::create_with_values({});
Jakt::ids::TypeId const wanted_type = program->get_variable(var_id)->type_id;
{
JaktInternal::SetIterator<size_t> _magic = src;
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t idx = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::VarId> __jakt_tmp243 = cases[idx].bindings.get(name);
if (__jakt_tmp243.has_value()){
Jakt::ids::VarId const var = __jakt_tmp243.value();
if (program->get_variable(var)->type_id.equals(wanted_type)){
correct.add(idx);
}
}
}

}
}

return correct;
}
}
}
} // namespace Jakt
