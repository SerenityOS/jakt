use std::collections::{HashMap, HashSet};

use crate::parser::{MatchBody, MatchCase};
use crate::{
    codegen::{self},
    compiler::{
        BOOL_TYPE_ID, CCHAR_TYPE_ID, CINT_TYPE_ID, F32_TYPE_ID, F64_TYPE_ID, I16_TYPE_ID,
        I32_TYPE_ID, I64_TYPE_ID, I8_TYPE_ID, STRING_TYPE_ID, U16_TYPE_ID, U32_TYPE_ID,
        U64_TYPE_ID, U8_TYPE_ID, UNKNOWN_TYPE_ID, USIZE_TYPE_ID, VOID_TYPE_ID,
    },
    error::JaktError,
    lexer::Span,
    parser::{
        BinaryOperator, DefinitionLinkage, DefinitionType, EnumVariant, FunctionLinkage,
        ParsedBlock, ParsedCall, ParsedEnum, ParsedExpression, ParsedFunction, ParsedNamespace,
        ParsedStatement, ParsedStruct, ParsedType, TypeCast, UnaryOperator,
    },
};
use std::os::raw::{c_char, c_int};

pub type StructId = usize;
pub type EnumId = usize;
pub type FunctionId = usize;
pub type ScopeId = usize;
pub type TypeId = usize;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum SafetyMode {
    Safe,
    Unsafe,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Type {
    Builtin,
    TypeVariable(String),
    // A GenericInstance is a generic that has known values for its type param
    // For example Foo<Bar> is an instance of the generic Foo<T>
    GenericInstance(StructId, Vec<TypeId>),
    GenericEnumInstance(EnumId, Vec<TypeId>),
    Struct(StructId),
    Enum(EnumId),
    RawPtr(TypeId),
}

pub fn is_integer(type_id: TypeId) -> bool {
    matches!(
        type_id,
        CCHAR_TYPE_ID
            | CINT_TYPE_ID
            | USIZE_TYPE_ID
            | I8_TYPE_ID
            | I16_TYPE_ID
            | I32_TYPE_ID
            | I64_TYPE_ID
            | U8_TYPE_ID
            | U16_TYPE_ID
            | U32_TYPE_ID
            | U64_TYPE_ID
    )
}

pub fn is_signed(type_id: TypeId) -> bool {
    match type_id {
        // c_char types can be both signed or unsigned values thus we have to check which variant
        // we have here. c_int on the other hand will always be signed.
        CCHAR_TYPE_ID => c_char::MIN < 0,
        USIZE_TYPE_ID | U8_TYPE_ID | U16_TYPE_ID | U32_TYPE_ID | U64_TYPE_ID => false,
        _ => true,
    }
}

pub fn get_bits(type_id: TypeId) -> u32 {
    match type_id {
        BOOL_TYPE_ID => 8,
        I8_TYPE_ID => i8::BITS,
        I16_TYPE_ID => i16::BITS,
        I32_TYPE_ID => i32::BITS,
        I64_TYPE_ID => i64::BITS,
        U8_TYPE_ID => u8::BITS,
        U16_TYPE_ID => u16::BITS,
        U32_TYPE_ID => u32::BITS,
        U64_TYPE_ID => u64::BITS,
        F32_TYPE_ID => 32,
        F64_TYPE_ID => 64,
        CCHAR_TYPE_ID => c_char::BITS,
        CINT_TYPE_ID => c_int::BITS,
        USIZE_TYPE_ID => usize::BITS,
        _ => panic!("get_bits not supported for type {}", type_id),
    }
}

pub fn can_fit_integer(type_id: TypeId, value: &IntegerConstant) -> bool {
    match *value {
        IntegerConstant::Signed(value) => match type_id {
            CCHAR_TYPE_ID => value >= c_char::MIN as i64 && value <= c_char::MAX as i64,
            CINT_TYPE_ID => value >= c_int::MIN as i64 && value <= c_int::MAX as i64,
            I8_TYPE_ID => value >= i8::MIN as i64 && value <= i8::MAX as i64,
            I16_TYPE_ID => value >= i16::MIN as i64 && value <= i16::MAX as i64,
            I32_TYPE_ID => value >= i32::MIN as i64 && value <= i32::MAX as i64,
            I64_TYPE_ID => true,
            U8_TYPE_ID => value >= 0 && value <= u8::MAX as i64,
            U16_TYPE_ID => value >= 0 && value <= u16::MAX as i64,
            U32_TYPE_ID => value >= 0 && value <= u32::MAX as i64,
            U64_TYPE_ID => value >= 0,
            // FIXME: Don't assume that usize is 64-bit
            USIZE_TYPE_ID => value >= 0,
            _ => false,
        },
        IntegerConstant::Unsigned(value) => match type_id {
            I8_TYPE_ID => value <= i8::MAX as u64,
            I16_TYPE_ID => value <= i16::MAX as u64,
            I32_TYPE_ID => value <= i32::MAX as u64,
            I64_TYPE_ID => value <= i64::MAX as u64,
            U8_TYPE_ID => value <= u8::MAX as u64,
            U16_TYPE_ID => value <= u16::MAX as u64,
            U32_TYPE_ID => value <= u32::MAX as u64,
            // FIXME: Don't assume that usize is 64-bit
            USIZE_TYPE_ID => true,
            U64_TYPE_ID => true,
            _ => false,
        },
    }
}

#[derive(Debug, Clone)]
pub struct Project {
    pub functions: Vec<CheckedFunction>,
    pub structs: Vec<CheckedStruct>,
    pub enums: Vec<CheckedEnum>,
    pub scopes: Vec<Scope>,
    pub types: Vec<Type>,

    pub current_function_index: Option<usize>,
}

impl Project {
    pub fn new() -> Self {
        // Top-level (project-global) scope has no parent scope
        // and is the parent scope of all file scopes
        let project_global_scope = Scope::new(None);

        Self {
            functions: Vec::new(),
            structs: Vec::new(),
            enums: Vec::new(),
            scopes: vec![project_global_scope],
            types: Vec::new(),
            current_function_index: None,
        }
    }

    pub fn find_or_add_type_id(&mut self, ty: Type) -> TypeId {
        for (idx, t) in self.types.iter().enumerate() {
            if t == &ty {
                return idx;
            }
        }

        // in the future, we may want to group related types (like instantiations of the same generic)
        self.types.push(ty);

        self.types.len() - 1
    }

    pub fn create_scope(&mut self, parent_id: ScopeId) -> ScopeId {
        self.scopes.push(Scope::new(Some(parent_id)));

        self.scopes.len() - 1
    }

    pub fn add_var_to_scope(
        &mut self,
        scope_id: ScopeId,
        var: CheckedVariable,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = &mut self.scopes[scope_id];
        for existing_var in &scope.vars {
            if var.name == existing_var.name {
                return Err(JaktError::TypecheckError(
                    format!("redefinition of variable {}", var.name),
                    span,
                ));
            }
        }
        scope.vars.push(var);

        Ok(())
    }

    pub fn find_var_in_scope(&self, scope_id: ScopeId, var: &str) -> Option<CheckedVariable> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for v in &scope.vars {
                if v.name == var {
                    return Some(v.clone());
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn add_struct_to_scope(
        &mut self,
        scope_id: ScopeId,
        name: String,
        struct_id: StructId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = &mut self.scopes[scope_id];
        for (existing_struct, _) in &scope.structs {
            if &name == existing_struct {
                return Err(JaktError::TypecheckError(
                    format!("redefinition of struct/class {}", name),
                    span,
                ));
            }
        }
        scope.structs.push((name, struct_id));

        Ok(())
    }

    pub fn add_enum_to_scope(
        &mut self,
        scope_id: ScopeId,
        name: String,
        enum_id: EnumId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = &mut self.scopes[scope_id];
        for (existing_enum, _) in &scope.enums {
            if &name == existing_enum {
                return Err(JaktError::TypecheckError(
                    format!("redefinition of enum {}", name),
                    span,
                ));
            }
        }
        scope.enums.push((name, enum_id));

        Ok(())
    }

    pub fn find_struct_in_scope(&self, scope_id: ScopeId, structure: &str) -> Option<StructId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for s in &scope.structs {
                if s.0 == structure {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn find_enum_in_scope(&self, scope_id: ScopeId, enum_name: &str) -> Option<EnumId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for e in &scope.enums {
                if e.0 == enum_name {
                    return Some(e.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    // Find the namespace in the current scope, or one of its parents
    pub fn find_namespace_in_scope(
        &self,
        scope_id: ScopeId,
        namespace_name: &str,
    ) -> Option<StructId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for child_scope_id in &scope.children {
                let child_scope = &self.scopes[*child_scope_id];
                if let Some(name) = &child_scope.namespace_name {
                    if name == namespace_name {
                        return Some(*child_scope_id);
                    }
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    // Find namespace in the current scope, but not any of its parents (strictly in the current scope)
    pub fn find_namespace_in_scope_strict(
        &self,
        scope_id: ScopeId,
        namespace_name: &str,
    ) -> Option<StructId> {
        let scope = &self.scopes[scope_id];
        for child_scope_id in &scope.children {
            let child_scope = &self.scopes[*child_scope_id];
            if let Some(name) = &child_scope.namespace_name {
                if name == namespace_name {
                    return Some(*child_scope_id);
                }
            }
        }

        None
    }

    pub fn add_function_to_scope(
        &mut self,
        scope_id: ScopeId,
        name: String,
        function_id: FunctionId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = &mut self.scopes[scope_id];

        for (existing_function, _) in &scope.functions {
            if &name == existing_function {
                return Err(JaktError::TypecheckError(
                    format!("redefinition of function {}", name),
                    span,
                ));
            }
        }
        scope.functions.push((name, function_id));

        Ok(())
    }

    pub fn find_function_in_scope(
        &self,
        scope_id: ScopeId,
        function_name: &str,
    ) -> Option<FunctionId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for s in &scope.functions {
                if s.0 == function_name {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn add_type_to_scope(
        &mut self,
        scope_id: ScopeId,
        type_name: String,
        type_id: TypeId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = &mut self.scopes[scope_id];

        for (existing_type, _) in &scope.types {
            if &type_name == existing_type {
                return Err(JaktError::TypecheckError(
                    format!("redefinition of type {}", type_name),
                    span,
                ));
            }
        }
        scope.types.push((type_name, type_id));

        Ok(())
    }

    pub fn find_type_in_scope(&self, scope_id: ScopeId, type_name: &str) -> Option<TypeId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for s in &scope.types {
                if s.0 == type_name {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }
}

#[derive(Clone, Debug)]
pub struct CheckedStruct {
    pub name: String,
    pub generic_parameters: Vec<TypeId>,
    pub fields: Vec<CheckedVarDecl>,
    pub scope_id: ScopeId,
    pub definition_linkage: DefinitionLinkage,
    pub definition_type: DefinitionType,
}

#[derive(Clone, Debug)]
pub struct CheckedEnum {
    pub name: String,
    pub generic_parameters: Vec<TypeId>,
    pub variants: Vec<CheckedEnumVariant>,
    pub scope_id: ScopeId,
    pub definition_linkage: DefinitionLinkage,
    pub underlying_type: Option<TypeId>,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub enum CheckedEnumVariant {
    Untyped(String, Span),
    Typed(String, TypeId, Span),
    WithValue(String, CheckedExpression, Span),
    StructLike(String, Vec<CheckedVarDecl>, Span),
}

#[derive(Clone, Debug)]
pub struct CheckedNamespace {
    pub name: Option<String>,
    pub scope: ScopeId,
}

#[derive(Clone, Debug)]
pub struct CheckedParameter {
    pub requires_label: bool,
    pub variable: CheckedVariable,
}

#[derive(Clone, Debug)]
pub enum FunctionGenericParameter {
    InferenceGuide(TypeId),
    Parameter(TypeId),
}

#[derive(Debug, Clone)]
pub struct CheckedFunction {
    pub name: String,
    pub throws: bool,
    pub return_type: TypeId,
    pub params: Vec<CheckedParameter>,
    pub generic_parameters: Vec<FunctionGenericParameter>,
    pub function_scope_id: ScopeId,
    pub block: CheckedBlock,
    pub linkage: FunctionLinkage,
}

impl CheckedFunction {
    pub fn is_static(&self) -> bool {
        for param in &self.params {
            if param.variable.name == "this" {
                return false;
            }
        }

        true
    }
}

#[derive(Debug, Clone)]
pub struct CheckedBlock {
    pub stmts: Vec<CheckedStatement>,
    pub definitely_returns: bool,
}

impl CheckedBlock {
    pub fn new() -> Self {
        Self {
            stmts: Vec::new(),
            definitely_returns: false,
        }
    }
}

#[derive(Debug, Clone)]
pub struct CheckedVarDecl {
    pub name: String,
    pub ty: TypeId,
    pub mutable: bool,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub struct CheckedVariable {
    pub name: String,
    pub ty: TypeId,
    pub mutable: bool,
}

#[derive(Debug, Clone)]
pub enum CheckedStatement {
    Expression(CheckedExpression),
    Defer(Box<CheckedStatement>),
    VarDecl(CheckedVarDecl, CheckedExpression),
    If(
        CheckedExpression,
        CheckedBlock,
        Option<Box<CheckedStatement>>, // optional else case
    ),
    Block(CheckedBlock),
    Loop(CheckedBlock),
    While(CheckedExpression, CheckedBlock),
    Return(CheckedExpression),
    For(String, CheckedExpression, CheckedBlock),
    Break,
    Continue,
    Throw(CheckedExpression),
    Try(Box<CheckedStatement>, String, CheckedBlock),
    InlineCpp(Vec<String>),
    Garbage,
}

#[derive(Clone, Debug)]
pub enum IntegerConstant {
    Signed(i64),
    Unsigned(u64),
}

impl IntegerConstant {
    pub fn to_usize(&self) -> usize {
        match self {
            IntegerConstant::Signed(value) => *value as usize,
            IntegerConstant::Unsigned(value) => *value as usize,
        }
    }

    pub fn promote(&self, type_id: TypeId) -> (Option<NumericConstant>, TypeId) {
        if !can_fit_integer(type_id, self) {
            return (None, UNKNOWN_TYPE_ID);
        }

        let bits = get_bits(type_id);
        let signed = is_signed(type_id);

        let new_constant = match self {
            IntegerConstant::Signed(value) => match (bits, signed) {
                (8, false) => NumericConstant::U8(*value as u8),
                (16, false) => NumericConstant::U16(*value as u16),
                (32, false) => NumericConstant::U32(*value as u32),
                (64, false) => NumericConstant::U64(*value as u64),
                (8, true) => NumericConstant::I8(*value as i8),
                (16, true) => NumericConstant::I16(*value as i16),
                (32, true) => NumericConstant::I32(*value as i32),
                (64, true) => NumericConstant::I64(*value as i64),
                _ => panic!("Numeric constants can only be 8, 16, 32, or 64 bits long"),
            },
            IntegerConstant::Unsigned(value) => match (bits, signed) {
                (8, false) => NumericConstant::U8(*value as u8),
                (16, false) => NumericConstant::U16(*value as u16),
                (32, false) => NumericConstant::U32(*value as u32),
                (64, false) => NumericConstant::U64(*value as u64),
                (8, true) => NumericConstant::I8(*value as i8),
                (16, true) => NumericConstant::I16(*value as i16),
                (32, true) => NumericConstant::I32(*value as i32),
                (64, true) => NumericConstant::I64(*value as i64),
                _ => panic!("Numeric constants can only be 8, 16, 32, or 64 bits long"),
            },
        };
        (Some(new_constant), type_id)
    }
}

#[derive(Clone, Debug)]
pub enum NumericConstant {
    I8(i8),
    I16(i16),
    I32(i32),
    I64(i64),
    U8(u8),
    U16(u16),
    U32(u32),
    U64(u64),
    USize(u64),
}

impl PartialEq for NumericConstant {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (NumericConstant::I8(l), NumericConstant::I8(r)) => l == r,
            (NumericConstant::I16(l), NumericConstant::I16(r)) => l == r,
            (NumericConstant::I32(l), NumericConstant::I32(r)) => l == r,
            (NumericConstant::I64(l), NumericConstant::I64(r)) => l == r,
            (NumericConstant::U8(l), NumericConstant::U8(r)) => l == r,
            (NumericConstant::U16(l), NumericConstant::U16(r)) => l == r,
            (NumericConstant::U32(l), NumericConstant::U32(r)) => l == r,
            (NumericConstant::U64(l), NumericConstant::U64(r)) => l == r,
            (NumericConstant::USize(l), NumericConstant::USize(r)) => l == r,
            _ => false,
        }
    }
}

impl NumericConstant {
    pub fn integer_constant(&self) -> Option<IntegerConstant> {
        match self {
            NumericConstant::I8(value) => Some(IntegerConstant::Signed(*value as i64)),
            NumericConstant::I16(value) => Some(IntegerConstant::Signed(*value as i64)),
            NumericConstant::I32(value) => Some(IntegerConstant::Signed(*value as i64)),
            NumericConstant::I64(value) => Some(IntegerConstant::Signed(*value as i64)),
            NumericConstant::U8(value) => Some(IntegerConstant::Unsigned(*value as u64)),
            NumericConstant::U16(value) => Some(IntegerConstant::Unsigned(*value as u64)),
            NumericConstant::U32(value) => Some(IntegerConstant::Unsigned(*value as u64)),
            NumericConstant::U64(value) => Some(IntegerConstant::Unsigned(*value as u64)),
            NumericConstant::USize(value) => Some(IntegerConstant::Unsigned(*value as u64)),
        }
    }

    pub fn ty(&self) -> TypeId {
        match self {
            NumericConstant::I8(_) => I8_TYPE_ID,
            NumericConstant::I16(_) => I16_TYPE_ID,
            NumericConstant::I32(_) => I32_TYPE_ID,
            NumericConstant::I64(_) => I64_TYPE_ID,
            NumericConstant::U8(_) => U8_TYPE_ID,
            NumericConstant::U16(_) => U16_TYPE_ID,
            NumericConstant::U32(_) => U32_TYPE_ID,
            NumericConstant::U64(_) => U64_TYPE_ID,
            NumericConstant::USize(_) => USIZE_TYPE_ID,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum CheckedTypeCast {
    Fallible(TypeId),
    Infallible(TypeId),
    Saturating(TypeId),
    Truncating(TypeId),
}

impl CheckedTypeCast {
    pub fn ty(&self) -> TypeId {
        match self {
            CheckedTypeCast::Fallible(ty) => *ty,
            CheckedTypeCast::Infallible(ty) => *ty,
            CheckedTypeCast::Saturating(ty) => *ty,
            CheckedTypeCast::Truncating(ty) => *ty,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum CheckedUnaryOperator {
    PreIncrement,
    PostIncrement,
    PreDecrement,
    PostDecrement,
    Negate,
    Dereference,
    RawAddress,
    LogicalNot,
    BitwiseNot,
    TypeCast(CheckedTypeCast),
    Is(TypeId),
}

#[derive(Debug, Clone)]
pub enum CheckedMatchBody {
    Expression(CheckedExpression),
    Block(CheckedBlock),
}

#[derive(Debug, Clone)]
pub enum CheckedMatchCase {
    EnumVariant {
        variant_name: String,
        variant_arguments: Vec<(Option<String>, String)>,
        subject_type_id: TypeId,
        variant_index: usize,
        scope_id: ScopeId,
        body: CheckedMatchBody,
    },
}

#[derive(Clone, Debug)]
pub enum CheckedExpression {
    // Standalone
    Boolean(bool, Span),
    NumericConstant(NumericConstant, Span, TypeId),
    QuotedString(String, Span),
    CharacterConstant(char, Span),
    UnaryOp(Box<CheckedExpression>, CheckedUnaryOperator, Span, TypeId),
    BinaryOp(
        Box<CheckedExpression>,
        BinaryOperator,
        Box<CheckedExpression>,
        Span,
        TypeId,
    ),
    Tuple(Vec<CheckedExpression>, Span, TypeId),
    Range(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    Array(
        Vec<CheckedExpression>,
        Option<Box<CheckedExpression>>,
        Span,
        TypeId,
    ),
    Dictionary(Vec<(CheckedExpression, CheckedExpression)>, Span, TypeId),
    Set(Vec<CheckedExpression>, Span, TypeId),
    IndexedExpression(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    IndexedDictionary(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    IndexedTuple(Box<CheckedExpression>, usize, Span, TypeId),
    IndexedStruct(Box<CheckedExpression>, String, Span, TypeId),

    Match(Box<CheckedExpression>, Vec<CheckedMatchCase>, Span, TypeId),

    Call(CheckedCall, Span, TypeId),
    MethodCall(Box<CheckedExpression>, CheckedCall, Span, TypeId),

    Var(CheckedVariable, Span),

    OptionalNone(Span, TypeId),
    OptionalSome(Box<CheckedExpression>, Span, TypeId),
    ForcedUnwrap(Box<CheckedExpression>, Span, TypeId),

    // Parsing error
    Garbage(Span),
}

impl CheckedExpression {
    pub fn ty(&self) -> TypeId {
        match self {
            CheckedExpression::Boolean(_, _) => BOOL_TYPE_ID,
            CheckedExpression::Call(_, _, ty) => *ty,
            CheckedExpression::NumericConstant(_, _, ty) => *ty,
            CheckedExpression::QuotedString(_, _) => STRING_TYPE_ID,
            CheckedExpression::CharacterConstant(_, _) => CCHAR_TYPE_ID, // use the C one for now
            CheckedExpression::UnaryOp(_, _, _, ty) => *ty,
            CheckedExpression::BinaryOp(_, _, _, _, ty) => *ty,
            CheckedExpression::Dictionary(_, _, ty) => *ty,
            CheckedExpression::Set(_, _, ty) => *ty,
            CheckedExpression::Array(_, _, _, ty) => *ty,
            CheckedExpression::Tuple(_, _, ty) => *ty,
            CheckedExpression::Range(_, _, _, ty) => *ty,
            CheckedExpression::IndexedDictionary(_, _, _, ty) => *ty,
            CheckedExpression::IndexedExpression(_, _, _, ty) => *ty,
            CheckedExpression::IndexedTuple(_, _, _, ty) => *ty,
            CheckedExpression::IndexedStruct(_, _, _, ty) => *ty,
            CheckedExpression::MethodCall(_, _, _, ty) => *ty,
            CheckedExpression::Var(CheckedVariable { ty, .. }, _) => *ty,
            CheckedExpression::OptionalNone(_, ty) => *ty,
            CheckedExpression::OptionalSome(_, _, ty) => *ty,
            CheckedExpression::ForcedUnwrap(_, _, ty) => *ty,
            CheckedExpression::Match(_, _, _, ty) => *ty,
            CheckedExpression::Garbage(_) => UNKNOWN_TYPE_ID,
        }
    }

    pub fn span(&self) -> Span {
        match self {
            CheckedExpression::Boolean(_, span) => *span,
            CheckedExpression::Call(_, span, _) => *span,
            CheckedExpression::NumericConstant(_, span, _) => *span,
            CheckedExpression::QuotedString(_, span) => *span,
            CheckedExpression::CharacterConstant(_, span) => *span,
            CheckedExpression::UnaryOp(_, _, span, _) => *span,
            CheckedExpression::BinaryOp(_, _, _, span, _) => *span,
            CheckedExpression::Dictionary(_, span, _) => *span,
            CheckedExpression::Set(_, span, _) => *span,
            CheckedExpression::Array(_, _, span, _) => *span,
            CheckedExpression::Tuple(_, span, _) => *span,
            CheckedExpression::Range(_, _, span, _) => *span,
            CheckedExpression::IndexedDictionary(_, _, span, _) => *span,
            CheckedExpression::IndexedExpression(_, _, span, _) => *span,
            CheckedExpression::IndexedTuple(_, _, span, _) => *span,
            CheckedExpression::IndexedStruct(_, _, span, _) => *span,
            CheckedExpression::MethodCall(_, _, span, _) => *span,
            CheckedExpression::Var(_, span) => *span,
            CheckedExpression::OptionalNone(span, _) => *span,
            CheckedExpression::OptionalSome(_, span, _) => *span,
            CheckedExpression::ForcedUnwrap(_, span, _) => *span,
            CheckedExpression::Match(_, _, span, _) => *span,
            CheckedExpression::Garbage(span) => *span,
        }
    }

    pub fn to_integer_constant(&self) -> Option<IntegerConstant> {
        match self {
            CheckedExpression::NumericConstant(constant, _, _) => constant.integer_constant(),
            CheckedExpression::UnaryOp(
                value,
                CheckedUnaryOperator::TypeCast(CheckedTypeCast::Infallible(_)),
                _,
                type_id,
            ) => {
                if !is_integer(*type_id) {
                    return None;
                }
                match &**value {
                    CheckedExpression::NumericConstant(constant, _, _) => {
                        constant.integer_constant()
                    }
                    _ => None,
                }
            }
            _ => None,
        }
    }

    pub fn is_mutable(&self) -> bool {
        match self {
            CheckedExpression::Var(var, _) => var.mutable,
            CheckedExpression::IndexedStruct(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedExpression(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedTuple(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedDictionary(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::ForcedUnwrap(expr, _, _) => expr.is_mutable(),
            _ => false,
        }
    }
}

#[derive(Clone, Debug)]
pub struct ResolvedNamespace {
    pub name: String,
    pub generic_parameters: Option<Vec<TypeId>>,
}

#[derive(Clone, Debug)]
pub struct CheckedCall {
    pub namespace: Vec<ResolvedNamespace>,
    pub name: String,
    pub callee_throws: bool,
    pub args: Vec<(String, CheckedExpression)>,
    pub type_args: Vec<TypeId>,
    pub linkage: FunctionLinkage,
    pub ty: TypeId,
}

#[derive(Clone, Debug)]
pub struct Scope {
    pub namespace_name: Option<String>,
    pub vars: Vec<CheckedVariable>,
    pub structs: Vec<(String, StructId)>,
    pub functions: Vec<(String, FunctionId)>,
    pub enums: Vec<(String, EnumId)>,
    pub types: Vec<(String, TypeId)>,
    pub parent: Option<ScopeId>,
    // Namespaces may also have children that are also namespaces
    pub children: Vec<ScopeId>,
}

impl Scope {
    pub fn new(parent: Option<ScopeId>) -> Self {
        Self {
            namespace_name: None,
            vars: Vec::new(),
            structs: Vec::new(),
            functions: Vec::new(),
            enums: Vec::new(),
            types: Vec::new(),
            parent,
            children: Vec::new(),
        }
    }
}

pub fn typecheck_namespace(
    parsed_namespace: &ParsedNamespace,
    scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let project_struct_len = project.structs.len();
    let project_enum_len = project.enums.len();
    let project_function_len = project.functions.len();

    for namespace in parsed_namespace.namespaces.iter() {
        let namespace_scope_id = project.create_scope(scope_id);
        project.scopes[namespace_scope_id].namespace_name = namespace.name.clone();
        project.scopes[scope_id].children.push(namespace_scope_id);
        typecheck_namespace(namespace, namespace_scope_id, project);
    }

    for (struct_id, structure) in parsed_namespace.structs.iter().enumerate() {
        //Ensure we know the types ahead of time, so they can be recursive
        let struct_id = struct_id + project_struct_len;
        project.types.push(Type::Struct(struct_id));

        let struct_type_id = project.types.len() - 1;
        if let Err(err) = project.add_type_to_scope(
            scope_id,
            structure.name.clone(),
            struct_type_id,
            structure.span,
        ) {
            error = error.or(Some(err));
        }

        if let Some(err) =
            typecheck_struct_predecl(structure, struct_type_id, struct_id, scope_id, project)
        {
            error = error.or(Some(err));
        }
    }

    for (enum_id, enum_) in parsed_namespace.enums.iter().enumerate() {
        let enum_id = enum_id + project_enum_len;
        project.types.push(Type::Enum(enum_id));

        let enum_type_id = project.types.len() - 1;
        if let Err(err) =
            project.add_type_to_scope(scope_id, enum_.name.clone(), enum_type_id, enum_.span)
        {
            error = error.or(Some(err));
        }

        if let Some(err) = typecheck_enum_predecl(enum_, enum_id, scope_id, project) {
            error = error.or(Some(err));
        }
    }

    for function in &parsed_namespace.functions {
        //Ensure we know the function ahead of time, so they can be recursive
        error = error.or(typecheck_function_predecl(function, scope_id, project));
    }

    for (struct_id, structure) in parsed_namespace.structs.iter().enumerate() {
        error = error.or(typecheck_struct(
            structure,
            struct_id + project_struct_len,
            scope_id,
            project,
        ));
    }

    for (enum_id, enum_) in parsed_namespace.enums.iter().enumerate() {
        error = error.or(typecheck_enum(
            enum_,
            enum_id + project_enum_len,
            project.find_type_in_scope(scope_id, &enum_.name).unwrap(),
            project.enums[enum_id + project_enum_len].scope_id,
            scope_id,
            project,
        ));
    }

    for (i, function) in parsed_namespace.functions.iter().enumerate() {
        project.current_function_index = Some(i + project_function_len);
        error = error.or(typecheck_function(function, scope_id, project));
        project.current_function_index = None;
    }

    error
}

fn typecheck_enum_predecl(
    enum_: &ParsedEnum,
    enum_id: EnumId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let enum_scope_id = project.create_scope(parent_scope_id);
    let mut generic_parameters = Vec::new();

    for (generic_parameter, parameter_span) in &enum_.generic_parameters {
        project
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let parameter_type_id = project.types.len() - 1;
        if let Err(err) = project.add_type_to_scope(
            enum_scope_id,
            generic_parameter.to_string(),
            parameter_type_id,
            *parameter_span,
        ) {
            error = error.or(Some(err));
        }

        generic_parameters.push(parameter_type_id);
    }

    let (type_id, type_error) = typecheck_typename(&enum_.underlying_type, enum_scope_id, project);
    error = error.or(type_error);

    let underlying_type = if type_id == UNKNOWN_TYPE_ID {
        None
    } else {
        Some(type_id)
    };

    project.enums.push(CheckedEnum {
        name: enum_.name.clone(),
        generic_parameters,
        variants: Vec::new(),
        scope_id: enum_scope_id,
        definition_linkage: enum_.definition_linkage,
        underlying_type,
        span: enum_.span,
    });

    match project.add_enum_to_scope(parent_scope_id, enum_.name.clone(), enum_id, enum_.span) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_enum(
    enum_: &ParsedEnum,
    enum_id: EnumId,
    enum_type_id: TypeId,
    enum_scope_id: ScopeId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    // Check enum variants and resolve them if needed.
    let mut variants = Vec::new();

    let mut next_constant_value: Option<u64> = Some(0);
    let mut seen_names = HashSet::new();

    let cast_to_underlying =
        |x: ParsedExpression, project: &mut Project| -> (CheckedExpression, Option<JaktError>) {
            let span = x.span();
            let expression = ParsedExpression::UnaryOp(
                Box::new(x),
                UnaryOperator::TypeCast(TypeCast::Infallible(enum_.underlying_type.clone())),
                span,
            );
            typecheck_expression(&expression, enum_scope_id, project, SafetyMode::Safe, None)
        };

    let underlying_type = project.enums[enum_id].underlying_type;

    for variant in &enum_.variants {
        match &variant {
            EnumVariant::Untyped(name, span) => {
                if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    if underlying_type.is_some() {
                        if next_constant_value.is_none() {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Missing enum variant value, the enum underlying type is not numeric, and so all enum variants must have explicit values".to_string(),
                                *span,
                            )));
                        } else {
                            let (checked_expression, type_error) = cast_to_underlying(
                                ParsedExpression::NumericConstant(
                                    NumericConstant::U64(next_constant_value?),
                                    *span,
                                ),
                                project,
                            );
                            error = error.or(type_error);

                            variants.push(CheckedEnumVariant::WithValue(
                                name.clone(),
                                checked_expression,
                                *span,
                            ));
                            next_constant_value = Some(next_constant_value? + 1);
                        }
                    } else {
                        variants.push(CheckedEnumVariant::Untyped(name.clone(), *span));
                    }

                    if project
                        .find_function_in_scope(enum_scope_id, name.as_str())
                        .is_none()
                    {
                        let function_scope_id = project.create_scope(parent_scope_id);

                        let checked_constructor = CheckedFunction {
                            name: name.clone(),
                            throws: false,
                            return_type: enum_type_id,
                            params: vec![],
                            function_scope_id,
                            generic_parameters: enum_
                                .generic_parameters
                                .iter()
                                .map(|x| {
                                    FunctionGenericParameter::InferenceGuide(
                                        project
                                            .find_type_in_scope(enum_scope_id, x.0.as_str())
                                            .unwrap(),
                                    )
                                })
                                .collect(),
                            block: CheckedBlock::new(),
                            linkage: FunctionLinkage::ImplicitEnumConstructor,
                        };

                        project.functions.push(checked_constructor);

                        if let Err(err) = project.add_function_to_scope(
                            enum_scope_id,
                            name.clone(),
                            project.functions.len() - 1,
                            *span,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                }
            }
            EnumVariant::WithValue(name, value, span) => {
                if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    let (checked_expression, type_error) =
                        cast_to_underlying((*value).clone(), project);
                    match checked_expression.to_integer_constant() {
                        Some(constant) => {
                            next_constant_value = Some(constant.to_usize() as u64 + 1);
                        }
                        None => {
                            error = error.or(Some(JaktError::TypecheckError(
                                format!(
                                    "Enum variant '{}' in enum '{}' has a non-constant value: {:?}",
                                    name, enum_.name, checked_expression
                                ),
                                *span,
                            )));
                        }
                    }
                    error = error.or(type_error);

                    variants.push(CheckedEnumVariant::WithValue(
                        name.clone(),
                        checked_expression,
                        *span,
                    ));

                    // FIXME: Generate a constructor
                }
            }
            EnumVariant::StructLike(name, members, span) => {
                if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    let mut member_names = HashSet::new();
                    let mut checked_members = Vec::new();
                    for member in members {
                        if member_names.contains(&member.name) {
                            error = error.or(Some(JaktError::TypecheckError(
                                format!(
                                    "Enum variant '{}' has a member named '{}' more than once",
                                    name, member.name
                                ),
                                *span,
                            )));
                        } else {
                            member_names.insert(member.name.clone());
                            let (decl, type_error) =
                                typecheck_typename(&member.ty, enum_scope_id, project);
                            error = error.or(type_error);
                            checked_members.push(CheckedVarDecl {
                                name: member.name.clone(),
                                ty: decl,
                                mutable: member.mutable,
                                span: member.span,
                            })
                        }
                    }

                    variants.push(CheckedEnumVariant::StructLike(
                        name.clone(),
                        checked_members.clone(),
                        *span,
                    ));

                    if project
                        .find_function_in_scope(enum_scope_id, name.as_str())
                        .is_none()
                    {
                        // Generate a constructor
                        let constructor_params = checked_members
                            .iter()
                            .map(|member| CheckedParameter {
                                requires_label: true,
                                variable: CheckedVariable {
                                    name: member.name.clone(),
                                    ty: member.ty,
                                    mutable: false,
                                },
                            })
                            .collect();
                        let function_scope_id = project.create_scope(parent_scope_id);

                        let checked_constructor = CheckedFunction {
                            name: name.clone(),
                            throws: false,
                            return_type: enum_type_id,
                            params: constructor_params,
                            function_scope_id,
                            generic_parameters: enum_
                                .generic_parameters
                                .iter()
                                .map(|x| {
                                    FunctionGenericParameter::InferenceGuide(
                                        project
                                            .find_type_in_scope(enum_scope_id, x.0.as_str())
                                            .unwrap(),
                                    )
                                })
                                .collect(),
                            block: CheckedBlock::new(),
                            linkage: FunctionLinkage::ImplicitEnumConstructor,
                        };

                        project.functions.push(checked_constructor);

                        if let Err(err) = project.add_function_to_scope(
                            enum_scope_id,
                            name.clone(),
                            project.functions.len() - 1,
                            *span,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                }
            }
            EnumVariant::Typed(name, unchecked_type, span) => {
                if !matches!(enum_.underlying_type, ParsedType::Empty) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Enum variants cannot have a type if the enum has an underlying type"
                            .to_string(),
                        *span,
                    )));
                } else if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    let (checked_type, type_error) =
                        typecheck_typename(unchecked_type, enum_scope_id, project);
                    error = error.or(type_error);

                    variants.push(CheckedEnumVariant::Typed(name.clone(), checked_type, *span));

                    if project
                        .find_function_in_scope(enum_scope_id, name.as_str())
                        .is_none()
                    {
                        // Generate a constructor
                        let constructor_params = vec![CheckedParameter {
                            requires_label: false,
                            variable: CheckedVariable {
                                name: "value".to_string(),
                                ty: checked_type,
                                mutable: false,
                            },
                        }];
                        let function_scope_id = project.create_scope(parent_scope_id);

                        let checked_constructor = CheckedFunction {
                            name: name.clone(),
                            throws: false,
                            return_type: enum_type_id,
                            params: constructor_params,
                            function_scope_id,
                            generic_parameters: enum_
                                .generic_parameters
                                .iter()
                                .map(|x| {
                                    FunctionGenericParameter::InferenceGuide(
                                        project
                                            .find_type_in_scope(enum_scope_id, x.0.as_str())
                                            .unwrap(),
                                    )
                                })
                                .collect(),
                            block: CheckedBlock::new(),
                            linkage: FunctionLinkage::ImplicitEnumConstructor,
                        };

                        project.functions.push(checked_constructor);

                        if let Err(err) = project.add_function_to_scope(
                            enum_scope_id,
                            name.clone(),
                            project.functions.len() - 1,
                            *span,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                }
            }
        }
    }

    project.enums[enum_id].variants = variants;

    error
}

fn typecheck_struct_predecl(
    structure: &ParsedStruct,
    struct_type_id: TypeId,
    struct_id: StructId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let struct_scope_id = project.create_scope(parent_scope_id);

    let mut generic_parameters = vec![];

    for (generic_parameter, parameter_span) in &structure.generic_parameters {
        project
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let parameter_type_id = project.types.len() - 1;

        generic_parameters.push(parameter_type_id);

        if let Err(err) = project.add_type_to_scope(
            struct_scope_id,
            generic_parameter.to_string(),
            parameter_type_id,
            *parameter_span,
        ) {
            error = error.or(Some(err));
        }
    }

    for function in &structure.methods {
        let mut generic_parameters = vec![];
        let method_scope_id = project.create_scope(struct_scope_id);

        for (generic_parameter, parameter_span) in &function.generic_parameters {
            project
                .types
                .push(Type::TypeVariable(generic_parameter.to_string()));
            let type_var_type_id = project.types.len() - 1;

            generic_parameters.push(FunctionGenericParameter::Parameter(type_var_type_id));

            if let Err(err) = project.add_type_to_scope(
                method_scope_id,
                generic_parameter.to_string(),
                type_var_type_id,
                *parameter_span,
            ) {
                error = error.or(Some(err));
            }
        }

        let mut checked_function = CheckedFunction {
            name: function.name.clone(),
            params: vec![],
            throws: function.throws,
            return_type: UNKNOWN_TYPE_ID,
            function_scope_id: method_scope_id,
            generic_parameters,
            block: CheckedBlock::new(),
            linkage: function.linkage,
        };

        for param in &function.params {
            if param.variable.name == "this" {
                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    ty: struct_type_id,
                    mutable: param.variable.mutable,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });
            } else {
                let (param_type, err) =
                    typecheck_typename(&param.variable.ty, method_scope_id, project);
                error = error.or(err);

                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    ty: param_type,
                    mutable: param.variable.mutable,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });
            }
        }

        project.functions.push(checked_function);
        if let Err(err) = project.add_function_to_scope(
            struct_scope_id,
            function.name.clone(),
            project.functions.len() - 1,
            structure.span,
        ) {
            error = error.or(Some(err));
        }
    }

    project.structs.push(CheckedStruct {
        name: structure.name.clone(),
        generic_parameters,
        fields: Vec::new(),
        scope_id: struct_scope_id,
        definition_linkage: structure.definition_linkage,
        definition_type: structure.definition_type,
    });

    match project.add_struct_to_scope(
        parent_scope_id,
        structure.name.clone(),
        struct_id,
        structure.span,
    ) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_struct(
    structure: &ParsedStruct,
    struct_id: StructId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let mut fields = Vec::new();

    let checked_struct = &mut project.structs[struct_id];
    let checked_struct_scope_id = checked_struct.scope_id;

    let struct_type_id = project.find_or_add_type_id(Type::Struct(struct_id));

    for unchecked_member in &structure.fields {
        let (checked_member_type, err) =
            typecheck_typename(&unchecked_member.ty, checked_struct_scope_id, project);
        error = error.or(err);

        fields.push(CheckedVarDecl {
            name: unchecked_member.name.clone(),
            ty: checked_member_type,
            mutable: unchecked_member.mutable,
            span: unchecked_member.span,
        });
    }

    if project
        .find_function_in_scope(checked_struct_scope_id, &structure.name)
        .is_none()
    {
        // No constructor found, so let's make one

        let mut constructor_params = Vec::new();
        for field in &fields {
            constructor_params.push(CheckedParameter {
                requires_label: true,
                variable: CheckedVariable {
                    name: field.name.clone(),
                    ty: field.ty,
                    mutable: field.mutable,
                },
            });
        }

        let function_scope_id = project.create_scope(parent_scope_id);

        let checked_constructor = CheckedFunction {
            name: structure.name.clone(),
            throws: structure.definition_type == DefinitionType::Class,
            return_type: struct_type_id,
            params: constructor_params,
            function_scope_id,
            generic_parameters: vec![],
            block: CheckedBlock::new(),
            linkage: FunctionLinkage::ImplicitConstructor,
        };

        // Internal constructor
        project.functions.push(checked_constructor);

        // Add constructor to the struct's scope
        if let Err(err) = project.add_function_to_scope(
            checked_struct_scope_id,
            structure.name.clone(),
            project.functions.len() - 1,
            structure.span,
        ) {
            error = error.or(Some(err));
        }
    }

    let checked_struct = &mut project.structs[struct_id];
    checked_struct.fields = fields;

    for function in &structure.methods {
        error = error.or(typecheck_method(function, project, struct_id));
    }

    error
}

fn typecheck_function_predecl(
    function: &ParsedFunction,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let function_scope_id = project.create_scope(parent_scope_id);

    let mut checked_function = CheckedFunction {
        name: function.name.clone(),
        params: vec![],
        throws: function.throws,
        return_type: UNKNOWN_TYPE_ID,
        function_scope_id,
        generic_parameters: vec![],
        block: CheckedBlock::new(),
        linkage: function.linkage,
    };

    let checked_function_scope_id = checked_function.function_scope_id;

    let mut generic_parameters = vec![];

    for (generic_parameter, parameter_span) in &function.generic_parameters {
        project
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let type_var_type_id = project.types.len() - 1;

        generic_parameters.push(FunctionGenericParameter::Parameter(type_var_type_id));

        if let Err(err) = project.add_type_to_scope(
            checked_function_scope_id,
            generic_parameter.to_string(),
            type_var_type_id,
            *parameter_span,
        ) {
            error = error.or(Some(err));
        }
    }

    checked_function.generic_parameters = generic_parameters;

    for param in &function.params {
        let (param_type, err) = typecheck_typename(&param.variable.ty, function_scope_id, project);
        error = error.or(err);

        let checked_variable = CheckedVariable {
            name: param.variable.name.clone(),
            ty: param_type,
            mutable: param.variable.mutable,
        };

        checked_function.params.push(CheckedParameter {
            requires_label: param.requires_label,
            variable: checked_variable.clone(),
        });
    }

    let function_id = project.functions.len();

    project.functions.push(checked_function);

    match project.add_function_to_scope(
        parent_scope_id,
        function.name.clone(),
        function_id,
        function.name_span,
    ) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_function(
    function: &ParsedFunction,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let function_id = project
        .find_function_in_scope(parent_scope_id, &function.name)
        .expect("Internal error: missing previously defined function");

    let checked_function = &mut project.functions[function_id];
    let function_scope_id = checked_function.function_scope_id;
    let function_linkage = checked_function.linkage;

    let mut param_vars = Vec::new();
    for param in &checked_function.params {
        param_vars.push(param.variable.clone());
    }

    for variable in param_vars.into_iter() {
        if let Err(err) = project.add_var_to_scope(function_scope_id, variable, function.name_span)
        {
            error = error.or(Some(err));
        }
    }

    // Do this once to resolve concrete types (if any)
    let (function_return_type, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    let checked_function = &mut project.functions[function_id];
    checked_function.return_type = function_return_type;

    let (block, err) = typecheck_block(
        &function.block,
        function_scope_id,
        project,
        SafetyMode::Safe,
    );
    error = error.or(err);

    // typecheck the return type again to resolve any generics.
    let (function_return_type, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type = if function_return_type == UNKNOWN_TYPE_ID {
        if let Some(CheckedStatement::Return(ret)) = block.stmts.last() {
            ret.ty()
        } else {
            VOID_TYPE_ID
        }
    } else {
        function_return_type
    };

    if function_linkage != FunctionLinkage::External
        && return_type != VOID_TYPE_ID
        && !block.definitely_returns
    {
        // FIXME: Use better span
        error = error.or(Some(JaktError::TypecheckError(
            "Control reaches end of non-void function".to_string(),
            function.name_span,
        )));
    }

    let checked_function = &mut project.functions[function_id];

    checked_function.block = block;
    checked_function.return_type = return_type;

    error
}

fn typecheck_method(
    function: &ParsedFunction,
    project: &mut Project,
    struct_id: StructId,
) -> Option<JaktError> {
    let mut error = None;

    let structure = &mut project.structs[struct_id];
    let structure_scope_id = structure.scope_id;
    let structure_linkage = structure.definition_linkage;

    let method_id = project.find_function_in_scope(structure_scope_id, &function.name);

    let method_id = method_id
        .expect("Internal error: we just pushed the checked function, but it's not present");

    let checked_function = &mut project.functions[method_id];
    let function_scope_id = checked_function.function_scope_id;

    let mut param_vars = Vec::new();
    for param in &checked_function.params {
        param_vars.push(param.variable.clone());
    }

    for variable in param_vars.into_iter() {
        if let Err(err) = project.add_var_to_scope(function_scope_id, variable, function.name_span)
        {
            error = error.or(Some(err));
        }
    }

    let (block, err) = typecheck_block(
        &function.block,
        function_scope_id,
        project,
        SafetyMode::Safe,
    );
    error = error.or(err);

    let (function_return_type, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type = if function_return_type == UNKNOWN_TYPE_ID {
        if let Some(CheckedStatement::Return(ret)) = block.stmts.first() {
            ret.ty()
        } else {
            VOID_TYPE_ID
        }
    } else {
        function_return_type
    };

    if structure_linkage != DefinitionLinkage::External
        && return_type != VOID_TYPE_ID
        && !block.definitely_returns
    {
        // FIXME: Use better span
        error = error.or(Some(JaktError::TypecheckError(
            "Control reaches end of non-void function".to_string(),
            function.name_span,
        )));
    }

    let checked_function = &mut project.functions[method_id];

    checked_function.block = block;
    checked_function.return_type = return_type;

    error
}

pub fn statement_definitely_returns(stmt: &CheckedStatement) -> bool {
    match stmt {
        CheckedStatement::Return(_) => true,
        CheckedStatement::If(_, then_block, Some(else_stmt)) => {
            // TODO: Things like `if true` should be also accepted as
            //       definitely returning, if we can prove at typecheck time
            //       that it's always truthy.
            then_block.definitely_returns && statement_definitely_returns(else_stmt.as_ref())
        }
        CheckedStatement::Block(block) => block.definitely_returns,
        CheckedStatement::Loop(block) => block.definitely_returns,
        CheckedStatement::While(_, block) => block.definitely_returns,
        CheckedStatement::For(_, _, block) => block.definitely_returns,
        _ => false,
    }
}

pub fn typecheck_block(
    block: &ParsedBlock,
    parent_scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedBlock, Option<JaktError>) {
    let mut error = None;
    let mut checked_block = CheckedBlock::new();

    let block_scope_id = project.create_scope(parent_scope_id);

    for stmt in &block.stmts {
        let (checked_stmt, err) = typecheck_statement(stmt, block_scope_id, project, safety_mode);
        error = error.or(err);

        if statement_definitely_returns(&checked_stmt) {
            checked_block.definitely_returns = true;
        }

        checked_block.stmts.push(checked_stmt);
    }

    (checked_block, error)
}

pub fn typecheck_statement(
    stmt: &ParsedStatement,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedStatement, Option<JaktError>) {
    let mut error = None;

    match stmt {
        ParsedStatement::Try(stmt, error_name, error_span, catch_block) => {
            let (checked_stmt, err) = typecheck_statement(stmt, scope_id, project, safety_mode);
            error = error.or(err);

            let error_struct_id = project
                .find_struct_in_scope(0, "Error")
                .expect("internal error: Error builtin definition not found");

            let error_decl = CheckedVariable {
                name: error_name.clone(),
                mutable: false,
                ty: project.find_or_add_type_id(Type::Struct(error_struct_id)),
            };

            let catch_scope_id = project.create_scope(scope_id);

            if let Err(err) = project.add_var_to_scope(catch_scope_id, error_decl, *error_span) {
                error = error.or(Some(err));
            }

            let (checked_catch_block, err) =
                typecheck_block(catch_block, catch_scope_id, project, safety_mode);
            error = error.or(err);
            (
                CheckedStatement::Try(
                    Box::new(checked_stmt),
                    error_name.clone(),
                    checked_catch_block,
                ),
                error,
            )
        }
        ParsedStatement::Throw(expr) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            // FIXME: Verify that the expression produces an Error
            (CheckedStatement::Throw(checked_expr), error)
        }
        ParsedStatement::For(iterator_name, range_expr, block) => {
            let (checked_expr, err) =
                typecheck_expression(range_expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let iterator_scope_id = project.create_scope(scope_id);

            let range_struct_id = project
                .find_struct_in_scope(0, "Range")
                .expect("internal error: Range builtin definition not found");

            let index_type;
            if let Type::GenericInstance(id, inner_type) = &project.types[checked_expr.ty()] {
                if id == &range_struct_id {
                    index_type = inner_type[0];
                } else {
                    panic!("Range expression doesn't have Range type");
                }
            } else {
                panic!("Range expression doesn't have Range type");
            }

            let iterator_decl = CheckedVariable {
                name: iterator_name.clone(),
                mutable: true,
                ty: index_type,
            };

            if let Err(err) =
                project.add_var_to_scope(iterator_scope_id, iterator_decl, range_expr.span())
            {
                error = error.or(Some(err));
            }

            let (checked_block, err) =
                typecheck_block(block, iterator_scope_id, project, safety_mode);
            error = error.or(err);

            (
                CheckedStatement::For(iterator_name.clone(), checked_expr, checked_block),
                error,
            )
        }
        ParsedStatement::Continue => (CheckedStatement::Continue, None),
        ParsedStatement::Break => (CheckedStatement::Break, None),
        ParsedStatement::Expression(expr) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);

            (CheckedStatement::Expression(checked_expr), err)
        }
        ParsedStatement::Defer(statement) => {
            let (checked_statement, err) =
                typecheck_statement(statement, scope_id, project, safety_mode);

            (CheckedStatement::Defer(Box::new(checked_statement)), err)
        }
        ParsedStatement::UnsafeBlock(block) => {
            let (checked_block, err) =
                typecheck_block(block, scope_id, project, SafetyMode::Unsafe);

            (CheckedStatement::Block(checked_block), err)
        }
        ParsedStatement::VarDecl(var_decl, init) => {
            let (mut checked_type_id, typename_err) =
                typecheck_typename(&var_decl.ty, scope_id, project);

            let (mut checked_expression, err) =
                typecheck_expression(init, scope_id, project, safety_mode, Some(checked_type_id));
            error = error.or(err);

            if checked_type_id == UNKNOWN_TYPE_ID && checked_expression.ty() != UNKNOWN_TYPE_ID {
                checked_type_id = checked_expression.ty()
            } else {
                error = error.or(typename_err);
            }

            let err = try_promote_constant_expr_to_type(
                checked_type_id,
                &mut checked_expression,
                &init.span(),
            );
            error = error.or(err);

            let checked_var_decl = CheckedVarDecl {
                name: var_decl.name.clone(),
                ty: checked_type_id,
                span: var_decl.span,
                mutable: var_decl.mutable,
            };

            if let Err(err) = project.add_var_to_scope(
                scope_id,
                CheckedVariable {
                    name: checked_var_decl.name.clone(),
                    ty: checked_var_decl.ty,
                    mutable: checked_var_decl.mutable,
                },
                checked_var_decl.span,
            ) {
                error = error.or(Some(err));
            }

            (
                CheckedStatement::VarDecl(checked_var_decl, checked_expression),
                error,
            )
        }
        ParsedStatement::If(cond, block, else_stmt) => {
            let (checked_cond, err) =
                typecheck_expression(cond, scope_id, project, safety_mode, None);
            error = error.or(err);

            if checked_cond.ty() != BOOL_TYPE_ID {
                error = error.or(Some(JaktError::TypecheckError(
                    "Condition must be a boolean expression".to_string(),
                    checked_cond.span(),
                )));
            }

            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);

            let else_output;
            if let Some(else_stmt) = else_stmt {
                let (checked_stmt, err) =
                    typecheck_statement(else_stmt, scope_id, project, safety_mode);
                error = error.or(err);

                else_output = Some(Box::new(checked_stmt));
            } else {
                else_output = None;
            }

            (
                CheckedStatement::If(checked_cond, checked_block, else_output),
                error,
            )
        }
        ParsedStatement::Loop(block) => {
            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);

            (CheckedStatement::Loop(checked_block), error)
        }
        ParsedStatement::While(cond, block) => {
            let (checked_cond, err) =
                typecheck_expression(cond, scope_id, project, safety_mode, None);
            error = error.or(err);

            if checked_cond.ty() != BOOL_TYPE_ID {
                error = error.or(Some(JaktError::TypecheckError(
                    "Condition must be a boolean expression".to_string(),
                    checked_cond.span(),
                )));
            }

            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);

            (CheckedStatement::While(checked_cond, checked_block), error)
        }
        ParsedStatement::Return(expr) => {
            let (output, err) = typecheck_expression(
                expr,
                scope_id,
                project,
                safety_mode,
                project
                    .current_function_index
                    .map(|i| project.functions[i].return_type),
            );

            (CheckedStatement::Return(output), err)
        }
        ParsedStatement::Block(block) => {
            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            (CheckedStatement::Block(checked_block), err)
        }
        ParsedStatement::InlineCpp(block, span) => {
            if safety_mode == SafetyMode::Safe {
                return (
                    CheckedStatement::InlineCpp(vec![]),
                    Some(JaktError::TypecheckError(
                        "Use of inline cpp block outside of unsafe block".to_string(),
                        *span,
                    )),
                );
            }

            let mut strings: Vec<String> = vec![];

            for statement in &block.stmts {
                match statement {
                    ParsedStatement::Expression(ParsedExpression::QuotedString(string, _)) => {
                        strings.push(string.clone())
                    }
                    _ => {
                        return (
                            CheckedStatement::InlineCpp(vec![]),
                            Some(JaktError::TypecheckError(
                                "Expected block of strings".to_string(),
                                *span,
                            )),
                        );
                    }
                }
            }
            (CheckedStatement::InlineCpp(strings), None)
        }
        ParsedStatement::Garbage => (CheckedStatement::Garbage, None),
    }
}

pub fn try_promote_constant_expr_to_type(
    lhs_type_id: TypeId,
    checked_rhs: &mut CheckedExpression,
    span: &Span,
) -> Option<JaktError> {
    if !is_integer(lhs_type_id) {
        return None;
    }
    if let Some(rhs_constant) = checked_rhs.to_integer_constant() {
        if let (Some(new_constant), new_ty) = rhs_constant.promote(lhs_type_id) {
            *checked_rhs = CheckedExpression::NumericConstant(new_constant, *span, new_ty);
        } else {
            return Some(JaktError::TypecheckError(
                "Integer promotion failed".to_string(),
                *span,
            ));
        }
    }

    None
}

pub fn typecheck_expression(
    expr: &ParsedExpression,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
    type_hint: Option<TypeId>,
) -> (CheckedExpression, Option<JaktError>) {
    let mut error = None;

    let unify_with_type_hint =
        |project: &mut Project, ty: &TypeId| -> (TypeId, Option<JaktError>) {
            if let Some(hint) = type_hint {
                if hint == UNKNOWN_TYPE_ID {
                    return (*ty, None);
                }

                let mut generic_interface = HashMap::new();
                let err =
                    check_types_for_compat(*ty, hint, &mut generic_interface, expr.span(), project);
                if err.is_some() {
                    return (*ty, err);
                }

                return (
                    substitute_typevars_in_type(*ty, &generic_interface, project),
                    None,
                );
            }

            (*ty, None)
        };

    match expr {
        ParsedExpression::Range(start_expr, end_expr, span) => {
            let (mut checked_start, err) =
                typecheck_expression(start_expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let (mut checked_end, err) =
                typecheck_expression(end_expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            // If the range starts or ends at a constant number, we try promoting the constant to the
            // type of the other end. This makes ranges like `0..array.size()` (as the 0 becomes 0uz).
            let err = try_promote_constant_expr_to_type(checked_start.ty(), &mut checked_end, span);
            error = error.or(err);
            let err = try_promote_constant_expr_to_type(checked_end.ty(), &mut checked_start, span);
            error = error.or(err);

            if checked_start.ty() != checked_end.ty() {
                error = error.or(Some(JaktError::TypecheckError(
                    "Range start and end must be the same type".to_string(),
                    *span,
                )))
            }

            let range_struct_id = project
                .find_struct_in_scope(0, "Range")
                .expect("internal error: Range builtin definition not found");

            let ty = Type::GenericInstance(range_struct_id, vec![checked_start.ty()]);
            let ty = project.find_or_add_type_id(ty);

            let (ty, err) = unify_with_type_hint(project, &ty);
            error = error.or(err);

            (
                CheckedExpression::Range(Box::new(checked_start), Box::new(checked_end), *span, ty),
                error,
            )
        }
        ParsedExpression::BinaryOp(lhs, op, rhs, span) => {
            let (checked_lhs, err) =
                typecheck_expression(lhs, scope_id, project, safety_mode, None);
            error = error.or(err);

            let (mut checked_rhs, err) =
                typecheck_expression(rhs, scope_id, project, safety_mode, None);
            error = error.or(err);

            let err = try_promote_constant_expr_to_type(checked_lhs.ty(), &mut checked_rhs, span);
            error = error.or(err);

            // TODO: actually do the binary operator typecheck against safe operations
            // For now, use a type we know
            let (ty, err) = typecheck_binary_operation(&checked_lhs, op, &checked_rhs, *span);
            error = error.or(err);

            let (ty, err) = unify_with_type_hint(project, &ty);
            error = error.or(err);

            (
                CheckedExpression::BinaryOp(
                    Box::new(checked_lhs),
                    op.clone(),
                    Box::new(checked_rhs),
                    *span,
                    ty,
                ),
                error,
            )
        }
        ParsedExpression::UnaryOp(expr, op, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let checked_op = match op {
                UnaryOperator::PreIncrement => CheckedUnaryOperator::PreIncrement,
                UnaryOperator::PostIncrement => CheckedUnaryOperator::PostIncrement,
                UnaryOperator::PreDecrement => CheckedUnaryOperator::PreDecrement,
                UnaryOperator::PostDecrement => CheckedUnaryOperator::PostDecrement,
                UnaryOperator::Negate => CheckedUnaryOperator::Negate,
                UnaryOperator::Dereference => CheckedUnaryOperator::Dereference,
                UnaryOperator::RawAddress => CheckedUnaryOperator::RawAddress,
                UnaryOperator::LogicalNot => CheckedUnaryOperator::LogicalNot,
                UnaryOperator::BitwiseNot => CheckedUnaryOperator::BitwiseNot,
                UnaryOperator::Is(unchecked_type) => {
                    let (type_id, err) = typecheck_typename(unchecked_type, scope_id, project);
                    error = error.or(err);
                    CheckedUnaryOperator::Is(type_id)
                }
                UnaryOperator::TypeCast(cast) => {
                    let (type_id, err) =
                        typecheck_typename(&cast.unchecked_type(), scope_id, project);
                    error = error.or(err);
                    let checked_cast = match cast {
                        TypeCast::Fallible(_) => CheckedTypeCast::Fallible(type_id),
                        TypeCast::Infallible(_) => CheckedTypeCast::Infallible(type_id),
                        TypeCast::Saturating(_) => CheckedTypeCast::Saturating(type_id),
                        TypeCast::Truncating(_) => CheckedTypeCast::Truncating(type_id),
                    };
                    CheckedUnaryOperator::TypeCast(checked_cast)
                }
            };

            let (checked_expr, err) =
                typecheck_unary_operation(checked_expr, checked_op, *span, project, safety_mode);
            error = error.or(err);

            (checked_expr, error)
        }
        ParsedExpression::OptionalNone(span) => (
            CheckedExpression::OptionalNone(*span, UNKNOWN_TYPE_ID),
            None,
        ),
        ParsedExpression::OptionalSome(expr, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            let ty = checked_expr.ty();

            (
                CheckedExpression::OptionalSome(Box::new(checked_expr), *span, ty),
                err,
            )
        }
        ParsedExpression::ForcedUnwrap(expr, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);

            let ty = &project.types[checked_expr.ty()];

            let optional_struct_id = project
                .find_struct_in_scope(0, "Optional")
                .expect("internal error: can't find builtin Optional type");

            let (ty, err) = match ty {
                Type::GenericInstance(struct_id, inner_tys) if struct_id == &optional_struct_id => {
                    (inner_tys[0], None)
                }
                _ => (
                    UNKNOWN_TYPE_ID,
                    err.or(Some(JaktError::TypecheckError(
                        "Forced unwrap only works on Optional".to_string(),
                        expr.span(),
                    ))),
                ),
            };
            error = error.or(err);

            let (ty, err) = unify_with_type_hint(project, &ty);
            error = error.or(err);

            (
                CheckedExpression::ForcedUnwrap(Box::new(checked_expr), *span, ty),
                error,
            )
        }
        ParsedExpression::Boolean(b, span) => (CheckedExpression::Boolean(*b, *span), None),
        ParsedExpression::Call(call, span) => {
            let (checked_call, err) = typecheck_call(
                call,
                scope_id,
                span,
                project,
                None,
                None,
                safety_mode,
                type_hint,
            );
            error = error.or(err);

            let (ty, err) = unify_with_type_hint(project, &checked_call.ty);
            error = error.or(err);

            (CheckedExpression::Call(checked_call, *span, ty), error)
        }
        ParsedExpression::NumericConstant(constant, span) => {
            // FIXME: Don't ignore type hint unification errors
            let (ty, _) = unify_with_type_hint(project, &constant.ty());

            (
                CheckedExpression::NumericConstant(constant.clone(), *span, ty),
                None,
            )
        }
        ParsedExpression::QuotedString(qs, span) => {
            let (_, err) = unify_with_type_hint(project, &STRING_TYPE_ID);

            (CheckedExpression::QuotedString(qs.clone(), *span), err)
        }
        ParsedExpression::CharacterLiteral(c, span) => {
            let (_, err) = unify_with_type_hint(project, &CCHAR_TYPE_ID);

            (CheckedExpression::CharacterConstant(*c, *span), err)
        }
        ParsedExpression::Var(v, span) => {
            if let Some(var) = project.find_var_in_scope(scope_id, v) {
                let (_, err) = unify_with_type_hint(project, &var.ty);

                (CheckedExpression::Var(var, *span), err)
            } else {
                (
                    CheckedExpression::Var(
                        CheckedVariable {
                            name: v.clone(),
                            ty: type_hint.unwrap_or(UNKNOWN_TYPE_ID),
                            mutable: false,
                        },
                        *span,
                    ),
                    Some(JaktError::TypecheckError(
                        "variable not found".to_string(),
                        *span,
                    )),
                )
            }
        }
        ParsedExpression::Array(vec, fill_size_expr, span) => {
            let mut inner_ty = UNKNOWN_TYPE_ID;
            let mut output = Vec::new();

            let mut checked_fill_size_expr = None;
            if let Some(fill_size_expr) = fill_size_expr {
                let (checked_expr, err) =
                    typecheck_expression(fill_size_expr, scope_id, project, safety_mode, None);
                checked_fill_size_expr = Some(Box::new(checked_expr));
                error = error.or(err);
            }

            for v in vec {
                let (checked_expr, err) =
                    typecheck_expression(v, scope_id, project, safety_mode, None);
                error = error.or(err);

                if inner_ty == UNKNOWN_TYPE_ID {
                    inner_ty = checked_expr.ty();
                } else if inner_ty != checked_expr.ty() {
                    error = error.or(Some(JaktError::TypecheckError(
                        "does not match type of previous values in vector".to_string(),
                        v.span(),
                    )))
                }

                output.push(checked_expr);
            }

            let array_struct_id = project
                .find_struct_in_scope(0, "Array")
                .expect("internal error: Array builtin definition not found");

            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(array_struct_id, vec![inner_ty]));

            let (ty, err) = unify_with_type_hint(project, &type_id);
            error = error.or(err);

            (
                CheckedExpression::Array(output, checked_fill_size_expr, *span, ty),
                error,
            )
        }
        ParsedExpression::Set(values, span) => {
            let mut inner_ty = UNKNOWN_TYPE_ID;
            let mut output = Vec::new();

            for value in values {
                let (checked_value, err) =
                    typecheck_expression(value, scope_id, project, safety_mode, None);
                error = error.or(err);

                if inner_ty == UNKNOWN_TYPE_ID {
                    inner_ty = checked_value.ty();
                } else if inner_ty != checked_value.ty() {
                    error = error.or(Some(JaktError::TypecheckError(
                        "does not match type of previous values in set".to_string(),
                        value.span(),
                    )))
                }
                output.push(checked_value);
            }

            let set_struct_id = project
                .find_struct_in_scope(0, "Set")
                .expect("internal error: Set builtin definition not found");

            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(set_struct_id, vec![inner_ty]));

            let (ty, err) = unify_with_type_hint(project, &type_id);
            error = error.or(err);

            (CheckedExpression::Set(output, *span, ty), error)
        }
        ParsedExpression::Dictionary(kv_pairs, span) => {
            let mut inner_ty = (UNKNOWN_TYPE_ID, UNKNOWN_TYPE_ID);
            let mut output = Vec::new();

            for (key, value) in kv_pairs {
                let (checked_key, err) =
                    typecheck_expression(key, scope_id, project, safety_mode, None);
                error = error.or(err);

                let (checked_value, err) =
                    typecheck_expression(value, scope_id, project, safety_mode, None);
                error = error.or(err);

                if inner_ty == (UNKNOWN_TYPE_ID, UNKNOWN_TYPE_ID) {
                    inner_ty = (checked_key.ty(), checked_value.ty());
                } else {
                    if inner_ty.0 != checked_key.ty() {
                        error = error.or(Some(JaktError::TypecheckError(
                            "does not match type of previous values in dictionary".to_string(),
                            key.span(),
                        )))
                    }

                    if inner_ty.1 != checked_value.ty() {
                        error = error.or(Some(JaktError::TypecheckError(
                            "does not match type of previous values in dictionary".to_string(),
                            value.span(),
                        )))
                    }
                }

                output.push((checked_key, checked_value));
            }

            let dictionary_struct_id = project
                .find_struct_in_scope(0, "Dictionary")
                .expect("internal error: Dictionary builtin definition not found");

            let type_id = project.find_or_add_type_id(Type::GenericInstance(
                dictionary_struct_id,
                vec![inner_ty.0, inner_ty.1],
            ));

            let (ty, err) = unify_with_type_hint(project, &type_id);
            error = error.or(err);

            (CheckedExpression::Dictionary(output, *span, ty), error)
        }
        ParsedExpression::Tuple(items, span) => {
            let mut checked_items = Vec::new();
            let mut checked_types = Vec::new();

            for item in items {
                let (checked_item, err) =
                    typecheck_expression(item, scope_id, project, safety_mode, None);
                error = error.or(err);

                checked_types.push(checked_item.ty());
                checked_items.push(checked_item);
            }

            let tuple_struct_id = project
                .find_struct_in_scope(0, "Tuple")
                .expect("internal error: Tuple builtin definition not found");

            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(tuple_struct_id, checked_types));

            let (ty, err) = unify_with_type_hint(project, &type_id);
            error = error.or(err);

            (CheckedExpression::Tuple(checked_items, *span, ty), error)
        }
        ParsedExpression::IndexedExpression(expr, idx, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let (checked_idx, err) =
                typecheck_expression(idx, scope_id, project, safety_mode, None);
            error = error.or(err);

            let mut expr_ty = UNKNOWN_TYPE_ID;

            let array_struct_id = project
                .find_struct_in_scope(0, "Array")
                .expect("internal error: Array builtin definition not found");

            let dict_struct_id = project
                .find_struct_in_scope(0, "Dictionary")
                .expect("internal error: Dictionary builtin definition not found");

            let ty = &project.types[checked_expr.ty()];

            match ty {
                Type::GenericInstance(parent_struct_id, inner_tys)
                    if parent_struct_id == &array_struct_id =>
                {
                    match checked_idx.ty() {
                        _ if is_integer(checked_idx.ty()) => {
                            expr_ty = inner_tys[0];
                        }

                        _ => {
                            error = error.or(Some(JaktError::TypecheckError(
                                "index is not an integer".to_string(),
                                idx.span(),
                            )))
                        }
                    }

                    let (expr_ty, err) = unify_with_type_hint(project, &expr_ty);
                    error = error.or(err);

                    (
                        CheckedExpression::IndexedExpression(
                            Box::new(checked_expr),
                            Box::new(checked_idx),
                            *span,
                            expr_ty,
                        ),
                        error,
                    )
                }
                Type::GenericInstance(parent_struct_id, inner_tys)
                    if parent_struct_id == &dict_struct_id =>
                {
                    let value_ty = inner_tys[1];
                    let optional_struct_id = project
                        .find_struct_in_scope(0, "Optional")
                        .expect("internal error: Optional builtin definition not found");

                    let inner_ty = project.find_or_add_type_id(Type::GenericInstance(
                        optional_struct_id,
                        vec![value_ty],
                    ));
                    expr_ty = inner_ty;

                    let (expr_ty, err) = unify_with_type_hint(project, &expr_ty);
                    error = error.or(err);

                    (
                        CheckedExpression::IndexedDictionary(
                            Box::new(checked_expr),
                            Box::new(checked_idx),
                            *span,
                            expr_ty,
                        ),
                        error,
                    )
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "index used on value that can't be indexed".to_string(),
                        expr.span(),
                    )));

                    let (expr_ty, err) = unify_with_type_hint(project, &expr_ty);
                    error = error.or(err);

                    (
                        CheckedExpression::IndexedExpression(
                            Box::new(checked_expr),
                            Box::new(checked_idx),
                            *span,
                            expr_ty,
                        ),
                        error,
                    )
                }
            }
        }
        ParsedExpression::IndexedTuple(expr, idx, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let mut ty = UNKNOWN_TYPE_ID;

            let tuple_struct_id = project
                .find_struct_in_scope(0, "Tuple")
                .expect("internal error: Tuple builtin definition not found");

            let checked_expr_ty = &project.types[checked_expr.ty()];
            match checked_expr_ty {
                Type::GenericInstance(parent_struct_id, inner_tys)
                    if parent_struct_id == &tuple_struct_id =>
                {
                    match inner_tys.get(*idx) {
                        Some(t) => ty = *t,
                        None => {
                            error = error.or(Some(JaktError::TypecheckError(
                                "tuple index past the end of the tuple".to_string(),
                                *span,
                            )))
                        }
                    }
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "tuple index used non-tuple value".to_string(),
                        expr.span(),
                    )))
                }
            }

            let (ty, err) = unify_with_type_hint(project, &ty);
            error = error.or(err);

            (
                CheckedExpression::IndexedTuple(Box::new(checked_expr), *idx, *span, ty),
                error,
            )
        }
        ParsedExpression::Match(expr, cases, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let mut checked_cases = Vec::new();
            let ty = &project.types[checked_expr.ty()];
            let subject_ty = checked_expr.ty();
            let mut generic_parameters = match ty {
                Type::GenericEnumInstance(enum_id, inner_tys) => {
                    let enum_ = &project.enums[*enum_id];
                    enum_.generic_parameters.iter().zip(inner_tys.iter()).fold(
                        HashMap::new(),
                        |mut acc, (param, ty)| {
                            acc.insert(*param, *ty);
                            acc
                        },
                    )
                }
                _ => HashMap::new(),
            };
            let mut final_result_type: Option<TypeId> = None;

            match ty {
                Type::Enum(enum_id) | Type::GenericEnumInstance(enum_id, _) => {
                    let enum_ = &project.enums[*enum_id];
                    let enum_name = enum_.name.clone();
                    let enum_id = *enum_id;
                    for case in cases {
                        match &case {
                            MatchCase::EnumVariant {
                                variant_name: name,
                                variant_arguments: args,
                                arguments_span: arg_span,
                                body,
                            } => {
                                let mut name = name.clone();
                                if name.len() == 1 {
                                    name.insert(0, (enum_name.clone(), name[0].1));
                                }
                                if name[0].0 != enum_name {
                                    error = error.or(Some(JaktError::TypecheckError(
                                        format!(
                                            "match case '{}' does not match enum '{}'",
                                            name[0].0, enum_name
                                        ),
                                        name[0].1,
                                    )));
                                } else {
                                    let variant_index: usize;
                                    let mut vars = Vec::new();
                                    {
                                        let enum_ = &project.enums[enum_id];
                                        let constructor_name = &name[1].0;
                                        let variant = (*enum_).variants.iter().find(|v| match v {
                                            CheckedEnumVariant::WithValue(name, _, _)
                                            | CheckedEnumVariant::Untyped(name, _)
                                            | CheckedEnumVariant::Typed(name, _, _)
                                            | CheckedEnumVariant::StructLike(name, _, _)
                                                if name == constructor_name =>
                                            {
                                                true
                                            }

                                            _ => false,
                                        });
                                        match variant {
                                            None => {
                                                error = error.or(Some(JaktError::TypecheckError(
                                                    format!(
                                                        "match case '{}' does not match enum '{}'",
                                                        name[0].0, enum_name
                                                    ),
                                                    name[1].1,
                                                )));
                                                return (
                                                    CheckedExpression::Match(
                                                        Box::new(checked_expr),
                                                        checked_cases,
                                                        *span,
                                                        // FIXME: Figure this out.
                                                        UNKNOWN_TYPE_ID,
                                                    ),
                                                    error,
                                                );
                                            }
                                            Some(variant) => {
                                                match variant {
                                                    CheckedEnumVariant::Untyped(name, _) => {
                                                        if !args.is_empty() {
                                                            error = error.or(Some(JaktError::TypecheckError(
                                                            format!(
                                                                "match case '{}' cannot have arguments",
                                                                name
                                                            ),
                                                            *arg_span,
                                                        )));
                                                        }
                                                    }
                                                    CheckedEnumVariant::Typed(name, ty, span) => {
                                                        if !args.is_empty() {
                                                            if args.len() != 1 {
                                                                error = error.or(Some(JaktError::TypecheckError(
                                                                format!(
                                                                    "match case '{}' must have exactly one argument",
                                                                    name
                                                                ),
                                                                *arg_span,
                                                            )));
                                                            }
                                                            let span = *span;

                                                            let ty = substitute_typevars_in_type(
                                                                *ty,
                                                                &generic_parameters,
                                                                project,
                                                            );
                                                            vars.push((
                                                                CheckedVariable {
                                                                    name: args[0].1.clone(),
                                                                    ty,
                                                                    mutable: false,
                                                                },
                                                                span,
                                                            ));
                                                        }
                                                    }
                                                    CheckedEnumVariant::WithValue(name, _, _) => {
                                                        if !args.is_empty() {
                                                            error = error.or(Some(JaktError::TypecheckError(
                                                            format!(
                                                                "match case '{}' cannot have arguments",
                                                                name
                                                            ),
                                                            *arg_span,
                                                        )));
                                                        }
                                                    }
                                                    CheckedEnumVariant::StructLike(
                                                        variant_name,
                                                        fields,
                                                        _,
                                                    ) => {
                                                        // Make the borrow checker shut up
                                                        let variant_name = variant_name.clone();
                                                        let fields = fields.clone();

                                                        let mut names_seen = HashMap::new();
                                                        for arg in args {
                                                            let name = &arg.0;
                                                            if name.is_none() {
                                                                error = error.or(Some(JaktError::TypecheckError(
                                                                format!("match case argument '{}' for struct-like enum variant cannot be anonymous", arg.1),
                                                                *arg_span,
                                                            )));
                                                            } else {
                                                                let name =
                                                                    name.as_ref().unwrap().clone();
                                                                if names_seen.contains_key(&name) {
                                                                    error = error.or(Some(JaktError::TypecheckError(
                                                                    format!(
                                                                        "match case argument '{}' is already defined",
                                                                        name
                                                                    ),
                                                                    *arg_span,
                                                                )));
                                                                } else {
                                                                    names_seen
                                                                        .insert(name.clone(), ());
                                                                    let field_type = fields
                                                                        .iter()
                                                                        .find(|f| f.name == name)
                                                                        .map(|f| f.ty);

                                                                    let field_type =
                                                                        if let Some(field_type) =
                                                                            field_type
                                                                        {
                                                                            Some(
                                                                        substitute_typevars_in_type(
                                                                            field_type,
                                                                            &generic_parameters,
                                                                            project,
                                                                        ),
                                                                    )
                                                                        } else {
                                                                            field_type
                                                                        };

                                                                    match field_type {
                                                                        Some(ty) => {
                                                                            let span = *span;
                                                                            vars.push((
                                                                                CheckedVariable {
                                                                                    name: arg
                                                                                        .1
                                                                                        .clone(),
                                                                                    ty,
                                                                                    mutable: false,
                                                                                },
                                                                                span,
                                                                            ))
                                                                        }
                                                                        None => {
                                                                            error = error.or(Some(JaktError::TypecheckError(
                                                                            format!("match case argument '{}' does not exist in struct-like enum variant '{}'", name, variant_name),
                                                                            *arg_span,
                                                                        )));
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

                                                // Look these up again to appease the borrow checker
                                                let enum_ = &project.enums[enum_id];
                                                let variant = (*enum_)
                                                    .variants
                                                    .iter()
                                                    .find(|v| {
                                                        matches!(v,
                                                        CheckedEnumVariant::WithValue(
                                                            name,
                                                            _,
                                                            _,
                                                        )
                                                        | CheckedEnumVariant::Untyped(name, _)
                                                        | CheckedEnumVariant::Typed(name, _, _)
                                                        | CheckedEnumVariant::StructLike(
                                                            name,
                                                            _,
                                                            _,
                                                        ) if name == constructor_name)
                                                    })
                                                    .unwrap();
                                                variant_index = enum_
                                                    .variants
                                                    .iter()
                                                    .position(|p| std::ptr::eq(p, variant))
                                                    .unwrap();
                                            }
                                        };
                                    }

                                    let new_scope_id = project.create_scope(scope_id);
                                    for (var, span) in vars {
                                        if let Err(err) =
                                            project.add_var_to_scope(new_scope_id, var, span)
                                        {
                                            error = error.or(Some(err));
                                        }
                                    }

                                    match body {
                                        MatchBody::Expression(expr) => {
                                            let (body, err) = typecheck_expression(
                                                expr,
                                                new_scope_id,
                                                project,
                                                safety_mode,
                                                None,
                                            );
                                            let span = *span;
                                            error = error.or(err);
                                            match final_result_type {
                                                Some(ty) => {
                                                    if let Some(err) = check_types_for_compat(
                                                        body.ty(),
                                                        ty,
                                                        &mut generic_parameters,
                                                        span,
                                                        project,
                                                    ) {
                                                        error = error.or(Some(err));
                                                    }
                                                }
                                                None => {
                                                    final_result_type = Some(body.ty());
                                                }
                                            }

                                            checked_cases.push(CheckedMatchCase::EnumVariant {
                                                variant_name: name[1].0.clone(),
                                                variant_arguments: (*args).clone(),
                                                subject_type_id: subject_ty,
                                                variant_index,
                                                scope_id: new_scope_id,
                                                body: CheckedMatchBody::Expression(body),
                                            });
                                        }
                                        MatchBody::Block(block) => {
                                            let (body, err) = typecheck_block(
                                                block,
                                                new_scope_id,
                                                project,
                                                safety_mode,
                                            );
                                            let span = *span;
                                            error = error.or(err);
                                            match final_result_type {
                                                Some(ty) => {
                                                    if let Some(err) = check_types_for_compat(
                                                        VOID_TYPE_ID,
                                                        ty,
                                                        &mut generic_parameters,
                                                        span,
                                                        project,
                                                    ) {
                                                        error = error.or(Some(err));
                                                    }
                                                }
                                                None => {
                                                    final_result_type = Some(VOID_TYPE_ID);
                                                }
                                            }

                                            checked_cases.push(CheckedMatchCase::EnumVariant {
                                                variant_name: name[1].0.clone(),
                                                variant_arguments: (*args).clone(),
                                                subject_type_id: subject_ty,
                                                variant_index,
                                                scope_id: new_scope_id,
                                                body: CheckedMatchBody::Block(body),
                                            });
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!(
                            "match used on non-enum value (nyi: {:?})",
                            project.types[subject_ty]
                        ),
                        expr.span(),
                    )))
                }
            }

            let mut err: Option<JaktError> = None;
            final_result_type = final_result_type.map(|p| {
                let (ty, unification_error) = unify_with_type_hint(project, &p);
                err = unification_error;
                ty
            });
            error = error.or(err);

            (
                CheckedExpression::Match(
                    Box::new(checked_expr),
                    checked_cases,
                    *span,
                    final_result_type.unwrap_or(VOID_TYPE_ID),
                ),
                error,
            )
        }
        ParsedExpression::IndexedStruct(expr, name, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let ty = UNKNOWN_TYPE_ID;

            let checked_expr_ty = &project.types[checked_expr.ty()];
            match checked_expr_ty {
                Type::GenericInstance(struct_id, _) | Type::Struct(struct_id) => {
                    let structure = &project.structs[*struct_id];

                    for member in &structure.fields {
                        if &member.name == name {
                            return (
                                CheckedExpression::IndexedStruct(
                                    Box::new(checked_expr),
                                    name.to_string(),
                                    *span,
                                    member.ty,
                                ),
                                None,
                            );
                        }
                    }

                    error = error.or(Some(JaktError::TypecheckError(
                        format!("unknown member of struct: {}.{}", structure.name, name),
                        *span,
                    )));
                }

                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "member access of non-struct value".to_string(),
                        *span,
                    )));
                }
            }

            let (ty, err) = unify_with_type_hint(project, &ty);
            error = error.or(err);

            (
                CheckedExpression::IndexedStruct(
                    Box::new(checked_expr),
                    name.to_string(),
                    *span,
                    ty,
                ),
                error,
            )
        }
        ParsedExpression::MethodCall(expr, call, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            if checked_expr.ty() == STRING_TYPE_ID {
                // Special-case the built-in so we don't accidentally find the user's definition
                let string_struct = project.find_struct_in_scope(0, "String");

                match string_struct {
                    Some(struct_id) => {
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(struct_id),
                            safety_mode,
                            type_hint,
                        );
                        error = error.or(err);

                        let (ty, err) = unify_with_type_hint(project, &checked_call.ty);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                ty,
                            ),
                            error,
                        )
                    }
                    _ => {
                        error = error.or(Some(JaktError::TypecheckError(
                            "no methods available on value".to_string(),
                            expr.span(),
                        )));

                        (CheckedExpression::Garbage(*span), error)
                    }
                }
            } else {
                let checked_expr_ty = &project.types[checked_expr.ty()];
                match checked_expr_ty {
                    Type::Struct(struct_id) => {
                        let struct_id = *struct_id;
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(struct_id),
                            safety_mode,
                            type_hint,
                        );
                        error = error.or(err);

                        let (ty, err) = unify_with_type_hint(project, &checked_call.ty);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                ty,
                            ),
                            error,
                        )
                    }
                    Type::GenericInstance(struct_id, _) => {
                        // ignore the inner types for now, but we'll need them in the future
                        let struct_id = *struct_id;
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(struct_id),
                            safety_mode,
                            type_hint,
                        );
                        error = error.or(err);

                        let (ty, err) = unify_with_type_hint(project, &checked_call.ty);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                ty,
                            ),
                            error,
                        )
                    }
                    _ => {
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "no methods available on value (type: {})",
                                checked_expr.ty()
                            ),
                            expr.span(),
                        )));

                        (CheckedExpression::Garbage(*span), error)
                    }
                }
            }
        }

        ParsedExpression::Operator(_, span) => (
            CheckedExpression::Garbage(*span),
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
        ParsedExpression::Garbage(span) => (
            CheckedExpression::Garbage(*span),
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
    }
}

pub fn typecheck_unary_operation(
    expr: CheckedExpression,
    op: CheckedUnaryOperator,
    span: Span,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedExpression, Option<JaktError>) {
    let expr_type_id = expr.ty();
    let expr_ty = &project.types[expr_type_id];

    match &op {
        CheckedUnaryOperator::Is(ty) => (
            CheckedExpression::UnaryOp(
                Box::new(expr),
                CheckedUnaryOperator::Is(*ty),
                span,
                BOOL_TYPE_ID,
            ),
            None,
        ),
        CheckedUnaryOperator::TypeCast(cast) => (
            CheckedExpression::UnaryOp(Box::new(expr), op.clone(), span, cast.ty()),
            None,
        ),
        CheckedUnaryOperator::Dereference => match expr_ty {
            Type::RawPtr(x) => {
                if safety_mode == SafetyMode::Unsafe {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, *x),
                        None,
                    )
                } else {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, *x),
                        Some(JaktError::TypecheckError(
                            "dereference of raw pointer outside of unsafe block".to_string(),
                            span,
                        )),
                    )
                }
            }
            _ => (
                CheckedExpression::UnaryOp(Box::new(expr), op, span, UNKNOWN_TYPE_ID),
                Some(JaktError::TypecheckError(
                    "dereference of a non-pointer value".to_string(),
                    span,
                )),
            ),
        },
        CheckedUnaryOperator::RawAddress => {
            let ty = expr.ty();

            let type_id = project.find_or_add_type_id(Type::RawPtr(ty));
            (
                CheckedExpression::UnaryOp(Box::new(expr), op, span, type_id),
                None,
            )
        }
        CheckedUnaryOperator::LogicalNot => {
            let ty = expr.ty();
            (
                CheckedExpression::UnaryOp(
                    Box::new(expr),
                    CheckedUnaryOperator::LogicalNot,
                    span,
                    ty,
                ),
                None,
            )
        }
        CheckedUnaryOperator::BitwiseNot => {
            let ty = expr.ty();
            (
                CheckedExpression::UnaryOp(
                    Box::new(expr),
                    CheckedUnaryOperator::BitwiseNot,
                    span,
                    ty,
                ),
                None,
            )
        }
        CheckedUnaryOperator::Negate => {
            let ty = expr.ty();

            match ty {
                crate::compiler::I8_TYPE_ID
                | crate::compiler::I16_TYPE_ID
                | crate::compiler::I32_TYPE_ID
                | crate::compiler::I64_TYPE_ID
                | crate::compiler::U8_TYPE_ID
                | crate::compiler::U16_TYPE_ID
                | crate::compiler::U32_TYPE_ID
                | crate::compiler::U64_TYPE_ID
                | crate::compiler::F32_TYPE_ID
                | crate::compiler::F64_TYPE_ID => (
                    CheckedExpression::UnaryOp(
                        Box::new(expr),
                        CheckedUnaryOperator::Negate,
                        span,
                        ty,
                    ),
                    None,
                ),
                _ => (
                    CheckedExpression::UnaryOp(
                        Box::new(expr),
                        CheckedUnaryOperator::Negate,
                        span,
                        ty,
                    ),
                    Some(JaktError::TypecheckError(
                        "negate on non-numeric value".to_string(),
                        span,
                    )),
                ),
            }
        }
        CheckedUnaryOperator::PostDecrement
        | CheckedUnaryOperator::PostIncrement
        | CheckedUnaryOperator::PreDecrement
        | CheckedUnaryOperator::PreIncrement => match expr.ty() {
            crate::compiler::I8_TYPE_ID
            | crate::compiler::I16_TYPE_ID
            | crate::compiler::I32_TYPE_ID
            | crate::compiler::I64_TYPE_ID
            | crate::compiler::U8_TYPE_ID
            | crate::compiler::U16_TYPE_ID
            | crate::compiler::U32_TYPE_ID
            | crate::compiler::U64_TYPE_ID
            | crate::compiler::F32_TYPE_ID
            | crate::compiler::F64_TYPE_ID => {
                if !expr.is_mutable() {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, expr_type_id),
                        Some(JaktError::TypecheckError(
                            "increment/decrement of immutable variable".to_string(),
                            span,
                        )),
                    )
                } else {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, expr_type_id),
                        None,
                    )
                }
            }
            _ => (
                CheckedExpression::UnaryOp(Box::new(expr), op, span, expr_type_id),
                Some(JaktError::TypecheckError(
                    "unary operation on non-numeric value".to_string(),
                    span,
                )),
            ),
        },
    }
}

pub fn typecheck_binary_operation(
    lhs: &CheckedExpression,
    op: &BinaryOperator,
    rhs: &CheckedExpression,
    span: Span,
) -> (TypeId, Option<JaktError>) {
    let mut ty = lhs.ty();
    match op {
        BinaryOperator::LogicalAnd
        | BinaryOperator::LogicalOr
        | BinaryOperator::LessThan
        | BinaryOperator::LessThanOrEqual
        | BinaryOperator::GreaterThan
        | BinaryOperator::GreaterThanOrEqual
        | BinaryOperator::Equal
        | BinaryOperator::NotEqual => {
            ty = BOOL_TYPE_ID;
        }
        BinaryOperator::Assign
        | BinaryOperator::AddAssign
        | BinaryOperator::SubtractAssign
        | BinaryOperator::MultiplyAssign
        | BinaryOperator::DivideAssign
        | BinaryOperator::ModuloAssign
        | BinaryOperator::BitwiseAndAssign
        | BinaryOperator::BitwiseOrAssign
        | BinaryOperator::BitwiseXorAssign
        | BinaryOperator::BitwiseLeftShiftAssign
        | BinaryOperator::BitwiseRightShiftAssign => {
            let lhs_ty = lhs.ty();
            let rhs_ty = rhs.ty();

            if lhs_ty != rhs_ty {
                return (
                    lhs.ty(),
                    Some(JaktError::TypecheckError(
                        format!(
                            "assignment between incompatible types ({:?} and {:?})",
                            lhs_ty, rhs_ty
                        ),
                        span,
                    )),
                );
            }

            if !lhs.is_mutable() {
                return (
                    lhs_ty,
                    Some(JaktError::TypecheckError(
                        "assignment to immutable variable".to_string(),
                        span,
                    )),
                );
            }
        }
        _ => {}
    }

    (ty, None)
}

pub fn resolve_call<'a>(
    call: &ParsedCall,
    namespaces: &mut [ResolvedNamespace],
    span: &Span,
    scope_id: ScopeId,
    project: &'a Project,
) -> (Option<&'a CheckedFunction>, Option<JaktError>) {
    let mut callee = None;
    let mut error = None;

    if let Some(namespace) = call.namespace.first() {
        // For now, assume class is our namespace
        // In the future, we'll have real namespaces

        if let Some(struct_id) = project.find_struct_in_scope(scope_id, namespace) {
            let structure = &project.structs[struct_id];

            // Look for the constructor
            if let Some(struct_id) = project.find_struct_in_scope(structure.scope_id, &call.name) {
                let structure = &project.structs[struct_id];

                if let Some(function_id) =
                    project.find_function_in_scope(structure.scope_id, &call.name)
                {
                    callee = Some(&project.functions[function_id]);
                }
            } else if let Some(function_id) =
                project.find_function_in_scope(structure.scope_id, &call.name)
            {
                callee = Some(&project.functions[function_id]);
            }

            if !structure.generic_parameters.is_empty() {
                namespaces[0].generic_parameters = Some(structure.generic_parameters.clone());
            }

            (callee, error)
        } else if let Some(enum_id) = project.find_enum_in_scope(scope_id, namespace) {
            let enum_ = &project.enums[enum_id];

            if let Some(function_id) = project.find_function_in_scope(enum_.scope_id, &call.name) {
                callee = Some(&project.functions[function_id]);
            }

            if !enum_.generic_parameters.is_empty() {
                namespaces[0].generic_parameters = Some(enum_.generic_parameters.clone());
            }

            (callee, error)
        } else if let Some(scope_id) = project.find_namespace_in_scope(scope_id, namespace) {
            if let Some(struct_id) = project.find_struct_in_scope(scope_id, &call.name) {
                let structure = &project.structs[struct_id];

                if let Some(function_id) =
                    project.find_function_in_scope(structure.scope_id, &call.name)
                {
                    callee = Some(&project.functions[function_id]);
                }
            } else if let Some(function_id) = project.find_function_in_scope(scope_id, &call.name) {
                callee = Some(&project.functions[function_id]);
            }

            (callee, error)
        } else {
            error = Some(JaktError::TypecheckError(
                format!("unknown namespace or class: {}", namespace),
                *span,
            ));

            (callee, error)
        }
    } else {
        // FIXME: Support function overloading.
        // Look for the constructor
        if let Some(struct_id) = project.find_struct_in_scope(scope_id, &call.name) {
            let structure = &project.structs[struct_id];

            if let Some(function_id) =
                project.find_function_in_scope(structure.scope_id, &call.name)
            {
                callee = Some(&project.functions[function_id]);
            }
        } else if let Some(function_id) = project.find_function_in_scope(scope_id, &call.name) {
            callee = Some(&project.functions[function_id]);
        }

        if callee.is_none() {
            error = Some(JaktError::TypecheckError(
                format!("call to unknown function: {}", call.name),
                *span,
            ));
        }

        (callee, error)
    }
}

pub fn typecheck_call(
    call: &ParsedCall,
    caller_scope_id: ScopeId,
    span: &Span,
    project: &mut Project,
    this_expr: Option<&CheckedExpression>,
    struct_id: Option<StructId>,
    safety_mode: SafetyMode,
    type_hint: Option<TypeId>,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;
    let mut return_ty = UNKNOWN_TYPE_ID;
    let mut linkage = FunctionLinkage::Internal;
    let mut generic_substitutions = HashMap::new();
    let mut type_args = vec![];
    let mut callee_throws = false;
    let mut resolved_namespaces = call
        .namespace
        .iter()
        .map(|n| ResolvedNamespace {
            name: n.clone(),
            generic_parameters: None,
        })
        .collect::<Vec<_>>();

    let callee_scope_id = match struct_id {
        Some(struct_id) => {
            // We are a method, so let's look up the scope id for our struct
            project.structs[struct_id].scope_id
        }
        _ => caller_scope_id,
    };

    match call.name.as_str() {
        "println" | "eprintln" if struct_id.is_none() => {
            // FIXME: This is a hack since println() and eprintln() are hard-coded into codegen at the moment.
            for arg in &call.args {
                let (checked_arg, err) =
                    typecheck_expression(&arg.1, caller_scope_id, project, safety_mode, None);
                error = error.or(err);

                let result_ty =
                    substitute_typevars_in_type(checked_arg.ty(), &generic_substitutions, project);

                if result_ty == VOID_TYPE_ID {
                    error = error.or(Some(JaktError::TypecheckError(
                        "println/eprintln can't take void values".into(),
                        *span,
                    )));
                }
                return_ty = VOID_TYPE_ID;

                checked_args.push((arg.0.clone(), checked_arg));
            }
        }
        _ => {
            let (callee, err) = resolve_call(
                call,
                &mut resolved_namespaces,
                span,
                callee_scope_id,
                project,
            );
            error = error.or(err);

            if let Some(callee) = callee {
                // Borrow checker workaround, would be nice to clean this up
                let callee = callee.clone();

                callee_throws = callee.throws;
                return_ty = callee.return_type;
                linkage = callee.linkage;

                // If the user gave us explicit type arguments, let's use them in our substitutions
                for (idx, type_arg) in call.type_args.iter().enumerate() {
                    let (checked_type, err) =
                        typecheck_typename(type_arg, caller_scope_id, project);
                    error = error.or(err);

                    if callee.generic_parameters.len() <= idx {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Trying to access generic parameter out of bounds".to_string(),
                            *span,
                        )));
                        continue;
                    }

                    // Find the associated type variable for this parameter, we'll use it in substitution
                    let typevar_type_id = match callee.generic_parameters[idx] {
                        FunctionGenericParameter::InferenceGuide(typevar_type_id)
                        | FunctionGenericParameter::Parameter(typevar_type_id) => typevar_type_id,
                    };

                    generic_substitutions.insert(typevar_type_id, checked_type);
                }

                // If this is a method, let's also add the types we know from our 'this' pointer
                if let Some(this_expr) = this_expr {
                    let type_id = this_expr.ty();
                    let param_type = &project.types[type_id];

                    if let Type::GenericInstance(struct_id, args) = param_type {
                        let structure = &project.structs[*struct_id];

                        let mut idx = 0;

                        while idx < structure.generic_parameters.len() {
                            generic_substitutions
                                .insert(structure.generic_parameters[idx], args[idx]);
                            idx += 1;
                        }
                    }
                }

                // Make sure that our call doesn't have a 'this' pointer to a static callee
                if this_expr.is_some() && callee.is_static() {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Cannot call static method on an instance of an object".to_string(),
                        *span,
                    )));
                }

                // This will be 0 for functions or 1 for instance methods, because of the
                // 'this' ptr
                let arg_offset = if this_expr.is_some() { 1 } else { 0 };

                // Check that we have the right number of arguments.
                if callee.params.len() != (call.args.len() + arg_offset) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "wrong number of arguments".to_string(),
                        *span,
                    )));
                } else {
                    let mut idx = 0;

                    while idx < call.args.len() {
                        let (mut checked_arg, err) = typecheck_expression(
                            &call.args[idx].1,
                            caller_scope_id,
                            project,
                            safety_mode,
                            None,
                        );
                        error = error.or(err);

                        // Borrowchecker workaround: since we need project to be mutable above, we
                        // need to let go of the previous callee and then look it up again
                        let (callee, _) = resolve_call(
                            call,
                            &mut resolved_namespaces,
                            span,
                            callee_scope_id,
                            project,
                        );
                        let callee = callee
                            .expect("internal error: previously resolved call is now unresolved");

                        if let ParsedExpression::Var(var_name, _) = &call.args[idx].1 {
                            if var_name != &callee.params[idx + arg_offset].variable.name
                                && callee.params[idx + arg_offset].requires_label
                                && call.args[idx].0 != callee.params[idx + arg_offset].variable.name
                            {
                                error = error.or(Some(JaktError::TypecheckError(
                                    "Wrong parameter name in argument label".to_string(),
                                    call.args[idx].1.span(),
                                )));
                            }
                        } else if callee.params[idx + arg_offset].requires_label
                            && call.args[idx].0 != callee.params[idx + arg_offset].variable.name
                        {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Wrong parameter name in argument label".to_string(),
                                call.args[idx].1.span(),
                            )));
                        }

                        let lhs_type_id = callee.params[idx + arg_offset].variable.ty;

                        let err =
                            try_promote_constant_expr_to_type(lhs_type_id, &mut checked_arg, span);
                        error = error.or(err);

                        let lhs_type_id = callee.params[idx + arg_offset].variable.ty;
                        let rhs_type_id = checked_arg.ty();

                        if let Some(err) = check_types_for_compat(
                            lhs_type_id,
                            rhs_type_id,
                            &mut generic_substitutions,
                            call.args[idx].1.span(),
                            project,
                        ) {
                            error = error.or(Some(err));
                        }

                        checked_args.push((call.args[idx].0.clone(), checked_arg));

                        idx += 1;
                    }
                }

                // We've now seen all the arguments and should be able to substitute the return type, if it's contains a
                // type variable. For the moment, we'll just checked to see if it's a type variable.
                if let Some(type_hint) = type_hint {
                    check_types_for_compat(
                        return_ty,
                        type_hint,
                        &mut generic_substitutions,
                        *span,
                        project,
                    );
                }
                return_ty = substitute_typevars_in_type(return_ty, &generic_substitutions, project);

                resolved_namespaces = resolved_namespaces
                    .iter()
                    .map(|n| ResolvedNamespace {
                        name: n.name.clone(),
                        generic_parameters: n.generic_parameters.as_ref().map(|p| {
                            p.iter()
                                .map(|ty| {
                                    substitute_typevars_in_type(
                                        *ty,
                                        &generic_substitutions,
                                        project,
                                    )
                                })
                                .collect()
                        }),
                    })
                    .collect();

                for generic_typevar in &callee.generic_parameters {
                    if let FunctionGenericParameter::Parameter(id) = generic_typevar {
                        if let Some(substitution) = generic_substitutions.get(id) {
                            type_args.push(*substitution)
                        } else {
                            error = error.or(Some(JaktError::TypecheckError(
                                "not all generic parameters have known types".into(),
                                *span,
                            )))
                        }
                    }
                }
            }
        }
    }

    (
        CheckedCall {
            namespace: resolved_namespaces,
            name: call.name.clone(),
            callee_throws,
            args: checked_args,
            type_args,
            linkage,
            ty: return_ty,
        },
        error,
    )
}

pub fn substitute_typevars_in_type(
    type_id: TypeId,
    generic_inferences: &HashMap<TypeId, TypeId>,
    project: &mut Project,
) -> TypeId {
    let mut result = substitute_typevars_in_type_helper(type_id, generic_inferences, project);

    loop {
        let fixed_point = substitute_typevars_in_type_helper(type_id, generic_inferences, project);

        if fixed_point == result {
            break;
        } else {
            result = fixed_point;
        }
    }

    result
}

fn substitute_typevars_in_type_helper(
    type_id: TypeId,
    generic_inferences: &HashMap<TypeId, TypeId>,
    project: &mut Project,
) -> TypeId {
    let ty = &project.types[type_id];
    match ty {
        Type::TypeVariable(_) => {
            if let Some(replacement) = generic_inferences.get(&type_id) {
                return *replacement;
            }
        }
        Type::GenericInstance(struct_id, args) => {
            let struct_id = *struct_id;
            let mut new_args = args.clone();

            for arg in &mut new_args {
                *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
            }

            return project.find_or_add_type_id(Type::GenericInstance(struct_id, new_args));
        }
        Type::GenericEnumInstance(enum_id, args) => {
            let enum_id = *enum_id;
            let mut new_args = args.clone();

            for arg in &mut new_args {
                *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
            }

            return project.find_or_add_type_id(Type::GenericEnumInstance(enum_id, new_args));
        }
        Type::Struct(struct_id) => {
            let struct_id = *struct_id;
            let structure = &project.structs[struct_id];

            if !structure.generic_parameters.is_empty() {
                let mut new_args = structure.generic_parameters.clone();

                for arg in &mut new_args {
                    *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
                }

                return project.find_or_add_type_id(Type::GenericInstance(struct_id, new_args));
            }
        }
        Type::Enum(enum_id) => {
            let enum_id = *enum_id;
            let enum_ = &project.enums[enum_id];

            if !enum_.generic_parameters.is_empty() {
                let mut new_args = enum_.generic_parameters.clone();

                for arg in &mut new_args {
                    *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
                }

                return project.find_or_add_type_id(Type::GenericEnumInstance(enum_id, new_args));
            }
        }
        _ => {}
    }

    type_id
}

pub fn check_types_for_compat(
    lhs_type_id: TypeId,
    rhs_type_id: TypeId,
    generic_inferences: &mut HashMap<TypeId, TypeId>,
    span: Span,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;
    let lhs_type = &project.types[lhs_type_id];

    match lhs_type {
        Type::TypeVariable(_) => {
            // If the call expects a generic type variable, let's see if we've already seen it
            if let Some(seen_type_id) = generic_inferences.get(&lhs_type_id) {
                // We've seen this type variable assigned something before
                // we should error if it's incompatible.

                if rhs_type_id != *seen_type_id {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!(
                            "Parameter type mismatch: {} vs {}",
                            codegen::codegen_type(*seen_type_id, project),
                            codegen::codegen_type(rhs_type_id, project)
                        ),
                        span,
                    )))
                }
            } else {
                // We haven't seen this type variable before, so go ahead
                // and give it an actual type during this call
                generic_inferences.insert(lhs_type_id, rhs_type_id);
            }
        }
        Type::GenericEnumInstance(lhs_enum_id, lhs_args) => {
            let lhs_args = lhs_args.clone();
            let rhs_type = &project.types[rhs_type_id];
            match rhs_type {
                Type::GenericEnumInstance(rhs_enum_id, rhs_args) => {
                    let rhs_args = rhs_args.clone();
                    if lhs_enum_id == rhs_enum_id {
                        // Same enum, so check the generic arguments

                        let lhs_enum = &project.enums[*lhs_enum_id];
                        if rhs_args.len() != lhs_args.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_enum.name
                                ),
                                span,
                            ));
                        }

                        let mut idx = 0;

                        while idx < lhs_args.len() {
                            let lhs_arg_type_id = lhs_args[idx];
                            let rhs_arg_type_id = rhs_args[idx];

                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Parameter type mismatch: {} vs {}",
                                codegen::codegen_type(lhs_type_id, project),
                                codegen::codegen_type(rhs_type_id, project)
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::GenericInstance(lhs_struct_id, lhs_args) => {
            let lhs_args = lhs_args.clone();
            let rhs_type = &project.types[rhs_type_id];
            match rhs_type {
                Type::GenericInstance(rhs_struct_id, rhs_args) => {
                    if lhs_struct_id == rhs_struct_id {
                        let rhs_args = rhs_args.clone();
                        // Same struct, perhaps this is an instantiation of it

                        let lhs_struct = &project.structs[*lhs_struct_id];
                        if rhs_args.len() != lhs_args.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_struct.name
                                ),
                                span,
                            ));
                        }

                        let mut idx = 0;

                        while idx < lhs_args.len() {
                            let lhs_arg_type_id = lhs_args[idx];
                            let rhs_arg_type_id = rhs_args[idx];

                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Parameter type mismatch: {} vs {}",
                                codegen::codegen_type(lhs_type_id, project),
                                codegen::codegen_type(rhs_type_id, project)
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::Enum(lhs_enum_id) => {
            if rhs_type_id == lhs_type_id {
                // They're the same type, might be okay to just leave now
                return None;
            }

            let rhs_type = &project.types[rhs_type_id];
            match rhs_type {
                Type::GenericEnumInstance(rhs_enum_id, rhs_args) => {
                    let rhs_args = rhs_args.clone();
                    if lhs_enum_id == rhs_enum_id {
                        let lhs_enum = &project.enums[*lhs_enum_id];
                        if rhs_args.len() != lhs_enum.generic_parameters.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_enum.name
                                ),
                                span,
                            ));
                        }

                        let lhs_enum_generic_parameters = lhs_enum.generic_parameters.clone();

                        let mut idx = 0;

                        while idx < rhs_args.len() {
                            let lhs_arg_type_id = lhs_enum_generic_parameters[idx];
                            let rhs_arg_type_id = rhs_args[idx];

                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Parameter type mismatch: {} vs {}",
                                codegen::codegen_type(lhs_type_id, project),
                                codegen::codegen_type(rhs_type_id, project)
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::Struct(lhs_struct_id) => {
            if rhs_type_id == lhs_type_id {
                // They're the same type, might be okay to just leave now
                return None;
            }

            let rhs_type = &project.types[rhs_type_id];
            match rhs_type {
                Type::GenericInstance(rhs_struct_id, args) => {
                    if lhs_struct_id == rhs_struct_id {
                        let args = args.clone();
                        // Same struct, perhaps this is an instantiation of it

                        let lhs_struct = &project.structs[*lhs_struct_id];
                        if args.len() != lhs_struct.generic_parameters.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_struct.name
                                ),
                                span,
                            ));
                        }

                        let mut idx = 0;

                        let lhs_arg_type_id = lhs_struct.generic_parameters[idx];
                        let rhs_arg_type_id = args[idx];

                        while idx < args.len() {
                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Parameter type mismatch: {} vs {}",
                                codegen::codegen_type(lhs_type_id, project),
                                codegen::codegen_type(rhs_type_id, project)
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        _ => {
            if rhs_type_id != lhs_type_id {
                error = error.or(Some(JaktError::TypecheckError(
                    format!(
                        "Parameter type mismatch: {} vs {}",
                        codegen::codegen_type(lhs_type_id, project),
                        codegen::codegen_type(rhs_type_id, project)
                    ),
                    span,
                )))
            }
        }
    }

    error
}

pub fn typecheck_typename(
    unchecked_type: &ParsedType,
    scope_id: ScopeId,
    project: &mut Project,
) -> (TypeId, Option<JaktError>) {
    let mut error = None;

    match unchecked_type {
        ParsedType::Name(name, span) => match name.as_str() {
            "i8" => (I8_TYPE_ID, None),
            "i16" => (I16_TYPE_ID, None),
            "i32" => (I32_TYPE_ID, None),
            "i64" => (I64_TYPE_ID, None),
            "u8" => (U8_TYPE_ID, None),
            "u16" => (U16_TYPE_ID, None),
            "u32" => (U32_TYPE_ID, None),
            "u64" => (U64_TYPE_ID, None),
            "f32" => (F32_TYPE_ID, None),
            "f64" => (F64_TYPE_ID, None),
            "c_char" => (CCHAR_TYPE_ID, None),
            "c_int" => (CINT_TYPE_ID, None),
            "usize" => (USIZE_TYPE_ID, None),
            "String" => (STRING_TYPE_ID, None),
            "bool" => (BOOL_TYPE_ID, None),
            "void" => (VOID_TYPE_ID, None),
            x => {
                let type_id = project.find_type_in_scope(scope_id, x);
                match type_id {
                    Some(type_id) => (type_id, None),
                    None => (
                        UNKNOWN_TYPE_ID,
                        Some(JaktError::TypecheckError("unknown type".to_string(), *span)),
                    ),
                }
            }
        },
        ParsedType::Empty => (UNKNOWN_TYPE_ID, None),
        ParsedType::Array(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let vector_struct_id = project
                .find_struct_in_scope(0, "Array")
                .expect("internal error: Array builtin definition not found");

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(vector_struct_id, vec![inner_ty]));

            (type_id, error)
        }
        ParsedType::Dictionary(key, value, _) => {
            let (key_ty, err) = typecheck_typename(key, scope_id, project);
            error = error.or(err);
            let (value_ty, err) = typecheck_typename(value, scope_id, project);
            error = error.or(err);

            let dictionary_struct_id = project
                .find_struct_in_scope(0, "Dictionary")
                .expect("internal error: Dictionary builtin definition not found");

            let type_id = project.find_or_add_type_id(Type::GenericInstance(
                dictionary_struct_id,
                vec![key_ty, value_ty],
            ));

            (type_id, error)
        }
        ParsedType::Set(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let set_struct_id = project
                .find_struct_in_scope(0, "Set")
                .expect("internal error: Set builtin definition not found");

            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(set_struct_id, vec![inner_ty]));

            (type_id, error)
        }
        ParsedType::Optional(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let optional_struct_id = project
                .find_struct_in_scope(0, "Optional")
                .expect("internal error: Optional builtin definition not found");

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(optional_struct_id, vec![inner_ty]));

            (type_id, error)
        }
        ParsedType::RawPtr(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let type_id = project.find_or_add_type_id(Type::RawPtr(inner_ty));

            (type_id, error)
        }
        ParsedType::GenericType(name, inner_types, span) => {
            let mut checked_inner_types = vec![];

            for inner_type in inner_types {
                let (inner_ty, err) = typecheck_typename(inner_type, scope_id, project);
                error = error.or(err);

                checked_inner_types.push(inner_ty);
            }

            let struct_id = project.find_struct_in_scope(scope_id, name);

            if let Some(struct_id) = struct_id {
                (
                    project
                        .find_or_add_type_id(Type::GenericInstance(struct_id, checked_inner_types)),
                    error,
                )
            } else {
                let enum_id = project.find_enum_in_scope(scope_id, name);
                if let Some(enum_id) = enum_id {
                    (
                        project.find_or_add_type_id(Type::GenericEnumInstance(
                            enum_id,
                            checked_inner_types,
                        )),
                        error,
                    )
                } else {
                    (
                        UNKNOWN_TYPE_ID,
                        Some(JaktError::TypecheckError(
                            format!("could not find {}", name),
                            *span,
                        )),
                    )
                }
            }
        }
    }
}
