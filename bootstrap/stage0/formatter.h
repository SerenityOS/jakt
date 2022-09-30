#pragma once
#include "__unified_forward.h"
#include "compiler.h"
#include "lexer.h"
namespace Jakt {
namespace formatter {
namespace ExpressionMode_Details {
struct OutsideExpression {};
struct AtExpressionStart {};
struct InExpression {};
}
struct ExpressionMode : public Variant<ExpressionMode_Details::OutsideExpression, ExpressionMode_Details::AtExpressionStart, ExpressionMode_Details::InExpression> {
using Variant<ExpressionMode_Details::OutsideExpression, ExpressionMode_Details::AtExpressionStart, ExpressionMode_Details::InExpression>::Variant;
    using OutsideExpression = ExpressionMode_Details::OutsideExpression;
    using AtExpressionStart = ExpressionMode_Details::AtExpressionStart;
    using InExpression = ExpressionMode_Details::InExpression;
ErrorOr<String> debug_description() const;
};
struct Stage0 {
  public:
JaktInternal::Array<lexer::Token> tokens;size_t index;JaktInternal::Array<formatter::State> states;size_t indent;bool already_seen_enclosure_in_current_line;JaktInternal::Array<size_t> dedents_to_skip;ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> next();
ErrorOr<void> replace_state(const formatter::State state);
formatter::State state() const;
ErrorOr<void> push_state(const formatter::State state);
static ErrorOr<formatter::Stage0> create(NonnullRefPtr<compiler::Compiler> compiler, const JaktInternal::Array<u8> source);
ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> next_impl(const bool reconsume);
lexer::Token peek(const i64 offset) const;
static ErrorOr<formatter::Stage0> for_tokens(const JaktInternal::Array<lexer::Token> tokens);
static ErrorOr<JaktInternal::Array<u8>> to_array(const String x);
void pop_state();
Stage0(JaktInternal::Array<lexer::Token> a_tokens, size_t a_index, JaktInternal::Array<formatter::State> a_states, size_t a_indent, bool a_already_seen_enclosure_in_current_line, JaktInternal::Array<size_t> a_dedents_to_skip);

lexer::Token consume();
ErrorOr<String> debug_description() const;
};struct Formatter {
  public:
formatter::Stage0 token_provider;JaktInternal::Array<formatter::ReflowState> current_line;size_t current_line_length;size_t max_allowed_line_length;JaktInternal::Array<formatter::BreakablePoint> breakable_points_in_current_line;JaktInternal::Array<formatter::ReflowState> tokens_to_reflow;JaktInternal::Array<JaktInternal::Optional<lexer::Token>> replace_commas_in_enclosure;size_t enclosures_to_ignore;bool in_if_expr;size_t empty_line_count;ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>> next();
static bool should_ignore_state(const formatter::State state);
static ErrorOr<formatter::Formatter> for_tokens(const JaktInternal::Array<lexer::Token> tokens, const size_t max_allowed_line_length);
static ErrorOr<JaktInternal::Array<u8>> to_array(const String s);
Formatter(formatter::Stage0 a_token_provider, JaktInternal::Array<formatter::ReflowState> a_current_line, size_t a_current_line_length, size_t a_max_allowed_line_length, JaktInternal::Array<formatter::BreakablePoint> a_breakable_points_in_current_line, JaktInternal::Array<formatter::ReflowState> a_tokens_to_reflow, JaktInternal::Array<JaktInternal::Optional<lexer::Token>> a_replace_commas_in_enclosure, size_t a_enclosures_to_ignore, bool a_in_if_expr, size_t a_empty_line_count);

ErrorOr<void> fixup_tokens_to_reflow();
ErrorOr<size_t> token_length(const formatter::FormattedToken token) const;
ErrorOr<void> fixup_closing_enclosures(JaktInternal::Array<formatter::ReflowState>& line) const;
size_t pick_breaking_point_index() const;
ErrorOr<String> debug_description() const;
};namespace Entity_Details {
struct Struct {};
struct Enum {};
struct Namespace {};
struct Function {
bool arrow;
bool indented;
template<typename _MemberT0, typename _MemberT1>
Function(_MemberT0&& member_0, _MemberT1&& member_1):
arrow{ forward<_MemberT0>(member_0)},
indented{ forward<_MemberT1>(member_1)}
{}
};
}
struct Entity : public Variant<Entity_Details::Struct, Entity_Details::Enum, Entity_Details::Namespace, Entity_Details::Function> {
using Variant<Entity_Details::Struct, Entity_Details::Enum, Entity_Details::Namespace, Entity_Details::Function>::Variant;
    using Struct = Entity_Details::Struct;
    using Enum = Entity_Details::Enum;
    using Namespace = Entity_Details::Namespace;
    using Function = Entity_Details::Function;
ErrorOr<String> debug_description() const;
static formatter::Entity from_token(lexer::Token const& token);
};
struct FormattedToken {
  public:
lexer::Token token;size_t indent;JaktInternal::Array<u8> trailing_trivia;JaktInternal::Array<u8> preceding_trivia;FormattedToken(lexer::Token a_token, size_t a_indent, JaktInternal::Array<u8> a_trailing_trivia, JaktInternal::Array<u8> a_preceding_trivia);

ErrorOr<String> token_text() const;
ErrorOr<String> debug_description() const;
};namespace State_Details {
struct Toplevel {
size_t open_parens;
size_t open_curlies;
size_t open_squares;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Toplevel(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
open_parens{ forward<_MemberT0>(member_0)},
open_curlies{ forward<_MemberT1>(member_1)},
open_squares{ forward<_MemberT2>(member_2)}
{}
};
struct Import {
bool is_extern;
template<typename _MemberT0>
Import(_MemberT0&& member_0):
is_extern{ forward<_MemberT0>(member_0)}
{}
};
struct ImportList {
bool emitted_comma;
template<typename _MemberT0>
ImportList(_MemberT0&& member_0):
emitted_comma{ forward<_MemberT0>(member_0)}
{}
};
struct EntityDeclaration {
formatter::Entity entity;
bool accept_generics;
bool has_generics;
size_t generic_nesting;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
EntityDeclaration(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
entity{ forward<_MemberT0>(member_0)},
accept_generics{ forward<_MemberT1>(member_1)},
has_generics{ forward<_MemberT2>(member_2)},
generic_nesting{ forward<_MemberT3>(member_3)}
{}
};
struct ParameterList {
size_t open_parens;
template<typename _MemberT0>
ParameterList(_MemberT0&& member_0):
open_parens{ forward<_MemberT0>(member_0)}
{}
};
struct RestrictionList {};
struct EntityDefinition {
formatter::Entity entity;
template<typename _MemberT0>
EntityDefinition(_MemberT0&& member_0):
entity{ forward<_MemberT0>(member_0)}
{}
};
struct StatementContext {
size_t open_parens;
size_t open_curlies;
size_t open_squares;
JaktInternal::Optional<size_t> allow_eol;
bool inserted_comma;
formatter::ExpressionMode expression_mode;
size_t dedents_on_open_curly;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
StatementContext(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
open_parens{ forward<_MemberT0>(member_0)},
open_curlies{ forward<_MemberT1>(member_1)},
open_squares{ forward<_MemberT2>(member_2)},
allow_eol{ forward<_MemberT3>(member_3)},
inserted_comma{ forward<_MemberT4>(member_4)},
expression_mode{ forward<_MemberT5>(member_5)},
dedents_on_open_curly{ forward<_MemberT6>(member_6)}
{}
};
struct MatchPattern {
size_t open_parens;
bool allow_multiple;
template<typename _MemberT0, typename _MemberT1>
MatchPattern(_MemberT0&& member_0, _MemberT1&& member_1):
open_parens{ forward<_MemberT0>(member_0)},
allow_multiple{ forward<_MemberT1>(member_1)}
{}
};
struct VariableDeclaration {
size_t open_parens;
template<typename _MemberT0>
VariableDeclaration(_MemberT0&& member_0):
open_parens{ forward<_MemberT0>(member_0)}
{}
};
struct GenericCallTypeParams {
size_t open_angles;
template<typename _MemberT0>
GenericCallTypeParams(_MemberT0&& member_0):
open_angles{ forward<_MemberT0>(member_0)}
{}
};
struct TypeContext {
size_t open_parens;
size_t open_curlies;
size_t open_squares;
size_t open_angles;
bool seen_start;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
TypeContext(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
open_parens{ forward<_MemberT0>(member_0)},
open_curlies{ forward<_MemberT1>(member_1)},
open_squares{ forward<_MemberT2>(member_2)},
open_angles{ forward<_MemberT3>(member_3)},
seen_start{ forward<_MemberT4>(member_4)}
{}
};
struct FunctionTypeContext {
bool seen_final_type;
template<typename _MemberT0>
FunctionTypeContext(_MemberT0&& member_0):
seen_final_type{ forward<_MemberT0>(member_0)}
{}
};
}
struct State : public Variant<State_Details::Toplevel, State_Details::Import, State_Details::ImportList, State_Details::EntityDeclaration, State_Details::ParameterList, State_Details::RestrictionList, State_Details::EntityDefinition, State_Details::StatementContext, State_Details::MatchPattern, State_Details::VariableDeclaration, State_Details::GenericCallTypeParams, State_Details::TypeContext, State_Details::FunctionTypeContext> {
using Variant<State_Details::Toplevel, State_Details::Import, State_Details::ImportList, State_Details::EntityDeclaration, State_Details::ParameterList, State_Details::RestrictionList, State_Details::EntityDefinition, State_Details::StatementContext, State_Details::MatchPattern, State_Details::VariableDeclaration, State_Details::GenericCallTypeParams, State_Details::TypeContext, State_Details::FunctionTypeContext>::Variant;
    using Toplevel = State_Details::Toplevel;
    using Import = State_Details::Import;
    using ImportList = State_Details::ImportList;
    using EntityDeclaration = State_Details::EntityDeclaration;
    using ParameterList = State_Details::ParameterList;
    using RestrictionList = State_Details::RestrictionList;
    using EntityDefinition = State_Details::EntityDefinition;
    using StatementContext = State_Details::StatementContext;
    using MatchPattern = State_Details::MatchPattern;
    using VariableDeclaration = State_Details::VariableDeclaration;
    using GenericCallTypeParams = State_Details::GenericCallTypeParams;
    using TypeContext = State_Details::TypeContext;
    using FunctionTypeContext = State_Details::FunctionTypeContext;
ErrorOr<String> debug_description() const;
ErrorOr<String> name() const;
};
struct ReflowState {
  public:
formatter::FormattedToken token;formatter::State state;size_t enclosures_to_ignore;ReflowState(formatter::FormattedToken a_token, formatter::State a_state, size_t a_enclosures_to_ignore);

ErrorOr<String> debug_description() const;
};namespace BreakablePoint_Details {
struct Paren {
size_t point;
size_t length;
template<typename _MemberT0, typename _MemberT1>
Paren(_MemberT0&& member_0, _MemberT1&& member_1):
point{ forward<_MemberT0>(member_0)},
length{ forward<_MemberT1>(member_1)}
{}
};
struct Curly {
size_t point;
size_t length;
template<typename _MemberT0, typename _MemberT1>
Curly(_MemberT0&& member_0, _MemberT1&& member_1):
point{ forward<_MemberT0>(member_0)},
length{ forward<_MemberT1>(member_1)}
{}
};
struct Square {
size_t point;
size_t length;
template<typename _MemberT0, typename _MemberT1>
Square(_MemberT0&& member_0, _MemberT1&& member_1):
point{ forward<_MemberT0>(member_0)},
length{ forward<_MemberT1>(member_1)}
{}
};
struct Logical {
size_t point;
size_t length;
template<typename _MemberT0, typename _MemberT1>
Logical(_MemberT0&& member_0, _MemberT1&& member_1):
point{ forward<_MemberT0>(member_0)},
length{ forward<_MemberT1>(member_1)}
{}
};
}
struct BreakablePoint : public Variant<BreakablePoint_Details::Paren, BreakablePoint_Details::Curly, BreakablePoint_Details::Square, BreakablePoint_Details::Logical> {
using Variant<BreakablePoint_Details::Paren, BreakablePoint_Details::Curly, BreakablePoint_Details::Square, BreakablePoint_Details::Logical>::Variant;
    using Paren = BreakablePoint_Details::Paren;
    using Curly = BreakablePoint_Details::Curly;
    using Square = BreakablePoint_Details::Square;
    using Logical = BreakablePoint_Details::Logical;
ErrorOr<String> debug_description() const;
size_t length() const;
size_t point() const;
};
template <typename T>
JaktInternal::Optional<T> collapse(const JaktInternal::Optional<JaktInternal::Optional<T>> x) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<T>,JaktInternal::Optional<T>>{
auto __jakt_enum_value = (((x).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((x.value()));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}()))
);
}
}

template <typename T>
ErrorOr<JaktInternal::Array<T>> concat(const JaktInternal::Array<T> xs,const T y) {
{
JaktInternal::Array<T> ys = (TRY((Array<T>::create_with({}))));
{
JaktInternal::ArrayIterator<T> _magic = ((xs).iterator());
for (;;){
JaktInternal::Optional<T> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
T x = (_magic_value.value());
{
TRY((((ys).push(x))));
}

}
}

TRY((((ys).push(y))));
return (ys);
}
}

template <typename T>
ErrorOr<JaktInternal::Array<T>> init(const JaktInternal::Array<T> xs) {
{
return (TRY((((((xs)[(JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>((JaktInternal::checked_sub<size_t>(((xs).size()),static_cast<size_t>(1ULL))))})])).to_array()))));
}
}

}
template<>struct Formatter<formatter::ExpressionMode> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::ExpressionMode const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::Stage0> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::Stage0 const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::Formatter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::Formatter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::Entity> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::Entity const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::FormattedToken> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::FormattedToken const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::State> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::State const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::ReflowState> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::ReflowState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<formatter::BreakablePoint> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, formatter::BreakablePoint const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
