#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace lexer {
struct LiteralPrefix {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static LiteralPrefix None();
[[nodiscard]] static LiteralPrefix Hexadecimal();
[[nodiscard]] static LiteralPrefix Octal();
[[nodiscard]] static LiteralPrefix Binary();
~LiteralPrefix();
LiteralPrefix& operator=(LiteralPrefix const &);
LiteralPrefix& operator=(LiteralPrefix &&);
LiteralPrefix(LiteralPrefix const&);
LiteralPrefix(LiteralPrefix &&);
private: void __jakt_destroy_variant();
public:
ByteString to_string() const;
private:
LiteralPrefix() {};
};
struct LiteralSuffix {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static LiteralSuffix None();
[[nodiscard]] static LiteralSuffix UZ();
[[nodiscard]] static LiteralSuffix U8();
[[nodiscard]] static LiteralSuffix U16();
[[nodiscard]] static LiteralSuffix U32();
[[nodiscard]] static LiteralSuffix U64();
[[nodiscard]] static LiteralSuffix I8();
[[nodiscard]] static LiteralSuffix I16();
[[nodiscard]] static LiteralSuffix I32();
[[nodiscard]] static LiteralSuffix I64();
[[nodiscard]] static LiteralSuffix F32();
[[nodiscard]] static LiteralSuffix F64();
~LiteralSuffix();
LiteralSuffix& operator=(LiteralSuffix const &);
LiteralSuffix& operator=(LiteralSuffix &&);
LiteralSuffix(LiteralSuffix const&);
LiteralSuffix(LiteralSuffix &&);
private: void __jakt_destroy_variant();
public:
ByteString to_string() const;
private:
LiteralSuffix() {};
};
struct Token {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString quote;
JaktInternal::Optional<ByteString> prefix;
utility::Span span;
} SingleQuotedString;
struct {
ByteString quote;
utility::Span span;
} QuotedString;
struct {
lexer::LiteralPrefix prefix;
ByteString number;
lexer::LiteralSuffix suffix;
utility::Span span;
} Number;
struct {
ByteString name;
utility::Span span;
} Identifier;
struct {
utility::Span value;
} Semicolon;
struct {
utility::Span value;
} Colon;
struct {
utility::Span value;
} ColonColon;
struct {
utility::Span value;
} LParen;
struct {
utility::Span value;
} RParen;
struct {
utility::Span value;
} LCurly;
struct {
utility::Span value;
} RCurly;
struct {
utility::Span value;
} LSquare;
struct {
utility::Span value;
} RSquare;
struct {
utility::Span value;
} PercentSign;
struct {
utility::Span value;
} Plus;
struct {
utility::Span value;
} Minus;
struct {
utility::Span value;
} Equal;
struct {
utility::Span value;
} PlusEqual;
struct {
utility::Span value;
} PlusPlus;
struct {
utility::Span value;
} MinusEqual;
struct {
utility::Span value;
} MinusMinus;
struct {
utility::Span value;
} AsteriskEqual;
struct {
utility::Span value;
} ForwardSlashEqual;
struct {
utility::Span value;
} PercentSignEqual;
struct {
utility::Span value;
} NotEqual;
struct {
utility::Span value;
} DoubleEqual;
struct {
utility::Span value;
} GreaterThan;
struct {
utility::Span value;
} GreaterThanOrEqual;
struct {
utility::Span value;
} LessThan;
struct {
utility::Span value;
} LessThanOrEqual;
struct {
utility::Span value;
} LeftArithmeticShift;
struct {
utility::Span value;
} LeftShift;
struct {
utility::Span value;
} LeftShiftEqual;
struct {
utility::Span value;
} RightShift;
struct {
utility::Span value;
} RightArithmeticShift;
struct {
utility::Span value;
} RightShiftEqual;
struct {
utility::Span value;
} Asterisk;
struct {
utility::Span value;
} Ampersand;
struct {
utility::Span value;
} AmpersandEqual;
struct {
utility::Span value;
} AmpersandAmpersand;
struct {
utility::Span value;
} Pipe;
struct {
utility::Span value;
} PipeEqual;
struct {
utility::Span value;
} PipePipe;
struct {
utility::Span value;
} Caret;
struct {
utility::Span value;
} CaretEqual;
struct {
utility::Span value;
} Dollar;
struct {
utility::Span value;
} Tilde;
struct {
utility::Span value;
} ForwardSlash;
struct {
utility::Span value;
} ExclamationPoint;
struct {
utility::Span value;
} QuestionMark;
struct {
utility::Span value;
} QuestionMarkQuestionMark;
struct {
utility::Span value;
} QuestionMarkQuestionMarkEqual;
struct {
utility::Span value;
} Comma;
struct {
utility::Span value;
} Dot;
struct {
utility::Span value;
} DotDot;
struct {
JaktInternal::Optional<ByteString> comment;
utility::Span span;
} Eol;
struct {
utility::Span value;
} Eof;
struct {
utility::Span value;
} FatArrow;
struct {
utility::Span value;
} Arrow;
struct {
utility::Span value;
} And;
struct {
utility::Span value;
} Anon;
struct {
utility::Span value;
} As;
struct {
utility::Span value;
} Boxed;
struct {
utility::Span value;
} Break;
struct {
utility::Span value;
} Catch;
struct {
utility::Span value;
} Class;
struct {
utility::Span value;
} Continue;
struct {
utility::Span value;
} Cpp;
struct {
utility::Span value;
} Defer;
struct {
utility::Span value;
} Destructor;
struct {
utility::Span value;
} Else;
struct {
utility::Span value;
} Enum;
struct {
utility::Span value;
} Extern;
struct {
utility::Span value;
} False;
struct {
utility::Span value;
} For;
struct {
utility::Span value;
} Fn;
struct {
utility::Span value;
} Comptime;
struct {
utility::Span value;
} If;
struct {
utility::Span value;
} Import;
struct {
utility::Span value;
} Relative;
struct {
utility::Span value;
} In;
struct {
utility::Span value;
} Is;
struct {
utility::Span value;
} Let;
struct {
utility::Span value;
} Loop;
struct {
utility::Span value;
} Match;
struct {
utility::Span value;
} Mut;
struct {
utility::Span value;
} Namespace;
struct {
utility::Span value;
} Not;
struct {
utility::Span value;
} Or;
struct {
utility::Span value;
} Override;
struct {
utility::Span value;
} Private;
struct {
utility::Span value;
} Public;
struct {
utility::Span value;
} Raw;
struct {
utility::Span value;
} Reflect;
struct {
utility::Span value;
} Return;
struct {
utility::Span value;
} Restricted;
struct {
utility::Span value;
} Sizeof;
struct {
utility::Span value;
} Struct;
struct {
utility::Span value;
} This;
struct {
utility::Span value;
} Throw;
struct {
utility::Span value;
} Throws;
struct {
utility::Span value;
} True;
struct {
utility::Span value;
} Try;
struct {
utility::Span value;
} Unsafe;
struct {
utility::Span value;
} Virtual;
struct {
utility::Span value;
} Weak;
struct {
utility::Span value;
} While;
struct {
utility::Span value;
} Yield;
struct {
utility::Span value;
} Guard;
struct {
utility::Span value;
} Implements;
struct {
utility::Span value;
} Requires;
struct {
utility::Span value;
} Trait;
struct {
JaktInternal::Optional<ByteString> consumed;
utility::Span span;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static Token SingleQuotedString(ByteString quote, JaktInternal::Optional<ByteString> prefix, utility::Span span);
[[nodiscard]] static Token QuotedString(ByteString quote, utility::Span span);
[[nodiscard]] static Token Number(lexer::LiteralPrefix prefix, ByteString number, lexer::LiteralSuffix suffix, utility::Span span);
[[nodiscard]] static Token Identifier(ByteString name, utility::Span span);
[[nodiscard]] static Token Semicolon(utility::Span value);
[[nodiscard]] static Token Colon(utility::Span value);
[[nodiscard]] static Token ColonColon(utility::Span value);
[[nodiscard]] static Token LParen(utility::Span value);
[[nodiscard]] static Token RParen(utility::Span value);
[[nodiscard]] static Token LCurly(utility::Span value);
[[nodiscard]] static Token RCurly(utility::Span value);
[[nodiscard]] static Token LSquare(utility::Span value);
[[nodiscard]] static Token RSquare(utility::Span value);
[[nodiscard]] static Token PercentSign(utility::Span value);
[[nodiscard]] static Token Plus(utility::Span value);
[[nodiscard]] static Token Minus(utility::Span value);
[[nodiscard]] static Token Equal(utility::Span value);
[[nodiscard]] static Token PlusEqual(utility::Span value);
[[nodiscard]] static Token PlusPlus(utility::Span value);
[[nodiscard]] static Token MinusEqual(utility::Span value);
[[nodiscard]] static Token MinusMinus(utility::Span value);
[[nodiscard]] static Token AsteriskEqual(utility::Span value);
[[nodiscard]] static Token ForwardSlashEqual(utility::Span value);
[[nodiscard]] static Token PercentSignEqual(utility::Span value);
[[nodiscard]] static Token NotEqual(utility::Span value);
[[nodiscard]] static Token DoubleEqual(utility::Span value);
[[nodiscard]] static Token GreaterThan(utility::Span value);
[[nodiscard]] static Token GreaterThanOrEqual(utility::Span value);
[[nodiscard]] static Token LessThan(utility::Span value);
[[nodiscard]] static Token LessThanOrEqual(utility::Span value);
[[nodiscard]] static Token LeftArithmeticShift(utility::Span value);
[[nodiscard]] static Token LeftShift(utility::Span value);
[[nodiscard]] static Token LeftShiftEqual(utility::Span value);
[[nodiscard]] static Token RightShift(utility::Span value);
[[nodiscard]] static Token RightArithmeticShift(utility::Span value);
[[nodiscard]] static Token RightShiftEqual(utility::Span value);
[[nodiscard]] static Token Asterisk(utility::Span value);
[[nodiscard]] static Token Ampersand(utility::Span value);
[[nodiscard]] static Token AmpersandEqual(utility::Span value);
[[nodiscard]] static Token AmpersandAmpersand(utility::Span value);
[[nodiscard]] static Token Pipe(utility::Span value);
[[nodiscard]] static Token PipeEqual(utility::Span value);
[[nodiscard]] static Token PipePipe(utility::Span value);
[[nodiscard]] static Token Caret(utility::Span value);
[[nodiscard]] static Token CaretEqual(utility::Span value);
[[nodiscard]] static Token Dollar(utility::Span value);
[[nodiscard]] static Token Tilde(utility::Span value);
[[nodiscard]] static Token ForwardSlash(utility::Span value);
[[nodiscard]] static Token ExclamationPoint(utility::Span value);
[[nodiscard]] static Token QuestionMark(utility::Span value);
[[nodiscard]] static Token QuestionMarkQuestionMark(utility::Span value);
[[nodiscard]] static Token QuestionMarkQuestionMarkEqual(utility::Span value);
[[nodiscard]] static Token Comma(utility::Span value);
[[nodiscard]] static Token Dot(utility::Span value);
[[nodiscard]] static Token DotDot(utility::Span value);
[[nodiscard]] static Token Eol(JaktInternal::Optional<ByteString> comment, utility::Span span);
[[nodiscard]] static Token Eof(utility::Span value);
[[nodiscard]] static Token FatArrow(utility::Span value);
[[nodiscard]] static Token Arrow(utility::Span value);
[[nodiscard]] static Token And(utility::Span value);
[[nodiscard]] static Token Anon(utility::Span value);
[[nodiscard]] static Token As(utility::Span value);
[[nodiscard]] static Token Boxed(utility::Span value);
[[nodiscard]] static Token Break(utility::Span value);
[[nodiscard]] static Token Catch(utility::Span value);
[[nodiscard]] static Token Class(utility::Span value);
[[nodiscard]] static Token Continue(utility::Span value);
[[nodiscard]] static Token Cpp(utility::Span value);
[[nodiscard]] static Token Defer(utility::Span value);
[[nodiscard]] static Token Destructor(utility::Span value);
[[nodiscard]] static Token Else(utility::Span value);
[[nodiscard]] static Token Enum(utility::Span value);
[[nodiscard]] static Token Extern(utility::Span value);
[[nodiscard]] static Token False(utility::Span value);
[[nodiscard]] static Token For(utility::Span value);
[[nodiscard]] static Token Fn(utility::Span value);
[[nodiscard]] static Token Comptime(utility::Span value);
[[nodiscard]] static Token If(utility::Span value);
[[nodiscard]] static Token Import(utility::Span value);
[[nodiscard]] static Token Relative(utility::Span value);
[[nodiscard]] static Token In(utility::Span value);
[[nodiscard]] static Token Is(utility::Span value);
[[nodiscard]] static Token Let(utility::Span value);
[[nodiscard]] static Token Loop(utility::Span value);
[[nodiscard]] static Token Match(utility::Span value);
[[nodiscard]] static Token Mut(utility::Span value);
[[nodiscard]] static Token Namespace(utility::Span value);
[[nodiscard]] static Token Not(utility::Span value);
[[nodiscard]] static Token Or(utility::Span value);
[[nodiscard]] static Token Override(utility::Span value);
[[nodiscard]] static Token Private(utility::Span value);
[[nodiscard]] static Token Public(utility::Span value);
[[nodiscard]] static Token Raw(utility::Span value);
[[nodiscard]] static Token Reflect(utility::Span value);
[[nodiscard]] static Token Return(utility::Span value);
[[nodiscard]] static Token Restricted(utility::Span value);
[[nodiscard]] static Token Sizeof(utility::Span value);
[[nodiscard]] static Token Struct(utility::Span value);
[[nodiscard]] static Token This(utility::Span value);
[[nodiscard]] static Token Throw(utility::Span value);
[[nodiscard]] static Token Throws(utility::Span value);
[[nodiscard]] static Token True(utility::Span value);
[[nodiscard]] static Token Try(utility::Span value);
[[nodiscard]] static Token Unsafe(utility::Span value);
[[nodiscard]] static Token Virtual(utility::Span value);
[[nodiscard]] static Token Weak(utility::Span value);
[[nodiscard]] static Token While(utility::Span value);
[[nodiscard]] static Token Yield(utility::Span value);
[[nodiscard]] static Token Guard(utility::Span value);
[[nodiscard]] static Token Implements(utility::Span value);
[[nodiscard]] static Token Requires(utility::Span value);
[[nodiscard]] static Token Trait(utility::Span value);
[[nodiscard]] static Token Garbage(JaktInternal::Optional<ByteString> consumed, utility::Span span);
~Token();
Token& operator=(Token const &);
Token& operator=(Token &&);
Token(Token const&);
Token(Token &&);
private: void __jakt_destroy_variant();
public:
static lexer::Token from_keyword_or_identifier(ByteString const string, utility::Span const span);
utility::Span span() const;
private:
Token() {};
};
struct Lexer {
  public:
public: size_t index;public: JaktInternal::DynamicArray<u8> input;public: NonnullRefPtr<compiler::Compiler> compiler;public: JaktInternal::Optional<JaktInternal::DynamicArray<u8>> comment_contents;public: JaktInternal::Set<ByteString> illegal_cpp_keywords;public: JaktInternal::Optional<ByteString> consume_comment_contents();
public: lexer::Token lex_quoted_string(u8 const delimiter);
public: ErrorOr<JaktInternal::Optional<lexer::Token>> next();
public: lexer::Token lex_character_constant_or_name();
public: lexer::Token lex_dot();
public: lexer::Token lex_question_mark();
public: ErrorOr<lexer::Token> lex_forward_slash();
public: u8 peek_behind(size_t const steps) const;
public: u8 peek_ahead(size_t const steps) const;
public: lexer::Token lex_asterisk();
public: lexer::Token lex_minus();
public: u8 peek() const;
public: lexer::Token lex_percent_sign();
public: lexer::Token lex_number_or_name();
public: lexer::Token lex_less_than();
public: bool eof() const;
public: Lexer(size_t a_index, JaktInternal::DynamicArray<u8> a_input, NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> a_comment_contents, JaktInternal::Set<ByteString> a_illegal_cpp_keywords);

public: lexer::Token lex_ampersand();
public: utility::Span span(size_t const start, size_t const end) const;
public: lexer::Token lex_plus();
public: lexer::Token lex_exclamation_point();
public: lexer::LiteralSuffix consume_numeric_literal_suffix();
public: lexer::Token lex_colon();
public: bool valid_digit(lexer::LiteralPrefix const prefix, u8 const digit, bool const decimal_allowed);
public: void error(ByteString const message, utility::Span const span);
public: lexer::Token lex_equals();
public: ByteString substring(size_t const start, size_t const length) const;
public: lexer::Token lex_greater_than();
public: lexer::Token lex_pipe();
public: lexer::Token lex_caret();
public: lexer::Token lex_number();
public: static ErrorOr<JaktInternal::DynamicArray<lexer::Token>> lex(NonnullRefPtr<compiler::Compiler> const compiler);
public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::LiteralPrefix> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::LiteralPrefix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::LiteralSuffix> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::LiteralSuffix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::Token> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::Token const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::Lexer> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::Lexer const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
