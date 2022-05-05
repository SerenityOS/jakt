use crate::{
    compiler::FileId,
    error::JaktError,
    parser::{Span, Token, TokenContents},
};

pub fn lex(file_id: FileId, bytes: &[u8]) -> Result<Vec<Token>, JaktError> {
    let mut output = Vec::new();
    let mut index = 0;

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
        } else if c == b'-' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::Minus,
                Span::new(file_id, start, start + 1),
            ));
        } else if c == b'>' {
            let start = index;
            index += 1;
            output.push(Token::new(
                TokenContents::GreaterThan,
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

            let token = lex_item(file_id, bytes, &mut index)?;

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

    Ok(output)
}

fn lex_item(file_id: FileId, bytes: &[u8], index: &mut usize) -> Result<Token, JaktError> {
    if bytes[*index].is_ascii_digit() {
        // Number
        let start = *index;
        while *index < bytes.len() && bytes[*index].is_ascii_digit() {
            *index += 1;
        }

        let str = String::from_utf8_lossy(&bytes[start..*index]);
        let number: Result<i64, _> = str.parse();

        match number {
            Ok(number) => Ok(Token::new(
                TokenContents::Number(number),
                Span::new(file_id, start, *index),
            )),
            Err(_) => Err(JaktError::ParserError(
                "could not parse int".to_string(),
                Span::new(file_id, start, *index),
            )),
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
            return Err(JaktError::ParserError(
                "Expected quote".to_string(),
                Span::new(file_id, *index, *index),
            ));
        }

        // Everything but the quotes
        let str = String::from_utf8_lossy(&bytes[(start + 1)..(*index)]);

        let end = *index;
        *index += 1;

        Ok(Token::new(
            TokenContents::QuotedString(str.to_string()),
            Span::new(file_id, start, end),
        ))
    } else {
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

        Ok(Token::new(
            TokenContents::Name(str.to_string()),
            Span::new(file_id, start, *index),
        ))
    }
}
