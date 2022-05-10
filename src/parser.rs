use crate::error::JaktError;

use crate::lexer::{Span, Token, TokenContents};
use crate::typechecker::NumericConstant;

macro_rules! trace {
    ($x: expr) => {
        #[cfg(feature = "trace")]
        {
            println!("{}", $x)
        }
    };
}

#[derive(Debug, PartialEq)]
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
pub enum UncheckedType {
    Name(String, Span),
    Optional(Box<UncheckedType>, Span),
    RawPtr(Box<UncheckedType>, Span),
    Empty,
}

#[derive(Debug, Clone)]
pub struct VarDecl {
    pub name: String,
    pub ty: UncheckedType,
    pub mutable: bool,
    pub span: Span,
}

impl VarDecl {
    pub fn new(span: Span) -> Self {
        Self {
            name: String::new(),
            ty: UncheckedType::Empty,
            mutable: false,
            span,
        }
    }
}

impl PartialEq for VarDecl {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name && self.ty == other.ty && self.mutable == other.mutable
    }
}

#[derive(Debug)]
pub struct ParsedFile {
    pub funs: Vec<Function>,
    pub structs: Vec<Struct>,
}

#[derive(Debug)]
pub struct Struct {
    pub name: String,
    pub members: Vec<VarDecl>,
    pub span: Span,
}

#[derive(Clone, Debug, PartialEq)]
pub enum FunctionLinkage {
    Internal,
    External,
    ImplicitConstructor,
}

#[derive(Debug)]
pub struct Function {
    pub name: String,
    pub name_span: Span,
    pub params: Vec<Parameter>,
    pub block: Block,
    pub return_type: UncheckedType,
    pub linkage: FunctionLinkage,
}

#[derive(Clone, Debug)]
pub struct Parameter {
    pub requires_label: bool,
    pub variable: Variable,
}

#[derive(Clone, Debug)]
pub struct Variable {
    pub name: String,
    pub ty: UncheckedType,
    pub mutable: bool,
}

impl Function {
    pub fn new(linkage: FunctionLinkage) -> Self {
        Function {
            name: String::new(),
            name_span: Span {
                file_id: 0,
                start: 0,
                end: 0,
            },
            params: Vec::new(),
            block: Block::new(),
            return_type: UncheckedType::Empty,
            linkage,
        }
    }
}

#[derive(Debug, PartialEq)]
pub enum Statement {
    Expression(Expression),
    Defer(Block),
    UnsafeBlock(Block),
    VarDecl(VarDecl, Expression),
    If(Expression, Block, Option<Box<Statement>>),
    Block(Block),
    While(Expression, Block),
    Return(Expression),
    Garbage,
}

#[derive(Debug, PartialEq)]
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
    NumericConstant(NumericConstant, Span),
    QuotedString(String, Span),
    Vector(Vec<Expression>, Span),
    IndexedExpression(Box<Expression>, Box<Expression>, Span),
    UnaryOp(Box<Expression>, UnaryOperator, Span),
    BinaryOp(Box<Expression>, BinaryOperator, Box<Expression>, Span),
    Var(String, Span),
    Tuple(Vec<Expression>, Span),
    IndexedTuple(Box<Expression>, usize, Span),
    IndexedStruct(Box<Expression>, String, Span),

    ForcedUnwrap(Box<Expression>, Span),

    // FIXME: These should be implemented as `enum` variant values once available.
    OptionalNone(Span),
    OptionalSome(Box<Expression>, Span),

    // Not standalone
    Operator(BinaryOperator, Span),

    // Parsing error
    Garbage(Span),
}

impl Expression {
    pub fn span(&self) -> Span {
        match self {
            Expression::Boolean(_, span) => *span,
            Expression::Call(_, span) => *span,
            Expression::NumericConstant(_, span) => *span,
            Expression::QuotedString(_, span) => *span,
            Expression::Vector(_, span) => *span,
            Expression::Tuple(_, span) => *span,
            Expression::IndexedExpression(_, _, span) => *span,
            Expression::IndexedTuple(_, _, span) => *span,
            Expression::IndexedStruct(_, _, span) => *span,
            Expression::UnaryOp(_, _, span) => *span,
            Expression::BinaryOp(_, _, _, span) => *span,
            Expression::Var(_, span) => *span,
            Expression::Operator(_, span) => *span,
            Expression::OptionalNone(span) => *span,
            Expression::OptionalSome(_, span) => *span,
            Expression::ForcedUnwrap(_, span) => *span,
            Expression::Garbage(span) => *span,
        }
    }
}

impl PartialEq for Expression {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (Self::Boolean(l0, _), Self::Boolean(r0, _)) => l0 == r0,
            (Self::Call(l0, _), Self::Call(r0, _)) => l0 == r0,
            (Self::NumericConstant(l0, _), Self::NumericConstant(r0, _)) => l0 == r0,
            (Self::QuotedString(l0, _), Self::QuotedString(r0, _)) => l0 == r0,
            (Self::BinaryOp(l0, l1, l2, _), Self::BinaryOp(r0, r1, r2, _)) => {
                l0 == r0 && l1 == r1 && l2 == r2
            }
            (Self::Var(l0, _), Self::Var(r0, _)) => l0 == r0,
            (Self::Operator(l0, _), Self::Operator(r0, _)) => l0 == r0,
            (Self::Garbage(_), Self::Garbage(_)) => true,
            _ => false,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum UnaryOperator {
    PreIncrement,
    PostIncrement,
    PreDecrement,
    PostDecrement,
    Negate,
    Dereference,
    RawAddress,
}

#[derive(Debug, Clone, PartialEq)]
pub enum BinaryOperator {
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
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
    ModuloAssign,
}

impl Expression {
    // Relative weighting of precedence. Numbers are made up
    // with the only importance being how they relate to each
    // other
    pub fn precedence(&self) -> u64 {
        match self {
            Expression::Operator(BinaryOperator::Multiply, _)
            | Expression::Operator(BinaryOperator::Modulo, _)
            | Expression::Operator(BinaryOperator::Divide, _) => 100,
            Expression::Operator(BinaryOperator::Add, _)
            | Expression::Operator(BinaryOperator::Subtract, _) => 90,
            Expression::Operator(BinaryOperator::LessThan, _)
            | Expression::Operator(BinaryOperator::LessThanOrEqual, _)
            | Expression::Operator(BinaryOperator::GreaterThan, _)
            | Expression::Operator(BinaryOperator::GreaterThanOrEqual, _)
            | Expression::Operator(BinaryOperator::Equal, _)
            | Expression::Operator(BinaryOperator::NotEqual, _) => 80,
            Expression::Operator(BinaryOperator::Assign, _)
            | Expression::Operator(BinaryOperator::AddAssign, _)
            | Expression::Operator(BinaryOperator::SubtractAssign, _)
            | Expression::Operator(BinaryOperator::MultiplyAssign, _)
            | Expression::Operator(BinaryOperator::ModuloAssign, _)
            | Expression::Operator(BinaryOperator::DivideAssign, _) => 50,
            _ => 0,
        }
    }
}

impl ParsedFile {
    pub fn new() -> Self {
        Self {
            funs: Vec::new(),
            structs: Vec::new(),
        }
    }
}

pub fn parse_file(tokens: &[Token]) -> (ParsedFile, Option<JaktError>) {
    trace!("parse_file");

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
                    let (fun, err) = parse_function(tokens, &mut index, FunctionLinkage::Internal);
                    error = error.or(err);

                    parsed_file.funs.push(fun);
                }
                "struct" => {
                    let (structure, err) = parse_struct(tokens, &mut index);
                    error = error.or(err);

                    parsed_file.structs.push(structure);
                }
                "extern" => {
                    if index + 1 < tokens.len() {
                        match &tokens[index + 1] {
                            Token {
                                contents: TokenContents::Name(name),
                                span,
                            } => match name.as_str() {
                                "fun" => {
                                    index += 1;
                                    let (fun, err) = parse_function(
                                        tokens,
                                        &mut index,
                                        FunctionLinkage::External,
                                    );
                                    error = error.or(err);

                                    parsed_file.funs.push(fun);
                                }
                                _ => {
                                    trace!("ERROR: unexpected keyword");

                                    error = error.or(Some(JaktError::ParserError(
                                        "unexpected keyword".to_string(),
                                        *span,
                                    )));
                                }
                            },
                            _ => {
                                trace!("ERROR: unexpected keyword");

                                error = error.or(Some(JaktError::ParserError(
                                    "unexpected keyword".to_string(),
                                    *span,
                                )));
                            }
                        }
                    }
                }
                _ => {
                    trace!("ERROR: unexpected keyword");
                    index += 1;

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
                trace!("ERROR: unexpected token (expected keyword)");
                index += 1;

                error = error.or(Some(JaktError::ParserError(
                    "unexpected token (expected keyword)".to_string(),
                    *span,
                )));
            }
        }
    }

    (parsed_file, error)
}

pub fn parse_struct(tokens: &[Token], index: &mut usize) -> (Struct, Option<JaktError>) {
    trace!(format!("parse_struct: {:?}", tokens[*index]));

    let mut error = None;

    *index += 1;

    if *index < tokens.len() {
        // we're expecting the name of the function
        match &tokens[*index] {
            Token {
                contents: TokenContents::Name(struct_name),
                ..
            } => {
                *index += 1;

                if *index < tokens.len() {
                    match tokens[*index] {
                        Token {
                            contents: TokenContents::LCurly,
                            ..
                        } => {
                            *index += 1;
                        }
                        _ => {
                            trace!("ERROR: expected '{'");

                            error = error.or(Some(JaktError::ParserError(
                                "expected '{'".to_string(),
                                tokens[*index].span,
                            )));
                        }
                    }
                } else {
                    trace!("ERROR: incomplete struct");

                    error = error.or(Some(JaktError::ParserError(
                        "incomplete struct".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                let mut fields = Vec::new();
                while *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::RCurly => {
                            *index += 1;
                            break;
                        }
                        TokenContents::Comma | TokenContents::Eol => {
                            // Treat comma as whitespace? Might require them in the future
                            *index += 1;
                        }

                        TokenContents::Name(..) => {
                            // Now lets parse a parameter

                            let (mut var_decl, err) = parse_variable_declaration(tokens, index);
                            error = error.or(err);

                            // Ignore immutable flag for now
                            var_decl.mutable = false;

                            if var_decl.ty == UncheckedType::Empty {
                                trace!("ERROR: parameter missing type");

                                error = error.or(Some(JaktError::ParserError(
                                    "parameter missing type".to_string(),
                                    var_decl.span,
                                )))
                            }

                            fields.push(var_decl);
                        }
                        _ => {
                            trace!(format!(
                                "ERROR: expected field, found: {:?}",
                                tokens[*index].contents
                            ));

                            error = error.or(Some(JaktError::ParserError(
                                "expected field".to_string(),
                                tokens[*index].span,
                            )));
                        }
                    }
                }
                if *index >= tokens.len() {
                    trace!("ERROR: incomplete struct");

                    error = error.or(Some(JaktError::ParserError(
                        "incomplete struct".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                (
                    Struct {
                        name: struct_name.clone(),
                        members: fields,
                        span: tokens[*index - 1].span,
                    },
                    error,
                )
            }
            _ => {
                trace!("ERROR: expected struct name");

                error = error.or(Some(JaktError::ParserError(
                    "expected struct name".to_string(),
                    tokens[*index].span,
                )));

                (
                    Struct {
                        name: String::new(),
                        members: Vec::new(),
                        span: tokens[*index].span,
                    },
                    error,
                )
            }
        }
    } else {
        trace!("ERROR: expected struct name");

        error = error.or(Some(JaktError::ParserError(
            "expected struct name".to_string(),
            tokens[*index].span,
        )));

        (
            Struct {
                name: String::new(),
                members: Vec::new(),
                span: tokens[*index].span,
            },
            error,
        )
    }
}

pub fn parse_function(
    tokens: &[Token],
    index: &mut usize,
    linkage: FunctionLinkage,
) -> (Function, Option<JaktError>) {
    trace!(format!("parse_function: {:?}", tokens[*index]));

    let mut error = None;

    *index += 1;

    if *index < tokens.len() {
        // we're expecting the name of the function
        match &tokens[*index] {
            Token {
                contents: TokenContents::Name(fun_name),
                ..
            } => {
                let name_span = tokens[*index].span;

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
                            trace!("ERROR: expected '('");

                            error = error.or(Some(JaktError::ParserError(
                                "expected '('".to_string(),
                                tokens[*index].span,
                            )));
                        }
                    }
                } else {
                    trace!("ERROR: incomplete function");

                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                let mut params = Vec::new();

                let mut current_param_requires_label = true;

                while *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::RParen => {
                            *index += 1;
                            break;
                        }
                        TokenContents::Comma => {
                            // Treat comma as whitespace? Might require them in the future
                            *index += 1;
                            current_param_requires_label = true;
                        }

                        TokenContents::Name(name) if name == "_" => {
                            current_param_requires_label = false;
                            *index += 1;
                        }

                        TokenContents::Name(..) => {
                            // Now lets parse a parameter

                            let (var_decl, err) = parse_variable_declaration(tokens, index);
                            error = error.or(err);

                            if var_decl.ty == UncheckedType::Empty {
                                trace!("ERROR: parameter missing type");

                                error = error.or(Some(JaktError::ParserError(
                                    "parameter missing type".to_string(),
                                    var_decl.span,
                                )))
                            }

                            params.push(Parameter {
                                requires_label: current_param_requires_label,
                                variable: Variable {
                                    name: var_decl.name,
                                    ty: var_decl.ty,
                                    mutable: var_decl.mutable,
                                },
                            });
                        }
                        _ => {
                            trace!("ERROR: expected parameter");

                            error = error.or(Some(JaktError::ParserError(
                                "expected parameter".to_string(),
                                tokens[*index].span,
                            )));
                        }
                    }
                }

                if *index >= tokens.len() {
                    trace!("ERROR: incomplete function");

                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                let mut return_type = UncheckedType::Empty;

                let mut fat_arrow_expr = None;

                if *index + 2 < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Equal => {
                            *index += 1;
                            match &tokens[*index].contents {
                                TokenContents::GreaterThan => {
                                    *index += 1;

                                    let (expr, err) = parse_expression(
                                        tokens,
                                        index,
                                        ExpressionKind::ExpressionWithoutAssignment,
                                    );
                                    return_type = UncheckedType::Empty;
                                    fat_arrow_expr = Some(expr);
                                    error = error.or(err);

                                    *index += 1;
                                }
                                _ => {
                                    trace!("ERROR: expected =>");

                                    error = error.or(Some(JaktError::ParserError(
                                        "expected =>".to_string(),
                                        tokens[*index - 1].span,
                                    )));
                                }
                            }
                        }
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
                                    trace!("ERROR: expected ->");

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
                    trace!("ERROR: incomplete function");
                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[*index - 1].span,
                    )));
                }

                if let FunctionLinkage::External = linkage {
                    return (
                        Function {
                            name: fun_name.clone(),
                            name_span,
                            params,
                            block: Block::new(),
                            return_type,
                            linkage,
                        },
                        error,
                    );
                }

                let (block, err) = match fat_arrow_expr {
                    Some(expr) => {
                        let mut block = Block::new();
                        block.stmts.push(Statement::Return(expr));
                        (block, None)
                    }
                    None => parse_block(tokens, index),
                };
                error = error.or(err);

                return (
                    Function {
                        name: fun_name.clone(),
                        name_span,
                        params,
                        block,
                        return_type,
                        linkage,
                    },
                    error,
                );
            }
            _ => {
                trace!("ERROR: expected function name");

                (
                    Function::new(FunctionLinkage::Internal),
                    Some(JaktError::ParserError(
                        "expected function name".to_string(),
                        tokens[*index].span,
                    )),
                )
            }
        }
    } else {
        trace!("ERROR: incomplete function definition");
        (
            Function::new(FunctionLinkage::Internal),
            Some(JaktError::ParserError(
                "incomplete function definition".to_string(),
                tokens[*index].span,
            )),
        )
    }
}

pub fn parse_block(tokens: &[Token], index: &mut usize) -> (Block, Option<JaktError>) {
    trace!(format!("parse_block: {:?}", tokens[*index]));

    let mut block = Block::new();
    let mut error = None;

    let start = tokens[*index].span;

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

    trace!("ERROR: expected complete block");
    (
        Block::new(),
        Some(JaktError::ParserError(
            "expected complete block".to_string(),
            Span {
                file_id: start.file_id,
                start: start.start,
                end: tokens[(*index - 1)].span.end,
            },
        )),
    )
}

pub fn parse_statement(tokens: &[Token], index: &mut usize) -> (Statement, Option<JaktError>) {
    trace!(format!("parse_statement: {:?}", tokens[*index]));

    let mut error = None;

    match &tokens[*index].contents {
        TokenContents::Name(name) if name == "defer" => {
            trace!("parsing defer");

            *index += 1;

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::Defer(block), error)
        }
        TokenContents::Name(name) if name == "unsafe" => {
            trace!("parsing unsafe");

            *index += 1;

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::UnsafeBlock(block), error)
        }
        TokenContents::Name(name) if name == "if" => parse_if_statement(tokens, index),
        TokenContents::Name(name) if name == "while" => {
            trace!("parsing while");

            *index += 1;

            let (cond, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::While(cond, block), error)
        }
        TokenContents::Name(name) if name == "return" => {
            trace!("parsing return");

            *index += 1;

            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            (Statement::Return(expr), error)
        }
        TokenContents::Name(name) if name == "let" || name.as_str() == "var" => {
            trace!("parsing let/var");

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
        TokenContents::LCurly => {
            trace!("parsing block from statement parser");

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (Statement::Block(block), error)
        }
        _ => {
            trace!("parsing expression from statement parser");

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
    trace!(format!("parse_if_statement: {:?}", tokens[*index]));

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

    let starting_span = tokens[*index].span;

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

                            // Before we continue, quickly lint that the else block and the if block are not
                            // the same. This helps prevent a copy/paste error
                            if block == else_block {
                                error = error.or(Some(JaktError::ValidationError(
                                    "if and else have identical blocks".to_string(),
                                    starting_span,
                                )));
                            }

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
    trace!(format!("parse_expression: {:?}", tokens[*index]));

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
                _ => {
                    break;
                }
            }
        }

        let precedence = op.precedence();

        if *index == tokens.len() {
            trace!("ERROR: incomplete math expression");

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

            match op {
                Expression::Operator(op, _) => {
                    let span = Span {
                        file_id: lhs.span().file_id,
                        start: lhs.span().start,
                        end: rhs.span().end,
                    };
                    expr_stack.push(Expression::BinaryOp(Box::new(lhs), op, Box::new(rhs), span));
                }
                _ => panic!("internal error: operator is not an operator"),
            }
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

        match op {
            Expression::Operator(op, _) => {
                let span = Span {
                    file_id: lhs.span().file_id,
                    start: lhs.span().start,
                    end: rhs.span().end,
                };
                expr_stack.push(Expression::BinaryOp(Box::new(lhs), op, Box::new(rhs), span));
            }
            _ => panic!("internal error: operator is not an operator"),
        }
    }

    let output = expr_stack
        .pop()
        .expect("internal error: expression stack empty");

    (output, error)
}

pub fn parse_operand(tokens: &[Token], index: &mut usize) -> (Expression, Option<JaktError>) {
    trace!(format!("parse_operand: {:?}", tokens[*index]));

    let mut error = None;

    let span = tokens[*index].span;

    let mut expr = match &tokens[*index].contents {
        TokenContents::Name(name) if name == "true" => {
            *index += 1;
            Expression::Boolean(true, span)
        }
        TokenContents::Name(name) if name == "false" => {
            *index += 1;
            Expression::Boolean(false, span)
        }
        TokenContents::Name(name) => {
            if *index + 1 < tokens.len() {
                match &tokens[*index + 1].contents {
                    TokenContents::LParen => match name.as_str() {
                        "Some" => {
                            *index += 1;
                            let (expr, err) = parse_expression(
                                tokens,
                                index,
                                ExpressionKind::ExpressionWithoutAssignment,
                            );
                            error = error.or(err);
                            Expression::OptionalSome(Box::new(expr), span)
                        }
                        _ => {
                            let (call, err) = parse_call(tokens, index);
                            error = error.or(err);

                            Expression::Call(call, span)
                        }
                    },
                    _ => {
                        *index += 1;

                        match name.as_str() {
                            "None" => Expression::OptionalNone(span),
                            _ => Expression::Var(name.to_string(), span),
                        }
                    }
                }
            } else {
                *index += 1;

                Expression::Var(name.to_string(), span)
            }
        }
        TokenContents::LParen => {
            let start = tokens[*index].span;

            *index += 1;
            let (mut expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            match &tokens[*index].contents {
                TokenContents::RParen => {
                    *index += 1;
                }
                TokenContents::Comma => {
                    // We have a tuple
                    let mut exprs = Vec::new();
                    exprs.push(expr);

                    *index += 1;

                    let mut end = start;

                    while *index < tokens.len() {
                        match &tokens[*index].contents {
                            TokenContents::RParen => {
                                *index += 1;
                                break;
                            }
                            TokenContents::Comma => {
                                *index += 1;
                            }
                            _ => {
                                let (expr, err) = parse_expression(
                                    tokens,
                                    index,
                                    ExpressionKind::ExpressionWithoutAssignment,
                                );

                                end = expr.span();

                                error = error.or(err);

                                exprs.push(expr);
                            }
                        }
                    }

                    if *index >= tokens.len() {
                        trace!("ERROR: expected ')'");

                        error = error.or(Some(JaktError::ParserError(
                            "expected ')'".to_string(),
                            tokens[*index].span,
                        )))
                    }

                    expr = Expression::Tuple(
                        exprs,
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: end.end,
                        },
                    )
                }
                _ => {
                    trace!("ERROR: expected ')'");

                    error = error.or(Some(JaktError::ParserError(
                        "expected ')'".to_string(),
                        tokens[*index].span,
                    )))
                }
            }

            expr
        }
        TokenContents::LSquare => {
            let (expr, err) = parse_vector(tokens, index);
            error = error.or(err);
            expr
        }
        TokenContents::PlusPlus => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            Expression::UnaryOp(Box::new(expr), UnaryOperator::PreIncrement, span)
        }
        TokenContents::MinusMinus => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            Expression::UnaryOp(Box::new(expr), UnaryOperator::PreDecrement, span)
        }
        TokenContents::Minus => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            Expression::UnaryOp(Box::new(expr), UnaryOperator::Negate, span)
        }
        TokenContents::Asterisk => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            Expression::UnaryOp(Box::new(expr), UnaryOperator::Dereference, span)
        }
        TokenContents::Ampersand => {
            *index += 1;

            if *index < tokens.len() {
                match &tokens[*index].contents {
                    TokenContents::Name(name)
                        if name == "raw"
                            && tokens[*index].span.start == tokens[*index - 1].span.end =>
                    {
                        // we found `&raw`

                        let start_span = tokens[*index].span;

                        *index += 1;

                        let (expr, err) = parse_operand(tokens, index);
                        error = error.or(err);

                        let span = Span {
                            file_id: start_span.file_id,
                            start: start_span.start,
                            end: expr.span().end,
                        };

                        Expression::UnaryOp(Box::new(expr), UnaryOperator::RawAddress, span)
                    }
                    _ => {
                        error = error.or(Some(JaktError::ParserError(
                            "ampersand not currently supported".to_string(),
                            tokens[*index - 1].span,
                        )));
                        Expression::Garbage(tokens[*index - 1].span)
                    }
                }
            } else {
                error = error.or(Some(JaktError::ParserError(
                    "ampersand not currently supported".to_string(),
                    tokens[*index - 1].span,
                )));
                Expression::Garbage(tokens[*index - 1].span)
            }
        }
        TokenContents::Number(number) => {
            *index += 1;
            Expression::NumericConstant(NumericConstant::I64(*number), span)
        }
        TokenContents::QuotedString(str) => {
            *index += 1;
            Expression::QuotedString(str.to_string(), span)
        }
        _ => {
            trace!("ERROR: unsupported expression");
            error = error.or(Some(JaktError::ParserError(
                "unsupported expression".to_string(),
                tokens[*index].span,
            )));

            Expression::Garbage(span)
        }
    };

    // Check for postfix operators, while we're at it
    while *index < tokens.len() {
        match &tokens[*index].contents {
            TokenContents::ExclamationPoint => {
                *index += 1;
                // Forced Optional unwrap
                expr = Expression::ForcedUnwrap(Box::new(expr), span);
            }
            TokenContents::PlusPlus => {
                let end_span = tokens[*index].span;

                *index += 1;

                let span = Span {
                    file_id: expr.span().file_id,
                    start: expr.span().start,
                    end: end_span.end,
                };

                expr = Expression::UnaryOp(Box::new(expr), UnaryOperator::PostIncrement, span)
            }
            TokenContents::MinusMinus => {
                let end_span = tokens[*index].span;

                *index += 1;

                let span = Span {
                    file_id: expr.span().file_id,
                    start: expr.span().start,
                    end: end_span.end,
                };

                expr = Expression::UnaryOp(Box::new(expr), UnaryOperator::PostDecrement, span)
            }
            TokenContents::Dot => {
                *index += 1;

                if *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Number(int) => {
                            *index += 1;

                            let span = Span {
                                file_id: expr.span().file_id,
                                start: expr.span().start,
                                end: tokens[*index].span.end,
                            };

                            expr = Expression::IndexedTuple(Box::new(expr), *int as usize, span);
                        }

                        TokenContents::Name(name) => {
                            *index += 1;
                            let span = Span {
                                file_id: expr.span().file_id,
                                start: expr.span().start,
                                end: tokens[*index].span.end,
                            };

                            expr =
                                Expression::IndexedStruct(Box::new(expr), name.to_string(), span);
                        }

                        _ => {
                            *index += 1;
                            error = error.or(Some(JaktError::ParserError(
                                "Unsupported index".to_string(),
                                tokens[*index].span,
                            )))
                        }
                    }
                }
            }
            TokenContents::LSquare => {
                // Indexing operation
                *index += 1;

                if *index < tokens.len() {
                    let (idx, err) = parse_expression(
                        tokens,
                        index,
                        ExpressionKind::ExpressionWithoutAssignment,
                    );
                    error = error.or(err);

                    let end;
                    if *index < tokens.len() {
                        end = *index;
                        match &tokens[*index].contents {
                            TokenContents::RSquare => {
                                *index += 1;
                            }
                            _ => {
                                error = error.or(Some(JaktError::ParserError(
                                    "expected ']'".to_string(),
                                    tokens[*index].span,
                                )))
                            }
                        }
                    } else {
                        end = *index - 1;
                        error = error.or(Some(JaktError::ParserError(
                            "expected ']'".to_string(),
                            tokens[*index - 1].span,
                        )));
                    }

                    expr = Expression::IndexedExpression(
                        Box::new(expr),
                        Box::new(idx),
                        Span {
                            file_id: span.file_id,
                            start: span.start,
                            end,
                        },
                    );
                }
            }
            _ => break,
        }
    }

    (expr, error)
}

pub fn parse_operator(tokens: &[Token], index: &mut usize) -> (Expression, Option<JaktError>) {
    trace!(format!("parse_operator: {:?}", tokens[*index]));

    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::Plus => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Add, span), None)
        }
        TokenContents::Minus => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Subtract, span), None)
        }
        TokenContents::Asterisk => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Multiply, span), None)
        }
        TokenContents::ForwardSlash => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Divide, span), None)
        }
        TokenContents::PercentSign => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Modulo, span), None)
        }
        TokenContents::Equal => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                Expression::Operator(BinaryOperator::Assign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::PlusEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                Expression::Operator(BinaryOperator::AddAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::MinusEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                Expression::Operator(BinaryOperator::SubtractAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::AsteriskEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                Expression::Operator(BinaryOperator::MultiplyAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::ForwardSlashEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                Expression::Operator(BinaryOperator::DivideAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::PercentSignEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                Expression::Operator(BinaryOperator::ModuloAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::DoubleEqual => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Equal, span), None)
        }
        TokenContents::NotEqual => {
            *index += 1;
            (Expression::Operator(BinaryOperator::NotEqual, span), None)
        }
        TokenContents::LessThan => {
            *index += 1;
            (Expression::Operator(BinaryOperator::LessThan, span), None)
        }
        TokenContents::LessThanOrEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::LessThanOrEqual, span),
                None,
            )
        }
        TokenContents::GreaterThan => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::GreaterThan, span),
                None,
            )
        }
        TokenContents::GreaterThanOrEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::GreaterThanOrEqual, span),
                None,
            )
        }
        _ => {
            trace!("ERROR: unsupported operator (possibly just the end of an expression)");

            (
                Expression::Garbage(span),
                Some(JaktError::ParserError(
                    "unsupported operator".to_string(),
                    tokens[*index].span,
                )),
            )
        }
    }
}

pub fn parse_operator_with_assignment(
    tokens: &[Token],
    index: &mut usize,
) -> (Expression, Option<JaktError>) {
    trace!(format!(
        "parse_operator_with_assignment: {:?}",
        tokens[*index]
    ));

    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::Plus => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Add, span), None)
        }
        TokenContents::Minus => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Subtract, span), None)
        }
        TokenContents::Asterisk => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Multiply, span), None)
        }
        TokenContents::ForwardSlash => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Divide, span), None)
        }
        TokenContents::PercentSign => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Modulo, span), None)
        }
        TokenContents::Equal => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Assign, span), None)
        }
        TokenContents::PlusEqual => {
            *index += 1;
            (Expression::Operator(BinaryOperator::AddAssign, span), None)
        }
        TokenContents::MinusEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::SubtractAssign, span),
                None,
            )
        }
        TokenContents::AsteriskEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::MultiplyAssign, span),
                None,
            )
        }
        TokenContents::ForwardSlashEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::DivideAssign, span),
                None,
            )
        }
        TokenContents::DoubleEqual => {
            *index += 1;
            (Expression::Operator(BinaryOperator::Equal, span), None)
        }
        TokenContents::NotEqual => {
            *index += 1;
            (Expression::Operator(BinaryOperator::NotEqual, span), None)
        }
        TokenContents::LessThan => {
            *index += 1;
            (Expression::Operator(BinaryOperator::LessThan, span), None)
        }
        TokenContents::LessThanOrEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::LessThanOrEqual, span),
                None,
            )
        }
        TokenContents::GreaterThan => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::GreaterThan, span),
                None,
            )
        }
        TokenContents::GreaterThanOrEqual => {
            *index += 1;
            (
                Expression::Operator(BinaryOperator::GreaterThanOrEqual, span),
                None,
            )
        }
        _ => {
            trace!("ERROR: unsupported operator (possibly just the end of an expression)");

            (
                Expression::Garbage(span),
                Some(JaktError::ParserError(
                    "unsupported operator".to_string(),
                    tokens[*index].span,
                )),
            )
        }
    }
}

pub fn parse_vector(tokens: &[Token], index: &mut usize) -> (Expression, Option<JaktError>) {
    let mut error = None;

    let mut output = Vec::new();

    let start;
    if *index < tokens.len() {
        start = *index;
        match tokens[*index] {
            Token {
                contents: TokenContents::LSquare,
                ..
            } => {
                *index += 1;
            }
            _ => {
                trace!("ERROR: expected '['");

                error = error.or(Some(JaktError::ParserError(
                    "expected '('".to_string(),
                    tokens[*index].span,
                )));
            }
        }
    } else {
        start = *index - 1;
        trace!("ERROR: incomplete function");

        error = error.or(Some(JaktError::ParserError(
            "incomplete function".to_string(),
            tokens[*index - 1].span,
        )));
    }

    while *index < tokens.len() {
        match &tokens[*index].contents {
            TokenContents::RSquare => {
                *index += 1;
                break;
            }
            TokenContents::Comma => {
                // Treat comma as whitespace? Might require them in the future
                *index += 1;
            }
            TokenContents::Eol => {
                // Treat comma as whitespace? Might require them in the future
                *index += 1;
            }

            _ => {
                let (expr, err) =
                    parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
                error = error.or(err);

                output.push(expr);
            }
        }
    }

    let end;
    if *index >= tokens.len() {
        trace!("ERROR: incomplete function");

        error = error.or(Some(JaktError::ParserError(
            "incomplete function".to_string(),
            tokens[*index - 1].span,
        )));

        end = *index - 1;
    } else {
        end = *index;
    }

    (
        Expression::Vector(
            output,
            Span {
                file_id: tokens[start].span.file_id,
                start: tokens[start].span.start,
                end: tokens[end].span.end,
            },
        ),
        error,
    )
}

pub fn parse_variable_declaration(
    tokens: &[Token],
    index: &mut usize,
) -> (VarDecl, Option<JaktError>) {
    trace!(format!("parse_variable_declaration: {:?}", tokens[*index]));

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
                                ty: UncheckedType::Empty,
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
                        ty: UncheckedType::Empty,
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
                trace!("ERROR: expected type");

                (
                    VarDecl {
                        name: name.to_string(),
                        ty: UncheckedType::Empty,
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
        _ => {
            trace!("ERROR: expected name");

            (
                VarDecl::new(tokens[*index].span),
                Some(JaktError::ParserError(
                    "expected name".to_string(),
                    tokens[*index].span,
                )),
            )
        }
    }
}

pub fn parse_typename(tokens: &[Token], index: &mut usize) -> (UncheckedType, Option<JaktError>) {
    let mut unchecked_type = UncheckedType::Empty;
    let mut error = None;

    let start = tokens[*index].span;

    trace!(format!("parse_typename: {:?}", tokens[*index]));
    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            ..
        } => {
            if name == "raw" {
                *index += 1;
                if *index < tokens.len() {
                    let (child_ty, err) = parse_typename(tokens, index);
                    error = error.or(err);

                    unchecked_type = UncheckedType::RawPtr(
                        Box::new(child_ty),
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: tokens[*index - 1].span.end,
                        },
                    );
                }
            } else {
                unchecked_type = UncheckedType::Name(name.clone(), tokens[*index].span);
            }
        }
        _ => {
            trace!("ERROR: expected type name");

            error = error.or(Some(JaktError::ParserError(
                "expected type name".to_string(),
                tokens[*index].span,
            )));
        }
    };

    if *index + 1 < tokens.len() {
        if let TokenContents::QuestionMark = tokens[*index + 1].contents {
            // T? is shorthand for Optional<T>
            *index += 1;
            unchecked_type = UncheckedType::Optional(
                Box::new(unchecked_type),
                Span {
                    file_id: start.file_id,
                    start: start.start,
                    end: tokens[*index].span.end,
                },
            );
        }
    };

    (unchecked_type, error)
}

pub fn parse_call_parameter_name(
    tokens: &[Token],
    index: &mut usize,
) -> (String, Option<JaktError>) {
    if let TokenContents::Name(name) = &tokens[*index].contents {
        if *index + 1 < tokens.len() {
            if let TokenContents::Colon = &tokens[*index + 1].contents {
                *index += 2;
                return (name.clone(), None);
            }
        }
    }
    (String::new(), None)
}

pub fn parse_call(tokens: &[Token], index: &mut usize) -> (Call, Option<JaktError>) {
    trace!(format!("parse_call: {:?}", tokens[*index]));
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
                        trace!("ERROR: expected '('");

                        return (
                            call,
                            Some(JaktError::ParserError("expected '('".to_string(), *span)),
                        );
                    }
                }
            } else {
                trace!("ERROR: incomplete function");

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
                        let (param_name, err) = parse_call_parameter_name(tokens, index);
                        error = error.or(err);

                        let (expr, err) = parse_expression(
                            tokens,
                            index,
                            ExpressionKind::ExpressionWithoutAssignment,
                        );
                        error = error.or(err);

                        call.args.push((param_name, expr));
                    }
                }
            }

            if *index >= tokens.len() {
                trace!("ERROR: incomplete call");

                error = error.or(Some(JaktError::ParserError(
                    "incomplete call".to_string(),
                    tokens[*index - 1].span,
                )));
            }
        }
        _ => {
            trace!("ERROR: expected function call");

            error = error.or(Some(JaktError::ParserError(
                "expected function call".to_string(),
                tokens[*index].span,
            )));
        }
    }
    (call, error)
}
