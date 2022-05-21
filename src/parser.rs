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

#[derive(Debug, Clone, PartialEq)]
pub struct ParsedCall {
    pub namespace: Vec<String>,
    pub name: String,
    pub args: Vec<(String, ParsedExpression)>,
    pub type_args: Vec<ParsedType>,
}

impl ParsedCall {
    pub fn new() -> Self {
        Self {
            namespace: Vec::new(),
            name: String::new(),
            args: Vec::new(),
            type_args: Vec::new(),
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum ExpressionKind {
    ExpressionWithAssignments,
    ExpressionWithoutAssignment,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ParsedType {
    Name(String, Span),
    GenericType(String, Vec<ParsedType>, Span),
    Array(Box<ParsedType>, Span),
    Set(Box<ParsedType>, Span),
    Optional(Box<ParsedType>, Span),
    RawPtr(Box<ParsedType>, Span),
    Empty,
}

#[derive(Debug, Clone)]
pub struct ParsedVarDecl {
    pub name: String,
    pub ty: ParsedType,
    pub mutable: bool,
    pub span: Span,
}

impl ParsedVarDecl {
    pub fn new(span: Span) -> Self {
        Self {
            name: String::new(),
            ty: ParsedType::Empty,
            mutable: false,
            span,
        }
    }
}

impl PartialEq for ParsedVarDecl {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name && self.ty == other.ty && self.mutable == other.mutable
    }
}

#[derive(Debug)]
pub struct ParsedNamespace {
    pub name: Option<String>,
    pub functions: Vec<ParsedFunction>,
    pub structs: Vec<ParsedStruct>,
    pub enums: Vec<ParsedEnum>,
    pub namespaces: Vec<ParsedNamespace>,
}

#[derive(Debug)]
pub struct ParsedStruct {
    pub name: String,
    pub generic_parameters: Vec<(String, Span)>,
    pub fields: Vec<ParsedVarDecl>,
    pub methods: Vec<ParsedFunction>,
    pub span: Span,
    pub definition_linkage: DefinitionLinkage,
    pub definition_type: DefinitionType,
}

#[derive(Debug)]
pub enum EnumVariant {
    Untyped(String, Span),
    WithValue(String, ParsedExpression, Span),
    StructLike(String, Vec<ParsedVarDecl>, Span),
    Typed(String, ParsedType, Span),
}

#[derive(Debug)]
pub struct ParsedEnum {
    pub name: String,
    pub generic_parameters: Vec<(String, Span)>,
    pub variants: Vec<EnumVariant>,
    pub span: Span,
    pub definition_linkage: DefinitionLinkage,
    pub underlying_type: ParsedType,
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum FunctionLinkage {
    Internal,
    External,
    ImplicitConstructor,
    ImplicitEnumConstructor,
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum DefinitionLinkage {
    Internal,
    External,
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum DefinitionType {
    Class,
    Struct,
}

#[derive(Debug)]
pub struct ParsedFunction {
    pub name: String,
    pub name_span: Span,
    pub params: Vec<ParsedParameter>,
    pub generic_parameters: Vec<(String, Span)>,
    pub block: ParsedBlock,
    pub throws: bool,
    pub return_type: ParsedType,
    pub linkage: FunctionLinkage,
}

#[derive(Clone, Debug)]
pub struct ParsedParameter {
    pub requires_label: bool,
    pub variable: ParsedVariable,
}

#[derive(Clone, Debug)]
pub struct ParsedVariable {
    pub name: String,
    pub ty: ParsedType,
    pub mutable: bool,
}

impl ParsedFunction {
    pub fn new(linkage: FunctionLinkage) -> Self {
        ParsedFunction {
            name: String::new(),
            name_span: Span {
                file_id: 0,
                start: 0,
                end: 0,
            },
            params: Vec::new(),
            generic_parameters: Vec::new(),
            block: ParsedBlock::new(),
            throws: false,
            return_type: ParsedType::Empty,
            linkage,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum ParsedStatement {
    Expression(ParsedExpression),
    Defer(Box<ParsedStatement>),
    UnsafeBlock(ParsedBlock),
    VarDecl(ParsedVarDecl, ParsedExpression),
    If(ParsedExpression, ParsedBlock, Option<Box<ParsedStatement>>),
    Block(ParsedBlock),
    Loop(ParsedBlock),
    While(ParsedExpression, ParsedBlock),
    For(String, ParsedExpression, ParsedBlock),
    Break,
    Continue,
    Return(ParsedExpression),
    Throw(ParsedExpression),
    Try(Box<ParsedStatement>, String, Span, ParsedBlock),
    InlineCpp(ParsedBlock, Span),
    Garbage,
}

#[derive(Debug, Clone, PartialEq)]
pub struct ParsedBlock {
    pub stmts: Vec<ParsedStatement>,
}

impl ParsedBlock {
    pub fn new() -> Self {
        Self { stmts: Vec::new() }
    }
}

#[derive(Debug, Clone)]
pub enum MatchBody {
    Expression(ParsedExpression),
    Block(ParsedBlock),
}

#[derive(Debug, Clone)]
pub enum MatchCase {
    EnumVariant {
        variant_name: Vec<(String, Span)>,
        variant_arguments: Vec<(Option<String>, String)>,
        arguments_span: Span,
        body: MatchBody,
    },
}

// TODO: add spans to individual expressions
// so we can give better errors during typecheck
#[derive(Debug, Clone)]
pub enum ParsedExpression {
    // Standalone
    Boolean(bool, Span),
    NumericConstant(NumericConstant, Span),
    QuotedString(String, Span),
    CharacterLiteral(char, Span),
    Array(Vec<ParsedExpression>, Option<Box<ParsedExpression>>, Span),
    Dictionary(Vec<(ParsedExpression, ParsedExpression)>, Span),
    Set(Vec<ParsedExpression>, Span),
    IndexedExpression(Box<ParsedExpression>, Box<ParsedExpression>, Span),
    UnaryOp(Box<ParsedExpression>, UnaryOperator, Span),
    BinaryOp(
        Box<ParsedExpression>,
        BinaryOperator,
        Box<ParsedExpression>,
        Span,
    ),
    Var(String, Span),
    Tuple(Vec<ParsedExpression>, Span),
    Range(Box<ParsedExpression>, Box<ParsedExpression>, Span),
    Match(Box<ParsedExpression>, Vec<MatchCase>, Span),

    IndexedTuple(Box<ParsedExpression>, usize, Span),
    IndexedStruct(Box<ParsedExpression>, String, Span),

    Call(ParsedCall, Span),
    MethodCall(Box<ParsedExpression>, ParsedCall, Span),

    ForcedUnwrap(Box<ParsedExpression>, Span),

    // FIXME: These should be implemented as `enum` variant values once available.
    OptionalNone(Span),
    OptionalSome(Box<ParsedExpression>, Span),

    // Not standalone
    Operator(BinaryOperator, Span),

    // Parsing error
    Garbage(Span),
}

impl ParsedExpression {
    pub fn span(&self) -> Span {
        match self {
            ParsedExpression::Boolean(_, span) => *span,
            ParsedExpression::NumericConstant(_, span) => *span,
            ParsedExpression::QuotedString(_, span) => *span,
            ParsedExpression::CharacterLiteral(_, span) => *span,
            ParsedExpression::Array(_, _, span) => *span,
            ParsedExpression::Dictionary(_, span) => *span,
            ParsedExpression::Set(_, span) => *span,
            ParsedExpression::Tuple(_, span) => *span,
            ParsedExpression::Range(_, _, span) => *span,
            ParsedExpression::IndexedExpression(_, _, span) => *span,
            ParsedExpression::IndexedTuple(_, _, span) => *span,
            ParsedExpression::IndexedStruct(_, _, span) => *span,
            ParsedExpression::Call(_, span) => *span,
            ParsedExpression::MethodCall(_, _, span) => *span,
            ParsedExpression::UnaryOp(_, _, span) => *span,
            ParsedExpression::BinaryOp(_, _, _, span) => *span,
            ParsedExpression::Var(_, span) => *span,
            ParsedExpression::Operator(_, span) => *span,
            ParsedExpression::OptionalNone(span) => *span,
            ParsedExpression::OptionalSome(_, span) => *span,
            ParsedExpression::ForcedUnwrap(_, span) => *span,
            ParsedExpression::Match(_, _, span) => *span,
            ParsedExpression::Garbage(span) => *span,
        }
    }
}

impl PartialEq for ParsedExpression {
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
pub enum TypeCast {
    Fallible(ParsedType),
    Infallible(ParsedType),
    Saturating(ParsedType),
    Truncating(ParsedType),
}

impl TypeCast {
    pub fn unchecked_type(&self) -> ParsedType {
        match self {
            TypeCast::Fallible(ty) => ty.clone(),
            TypeCast::Infallible(ty) => ty.clone(),
            TypeCast::Saturating(ty) => ty.clone(),
            TypeCast::Truncating(ty) => ty.clone(),
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
    LogicalNot,
    BitwiseNot,
    TypeCast(TypeCast),
    Is(ParsedType),
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
    LogicalAnd,
    LogicalOr,
    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,
    BitwiseLeftShift,
    BitwiseRightShift,
    ArithmeticLeftShift,
    ArithmeticRightShift,
    Assign,
    AddAssign,
    SubtractAssign,
    MultiplyAssign,
    DivideAssign,
    ModuloAssign,
    BitwiseAndAssign,
    BitwiseOrAssign,
    BitwiseXorAssign,
    BitwiseLeftShiftAssign,
    BitwiseRightShiftAssign,
    NoneCoalescing,
}

impl ParsedExpression {
    // Relative weighting of precedence. Numbers are made up
    // with the only importance being how they relate to each
    // other
    pub fn precedence(&self) -> u64 {
        match self {
            ParsedExpression::Operator(BinaryOperator::Multiply, _)
            | ParsedExpression::Operator(BinaryOperator::Modulo, _)
            | ParsedExpression::Operator(BinaryOperator::Divide, _) => 100,
            ParsedExpression::Operator(BinaryOperator::Add, _)
            | ParsedExpression::Operator(BinaryOperator::Subtract, _) => 90,
            ParsedExpression::Operator(BinaryOperator::BitwiseLeftShift, _)
            | ParsedExpression::Operator(BinaryOperator::BitwiseRightShift, _)
            | ParsedExpression::Operator(BinaryOperator::ArithmeticLeftShift, _)
            | ParsedExpression::Operator(BinaryOperator::ArithmeticRightShift, _) => 85,
            ParsedExpression::Operator(BinaryOperator::LessThan, _)
            | ParsedExpression::Operator(BinaryOperator::LessThanOrEqual, _)
            | ParsedExpression::Operator(BinaryOperator::GreaterThan, _)
            | ParsedExpression::Operator(BinaryOperator::GreaterThanOrEqual, _)
            | ParsedExpression::Operator(BinaryOperator::Equal, _)
            | ParsedExpression::Operator(BinaryOperator::NotEqual, _) => 80,
            ParsedExpression::Operator(BinaryOperator::BitwiseAnd, _) => 73,
            ParsedExpression::Operator(BinaryOperator::BitwiseXor, _) => 72,
            ParsedExpression::Operator(BinaryOperator::BitwiseOr, _) => 71,
            ParsedExpression::Operator(BinaryOperator::LogicalAnd, _) => 70,
            ParsedExpression::Operator(BinaryOperator::LogicalOr, _)
            | ParsedExpression::Operator(BinaryOperator::NoneCoalescing, _) => 69,
            ParsedExpression::Operator(BinaryOperator::Assign, _)
            | ParsedExpression::Operator(BinaryOperator::BitwiseAndAssign, _)
            | ParsedExpression::Operator(BinaryOperator::BitwiseOrAssign, _)
            | ParsedExpression::Operator(BinaryOperator::BitwiseXorAssign, _)
            | ParsedExpression::Operator(BinaryOperator::BitwiseLeftShiftAssign, _)
            | ParsedExpression::Operator(BinaryOperator::BitwiseRightShiftAssign, _)
            | ParsedExpression::Operator(BinaryOperator::AddAssign, _)
            | ParsedExpression::Operator(BinaryOperator::SubtractAssign, _)
            | ParsedExpression::Operator(BinaryOperator::MultiplyAssign, _)
            | ParsedExpression::Operator(BinaryOperator::ModuloAssign, _)
            | ParsedExpression::Operator(BinaryOperator::DivideAssign, _) => 50,
            _ => 0,
        }
    }
}

impl ParsedNamespace {
    pub fn new() -> Self {
        Self {
            name: None,
            functions: Vec::new(),
            structs: Vec::new(),
            enums: Vec::new(),
            namespaces: Vec::new(),
        }
    }
}

pub fn parse_namespace(
    tokens: &[Token],
    index: &mut usize,
) -> (ParsedNamespace, Option<JaktError>) {
    trace!("parse_namespace");

    let mut error = None;

    let mut parsed_namespace = ParsedNamespace::new();

    while *index < tokens.len() {
        let token = &tokens[*index];

        match token {
            Token {
                contents: TokenContents::Name(name),
                span,
            } => match name.as_str() {
                "function" => {
                    let (fun, err) = parse_function(tokens, index, FunctionLinkage::Internal);
                    error = error.or(err);

                    parsed_namespace.functions.push(fun);
                }
                "enum" => {
                    let (enum_, err) = parse_enum(tokens, index, DefinitionLinkage::Internal);
                    error = error.or(err);

                    parsed_namespace.enums.push(enum_);
                }
                "struct" => {
                    let (structure, err) = parse_struct(
                        tokens,
                        index,
                        DefinitionLinkage::Internal,
                        DefinitionType::Struct,
                    );
                    error = error.or(err);

                    parsed_namespace.structs.push(structure);
                }
                "class" => {
                    let (structure, err) = parse_struct(
                        tokens,
                        index,
                        DefinitionLinkage::Internal,
                        DefinitionType::Class,
                    );
                    error = error.or(err);

                    parsed_namespace.structs.push(structure);
                }
                "namespace" => {
                    *index += 1;

                    if *index + 2 < tokens.len() {
                        // First is the name
                        // Then the LCurly and RCurly, then we parse the contents inside
                        let mut name = None;
                        match &tokens[*index].contents {
                            TokenContents::Name(namespace_name) => {
                                *index += 1;
                                name = Some(namespace_name.clone())
                            }
                            _ => {}
                        }

                        match &tokens[*index].contents {
                            TokenContents::LCurly => {
                                *index += 1;

                                let (mut namespace, err) = parse_namespace(tokens, index);
                                error = error.or(err);

                                *index += 1;
                                if *index < tokens.len() {
                                    if tokens[*index].contents == TokenContents::RCurly {
                                        *index += 1;
                                    }
                                }
                                namespace.name = name;
                                parsed_namespace.namespaces.push(namespace);
                            }
                            _ => {}
                        }
                    }
                }
                "extern" => {
                    if *index + 1 < tokens.len() {
                        match &tokens[*index + 1] {
                            Token {
                                contents: TokenContents::Name(name),
                                span,
                            } => match name.as_str() {
                                "function" => {
                                    *index += 1;
                                    let (fun, err) =
                                        parse_function(tokens, index, FunctionLinkage::External);
                                    error = error.or(err);

                                    parsed_namespace.functions.push(fun);
                                }
                                "struct" => {
                                    *index += 1;
                                    let (structure, err) = parse_struct(
                                        tokens,
                                        index,
                                        DefinitionLinkage::External,
                                        DefinitionType::Struct,
                                    );
                                    error = error.or(err);

                                    parsed_namespace.structs.push(structure);
                                }
                                "class" => {
                                    *index += 1;
                                    let (structure, err) = parse_struct(
                                        tokens,
                                        index,
                                        DefinitionLinkage::External,
                                        DefinitionType::Class,
                                    );
                                    error = error.or(err);

                                    parsed_namespace.structs.push(structure);
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
                    *index += 1;

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
                *index += 1;
            }
            Token {
                contents: TokenContents::RCurly,
                ..
            } => {
                break;
            }
            Token {
                contents: TokenContents::Eof,
                ..
            } => {
                break;
            }
            Token { span, .. } => {
                trace!("ERROR: unexpected token (expected keyword)");
                *index += 1;

                error = error.or(Some(JaktError::ParserError(
                    "unexpected token (expected keyword)".to_string(),
                    *span,
                )));
            }
        }
    }

    (parsed_namespace, error)
}

fn skip_newlines(tokens: &[Token], index: &mut usize) {
    while let Token {
        contents: TokenContents::Eol,
        ..
    } = tokens[*index]
    {
        *index += 1;
    }
}

pub fn parse_enum(
    tokens: &[Token],
    index: &mut usize,
    definition_linkage: DefinitionLinkage,
) -> (ParsedEnum, Option<JaktError>) {
    trace!(format!("parse_enum({:?})", tokens[*index]));

    let mut error = None;
    let start_index = *index;
    let mut enum_ = ParsedEnum {
        name: "".to_string(),
        definition_linkage,
        generic_parameters: vec![],
        variants: Vec::new(),
        span: Span {
            file_id: tokens[start_index].span.file_id,
            start: tokens[start_index].span.start,
            end: tokens[*index].span.end,
        },
        underlying_type: ParsedType::Empty,
    };

    *index += 1;

    skip_newlines(tokens, index);
    if let Some(Token {
        contents: TokenContents::Name(name),
        ..
    }) = tokens.get(*index)
    {
        trace!(format!("enum name: {}", name));
        *index += 1;
        enum_.name = name.to_string();
        // Following the name can either be a `:` to denote the underlying type, a `<` to denote generic parameters, or nothing.
        skip_newlines(tokens, index);
        match tokens.get(*index) {
            Some(Token {
                contents: TokenContents::Colon,
                ..
            }) => {
                trace!("enum with underlying type");
                *index += 1;
                let (type_, parse_error) = parse_typename(tokens, index);
                enum_.underlying_type = type_;
                error = error.or(parse_error);
                trace!(format!("next token: {:?}", tokens[*index]));
            }
            Some(Token {
                contents: TokenContents::LessThan,
                ..
            }) => {
                trace!("enum with generic parameters");
                let (params, parse_error) = parse_generic_parameters(tokens, index);
                enum_.generic_parameters = params;
                error = error.or(parse_error);
            }
            _ => (),
        }

        // Now parse the body of the enum, starting with the `{`
        skip_newlines(tokens, index);
        if !matches!(
            tokens.get(*index),
            Some(Token {
                contents: TokenContents::LCurly,
                ..
            })
        ) {
            error = error.or(Some(JaktError::ParserError(
                "expected `{` to start the enum body".to_string(),
                tokens[*index].span,
            )));
        } else {
            *index += 1;
        }
        trace!(format!("enum body: {:?}", tokens[*index]));

        // Variants in one of the following forms:
        // - Ident(name) Colon Type
        // - Ident(name) LCurly struct_body RCurly
        // - Ident(name) Equal Expression
        //    expression should evaluate to the underlying type (not allowed if no underlying type)
        // - Ident(name)

        skip_newlines(tokens, index);
        while !matches!(
            tokens.get(*index),
            Some(Token {
                contents: TokenContents::RCurly,
                ..
            }) | None
        ) {
            trace!(format!("parse_enum_variant({:?})", tokens[*index]));
            let start_index = *index;
            let variant_name = tokens.get(*index);
            if !matches!(
                variant_name,
                Some(Token {
                    contents: TokenContents::Name(_),
                    ..
                })
            ) {
                error = error.or(Some(JaktError::ParserError(
                    "expected variant name".to_string(),
                    tokens[*index].span,
                )));
                break;
            }

            let name = match &variant_name.unwrap().contents {
                TokenContents::Name(name) => name,
                _ => unreachable!(),
            };

            *index += 1;

            match tokens.get(*index) {
                Some(Token {
                    contents: TokenContents::Colon,
                    ..
                }) => {
                    trace!("variant with type");
                    *index += 1;
                    let (variant_type, type_error) = parse_typename(tokens, index);
                    error = error.or(type_error);
                    enum_.variants.push(EnumVariant::Typed(
                        name.to_string(),
                        variant_type,
                        Span {
                            file_id: tokens[*index].span.file_id,
                            start: tokens[start_index].span.start,
                            end: tokens[*index].span.end,
                        },
                    ));
                }
                Some(Token {
                    contents: TokenContents::LCurly,
                    ..
                }) => {
                    *index += 1;
                    let mut members = Vec::new();
                    skip_newlines(tokens, index);
                    while !matches!(
                        tokens.get(*index),
                        Some(Token {
                            contents: TokenContents::RCurly,
                            ..
                        }) | None
                    ) {
                        let (decl, parse_error) = parse_variable_declaration(tokens, index);
                        error = error.or(parse_error);
                        members.push(decl);
                        // Allow a comma or a newline after each member
                        if let Some(Token {
                            contents: TokenContents::Comma | TokenContents::Eol,
                            ..
                        }) = tokens.get(*index)
                        {
                            *index += 1;
                        }
                    }
                    *index += 1;
                    enum_.variants.push(EnumVariant::StructLike(
                        name.to_string(),
                        members,
                        Span {
                            file_id: tokens[*index].span.file_id,
                            start: tokens[start_index].span.start,
                            end: tokens[*index].span.end,
                        },
                    ));
                }
                Some(Token {
                    contents: TokenContents::Equal,
                    ..
                }) => {
                    if let ParsedType::Empty = enum_.underlying_type {
                        error = error.or(Some(JaktError::ParserError(
                            "enums with explicit values must have an underlying type".to_string(),
                            tokens[*index].span,
                        )));
                    }
                    *index += 1;
                    let (expr, parse_error) = parse_expression(
                        tokens,
                        index,
                        ExpressionKind::ExpressionWithoutAssignment,
                    );
                    error = error.or(parse_error);
                    enum_.variants.push(EnumVariant::WithValue(
                        name.to_string(),
                        expr,
                        Span {
                            file_id: tokens[*index].span.file_id,
                            start: tokens[*index].span.start,
                            end: tokens[*index].span.end,
                        },
                    ));
                }
                Some(Token {
                    contents: TokenContents::RCurly,
                    ..
                }) => {
                    break;
                }
                _ => {
                    enum_.variants.push(EnumVariant::Untyped(
                        name.to_string(),
                        Span {
                            file_id: tokens[*index].span.file_id,
                            start: tokens[*index].span.start,
                            end: tokens[*index].span.end,
                        },
                    ));
                }
            }

            // Require a comma or a newline after each variant
            if let Some(Token {
                contents: TokenContents::Comma | TokenContents::Eol,
                ..
            }) = tokens.get(*index)
            {
                *index += 1;
            } else {
                trace!(format!(
                    "Expected comma or newline after enum variant, found {:?}",
                    tokens.get(*index)
                ));
                error = error.or(Some(JaktError::ParserError(
                    "expected comma or newline after enum variant".to_string(),
                    tokens[*index].span,
                )));
            }
        }

        if tokens.len() == *index {
            error = error.or(Some(JaktError::ParserError(
                "expected `}` to end the enum body".to_string(),
                tokens[*index].span,
            )));
        } else {
            *index += 1;
        }
    } else {
        error = error.or(Some(JaktError::ParserError(
            "expected enum name".to_string(),
            tokens[*index].span,
        )));
    }

    (enum_, error)
}

pub fn parse_generic_parameters(
    tokens: &[Token],
    index: &mut usize,
) -> (Vec<(String, Span)>, Option<JaktError>) {
    if !matches!(
        tokens.get(*index),
        Some(Token {
            contents: TokenContents::LessThan,
            ..
        })
    ) {
        return (Vec::new(), None);
    }

    *index += 1;

    let mut generic_parameters = vec![];

    while !matches!(
        tokens.get(*index),
        Some(Token {
            contents: TokenContents::GreaterThan,
            ..
        }) | None
    ) {
        skip_newlines(tokens, index);
        match tokens.get(*index) {
            Some(Token {
                contents: TokenContents::Name(name),
                span,
            }) => {
                generic_parameters.push((name.to_string(), *span));
                *index += 1;
                if let Some(Token {
                    contents: TokenContents::Comma | TokenContents::Eol,
                    ..
                }) = tokens.get(*index)
                {
                    *index += 1;
                }
            }
            _ => {
                return (
                    generic_parameters,
                    Some(JaktError::ParserError(
                        "expected generic parameter name".to_string(),
                        tokens[*index].span,
                    )),
                );
            }
        }
    }

    if let Some(Token {
        contents: TokenContents::GreaterThan,
        ..
    }) = tokens.get(*index)
    {
        *index += 1;
    } else {
        return (
            generic_parameters,
            Some(JaktError::ParserError(
                "expected `>` to end the generic parameters".to_string(),
                tokens[*index].span,
            )),
        );
    }

    (generic_parameters, None)
}

pub fn parse_struct(
    tokens: &[Token],
    index: &mut usize,
    definition_linkage: DefinitionLinkage,
    definition_type: DefinitionType,
) -> (ParsedStruct, Option<JaktError>) {
    trace!(format!("parse_struct: {:?}", tokens[*index]));

    let mut error = None;
    let mut generic_parameters = vec![];

    *index += 1;

    if *index < tokens.len() {
        // we're expecting the name of the struct
        match &tokens[*index] {
            Token {
                contents: TokenContents::Name(struct_name),
                ..
            } => {
                *index += 1;

                // Check for generic
                let (params, parse_error) = parse_generic_parameters(tokens, index);
                generic_parameters = params;
                error = error.or(parse_error);

                // Read in definition
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

                let mut methods = Vec::new();

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

                        TokenContents::Name(name) if name == "function" => {
                            // Lets parse a method

                            let function_linkage = match definition_linkage {
                                DefinitionLinkage::Internal => FunctionLinkage::Internal,
                                DefinitionLinkage::External => FunctionLinkage::External,
                            };

                            let (function, err) = parse_function(tokens, index, function_linkage);
                            error = error.or(err);

                            methods.push(function);
                        }

                        TokenContents::Name(..) => {
                            // Lets parse a parameter

                            let (mut var_decl, err) = parse_variable_declaration(tokens, index);
                            error = error.or(err);

                            // Ignore immutable flag for now
                            var_decl.mutable = false;

                            if var_decl.ty == ParsedType::Empty {
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
                            break;
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
                    ParsedStruct {
                        name: struct_name.clone(),
                        generic_parameters,
                        fields,
                        methods,
                        span: tokens[*index - 1].span,
                        definition_linkage,
                        definition_type,
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
                    ParsedStruct {
                        name: String::new(),
                        generic_parameters,
                        fields: Vec::new(),
                        methods: Vec::new(),
                        span: tokens[*index].span,
                        definition_linkage,
                        definition_type,
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
            ParsedStruct {
                name: String::new(),
                generic_parameters,
                fields: Vec::new(),
                methods: Vec::new(),
                span: tokens[*index].span,
                definition_linkage,
                definition_type,
            },
            error,
        )
    }
}

pub fn parse_function(
    tokens: &[Token],
    index: &mut usize,
    linkage: FunctionLinkage,
) -> (ParsedFunction, Option<JaktError>) {
    trace!(format!("parse_function: {:?}", tokens[*index]));

    let mut error = None;
    let generic_parameters;

    *index += 1;

    if *index < tokens.len() {
        // we're expecting the name of the function
        match &tokens[*index] {
            Token {
                contents: TokenContents::Name(function_name),
                ..
            } => {
                let name_span = tokens[*index].span;

                *index += 1;

                // Check for generic
                let (params, err) = parse_generic_parameters(tokens, index);
                error = error.or(err);
                generic_parameters = params;

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
                let mut current_param_is_mutable = false;

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

                        TokenContents::Name(name) if name == "anonymous" => {
                            current_param_requires_label = false;
                            *index += 1;
                        }

                        TokenContents::Name(name) if name == "mutable" => {
                            current_param_is_mutable = true;
                            *index += 1;
                        }

                        TokenContents::Name(name) if name == "this" => {
                            *index += 1;

                            params.push(ParsedParameter {
                                requires_label: false,
                                variable: ParsedVariable {
                                    name: "this".to_string(),
                                    ty: ParsedType::Empty,
                                    mutable: current_param_is_mutable,
                                },
                            });
                        }

                        TokenContents::Name(..) => {
                            // Now lets parse a parameter

                            let (var_decl, err) = parse_variable_declaration(tokens, index);
                            error = error.or(err);

                            if var_decl.ty == ParsedType::Empty {
                                trace!("ERROR: parameter missing type");

                                error = error.or(Some(JaktError::ParserError(
                                    "parameter missing type".to_string(),
                                    var_decl.span,
                                )))
                            }

                            params.push(ParsedParameter {
                                requires_label: current_param_requires_label,
                                variable: ParsedVariable {
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

                let mut throws = false;

                if *index + 1 < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Name(name) if name == "throws" => {
                            *index += 1;
                            throws = true;
                        }
                        _ => {}
                    }
                }

                let mut return_type = ParsedType::Empty;

                let mut fat_arrow_expr = None;

                if *index + 2 < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::FatArrow => {
                            *index += 1;

                            let (expr, err) = parse_expression(
                                tokens,
                                index,
                                ExpressionKind::ExpressionWithoutAssignment,
                            );
                            return_type = ParsedType::Empty;
                            fat_arrow_expr = Some(expr);
                            error = error.or(err);

                            *index += 1;
                        }
                        TokenContents::Minus => {
                            *index += 1;

                            match &tokens[*index].contents {
                                TokenContents::GreaterThan => {
                                    *index += 1;

                                    let (ret_type, err) = parse_typename(tokens, index);
                                    return_type = ret_type;
                                    error = error.or(err);
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
                        tokens[tokens.len() - 1].span,
                    )));
                }

                if let FunctionLinkage::External = linkage {
                    return (
                        ParsedFunction {
                            name: function_name.clone(),
                            name_span,
                            params,
                            generic_parameters,
                            block: ParsedBlock::new(),
                            throws,
                            return_type,
                            linkage,
                        },
                        error,
                    );
                }

                let (block, err) = match fat_arrow_expr {
                    Some(expr) => {
                        let mut block = ParsedBlock::new();
                        block.stmts.push(ParsedStatement::Return(expr));
                        (block, None)
                    }
                    None => parse_block(tokens, index),
                };
                error = error.or(err);

                (
                    ParsedFunction {
                        name: function_name.clone(),
                        name_span,
                        params,
                        generic_parameters,
                        block,
                        throws,
                        return_type,
                        linkage,
                    },
                    error,
                )
            }
            _ => {
                trace!("ERROR: expected function name");

                (
                    ParsedFunction::new(FunctionLinkage::Internal),
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
            ParsedFunction::new(FunctionLinkage::Internal),
            Some(JaktError::ParserError(
                "incomplete function definition".to_string(),
                tokens[*index].span,
            )),
        )
    }
}

pub fn parse_block(tokens: &[Token], index: &mut usize) -> (ParsedBlock, Option<JaktError>) {
    trace!(format!("parse_block: {:?}", tokens[*index]));

    let mut block = ParsedBlock::new();
    let mut error = None;

    if tokens.get(*index).is_none() {
        trace!("ERROR: incomplete block");
        error = Some(JaktError::ParserError(
            "incomplete block".to_string(),
            tokens[tokens.len() - 1].span,
        ));
        return (block, error);
    }

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
        ParsedBlock::new(),
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

pub fn parse_statement(
    tokens: &[Token],
    index: &mut usize,
) -> (ParsedStatement, Option<JaktError>) {
    trace!(format!("parse_statement: {:?}", tokens[*index]));

    let mut error = None;

    match &tokens[*index].contents {
        TokenContents::Name(name) if name == "throw" => {
            trace!("parsing throw");

            *index += 1;

            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            (ParsedStatement::Throw(expr), error)
        }
        TokenContents::Name(name) if name == "defer" => {
            trace!("parsing defer");

            *index += 1;

            let (statement, err) = parse_statement(tokens, index);
            error = error.or(err);

            (ParsedStatement::Defer(Box::new(statement)), error)
        }
        TokenContents::Name(name) if name == "unsafe" => {
            trace!("parsing unsafe");

            *index += 1;

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (ParsedStatement::UnsafeBlock(block), error)
        }
        TokenContents::Name(name) if name == "if" => parse_if_statement(tokens, index),
        TokenContents::Name(name) if name == "break" => {
            trace!("parsing break");
            *index += 1;
            (ParsedStatement::Break, None)
        }
        TokenContents::Name(name) if name == "continue" => {
            trace!("parsing continue");
            *index += 1;
            (ParsedStatement::Continue, None)
        }
        TokenContents::Name(name) if name == "loop" => {
            trace!("parsing loop");

            *index += 1;

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (ParsedStatement::Loop(block), error)
        }
        TokenContents::Name(name) if name == "while" => {
            trace!("parsing while");

            *index += 1;

            let (cond, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (ParsedStatement::While(cond, block), error)
        }
        TokenContents::Name(name) if name == "try" => {
            trace!("parsing try");

            *index += 1;

            let (stmt, err) = parse_statement(tokens, index);
            error = error.or(err);

            let mut error_name = String::new();
            let mut error_span = &tokens[*index].span;

            match &tokens[*index].contents {
                TokenContents::Name(name) if name == "catch" => {
                    *index += 1;

                    // FIXME: Error about missing error binding
                    if let TokenContents::Name(name) = &tokens[*index].contents {
                        error_span = &tokens[*index].span;
                        error_name = name.clone();
                        *index += 1;
                    }
                }
                _ => {
                    // FIXME: Error about missing "catch"
                }
            }

            let (catch_block, err) = parse_block(tokens, index);
            error = error.or(err);

            (
                ParsedStatement::Try(Box::new(stmt), error_name, *error_span, catch_block),
                error,
            )
        }
        TokenContents::Name(name) if name == "for" => {
            trace!("parsing for");

            *index += 1;

            if let TokenContents::Name(iterator_name) = &tokens[*index].contents {
                *index += 1;

                match &tokens[*index].contents {
                    TokenContents::Name(keyword) if keyword == "in" => {
                        *index += 1;
                        let (range_expr, err) = parse_expression(
                            tokens,
                            index,
                            ExpressionKind::ExpressionWithoutAssignment,
                        );
                        error = error.or(err);

                        let (block, err) = parse_block(tokens, index);
                        error = error.or(err);

                        (
                            ParsedStatement::For(iterator_name.clone(), range_expr, block),
                            error,
                        )
                    }
                    _ => (ParsedStatement::Garbage, error),
                }
            } else {
                (ParsedStatement::Garbage, error)
            }
        }
        TokenContents::Name(name) if name == "return" => {
            trace!("parsing return");

            *index += 1;

            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            (ParsedStatement::Return(expr), error)
        }
        TokenContents::Name(name) if name == "let" => {
            trace!("parsing let");

            let mutable = if *index + 1 < tokens.len() {
                match &tokens[*index + 1].contents {
                    TokenContents::Name(name) if name == "mutable" => {
                        *index += 1;
                        true
                    }
                    _ => false,
                }
            } else {
                false
            };

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

                            (ParsedStatement::VarDecl(var_decl, expr), error)
                        } else {
                            (
                                ParsedStatement::Garbage,
                                Some(JaktError::ParserError(
                                    "expected initializer".to_string(),
                                    tokens[*index - 1].span,
                                )),
                            )
                        }
                    }
                    _ => (
                        ParsedStatement::Garbage,
                        Some(JaktError::ParserError(
                            "expected initializer".to_string(),
                            tokens[*index].span,
                        )),
                    ),
                }
            } else {
                (
                    ParsedStatement::Garbage,
                    Some(JaktError::ParserError(
                        "expected initializer".to_string(),
                        tokens[*index].span,
                    )),
                )
            }
        }
        TokenContents::Name(name) if name == "cpp" => {
            trace!("parsing inline cpp block");

            *index += 1;

            let start_span = tokens[*index].span;

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: tokens[*index].span.end,
            };

            (ParsedStatement::InlineCpp(block, span), error)
        }
        TokenContents::LCurly => {
            trace!("parsing block from statement parser");

            let (block, err) = parse_block(tokens, index);
            error = error.or(err);

            (ParsedStatement::Block(block), error)
        }
        _ => {
            trace!("parsing expression from statement parser");

            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithAssignments);
            error = error.or(err);

            // Make sure, if there is an error and we can make progress, that we make progress.
            // This allows the parser to be more forgiving when there are errors
            // and to ensure parsing continues to make progress.
            if error.is_some() && *index < tokens.len() {
                *index += 1;
            }

            (ParsedStatement::Expression(expr), error)
        }
    }
}

fn parse_if_statement(tokens: &[Token], index: &mut usize) -> (ParsedStatement, Option<JaktError>) {
    trace!(format!("parse_if_statement: {:?}", tokens[*index]));

    let mut error = None;

    match &tokens[*index].contents {
        TokenContents::Name(name) if name == "if" => {
            // Good, we have our keyword
        }
        _ => {
            return (
                ParsedStatement::Garbage,
                Some(JaktError::ParserError(
                    "expected if statement".to_string(),
                    tokens[*index].span,
                )),
            );
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

                            else_stmt = Some(Box::new(ParsedStatement::Block(else_block)));
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

    (ParsedStatement::If(cond, block, else_stmt), error)
}

pub fn parse_expression(
    tokens: &[Token],
    index: &mut usize,
    expression_kind: ExpressionKind,
) -> (ParsedExpression, Option<JaktError>) {
    trace!(format!("parse_expression: {:?}", tokens[*index]));

    // As the expr_stack grows, we increase the required precedence.
    // If, at any time, the operator we're looking at is the same or lower precedence
    // of what is in the expression stack, we collapse the expression stack.

    let mut error = None;

    let mut expr_stack: Vec<ParsedExpression> = vec![];
    let mut last_prec = 1000000;

    let (lhs, err) = parse_operand(tokens, index);
    error = error.or(err);

    expr_stack.push(lhs);

    while *index < tokens.len() {
        // Test to see if the next token is an operator
        if tokens[*index].contents == TokenContents::Eol {
            break;
        }

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

            expr_stack.push(ParsedExpression::Garbage(tokens[*index - 1].span));
            expr_stack.push(ParsedExpression::Garbage(tokens[*index - 1].span));
            break;
        }

        while tokens[*index].contents == TokenContents::Eol {
            *index += 1;
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
                ParsedExpression::Operator(op, _) => {
                    let span = Span {
                        file_id: lhs.span().file_id,
                        start: lhs.span().start,
                        end: rhs.span().end,
                    };
                    expr_stack.push(ParsedExpression::BinaryOp(
                        Box::new(lhs),
                        op,
                        Box::new(rhs),
                        span,
                    ));
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
            ParsedExpression::Operator(op, _) => {
                let span = Span {
                    file_id: lhs.span().file_id,
                    start: lhs.span().start,
                    end: rhs.span().end,
                };
                expr_stack.push(ParsedExpression::BinaryOp(
                    Box::new(lhs),
                    op,
                    Box::new(rhs),
                    span,
                ));
            }
            _ => panic!("internal error: operator is not an operator"),
        }
    }

    let output = expr_stack
        .pop()
        .expect("internal error: expression stack empty");

    (output, error)
}

pub fn parse_pattern_case(tokens: &[Token], index: &mut usize) -> (MatchCase, Option<JaktError>) {
    // case:
    // QualifiedName('(' ((name ':')? expression),* ')')? '=>' (expression | block)

    let mut error = None;
    let mut pattern = Vec::new();
    while let Some(Token {
        contents: TokenContents::Name(name),
        span,
    }) = tokens.get(*index)
    {
        *index += 1;
        if let Some(Token {
            contents: TokenContents::ColonColon,
            ..
        }) = tokens.get(*index)
        {
            *index += 1;
        } else {
            pattern.push((name.clone(), *span));
            break;
        }
        pattern.push((name.clone(), *span));
    }

    let mut arguments = Vec::new();
    let mut has_parens = false;
    let args_start = *index;

    if let Some(Token {
        contents: TokenContents::LParen,
        ..
    }) = tokens.get(*index)
    {
        has_parens = true;
        *index += 1;
        while !matches!(
            tokens.get(*index),
            Some(Token {
                contents: TokenContents::RParen,
                ..
            }) | None
        ) {
            if let Some(Token {
                contents: TokenContents::Name(name),
                ..
            }) = tokens.get(*index)
            {
                if let Some(Token {
                    contents: TokenContents::Colon,
                    ..
                }) = tokens.get(*index + 1)
                {
                    *index += 1;
                    if let Some(Token {
                        contents: TokenContents::Colon,
                        ..
                    }) = tokens.get(*index)
                    {
                        *index += 1;
                    } else {
                        error = Some(JaktError::ParserError(
                            "expected ':' after explicit pattern argument name".to_string(),
                            tokens.get(*index).unwrap().span,
                        ));
                        break;
                    }

                    if let Some(Token {
                        contents: TokenContents::Name(binding),
                        ..
                    }) = tokens.get(*index)
                    {
                        *index += 1;
                        arguments.push((Some(name.clone()), binding.clone()));
                    } else {
                        error = Some(JaktError::ParserError(
                            "expected pattern argument name".to_string(),
                            tokens.get(*index).unwrap().span,
                        ));
                        break;
                    }

                    if let Some(Token {
                        contents: TokenContents::Comma,
                        ..
                    }) = tokens.get(*index)
                    {
                        *index += 1;
                    }
                } else {
                    if let Some(Token {
                        contents: TokenContents::Name(binding),
                        ..
                    }) = tokens.get(*index)
                    {
                        *index += 1;
                        arguments.push((None, binding.clone()));
                    } else {
                        error = Some(JaktError::ParserError(
                            "expected pattern argument name".to_string(),
                            tokens.get(*index).unwrap().span,
                        ));
                        break;
                    }

                    if let Some(Token {
                        contents: TokenContents::Comma,
                        ..
                    }) = tokens.get(*index)
                    {
                        *index += 1;
                    }
                }
            } else if let Some(Token {
                contents: TokenContents::Name(binding),
                ..
            }) = tokens.get(*index)
            {
                *index += 1;
                arguments.push((None, binding.clone()));
            } else {
                error = Some(JaktError::ParserError(
                    "expected pattern argument name".to_string(),
                    tokens.get(*index).unwrap().span,
                ));
                break;
            }
        }
    }

    if has_parens {
        *index += 1;
    }
    let args_end = *index;

    if let Some(Token {
        contents: TokenContents::FatArrow,
        ..
    }) = tokens.get(*index)
    {
        *index += 1;
    } else {
        error = Some(JaktError::ParserError(
            "expected '=>' after pattern case".to_string(),
            tokens.get(*index).unwrap().span,
        ));
    }

    if let Some(Token {
        contents: TokenContents::LCurly,
        ..
    }) = tokens.get(*index)
    {
        *index += 1;
        let (block, err) = parse_block(tokens, index);
        error = error.or(err);
        (
            MatchCase::EnumVariant {
                variant_name: pattern,
                variant_arguments: arguments,
                arguments_span: Span {
                    file_id: tokens[args_start].span.file_id,
                    start: tokens[args_start].span.start,
                    end: tokens[args_end - 1].span.end,
                },
                body: MatchBody::Block(block),
            },
            error,
        )
    } else {
        let (expr, err) =
            parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
        error = error.or(err);
        (
            MatchCase::EnumVariant {
                variant_name: pattern,
                variant_arguments: arguments,
                arguments_span: Span {
                    file_id: tokens[args_start].span.file_id,
                    start: tokens[args_start].span.start,
                    end: tokens[args_end - 1].span.end,
                },
                body: MatchBody::Expression(expr),
            },
            error,
        )
    }
}

pub fn parse_patterns(tokens: &[Token], index: &mut usize) -> (Vec<MatchCase>, Option<JaktError>) {
    let mut cases = Vec::new();
    let mut error = None;

    skip_newlines(tokens, index);
    if !matches!(
        tokens.get(*index),
        Some(Token {
            contents: TokenContents::LCurly,
            ..
        })
    ) {
        skip_newlines(tokens, index);
        error = error.or(Some(JaktError::ParserError(
            "expected '{'".to_string(),
            tokens[*index].span,
        )));
        return (cases, error);
    }
    *index += 1;
    skip_newlines(tokens, index);

    while !matches!(
        tokens.get(*index),
        Some(Token {
            contents: TokenContents::RCurly,
            ..
        })
    ) {
        let (pattern, err) = parse_pattern_case(tokens, index);
        error = error.or(err);
        cases.push(pattern);

        if let TokenContents::Eol | TokenContents::Comma = tokens[*index].contents {
            *index += 1;
        }
    }

    skip_newlines(tokens, index);
    if !matches!(
        tokens.get(*index),
        Some(Token {
            contents: TokenContents::RCurly,
            ..
        })
    ) {
        error = error.or(Some(JaktError::ParserError(
            "expected '}'".to_string(),
            tokens[*index].span,
        )));
    }
    *index += 1;

    (cases, error)
}

pub fn parse_operand(tokens: &[Token], index: &mut usize) -> (ParsedExpression, Option<JaktError>) {
    trace!(format!("parse_operand: {:?}", tokens[*index]));

    let mut error = None;

    let span = tokens[*index].span;

    while *index < tokens.len() && tokens[*index].contents == TokenContents::Eol {
        *index += 1;
    }

    let mut expr = match &tokens[*index].contents {
        TokenContents::Name(name) if name == "true" => {
            *index += 1;
            ParsedExpression::Boolean(true, span)
        }
        TokenContents::Name(name) if name == "false" => {
            *index += 1;
            ParsedExpression::Boolean(false, span)
        }
        TokenContents::Name(name) if name == "and" => {
            *index += 1;
            ParsedExpression::Operator(BinaryOperator::LogicalAnd, span)
        }
        TokenContents::Name(name) if name == "or" => {
            *index += 1;
            ParsedExpression::Operator(BinaryOperator::LogicalOr, span)
        }
        TokenContents::Name(name) if name == "not" => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::LogicalNot, span)
        }
        TokenContents::Name(name) if name == "match" => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let (patterns, err) = parse_patterns(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            ParsedExpression::Match(Box::new(expr), patterns, span)
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
                            ParsedExpression::OptionalSome(Box::new(expr), span)
                        }
                        _ => {
                            let (call, err) = parse_call(tokens, index);
                            error = error.or(err);

                            ParsedExpression::Call(call, span)
                        }
                    },
                    TokenContents::LessThan => {
                        // We *try* to see if it's a generic, but the parse errors, we back up and try something else
                        let (call, err) = parse_call(tokens, index);

                        if err.is_some() {
                            match name.as_str() {
                                "None" => ParsedExpression::OptionalNone(span),
                                _ => ParsedExpression::Var(name.to_string(), span),
                            }
                        } else {
                            error = error.or(err);

                            ParsedExpression::Call(call, span)
                        }
                    }
                    _ => {
                        *index += 1;

                        match name.as_str() {
                            "None" => ParsedExpression::OptionalNone(span),
                            _ => ParsedExpression::Var(name.to_string(), span),
                        }
                    }
                }
            } else {
                *index += 1;

                ParsedExpression::Var(name.to_string(), span)
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
                    let mut exprs = vec![expr];

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

                    expr = ParsedExpression::Tuple(
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
            let (expr, err) = parse_array(tokens, index);
            error = error.or(err);
            expr
        }
        TokenContents::LCurly => {
            let (expr, err) = parse_set(tokens, index);
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

            ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::PreIncrement, span)
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

            ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::PreDecrement, span)
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

            ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::Negate, span)
        }
        TokenContents::Tilde => {
            let start_span = tokens[*index].span;

            *index += 1;

            let (expr, err) = parse_operand(tokens, index);
            error = error.or(err);

            let span = Span {
                file_id: start_span.file_id,
                start: start_span.start,
                end: expr.span().end,
            };

            ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::BitwiseNot, span)
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

            ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::Dereference, span)
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

                        ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::RawAddress, span)
                    }
                    _ => {
                        error = error.or(Some(JaktError::ParserError(
                            "ampersand not currently supported".to_string(),
                            tokens[*index - 1].span,
                        )));
                        ParsedExpression::Garbage(tokens[*index - 1].span)
                    }
                }
            } else {
                error = error.or(Some(JaktError::ParserError(
                    "ampersand not currently supported".to_string(),
                    tokens[*index - 1].span,
                )));
                ParsedExpression::Garbage(tokens[*index - 1].span)
            }
        }
        TokenContents::Number(constant) => {
            *index += 1;
            ParsedExpression::NumericConstant(constant.clone(), span)
        }
        TokenContents::QuotedString(str) => {
            *index += 1;
            ParsedExpression::QuotedString(str.to_string(), span)
        }
        TokenContents::SingleQuotedString(c) => {
            *index += 1;
            if let Some(first) = c.chars().next() {
                ParsedExpression::CharacterLiteral(first, span)
            } else {
                ParsedExpression::Garbage(span)
            }
        }
        _ => {
            trace!("ERROR: unsupported expression");
            error = error.or(Some(JaktError::ParserError(
                "unsupported expression".to_string(),
                tokens[*index].span,
            )));

            ParsedExpression::Garbage(span)
        }
    };

    // Check for postfix operators, while we're at it
    while *index < tokens.len() {
        match &tokens[*index].contents {
            TokenContents::DotDot => {
                *index += 1;
                let (end_expr, err) =
                    parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
                error = error.or(err);
                expr = ParsedExpression::Range(Box::new(expr), Box::new(end_expr), span);
            }
            TokenContents::ExclamationPoint => {
                *index += 1;
                // Forced Optional unwrap
                expr = ParsedExpression::ForcedUnwrap(Box::new(expr), span);
            }
            TokenContents::PlusPlus => {
                let end_span = tokens[*index].span;

                *index += 1;

                let span = Span {
                    file_id: expr.span().file_id,
                    start: expr.span().start,
                    end: end_span.end,
                };

                expr = ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::PostIncrement, span)
            }
            TokenContents::Name(name) if name == "is" => {
                let end_span = tokens[*index + 1].span;

                *index += 1;

                let span = Span {
                    file_id: expr.span().file_id,
                    start: expr.span().start,
                    end: end_span.end,
                };

                let (typename, err) = parse_typename(tokens, index);
                error = error.or(err);

                expr = ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::Is(typename), span)
            }

            TokenContents::Name(name) if name == "as" => {
                let end_span = tokens[*index + 1].span;

                *index += 1;

                let span = Span {
                    file_id: expr.span().file_id,
                    start: expr.span().start,
                    end: end_span.end,
                };

                let cast = match &tokens[*index].contents {
                    TokenContents::ExclamationPoint => {
                        *index += 1;
                        let (typename, err) = parse_typename(tokens, index);
                        error = error.or(err);
                        TypeCast::Infallible(typename)
                    }
                    TokenContents::QuestionMark => {
                        *index += 1;
                        let (typename, err) = parse_typename(tokens, index);
                        error = error.or(err);
                        TypeCast::Fallible(typename)
                    }
                    TokenContents::Name(name) if name == "truncated" => {
                        *index += 1;
                        let (typename, err) = parse_typename(tokens, index);
                        error = error.or(err);
                        TypeCast::Truncating(typename)
                    }
                    TokenContents::Name(name) if name == "saturated" => {
                        *index += 1;
                        let (typename, err) = parse_typename(tokens, index);
                        error = error.or(err);
                        TypeCast::Saturating(typename)
                    }
                    _ => {
                        error = error.or(Some(JaktError::ParserError(
                            "Invalid cast syntax".to_string(),
                            span,
                        )));
                        TypeCast::Truncating(ParsedType::Empty)
                    }
                };

                *index += 1;
                expr =
                    ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::TypeCast(cast), span)
            }
            TokenContents::MinusMinus => {
                let end_span = tokens[*index].span;

                *index += 1;

                let span = Span {
                    file_id: expr.span().file_id,
                    start: expr.span().start,
                    end: end_span.end,
                };

                expr = ParsedExpression::UnaryOp(Box::new(expr), UnaryOperator::PostDecrement, span)
            }
            TokenContents::ColonColon => {
                *index += 1;

                let mut namespace = Vec::new();

                match &expr {
                    ParsedExpression::Var(name, _) => namespace.push(name.clone()),
                    x => {
                        error = error.or(Some(JaktError::ParserError(
                            "expected namespace".to_string(),
                            x.span(),
                        )));
                    }
                }

                if *index >= tokens.len() {
                    error = error.or(Some(JaktError::ParserError(
                        "Incomplete static method call".to_string(),
                        tokens[*index].span,
                    )))
                }

                while *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Name(_) => {
                            *index += 1;
                            if *index < tokens.len() {
                                if tokens[*index].contents == TokenContents::LParen {
                                    *index -= 1;
                                    let (mut method, err) = parse_call(tokens, index);
                                    error = error.or(err);

                                    method.namespace = namespace;

                                    let span = Span {
                                        file_id: expr.span().file_id,
                                        start: expr.span().start,
                                        end: tokens[*index].span.end,
                                    };

                                    expr = ParsedExpression::Call(method, span);
                                    break;
                                } else if tokens[*index].contents == TokenContents::ColonColon {
                                    match &tokens[*index - 1].contents {
                                        TokenContents::Name(name) => namespace.push(name.clone()),
                                        _ => {
                                            error = error.or(Some(JaktError::ParserError(
                                                "expected namespace".to_string(),
                                                tokens[*index - 1].span,
                                            )));
                                        }
                                    }
                                    *index += 1;
                                } else if tokens[*index].contents == TokenContents::LessThan {
                                    *index -= 1;
                                    let (mut call, err) = parse_call(tokens, index);
                                    if err.is_some() {
                                        error = error.or(err);
                                    } else {
                                        call.namespace = namespace;
                                        expr = ParsedExpression::Call(call, span);
                                    }
                                    break;
                                } else {
                                    *index += 1;
                                    error = error.or(Some(JaktError::ParserError(
                                        "Unsupported static method call".to_string(),
                                        tokens[*index].span,
                                    )));
                                    break;
                                }
                            } else {
                                error = error.or(Some(JaktError::ParserError(
                                    "Unsupported static method call".to_string(),
                                    tokens[*index].span,
                                )));
                                break;
                            }
                        }

                        _ => {
                            *index += 1;
                            error = error.or(Some(JaktError::ParserError(
                                "Unsupported static method call".to_string(),
                                tokens[*index].span,
                            )));
                            break;
                        }
                    }
                }
            }
            TokenContents::Dot => {
                *index += 1;

                if *index < tokens.len() {
                    match &tokens[*index].contents {
                        TokenContents::Number(constant) => {
                            *index += 1;

                            let span = Span {
                                file_id: expr.span().file_id,
                                start: expr.span().start,
                                end: tokens[*index].span.end,
                            };

                            expr = ParsedExpression::IndexedTuple(
                                Box::new(expr),
                                constant.integer_constant().unwrap().to_usize(),
                                span,
                            );
                        }

                        TokenContents::Name(name) => {
                            *index += 1;
                            if *index < tokens.len() {
                                if tokens[*index].contents == TokenContents::LParen {
                                    *index -= 1;

                                    let span = Span {
                                        file_id: expr.span().file_id,
                                        start: expr.span().start,
                                        end: tokens[*index].span.end,
                                    };

                                    let (method, err) = parse_call(tokens, index);
                                    error = error.or(err);

                                    expr =
                                        ParsedExpression::MethodCall(Box::new(expr), method, span)
                                } else {
                                    let span = Span {
                                        file_id: expr.span().file_id,
                                        start: expr.span().start,
                                        end: tokens[*index - 1].span.end,
                                    };

                                    expr = ParsedExpression::IndexedStruct(
                                        Box::new(expr),
                                        name.to_string(),
                                        span,
                                    );
                                }
                            } else {
                                let span = Span {
                                    file_id: expr.span().file_id,
                                    start: expr.span().start,
                                    end: tokens[*index].span.end,
                                };

                                expr = ParsedExpression::IndexedStruct(
                                    Box::new(expr),
                                    name.to_string(),
                                    span,
                                );
                            }
                        }

                        _ => {
                            *index += 1;
                            error = error.or(Some(JaktError::ParserError(
                                "Unsupported dot operation".to_string(),
                                tokens[*index].span,
                            )))
                        }
                    }
                } else {
                    *index += 1;
                    error = error.or(Some(JaktError::ParserError(
                        "Incomplete dot operation".to_string(),
                        tokens[*index].span,
                    )))
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

                    expr = ParsedExpression::IndexedExpression(
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

pub fn parse_operator(
    tokens: &[Token],
    index: &mut usize,
) -> (ParsedExpression, Option<JaktError>) {
    trace!(format!("parse_operator: {:?}", tokens[*index]));

    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::QuestionMarkQuestionMark => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::NoneCoalescing, span),
                None,
            )
        }
        TokenContents::Name(name) if name == "and" => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LogicalAnd, span),
                None,
            )
        }
        TokenContents::Name(name) if name == "or" => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LogicalOr, span),
                None,
            )
        }
        TokenContents::Plus => {
            *index += 1;
            (ParsedExpression::Operator(BinaryOperator::Add, span), None)
        }
        TokenContents::Minus => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Subtract, span),
                None,
            )
        }
        TokenContents::Asterisk => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Multiply, span),
                None,
            )
        }
        TokenContents::ForwardSlash => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Divide, span),
                None,
            )
        }
        TokenContents::PercentSign => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Modulo, span),
                None,
            )
        }
        TokenContents::Equal => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Assign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::LeftShiftEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseLeftShiftAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::RightShiftEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseRightShiftAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::AmpersandEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseAndAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::PipeEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseOrAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::CaretEqual => {
            trace!("ERROR: assignment not allowed in this position");

            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseXorAssign, span),
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
                ParsedExpression::Operator(BinaryOperator::AddAssign, span),
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
                ParsedExpression::Operator(BinaryOperator::SubtractAssign, span),
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
                ParsedExpression::Operator(BinaryOperator::MultiplyAssign, span),
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
                ParsedExpression::Operator(BinaryOperator::DivideAssign, span),
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
                ParsedExpression::Operator(BinaryOperator::ModuloAssign, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::DoubleEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Equal, span),
                None,
            )
        }
        TokenContents::NotEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::NotEqual, span),
                None,
            )
        }
        TokenContents::LessThan => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LessThan, span),
                None,
            )
        }
        TokenContents::LessThanOrEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LessThanOrEqual, span),
                None,
            )
        }
        TokenContents::GreaterThan => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::GreaterThan, span),
                None,
            )
        }
        TokenContents::GreaterThanOrEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::GreaterThanOrEqual, span),
                None,
            )
        }
        TokenContents::Ampersand => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseAnd, span),
                None,
            )
        }
        TokenContents::Pipe => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseOr, span),
                None,
            )
        }
        TokenContents::Caret => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseXor, span),
                None,
            )
        }
        TokenContents::LeftShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseLeftShift, span),
                None,
            )
        }
        TokenContents::RightShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseRightShift, span),
                None,
            )
        }
        TokenContents::LeftArithmeticShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::ArithmeticLeftShift, span),
                None,
            )
        }
        TokenContents::RightArithmeticShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::ArithmeticRightShift, span),
                None,
            )
        }
        _ => {
            trace!("ERROR: unsupported operator (possibly just the end of an expression)");

            (
                ParsedExpression::Garbage(span),
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
) -> (ParsedExpression, Option<JaktError>) {
    trace!(format!(
        "parse_operator_with_assignment: {:?}",
        tokens[*index]
    ));

    let span = tokens[*index].span;

    match &tokens[*index].contents {
        TokenContents::QuestionMarkQuestionMark => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::NoneCoalescing, span),
                None,
            )
        }
        TokenContents::Plus => {
            *index += 1;
            (ParsedExpression::Operator(BinaryOperator::Add, span), None)
        }
        TokenContents::Minus => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Subtract, span),
                None,
            )
        }
        TokenContents::Asterisk => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Multiply, span),
                None,
            )
        }
        TokenContents::ForwardSlash => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Divide, span),
                None,
            )
        }
        TokenContents::PercentSign => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Modulo, span),
                None,
            )
        }
        TokenContents::Name(name) if name == "and" => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LogicalAnd, span),
                None,
            )
        }
        TokenContents::Name(name) if name == "or" => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LogicalOr, span),
                None,
            )
        }
        TokenContents::Ampersand => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseAnd, span),
                None,
            )
        }
        TokenContents::Pipe => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseOr, span),
                None,
            )
        }
        TokenContents::Caret => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseXor, span),
                None,
            )
        }
        TokenContents::LeftShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseLeftShift, span),
                None,
            )
        }
        TokenContents::RightShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseRightShift, span),
                None,
            )
        }
        TokenContents::LeftArithmeticShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::ArithmeticLeftShift, span),
                None,
            )
        }
        TokenContents::RightArithmeticShift => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::ArithmeticRightShift, span),
                None,
            )
        }
        TokenContents::Equal => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Assign, span),
                None,
            )
        }
        TokenContents::LeftShiftEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseLeftShiftAssign, span),
                None,
            )
        }
        TokenContents::RightShiftEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseRightShiftAssign, span),
                None,
            )
        }
        TokenContents::AmpersandEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseAndAssign, span),
                None,
            )
        }
        TokenContents::PipeEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseOrAssign, span),
                None,
            )
        }
        TokenContents::CaretEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::BitwiseXorAssign, span),
                None,
            )
        }
        TokenContents::PlusEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::AddAssign, span),
                None,
            )
        }
        TokenContents::MinusEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::SubtractAssign, span),
                None,
            )
        }
        TokenContents::AsteriskEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::MultiplyAssign, span),
                None,
            )
        }
        TokenContents::ForwardSlashEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::DivideAssign, span),
                None,
            )
        }
        TokenContents::DoubleEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::Equal, span),
                None,
            )
        }
        TokenContents::NotEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::NotEqual, span),
                None,
            )
        }
        TokenContents::LessThan => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LessThan, span),
                None,
            )
        }
        TokenContents::LessThanOrEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::LessThanOrEqual, span),
                None,
            )
        }
        TokenContents::GreaterThan => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::GreaterThan, span),
                None,
            )
        }
        TokenContents::GreaterThanOrEqual => {
            *index += 1;
            (
                ParsedExpression::Operator(BinaryOperator::GreaterThanOrEqual, span),
                None,
            )
        }
        _ => {
            trace!("ERROR: unsupported operator (possibly just the end of an expression)");

            (
                ParsedExpression::Garbage(span),
                Some(JaktError::ParserError(
                    "unsupported operator".to_string(),
                    tokens[*index].span,
                )),
            )
        }
    }
}

pub fn parse_set(tokens: &[Token], index: &mut usize) -> (ParsedExpression, Option<JaktError>) {
    let mut error = None;

    let mut output = Vec::new();

    let start;
    if *index < tokens.len() {
        start = *index;
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
        start = *index - 1;
        trace!("ERROR: incomplete set");

        error = error.or(Some(JaktError::ParserError(
            "incomplete set".to_string(),
            tokens[*index - 1].span,
        )));
    }

    while *index < tokens.len() {
        match &tokens[*index].contents {
            TokenContents::RCurly => {
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

    let end = *index - 1;

    (
        ParsedExpression::Set(
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

pub fn parse_array(tokens: &[Token], index: &mut usize) -> (ParsedExpression, Option<JaktError>) {
    let mut error = None;

    let mut output = Vec::new();
    let mut dict_output = Vec::new();

    let mut is_dictionary = false;

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

    let mut fill_size_expr = None;

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
            TokenContents::Semicolon => {
                if output.len() == 1 {
                    *index += 1;

                    let (expr, err) = parse_expression(
                        tokens,
                        index,
                        ExpressionKind::ExpressionWithoutAssignment,
                    );
                    error = error.or(err);
                    fill_size_expr = Some(Box::new(expr));
                } else {
                    error = error.or(Some(JaktError::ParserError(
                        "Can't fill an Array with more than one expression".to_string(),
                        tokens[*index].span,
                    )));
                }
            }
            _ => {
                let (expr, err) =
                    parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
                error = error.or(err);

                if *index < tokens.len() {
                    if tokens[*index].contents == TokenContents::Colon {
                        if !output.is_empty() {
                            error = error.or(Some(JaktError::ParserError(
                                "mixing dictionary and array values".to_string(),
                                tokens[*index].span,
                            )))
                        }

                        is_dictionary = true;

                        *index += 1;

                        if *index < tokens.len() {
                            let (value, err) = parse_expression(
                                tokens,
                                index,
                                ExpressionKind::ExpressionWithoutAssignment,
                            );
                            error = error.or(err);

                            dict_output.push((expr, value));
                        } else {
                            error = error.or(Some(JaktError::ParserError(
                                "key missing value in dictionary".to_string(),
                                tokens[*index - 1].span,
                            )))
                        }
                    } else if !is_dictionary {
                        output.push(expr);
                    }
                } else if !is_dictionary {
                    output.push(expr);
                }
            }
        }
    }

    let end = *index - 1;

    if is_dictionary {
        (
            ParsedExpression::Dictionary(
                dict_output,
                Span {
                    file_id: tokens[start].span.file_id,
                    start: tokens[start].span.start,
                    end: tokens[end].span.end,
                },
            ),
            error,
        )
    } else {
        (
            ParsedExpression::Array(
                output,
                fill_size_expr,
                Span {
                    file_id: tokens[start].span.file_id,
                    start: tokens[start].span.start,
                    end: tokens[end].span.end,
                },
            ),
            error,
        )
    }
}

pub fn parse_variable_declaration(
    tokens: &[Token],
    index: &mut usize,
) -> (ParsedVarDecl, Option<JaktError>) {
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
                            ParsedVarDecl {
                                name: name.to_string(),
                                ty: ParsedType::Empty,
                                mutable: false,
                                span: tokens[*index - 1].span,
                            },
                            None,
                        );
                    }
                }
            } else {
                return (
                    ParsedVarDecl {
                        name: name.to_string(),
                        ty: ParsedType::Empty,
                        mutable: false,
                        span: tokens[*index - 1].span,
                    },
                    None,
                );
            }

            if *index < tokens.len() {
                let decl_span = tokens[*index - 1].span;
                let mutable = *index + 1 < tokens.len()
                    && match &tokens[*index].contents {
                        TokenContents::Name(name) if name == "mutable" => {
                            *index += 1;
                            true
                        }
                        _ => false,
                    };

                let (var_type, err) = parse_typename(tokens, index);
                error = error.or(err);

                let result = ParsedVarDecl {
                    name: var_name,
                    ty: var_type,
                    mutable,
                    span: decl_span,
                };

                (result, error)
            } else {
                trace!("ERROR: expected type");

                (
                    ParsedVarDecl {
                        name: name.to_string(),
                        ty: ParsedType::Empty,
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
                ParsedVarDecl::new(tokens[*index].span),
                Some(JaktError::ParserError(
                    "expected name".to_string(),
                    tokens[*index].span,
                )),
            )
        }
    }
}

pub fn parse_shorthand_type(
    tokens: &[Token],
    index: &mut usize,
) -> (ParsedType, Option<JaktError>) {
    if *index + 2 >= tokens.len() {
        return (ParsedType::Empty, None);
    }
    let start = tokens[*index].span;
    if let TokenContents::LSquare = &tokens[*index].contents {
        // [T] is shorthand for Array<T>
        *index += 1;
        let (ty, err) = parse_typename(tokens, index);
        if let TokenContents::RSquare = &tokens[*index].contents {
            *index += 1;
            return (
                ParsedType::Array(
                    Box::new(ty),
                    Span {
                        file_id: start.file_id,
                        start: start.start,
                        end: tokens[*index - 1].span.end,
                    },
                ),
                err,
            );
        }

        (
            ParsedType::Empty,
            err.or(Some(JaktError::ParserError(
                "expected ]".to_string(),
                tokens[*index].span,
            ))),
        )
    } else if let TokenContents::LCurly = &tokens[*index].contents {
        // {T} is shorthand for Set<T>
        *index += 1;
        let (ty, err) = parse_typename(tokens, index);
        if let TokenContents::RCurly = &tokens[*index].contents {
            *index += 1;
            return (
                ParsedType::Set(
                    Box::new(ty),
                    Span {
                        file_id: start.file_id,
                        start: start.start,
                        end: tokens[*index - 1].span.end,
                    },
                ),
                err,
            );
        }

        // TODO: Add {K:V} shorthand for Dictionary<K,V>?

        (
            ParsedType::Empty,
            err.or(Some(JaktError::ParserError(
                "expected ]".to_string(),
                tokens[*index].span,
            ))),
        )
    } else {
        (ParsedType::Empty, None)
    }
}

pub fn parse_typename(tokens: &[Token], index: &mut usize) -> (ParsedType, Option<JaktError>) {
    let mut unchecked_type = ParsedType::Empty;
    let mut error = None;

    let start = tokens[*index].span;

    let mut typename = String::new();

    trace!(format!("parse_typename: {:?}", tokens[*index]));

    let (shorthand_type, err) = parse_shorthand_type(tokens, index);
    error = error.or(err);

    if shorthand_type != ParsedType::Empty {
        return (shorthand_type, error);
    }

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

                    unchecked_type = ParsedType::RawPtr(
                        Box::new(child_ty),
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: tokens[*index - 1].span.end,
                        },
                    );
                }
            } else {
                typename = name.clone();
                unchecked_type = ParsedType::Name(name.clone(), tokens[*index].span);
                *index += 1;
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

    if *index < tokens.len() {
        if let TokenContents::QuestionMark = tokens[*index].contents {
            // T? is shorthand for Optional<T>
            unchecked_type = ParsedType::Optional(
                Box::new(unchecked_type),
                Span {
                    file_id: start.file_id,
                    start: start.start,
                    end: tokens[*index].span.end,
                },
            );
            *index += 1;
        }

        if *index < tokens.len() {
            let previous_index = *index;
            if let TokenContents::LessThan = tokens[*index].contents {
                // Generic type
                *index += 1;
                let mut inner_types = vec![];

                while *index < tokens.len() {
                    match tokens[*index].contents {
                        TokenContents::GreaterThan => {
                            *index += 1;
                            break;
                        }
                        TokenContents::Comma => {
                            *index += 1;
                        }
                        TokenContents::Eol => {
                            *index += 1;
                        }
                        _ => {
                            let i = *index;
                            let (inner_ty, err) = parse_typename(tokens, index);
                            if i == *index {
                                // This is not a generic parameter, reset and leave.
                                error = error.or(err);
                                break;
                            }
                            error = error.or(err);
                            inner_types.push(inner_ty);
                        }
                    }
                }

                if *index >= tokens.len() {
                    unchecked_type = ParsedType::GenericType(
                        typename,
                        inner_types,
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: tokens[tokens.len() - 1].span.end,
                        },
                    )
                } else {
                    unchecked_type = ParsedType::GenericType(
                        typename,
                        inner_types,
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: tokens[*index].span.end,
                        },
                    )
                }

                if error.is_some() {
                    *index = previous_index;
                }
            }
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

pub fn parse_call(tokens: &[Token], index: &mut usize) -> (ParsedCall, Option<JaktError>) {
    trace!(format!("parse_call: {:?}", tokens[*index]));
    let mut call = ParsedCall::new();
    let mut error = None;

    match &tokens[*index] {
        Token {
            contents: TokenContents::Name(name),
            ..
        } => {
            call.name = name.to_string();

            *index += 1;

            // this is to allow the lookahead. Without it, we may see something like
            // foo < Bar, think the start of a generic call when it actually isn't
            let index_reset = *index;

            if *index < tokens.len() {
                if let TokenContents::LessThan = tokens[*index].contents {
                    // Generic type
                    *index += 1;

                    let mut inner_types = vec![];

                    while *index < tokens.len() {
                        match tokens[*index].contents {
                            TokenContents::GreaterThan => {
                                *index += 1;
                                break;
                            }
                            TokenContents::Comma => {
                                *index += 1;
                            }
                            TokenContents::Eol => {
                                *index += 1;
                            }
                            _ => {
                                let i = *index;
                                let (inner_ty, err) = parse_typename(tokens, index);
                                if i == *index {
                                    // Can't parse further, this is not a generic call.
                                    *index = index_reset;
                                    break;
                                }
                                error = error.or(err);
                                inner_types.push(inner_ty);
                            }
                        }
                    }

                    call.type_args = inner_types;
                }
            }

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
                        *index = index_reset;
                        return (
                            call,
                            Some(JaktError::ParserError("expected '('".to_string(), *span)),
                        );
                    }
                }
            } else {
                trace!("ERROR: incomplete function");
                *index = index_reset;

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
                    TokenContents::Eol => {
                        *index += 1;
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
