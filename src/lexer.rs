use crate::{compiler::FileId, error::JaktError, typechecker::NumericConstant};

#[derive(Debug, Clone, Copy, PartialEq)]
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
}

#[derive(Debug, PartialEq)]
pub enum TokenContents {
    SingleQuotedString(String),
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
    LeftShift,
    LeftShiftEqual,
    RightShift,
    RightShiftEqual,
    Asterisk,
    Ampersand,
    AmpersandEqual,
    Pipe,
    PipeEqual,
    Caret,
    CaretEqual,
    Tilde,
    ForwardSlash,
    ExclamationPoint,
    QuestionMark,
    Comma,
    Dot,
    Eol,
    Eof,

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

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::AsteriskEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
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
            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::NotEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }
            output.push(Token::new(
                TokenContents::ExclamationPoint,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'&' {
            let start = index;
            index += 1;

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::AmpersandEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }
            output.push(Token::new(
                TokenContents::Ampersand,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'|' {
            let start = index;
            index += 1;

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::PipeEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }

            output.push(Token::new(
                TokenContents::Pipe,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'^' {
            let start = index;
            index += 1;

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::CaretEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }

            output.push(Token::new(
                TokenContents::Caret,
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

            if index < bytes.len() {
                if bytes[index] == b'=' {
                    index += 1;
                    output.push(Token::new(
                        TokenContents::PercentSignEqual,
                        Span::new(file_id, start, start + 2),
                    ));
                    continue;
                }
            }

            output.push(Token::new(
                TokenContents::PercentSign,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'?' {
            let start = index;
            index += 1;
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

fn consume_numeric_literal_suffix(bytes: &[u8], index: &mut usize) -> Option<LiteralSuffix> {
    match bytes[*index] {
        b'u' | b'i' | b'f' => {}
        _ => return None,
    }

    let mut local_index = *index + 1;
    if local_index >= bytes.len() {
        return None;
    }

    let start = local_index;
    while local_index < bytes.len() && bytes[local_index].is_ascii_digit() {
        local_index += 1;
    }
    let str = String::from_utf8_lossy(&bytes[start..local_index]);
    let width = i64::from_str_radix(&str, 10).ok();

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

fn make_number_token(number: i64, suffix: Option<LiteralSuffix>) -> TokenContents {
    match suffix {
        Some(LiteralSuffix::U8) => TokenContents::Number(NumericConstant::U8(number as u8)),
        Some(LiteralSuffix::U16) => TokenContents::Number(NumericConstant::U16(number as u16)),
        Some(LiteralSuffix::U32) => TokenContents::Number(NumericConstant::U32(number as u32)),

        // FIXME: This loses precision:
        Some(LiteralSuffix::U64) => TokenContents::Number(NumericConstant::U64(number as u64)),

        Some(LiteralSuffix::I8) => TokenContents::Number(NumericConstant::I8(number as i8)),
        Some(LiteralSuffix::I16) => TokenContents::Number(NumericConstant::I16(number as i16)),
        Some(LiteralSuffix::I32) => TokenContents::Number(NumericConstant::I32(number as i32)),
        Some(LiteralSuffix::I64) => TokenContents::Number(NumericConstant::I64(number)),

        // FIXME: These 2 don't work at all:
        Some(LiteralSuffix::F32) => TokenContents::Number(NumericConstant::I64(number as i64)),
        Some(LiteralSuffix::F64) => TokenContents::Number(NumericConstant::I64(number as i64)),

        _ => TokenContents::Number(NumericConstant::I64(number)),
    }
}

fn lex_item(file_id: FileId, bytes: &[u8], index: &mut usize) -> (Token, Option<JaktError>) {
    let mut error = None;

    if bytes[*index] == b'0' && *index + 2 < bytes.len() && bytes[*index + 1] == b'x' {
        // Hex number
        let start = *index;
        *index += 2;
        while *index < bytes.len() && bytes[*index].is_ascii_hexdigit() {
            *index += 1;
        }
        let str = String::from_utf8_lossy(&bytes[start + 2..*index]);
        let number = i64::from_str_radix(&str, 16);
        let suffix = consume_numeric_literal_suffix(bytes, index);
        match number {
            Ok(number) => (
                Token::new(
                    make_number_token(number, suffix),
                    Span::new(file_id, start, *index),
                ),
                None,
            ),
            Err(_) => (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "could not parse hex".to_string(),
                    Span::new(file_id, start, *index),
                )),
            ),
        }
    } else if bytes[*index] == b'0' && *index + 2 < bytes.len() && bytes[*index + 1] == b'b' {
        // Binary number
        let start = *index;
        *index += 2;
        while *index < bytes.len() && (bytes[*index] == b'0' || bytes[*index] == b'1') {
            *index += 1;
        }
        let str = String::from_utf8_lossy(&bytes[start + 2..*index]);
        let number = i64::from_str_radix(&str, 2);
        let suffix = consume_numeric_literal_suffix(bytes, index);
        match number {
            Ok(number) => (
                Token::new(
                    make_number_token(number, suffix),
                    Span::new(file_id, start, *index),
                ),
                None,
            ),
            Err(_) => (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "could not parse binary number".to_string(),
                    Span::new(file_id, start, *index),
                )),
            ),
        }
    } else if bytes[*index].is_ascii_digit() {
        // Number
        let start = *index;
        while *index < bytes.len() && bytes[*index].is_ascii_digit() {
            *index += 1;
        }

        let str = String::from_utf8_lossy(&bytes[start..*index]);
        let number: Result<i64, _> = str.parse();
        let suffix = consume_numeric_literal_suffix(bytes, index);
        match number {
            Ok(number) => (
                Token::new(
                    make_number_token(number, suffix),
                    Span::new(file_id, start, *index),
                ),
                None,
            ),
            Err(_) => (
                Token::unknown(Span::new(file_id, start, *index)),
                Some(JaktError::ParserError(
                    "could not parse int".to_string(),
                    Span::new(file_id, start, *index),
                )),
            ),
        }
    } else if bytes[*index] == b'\'' {
        // Character

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

        (
            Token::new(
                TokenContents::SingleQuotedString(str.to_string()),
                Span::new(file_id, start, end),
            ),
            error,
        )
    } else if bytes[*index] == b'"' {
        // Quoted string

        let start = *index;
        *index += 1;

        let mut escaped = false;

        while *index < bytes.len() && (escaped || bytes[*index] != b'"') {
            if !escaped && bytes[*index] == b'\\' {
                escaped = true;
            } else {
                escaped = false;
            }

            *index += 1;
        }

        if *index == bytes.len() || bytes[*index] != b'"' {
            error = error.or(Some(JaktError::ParserError(
                "expected quote".to_string(),
                Span::new(file_id, *index, *index),
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
