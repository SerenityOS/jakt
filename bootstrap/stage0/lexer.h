#pragma once
#include <lib.h>
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace lexer {
struct Lexer;
struct Token;

struct LiteralPrefix;

struct LiteralSuffix;

}
namespace lexer {
struct LiteralPrefix {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
Jakt::utility::Span span;
} SingleQuotedString;
struct {
ByteString quote;
Jakt::utility::Span span;
} QuotedString;
struct {
Jakt::lexer::LiteralPrefix prefix;
ByteString number;
Jakt::lexer::LiteralSuffix suffix;
Jakt::utility::Span span;
} Number;
struct {
ByteString name;
Jakt::utility::Span span;
} Identifier;
struct {
Jakt::utility::Span value;
} Semicolon;
struct {
Jakt::utility::Span value;
} Colon;
struct {
Jakt::utility::Span value;
} ColonColon;
struct {
Jakt::utility::Span value;
} LParen;
struct {
Jakt::utility::Span value;
} RParen;
struct {
Jakt::utility::Span value;
} LCurly;
struct {
Jakt::utility::Span value;
} RCurly;
struct {
Jakt::utility::Span value;
} LSquare;
struct {
Jakt::utility::Span value;
} RSquare;
struct {
Jakt::utility::Span value;
} PercentSign;
struct {
Jakt::utility::Span value;
} Plus;
struct {
Jakt::utility::Span value;
} Minus;
struct {
Jakt::utility::Span value;
} Equal;
struct {
Jakt::utility::Span value;
} PlusEqual;
struct {
Jakt::utility::Span value;
} PlusPlus;
struct {
Jakt::utility::Span value;
} MinusEqual;
struct {
Jakt::utility::Span value;
} MinusMinus;
struct {
Jakt::utility::Span value;
} AsteriskEqual;
struct {
Jakt::utility::Span value;
} ForwardSlashEqual;
struct {
Jakt::utility::Span value;
} PercentSignEqual;
struct {
Jakt::utility::Span value;
} NotEqual;
struct {
Jakt::utility::Span value;
} DoubleEqual;
struct {
Jakt::utility::Span value;
} GreaterThan;
struct {
Jakt::utility::Span value;
} GreaterThanOrEqual;
struct {
Jakt::utility::Span value;
} LessThan;
struct {
Jakt::utility::Span value;
} LessThanOrEqual;
struct {
Jakt::utility::Span value;
} LeftArithmeticShift;
struct {
Jakt::utility::Span value;
} LeftShift;
struct {
Jakt::utility::Span value;
} LeftShiftEqual;
struct {
Jakt::utility::Span value;
} RightShift;
struct {
Jakt::utility::Span value;
} RightArithmeticShift;
struct {
Jakt::utility::Span value;
} RightShiftEqual;
struct {
Jakt::utility::Span value;
} Asterisk;
struct {
Jakt::utility::Span value;
} Ampersand;
struct {
Jakt::utility::Span value;
} AmpersandEqual;
struct {
Jakt::utility::Span value;
} AmpersandAmpersand;
struct {
Jakt::utility::Span value;
} Pipe;
struct {
Jakt::utility::Span value;
} PipeEqual;
struct {
Jakt::utility::Span value;
} PipePipe;
struct {
Jakt::utility::Span value;
} Caret;
struct {
Jakt::utility::Span value;
} CaretEqual;
struct {
Jakt::utility::Span value;
} Dollar;
struct {
Jakt::utility::Span value;
} Tilde;
struct {
Jakt::utility::Span value;
} ForwardSlash;
struct {
Jakt::utility::Span value;
} ExclamationPoint;
struct {
Jakt::utility::Span value;
} QuestionMark;
struct {
Jakt::utility::Span value;
} QuestionMarkQuestionMark;
struct {
Jakt::utility::Span value;
} QuestionMarkQuestionMarkEqual;
struct {
Jakt::utility::Span value;
} Comma;
struct {
Jakt::utility::Span value;
} Dot;
struct {
Jakt::utility::Span value;
} DotDot;
struct {
JaktInternal::Optional<ByteString> comment;
Jakt::utility::Span span;
} Eol;
struct {
Jakt::utility::Span value;
} Eof;
struct {
Jakt::utility::Span value;
} FatArrow;
struct {
Jakt::utility::Span value;
} Arrow;
struct {
Jakt::utility::Span value;
} And;
struct {
Jakt::utility::Span value;
} Anon;
struct {
Jakt::utility::Span value;
} As;
struct {
Jakt::utility::Span value;
} Boxed;
struct {
Jakt::utility::Span value;
} Break;
struct {
Jakt::utility::Span value;
} Catch;
struct {
Jakt::utility::Span value;
} Class;
struct {
Jakt::utility::Span value;
} Continue;
struct {
Jakt::utility::Span value;
} Cpp;
struct {
Jakt::utility::Span value;
} Defer;
struct {
Jakt::utility::Span value;
} Destructor;
struct {
Jakt::utility::Span value;
} Else;
struct {
Jakt::utility::Span value;
} Enum;
struct {
Jakt::utility::Span value;
} Extern;
struct {
Jakt::utility::Span value;
} Export;
struct {
Jakt::utility::Span value;
} False;
struct {
Jakt::utility::Span value;
} For;
struct {
Jakt::utility::Span value;
} Fn;
struct {
Jakt::utility::Span value;
} Comptime;
struct {
Jakt::utility::Span value;
} If;
struct {
Jakt::utility::Span value;
} Import;
struct {
Jakt::utility::Span value;
} Relative;
struct {
Jakt::utility::Span value;
} In;
struct {
Jakt::utility::Span value;
} Is;
struct {
Jakt::utility::Span value;
} Let;
struct {
Jakt::utility::Span value;
} Loop;
struct {
Jakt::utility::Span value;
} Match;
struct {
Jakt::utility::Span value;
} Must;
struct {
Jakt::utility::Span value;
} Mut;
struct {
Jakt::utility::Span value;
} Namespace;
struct {
Jakt::utility::Span value;
} Not;
struct {
Jakt::utility::Span value;
} Or;
struct {
Jakt::utility::Span value;
} Override;
struct {
Jakt::utility::Span value;
} Private;
struct {
Jakt::utility::Span value;
} Public;
struct {
Jakt::utility::Span value;
} Raw;
struct {
Jakt::utility::Span value;
} Reflect;
struct {
Jakt::utility::Span value;
} Return;
struct {
Jakt::utility::Span value;
} Restricted;
struct {
Jakt::utility::Span value;
} Sizeof;
struct {
Jakt::utility::Span value;
} Struct;
struct {
Jakt::utility::Span value;
} This;
struct {
Jakt::utility::Span value;
} Throw;
struct {
Jakt::utility::Span value;
} Throws;
struct {
Jakt::utility::Span value;
} True;
struct {
Jakt::utility::Span value;
} Try;
struct {
Jakt::utility::Span value;
} Unsafe;
struct {
Jakt::utility::Span value;
} Virtual;
struct {
Jakt::utility::Span value;
} Weak;
struct {
Jakt::utility::Span value;
} While;
struct {
Jakt::utility::Span value;
} Yield;
struct {
Jakt::utility::Span value;
} Guard;
struct {
Jakt::utility::Span value;
} Implements;
struct {
Jakt::utility::Span value;
} Requires;
struct {
Jakt::utility::Span value;
} Trait;
struct {
JaktInternal::Optional<ByteString> consumed;
Jakt::utility::Span span;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Token SingleQuotedString(ByteString quote, JaktInternal::Optional<ByteString> prefix, Jakt::utility::Span span);
[[nodiscard]] static Token QuotedString(ByteString quote, Jakt::utility::Span span);
[[nodiscard]] static Token Number(Jakt::lexer::LiteralPrefix prefix, ByteString number, Jakt::lexer::LiteralSuffix suffix, Jakt::utility::Span span);
[[nodiscard]] static Token Identifier(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static Token Semicolon(Jakt::utility::Span value);
[[nodiscard]] static Token Colon(Jakt::utility::Span value);
[[nodiscard]] static Token ColonColon(Jakt::utility::Span value);
[[nodiscard]] static Token LParen(Jakt::utility::Span value);
[[nodiscard]] static Token RParen(Jakt::utility::Span value);
[[nodiscard]] static Token LCurly(Jakt::utility::Span value);
[[nodiscard]] static Token RCurly(Jakt::utility::Span value);
[[nodiscard]] static Token LSquare(Jakt::utility::Span value);
[[nodiscard]] static Token RSquare(Jakt::utility::Span value);
[[nodiscard]] static Token PercentSign(Jakt::utility::Span value);
[[nodiscard]] static Token Plus(Jakt::utility::Span value);
[[nodiscard]] static Token Minus(Jakt::utility::Span value);
[[nodiscard]] static Token Equal(Jakt::utility::Span value);
[[nodiscard]] static Token PlusEqual(Jakt::utility::Span value);
[[nodiscard]] static Token PlusPlus(Jakt::utility::Span value);
[[nodiscard]] static Token MinusEqual(Jakt::utility::Span value);
[[nodiscard]] static Token MinusMinus(Jakt::utility::Span value);
[[nodiscard]] static Token AsteriskEqual(Jakt::utility::Span value);
[[nodiscard]] static Token ForwardSlashEqual(Jakt::utility::Span value);
[[nodiscard]] static Token PercentSignEqual(Jakt::utility::Span value);
[[nodiscard]] static Token NotEqual(Jakt::utility::Span value);
[[nodiscard]] static Token DoubleEqual(Jakt::utility::Span value);
[[nodiscard]] static Token GreaterThan(Jakt::utility::Span value);
[[nodiscard]] static Token GreaterThanOrEqual(Jakt::utility::Span value);
[[nodiscard]] static Token LessThan(Jakt::utility::Span value);
[[nodiscard]] static Token LessThanOrEqual(Jakt::utility::Span value);
[[nodiscard]] static Token LeftArithmeticShift(Jakt::utility::Span value);
[[nodiscard]] static Token LeftShift(Jakt::utility::Span value);
[[nodiscard]] static Token LeftShiftEqual(Jakt::utility::Span value);
[[nodiscard]] static Token RightShift(Jakt::utility::Span value);
[[nodiscard]] static Token RightArithmeticShift(Jakt::utility::Span value);
[[nodiscard]] static Token RightShiftEqual(Jakt::utility::Span value);
[[nodiscard]] static Token Asterisk(Jakt::utility::Span value);
[[nodiscard]] static Token Ampersand(Jakt::utility::Span value);
[[nodiscard]] static Token AmpersandEqual(Jakt::utility::Span value);
[[nodiscard]] static Token AmpersandAmpersand(Jakt::utility::Span value);
[[nodiscard]] static Token Pipe(Jakt::utility::Span value);
[[nodiscard]] static Token PipeEqual(Jakt::utility::Span value);
[[nodiscard]] static Token PipePipe(Jakt::utility::Span value);
[[nodiscard]] static Token Caret(Jakt::utility::Span value);
[[nodiscard]] static Token CaretEqual(Jakt::utility::Span value);
[[nodiscard]] static Token Dollar(Jakt::utility::Span value);
[[nodiscard]] static Token Tilde(Jakt::utility::Span value);
[[nodiscard]] static Token ForwardSlash(Jakt::utility::Span value);
[[nodiscard]] static Token ExclamationPoint(Jakt::utility::Span value);
[[nodiscard]] static Token QuestionMark(Jakt::utility::Span value);
[[nodiscard]] static Token QuestionMarkQuestionMark(Jakt::utility::Span value);
[[nodiscard]] static Token QuestionMarkQuestionMarkEqual(Jakt::utility::Span value);
[[nodiscard]] static Token Comma(Jakt::utility::Span value);
[[nodiscard]] static Token Dot(Jakt::utility::Span value);
[[nodiscard]] static Token DotDot(Jakt::utility::Span value);
[[nodiscard]] static Token Eol(JaktInternal::Optional<ByteString> comment, Jakt::utility::Span span);
[[nodiscard]] static Token Eof(Jakt::utility::Span value);
[[nodiscard]] static Token FatArrow(Jakt::utility::Span value);
[[nodiscard]] static Token Arrow(Jakt::utility::Span value);
[[nodiscard]] static Token And(Jakt::utility::Span value);
[[nodiscard]] static Token Anon(Jakt::utility::Span value);
[[nodiscard]] static Token As(Jakt::utility::Span value);
[[nodiscard]] static Token Boxed(Jakt::utility::Span value);
[[nodiscard]] static Token Break(Jakt::utility::Span value);
[[nodiscard]] static Token Catch(Jakt::utility::Span value);
[[nodiscard]] static Token Class(Jakt::utility::Span value);
[[nodiscard]] static Token Continue(Jakt::utility::Span value);
[[nodiscard]] static Token Cpp(Jakt::utility::Span value);
[[nodiscard]] static Token Defer(Jakt::utility::Span value);
[[nodiscard]] static Token Destructor(Jakt::utility::Span value);
[[nodiscard]] static Token Else(Jakt::utility::Span value);
[[nodiscard]] static Token Enum(Jakt::utility::Span value);
[[nodiscard]] static Token Extern(Jakt::utility::Span value);
[[nodiscard]] static Token Export(Jakt::utility::Span value);
[[nodiscard]] static Token False(Jakt::utility::Span value);
[[nodiscard]] static Token For(Jakt::utility::Span value);
[[nodiscard]] static Token Fn(Jakt::utility::Span value);
[[nodiscard]] static Token Comptime(Jakt::utility::Span value);
[[nodiscard]] static Token If(Jakt::utility::Span value);
[[nodiscard]] static Token Import(Jakt::utility::Span value);
[[nodiscard]] static Token Relative(Jakt::utility::Span value);
[[nodiscard]] static Token In(Jakt::utility::Span value);
[[nodiscard]] static Token Is(Jakt::utility::Span value);
[[nodiscard]] static Token Let(Jakt::utility::Span value);
[[nodiscard]] static Token Loop(Jakt::utility::Span value);
[[nodiscard]] static Token Match(Jakt::utility::Span value);
[[nodiscard]] static Token Must(Jakt::utility::Span value);
[[nodiscard]] static Token Mut(Jakt::utility::Span value);
[[nodiscard]] static Token Namespace(Jakt::utility::Span value);
[[nodiscard]] static Token Not(Jakt::utility::Span value);
[[nodiscard]] static Token Or(Jakt::utility::Span value);
[[nodiscard]] static Token Override(Jakt::utility::Span value);
[[nodiscard]] static Token Private(Jakt::utility::Span value);
[[nodiscard]] static Token Public(Jakt::utility::Span value);
[[nodiscard]] static Token Raw(Jakt::utility::Span value);
[[nodiscard]] static Token Reflect(Jakt::utility::Span value);
[[nodiscard]] static Token Return(Jakt::utility::Span value);
[[nodiscard]] static Token Restricted(Jakt::utility::Span value);
[[nodiscard]] static Token Sizeof(Jakt::utility::Span value);
[[nodiscard]] static Token Struct(Jakt::utility::Span value);
[[nodiscard]] static Token This(Jakt::utility::Span value);
[[nodiscard]] static Token Throw(Jakt::utility::Span value);
[[nodiscard]] static Token Throws(Jakt::utility::Span value);
[[nodiscard]] static Token True(Jakt::utility::Span value);
[[nodiscard]] static Token Try(Jakt::utility::Span value);
[[nodiscard]] static Token Unsafe(Jakt::utility::Span value);
[[nodiscard]] static Token Virtual(Jakt::utility::Span value);
[[nodiscard]] static Token Weak(Jakt::utility::Span value);
[[nodiscard]] static Token While(Jakt::utility::Span value);
[[nodiscard]] static Token Yield(Jakt::utility::Span value);
[[nodiscard]] static Token Guard(Jakt::utility::Span value);
[[nodiscard]] static Token Implements(Jakt::utility::Span value);
[[nodiscard]] static Token Requires(Jakt::utility::Span value);
[[nodiscard]] static Token Trait(Jakt::utility::Span value);
[[nodiscard]] static Token Garbage(JaktInternal::Optional<ByteString> consumed, Jakt::utility::Span span);
~Token();
Token& operator=(Token const &);
Token& operator=(Token &&);
Token(Token const&);
Token(Token &&);
private: void __jakt_destroy_variant();
public:
Jakt::utility::Span span() const;
static Jakt::lexer::Token from_keyword_or_identifier(ByteString const string, Jakt::utility::Span const span);
private:
Token() {};
};
struct Lexer {
  public:
public: size_t index;public: JaktInternal::DynamicArray<u8> input;public: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: JaktInternal::Optional<JaktInternal::DynamicArray<u8>> comment_contents;public: JaktInternal::Set<ByteString> illegal_cpp_keywords;public: static JaktInternal::DynamicArray<Jakt::lexer::Token> lex(NonnullRefPtr<Jakt::compiler::Compiler> const compiler);
public: void error(ByteString const message, Jakt::utility::Span const span);
public: Jakt::utility::Span span(size_t const start, size_t const end) const;
public: u8 peek() const;
public: u8 peek_ahead(size_t const steps) const;
public: u8 peek_behind(size_t const steps) const;
public: bool eof() const;
public: ByteString substring(size_t const start, size_t const length) const;
public: Jakt::lexer::Token lex_character_constant_or_name();
public: Jakt::lexer::Token lex_number_or_name();
public: bool valid_digit(Jakt::lexer::LiteralPrefix const prefix, u8 const digit, bool const decimal_allowed);
public: Jakt::lexer::Token lex_number();
public: Jakt::lexer::LiteralSuffix consume_numeric_literal_suffix();
public: Jakt::lexer::Token lex_quoted_string(u8 const delimiter);
public: Jakt::lexer::Token lex_plus();
public: Jakt::lexer::Token lex_minus();
public: Jakt::lexer::Token lex_asterisk();
public: Jakt::lexer::Token lex_forward_slash();
public: Jakt::lexer::Token lex_caret();
public: Jakt::lexer::Token lex_pipe();
public: Jakt::lexer::Token lex_percent_sign();
public: Jakt::lexer::Token lex_exclamation_point();
public: Jakt::lexer::Token lex_ampersand();
public: Jakt::lexer::Token lex_less_than();
public: Jakt::lexer::Token lex_greater_than();
public: Jakt::lexer::Token lex_dot();
public: Jakt::lexer::Token lex_colon();
public: Jakt::lexer::Token lex_question_mark();
public: Jakt::lexer::Token lex_equals();
public: JaktInternal::Optional<ByteString> consume_comment_contents();
public: JaktInternal::Optional<Jakt::lexer::Token> next();
public: Lexer(size_t a_index, JaktInternal::DynamicArray<u8> a_input, NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> a_comment_contents, JaktInternal::Set<ByteString> a_illegal_cpp_keywords);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::LiteralPrefix> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::LiteralPrefix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::LiteralSuffix> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::LiteralSuffix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::Token> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::Token const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::Lexer> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::Lexer const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
