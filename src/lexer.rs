use crate::{compiler::FileId, error::JaktError};

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

#[derive(Debug)]
pub enum TokenContents {
    QuotedString(String),
    Number(i64),
    Name(String),
    Semicolon,
    Colon,
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
    Asterisk,
    Ampersand,
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
            output.push(Token::new(
                TokenContents::Colon,
                Span::new(file_id, start, start + 1),
            ));
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
            output.push(Token::new(
                TokenContents::Ampersand,
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
        match number {
            Ok(number) => (
                Token::new(
                    TokenContents::Number(number),
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
        match number {
            Ok(number) => (
                Token::new(
                    TokenContents::Number(number),
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

        match number {
            Ok(number) => (
                Token::new(
                    TokenContents::Number(number),
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
