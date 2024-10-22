#include "codegen.h"
namespace Jakt {
namespace codegen {

/* specialisation 0 of function has_control_flow: ["Jakt::types::CheckedMatchCase"] */
template<> bool has_control_flow<Jakt::types::CheckedMatchCase>(JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const any_of,bool const include_loop_control_flow);

/* specialisation 1 of function has_control_flow: ["NonnullRefPtr<typename Jakt::types::CheckedStatement>"] */
template<> bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const any_of,bool const include_loop_control_flow);

/* specialisation 0 of function has_control_flow: ["NonnullRefPtr<typename Jakt::types::CheckedStatement>"] */
template<> bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const maybe_v,bool const include_loop_control_flow);

/* specialisation 2 of function has_control_flow: ["NonnullRefPtr<typename Jakt::types::CheckedExpression>"] */
template<> bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const any_of,bool const include_loop_control_flow);

/* specialisation 1 of function has_control_flow: ["NonnullRefPtr<typename Jakt::types::CheckedExpression>"] */
template<> bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const maybe_v,bool const include_loop_control_flow);

/* specialisation 3 of function has_control_flow: ["JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>"] */
template<> bool has_control_flow<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const any_of,bool const include_loop_control_flow);

/* specialisation 4 of function has_control_flow: ["JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>"] */
template<> bool has_control_flow<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const any_of,bool const include_loop_control_flow);

/* specialisation 2 of function has_control_flow: ["Jakt::types::CheckedBlock"] */
template<> bool has_control_flow<Jakt::types::CheckedBlock>(JaktInternal::Optional<Jakt::types::CheckedBlock> const maybe_v,bool const include_loop_control_flow);
template<>
bool has_control_flow<Jakt::types::CheckedMatchCase>(JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const any_of,bool const include_loop_control_flow) {
{
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = any_of.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchCase t = _magic_value.value();
{
if (Jakt::codegen::has_control_flow(t,include_loop_control_flow)){
return true;
}
}

}
}

return false;
}
}
template<>
bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const any_of,bool const include_loop_control_flow) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = any_of.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> t = _magic_value.value();
{
if (Jakt::codegen::has_control_flow(t,include_loop_control_flow)){
return true;
}
}

}
}

return false;
}
}
template<>
bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const maybe_v,bool const include_loop_control_flow) {
{
return maybe_v.has_value() && Jakt::codegen::has_control_flow(maybe_v.value(),include_loop_control_flow);
}
}
template<>
bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const any_of,bool const include_loop_control_flow) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = any_of.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> t = _magic_value.value();
{
if (Jakt::codegen::has_control_flow(t,include_loop_control_flow)){
return true;
}
}

}
}

return false;
}
}
template<>
bool has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const maybe_v,bool const include_loop_control_flow) {
{
return maybe_v.has_value() && Jakt::codegen::has_control_flow(maybe_v.value(),include_loop_control_flow);
}
}
template<>
bool has_control_flow<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const any_of,bool const include_loop_control_flow) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = any_of.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> t = _magic_value.value();
{
if (Jakt::codegen::has_control_flow(t,include_loop_control_flow)){
return true;
}
}

}
}

return false;
}
}
template<>
bool has_control_flow<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const any_of,bool const include_loop_control_flow) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = any_of.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> t = _magic_value.value();
{
if (Jakt::codegen::has_control_flow(t,include_loop_control_flow)){
return true;
}
}

}
}

return false;
}
}
template<>
bool has_control_flow<Jakt::types::CheckedBlock>(JaktInternal::Optional<Jakt::types::CheckedBlock> const maybe_v,bool const include_loop_control_flow) {
{
return maybe_v.has_value() && Jakt::codegen::has_control_flow(maybe_v.value(),include_loop_control_flow);
}
}
}
} // namespace Jakt
