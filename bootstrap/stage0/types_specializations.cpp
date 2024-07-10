#include "types.h"
namespace Jakt {
namespace types {

/* specialisation 0 of function for_each_scope_accessible_unqualified_from_scope: ["NonnullRefPtr<Jakt::types::CheckedVariable>"] */
template<> ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<Jakt::types::CheckedVariable>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<NonnullRefPtr<Jakt::types::CheckedVariable>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 1 of function for_each_scope_accessible_unqualified_from_scope: ["Jakt::types::Value"] */
template<> ErrorOr<JaktInternal::Optional<Jakt::types::Value>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::types::Value>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::types::Value>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 2 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 3 of function for_each_scope_accessible_unqualified_from_scope: ["Jakt::ids::EnumId"] */
template<> ErrorOr<JaktInternal::Optional<Jakt::ids::EnumId>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::ids::EnumId>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::EnumId>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 4 of function for_each_scope_accessible_unqualified_from_scope: ["Jakt::ids::TraitId"] */
template<> ErrorOr<JaktInternal::Optional<Jakt::ids::TraitId>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::ids::TraitId>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::TraitId>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 5 of function for_each_scope_accessible_unqualified_from_scope: ["Jakt::ids::StructId"] */
template<> ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::ids::StructId>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::StructId>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 6 of function for_each_scope_accessible_unqualified_from_scope: ["bool"] */
template<> ErrorOr<JaktInternal::Optional<bool>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<bool>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<bool>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 7 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<Jakt::ids::ScopeId,bool>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;

/* specialisation 8 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
template<>
ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<Jakt::types::CheckedVariable>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<NonnullRefPtr<Jakt::types::CheckedVariable>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<Jakt::types::Value>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::types::Value>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::types::Value>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<Jakt::types::Value> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<Jakt::ids::EnumId>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::ids::EnumId>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::EnumId>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<Jakt::ids::EnumId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<Jakt::ids::TraitId>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::ids::TraitId>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::TraitId>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<Jakt::ids::TraitId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<Jakt::ids::StructId>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::StructId>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<Jakt::ids::StructId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<bool>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<bool>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<bool>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<bool> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename Jakt::utility::IterationDecision<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(mixin,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return Jakt::utility::IterationDecision<bool>::Continue();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
)),ignore_mixin_scopes,root_scope))));
return result;
}
}
}
} // namespace Jakt
