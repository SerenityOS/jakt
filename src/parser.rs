/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

use crate::error::JaktError;

use crate::compiler::Compiler;
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
    Tuple(Vec<ParsedType>, Span),
    Array(Box<ParsedType>, Span),
    Dictionary(Box<ParsedType>, Box<ParsedType>, Span),
    Set(Box<ParsedType>, Span),
    Optional(Box<ParsedType>, Span),
    RawPtr(Box<ParsedType>, Span),
    WeakPtr(Box<ParsedType>, Span),
    Empty,
}

#[derive(Debug, Clone)]
pub struct ParsedVarDecl {
    pub name: String,
    pub parsed_type: ParsedType,
    pub mutable: bool,
    pub span: Span,
    pub visibility: Visibility,
}

impl ParsedVarDecl {
    pub fn new(span: Span) -> Self {
        Self {
            name: String::new(),
            parsed_type: ParsedType::Empty,
            mutable: false,
            span,
            visibility: Visibility::Public,
        }
    }
}

impl PartialEq for ParsedVarDecl {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
            && self.parsed_type == other.parsed_type
            && self.mutable == other.mutable
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
    pub is_recursive: bool,
    pub definition_linkage: DefinitionLinkage,
    pub underlying_type: ParsedType,
    pub methods: Vec<ParsedFunction>,
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum FunctionLinkage {
    Internal,
    External,
    ImplicitConstructor,
    ImplicitEnumConstructor,
    ExternalClassConstructor,
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

#[derive(Debug, Clone)]
pub struct ParsedFunction {
    pub name: String,
    pub visibility: Visibility,
    pub name_span: Span,
    pub params: Vec<ParsedParameter>,
    pub generic_parameters: Vec<(String, Span)>,
    pub block: ParsedBlock,
    pub throws: bool,
    pub return_type: ParsedType,
    pub return_type_span: Option<Span>,
    pub linkage: FunctionLinkage,
    pub must_instantiate: bool,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Visibility {
    Public,
    Private,
    Restricted(Vec<ParsedType>, Span),
}

#[derive(Clone, Debug)]
pub struct ParsedParameter {
    pub requires_label: bool,
    pub variable: ParsedVariable,
}

#[derive(Clone, Debug)]
pub struct ParsedVariable {
    pub name: String,
    pub parsed_type: ParsedType,
    pub mutable: bool,
    pub span: Span,
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
            visibility: Visibility::Public,
            params: Vec::new(),
            generic_parameters: Vec::new(),
            block: ParsedBlock::new(),
            throws: false,
            return_type: ParsedType::Empty,
            return_type_span: None,
            linkage,
            must_instantiate: false,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum ParsedStatement {
    Expression(ParsedExpression),
    Defer(Box<ParsedStatement>, Span),
    UnsafeBlock(ParsedBlock),
    VarDecl(ParsedVarDecl, ParsedExpression),
    If(ParsedExpression, ParsedBlock, Option<Box<ParsedStatement>>),
    Block(ParsedBlock),
    Loop(ParsedBlock),
    While(ParsedExpression, ParsedBlock),
    For((String, Span), ParsedExpression, ParsedBlock),
    Break,
    Continue,
    Return(ParsedExpression, Span),
    Yield(ParsedExpression, Span),
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
        marker_span: Span,
    },
    CatchAll {
        body: MatchBody,
        marker_span: Span,
    },
    Expression {
        matched_expression: ParsedExpression,
        body: MatchBody,
        marker_span: Span,
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
    CharacterLiteral(String, Span),
    ByteLiteral(String, Span),
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
    NamespacedVar(String, Vec<String>, Span),
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
            ParsedExpression::ByteLiteral(_, span) => *span,
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
            ParsedExpression::NamespacedVar(_, _, span) => *span,
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
            (Self::NamespacedVar(l0, l1, _), Self::NamespacedVar(r0, r1, _)) => {
                l0 == r0 && l1 == r1
            }
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
}

impl TypeCast {
    pub fn unchecked_type(&self) -> ParsedType {
        match self {
            TypeCast::Fallible(parsed_type) => parsed_type.clone(),
            TypeCast::Infallible(parsed_type) => parsed_type.clone(),
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
    NoneCoalescingAssign,
}

impl ParsedExpression {
    // Relative weighting of precedence. Numbers are made up
    // with the only importance being how they relate to each
    // other
    pub fn precedence(&self) -> u64 {
        match self {
            ParsedExpression::Operator(operator, _) => match operator {
                BinaryOperator::Multiply | BinaryOperator::Modulo | BinaryOperator::Divide => 100,
                BinaryOperator::Add | BinaryOperator::Subtract => 90,
                BinaryOperator::BitwiseLeftShift
                | BinaryOperator::BitwiseRightShift
                | BinaryOperator::ArithmeticLeftShift
                | BinaryOperator::ArithmeticRightShift => 85,
                BinaryOperator::LessThan
                | BinaryOperator::LessThanOrEqual
                | BinaryOperator::GreaterThan
                | BinaryOperator::GreaterThanOrEqual
                | BinaryOperator::Equal
                | BinaryOperator::NotEqual => 80,
                BinaryOperator::BitwiseAnd => 73,
                BinaryOperator::BitwiseXor => 72,
                BinaryOperator::BitwiseOr => 71,
                BinaryOperator::LogicalAnd => 70,
                BinaryOperator::LogicalOr | BinaryOperator::NoneCoalescing => 69,
                BinaryOperator::Assign
                | BinaryOperator::BitwiseAndAssign
                | BinaryOperator::BitwiseOrAssign
                | BinaryOperator::BitwiseXorAssign
                | BinaryOperator::BitwiseLeftShiftAssign
                | BinaryOperator::BitwiseRightShiftAssign
                | BinaryOperator::AddAssign
                | BinaryOperator::SubtractAssign
                | BinaryOperator::MultiplyAssign
                | BinaryOperator::ModuloAssign
                | BinaryOperator::DivideAssign
                | BinaryOperator::NoneCoalescingAssign => 50,
            },
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

fn parse_import(
    tokens: &[Token],
    index: &mut usize,
    compiler: &mut Compiler,
) -> (ParsedNamespace, Option<JaktError>) {
    let mut error = None;
    *index += 1;

    if *index < tokens.len() {
        if let Token {
            contents: TokenContents::Name(module_name),
            span,
        } = &tokens[*index]
        {
            *index += 1;
            let (mut namespace, err) = compiler.find_and_include_module(module_name, *span);
            namespace.name = Some(module_name.clone());
            error = error.or(err);

            if *index < tokens.len() {
                match &tokens[*index] {
                    Token {
                        contents: TokenContents::Name(name),
                        ..
                    } if name == "as" => {
                        *index += 1;

                        if *index < tokens.len() {
                            if let Token {
                                contents: TokenContents::Name(alias),
                                ..
                            } = &tokens[*index]
                            {
                                *index += 1;
                                namespace.name = Some(alias.clone());
                                return (namespace, error);
                            }
                        }
                        error = error.or(Some(JaktError::ParserError(
                            "Expected an identifier after 'as'".to_string(),
                            *span,
                        )));
                    }
                    _ => {}
                }
            }

            return (namespace, error);
        } else {
            error = error.or(Some(JaktError::ParserError(
                "Expected module name after import keyword".to_string(),
                tokens[*index].span,
            )));
        }
    } else {
        error = error.or(Some(JaktError::ParserError(
            "expected name after import keyword".to_string(),
            tokens[*index - 1].span,
        )));
    }

    (ParsedNamespace::new(), error)
}

pub fn parse_namespace(
    tokens: &[Token],
    index: &mut usize,
    compiler: &mut Compiler,
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
                    let (fun, err) = parse_function(
                        tokens,
                        index,
                        FunctionLinkage::Internal,
                        Visibility::Public,
                    );
                    error = error.or(err);

                    parsed_namespace.functions.push(fun);
                }
                "boxed" => {
                    *index += 1;

                    if let Some(Token {
                        contents: TokenContents::Name(name),
                        ..
                    }) = tokens.get(*index)
                    {
                        if name == "enum" {
                            let (enum_, err) =
                                parse_enum(tokens, index, DefinitionLinkage::Internal, true);
                            error = error.or(err);

                            parsed_namespace.enums.push(enum_);
                            continue;
                        }
                    }

                    error = error.or(Some(JaktError::ParserError(
                        "expected enum keyword".to_string(),
                        tokens[*index].span,
                    )));
                }
                "enum" => {
                    let (enum_, err) =
                        parse_enum(tokens, index, DefinitionLinkage::Internal, false);
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
                        if let TokenContents::Name(namespace_name) = &tokens[*index].contents {
                            *index += 1;
                            name = Some(namespace_name.clone())
                        }

                        if let TokenContents::LCurly = &tokens[*index].contents {
                            *index += 1;

                            let (mut namespace, err) = parse_namespace(tokens, index, compiler);
                            error = error.or(err);

                            *index += 1;
                            if *index < tokens.len()
                                && tokens[*index].contents == TokenContents::RCurly
                            {
                                *index += 1;
                            }
                            namespace.name = name;
                            parsed_namespace.namespaces.push(namespace);
                        }
                    }
                }
                "import" => {
                    let (namespace, err) = parse_import(tokens, index, compiler);
                    error = error.or(err);
                    parsed_namespace.namespaces.push(namespace);
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
                                    let (mut fun, err) = parse_function(
                                        tokens,
                                        index,
                                        FunctionLinkage::External,
                                        Visibility::Public,
                                    );
                                    error = error.or(err);

                                    fun.must_instantiate = true;
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

                                    *index += 1;
                                    error = error.or(Some(JaktError::ParserError(
                                        "unexpected keyword".to_string(),
                                        *span,
                                    )));
                                }
                            },
                            _ => {
                                trace!("ERROR: unexpected token");

                                *index += 1;
                                error = error.or(Some(JaktError::ParserError(
                                    "unexpected token".to_string(),
                                    tokens[*index].span,
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
    while let Some(Token {
        contents: TokenContents::Eol,
        ..
    }) = tokens.get(*index)
    {
        *index += 1;
    }
}

pub fn parse_enum(
    tokens: &[Token],
    index: &mut usize,
    definition_linkage: DefinitionLinkage,
    is_recursive: bool,
) -> (ParsedEnum, Option<JaktError>) {
    trace!(format!("parse_enum({:?})", tokens[*index]));

    let mut error = None;
    let start_index = *index;
    let mut enum_ = ParsedEnum {
        name: "".to_string(),
        definition_linkage,
        generic_parameters: vec![],
        variants: Vec::new(),
        is_recursive,
        span: Span {
            file_id: tokens[start_index].span.file_id,
            start: tokens[start_index].span.start,
            end: tokens[*index].span.end,
        },
        underlying_type: ParsedType::Empty,
        methods: Vec::new(),
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
        // - Ident(name) LParen Type RParen
        // - Ident(name) LParen struct_body RParen
        // - Ident(name) Equal Expression
        //    expression should evaluate to the underlying type (not allowed if no underlying type)
        // - Ident(name)

        skip_newlines(tokens, index);
        let mut last_visibility_modifier = None;
        let mut last_visibility_modifier_span = None;
        while !matches!(
            tokens.get(*index),
            Some(Token {
                contents: TokenContents::RCurly,
                ..
            }) | None
        ) {
            skip_newlines(tokens, index);
            if let Some(Token {
                contents: TokenContents::Eol | TokenContents::Comma,
                ..
            }) = tokens.get(*index)
            {
                *index += 1;
                continue;
            }

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
                    format!(
                        "expected variant name or (public/private) 'function', not {:?}",
                        variant_name
                    ),
                    tokens[*index].span,
                )));
                break;
            }

            let name = match &variant_name.unwrap().contents {
                TokenContents::Name(name) => name,
                _ => unreachable!(),
            };

            match name.as_str() {
                "function" => {
                    // Lets parse a method
                    let function_linkage = match definition_linkage {
                        DefinitionLinkage::Internal => FunctionLinkage::Internal,
                        DefinitionLinkage::External => FunctionLinkage::External,
                    };

                    let visibility = last_visibility_modifier.unwrap_or(Visibility::Public);
                    last_visibility_modifier = None;

                    let (mut function, err) =
                        parse_function(tokens, index, function_linkage, visibility);
                    error = error.or(err);

                    if definition_linkage == DefinitionLinkage::External {
                        function.must_instantiate = true;
                    }

                    enum_.methods.push(function);
                    skip_newlines(tokens, index);
                    continue;
                }
                "public" => {
                    last_visibility_modifier = Some(Visibility::Public);
                    last_visibility_modifier_span = Some(tokens[*index].span);
                    *index += 1;
                    continue;
                }
                "private" => {
                    last_visibility_modifier = Some(Visibility::Private);
                    last_visibility_modifier_span = Some(tokens[*index].span);
                    *index += 1;
                    continue;
                }
                _ if last_visibility_modifier.is_some() => {
                    error = error.or(Some(JaktError::ParserErrorWithHint(
                        "Only enum methods may have visibility modifiers".to_string(),
                        tokens[*index].span,
                        "Remove this visibility modifier".to_string(),
                        last_visibility_modifier_span.unwrap(),
                    )));
                    // We came, we saw, we errored, now continue checking everything else as if nothing had happened.
                    last_visibility_modifier = None;
                }
                _ => {}
            }

            *index += 1;

            match tokens.get(*index) {
                Some(Token {
                    contents: TokenContents::LParen,
                    ..
                }) => {
                    trace!("variant with type");
                    *index += 1;

                    let mut members = Vec::new();
                    let mut parsed_type = None;

                    skip_newlines(tokens, index);
                    while !matches!(
                        tokens.get(*index),
                        Some(Token {
                            contents: TokenContents::RParen,
                            ..
                        }) | None
                    ) {
                        // If we have (Ident Colon), parse as a variable
                        // otherwise parse as a type.
                        let parse_as_type = members.is_empty() && parsed_type.is_none() && {
                            let lookahead_save = *index;
                            skip_newlines(tokens, index);
                            let result = !matches!(
                                (tokens.get(*index), tokens.get(*index + 1)),
                                (
                                    Some(Token {
                                        contents: TokenContents::Name(_),
                                        ..
                                    }),
                                    Some(Token {
                                        contents: TokenContents::Colon,
                                        ..
                                    }),
                                )
                            );
                            *index = lookahead_save;
                            result
                        };

                        if parse_as_type {
                            let (type_, parse_error) = parse_typename(tokens, index);
                            error = error.or(parse_error);
                            parsed_type = Some(type_);
                            skip_newlines(tokens, index);
                            if !matches!(
                                tokens.get(*index),
                                Some(Token {
                                    contents: TokenContents::RParen,
                                    ..
                                }) | None
                            ) {
                                error = error.or(Some(JaktError::ParserError(
                                    "expected `)` to end type in enum variant".to_string(),
                                    tokens[*index].span,
                                )));
                            }
                            break;
                        }

                        // Fields in struct-like enums are always public.
                        let (decl, parse_error) =
                            parse_variable_declaration(tokens, index, Visibility::Public);
                        error = error.or(parse_error);
                        if decl.name == enum_.name
                            && decl.parsed_type == ParsedType::Empty
                            && !is_recursive
                        {
                            error = error.or(Some(JaktError::ParserError(
                                "use 'boxed enum' to make the enum recursive".into(),
                                tokens[*index - 1].span,
                            )));
                        } else {
                            match &decl.parsed_type {
                                ParsedType::Name(decl_name, _)
                                    if decl_name == &enum_.name && !is_recursive =>
                                {
                                    error = error.or(Some(JaktError::ParserError(
                                        "use 'boxed enum' to make the enum recursive".into(),
                                        tokens[*index - 1].span,
                                    )));
                                }
                                _ => {}
                            }
                        }

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
                    if let Some(type_) = parsed_type {
                        // We have a simple value (non-struct) case
                        enum_.variants.push(EnumVariant::Typed(
                            name.to_string(),
                            type_,
                            Span {
                                file_id: tokens[*index].span.file_id,
                                start: tokens[start_index].span.start,
                                end: tokens[*index].span.end,
                            },
                        ));
                    } else {
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
                _ => {
                    enum_.variants.push(EnumVariant::Untyped(
                        name.to_string(),
                        Span {
                            file_id: tokens[*index].span.file_id,
                            start: tokens[*index].span.start,
                            end: tokens[*index].span.end,
                        },
                    ));
                    if let Some(Token {
                        contents: TokenContents::RCurly,
                        ..
                    }) = tokens.get(*index)
                    {
                        break;
                    }
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

        if tokens.len() == *index || matches!(tokens[*index].contents, TokenContents::Eof) {
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

                // This gets reset after each loop. If someone doesn't consume it, we error out.
                let mut last_visibility = None;

                while *index < tokens.len() {
                    match &tokens[*index].contents {
                        // avoid infinite loops
                        TokenContents::Eof => break,
                        TokenContents::RCurly => {
                            if last_visibility.is_some() {
                                error = error.or(Some(JaktError::ParserError(
                                    "Expected function or parameter after visibility modifier"
                                        .to_string(),
                                    tokens[*index].span,
                                )))
                            }
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

                            let visibility = last_visibility.unwrap_or(match definition_type {
                                DefinitionType::Class => Visibility::Private,
                                DefinitionType::Struct => Visibility::Public,
                            });
                            last_visibility = None;

                            let (mut function, err) =
                                parse_function(tokens, index, function_linkage, visibility);
                            error = error.or(err);

                            if definition_linkage == DefinitionLinkage::External {
                                function.must_instantiate = true;
                            }

                            methods.push(function);
                        }

                        TokenContents::Name(name) if name == "public" => {
                            last_visibility = Some(Visibility::Public);
                            *index += 1;
                            // By using continue, we skip the "visibility consumed"-check
                            continue;
                        }

                        TokenContents::Name(name) if name == "private" => {
                            last_visibility = Some(Visibility::Private);
                            *index += 1;
                            // By using continue, we skip the "visibility consumed"-check
                            continue;
                        }

                        TokenContents::Name(name) if name == "restricted" => {
                            let restricted_start = &tokens[*index].span;
                            *index += 1;

                            if tokens[*index].contents != TokenContents::LParen {
                                error = error.or(Some(JaktError::ParserError(
                                    "Expected ‘(’".to_string(),
                                    tokens[*index].span,
                                )));
                                break;
                            }
                            *index += 1;

                            let mut whitelisted_types: Vec<ParsedType> = vec![];
                            while !matches!(
                                tokens.get(*index),
                                Some(Token {
                                    contents: TokenContents::RParen,
                                    ..
                                }) | None
                            ) {
                                skip_newlines(tokens, index);
                                let (parsed_type, err) = parse_typename(tokens, index);
                                if err.is_some() {
                                    error = error.or(err);
                                    break;
                                } else {
                                    whitelisted_types.push(parsed_type);
                                }

                                skip_newlines(tokens, index);
                                if tokens.get(*index).is_some()
                                    && tokens[*index].contents == TokenContents::Comma
                                {
                                    *index += 1;
                                }

                                skip_newlines(tokens, index);
                            }

                            if whitelisted_types.is_empty() {
                                error = error.or(Some(JaktError::ParserError(
                                    "Type list cannot be empty".to_string(),
                                    tokens[*index].span,
                                )));
                                break;
                            }

                            if tokens[*index].contents != TokenContents::RParen {
                                error = error.or(Some(JaktError::ParserError(
                                    "Expected ‘)’".to_string(),
                                    tokens[*index].span,
                                )));
                                break;
                            }
                            *index += 1;

                            last_visibility = Some(Visibility::Restricted(
                                whitelisted_types,
                                Span::new(
                                    restricted_start.file_id,
                                    restricted_start.start,
                                    tokens[*index - 1].span.end,
                                ),
                            ));
                            // By using continue, we skip the "visibility consumed"-check
                            continue;
                        }

                        TokenContents::Name(..) => {
                            // Lets parse a parameter

                            let visibility = last_visibility.unwrap_or(match definition_type {
                                DefinitionType::Class => Visibility::Private,
                                DefinitionType::Struct => Visibility::Public,
                            });
                            last_visibility = None;

                            let (mut var_decl, err) =
                                parse_variable_declaration(tokens, index, visibility);
                            error = error.or(err);

                            // Ignore immutable flag for now
                            var_decl.mutable = false;

                            if var_decl.parsed_type == ParsedType::Empty {
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

                    if last_visibility.is_some() {
                        error = error.or(Some(JaktError::ParserError(
                            "Expected function or parameter after visibility modifier".to_string(),
                            tokens[*index].span,
                        )))
                    }
                }

                if *index == tokens.len() || matches!(tokens[*index].contents, TokenContents::Eof) {
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
    visibility: Visibility,
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
                                    parsed_type: ParsedType::Empty,
                                    mutable: current_param_is_mutable,
                                    span: tokens[*index - 1].span,
                                },
                            });
                        }

                        TokenContents::Name(..) => {
                            // Now lets parse a parameter

                            let (var_decl, err) =
                                parse_variable_declaration(tokens, index, Visibility::Public);
                            error = error.or(err);

                            if var_decl.parsed_type == ParsedType::Empty {
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
                                    parsed_type: var_decl.parsed_type,
                                    mutable: var_decl.mutable,
                                    span: tokens[*index - 1].span,
                                },
                            });
                        }
                        _ => {
                            trace!("ERROR: expected parameter");

                            error = error.or(Some(JaktError::ParserError(
                                "expected parameter".to_string(),
                                tokens[*index].span,
                            )));

                            break;
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

                //  accept return type specification with '->'
                let return_type_span = if tokens[*index].contents == TokenContents::Minus {
                    *index += 1;
                    if tokens[*index].contents != TokenContents::GreaterThan {
                        error = error.or(Some(JaktError::ParserError(
                            "expected ->".to_string(),
                            tokens[*index - 1].span,
                        )));
                    }
                    let start = *index;
                    let file_id = tokens[*index].span.file_id;
                    *index += 1;
                    let (ret_type, err) = parse_typename(tokens, index);
                    return_type = ret_type;
                    error = error.or(err);
                    Some(Span {
                        file_id,
                        start,
                        end: tokens[*index - 1].span.end,
                    })
                } else {
                    None
                };

                // Accept an (optional) fat arrow
                let fat_arrow_expr = if tokens[*index].contents == TokenContents::FatArrow {
                    *index += 1;
                    let (expr, err) = parse_expression(
                        tokens,
                        index,
                        ExpressionKind::ExpressionWithoutAssignment,
                    );
                    error = error.or(err);
                    Some(expr)
                } else {
                    None
                };

                if *index >= tokens.len() {
                    trace!("ERROR: incomplete function");
                    error = error.or(Some(JaktError::ParserError(
                        "incomplete function".to_string(),
                        tokens[tokens.len() - 1].span,
                    )));
                }

                if function_name == "main" {
                    throws = true
                }

                if let FunctionLinkage::External = linkage {
                    return (
                        ParsedFunction {
                            name: function_name.clone(),
                            name_span,
                            params,
                            visibility,
                            generic_parameters,
                            block: ParsedBlock::new(),
                            throws,
                            return_type,
                            return_type_span,
                            linkage,
                            must_instantiate: true,
                        },
                        error,
                    );
                }

                let (block, err) = match fat_arrow_expr {
                    Some(expr) => {
                        let mut block = ParsedBlock::new();
                        block.stmts.push(ParsedStatement::Return(expr, name_span));
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
                        visibility,
                        generic_parameters,
                        block,
                        throws,
                        return_type,
                        return_type_span,
                        linkage,
                        must_instantiate: false,
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

#[derive(Debug, PartialEq)]
pub enum InsideBlock {
    No,
    Yes,
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

    skip_newlines(tokens, index);

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
                let (stmt, err) = parse_statement(tokens, index, InsideBlock::Yes);
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
    inside_block: InsideBlock,
) -> (ParsedStatement, Option<JaktError>) {
    trace!(format!("parse_statement: {:?}", tokens[*index]));

    let mut error = None;
    let start = tokens[*index].span;

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

            let span = tokens[*index].span;
            *index += 1;

            let (statement, err) = parse_statement(tokens, index, InsideBlock::No);
            error = error.or(err);

            (ParsedStatement::Defer(Box::new(statement), span), error)
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

            let (stmt, err) = parse_statement(tokens, index, InsideBlock::No);
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

            if let Token {
                contents: TokenContents::Name(iterator_name),
                span,
            } = &tokens[*index]
            {
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
                            ParsedStatement::For((iterator_name.clone(), *span), range_expr, block),
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

            (
                ParsedStatement::Return(
                    expr,
                    Span {
                        file_id: start.file_id,
                        start: start.start,
                        end: tokens[(*index - 1)].span.end,
                    },
                ),
                error,
            )
        }
        TokenContents::Name(name) if name == "yield" => {
            trace!("parsing yield");

            *index += 1;

            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
            error = error.or(err);

            let span = Span {
                file_id: start.file_id,
                start: start.start,
                end: tokens[(*index - 1)].span.end,
            };

            if inside_block == InsideBlock::No {
                error = error.or(Some(JaktError::ParserError(
                    "yield can only be used inside a block".to_string(),
                    span,
                )));
            }

            (ParsedStatement::Yield(expr, span), error)
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

            let (mut var_decl, err) = parse_variable_declaration(tokens, index, Visibility::Public);
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

pub fn parse_literal(tokens: &[Token], index: &mut usize) -> Option<ParsedExpression> {
    match tokens.get(*index) {
        Some(Token {
            contents:
                TokenContents::Number(..)
                | TokenContents::SingleQuotedString(..)
                | TokenContents::SingleQuotedByteString(..)
                | TokenContents::QuotedString(..),
            ..
        }) => {
            let (expr, err) = parse_operand(tokens, index);
            if err.is_none() {
                Some(expr)
            } else {
                None
            }
        }
        Some(Token {
            contents: TokenContents::Name(name),
            ..
        }) if name == "true" => {
            *index += 1;
            Some(ParsedExpression::Boolean(true, tokens[*index].span))
        }
        Some(Token {
            contents: TokenContents::Name(name),
            ..
        }) if name == "false" => {
            *index += 1;
            Some(ParsedExpression::Boolean(false, tokens[*index].span))
        }
        _ => None,
    }
}

pub fn parse_pattern_case(
    tokens: &[Token],
    index: &mut usize,
) -> (Vec<MatchCase>, Option<JaktError>) {
    // case:
    // 'else' '=>' (expression | block)
    // QualifiedName('(' ((name ':')? expression),* ')')? ('|' pattern)* '=>' (expression | block)
    // '(' expression ')' ('|' pattern)* '=>' (expression | block)

    let mut error = None;
    let mut all_cases: Vec<Box<dyn FnOnce(MatchBody) -> MatchCase>> = vec![];
    let make_cases: Box<dyn FnOnce(MatchBody) -> Vec<MatchCase>> = loop {
        let make_single_case: Box<dyn FnOnce(MatchBody) -> MatchCase> = loop {
            if let Some(expr) = parse_literal(tokens, index) {
                let span = expr.span();
                break Box::new(move |x| MatchCase::Expression {
                    matched_expression: expr,
                    body: x,
                    marker_span: span,
                });
            }

            if matches!(
                tokens.get(*index),
                Some(Token{
                    contents: TokenContents::Name(name),
                    ..
                }) if name == "else"
            ) {
                *index += 1;
                let span = Span {
                    file_id: tokens[*index - 1].span.file_id,
                    start: tokens[*index - 1].span.start,
                    end: tokens[*index - 1].span.end,
                };
                break Box::new(move |x| MatchCase::CatchAll {
                    body: x,
                    marker_span: span,
                });
            }

            if matches!(
                tokens.get(*index),
                Some(Token {
                    contents: TokenContents::LParen,
                    ..
                })
            ) {
                let (expr, err) =
                    parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
                error = error.or(err);

                let span = expr.span();
                break Box::new(move |x| MatchCase::Expression {
                    matched_expression: expr,
                    body: x,
                    marker_span: span,
                });
            }

            let pattern_start_index = *index;
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
            let index = *index;
            let span = Span {
                file_id: tokens[pattern_start_index].span.file_id,
                start: tokens[pattern_start_index].span.start,
                end: tokens[index - 1].span.end,
            };
            break Box::new(move |x| MatchCase::EnumVariant {
                variant_name: pattern,
                variant_arguments: arguments,
                arguments_span: Span {
                    file_id: tokens[args_start].span.file_id,
                    start: tokens[args_start].span.start,
                    end: tokens[index - 1].span.end,
                },
                body: x,
                marker_span: span,
            });
        };
        all_cases.push(make_single_case);

        skip_newlines(tokens, index);
        if let Some(Token {
            contents: TokenContents::Pipe,
            ..
        }) = tokens.get(*index)
        {
            *index += 1;
            continue;
        }
        skip_newlines(tokens, index);

        break Box::new(move |x| {
            all_cases
                .into_iter()
                .map(|case| case(x.clone()))
                .collect::<Vec<_>>()
        });
    };

    skip_newlines(tokens, index);

    if let Some(Token {
        contents: TokenContents::FatArrow,
        ..
    }) = tokens.get(*index)
    {
        *index += 1;
    } else {
        error = Some(JaktError::ParserError(
            "expected '=>' after pattern case".to_string(),
            tokens[*index].span,
        ));
    }

    skip_newlines(tokens, index);

    if let Some(Token {
        contents: TokenContents::LCurly,
        ..
    }) = tokens.get(*index)
    {
        let (block, err) = parse_block(tokens, index);
        error = error.or(err);
        (make_cases(MatchBody::Block(block)), error)
    } else {
        let (expr, err) =
            parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
        error = error.or(err);
        (make_cases(MatchBody::Expression(expr)), error)
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
            contents: TokenContents::RCurly | TokenContents::Eof,
            ..
        })
    ) {
        let pattern_start_index = *index;
        let (patterns, err) = parse_pattern_case(tokens, index);
        error = error.or(err);
        cases.extend(patterns);

        if pattern_start_index == *index {
            // Parser didn't advance, bail.
            break;
        }

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

    skip_newlines(tokens, index);

    let mut expr = match &tokens[*index].contents {
        TokenContents::Dot => ParsedExpression::Var("this".to_string(), tokens[*index].span),
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

            let (expr, err) =
                parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
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

            skip_newlines(tokens, index);

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
                            TokenContents::Eol => {
                                *index += 1;
                            }
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
            match c.chars().next() {
                Some('\\') if c.len() == 2 => ParsedExpression::CharacterLiteral(c.clone(), span),
                _ if c.len() == 1 => ParsedExpression::CharacterLiteral(c.clone(), span),
                _ => ParsedExpression::Garbage(span),
            }
        }
        TokenContents::SingleQuotedByteString(c) => {
            *index += 1;
            match c.chars().next() {
                Some('\\') if c.len() == 2 => ParsedExpression::ByteLiteral(c.clone(), span),
                _ if c.len() == 1 => ParsedExpression::ByteLiteral(c.clone(), span),
                _ => ParsedExpression::Garbage(span),
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
                    _ => {
                        error = error.or(Some(JaktError::ParserError(
                            "Invalid cast syntax".to_string(),
                            span,
                        )));
                        TypeCast::Fallible(ParsedType::Empty)
                    }
                };

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
                                    let name = match &tokens[*index - 1].contents {
                                        TokenContents::Name(name) => name.clone(),
                                        _ => unreachable!(),
                                    };

                                    // Just a reference to a variable in a namespace
                                    expr = ParsedExpression::NamespacedVar(
                                        name,
                                        namespace,
                                        Span {
                                            file_id: span.file_id,
                                            start: span.start,
                                            end: tokens[*index].span.end,
                                        },
                                    );
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
                                constant.number_constant().unwrap().to_usize(),
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
        TokenContents::QuestionMarkQuestionMark
        | TokenContents::Plus
        | TokenContents::Minus
        | TokenContents::Asterisk
        | TokenContents::ForwardSlash
        | TokenContents::PercentSign => {
            let operator = match &tokens[*index].contents {
                TokenContents::QuestionMarkQuestionMark => BinaryOperator::NoneCoalescing,
                TokenContents::Plus => BinaryOperator::Add,
                TokenContents::Minus => BinaryOperator::Subtract,
                TokenContents::Asterisk => BinaryOperator::Multiply,
                TokenContents::ForwardSlash => BinaryOperator::Divide,
                TokenContents::PercentSign => BinaryOperator::Modulo,
                _ => panic!("Internal error: Couldn't match token contents"),
            };
            *index += 1;
            (ParsedExpression::Operator(operator, span), None)
        }
        TokenContents::Name(name) if name == "and" || name == "or" => {
            let operator = match &tokens[*index].contents {
                TokenContents::Name(name) if name == "and" => BinaryOperator::LogicalAnd,
                TokenContents::Name(name) if name == "or" => BinaryOperator::LogicalOr,
                _ => panic!("Internal error: Couldn't match token contents"),
            };
            *index += 1;
            (ParsedExpression::Operator(operator, span), None)
        }
        TokenContents::Equal
        | TokenContents::LeftShiftEqual
        | TokenContents::RightShiftEqual
        | TokenContents::AmpersandEqual
        | TokenContents::PipeEqual
        | TokenContents::CaretEqual
        | TokenContents::PlusEqual
        | TokenContents::MinusEqual
        | TokenContents::AsteriskEqual
        | TokenContents::ForwardSlashEqual
        | TokenContents::PercentSignEqual
        | TokenContents::QuestionMarkQuestionMarkEqual => {
            trace!("ERROR: assignment not allowed in this position");

            let operator = match &tokens[*index].contents {
                TokenContents::Equal => BinaryOperator::Assign,
                TokenContents::LeftShiftEqual => BinaryOperator::BitwiseLeftShiftAssign,
                TokenContents::RightShiftEqual => BinaryOperator::BitwiseRightShiftAssign,
                TokenContents::AmpersandEqual => BinaryOperator::BitwiseAndAssign,
                TokenContents::PipeEqual => BinaryOperator::BitwiseOrAssign,
                TokenContents::CaretEqual => BinaryOperator::BitwiseXorAssign,
                TokenContents::PlusEqual => BinaryOperator::AddAssign,
                TokenContents::MinusEqual => BinaryOperator::SubtractAssign,
                TokenContents::AsteriskEqual => BinaryOperator::MultiplyAssign,
                TokenContents::ForwardSlashEqual => BinaryOperator::DivideAssign,
                TokenContents::PercentSignEqual => BinaryOperator::ModuloAssign,
                TokenContents::QuestionMarkQuestionMarkEqual => {
                    BinaryOperator::NoneCoalescingAssign
                }
                _ => panic!("Internal error: Couldn't match token contents"),
            };
            if operator != BinaryOperator::NoneCoalescingAssign {
                *index += 1;
            } else {
                *index += 2;
            }
            (
                ParsedExpression::Operator(operator, span),
                Some(JaktError::ValidationError(
                    "assignment is not allowed in this position".to_string(),
                    span,
                )),
            )
        }
        TokenContents::DoubleEqual
        | TokenContents::NotEqual
        | TokenContents::LessThan
        | TokenContents::LessThanOrEqual
        | TokenContents::GreaterThan
        | TokenContents::GreaterThanOrEqual
        | TokenContents::Ampersand
        | TokenContents::Pipe
        | TokenContents::Caret
        | TokenContents::LeftShift
        | TokenContents::RightShift
        | TokenContents::LeftArithmeticShift
        | TokenContents::RightArithmeticShift => {
            let operator = match &tokens[*index].contents {
                TokenContents::DoubleEqual => BinaryOperator::Equal,
                TokenContents::NotEqual => BinaryOperator::NotEqual,
                TokenContents::LessThan => BinaryOperator::LessThan,
                TokenContents::LessThanOrEqual => BinaryOperator::LessThanOrEqual,
                TokenContents::GreaterThan => BinaryOperator::GreaterThan,
                TokenContents::GreaterThanOrEqual => BinaryOperator::GreaterThanOrEqual,
                TokenContents::Ampersand => BinaryOperator::BitwiseAnd,
                TokenContents::Pipe => BinaryOperator::BitwiseOr,
                TokenContents::Caret => BinaryOperator::BitwiseXor,
                TokenContents::LeftShift => BinaryOperator::BitwiseLeftShift,
                TokenContents::RightShift => BinaryOperator::BitwiseRightShift,
                TokenContents::LeftArithmeticShift => BinaryOperator::ArithmeticLeftShift,
                TokenContents::RightArithmeticShift => BinaryOperator::ArithmeticRightShift,
                _ => panic!("Internal error: Couldn't match token contents"),
            };
            *index += 1;
            (ParsedExpression::Operator(operator, span), None)
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
        TokenContents::QuestionMarkQuestionMark
        | TokenContents::Plus
        | TokenContents::Minus
        | TokenContents::Asterisk
        | TokenContents::ForwardSlash
        | TokenContents::PercentSign
        | TokenContents::Ampersand
        | TokenContents::Pipe
        | TokenContents::Caret
        | TokenContents::LeftShift
        | TokenContents::RightShift
        | TokenContents::LeftArithmeticShift
        | TokenContents::RightArithmeticShift
        | TokenContents::Equal
        | TokenContents::LeftShiftEqual
        | TokenContents::RightShiftEqual
        | TokenContents::AmpersandEqual
        | TokenContents::PipeEqual
        | TokenContents::CaretEqual
        | TokenContents::PlusEqual
        | TokenContents::MinusEqual
        | TokenContents::AsteriskEqual
        | TokenContents::ForwardSlashEqual
        | TokenContents::PercentSignEqual
        | TokenContents::QuestionMarkQuestionMarkEqual
        | TokenContents::DoubleEqual
        | TokenContents::NotEqual
        | TokenContents::LessThan
        | TokenContents::LessThanOrEqual
        | TokenContents::GreaterThan
        | TokenContents::GreaterThanOrEqual => {
            let operator = match &tokens[*index].contents {
                TokenContents::QuestionMarkQuestionMark => BinaryOperator::NoneCoalescing,
                TokenContents::Plus => BinaryOperator::Add,
                TokenContents::Minus => BinaryOperator::Subtract,
                TokenContents::Asterisk => BinaryOperator::Multiply,
                TokenContents::ForwardSlash => BinaryOperator::Divide,
                TokenContents::PercentSign => BinaryOperator::Modulo,
                TokenContents::Ampersand => BinaryOperator::BitwiseAnd,
                TokenContents::Pipe => BinaryOperator::BitwiseOr,
                TokenContents::Caret => BinaryOperator::BitwiseXor,
                TokenContents::LeftShift => BinaryOperator::BitwiseLeftShift,
                TokenContents::RightShift => BinaryOperator::BitwiseRightShift,
                TokenContents::LeftArithmeticShift => BinaryOperator::ArithmeticLeftShift,
                TokenContents::RightArithmeticShift => BinaryOperator::ArithmeticRightShift,
                TokenContents::Equal => BinaryOperator::Assign,
                TokenContents::LeftShiftEqual => BinaryOperator::BitwiseLeftShiftAssign,
                TokenContents::RightShiftEqual => BinaryOperator::BitwiseRightShiftAssign,
                TokenContents::AmpersandEqual => BinaryOperator::BitwiseAndAssign,
                TokenContents::PipeEqual => BinaryOperator::BitwiseOrAssign,
                TokenContents::CaretEqual => BinaryOperator::BitwiseXorAssign,
                TokenContents::PlusEqual => BinaryOperator::AddAssign,
                TokenContents::MinusEqual => BinaryOperator::SubtractAssign,
                TokenContents::AsteriskEqual => BinaryOperator::MultiplyAssign,
                TokenContents::ForwardSlashEqual => BinaryOperator::DivideAssign,
                TokenContents::PercentSignEqual => BinaryOperator::ModuloAssign,
                TokenContents::QuestionMarkQuestionMarkEqual => {
                    BinaryOperator::NoneCoalescingAssign
                }
                TokenContents::DoubleEqual => BinaryOperator::Equal,
                TokenContents::NotEqual => BinaryOperator::NotEqual,
                TokenContents::LessThan => BinaryOperator::LessThan,
                TokenContents::LessThanOrEqual => BinaryOperator::LessThanOrEqual,
                TokenContents::GreaterThan => BinaryOperator::GreaterThan,
                TokenContents::GreaterThanOrEqual => BinaryOperator::GreaterThanOrEqual,
                _ => panic!("Internal error: Couldn't match token contents"),
            };
            if operator != BinaryOperator::NoneCoalescingAssign {
                *index += 1;
            } else {
                *index += 2;
            }
            (ParsedExpression::Operator(operator, span), None)
        }
        TokenContents::Name(name) if name == "and" || name == "or" => {
            let operator = match &tokens[*index].contents {
                TokenContents::Name(name) if name == "and" => BinaryOperator::LogicalAnd,
                TokenContents::Name(name) if name == "or" => BinaryOperator::LogicalOr,
                _ => panic!("Internal error: Couldn't match token contents"),
            };
            *index += 1;
            (ParsedExpression::Operator(operator, span), None)
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
                let previous_index = *index;

                let (expr, err) =
                    parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);
                error = error.or(err);

                if *index == previous_index {
                    break;
                }

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
                    *index += 1;
                }
            }
            TokenContents::Colon => {
                *index += 1;
                if dict_output.is_empty() {
                    if *index < tokens.len() && tokens[*index].contents == TokenContents::RSquare {
                        *index += 1;
                        is_dictionary = true;
                        break;
                    } else {
                        error = error.or(Some(JaktError::ParserError(
                            "Expected ']'".to_string(),
                            tokens[*index].span,
                        )));
                    }
                } else {
                    error = error.or(Some(JaktError::ParserError(
                        "Missing key in dictionary literal".to_string(),
                        tokens[*index].span,
                    )));
                }
            }
            _ => {
                let (expr, err) =
                    parse_expression(tokens, index, ExpressionKind::ExpressionWithoutAssignment);

                if err.is_some() {
                    // bail out with no expression and an error
                    return (ParsedExpression::OptionalNone(tokens[*index].span), err);
                }

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
    visibility: Visibility,
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
                                parsed_type: ParsedType::Empty,
                                mutable: false,
                                span: tokens[*index - 1].span,
                                visibility,
                            },
                            None,
                        );
                    }
                }
            } else {
                return (
                    ParsedVarDecl {
                        name: name.to_string(),
                        parsed_type: ParsedType::Empty,
                        mutable: false,
                        span: tokens[*index - 1].span,
                        visibility,
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
                    parsed_type: var_type,
                    mutable,
                    span: decl_span,
                    visibility,
                };

                (result, error)
            } else {
                trace!("ERROR: expected type");

                (
                    ParsedVarDecl {
                        name: name.to_string(),
                        parsed_type: ParsedType::Empty,
                        mutable: false,
                        span: tokens[*index - 2].span,
                        visibility,
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
        // [K:V] is shorthand for Dictionary<K, V>
        *index += 1;
        let (parsed_type, err) = parse_typename(tokens, index);
        match &tokens[*index].contents {
            TokenContents::RSquare => {
                *index += 1;
                return (
                    ParsedType::Array(
                        Box::new(parsed_type),
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: tokens[*index - 1].span.end,
                        },
                    ),
                    err,
                );
            }
            TokenContents::Colon => {
                *index += 1;
                let (value_parsed_type, value_err) = parse_typename(tokens, index);
                if *index < tokens.len() {
                    if let TokenContents::RSquare = &tokens[*index].contents {
                        *index += 1;
                        return (
                            ParsedType::Dictionary(
                                Box::new(parsed_type),
                                Box::new(value_parsed_type),
                                Span {
                                    file_id: start.file_id,
                                    start: start.start,
                                    end: tokens[*index - 1].span.end,
                                },
                            ),
                            err.or(value_err),
                        );
                    }
                }
            }
            _ => {}
        };

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
        let (parsed_type, err) = parse_typename(tokens, index);
        if let TokenContents::RCurly = &tokens[*index].contents {
            *index += 1;
            return (
                ParsedType::Set(
                    Box::new(parsed_type),
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
    } else if let TokenContents::LParen = &tokens[*index].contents {
        // (A, B, C) is shorthand for Tuple<A, B, C>
        *index += 1;
        let mut parsed_types = Vec::new();
        let mut error = None;

        while *index < tokens.len() {
            if let TokenContents::RParen = &tokens[*index].contents {
                *index += 1;

                return (
                    ParsedType::Tuple(
                        parsed_types,
                        Span {
                            file_id: start.file_id,
                            start: start.start,
                            end: tokens[*index - 1].span.end,
                        },
                    ),
                    error,
                );
            }
            if let TokenContents::Comma = &tokens[*index].contents {
                *index += 1;
            }
            let (parsed_type, err) = parse_typename(tokens, index);
            parsed_types.push(parsed_type);
            if err.is_some() {
                error = error.or(err);
                break;
            }
        }

        (
            ParsedType::Empty,
            error.or(Some(JaktError::ParserError(
                "expected )".to_string(),
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
        unchecked_type = shorthand_type
    } else {
        match &tokens[*index] {
            Token {
                contents: TokenContents::Name(name),
                ..
            } => {
                if name == "raw" || name == "weak" {
                    *index += 1;
                    if *index < tokens.len() {
                        let typename_start = tokens[*index].span;
                        let (child_parsed_type, err) = parse_typename(tokens, index);
                        error = error.or(err);

                        if name == "raw" {
                            unchecked_type = ParsedType::RawPtr(
                                Box::new(child_parsed_type),
                                Span {
                                    file_id: start.file_id,
                                    start: start.start,
                                    end: tokens[*index - 1].span.end,
                                },
                            );
                        } else if name == "weak" {
                            match child_parsed_type {
                                ParsedType::Optional(optional_type, ..) => {
                                    unchecked_type = ParsedType::WeakPtr(
                                        optional_type,
                                        Span {
                                            file_id: start.file_id,
                                            start: start.start,
                                            end: tokens[*index - 1].span.end,
                                        },
                                    );
                                }
                                _ => {
                                    trace!("ERROR: missing `?` after weak pointer type name");

                                    error = error.or(Some(JaktError::ParserError(
                                        "missing `?` after weak pointer type name".to_string(),
                                        Span {
                                            file_id: typename_start.file_id,
                                            start: typename_start.start,
                                            end: tokens[*index - 1].span.end,
                                        },
                                    )));
                                }
                            }
                        }
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
    }

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
                            let (inner_type, err) = parse_typename(tokens, index);
                            if i == *index {
                                // This is not a generic parameter, reset and leave.
                                error = error.or(err);
                                break;
                            }
                            error = error.or(err);
                            inner_types.push(inner_type);
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
                                let (inner_type, err) = parse_typename(tokens, index);
                                if i == *index {
                                    // Can't parse further, this is not a generic call.
                                    *index = index_reset;
                                    break;
                                }
                                error = error.or(err);
                                inner_types.push(inner_type);
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

                        if let Some(jakt_error) = err {
                            trace!(
                                "ERROR: error while parsing expression in function call parameter"
                            );
                            error = error.or(Some(jakt_error));
                            break;
                        } else {
                            error = error.or(err);
                        }

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
