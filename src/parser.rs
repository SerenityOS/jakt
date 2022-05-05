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

impl VarDecl {
    pub fn new() -> Self {
        Self {
            name: String::new(),
            ty: Type::Void,
            mutable: false,
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

impl Function {
    pub fn new() -> Self {
        Function {
            name: String::new(),
            params: Vec::new(),
            block: Block::new(),
            return_type: Type::Void,
        }
    }
}

#[derive(Debug)]
pub enum Statement {
    Expression(Expression),
    Defer(Block),
    VarDecl(VarDecl, Expression),
    Return(Expression),
    Garbage,
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
    Garbage,
}

impl ParsedFile {
    pub fn new() -> Self {
        Self { funs: Vec::new() }
    }
}

pub fn parse_file(tokens: &[Token]) -> (ParsedFile, Option<JaktError>) {
    let mut error = None;

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
                    let (fun, err) = parse_function(tokens, &mut index);
                    error = error.or(err);

                    parsed_file.funs.push(fun);
                }
                _ => {
                    error = error.or(Some(JaktError::ParserError(
                        "unexpected keyword".to_string(),
                        *span,
                    )));
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
                error = error.or(Some(JaktError::ParserError(
                    "unexpected token (expected keyword)".to_string(),
                    *span,
                )));
            }
        }
    }

    (parsed_file, error)
}

pub fn parse_function(tokens: &[Token], index: &mut usize) -> (Function, Option<JaktError>) {
    let mut error = None;

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
                            error = error.or(Some(JaktError::ParserError(
                                "expected '('".to_string(),
                                tokens[*index].span,
                            )));
                        }
                    }
                } else {
                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )));
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

                            let (var_decl, err) = parse_variable_declaration(tokens, index);
                            error = error.or(err);

                            params.push((var_decl.name, var_decl.ty));
                        }
                        _ => {
                            error = error.or(Some(JaktError::ParserError(
                                "expected parameter".to_string(),
                                tokens[*index].span,
                            )));
                        }
                    }
                }

                if *index >= tokens.len() {
                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                let mut return_type = Type::Void;

                if *index + 2 < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Minus => {
                            *index += 1;

                            match &tokens[*index].contents {
                                TokenContents::GreaterThan => {
                                    *index += 1;

                                    let (ret_type, err) = parse_typename(tokens, index);
                                    return_type = ret_type;
                                    error = error.or(err);

                                    *index += 1;
                                }
                                _ => {
                                    error = error.or(Some(JaktError::ParserError(
                                        "expected ->".to_string(),
                                        tokens[*index - 1].span,
                                    )));
                                }
                            }
                        }
                        _ => {}
                    }
                }

                if *index >= tokens.len() {
                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                let (block, err) = parse_block(tokens, index);
                error = error.or(err);

                return (
                    Function {
                        name: fun_name.clone(),
                        params,
                        block,
                        return_type,
                    },
                    error,
                );
            }
            _ => (
                Function::new(),
                Some(JaktError::ParserError(
                    "expected function name".to_string(),
                    tokens[*index].span,
                )),
            ),
        }
    } else {
        (
            Function::new(),
            Some(JaktError::ParserError(
                "incomplete function definition".to_string(),
                tokens[*index].span,
            )),
        )
    }
}

pub fn parse_block(tokens: &[Token], index: &mut usize) -> (Block, Option<JaktError>) {
    let mut block = Block::new();
    let mut error = None;

    *index += 1;

    while *index < tokens.len() {
        match tokens[*index] {
            Token {
                contents: TokenContents::RCurly,
                ..
            } => {
                *index += 1;
                return (block, error);
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
                let (stmt, err) = parse_statement(tokens, index);
                error = error.or(err);

                block.stmts.push(stmt);
                *index += 1;
            }
        }
    }

    (
        Block::new(),
        Some(JaktError::ParserError(
            "expected complete block".to_string(),
            tokens[(*index - 1)].span,
        )),
    )
}

pub fn parse_statement(tokens: &[Token], index: &mut usize) -> (Statement, Option<JaktError>) {
    let mut error = None;

    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            ..
        } if name.as_str() == "defer" => {
            *index += 1;
            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::Defer(block), error)
        }
        Token {
            contents: TokenContents::Name(name),
            ..
        } if name.as_str() == "return" => {
            *index += 1;
            let (expr, err) = parse_expression(tokens, index);
            error = error.or(err);

            (Statement::Return(expr), error)
        }
        Token {
            contents: TokenContents::Name(name),
            ..
        } if name.as_str() == "let" || name.as_str() == "var" => {
            let mutable = name == "var";

            *index += 1;

            let (mut var_decl, err) = parse_variable_declaration(tokens, index);
            error = error.or(err);

            var_decl.mutable = mutable;

            // Hardwire an initialiser for now, but we may not want this long-term
            if *index < tokens.len() {
                match &tokens[*index].contents {
                    TokenContents::Equals => {
                        *index += 1;

                        if *index < tokens.len() {
                            let (expr, err) = parse_expression(tokens, index);
                            error = error.or(err);

                            (Statement::VarDecl(var_decl, expr), error)
                        } else {
                            (
                                Statement::Garbage,
                                Some(JaktError::ParserError(
                                    "expected initializer".to_string(),
                                    tokens[*index - 1].span,
                                )),
                            )
                        }
                    }
                    _ => (
                        Statement::Garbage,
                        Some(JaktError::ParserError(
                            "expected initializer".to_string(),
                            tokens[*index].span,
                        )),
                    ),
                }
            } else {
                (
                    Statement::Garbage,
                    Some(JaktError::ParserError(
                        "expected initializer".to_string(),
                        tokens[*index].span,
                    )),
                )
            }
        }
        _ => {
            let (expr, err) = parse_expression(&tokens, index);
            error = error.or(err);

            (Statement::Expression(expr), error)
        }
    }
}

pub fn parse_expression(tokens: &[Token], index: &mut usize) -> (Expression, Option<JaktError>) {
    let mut error = None;

    match &tokens[*index].contents {
        TokenContents::Name(name) => {
            if *index + 1 < tokens.len() {
                match &tokens[*index + 1].contents {
                    TokenContents::LParen => {
                        let (call, err) = parse_call(tokens, index);
                        error = error.or(err);

                        return (Expression::Call(call), error);
                    }
                    _ => {}
                }
            }

            *index += 1;

            (Expression::Var(name.to_string()), error)
        }
        TokenContents::Number(number) => {
            *index += 1;
            (Expression::Int64(*number), error)
        }
        TokenContents::QuotedString(str) => {
            *index += 1;
            (Expression::QuotedString(str.to_string()), error)
        }
        _ => (
            Expression::Garbage,
            Some(JaktError::ParserError(
                "unsupported expression".to_string(),
                tokens[*index].span,
            )),
        ),
    }
}

pub fn parse_variable_declaration(
    tokens: &[Token],
    index: &mut usize,
) -> (VarDecl, Option<JaktError>) {
    let mut error = None;

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
                        (
                            VarDecl::new(),
                            (JaktError::ParserError(
                                "expected ':'".to_string(),
                                tokens[*index].span,
                            )),
                        );
                    }
                }
            }

            if *index < tokens.len() {
                let (var_type, err) = parse_typename(tokens, index);
                error = error.or(err);

                let result = VarDecl {
                    name: var_name,
                    ty: var_type,
                    mutable: false,
                };

                *index += 1;

                (result, error)
            } else {
                (
                    VarDecl {
                        name: name.to_string(),
                        ty: Type::Void,
                        mutable: false,
                    },
                    Some(JaktError::ParserError(
                        "expected type".to_string(),
                        tokens[*index].span,
                    )),
                )
            }
        }
        _ => (
            VarDecl::new(),
            Some(JaktError::ParserError(
                "expected name".to_string(),
                tokens[*index].span,
            )),
        ),
    }
}

pub fn parse_typename(tokens: &[Token], index: &mut usize) -> (Type, Option<JaktError>) {
    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            span,
        } => match name.as_str() {
            "i64" => (Type::I64, None),
            "String" => (Type::String, None),
            _ => (
                Type::Void,
                Some(JaktError::ParserError("unknown type".to_string(), *span)),
            ),
        },
        _ => (
            Type::Void,
            Some(JaktError::ParserError(
                "expected function call".to_string(),
                tokens[*index].span,
            )),
        ),
    }
}

pub fn parse_call(tokens: &[Token], index: &mut usize) -> (Call, Option<JaktError>) {
    let mut call = Call::new();
    let mut error = None;

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
                        return (
                            call,
                            Some(JaktError::ParserError("expected '('".to_string(), *span)),
                        );
                    }
                }
            } else {
                return (
                    call,
                    Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )),
                );
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
                        let (expr, err) = parse_expression(tokens, index);
                        error = error.or(err);

                        call.args.push((String::new(), expr));
                    }
                }
            }

            if *index >= tokens.len() {
                error = error.or(Some(JaktError::ParserError(
                    "incomplete call".to_string(),
                    tokens[*index - 1].span,
                )));
            }
        }
        _ => {
            error = error.or(Some(JaktError::ParserError(
                "expected function call".to_string(),
                tokens[*index].span,
            )));
        }
    }
    (call, error)
}
