#include "types.h"
#include "main.h"
#include "platform__unknown_compiler.h"
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
namespace types {

/* specialisation 0 of function for_each_scope_accessible_unqualified_from_scope: ["NonnullRefPtr<types::CheckedVariable>"] */
template<> ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<types::CheckedVariable>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 1 of function for_each_scope_accessible_unqualified_from_scope: ["types::Value"] */
template<> ErrorOr<JaktInternal::Optional<types::Value>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::Value>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::Value>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 2 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<ids::TypeId,ids::ScopeId>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 3 of function for_each_scope_accessible_unqualified_from_scope: ["ids::EnumId"] */
template<> ErrorOr<JaktInternal::Optional<ids::EnumId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<ids::EnumId>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<ids::EnumId>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 4 of function for_each_scope_accessible_unqualified_from_scope: ["ids::TraitId"] */
template<> ErrorOr<JaktInternal::Optional<ids::TraitId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<ids::TraitId>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<ids::TraitId>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 5 of function for_each_scope_accessible_unqualified_from_scope: ["ids::StructId"] */
template<> ErrorOr<JaktInternal::Optional<ids::StructId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<ids::StructId>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<ids::StructId>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 6 of function for_each_scope_accessible_unqualified_from_scope: ["bool"] */
template<> ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<bool>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 7 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<ids::ScopeId,bool>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::ScopeId,bool>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;

/* specialisation 8 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const;
template<>
ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<types::CheckedVariable>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<types::Value>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::Value>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::Value>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<types::Value> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<ids::EnumId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<ids::EnumId>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<ids::EnumId>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<ids::EnumId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<ids::TraitId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<ids::TraitId>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<ids::TraitId>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<ids::TraitId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<ids::StructId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<ids::StructId>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<ids::StructId>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<ids::StructId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<bool>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<bool> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::ScopeId,bool>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](ids::ScopeId scope_id, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
(result = value);
return utility::IterationDecision<bool>::Break(true);
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.__jakt_init_index() == 1 /* Continue */) {
{
return utility::IterationDecision<bool>::Continue();
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
