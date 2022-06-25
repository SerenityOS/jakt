/*
 * !!! DEPRECATION WARNING !!!
 * We're not doing any more feature development in the rust-based compiler at this point.
 * It'll be limited to bug fixes and necessities only.
 *
 * New features should go into the self-hosted compiler.
 */

/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

use crate::{compiler::FileId, error::JaktError, typechecker::NumericConstant};

#[derive(Debug, Clone, Copy, PartialEq, Default)]
pub struct Span {
    pub file_id: FileId,
    pub start: usize,
    pub end: usize,
}

impl Span {
    pub fn new(file_id: FileId, start: usize, end: usize) -> Self {
        Self {
            file_id,
            start,
            end,
        }
    }

    pub fn contains(self, span: Span) -> bool {
        self.file_id == span.file_id && span.start >= self.start && span.end <= self.end
    }
}

#[derive(Debug, PartialEq)]
pub enum TokenContents {
    SingleQuotedString(String),
    SingleQuotedByteString(String),
    QuotedString(String),
    Number(NumericConstant),
    Name(String),
    Semicolon,
    Colon,
    ColonColon,
    LParen,
    RParen,
    LCurly,
    RCurly,
    LSquare,
    RSquare,
    PercentSign,
    Plus,
    Minus,
    Equal,
    PlusEqual,
    PlusPlus,
    MinusEqual,
    MinusMinus,
    AsteriskEqual,
    ForwardSlashEqual,
    PercentSignEqual,
    NotEqual,
    DoubleEqual,
    GreaterThan,
    GreaterThanOrEqual,
    LessThan,
    LessThanOrEqual,
    LeftArithmeticShift,
    LeftShift,
    LeftShiftEqual,
    RightShift,
    RightArithmeticShift,
    RightShiftEqual,
    Asterisk,
    Ampersand,
    AmpersandEqual,
    Pipe,
    PipeEqual,
    Caret,
    CaretEqual,
    Dollar,
    Tilde,
    ForwardSlash,
    ExclamationPoint,
    QuestionMark,
    QuestionMarkQuestionMark,
    QuestionMarkQuestionMarkEqual,
    Comma,
    Dot,
    DotDot,
    Eol,
    Eof,
    FatArrow,

    Garbage,
}

#[derive(Debug)]
pub struct Token {
    pub contents: TokenContents,
    pub span: Span,
}

impl Token {
    pub fn new(contents: TokenContents, span: Span) -> Self {
        Self { contents, span }
    }

    pub fn unknown(span: Span) -> Self {
        Self {
            contents: TokenContents::Garbage,
            span,
        }
    }
}

pub fn lex(file_id: FileId, bytes: &[u8]) -> (Vec<Token>, Option<JaktError>) {
    let mut output = Vec::new();
    let mut index = 0;
    let mut error = None;

    while index < bytes.len() {
        let c = bytes[index];

        if c == b';' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Semicolon,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b':' {
            let start = index;
            index += 1;
            if index < bytes.len() {
                if bytes[index] == b':' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::ColonColon,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
                output.push(Token::new(
                    TokenContents::Colon,
                    Span::new(file_id, start, start + 1),
                ));
            }
        } else if c == b'+' {
            let start = index;
            index += 1;

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::PlusEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                } else if bytes[index] == b'+' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::PlusPlus,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }

            output.push(Token::new(
                TokenContents::Plus,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'-' {
            let start = index;
            index += 1;

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::MinusEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                } else if bytes[index] == b'-' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::MinusMinus,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }

            output.push(Token::new(
                TokenContents::Minus,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'*' {
            let start = index;
            index += 1;

            if index < bytes.len() && bytes[index] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::AsteriskEqual,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }

            output.push(Token::new(
                TokenContents::Asterisk,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'/' {
            let start = index;
            index += 1;

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::ForwardSlashEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                } else if bytes[index] == b'/' {
                    // We are in a comment, skip it
                    while index < bytes.len() {
                        if bytes[index] == b'\n' {
                            index += 1;
                            break;
                        }
                        index += 1;
                    }
                    continue;
                }
            }

            output.push(Token::new(
                TokenContents::ForwardSlash,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'=' {
            let start = index;
            index += 1;
            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::DoubleEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
                if bytes[index] == b'>' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::FatArrow,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }
            output.push(Token::new(
                TokenContents::Equal,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'>' {
            let start = index;
            index += 1;
            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::GreaterThanOrEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                } else if bytes[index] == b'>' {
                    index += 1;
                    if index < bytes.len() {
                        if bytes[index] == b'=' {
                            index += 1;
                            output.push(Token::new(
                                TokenContents::RightShiftEqual,
                                Span::new(file_id, start, start + 3),
                            ));
                        } else if bytes[index] == b'>' {
                            index += 1;
                            output.push(Token::new(
                                TokenContents::RightArithmeticShift,
                                Span::new(file_id, start, start + 3),
                            ));
                        } else {
                            output.push(Token::new(
                                TokenContents::RightShift,
                                Span::new(file_id, start, start + 2),
                            ));
                        }
                    }

                    continue;
                }
            }
            output.push(Token::new(
                TokenContents::GreaterThan,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'<' {
            let start = index;
            index += 1;
            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::LessThanOrEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                } else if bytes[index] == b'<' {
                    index += 1;
                    if bytes[index] == b'=' {
                        index += 1;
                        output.push(Token::new(
                            TokenContents::LeftShiftEqual,
                            Span::new(file_id, start, start + 3),
                        ));
                    } else if bytes[index] == b'<' {
                        index += 1;
                        output.push(Token::new(
                            TokenContents::LeftArithmeticShift,
                            Span::new(file_id, start, start + 3),
                        ));
                    } else {
                        output.push(Token::new(
                            TokenContents::LeftShift,
                            Span::new(file_id, start, start + 2),
                        ));
                    }
                    continue;
                }
            }
            output.push(Token::new(
                TokenContents::LessThan,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'!' {
            let start = index;
            index += 1;
            if index < bytes.len() && bytes[index] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::NotEqual,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }
            output.push(Token::new(
                TokenContents::ExclamationPoint,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'&' {
            let start = index;
            index += 1;

            if index < bytes.len() && bytes[index] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::AmpersandEqual,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }
            output.push(Token::new(
                TokenContents::Ampersand,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'|' {
            let start = index;
            index += 1;

            if index < bytes.len() && bytes[index] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::PipeEqual,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }

            output.push(Token::new(
                TokenContents::Pipe,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'^' {
            let start = index;
            index += 1;

            if index < bytes.len() && bytes[index] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::CaretEqual,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }

            output.push(Token::new(
                TokenContents::Caret,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'$' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Dollar,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'~' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Tilde,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'%' {
            let start = index;
            index += 1;

            if index < bytes.len() && bytes[index] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::PercentSignEqual,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }

            output.push(Token::new(
                TokenContents::PercentSign,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'?' {
            let start = index;
            index += 1;

            if index + 1 < bytes.len() && bytes[index] == b'?' && bytes[index + 1] == b'=' {
                index += 1;
                output.push(Token::new(
                    TokenContents::QuestionMarkQuestionMarkEqual,
                    Span::new(file_id, start, start + 3),
                ));
                continue;
            } else if index < bytes.len() && bytes[index] == b'?' {
                index += 1;
                output.push(Token::new(
                    TokenContents::QuestionMarkQuestionMark,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }

            output.push(Token::new(
                TokenContents::QuestionMark,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b',' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Comma,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'.' {
            let start = index;
            index += 1;
            if index < bytes.len() && bytes[index] == b'.' {
                index += 1;
                output.push(Token::new(
                    TokenContents::DotDot,
                    Span::new(file_id, start, start + 2),
                ));
                continue;
            }
            output.push(Token::new(
                TokenContents::Dot,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'(' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::LParen,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b')' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::RParen,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'{' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::LCurly,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'}' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::RCurly,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'[' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::LSquare,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b']' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::RSquare,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'\r' || c == b' ' || c == b'\t' {
            // Ignore a stand-alone carriage return
            index += 1;
        } else if c == b'\n' {
            // If the next character is a newline, we're looking at an EOL (end of line) token.
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Eol,
                Span::new(file_id, start, start + 1),
            ));
        } else {
            // Otherwise, try to consume a token.

            let (token, err) = lex_item(file_id, bytes, &mut index);
            error = error.or(err);

            output.push(token);
        }
    }

    output.push(Token {
        contents: TokenContents::Eof,
        span: Span {
            file_id,
            start: index,
            end: index,
        },
    });

    (output, error)
}

#[derive(Debug)]
pub enum LiteralSuffix {
    UZ,
    U8,
    U16,
    U32,
    U64,
    I8,
    I16,
    I32,
    I64,
    F32,
    F64,
}

#[derive(Debug)]
pub enum NumberToken {
    Integer(i128),
    Floating(f64),
}

fn consume_numeric_literal_suffix(bytes: &[u8], index: &mut usize) -> Option<LiteralSuffix> {
    match bytes[*index] {
        b'u' | b'i' | b'f' => {}
        _ => return None,
    }

    let mut local_index = *index + 1;
    if local_index >= bytes.len() {
        return None;
    }

    if bytes[*index] == b'u' && bytes[local_index] == b'z' {
        *index += 2;
        return Some(LiteralSuffix::UZ);
    }

    let start = local_index;
    while local_index < bytes.len() && bytes[local_index].is_ascii_digit() {
        local_index += 1;
    }
    let str = String::from_utf8_lossy(&bytes[start..local_index]);
    let width = (&str).parse::<i64>().ok();

    let suffix = match bytes[*index] {
        b'u' => match width {
            Some(8) => Some(LiteralSuffix::U8),
            Some(16) => Some(LiteralSuffix::U16),
            Some(32) => Some(LiteralSuffix::U32),
            Some(64) => Some(LiteralSuffix::U64),
            _ => None,
        },
        b'i' => match width {
            Some(8) => Some(LiteralSuffix::I8),
            Some(16) => Some(LiteralSuffix::I16),
            Some(32) => Some(LiteralSuffix::I32),
            Some(64) => Some(LiteralSuffix::I64),
            _ => None,
        },
        b'f' => match width {
            Some(32) => Some(LiteralSuffix::F32),
            Some(64) => Some(LiteralSuffix::F64),
            _ => None,
        },
        _ => None,
    };

    if suffix.is_some() {
        *index = local_index;
    }

    suffix
}

fn make_number_token(
    number: NumberToken,
    suffix: Option<LiteralSuffix>,
    span: Span,
) -> (TokenContents, Option<JaktError>) {
    let mut error = None;
    match number {
        NumberToken::Integer(number) => {
            let token_contents = match suffix {
                Some(LiteralSuffix::U8) => TokenContents::Number(NumericConstant::U8(number as u8)),
                Some(LiteralSuffix::U16) => {
                    TokenContents::Number(NumericConstant::U16(number as u16))
                }
                Some(LiteralSuffix::U32) => {
                    TokenContents::Number(NumericConstant::U32(number as u32))
                }

                // FIXME: This loses precision if usize is 64-bit
                Some(LiteralSuffix::UZ) => {
                    TokenContents::Number(NumericConstant::USize(number as u64))
                }

                // FIXME: This loses precision:
                Some(LiteralSuffix::U64) => {
                    TokenContents::Number(NumericConstant::U64(number as u64))
                }

                Some(LiteralSuffix::I8) => TokenContents::Number(NumericConstant::I8(number as i8)),
                Some(LiteralSuffix::I16) => {
                    TokenContents::Number(NumericConstant::I16(number as i16))
                }
                Some(LiteralSuffix::I32) => {
                    TokenContents::Number(NumericConstant::I32(number as i32))
                }
                Some(LiteralSuffix::I64) => {
                    TokenContents::Number(NumericConstant::I64(number as i64))
                }

                Some(LiteralSuffix::F32) => {
                    TokenContents::Number(NumericConstant::F32(number as f32))
                }
                Some(LiteralSuffix::F64) => {
                    TokenContents::Number(NumericConstant::F64(number as f64))
                }

                _ => {
                    // FIXME: We should use a generic "integer" type here that stores i128, and infer the type later.
                    // For now, just check the size of the integer and create an i64 or u64.
                    if number > i64::MAX.into() {
                        if number <= u64::MAX.into() {
                            TokenContents::Number(NumericConstant::U64(number as u64))
                        } else {
                            error = Some(JaktError::ParserError(
                                format!("Integer literal {} too large", number),
                                span,
                            ));
                            TokenContents::Garbage
                        }
                    } else if number >= i64::MIN.into() {
                        TokenContents::Number(NumericConstant::I64(number as i64))
                    } else {
                        error = Some(JaktError::ParserError(
                            format!("Integer literal {} too small", number),
                            span,
                        ));
                        TokenContents::Garbage
                    }
                }
            };
            (token_contents, error)
        }
        NumberToken::Floating(number) => {
            let token_contents = match suffix {
                Some(LiteralSuffix::U8) => TokenContents::Number(NumericConstant::U8(number as u8)),
                Some(LiteralSuffix::U16) => {
                    TokenContents::Number(NumericConstant::U16(number as u16))
                }
                Some(LiteralSuffix::U32) => {
                    TokenContents::Number(NumericConstant::U32(number as u32))
                }

                // FIXME: This loses precision if usize is 64-bit
                Some(LiteralSuffix::UZ) => {
                    TokenContents::Number(NumericConstant::USize(number as u64))
                }

                // FIXME: This loses precision:
                Some(LiteralSuffix::U64) => {
                    TokenContents::Number(NumericConstant::U64(number as u64))
                }

                Some(LiteralSuffix::I8) => TokenContents::Number(NumericConstant::I8(number as i8)),
                Some(LiteralSuffix::I16) => {
                    TokenContents::Number(NumericConstant::I16(number as i16))
                }
                Some(LiteralSuffix::I32) => {
                    TokenContents::Number(NumericConstant::I32(number as i32))
                }
                Some(LiteralSuffix::I64) => {
                    TokenContents::Number(NumericConstant::I64(number as i64))
                }

                Some(LiteralSuffix::F32) => {
                    TokenContents::Number(NumericConstant::F32(number as f32))
                }
                Some(LiteralSuffix::F64) => {
                    TokenContents::Number(NumericConstant::F64(number as f64))
                }

                _ => TokenContents::Number(NumericConstant::F64(number as f64)),
            };
            (token_contents, error)
        }
    }
}

fn lex_item(file_id: FileId, bytes: &[u8], index: &mut usize) -> (Token, Option<JaktError>) {
    let mut error = None;

    if bytes[*index] == b'0' && *index + 2 < bytes.len() && bytes[*index + 1] == b'x' {
        // Hex number
        let start = *index;
        *index += 2;
        while *index < bytes.len() && bytes[*index].is_ascii_hexdigit()
            || (bytes[*index] == b'_' && bytes[*index - 1] != b'_')
        {
            *index += 1;
        }
        if bytes[*index - 1] == b'_' {
            return (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "hex number literal cannot end with underscore".to_string(),
                    Span::new(file_id, start, *index),
                )),
            );
        }
        let str = String::from_utf8_lossy(&bytes[start + 2..*index]).replace('_', "");
        let number = i128::from_str_radix(&str, 16);
        let suffix = consume_numeric_literal_suffix(bytes, index);
        let span = Span::new(file_id, start, *index);
        match number {
            Ok(number) => {
                let (token_contents, err) =
                    make_number_token(NumberToken::Integer(number), suffix, span);
                (Token::new(token_contents, span), err)
            }
            Err(_) => (
                Token::unknown(span),
                Some(JaktError::ParserError(
                    "could not parse hex number".to_string(),
                    span,
                )),
            ),
        }
    } else if bytes[*index] == b'0' && *index + 2 < bytes.len() && bytes[*index + 1] == b'o' {
        // Octal number
        let start = *index;
        *index += 2;
        while *index < bytes.len()
            && (bytes[*index].is_ascii_digit() && bytes[*index] != b'8' && bytes[*index] != b'9')
            || (bytes[*index] == b'_' && bytes[*index - 1] != b'_')
        {
            *index += 1;
        }
        let span = Span::new(file_id, start, *index);
        if bytes[*index - 1] == b'_' {
            return (
                Token::unknown(span),
                Some(JaktError::ParserError(
                    "octal number literal cannot end with underscore".to_string(),
                    Span::new(file_id, start, *index),
                )),
            );
        }

        if bytes[*index].is_ascii_digit() {
            return (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "could not parse octal number".to_string(),
                    Span::new(file_id, start, *index),
                )),
            );
        }

        let str = String::from_utf8_lossy(&bytes[start + 2..*index]).replace('_', "");
        let number = i128::from_str_radix(&str, 8);
        let suffix = consume_numeric_literal_suffix(bytes, index);
        let span = Span::new(file_id, start, *index);
        match number {
            Ok(number) => {
                let (token_contents, err) =
                    make_number_token(NumberToken::Integer(number), suffix, span);
                (Token::new(token_contents, span), err)
            }
            Err(_) => (
                Token::unknown(span),
                Some(JaktError::ParserError(
                    "could not parse octal number".to_string(),
                    span,
                )),
            ),
        }
    } else if bytes[*index] == b'0' && *index + 2 < bytes.len() && bytes[*index + 1] == b'b' {
        // Binary number
        let start = *index;
        *index += 2;
        while *index < bytes.len()
            && (bytes[*index] == b'0'
                || bytes[*index] == b'1'
                || (bytes[*index] == b'_' && bytes[*index - 1] != b'_'))
        {
            *index += 1;
        }
        if bytes[*index - 1] == b'_' {
            return (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "binary number literal cannot end with underscore".to_string(),
                    Span::new(file_id, start, *index),
                )),
            );
        }

        if bytes[*index].is_ascii_digit() {
            return (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "could not parse binary number".to_string(),
                    Span::new(file_id, start, *index),
                )),
            );
        }

        let str = String::from_utf8_lossy(&bytes[start + 2..*index]).replace('_', "");
        let number = i128::from_str_radix(&str, 2);
        let suffix = consume_numeric_literal_suffix(bytes, index);
        let span = Span::new(file_id, start, *index);
        match number {
            Ok(number) => {
                let (token_contents, err) =
                    make_number_token(NumberToken::Integer(number), suffix, span);
                (Token::new(token_contents, span), err)
            }
            Err(_) => (
                Token::unknown(span),
                Some(JaktError::ParserError(
                    "could not parse binary number".to_string(),
                    span,
                )),
            ),
        }
    } else if bytes[*index].is_ascii_digit() || bytes[*index] == b'_' {
        // Number
        let mut floating = false;
        let start = *index;
        while *index < bytes.len() && bytes[*index].is_ascii_digit()
            || (bytes[*index] == b'_' && bytes[*index - 1] != b'_')
        {
            *index += 1;
        }
        if bytes[*index - 1] == b'_' {
            return (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "number literal cannot end with underscore".to_string(),
                    Span::new(file_id, start, *index),
                )),
            );
        } else if bytes[*index] == b'.' && bytes[*index + 1].is_ascii_digit() {
            *index += 1;
            while *index < bytes.len() && bytes[*index].is_ascii_digit()
                || (bytes[*index] == b'_' && bytes[*index - 1] != b'_')
            {
                *index += 1;
            }
            floating = true;
        }

        let str = String::from_utf8_lossy(&bytes[start..*index]);

        if floating {
            let number: Result<f64, _> = str.replace('_', "").parse();
            let suffix = consume_numeric_literal_suffix(bytes, index);
            let span = Span::new(file_id, start, *index);
            match number {
                Ok(number) => {
                    let (token_contents, err) =
                        make_number_token(NumberToken::Floating(number), suffix, span);
                    (Token::new(token_contents, span), err)
                }
                Err(_) => (
                    Token::unknown(span),
                    Some(JaktError::ParserError(
                        "could not parse float".to_string(),
                        span,
                    )),
                ),
            }
        } else {
            let number: Result<i128, _> = str.replace('_', "").parse();
            let suffix = consume_numeric_literal_suffix(bytes, index);
            let span = Span::new(file_id, start, *index);
            match number {
                Ok(number) => {
                    let (token_contents, err) =
                        make_number_token(NumberToken::Integer(number), suffix, span);
                    (Token::new(token_contents, span), err)
                }
                Err(_) => (
                    Token::unknown(span),
                    Some(JaktError::ParserError(
                        "could not parse int".to_string(),
                        span,
                    )),
                ),
            }
        }
    } else if bytes[*index] == b'\''
        || (bytes[*index] == b'b' && *index + 1 < bytes.len() && bytes[*index + 1] == b'\'')
    {
        // 'c' Character literal
        // b'c' Byte literal (u8)

        let is_byte = if bytes[*index] == b'b' {
            *index += 1;
            true
        } else {
            false
        };

        let start = *index;
        *index += 1;

        let mut escaped = false;

        while *index < bytes.len() && (escaped || bytes[*index] != b'\'') {
            if !escaped && bytes[*index] == b'\\' {
                escaped = true;
            } else {
                escaped = false;
            }

            *index += 1;
        }

        if *index == bytes.len() || bytes[*index] != b'\'' {
            error = error.or(Some(JaktError::ParserError(
                "expected single quote".to_string(),
                Span::new(file_id, *index, *index),
            )));
        }

        // Everything but the quotes
        let str = String::from_utf8_lossy(&bytes[(start + 1)..(*index)]);

        *index += 1;

        let end = *index;

        let contents = match is_byte {
            true => TokenContents::SingleQuotedByteString(str.to_string()),
            false => TokenContents::SingleQuotedString(str.to_string()),
        };
        (Token::new(contents, Span::new(file_id, start, end)), error)
    } else if bytes[*index] == b'"' {
        // Quoted string

        let start = *index;
        *index += 1;

        let mut escaped = false;
        let mut found_newline = false;

        while *index < bytes.len() && (escaped || bytes[*index] != b'"') {
            // Ignore a standalone carriage return
            if bytes[*index] == b'\r' {
                *index += 1;
            }

            // Strings can't span multiple lines
            if bytes[*index] == b'\n' {
                found_newline = true;
                break;
            }

            if !escaped && bytes[*index] == b'\\' {
                escaped = true;
            } else {
                escaped = false;
            }

            *index += 1;
        }

        if found_newline {
            error = error.or(Some(JaktError::ParserError(
                "strings spanning multiple lines are not allowed".to_string(),
                Span::new(file_id, start, *index),
            )));
        }

        if *index == bytes.len() || bytes[*index] != b'"' {
            error = error.or(Some(JaktError::ParserError(
                "expected end quote".to_string(),
                Span::new(file_id, start, start + 1),
            )));
        }

        // Everything but the quotes
        let str = String::from_utf8_lossy(&bytes[(start + 1)..(*index)]);

        *index += 1;

        let end = *index;

        (
            Token::new(
                TokenContents::QuotedString(str.to_string()),
                Span::new(file_id, start, end),
            ),
            error,
        )
    } else if bytes[*index].is_ascii_alphabetic() || bytes[*index] == b'_' {
        // Symbol name
        let start = *index;
        *index += 1;

        let mut escaped = false;

        while *index < bytes.len()
            && (bytes[*index].is_ascii_alphanumeric() || (bytes[*index] == b'_'))
        {
            if !escaped && bytes[*index] == b'\\' {
                escaped = true;
            } else {
                escaped = false;
            }

            *index += 1;
        }

        // Everything but the quotes
        let str = String::from_utf8_lossy(&bytes[start..*index]);

        (
            Token::new(
                TokenContents::Name(str.to_string()),
                Span::new(file_id, start, *index),
            ),
            error,
        )
    } else {
        let span = Span::new(file_id, *index, *index + 1);

        error = error.or(Some(JaktError::ParserError(
            "unknown character".to_string(),
            span,
        )));

        *index += 1;

        (Token::unknown(span), error)
    }
}
