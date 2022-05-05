use crate::{compiler::FileId, error::JaktError};

#[derive(Debug)]
pub struct Call {
    pub name: String,
    pub args: Vec<(String, Expression)>,
}

impl Call {
    pub fn new() -> Self {
        Self {
            name: String::new(),
            args: Vec::new(),
        }
    }
}

#[derive(Debug)]
pub enum Type {
    String,
    I64,
    Void,
}

#[derive(Debug)]
pub struct VarDecl {
    pub name: String,
    pub ty: Type,
    pub mutable: bool,
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
    Colon,
    LParen,
    RParen,
    LCurly,
    RCurly,
    Minus,
    Equals,
    GreaterThan,
    Comma,
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
    pub params: Vec<(String, Type)>,
    pub block: Block,
    pub return_type: Type,
}

#[derive(Debug)]
pub enum Statement {
    Expression(Expression),
    Defer(Block),
    VarDecl(VarDecl, Expression),
    Return(Expression),
}

#[derive(Debug)]
pub struct Block {
    pub stmts: Vec<Statement>,
}

impl Block {
    pub fn new() -> Self {
        Self { stmts: Vec::new() }
    }
}

#[derive(Debug)]
pub enum Expression {
    Call(Call),
    Int64(i64),
    QuotedString(String),
    Var(String),
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
                            return Err(JaktError::ParserError(
                                "expected '('".to_string(),
                                tokens[*index].span,
                            ));
                        }
                    }
                } else {
                    return Err(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    ));
                }

                let mut params = Vec::new();

                while *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::RParen => {
                            *index += 1;
                            break;
                        }
                        TokenContents::Comma => {
                            // Treat comma as whitespace? Might require them in the future
                            *index += 1;
                        }

                        TokenContents::Name(..) => {
                            // Now lets parse a parameter

                            let var_decl = parse_variable_declaration(tokens, index)?;

                            params.push((var_decl.name, var_decl.ty));
                        }
                        _ => {
                            return Err(JaktError::ParserError(
                                "expected parameter".to_string(),
                                tokens[*index].span,
                            ));
                        }
                    }
                }

                if *index >= tokens.len() {
                    return Err(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    ));
                }

                let mut return_type = Type::Void;

                if *index + 2 < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Minus => {
                            *index += 1;

                            match &tokens[*index].contents {
                                TokenContents::GreaterThan => {
                                    *index += 1;

                                    return_type = parse_typename(tokens, index)?;
                                    *index += 1;
                                }
                                _ => {
                                    return Err(JaktError::ParserError(
                                        "expected ->".to_string(),
                                        tokens[*index - 1].span,
                                    ))
                                }
                            }
                        }
                        _ => {}
                    }
                }

                if *index >= tokens.len() {
                    return Err(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    ));
                }

                let block = parse_block(tokens, index)?;

                return Ok(Function {
                    name: fun_name.clone(),
                    params,
                    block,
                    return_type,
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
                let stmt = parse_statement(tokens, index)?;
                block.stmts.push(stmt);
                *index += 1;
            }
        }
    }

    Err(JaktError::ParserError(
        "expected complete block".to_string(),
        tokens[(*index - 1)].span,
    ))
}

pub fn parse_statement(tokens: &[Token], index: &mut usize) -> Result<Statement, JaktError> {
    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            ..
        } if name.as_str() == "defer" => {
            *index += 1;
            let block = parse_block(tokens, index)?;
            Ok(Statement::Defer(block))
        }
        Token {
            contents: TokenContents::Name(name),
            ..
        } if name.as_str() == "return" => {
            *index += 1;
            let expr = parse_expression(tokens, index)?;
            Ok(Statement::Return(expr))
        }
        Token {
            contents: TokenContents::Name(name),
            ..
        } if name.as_str() == "let" || name.as_str() == "var" => {
            let mutable = name == "var";

            *index += 1;

            let mut var_decl = parse_variable_declaration(tokens, index)?;
            var_decl.mutable = mutable;

            // Hardwire an initialiser for now, but we may not want this long-term
            if *index < tokens.len() {
                match &tokens[*index].contents {
                    TokenContents::Equals => {
                        *index += 1;

                        if *index < tokens.len() {
                            let expr = parse_expression(tokens, index)?;

                            Ok(Statement::VarDecl(var_decl, expr))
                        } else {
                            Err(JaktError::ParserError(
                                "expected initializer".to_string(),
                                tokens[*index - 1].span,
                            ))
                        }
                    }
                    _ => Err(JaktError::ParserError(
                        "expected initializer".to_string(),
                        tokens[*index].span,
                    )),
                }
            } else {
                Err(JaktError::ParserError(
                    "expected initializer".to_string(),
                    tokens[*index].span,
                ))
            }
        }
        _ => {
            let expr = parse_expression(&tokens, index)?;
            Ok(Statement::Expression(expr))
        }
    }
}

pub fn parse_expression(tokens: &[Token], index: &mut usize) -> Result<Expression, JaktError> {
    match &tokens[*index].contents {
        TokenContents::Name(name) => {
            if *index + 1 < tokens.len() {
                match &tokens[*index + 1].contents {
                    TokenContents::LParen => {
                        let call: Call = parse_call(tokens, index)?;

                        return Ok(Expression::Call(call));
                    }
                    _ => {}
                }
            }

            *index += 1;

            Ok(Expression::Var(name.to_string()))
        }
        TokenContents::Number(number) => {
            *index += 1;
            Ok(Expression::Int64(*number))
        }
        TokenContents::QuotedString(str) => {
            *index += 1;
            Ok(Expression::QuotedString(str.to_string()))
        }
        _ => Err(JaktError::ParserError(
            "unsupported expression".to_string(),
            tokens[*index].span,
        )),
    }
}

pub fn parse_variable_declaration(
    tokens: &[Token],
    index: &mut usize,
) -> Result<VarDecl, JaktError> {
    match &tokens[*index].contents {
        TokenContents::Name(name) => {
            let var_name = name.to_string();

            *index += 1;

            if *index < tokens.len() {
                match &tokens[*index].contents {
                    TokenContents::Colon => {
                        *index += 1;
                    }
                    _ => {
                        return Err(JaktError::ParserError(
                            "expected ':'".to_string(),
                            tokens[*index].span,
                        ));
                    }
                }
            }

            if *index < tokens.len() {
                let var_type = parse_typename(tokens, index)?;
                let result = VarDecl {
                    name: var_name,
                    ty: var_type,
                    mutable: false,
                };

                *index += 1;

                Ok(result)
            } else {
                Err(JaktError::ParserError(
                    "expected type".to_string(),
                    tokens[*index].span,
                ))
            }
        }
        _ => Err(JaktError::ParserError(
            "expected type".to_string(),
            tokens[*index].span,
        )),
    }
}

pub fn parse_typename(tokens: &[Token], index: &mut usize) -> Result<Type, JaktError> {
    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            span,
        } => match name.as_str() {
            "i64" => Ok(Type::I64),
            "String" => Ok(Type::String),
            _ => Err(JaktError::ParserError("unknown type".to_string(), *span)),
        },
        _ => Err(JaktError::ParserError(
            "expected function call".to_string(),
            tokens[*index].span,
        )),
    }
}

pub fn parse_call(tokens: &[Token], index: &mut usize) -> Result<Call, JaktError> {
    let mut call = Call::new();

    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            ..
        } => {
            call.name = name.to_string();

            *index += 1;

            if *index < tokens.len() {
                match &tokens[*index] {
                    Token {
                        contents: TokenContents::LParen,
                        ..
                    } => {
                        *index += 1;
                    }
                    Token { span, .. } => {
                        return Err(JaktError::ParserError("expected '('".to_string(), *span));
                    }
                }
            } else {
                return Err(JaktError::ParserError(
                    "incomplete function".to_string(),
                    tokens[*index - 1].span,
                ));
            }

            while *index < tokens.len() {
                match &tokens[*index].contents {
                    TokenContents::RParen => {
                        *index += 1;
                        break;
                    }
                    TokenContents::Comma => {
                        // Treat comma as whitespace? Might require them in the future
                        *index += 1;
                    }
                    _ => {
                        let expr = parse_expression(tokens, index)?;
                        call.args.push((String::new(), expr));
                    }
                }
            }

            if *index >= tokens.len() {
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
