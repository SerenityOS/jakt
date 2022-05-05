use crate::{compiler::FileId, error::JaktError};

#[derive(Debug)]
pub struct Call {
    pub name: String,
    pub params: Vec<(String, Expression)>,
}

impl Call {
    pub fn new() -> Self {
        Self {
            name: String::new(),
            params: Vec::new(),
        }
    }
}

#[derive(Debug, Clone, Copy)]
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
    LParen,
    RParen,
    LCurly,
    RCurly,
    Eol,
    Eof,
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
}

#[derive(Debug)]
pub struct ParsedFile {
    pub funs: Vec<Function>,
}

#[derive(Debug)]
pub struct Function {
    pub name: String,
    pub params: Vec<Parameter>,
    pub block: Block,
}

#[derive(Debug)]
pub struct Parameter {
    pub name: String,
}

#[derive(Debug)]
pub struct Block {
    pub stmts: Vec<Expression>,
}

impl Block {
    pub fn new() -> Self {
        Self { stmts: Vec::new() }
    }
}

#[derive(Debug)]
pub enum Expression {
    Call(Call),
    QuotedString(String),
}

impl ParsedFile {
    pub fn new() -> Self {
        Self { funs: Vec::new() }
    }
}

pub fn parse_file(tokens: &[Token]) -> Result<ParsedFile, JaktError> {
    let mut parsed_file = ParsedFile::new();

    let mut index = 0;

    while index < tokens.len() {
        let token = &tokens[index];

        match token {
            Token {
                contents: TokenContents::Name(name),
                span,
            } => match name.as_str() {
                "fun" => {
                    let fun = parse_function(tokens, &mut index)?;
                    parsed_file.funs.push(fun);
                }
                _ => {
                    return Err(JaktError::ParserError(
                        "unexpected keyword".to_string(),
                        *span,
                    ))
                }
            },
            Token {
                contents: TokenContents::Eol,
                ..
            } => {
                //ignore
                index += 1;
            }
            Token {
                contents: TokenContents::Eof,
                ..
            } => {
                break;
            }
            Token { span, .. } => {
                return Err(JaktError::ParserError(
                    "unexpected token (expected keyword)".to_string(),
                    *span,
                ));
            }
        }
    }

    Ok(parsed_file)
}

pub fn parse_function(tokens: &[Token], index: &mut usize) -> Result<Function, JaktError> {
    *index += 1;

    if *index < tokens.len() {
        // we're expecting the name of the function
        match &tokens[*index] {
            Token {
                contents: TokenContents::Name(fun_name),
                ..
            } => {
                // Good, we have the function name
                // for now skip skip
                // TODO: actually parse params
                *index += 3;

                let block = parse_block(tokens, index)?;

                return Ok(Function {
                    name: fun_name.clone(),
                    params: Vec::new(),
                    block,
                });
            }
            _ => Err(JaktError::ParserError(
                "expected function name".to_string(),
                tokens[*index].span,
            )),
        }
    } else {
        Err(JaktError::ParserError(
            "incomplete function definition".to_string(),
            tokens[*index].span,
        ))
    }
}

pub fn parse_block(tokens: &[Token], index: &mut usize) -> Result<Block, JaktError> {
    let mut block = Block::new();

    *index += 1;

    while *index < tokens.len() {
        match tokens[*index] {
            Token {
                contents: TokenContents::RCurly,
                ..
            } => {
                *index += 1;
                return Ok(block);
            }
            Token {
                contents: TokenContents::Semicolon,
                ..
            } => {
                *index += 1;
            }
            Token {
                contents: TokenContents::Eol,
                ..
            } => {
                *index += 1;
            }
            _ => {
                let expr = parse_expression(tokens, index)?;
                block.stmts.push(expr);
                *index += 1;
            }
        }
    }

    Err(JaktError::ParserError(
        "expected complete block".to_string(),
        tokens[(*index - 1)].span,
    ))
}

pub fn parse_expression(tokens: &[Token], index: &mut usize) -> Result<Expression, JaktError> {
    match tokens[*index] {
        Token {
            contents: TokenContents::Name(_),
            ..
        } => {
            let call: Call = parse_call(tokens, index)?;

            Ok(Expression::Call(call))
        }
        Token { span, .. } => {
            println!("{:?}", tokens[*index]);
            Err(JaktError::ParserError(
                "unsupported expression".to_string(),
                span,
            ))
        }
    }
}

pub fn parse_call(tokens: &[Token], index: &mut usize) -> Result<Call, JaktError> {
    let mut call = Call::new();

    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            span,
        } => {
            if name == "print" {
                // Good, we know this one
                call.name = "print".to_string();
            } else {
                return Err(JaktError::ParserError(
                    "unknown function".to_string(),
                    *span,
                ));
            }

            *index += 1;

            if *index < tokens.len() {
                match tokens[*index] {
                    Token {
                        contents: TokenContents::LParen,
                        ..
                    } => {
                        *index += 1;
                    }
                    _ => {
                        return Err(JaktError::ParserError("expected '('".to_string(), *span));
                    }
                }
            } else {
                return Err(JaktError::ParserError(
                    "incomplete function".to_string(),
                    tokens[*index - 1].span,
                ));
            }

            if *index < tokens.len() {
                match &tokens[*index] {
                    Token {
                        contents: TokenContents::QuotedString(contents),
                        ..
                    } => {
                        call.params.push((
                            "msg".to_string(),
                            Expression::QuotedString(contents.to_string()),
                        ));
                        *index += 1;
                    }
                    _ => {
                        return Err(JaktError::ParserError("expected '('".to_string(), *span));
                    }
                }
            } else {
                return Err(JaktError::ParserError(
                    "incomplete function".to_string(),
                    tokens[*index - 1].span,
                ));
            }

            if *index < tokens.len() {
                match tokens[*index] {
                    Token {
                        contents: TokenContents::RParen,
                        ..
                    } => {
                        *index += 1;
                    }
                    _ => {
                        return Err(JaktError::ParserError("expected ')'".to_string(), *span));
                    }
                }
            } else {
                return Err(JaktError::ParserError(
                    "incomplete function".to_string(),
                    tokens[*index - 1].span,
                ));
            }

            Ok(call)
        }
        _ => Err(JaktError::ParserError(
            "expected function call".to_string(),
            tokens[*index].span,
        )),
    }
}
