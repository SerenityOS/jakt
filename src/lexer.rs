use crate::{
    compiler::FileId,
    error::JaktError,
    parser::{Span, Token, TokenContents},
};

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
            output.push(Token::new(
                TokenContents::Plus,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'-' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Minus,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'*' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Asterisk,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'/' {
            let start = index;
            index += 1;
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
                        Span::new(file_id, start, start + 1),
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
                        Span::new(file_id, start, start + 1),
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
                        Span::new(file_id, start, start + 1),
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
                        Span::new(file_id, start, start + 1),
                    ));
                    continue;
                }
            }
            output.push(Token::new(
                TokenContents::ExclamationPoint,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b',' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Comma,
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

    if bytes[*index].is_ascii_digit() {
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
                "Expected quote".to_string(),
                Span::new(file_id, *index, *index),
            )));
        }

        // Everything but the quotes
        let str = String::from_utf8_lossy(&bytes[(start + 1)..(*index)]);

        let end = *index;
        *index += 1;

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
