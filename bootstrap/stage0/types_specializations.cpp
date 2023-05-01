#include "types.h"
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
#include "jakt__prelude__hash.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__iteration.h"
namespace Jakt {
namespace types {

/* specialisation 0 of function for_each_scope_accessible_unqualified_from_scope: ["NonnullRefPtr<types::CheckedVariable>"] */
template<> ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<types::CheckedVariable>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 1 of function for_each_scope_accessible_unqualified_from_scope: ["types::Value"] */
template<> ErrorOr<JaktInternal::Optional<types::Value>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::Value>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::Value>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 2 of function for_each_scope_accessible_unqualified_from_scope: ["types::EnumId"] */
template<> ErrorOr<JaktInternal::Optional<types::EnumId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::EnumId>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::EnumId>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 3 of function for_each_scope_accessible_unqualified_from_scope: ["types::TraitId"] */
template<> ErrorOr<JaktInternal::Optional<types::TraitId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::TraitId>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::TraitId>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 4 of function for_each_scope_accessible_unqualified_from_scope: ["types::StructId"] */
template<> ErrorOr<JaktInternal::Optional<types::StructId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::StructId>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::StructId>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 5 of function for_each_scope_accessible_unqualified_from_scope: ["bool"] */
template<> ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<bool>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 6 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<types::ScopeId,bool>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<types::ScopeId,bool>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<types::ScopeId,bool>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 7 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;

/* specialisation 8 of function for_each_scope_accessible_unqualified_from_scope: ["JaktInternal::Tuple<types::TypeId,types::ScopeId>"] */
template<> ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<types::TypeId,types::ScopeId>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;
template<>
ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<types::CheckedVariable>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<types::Value>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::Value>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::Value>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<types::Value> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<types::Value>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<types::EnumId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::EnumId>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::EnumId>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<types::EnumId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<types::EnumId>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<types::TraitId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::TraitId>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::TraitId>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<types::TraitId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<types::TraitId>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<types::StructId>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<types::StructId>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<types::StructId>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<types::StructId> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<types::StructId>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<bool>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<bool> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<bool>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<types::ScopeId,bool>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<types::ScopeId,bool>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<JaktInternal::Tuple<types::ScopeId,bool>>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
template<>
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<types::TypeId,types::ScopeId>>(types::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>>>(types::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>> result = JaktInternal::OptionalNone();
TRY((((*this).for_each_scope_accessible_unqualified_from_scope_impl(scope_id,(([&callback, &result](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<typename utility::IterationDecision<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(TRY((callback(scope_id,name_override,is_alias))));
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>>>::Break>();
auto& value = __jakt_match_value.value;
{
(result = value);
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return JaktInternal::ExplicitValue<void>();
}
if (__jakt_enum_value.index() == 1 /* Continue */) {
{
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
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
))))));
return result;
}
}
}
} // namespace Jakt
