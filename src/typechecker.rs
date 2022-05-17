use std::collections::HashMap;

use crate::{
    compiler::{
        BOOL_TYPE_ID, CCHAR_TYPE_ID, CINT_TYPE_ID, F32_TYPE_ID, F64_TYPE_ID, I16_TYPE_ID,
        I32_TYPE_ID, I64_TYPE_ID, I8_TYPE_ID, STRING_TYPE_ID, U16_TYPE_ID, U32_TYPE_ID,
        U64_TYPE_ID, U8_TYPE_ID, UNKNOWN_TYPE_ID, USIZE_TYPE_ID, VOID_TYPE_ID,
    },
    error::JaktError,
    lexer::Span,
    parser::{
        BinaryOperator, Block, Call, DefinitionLinkage, DefinitionType, Expression, Function,
        FunctionLinkage, ParsedFile, Statement, Struct, TypeCast, UnaryOperator, UncheckedType,
    },
};

pub type StructId = usize;
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
    Struct(StructId),
    RawPtr(TypeId),
}

pub fn is_integer(type_id: TypeId) -> bool {
    match type_id {
        USIZE_TYPE_ID | I8_TYPE_ID | I16_TYPE_ID | I32_TYPE_ID | I64_TYPE_ID | U8_TYPE_ID
        | U16_TYPE_ID | U32_TYPE_ID | U64_TYPE_ID => true,
        _ => false,
    }
}

pub fn can_fit_integer(type_id: TypeId, value: &IntegerConstant) -> bool {
    match *value {
        IntegerConstant::Signed(value) => match type_id {
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
    pub funs: Vec<CheckedFunction>,
    pub structs: Vec<CheckedStruct>,
    pub scopes: Vec<Scope>,
    pub types: Vec<Type>,
}

impl Project {
    pub fn new() -> Self {
        // Top-level (project-global) scope has no parent scope
        // and is the parent scope of all file scopes
        let project_global_scope = Scope::new(None);

        Self {
            funs: Vec::new(),
            structs: Vec::new(),
            scopes: vec![project_global_scope],
            types: Vec::new(),
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
                    format!("redefinition of {}", var.name),
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
            scope_id = scope.parent.clone();
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
                    format!("redefinition of {}", name),
                    span,
                ));
            }
        }
        scope.structs.push((name, struct_id));

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
            scope_id = scope.parent.clone();
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

        for (existing_fun, _) in &scope.funs {
            if &name == existing_fun {
                return Err(JaktError::TypecheckError(
                    format!("redefinition of {}", name),
                    span,
                ));
            }
        }
        scope.funs.push((name, function_id));

        Ok(())
    }

    pub fn find_function_in_scope(&self, scope_id: ScopeId, fun_name: &str) -> Option<FunctionId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = &self.scopes[current_id];
            for s in &scope.funs {
                if s.0 == fun_name {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent.clone();
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
                    format!("redefinition of {}", type_name),
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
            scope_id = scope.parent.clone();
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
pub struct CheckedParameter {
    pub requires_label: bool,
    pub variable: CheckedVariable,
}

#[derive(Debug, Clone)]
pub struct CheckedFunction {
    pub name: String,
    pub return_type: TypeId,
    pub params: Vec<CheckedParameter>,
    pub generic_parameters: Vec<TypeId>,
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
}

impl CheckedBlock {
    pub fn new() -> Self {
        Self { stmts: Vec::new() }
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
    While(CheckedExpression, CheckedBlock),
    Return(CheckedExpression),
    For(String, CheckedExpression, CheckedBlock),
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
        let new_constant = match self {
            IntegerConstant::Signed(value) => match type_id {
                I8_TYPE_ID => NumericConstant::I8(*value as i8),
                I16_TYPE_ID => NumericConstant::I16(*value as i16),
                I32_TYPE_ID => NumericConstant::I32(*value as i32),
                I64_TYPE_ID => NumericConstant::I64(*value as i64),
                U8_TYPE_ID => NumericConstant::U8(*value as u8),
                U16_TYPE_ID => NumericConstant::U16(*value as u16),
                U32_TYPE_ID => NumericConstant::U32(*value as u32),
                U64_TYPE_ID => NumericConstant::U64(*value as u64),
                USIZE_TYPE_ID => NumericConstant::USize(*value as u64),
                _ => panic!("Bogus state in IntegerConstant::promote"),
            },
            IntegerConstant::Unsigned(value) => match type_id {
                I8_TYPE_ID => NumericConstant::I8(*value as i8),
                I16_TYPE_ID => NumericConstant::I16(*value as i16),
                I32_TYPE_ID => NumericConstant::I32(*value as i32),
                I64_TYPE_ID => NumericConstant::I64(*value as i64),
                U8_TYPE_ID => NumericConstant::U8(*value as u8),
                U16_TYPE_ID => NumericConstant::U16(*value as u16),
                U32_TYPE_ID => NumericConstant::U32(*value as u32),
                U64_TYPE_ID => NumericConstant::U64(*value as u64),
                USIZE_TYPE_ID => NumericConstant::USize(*value as u64),
                _ => panic!("Bogus state in IntegerConstant::promote"),
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
    IndexedExpression(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    IndexedTuple(Box<CheckedExpression>, usize, Span, TypeId),
    IndexedStruct(Box<CheckedExpression>, String, Span, TypeId),

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
            CheckedExpression::Array(_, _, _, ty) => *ty,
            CheckedExpression::Tuple(_, _, ty) => *ty,
            CheckedExpression::Range(_, _, _, ty) => *ty,
            CheckedExpression::IndexedExpression(_, _, _, ty) => *ty,
            CheckedExpression::IndexedTuple(_, _, _, ty) => *ty,
            CheckedExpression::IndexedStruct(_, _, _, ty) => *ty,
            CheckedExpression::MethodCall(_, _, _, ty) => *ty,
            CheckedExpression::Var(CheckedVariable { ty, .. }, _) => *ty,
            CheckedExpression::OptionalNone(_, ty) => *ty,
            CheckedExpression::OptionalSome(_, _, ty) => *ty,
            CheckedExpression::ForcedUnwrap(_, _, ty) => *ty,
            CheckedExpression::Garbage(_) => UNKNOWN_TYPE_ID,
        }
    }

    pub fn to_integer_constant(&self) -> Option<IntegerConstant> {
        match self {
            CheckedExpression::NumericConstant(constant, _, _) => constant.integer_constant(),
            _ => None,
        }
    }

    pub fn is_mutable(&self) -> bool {
        match self {
            CheckedExpression::Var(var, _) => var.mutable,
            CheckedExpression::IndexedStruct(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedExpression(expr, _, _, _) => expr.is_mutable(),
            _ => false,
        }
    }
}

#[derive(Clone, Debug)]
pub struct CheckedCall {
    pub namespace: Vec<String>,
    pub name: String,
    pub args: Vec<(String, CheckedExpression)>,
    pub type_args: Vec<TypeId>,
    pub linkage: FunctionLinkage,
    pub ty: TypeId,
}

#[derive(Clone, Debug)]
pub struct Scope {
    pub vars: Vec<CheckedVariable>,
    pub structs: Vec<(String, StructId)>,
    pub funs: Vec<(String, FunctionId)>,
    pub types: Vec<(String, TypeId)>,
    pub parent: Option<ScopeId>,
}

impl Scope {
    pub fn new(parent: Option<ScopeId>) -> Self {
        Self {
            vars: Vec::new(),
            structs: Vec::new(),
            funs: Vec::new(),
            types: Vec::new(),
            parent,
        }
    }
}

pub fn typecheck_file(
    parsed_file: &ParsedFile,
    scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let project_struct_len = project.structs.len();

    for (struct_id, structure) in parsed_file.structs.iter().enumerate() {
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

        typecheck_struct_predecl(structure, struct_type_id, struct_id, scope_id, project);
    }

    for fun in &parsed_file.funs {
        //Ensure we know the function ahead of time, so they can be recursive
        error = error.or(typecheck_fun_predecl(fun, scope_id, project));
    }

    for (struct_id, structure) in parsed_file.structs.iter().enumerate() {
        error = error.or(typecheck_struct(
            structure,
            struct_id + project_struct_len,
            scope_id,
            project,
        ));
    }

    for fun in &parsed_file.funs {
        error = error.or(typecheck_fun(fun, scope_id, project));
    }

    error
}

fn typecheck_struct_predecl(
    structure: &Struct,
    struct_type_id: TypeId,
    struct_id: StructId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let struct_scope_id = project.create_scope(parent_scope_id);

    for fun in &structure.methods {
        let mut generic_parameters = vec![];
        let method_scope_id = project.create_scope(struct_scope_id);

        for (generic_parameter, parameter_span) in &fun.generic_parameters {
            project
                .types
                .push(Type::TypeVariable(generic_parameter.to_string()));
            let type_var_type_id = project.types.len() - 1;

            generic_parameters.push(type_var_type_id);

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
            name: fun.name.clone(),
            params: vec![],
            return_type: UNKNOWN_TYPE_ID,
            function_scope_id: method_scope_id,
            generic_parameters,
            block: CheckedBlock::new(),
            linkage: fun.linkage.clone(),
        };

        for param in &fun.params {
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

        project.funs.push(checked_function);
        if let Err(err) = project.add_function_to_scope(
            struct_scope_id,
            fun.name.clone(),
            project.funs.len() - 1,
            structure.span,
        ) {
            error = error.or(Some(err));
        }
    }

    project.structs.push(CheckedStruct {
        name: structure.name.clone(),
        generic_parameters: vec![],
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
    structure: &Struct,
    struct_id: StructId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let mut fields = Vec::new();

    for (generic_parameter, parameter_span) in &structure.generic_parameters {
        project
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let parameter_type_id = project.types.len() - 1;

        let checked_struct = &mut project.structs[struct_id];
        let checked_struct_scope_id = checked_struct.scope_id;

        checked_struct.generic_parameters.push(parameter_type_id);

        if let Err(err) = project.add_type_to_scope(
            checked_struct_scope_id,
            generic_parameter.to_string(),
            parameter_type_id,
            *parameter_span,
        ) {
            error = error.or(Some(err));
        }
    }

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

    let checked_struct = &mut project.structs[struct_id];
    checked_struct.fields = fields;

    let checked_constructor = CheckedFunction {
        name: structure.name.clone(),
        return_type: struct_type_id,
        params: constructor_params,
        function_scope_id,
        generic_parameters: vec![],
        block: CheckedBlock::new(),
        linkage: FunctionLinkage::ImplicitConstructor,
    };

    // Internal constructor
    project.funs.push(checked_constructor);

    let checked_struct_scope_id = checked_struct.scope_id;

    // Add constructor to the struct's scope
    if let Err(err) = project.add_function_to_scope(
        checked_struct_scope_id,
        structure.name.clone(),
        project.funs.len() - 1,
        structure.span,
    ) {
        error = error.or(Some(err));
    }

    // Add helper function for constructor to the parent scope
    if let Err(err) = project.add_function_to_scope(
        parent_scope_id,
        structure.name.clone(),
        project.funs.len() - 1,
        structure.span,
    ) {
        error = error.or(Some(err));
    }

    for fun in &structure.methods {
        error = error.or(typecheck_method(fun, project, struct_id));
    }

    error
}

fn typecheck_fun_predecl(
    fun: &Function,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let function_scope_id = project.create_scope(parent_scope_id);

    let mut checked_function = CheckedFunction {
        name: fun.name.clone(),
        params: vec![],
        return_type: UNKNOWN_TYPE_ID,
        function_scope_id,
        generic_parameters: vec![],
        block: CheckedBlock::new(),
        linkage: fun.linkage.clone(),
    };

    let checked_function_scope_id = checked_function.function_scope_id;

    let mut generic_parameters = vec![];

    for (generic_parameter, parameter_span) in &fun.generic_parameters {
        project
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let type_var_type_id = project.types.len() - 1;

        generic_parameters.push(type_var_type_id);

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

    for param in &fun.params {
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

    let function_id = project.funs.len();

    project.funs.push(checked_function);

    match project.add_function_to_scope(
        parent_scope_id,
        fun.name.clone(),
        function_id,
        fun.name_span,
    ) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_fun(
    fun: &Function,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let function_id = project
        .find_function_in_scope(parent_scope_id, &fun.name)
        .expect("Internal error: missing previously defined function");

    let checked_function = &mut project.funs[function_id];
    let function_scope_id = checked_function.function_scope_id;

    let mut param_vars = Vec::new();
    for param in &checked_function.params {
        param_vars.push(param.variable.clone());
    }

    for variable in param_vars.into_iter() {
        if let Err(err) = project.add_var_to_scope(function_scope_id, variable, fun.name_span) {
            error = error.or(Some(err));
        }
    }

    let (block, err) = typecheck_block(&fun.block, function_scope_id, project, SafetyMode::Safe);
    error = error.or(err);

    let (fun_return_type, err) = typecheck_typename(&fun.return_type, function_scope_id, project);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type = if fun_return_type == UNKNOWN_TYPE_ID {
        if let Some(CheckedStatement::Return(ret)) = block.stmts.first() {
            ret.ty()
        } else {
            VOID_TYPE_ID
        }
    } else {
        fun_return_type.clone()
    };

    let checked_function = &mut project.funs[function_id];

    checked_function.block = block;
    checked_function.return_type = return_type;

    error
}

fn typecheck_method(
    fun: &Function,
    project: &mut Project,
    struct_id: StructId,
) -> Option<JaktError> {
    let mut error = None;

    let structure = &mut project.structs[struct_id];
    let structure_scope_id = structure.scope_id;

    let method_id = project.find_function_in_scope(structure_scope_id, &fun.name);

    let method_id = method_id
        .expect("Internal error: we just pushed the checked function, but it's not present");

    let checked_function = &mut project.funs[method_id];
    let function_scope_id = checked_function.function_scope_id;

    let mut param_vars = Vec::new();
    for param in &checked_function.params {
        param_vars.push(param.variable.clone());
    }

    for variable in param_vars.into_iter() {
        if let Err(err) = project.add_var_to_scope(function_scope_id, variable, fun.name_span) {
            error = error.or(Some(err));
        }
    }

    let (block, err) = typecheck_block(&fun.block, function_scope_id, project, SafetyMode::Safe);
    error = error.or(err);

    let (fun_return_type, err) = typecheck_typename(&fun.return_type, function_scope_id, project);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type = if fun_return_type == UNKNOWN_TYPE_ID {
        if let Some(CheckedStatement::Return(ret)) = block.stmts.first() {
            ret.ty()
        } else {
            VOID_TYPE_ID
        }
    } else {
        fun_return_type.clone()
    };

    let checked_function = &mut project.funs[method_id];

    checked_function.block = block;
    checked_function.return_type = return_type;

    error
}

pub fn typecheck_block(
    block: &Block,
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

        checked_block.stmts.push(checked_stmt);
    }

    (checked_block, error)
}

pub fn typecheck_statement(
    stmt: &Statement,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedStatement, Option<JaktError>) {
    let mut error = None;

    match stmt {
        Statement::For(iterator_name, range_expr, block) => {
            let (checked_expr, err) =
                typecheck_expression(range_expr, scope_id, project, safety_mode);
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
                typecheck_block(block, iterator_scope_id, project, SafetyMode::Unsafe);
            error = error.or(err);

            (
                CheckedStatement::For(iterator_name.clone(), checked_expr, checked_block),
                error,
            )
        }
        Statement::Expression(expr) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);

            (CheckedStatement::Expression(checked_expr), err)
        }
        Statement::Defer(statement) => {
            let (checked_statement, err) =
                typecheck_statement(statement, scope_id, project, safety_mode);

            (CheckedStatement::Defer(Box::new(checked_statement)), err)
        }
        Statement::UnsafeBlock(block) => {
            let (checked_block, err) =
                typecheck_block(block, scope_id, project, SafetyMode::Unsafe);

            (CheckedStatement::Block(checked_block), err)
        }
        Statement::VarDecl(var_decl, init) => {
            let (mut checked_expression, err) =
                typecheck_expression(init, scope_id, project, safety_mode);
            error = error.or(err);

            let (mut checked_type_id, err) = typecheck_typename(&var_decl.ty, scope_id, project);

            if checked_type_id == UNKNOWN_TYPE_ID && checked_expression.ty() != UNKNOWN_TYPE_ID {
                checked_type_id = checked_expression.ty()
            } else {
                error = error.or(err);
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
                    ty: checked_var_decl.ty.clone(),
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
        Statement::If(cond, block, else_stmt) => {
            let (checked_cond, err) = typecheck_expression(cond, scope_id, project, safety_mode);
            error = error.or(err);

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
        Statement::While(cond, block) => {
            let (checked_cond, err) = typecheck_expression(cond, scope_id, project, safety_mode);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);

            (CheckedStatement::While(checked_cond, checked_block), error)
        }
        Statement::Return(expr) => {
            let (output, err) = typecheck_expression(expr, scope_id, project, safety_mode);

            (CheckedStatement::Return(output), err)
        }
        Statement::Block(block) => {
            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            (CheckedStatement::Block(checked_block), err)
        }
        Statement::Garbage => (CheckedStatement::Garbage, None),
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

    return None;
}

pub fn typecheck_expression(
    expr: &Expression,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedExpression, Option<JaktError>) {
    let mut error = None;

    match expr {
        Expression::Range(start_expr, end_expr, span) => {
            let (mut checked_start, err) =
                typecheck_expression(&start_expr, scope_id, project, safety_mode);
            error = error.or(err);

            let (mut checked_end, err) =
                typecheck_expression(&end_expr, scope_id, project, safety_mode);
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
            (
                CheckedExpression::Range(
                    Box::new(checked_start),
                    Box::new(checked_end),
                    *span,
                    project.find_or_add_type_id(ty),
                ),
                error,
            )
        }
        Expression::BinaryOp(lhs, op, rhs, span) => {
            let (checked_lhs, err) = typecheck_expression(lhs, scope_id, project, safety_mode);
            error = error.or(err);

            let (mut checked_rhs, err) = typecheck_expression(rhs, scope_id, project, safety_mode);
            error = error.or(err);

            let err = try_promote_constant_expr_to_type(checked_lhs.ty(), &mut checked_rhs, span);
            error = error.or(err);

            // TODO: actually do the binary operator typecheck against safe operations
            // For now, use a type we know
            let (ty, err) = typecheck_binary_operation(&checked_lhs, &op, &checked_rhs, *span);
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
        Expression::UnaryOp(expr, op, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);
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
        Expression::OptionalNone(span) => (
            CheckedExpression::OptionalNone(*span, UNKNOWN_TYPE_ID),
            None,
        ),
        Expression::OptionalSome(expr, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);
            let ty = checked_expr.ty();
            (
                CheckedExpression::OptionalSome(Box::new(checked_expr), *span, ty),
                err,
            )
        }
        Expression::ForcedUnwrap(expr, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);

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
            (
                CheckedExpression::ForcedUnwrap(Box::new(checked_expr), *span, ty),
                err,
            )
        }
        Expression::Boolean(b, span) => (CheckedExpression::Boolean(*b, *span), None),
        Expression::Call(call, span) => {
            let (checked_call, err) = typecheck_call(call, scope_id, span, project, safety_mode);
            let ty = checked_call.ty;
            (CheckedExpression::Call(checked_call, *span, ty), err)
        }
        Expression::NumericConstant(constant, span) => (
            CheckedExpression::NumericConstant(constant.clone(), *span, constant.ty()),
            None,
        ),
        Expression::QuotedString(qs, span) => {
            (CheckedExpression::QuotedString(qs.clone(), *span), None)
        }
        Expression::CharacterLiteral(c, span) => {
            (CheckedExpression::CharacterConstant(*c, *span), None)
        }
        Expression::Var(v, span) => {
            if let Some(var) = project.find_var_in_scope(scope_id, v) {
                (CheckedExpression::Var(var.clone(), *span), None)
            } else {
                (
                    CheckedExpression::Var(
                        CheckedVariable {
                            name: v.clone(),
                            ty: UNKNOWN_TYPE_ID,
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
        Expression::Array(vec, fill_size_expr, span) => {
            let mut inner_ty = UNKNOWN_TYPE_ID;
            let mut output = Vec::new();

            let mut checked_fill_size_expr = None;
            if let Some(fill_size_expr) = fill_size_expr {
                let (checked_expr, err) =
                    typecheck_expression(fill_size_expr, scope_id, project, safety_mode);
                checked_fill_size_expr = Some(Box::new(checked_expr));
                error = error.or(err);
            }

            for v in vec {
                let (checked_expr, err) = typecheck_expression(v, scope_id, project, safety_mode);
                error = error.or(err);

                if inner_ty == UNKNOWN_TYPE_ID {
                    inner_ty = checked_expr.ty();
                } else {
                    if inner_ty != checked_expr.ty() {
                        error = error.or(Some(JaktError::TypecheckError(
                            "does not match type of previous values in vector".to_string(),
                            v.span(),
                        )))
                    }
                }

                output.push(checked_expr);
            }

            let vector_struct_id = project
                .find_struct_in_scope(0, "Array")
                .expect("internal error: Array builtin definition not found");

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(vector_struct_id, vec![inner_ty]));

            (
                CheckedExpression::Array(output, checked_fill_size_expr, *span, type_id),
                error,
            )
        }
        Expression::Tuple(items, span) => {
            let mut checked_items = Vec::new();
            let mut checked_types = Vec::new();

            for item in items {
                let (checked_item, err) =
                    typecheck_expression(item, scope_id, project, safety_mode);
                error = error.or(err);

                checked_types.push(checked_item.ty());
                checked_items.push(checked_item);
            }

            let tuple_struct_id = project
                .find_struct_in_scope(0, "Tuple")
                .expect("internal error: Tuple builtin definition not found");

            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(tuple_struct_id, checked_types));

            (
                CheckedExpression::Tuple(checked_items, *span, type_id),
                error,
            )
        }
        Expression::IndexedExpression(expr, idx, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);
            error = error.or(err);

            let (checked_idx, err) = typecheck_expression(idx, scope_id, project, safety_mode);
            error = error.or(err);

            let mut expr_ty = UNKNOWN_TYPE_ID;

            let vector_struct_id = project
                .find_struct_in_scope(0, "Array")
                .expect("internal error: Array builtin definition not found");

            let ty = &project.types[checked_expr.ty()];
            match ty {
                Type::GenericInstance(parent_struct_id, inner_tys)
                    if parent_struct_id == &vector_struct_id =>
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
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "index used on value that can't be indexed".to_string(),
                        expr.span(),
                    )))
                }
            }

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
        Expression::IndexedTuple(expr, idx, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);
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
                        Some(t) => ty = t.clone(),
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

            (
                CheckedExpression::IndexedTuple(Box::new(checked_expr), *idx, *span, ty),
                error,
            )
        }

        Expression::IndexedStruct(expr, name, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);
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
                                    member.ty.clone(),
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
        Expression::MethodCall(expr, call, span) => {
            let (checked_expr, err) = typecheck_expression(expr, scope_id, project, safety_mode);
            error = error.or(err);

            if checked_expr.ty() == STRING_TYPE_ID {
                // Special-case the built-in so we don't accidentally find the user's definition
                let string_struct = project.find_struct_in_scope(0, "String");

                match string_struct {
                    Some(struct_id) => {
                        let (checked_call, err) = typecheck_method_call(
                            call,
                            scope_id,
                            span,
                            project,
                            &checked_expr,
                            struct_id,
                            safety_mode,
                        );
                        error = error.or(err);

                        let ty = checked_call.ty.clone();
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
                        let (checked_call, err) = typecheck_method_call(
                            call,
                            scope_id,
                            span,
                            project,
                            &checked_expr,
                            struct_id,
                            safety_mode,
                        );
                        error = error.or(err);

                        let ty = checked_call.ty.clone();
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
                        let (checked_call, err) = typecheck_method_call(
                            call,
                            scope_id,
                            span,
                            project,
                            &checked_expr,
                            struct_id,
                            safety_mode,
                        );
                        error = error.or(err);

                        let ty = checked_call.ty.clone();
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
            }
        }

        Expression::Operator(_, span) => (
            CheckedExpression::Garbage(*span),
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
        Expression::Garbage(span) => (
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
        BinaryOperator::LogicalAnd | BinaryOperator::LogicalOr => {
            ty = BOOL_TYPE_ID;
        }
        BinaryOperator::Assign
        | BinaryOperator::AddAssign
        | BinaryOperator::SubtractAssign
        | BinaryOperator::MultiplyAssign
        | BinaryOperator::DivideAssign
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
    call: &Call,
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

            if let Some(function_id) =
                project.find_function_in_scope(structure.scope_id, &call.name)
            {
                callee = Some(&project.funs[function_id]);
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
        if let Some(function_id) = project.find_function_in_scope(scope_id, &call.name) {
            callee = Some(&project.funs[function_id]);
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
    call: &Call,
    scope_id: ScopeId,
    span: &Span,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;
    let mut return_ty = UNKNOWN_TYPE_ID;
    let mut linkage = FunctionLinkage::Internal;
    let mut generic_inferences = HashMap::new();
    let mut type_args = vec![];

    match call.name.as_str() {
        "println" | "eprintln" => {
            // FIXME: This is a hack since println() and eprintln() are hard-coded into codegen at the moment.
            for arg in &call.args {
                let (checked_arg, err) =
                    typecheck_expression(&arg.1, scope_id, project, safety_mode);
                error = error.or(err);

                if checked_arg.ty() == VOID_TYPE_ID {
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
            let (callee, err) = resolve_call(call, span, scope_id, project);
            error = error.or(err);

            if let Some(callee) = callee {
                // Borrow checker workaround, would be nice to clean this up
                let callee = callee.clone();

                return_ty = callee.return_type;

                linkage = callee.linkage;

                // Check that we have the right number of arguments.
                if callee.params.len() != call.args.len() {
                    error = error.or(Some(JaktError::TypecheckError(
                        "wrong number of arguments".to_string(),
                        *span,
                    )));
                } else {
                    let mut idx = 0;

                    while idx < call.args.len() {
                        let (mut checked_arg, err) =
                            typecheck_expression(&call.args[idx].1, scope_id, project, safety_mode);
                        error = error.or(err);

                        // Borrowchecker workaround: since we need project to be mutable above, we
                        // need to let go of the previous callee and then look it up again
                        let (callee, _) = resolve_call(call, span, scope_id, project);
                        let callee = callee
                            .expect("internal error: previously resolved call is now unresolved");

                        if let Expression::Var(var_name, _) = &call.args[idx].1 {
                            if var_name != &callee.params[idx].variable.name
                                && callee.params[idx].requires_label
                                && call.args[idx].0 != callee.params[idx].variable.name
                            {
                                error = error.or(Some(JaktError::TypecheckError(
                                    "Wrong parameter name in argument label".to_string(),
                                    call.args[idx].1.span(),
                                )));
                            }
                        } else if callee.params[idx].requires_label
                            && call.args[idx].0 != callee.params[idx].variable.name
                        {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Wrong parameter name in argument label".to_string(),
                                call.args[idx].1.span(),
                            )));
                        }

                        let lhs_type_id = callee.params[idx].variable.ty;

                        let err =
                            try_promote_constant_expr_to_type(lhs_type_id, &mut checked_arg, &span);
                        error = error.or(err);

                        let rhs_type_id = checked_arg.ty();

                        if let Some(err) = check_types_for_compat(
                            callee.params[idx].variable.ty,
                            rhs_type_id,
                            &mut generic_inferences,
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
                return_ty = substitute_typevars_in_type(return_ty, &generic_inferences, project);

                for generic_typevar in &callee.generic_parameters {
                    if let Some(substitution) = generic_inferences.get(&generic_typevar) {
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

    (
        CheckedCall {
            namespace: call.namespace.clone(),
            name: call.name.clone(),
            args: checked_args,
            type_args,
            linkage,
            ty: return_ty,
        },
        error,
    )
}

pub fn typecheck_method_call(
    call: &Call,
    scope_id: ScopeId,
    span: &Span,
    project: &mut Project,
    this_expr: &CheckedExpression,
    struct_id: StructId,
    safety_mode: SafetyMode,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;
    let mut return_ty = UNKNOWN_TYPE_ID;
    let mut linkage = FunctionLinkage::Internal;
    let mut type_args = vec![];

    let mut generic_inferences = HashMap::new();

    let (callee, err) = resolve_call(call, span, project.structs[struct_id].scope_id, project);
    error = error.or(err);

    if let Some(callee) = callee {
        // Borrow checker workaround, would be nice to clean this up
        let callee = callee.clone();

        return_ty = callee.return_type;
        linkage = callee.linkage;

        // Before we check the method, let's go ahead and make sure we know any instantiated generic types
        // This will make it easier later to know how to create the proper return type
        let type_id = this_expr.ty();
        let param_type = &project.types[type_id];

        match param_type {
            Type::GenericInstance(struct_id, args) => {
                let structure = &project.structs[*struct_id];

                let mut idx = 0;

                while idx < structure.generic_parameters.len() {
                    generic_inferences.insert(structure.generic_parameters[idx], args[idx]);
                    idx += 1;
                }
            }
            _ => {}
        }

        // Check that we have the right number of arguments.
        if callee.params.len() != (call.args.len() + 1) {
            error = error.or(Some(JaktError::TypecheckError(
                "wrong number of arguments".to_string(),
                *span,
            )));
        } else {
            let mut idx = 0;

            while idx < call.args.len() {
                let (mut checked_arg, err) =
                    typecheck_expression(&call.args[idx].1, scope_id, project, safety_mode);
                error = error.or(err);

                // Borrowchecker workaround: since we need project to be mutable above, we
                // need to let go of the previous callee and then look it up again
                let (callee, _) =
                    resolve_call(call, span, project.structs[struct_id].scope_id, project);
                let callee =
                    callee.expect("internal error: previously resolved call is now unresolved");

                if let Expression::Var(var_name, _) = &call.args[idx].1 {
                    if var_name != &callee.params[idx + 1].variable.name
                        && callee.params[idx + 1].requires_label
                        && call.args[idx].0 != callee.params[idx + 1].variable.name
                    {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Wrong parameter name in argument label".to_string(),
                            call.args[idx].1.span(),
                        )));
                    }
                } else if callee.params[idx].requires_label
                    && call.args[idx].0 != callee.params[idx + 1].variable.name
                {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Wrong parameter name in argument label".to_string(),
                        call.args[idx].1.span(),
                    )));
                }

                let lhs_type_id = callee.params[idx + 1].variable.ty;

                let err = try_promote_constant_expr_to_type(lhs_type_id, &mut checked_arg, &span);
                error = error.or(err);

                let rhs_type_id = checked_arg.ty();

                if let Some(err) = check_types_for_compat(
                    lhs_type_id,
                    rhs_type_id,
                    &mut generic_inferences,
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
        return_ty = substitute_typevars_in_type(return_ty, &generic_inferences, project);

        for generic_typevar in &callee.generic_parameters {
            if let Some(substitution) = generic_inferences.get(&generic_typevar) {
                type_args.push(*substitution)
            } else {
                error = error.or(Some(JaktError::TypecheckError(
                    "not all generic parameters have known types".into(),
                    *span,
                )))
            }
        }
    }

    (
        CheckedCall {
            namespace: Vec::new(),
            name: call.name.clone(),
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
                        "Parameter type mismatch".to_string(),
                        span,
                    )))
                }
            } else {
                // We haven't seen this type variable before, so go ahead
                // and give it an actual type during this call
                generic_inferences.insert(lhs_type_id, rhs_type_id);
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

                        let lhs_arg_type_id = lhs_args[idx];
                        let rhs_arg_type_id = rhs_args[idx];

                        while idx < lhs_args.len() {
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
                            "Parameter type mismatch".to_string(),
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
                            "Parameter type mismatch".to_string(),
                            span,
                        )))
                    }
                }
            }
        }
        _ => {
            if rhs_type_id != lhs_type_id {
                error = error.or(Some(JaktError::TypecheckError(
                    "Parameter type mismatch".to_string(),
                    span,
                )))
            }
        }
    }

    error
}
pub fn typecheck_typename(
    unchecked_type: &UncheckedType,
    scope_id: ScopeId,
    project: &mut Project,
) -> (TypeId, Option<JaktError>) {
    let mut error = None;

    match unchecked_type {
        UncheckedType::Name(name, span) => match name.as_str() {
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
        UncheckedType::Empty => (UNKNOWN_TYPE_ID, None),
        UncheckedType::Array(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let vector_struct_id = project
                .find_struct_in_scope(0, "Array")
                .expect("internal error: Array builtin definition not found");

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(vector_struct_id, vec![inner_ty]));

            (type_id, error)
        }
        UncheckedType::Optional(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let optional_struct_id = project
                .find_struct_in_scope(0, "Optional")
                .expect("internal error: Optional builtin definition not found");

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(optional_struct_id, vec![inner_ty]));

            (type_id, error)
        }
        UncheckedType::RawPtr(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let type_id = project.find_or_add_type_id(Type::RawPtr(inner_ty));

            (type_id, error)
        }
        UncheckedType::GenericType(name, inner_types, span) => {
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
