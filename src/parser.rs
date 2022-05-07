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

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum ExpressionKind {
    ExpressionWithAssignments,
    ExpressionWithoutAssignment,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Type {
    Bool,
    String,
    I8,
    I16,
    I32,
    I64,
    U8,
    U16,
    U32,
    U64,
    F32,
    F64,
    Void,
    Unknown,
}

#[derive(Debug, Clone)]
pub struct VarDecl {
    pub name: String,
    pub ty: Type,
    pub mutable: bool,
    pub span: Span,
}

impl VarDecl {
    pub fn new(span: Span) -> Self {
        Self {
            name: String::new(),
            ty: Type::Void,
            mutable: false,
            span,
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
    Plus,
    Minus,
    Equal,
    PlusEqual,
    MinusEqual,
    AsteriskEqual,
    ForwardSlashEqual,
    NotEqual,
    DoubleEqual,
    GreaterThan,
    GreaterThanOrEqual,
    LessThan,
    LessThanOrEqual,
    Asterisk,
    ForwardSlash,
    ExclamationPoint,
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
    pub params: Vec<Variable>,
    pub block: Block,
    pub return_type: Type,
}

#[derive(Clone, Debug)]
pub struct Variable {
    pub name: String,
    pub ty: Type,
    pub mutable: bool,
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
    If(Expression, Block, Option<Box<Statement>>),
    Block(Block),
    While(Expression, Block),
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

// TODO: add spans to individual expressions
// so we can give better errors during typecheck
#[derive(Debug)]
pub enum Expression {
    // Standalone
    Boolean(bool, Span),
    Call(Call, Span),
    Int64(i64, Span),
    QuotedString(String, Span),
    BinaryOp(Box<Expression>, Box<Expression>, Box<Expression>),
    Var(String, Span),

    // Not standalone
    Operator(Operator, Span),

    // Parsing error
    Garbage(Span),
}

impl Expression {
    pub fn span(&self) -> Span {
        match self {
            Expression::Boolean(_, span) => *span,
            Expression::Call(_, span) => *span,
            Expression::Int64(_, span) => *span,
            Expression::QuotedString(_, span) => *span,
            Expression::BinaryOp(_, op, _) => op.span(),
            Expression::Var(_, span) => *span,
            Expression::Operator(_, span) => *span,
            Expression::Garbage(span) => *span,
        }
    }
}

#[derive(Debug, Clone)]
pub enum Operator {
    Add,
    Subtract,
    Multiply,
    Divide,
    Equal,
    NotEqual,
    LessThan,
    GreaterThan,
    LessThanOrEqual,
    GreaterThanOrEqual,
    Assign,
    AddAssign,
    SubtractAssign,
    MultiplyAssign,
    DivideAssign,
}

impl Expression {
    // Relative weighting of precedence. Numbers are made up
    // with the only importance being how they relate to each
    // other
    pub fn precedence(&self) -> u64 {
        match self {
            Expression::Operator(Operator::Multiply, _)
            | Expression::Operator(Operator::Divide, _) => 100,
            Expression::Operator(Operator::Add, _)
            | Expression::Operator(Operator::Subtract, _) => 90,
            Expression::Operator(Operator::LessThan, _)
            | Expression::Operator(Operator::LessThanOrEqual, _)
            | Expression::Operator(Operator::GreaterThan, _)
            | Expression::Operator(Operator::GreaterThanOrEqual, _)
            | Expression::Operator(Operator::Equal, _)
            | Expression::Operator(Operator::NotEqual, _) => 80,
            Expression::Operator(Operator::Assign, _)
            | Expression::Operator(Operator::AddAssign, _)
            | Expression::Operator(Operator::SubtractAssign, _)
            | Expression::Operator(Operator::MultiplyAssign, _)
            | Expression::Operator(Operator::DivideAssign, _) => 50,
            _ => 0,
        }
    }
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

                            if var_decl.ty == Type::Unknown {
                                error = error.or(Some(JaktError::ParserError(
                                    "parameter missing type".to_string(),
                                    var_decl.span,
                                )))
                            }

                            params.push(Variable {
                                name: var_decl.name,
                                ty: var_decl.ty,
                                mutable: var_decl.mutable,
                            });
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

    match &tokens[*index].contents {
        TokenContents::Name(name) if name == "defer" => {
            *index += 1;
            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::Defer(block), error)
        }
        TokenContents::Name(name) if name == "if" => parse_if_statement(tokens, index),
        TokenContents::Name(name) if name == "while" => {
            *index += 1;

            let (cond, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::While(cond, block), error)
        }
        TokenContents::Name(name) if name == "return" => {
            *index += 1;
            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            (Statement::Return(expr), error)
        }
        TokenContents::Name(name) if name == "let" || name.as_str() == "var" => {
            let mutable = name == "var";

            *index += 1;

            let (mut var_decl, err) = parse_variable_declaration(tokens, index);
            error = error.or(err);

            var_decl.mutable = mutable;

            // Hardwire an initialiser for now, but we may not want this long-term
            if *index < tokens.len() {
                match &tokens[*index].contents {
                    TokenContents::Equal => {
                        *index += 1;

                        if *index < tokens.len() {
                            let (expr, err) = parse_expression(
                                tokens,
                                index,
                                ExpressionKind::ExpressionWithoutAssignment,
                            );
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
            let (expr, err) =
                parse_expression(&tokens, index, ExpressionKind::ExpressionWithAssignments);
            error = error.or(err);

            // Make sure, if there is an error and we can make progress, that we make progress.
            // This allows the parser to be more forgiving when there are errors
            // and to ensure parsing continues to make progress.
            if error.is_some() {
                if *index < tokens.len() {
                    *index += 1;
                }
            }

            (Statement::Expression(expr), error)
        }
    }
}

fn parse_if_statement(tokens: &[Token], index: &mut usize) -> (Statement, Option<JaktError>) {
    let mut error = None;

    match &tokens[*index].contents {
        TokenContents::Name(name) if name == "if" => {
            // Good, we have our keyword
        }
        _ => {
            return (
                Statement::Garbage,
                Some(JaktError::ParserError(
                    "expected if statement".to_string(),
                    tokens[*index].span,
                )),
            )
        }
    }

    *index += 1;

    let (cond, err) = parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
    error = error.or(err);

    let (block, err) = parse_block(tokens, index);
    error = error.or(err);

    let mut else_stmt = None;

    if *index < tokens.len() {
        // Check for an 'else'

        match &tokens[*index].contents {
            TokenContents::Name(name) if name == "else" => {
                // Good, we have our else keyword
                *index += 1;

                if *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Name(name) if name == "if" => {
                            let (else_if_stmt, err) = parse_if_statement(tokens, index);
                            else_stmt = Some(Box::new(else_if_stmt));
                            error = error.or(err);
                        }
                        TokenContents::LCurly => {
                            let (else_block, err) = parse_block(tokens, index);
                            else_stmt = Some(Box::new(Statement::Block(else_block)));
                            error = error.or(err);
                        }
                        _ => {
                            error = error.or(Some(JaktError::ParserError(
                                "else missing if or block".to_string(),
                                tokens[*index - 1].span,
                            )));
                        }
                    }
                } else {
                    error = error.or(Some(JaktError::ParserError(
                        "else missing if or block".to_string(),
                        tokens[*index - 1].span,
                    )));
                }
            }
            _ => {}
        }
        // try to parse an if statement again if we see an else
    }

    (Statement::If(cond, block, else_stmt), error)
}

pub fn parse_expression(
    tokens: &[Token],
    index: &mut usize,
    expression_kind: ExpressionKind,
) -> (Expression, Option<JaktError>) {
    // As the expr_stack grows, we increase the required precedence.
    // If, at any time, the operator we're looking at is the same or lower precedence
    // of what is in the expression stack, we collapse the expression stack.

    let mut error = None;

    let mut expr_stack: Vec<Expression> = vec![];
    let mut last_prec = 1000000;

    let (lhs, err) = parse_operand(tokens, index);
    error = error.or(err);

    expr_stack.push(lhs);

    while *index < tokens.len() {
        // Test to see if the next token is an operator

        let (op, err) = match expression_kind {
            ExpressionKind::ExpressionWithAssignments => {
                parse_operator_with_assignment(tokens, index)
            }
            ExpressionKind::ExpressionWithoutAssignment => parse_operator(tokens, index),
        };

        if let Some(jakt_error) = &err {
            match jakt_error {
                JaktError::ValidationError(..) => {
                    // Because we just saw a validation error, we need to remember it
                    // for later
                    error = error.or(err);
                }
                _ => {}
            }
            break;
        }

        let precedence = op.precedence();

        if *index == tokens.len() {
            error = error.or(Some(JaktError::ParserError(
                "incomplete math expression".to_string(),
                tokens[*index - 1].span,
            )));

            expr_stack.push(Expression::Garbage(tokens[*index - 1].span));
            expr_stack.push(Expression::Garbage(tokens[*index - 1].span));
            break;
        }

        let (rhs, err) = parse_operand(tokens, index);
        error = error.or(err);

        while precedence <= last_prec && expr_stack.len() > 1 {
            let rhs = expr_stack
                .pop()
                .expect("internal error: expression stack empty");

            let op = expr_stack
                .pop()
                .expect("internal error: expression stack empty");

            last_prec = op.precedence();

            if last_prec < precedence {
                expr_stack.push(op);
                expr_stack.push(rhs);
                break;
            }

            let lhs = expr_stack
                .pop()
                .expect("internal error: expression stack empty");

            expr_stack.push(Expression::BinaryOp(
                Box::new(lhs),
                Box::new(op),
                Box::new(rhs),
            ));
        }

        expr_stack.push(op);
        expr_stack.push(rhs);

        last_prec = precedence;
    }

    while expr_stack.len() != 1 {
        let rhs = expr_stack
            .pop()
            .expect("internal error: expression stack empty");
        let op = expr_stack
            .pop()
            .expect("internal error: expression stack empty");
        let lhs = expr_stack
            .pop()
            .expect("internal error: expression stack empty");

        expr_stack.push(Expression::BinaryOp(
            Box::new(lhs),
            Box::new(op),
            Box::new(rhs),
        ));
    }

    let output = expr_stack
        .pop()
        .expect("internal error: expression stack empty");

    (output, error)
}

pub fn parse_operand(tokens: &[Token], index: &mut usize) -> (Expression, Option<JaktError>) {
    let mut error = None;

    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::Name(name) if name == "true" => {
            *index += 1;
            (Expression::Boolean(true, span), None)
        }
        TokenContents::Name(name) if name == "false" => {
            *index += 1;
            (Expression::Boolean(false, span), None)
        }
        TokenContents::Name(name) => {
            if *index + 1 < tokens.len() {
                match &tokens[*index + 1].contents {
                    TokenContents::LParen => {
                        let (call, err) = parse_call(tokens, index);
                        error = error.or(err);

                        return (Expression::Call(call, span), error);
                    }
                    _ => {}
                }
            }

            *index += 1;

            (Expression::Var(name.to_string(), span), error)
        }
        TokenContents::LParen => {
            *index += 1;
            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            match &tokens[*index].contents {
                TokenContents::RParen => {
                    *index += 1;
                }
                _ => {
                    error = error.or(Some(JaktError::ParserError(
                        "expected ')'".to_string(),
                        tokens[*index].span,
                    )))
                }
            }

            (expr, error)
        }
        TokenContents::Number(number) => {
            *index += 1;
            (Expression::Int64(*number, span), error)
        }
        TokenContents::QuotedString(str) => {
            *index += 1;
            (Expression::QuotedString(str.to_string(), span), error)
        }
        _ => (
            Expression::Garbage(span),
            Some(JaktError::ParserError(
                "unsupported expression".to_string(),
                tokens[*index].span,
            )),
        ),
    }
}

pub fn parse_operator(tokens: &[Token], index: &mut usize) -> (Expression, Option<JaktError>) {
    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::Plus => {
            *index += 1;
            (Expression::Operator(Operator::Add, span), None)
        }
        TokenContents::Minus => {
            *index += 1;
            (Expression::Operator(Operator::Subtract, span), None)
        }
        TokenContents::Asterisk => {
            *index += 1;
            (Expression::Operator(Operator::Multiply, span), None)
        }
        TokenContents::ForwardSlash => {
            *index += 1;
            (Expression::Operator(Operator::Divide, span), None)
        }
        TokenContents::Equal => {
            *index += 1;
            (
                Expression::Operator(Operator::Assign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::PlusEqual => {
            *index += 1;
            (
                Expression::Operator(Operator::AddAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::MinusEqual => {
            *index += 1;
            (
                Expression::Operator(Operator::SubtractAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::AsteriskEqual => {
            *index += 1;
            (
                Expression::Operator(Operator::MultiplyAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::ForwardSlashEqual => {
            *index += 1;
            (
                Expression::Operator(Operator::DivideAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::DoubleEqual => {
            *index += 1;
            (Expression::Operator(Operator::Equal, span), None)
        }
        TokenContents::NotEqual => {
            *index += 1;
            (Expression::Operator(Operator::NotEqual, span), None)
        }
        TokenContents::LessThan => {
            *index += 1;
            (Expression::Operator(Operator::LessThan, span), None)
        }
        TokenContents::LessThanOrEqual => {
            *index += 1;
            (Expression::Operator(Operator::LessThanOrEqual, span), None)
        }
        TokenContents::GreaterThan => {
            *index += 1;
            (Expression::Operator(Operator::GreaterThan, span), None)
        }
        TokenContents::GreaterThanOrEqual => {
            *index += 1;
            (
                Expression::Operator(Operator::GreaterThanOrEqual, span),
                None,
            )
        }
        _ => (
            Expression::Garbage(span),
            Some(JaktError::ParserError(
                "unsupported operator".to_string(),
                tokens[*index].span,
            )),
        ),
    }
}

pub fn parse_operator_with_assignment(
    tokens: &[Token],
    index: &mut usize,
) -> (Expression, Option<JaktError>) {
    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::Plus => {
            *index += 1;
            (Expression::Operator(Operator::Add, span), None)
        }
        TokenContents::Minus => {
            *index += 1;
            (Expression::Operator(Operator::Subtract, span), None)
        }
        TokenContents::Asterisk => {
            *index += 1;
            (Expression::Operator(Operator::Multiply, span), None)
        }
        TokenContents::ForwardSlash => {
            *index += 1;
            (Expression::Operator(Operator::Divide, span), None)
        }
        TokenContents::Equal => {
            *index += 1;
            (Expression::Operator(Operator::Assign, span), None)
        }
        TokenContents::PlusEqual => {
            *index += 1;
            (Expression::Operator(Operator::AddAssign, span), None)
        }
        TokenContents::MinusEqual => {
            *index += 1;
            (Expression::Operator(Operator::SubtractAssign, span), None)
        }
        TokenContents::AsteriskEqual => {
            *index += 1;
            (Expression::Operator(Operator::MultiplyAssign, span), None)
        }
        TokenContents::ForwardSlashEqual => {
            *index += 1;
            (Expression::Operator(Operator::DivideAssign, span), None)
        }
        TokenContents::DoubleEqual => {
            *index += 1;
            (Expression::Operator(Operator::Equal, span), None)
        }
        TokenContents::NotEqual => {
            *index += 1;
            (Expression::Operator(Operator::NotEqual, span), None)
        }
        TokenContents::LessThan => {
            *index += 1;
            (Expression::Operator(Operator::LessThan, span), None)
        }
        TokenContents::LessThanOrEqual => {
            *index += 1;
            (Expression::Operator(Operator::LessThanOrEqual, span), None)
        }
        TokenContents::GreaterThan => {
            *index += 1;
            (Expression::Operator(Operator::GreaterThan, span), None)
        }
        TokenContents::GreaterThanOrEqual => {
            *index += 1;
            (
                Expression::Operator(Operator::GreaterThanOrEqual, span),
                None,
            )
        }
        _ => (
            Expression::Garbage(span),
            Some(JaktError::ParserError(
                "unsupported operator".to_string(),
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
                        return (
                            VarDecl {
                                name: name.to_string(),
                                ty: Type::Unknown,
                                mutable: false,
                                span: tokens[*index - 1].span,
                            },
                            None,
                        );
                    }
                }
            } else {
                return (
                    VarDecl {
                        name: name.to_string(),
                        ty: Type::Unknown,
                        mutable: false,
                        span: tokens[*index - 1].span,
                    },
                    None,
                );
            }

            if *index < tokens.len() {
                let (var_type, err) = parse_typename(tokens, index);
                error = error.or(err);

                let result = VarDecl {
                    name: var_name,
                    ty: var_type,
                    mutable: false,
                    span: tokens[*index - 3].span,
                };

                *index += 1;

                (result, error)
            } else {
                (
                    VarDecl {
                        name: name.to_string(),
                        ty: Type::Unknown,
                        mutable: false,
                        span: tokens[*index - 2].span,
                    },
                    Some(JaktError::ParserError(
                        "expected type".to_string(),
                        tokens[*index].span,
                    )),
                )
            }
        }
        _ => (
            VarDecl::new(tokens[*index].span),
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
            "i8" => (Type::I8, None),
            "i16" => (Type::I16, None),
            "i32" => (Type::I32, None),
            "i64" => (Type::I64, None),
            "u8" => (Type::U8, None),
            "u16" => (Type::U16, None),
            "u32" => (Type::U32, None),
            "u64" => (Type::U64, None),
            "f32" => (Type::F32, None),
            "f64" => (Type::F64, None),
            "String" => (Type::String, None),
            "bool" => (Type::Bool, None),
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
                        let (expr, err) = parse_expression(
                            tokens,
                            index,
                            ExpressionKind::ExpressionWithoutAssignment,
                        );
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
