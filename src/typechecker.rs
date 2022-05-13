use crate::{
    error::JaktError,
    lexer::Span,
    parser::{
        BinaryOperator, Block, Call, DefinitionLinkage, DefinitionType, Expression, Function,
        FunctionLinkage, ParsedFile, Statement, Struct, UnaryOperator, UncheckedType,
    },
};

pub type StructId = usize;
pub type FunctionId = usize;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum SafetyMode {
    Safe,
    Unsafe,
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
    Vector(Box<Type>),
    Tuple(Vec<Type>),
    Optional(Box<Type>),
    Struct(StructId),
    RawPtr(Box<Type>),
    Unknown,

    // C interop types
    CChar,
    CInt,
}

impl Type {
    pub fn is_integer(&self) -> bool {
        match self {
            Type::I8
            | Type::I16
            | Type::I32
            | Type::I64
            | Type::U8
            | Type::U16
            | Type::U32
            | Type::U64 => true,
            _ => false,
        }
    }

    pub fn can_fit_integer(&self, value: &IntegerConstant) -> bool {
        match *value {
            IntegerConstant::Signed(value) => match self {
                Type::I8 => value >= i8::MIN as i64 && value <= i8::MAX as i64,
                Type::I16 => value >= i16::MIN as i64 && value <= i16::MAX as i64,
                Type::I32 => value >= i32::MIN as i64 && value <= i32::MAX as i64,
                Type::I64 => true,
                Type::U8 => value >= 0 && value <= u8::MAX as i64,
                Type::U16 => value >= 0 && value <= u16::MAX as i64,
                Type::U32 => value >= 0 && value <= u32::MAX as i64,
                Type::U64 => value >= 0,
                _ => false,
            },
            IntegerConstant::Unsigned(value) => match self {
                Type::I8 => value <= i8::MAX as u64,
                Type::I16 => value <= i16::MAX as u64,
                Type::I32 => value <= i32::MAX as u64,
                Type::I64 => value <= i64::MAX as u64,
                Type::U8 => value <= u8::MAX as u64,
                Type::U16 => value <= u16::MAX as u64,
                Type::U32 => value <= u32::MAX as u64,
                Type::U64 => true,
                _ => false,
            },
        }
    }
}

#[derive(Debug, Clone)]
pub struct Project {
    pub funs: Vec<CheckedFunction>,
    pub structs: Vec<CheckedStruct>,
}

impl Project {
    pub fn new() -> Self {
        Self {
            funs: Vec::new(),
            structs: Vec::new(),
        }
    }

    pub fn get_struct_mut(&mut self, name: &str) -> Option<(&mut CheckedStruct, usize)> {
        for (idx, structure) in self.structs.iter_mut().enumerate() {
            if structure.name == name {
                return Some((structure, idx));
            }
        }
        None
    }

    pub fn get_fun_mut(&mut self, name: &str) -> Option<&mut CheckedFunction> {
        for fun in self.funs.iter_mut() {
            if fun.name == name {
                return Some(fun);
            }
        }
        None
    }
}

#[derive(Clone, Debug)]
pub struct CheckedStruct {
    pub name: String,
    pub fields: Vec<CheckedVarDecl>,
    pub methods: Vec<CheckedFunction>,
    pub definition_linkage: DefinitionLinkage,
    pub definition_type: DefinitionType,
}

impl CheckedStruct {
    pub fn get_method_mut(&mut self, name: &str) -> Option<&mut CheckedFunction> {
        for fun in self.methods.iter_mut() {
            if fun.name == name {
                return Some(fun);
            }
        }
        None
    }
}

#[derive(Clone, Debug)]
pub struct CheckedParameter {
    pub requires_label: bool,
    pub variable: CheckedVariable,
}

#[derive(Debug, Clone)]
pub struct CheckedFunction {
    pub name: String,
    pub return_type: Type,
    pub params: Vec<CheckedParameter>,
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
    pub ty: Type,
    pub mutable: bool,
    pub span: Span,
}

#[derive(Clone, Debug)]
pub struct CheckedVariable {
    pub name: String,
    pub ty: Type,
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
    Garbage,
}

#[derive(Clone, Debug)]
pub enum IntegerConstant {
    Signed(i64),
    Unsigned(u64),
}

impl IntegerConstant {
    pub fn promote(&self, ty: &Type) -> (Option<NumericConstant>, Type) {
        if !ty.can_fit_integer(self) {
            return (None, Type::Unknown);
        }
        let new_constant = match self {
            IntegerConstant::Signed(value) => match ty {
                Type::I8 => NumericConstant::I8(*value as i8),
                Type::I16 => NumericConstant::I16(*value as i16),
                Type::I32 => NumericConstant::I32(*value as i32),
                Type::I64 => NumericConstant::I64(*value as i64),
                Type::U8 => NumericConstant::U8(*value as u8),
                Type::U16 => NumericConstant::U16(*value as u16),
                Type::U32 => NumericConstant::U32(*value as u32),
                Type::U64 => NumericConstant::U64(*value as u64),
                _ => panic!("Bogus state in IntegerConstant::promote"),
            },
            IntegerConstant::Unsigned(value) => match ty {
                Type::I8 => NumericConstant::I8(*value as i8),
                Type::I16 => NumericConstant::I16(*value as i16),
                Type::I32 => NumericConstant::I32(*value as i32),
                Type::I64 => NumericConstant::I64(*value as i64),
                Type::U8 => NumericConstant::U8(*value as u8),
                Type::U16 => NumericConstant::U16(*value as u16),
                Type::U32 => NumericConstant::U32(*value as u32),
                Type::U64 => NumericConstant::U64(*value as u64),
                _ => panic!("Bogus state in IntegerConstant::promote"),
            },
        };
        (Some(new_constant), ty.clone())
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
        }
    }

    pub fn ty(&self) -> Type {
        match self {
            NumericConstant::I8(_) => Type::I8,
            NumericConstant::I16(_) => Type::I16,
            NumericConstant::I32(_) => Type::I32,
            NumericConstant::I64(_) => Type::I64,
            NumericConstant::U8(_) => Type::U8,
            NumericConstant::U16(_) => Type::U16,
            NumericConstant::U32(_) => Type::U32,
            NumericConstant::U64(_) => Type::U64,
        }
    }
}

#[derive(Clone, Debug)]
pub enum CheckedExpression {
    // Standalone
    Boolean(bool),
    NumericConstant(NumericConstant, Type),
    QuotedString(String),
    CharacterConstant(char),
    UnaryOp(Box<CheckedExpression>, UnaryOperator, Type),
    BinaryOp(
        Box<CheckedExpression>,
        BinaryOperator,
        Box<CheckedExpression>,
        Type,
    ),
    Tuple(Vec<CheckedExpression>, Type),
    Vector(Vec<CheckedExpression>, Type),
    IndexedExpression(Box<CheckedExpression>, Box<CheckedExpression>, Type),
    IndexedTuple(Box<CheckedExpression>, usize, Type),
    IndexedStruct(Box<CheckedExpression>, String, Type),

    Call(CheckedCall, Type),
    MethodCall(Box<CheckedExpression>, CheckedCall, Type),

    Var(CheckedVariable),

    OptionalNone(Type),
    OptionalSome(Box<CheckedExpression>, Type),
    ForcedUnwrap(Box<CheckedExpression>, Type),

    // Parsing error
    Garbage,
}

impl CheckedExpression {
    pub fn ty(&self) -> Type {
        match self {
            CheckedExpression::Boolean(_) => Type::Bool,
            CheckedExpression::Call(_, ty) => ty.clone(),
            CheckedExpression::NumericConstant(_, ty) => ty.clone(),
            CheckedExpression::QuotedString(_) => Type::String,
            CheckedExpression::CharacterConstant(_) => Type::CChar, // use the C one for now
            CheckedExpression::UnaryOp(_, _, ty) => ty.clone(),
            CheckedExpression::BinaryOp(_, _, _, ty) => ty.clone(),
            CheckedExpression::Vector(_, ty) => ty.clone(),
            CheckedExpression::Tuple(_, ty) => ty.clone(),
            CheckedExpression::IndexedExpression(_, _, ty) => ty.clone(),
            CheckedExpression::IndexedTuple(_, _, ty) => ty.clone(),
            CheckedExpression::IndexedStruct(_, _, ty) => ty.clone(),
            CheckedExpression::MethodCall(_, _, ty) => ty.clone(),
            CheckedExpression::Var(CheckedVariable { ty, .. }) => ty.clone(),
            CheckedExpression::OptionalNone(ty) => ty.clone(),
            CheckedExpression::OptionalSome(_, ty) => ty.clone(),
            CheckedExpression::ForcedUnwrap(_, ty) => ty.clone(),
            CheckedExpression::Garbage => Type::Unknown,
        }
    }

    pub fn to_integer_constant(&self) -> Option<IntegerConstant> {
        match self {
            CheckedExpression::NumericConstant(constant, _) => constant.integer_constant(),
            _ => None,
        }
    }

    pub fn is_mutable(&self) -> bool {
        match self {
            CheckedExpression::Var(var) => var.mutable,
            CheckedExpression::IndexedStruct(expr, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedExpression(expr, _, _) => expr.is_mutable(),
            _ => false,
        }
    }
}

#[derive(Clone, Debug)]
pub struct CheckedCall {
    pub namespace: Vec<String>,
    pub name: String,
    pub args: Vec<(String, CheckedExpression)>,
    pub ty: Type,
}

#[derive(Clone, Debug)]
pub struct ScopeStack {
    pub frames: Vec<Scope>,
}

impl ScopeStack {
    pub fn new() -> Self {
        Self {
            frames: vec![Scope::new()],
        }
    }
    pub fn push_frame(&mut self) {
        self.frames.push(Scope::new())
    }

    pub fn pop_frame(&mut self) {
        self.frames.pop();
    }

    pub fn add_var(&mut self, var: CheckedVariable, span: Span) -> Result<(), JaktError> {
        if let Some(frame) = self.frames.last_mut() {
            for existing_var in &frame.vars {
                if var.name == existing_var.name {
                    return Err(JaktError::TypecheckError(
                        format!("redefinition of {}", var.name),
                        span,
                    ));
                }
            }
            frame.vars.push(var);
        }
        Ok(())
    }

    pub fn find_var(&self, var: &str) -> Option<CheckedVariable> {
        for frame in self.frames.iter().rev() {
            for v in &frame.vars {
                if v.name == var {
                    return Some(v.clone());
                }
            }
        }

        None
    }

    pub fn add_struct(
        &mut self,
        name: String,
        struct_id: StructId,
        span: Span,
    ) -> Result<(), JaktError> {
        if let Some(scope) = self.frames.last_mut() {
            for (existing_struct, _) in &scope.structs {
                if &name == existing_struct {
                    return Err(JaktError::TypecheckError(
                        format!("redefinition of {}", name),
                        span,
                    ));
                }
            }
            scope.structs.push((name, struct_id));
        }
        Ok(())
    }

    pub fn find_struct(&self, structure: &str) -> Option<StructId> {
        for frame in self.frames.iter().rev() {
            for s in &frame.structs {
                if s.0 == structure {
                    return Some(s.1);
                }
            }
        }

        None
    }

    pub fn add_function(
        &mut self,
        name: String,
        function_id: FunctionId,
        span: Span,
    ) -> Result<(), JaktError> {
        if let Some(scope) = self.frames.last_mut() {
            for (existing_fun, _) in &scope.funs {
                if &name == existing_fun {
                    return Err(JaktError::TypecheckError(
                        format!("redefinition of {}", name),
                        span,
                    ));
                }
            }
            scope.funs.push((name, function_id));
        }
        Ok(())
    }

    pub fn find_function(&self, fun_name: &str) -> Option<FunctionId> {
        for frame in self.frames.iter().rev() {
            for s in &frame.funs {
                if s.0 == fun_name {
                    return Some(s.1);
                }
            }
        }

        None
    }
}

#[derive(Clone, Debug)]
pub struct Scope {
    vars: Vec<CheckedVariable>,

    structs: Vec<(String, StructId)>,
    funs: Vec<(String, FunctionId)>,
}

impl Scope {
    pub fn new() -> Self {
        Self {
            vars: Vec::new(),
            structs: Vec::new(),
            funs: Vec::new(),
        }
    }
}

pub fn typecheck_file(file: &ParsedFile, prelude: &Project) -> (Project, Option<JaktError>) {
    let mut stack = ScopeStack::new();

    typecheck_file_helper(file, &mut stack, prelude)
}

fn typecheck_file_helper(
    parsed_file: &ParsedFile,
    stack: &mut ScopeStack,
    prelude: &Project,
) -> (Project, Option<JaktError>) {
    let mut file = Project::new();
    let mut error = None;

    for structure in &prelude.structs {
        file.structs.push(structure.clone());
        let _ = stack.add_struct(
            structure.name.clone(),
            file.structs.len() - 1,
            Span::new(0, 0, 0),
        );
    }

    for fun in &prelude.funs {
        file.funs.push(fun.clone());
        if let Err(err) =
            stack.add_function(fun.name.clone(), file.funs.len() - 1, Span::new(0, 0, 0))
        {
            error = error.or(Some(err));
        }
    }

    for (struct_id, structure) in parsed_file.structs.iter().enumerate() {
        //Ensure we know the types ahead of time, so they can be recursive
        typecheck_struct_predecl(
            structure,
            struct_id + prelude.structs.len(),
            stack,
            &mut file,
        );
    }

    for fun in &parsed_file.funs {
        //Ensure we know the function ahead of time, so they can be recursive
        error = error.or(typecheck_fun_predecl(fun, stack, &mut file));
    }

    for (struct_id, structure) in parsed_file.structs.iter().enumerate() {
        error = error.or(typecheck_struct(
            structure,
            struct_id + prelude.structs.len(),
            stack,
            &mut file,
        ));
    }

    for fun in &parsed_file.funs {
        error = error.or(typecheck_fun(fun, stack, &mut file));
    }

    (file, error)
}

fn typecheck_struct_predecl(
    structure: &Struct,
    struct_id: StructId,
    stack: &mut ScopeStack,
    file: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let mut methods = Vec::new();

    for fun in &structure.methods {
        let mut checked_function = CheckedFunction {
            name: fun.name.clone(),
            params: vec![],
            return_type: Type::Unknown,
            block: CheckedBlock::new(),
            linkage: fun.linkage.clone(),
        };

        for param in &fun.params {
            if param.variable.name == "this" {
                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    ty: Type::Struct(struct_id),
                    mutable: param.variable.mutable,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });
            } else {
                let (param_type, err) = typecheck_typename(&param.variable.ty, stack);
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

        methods.push(checked_function);
    }

    file.structs.push(CheckedStruct {
        name: structure.name.clone(),
        fields: Vec::new(),
        methods,
        definition_linkage: structure.definition_linkage,
        definition_type: structure.definition_type,
    });

    match stack.add_struct(structure.name.clone(), struct_id, structure.span) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_struct(
    structure: &Struct,
    struct_id: StructId,
    stack: &mut ScopeStack,
    file: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let mut fields = Vec::new();

    for unchecked_member in &structure.fields {
        let (checked_member_type, err) = typecheck_typename(&unchecked_member.ty, stack);
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
                ty: field.ty.clone(),
                mutable: field.mutable,
            },
        });
    }

    let checked_struct = &mut file.structs[struct_id];
    checked_struct.fields = fields;

    let checked_constructor = {
        let (checked_struct, struct_id) = file
            .get_struct_mut(&structure.name)
            .expect("Internal error: we previously defined the struct but it's now missing");

        let checked_constructor = CheckedFunction {
            name: structure.name.clone(),
            block: CheckedBlock::new(),
            linkage: FunctionLinkage::ImplicitConstructor,
            params: constructor_params,
            return_type: Type::Struct(struct_id),
        };
        checked_struct.methods.push(checked_constructor.clone());
        checked_constructor
    };

    file.funs.push(checked_constructor);

    for fun in &structure.methods {
        error = error.or(typecheck_method(fun, stack, file, struct_id));
    }

    error
}

fn typecheck_fun_predecl(
    fun: &Function,
    stack: &mut ScopeStack,
    file: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let mut checked_function = CheckedFunction {
        name: fun.name.clone(),
        params: vec![],
        return_type: Type::Unknown,
        block: CheckedBlock::new(),
        linkage: fun.linkage.clone(),
    };

    for param in &fun.params {
        let (param_type, err) = typecheck_typename(&param.variable.ty, stack);
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

    let function_id = file.funs.len();

    file.funs.push(checked_function);

    match stack.add_function(fun.name.clone(), function_id, fun.name_span) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_fun(fun: &Function, stack: &mut ScopeStack, file: &mut Project) -> Option<JaktError> {
    let mut error = None;

    stack.push_frame();

    let checked_function = file
        .get_fun_mut(&fun.name)
        .expect("Internal error: we just pushed the checked function, but it's not present");

    for param in &checked_function.params {
        if let Err(err) = stack.add_var(param.variable.clone(), fun.name_span) {
            error = error.or(Some(err));
        }
    }

    let (block, err) = typecheck_block(&fun.block, stack, file, SafetyMode::Safe);
    error = error.or(err);

    stack.pop_frame();

    let (fun_return_type, err) = typecheck_typename(&fun.return_type, stack);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type = if fun_return_type == Type::Unknown {
        if let Some(CheckedStatement::Return(ret)) = block.stmts.first() {
            ret.ty()
        } else {
            Type::Void
        }
    } else {
        fun_return_type.clone()
    };

    let checked_function = file
        .get_fun_mut(&fun.name)
        .expect("Internal error: we just pushed the checked function, but it's not present");

    checked_function.block = block;
    checked_function.return_type = return_type;

    error
}

fn typecheck_method(
    fun: &Function,
    stack: &mut ScopeStack,
    file: &mut Project,
    struct_id: StructId,
) -> Option<JaktError> {
    let mut error = None;

    stack.push_frame();

    let structure = &mut file.structs[struct_id];
    let checked_function = structure
        .get_method_mut(&fun.name)
        .expect("Internal error: we just pushed the checked function, but it's not present");

    for param in &checked_function.params {
        if let Err(err) = stack.add_var(param.variable.clone(), fun.name_span) {
            error = error.or(Some(err));
        }
    }

    let (block, err) = typecheck_block(&fun.block, stack, file, SafetyMode::Safe);
    error = error.or(err);

    stack.pop_frame();

    let (fun_return_type, err) = typecheck_typename(&fun.return_type, stack);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type = if fun_return_type == Type::Unknown {
        if let Some(CheckedStatement::Return(ret)) = block.stmts.first() {
            ret.ty()
        } else {
            Type::Void
        }
    } else {
        fun_return_type.clone()
    };

    let structure = &mut file.structs[struct_id];
    let checked_function = structure
        .get_method_mut(&fun.name)
        .expect("Internal error: we just pushed the checked function, but it's not present");

    checked_function.block = block;
    checked_function.return_type = return_type;

    error
}

pub fn typecheck_block(
    block: &Block,
    stack: &mut ScopeStack,
    file: &Project,
    safety_mode: SafetyMode,
) -> (CheckedBlock, Option<JaktError>) {
    let mut error = None;
    let mut checked_block = CheckedBlock::new();

    stack.push_frame();

    for stmt in &block.stmts {
        let (checked_stmt, err) = typecheck_statement(stmt, stack, file, safety_mode);
        error = error.or(err);

        checked_block.stmts.push(checked_stmt);
    }

    stack.pop_frame();

    (checked_block, error)
}

pub fn typecheck_statement(
    stmt: &Statement,
    stack: &mut ScopeStack,
    project: &Project,
    safety_mode: SafetyMode,
) -> (CheckedStatement, Option<JaktError>) {
    let mut error = None;

    match stmt {
        Statement::Expression(expr) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);

            (CheckedStatement::Expression(checked_expr), err)
        }
        Statement::Defer(statement) => {
            let (checked_statement, err) =
                typecheck_statement(statement, stack, project, safety_mode);

            (CheckedStatement::Defer(Box::new(checked_statement)), err)
        }
        Statement::UnsafeBlock(block) => {
            let (checked_block, err) = typecheck_block(block, stack, project, SafetyMode::Unsafe);

            (CheckedStatement::Block(checked_block), err)
        }
        Statement::VarDecl(var_decl, init) => {
            let (mut checked_expression, err) =
                typecheck_expression(init, stack, project, safety_mode);
            error = error.or(err);

            let (mut checked_type, err) = typecheck_typename(&var_decl.ty, stack);

            if checked_type == Type::Unknown && checked_expression.ty() != Type::Unknown {
                checked_type = checked_expression.ty()
            } else {
                error = error.or(err);
            }

            let err = try_promote_constant_expr_to_type(
                &checked_type,
                &mut checked_expression,
                &init.span(),
            );
            error = error.or(err);

            let checked_var_decl = CheckedVarDecl {
                name: var_decl.name.clone(),
                ty: checked_type.clone(),
                span: var_decl.span,
                mutable: var_decl.mutable,
            };

            // Taking this out for now until we have better number type support
            // } else if var_decl.ty != checked_expression.ty() {
            //     error = error.or(Some(JaktError::TypecheckError(
            //         "mismatch between declaration and initializer".to_string(),
            //         init.span(),
            //     )));
            // }

            if let Err(err) = stack.add_var(
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
            let (checked_cond, err) = typecheck_expression(cond, stack, project, safety_mode);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, stack, project, safety_mode);
            error = error.or(err);

            let else_output;
            if let Some(else_stmt) = else_stmt {
                let (checked_stmt, err) =
                    typecheck_statement(else_stmt, stack, project, safety_mode);
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
            let (checked_cond, err) = typecheck_expression(cond, stack, project, safety_mode);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, stack, project, safety_mode);
            error = error.or(err);

            (CheckedStatement::While(checked_cond, checked_block), error)
        }
        Statement::Return(expr) => {
            let (output, err) = typecheck_expression(expr, stack, project, safety_mode);

            (CheckedStatement::Return(output), err)
        }
        Statement::Block(block) => {
            let (checked_block, err) = typecheck_block(block, stack, project, safety_mode);
            (CheckedStatement::Block(checked_block), err)
        }
        Statement::Garbage => (CheckedStatement::Garbage, None),
    }
}

pub fn try_promote_constant_expr_to_type(
    lhs_type: &Type,
    checked_rhs: &mut CheckedExpression,
    span: &Span,
) -> Option<JaktError> {
    if !lhs_type.is_integer() {
        return None;
    }
    if let Some(rhs_constant) = checked_rhs.to_integer_constant() {
        if let (Some(new_constant), new_ty) = rhs_constant.promote(lhs_type) {
            *checked_rhs = CheckedExpression::NumericConstant(new_constant, new_ty);
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
    stack: &mut ScopeStack,
    project: &Project,
    safety_mode: SafetyMode,
) -> (CheckedExpression, Option<JaktError>) {
    let mut error = None;

    match expr {
        Expression::BinaryOp(lhs, op, rhs, span) => {
            let (checked_lhs, err) = typecheck_expression(lhs, stack, project, safety_mode);
            error = error.or(err);

            let (mut checked_rhs, err) = typecheck_expression(rhs, stack, project, safety_mode);
            error = error.or(err);

            let err = try_promote_constant_expr_to_type(&checked_lhs.ty(), &mut checked_rhs, span);
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
                    ty,
                ),
                error,
            )
        }
        Expression::UnaryOp(expr, op, span) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);
            error = error.or(err);

            let (checked_expr, err) =
                typecheck_unary_operation(checked_expr, op.clone(), *span, stack, safety_mode);
            error = error.or(err);

            (checked_expr, error)
        }
        Expression::OptionalNone(_) => (CheckedExpression::OptionalNone(Type::Unknown), None),
        Expression::OptionalSome(expr, _) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);
            let ty = checked_expr.ty();
            (
                CheckedExpression::OptionalSome(Box::new(checked_expr), ty),
                err,
            )
        }
        Expression::ForcedUnwrap(expr, _) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);

            let (ty, err) = if let Type::Optional(inner_type) = checked_expr.ty() {
                (*inner_type, err)
            } else {
                (
                    Type::Unknown,
                    err.or(Some(JaktError::TypecheckError(
                        "Forced unwrap only works on Optional".to_string(),
                        expr.span(),
                    ))),
                )
            };
            (
                CheckedExpression::ForcedUnwrap(Box::new(checked_expr), ty),
                err,
            )
        }
        Expression::Boolean(b, _) => (CheckedExpression::Boolean(*b), None),
        Expression::Call(call, span) => {
            let (checked_call, err) = typecheck_call(call, stack, span, project, safety_mode);
            let ty = checked_call.ty.clone();
            (CheckedExpression::Call(checked_call, ty), err)
        }
        Expression::NumericConstant(constant, _) => (
            CheckedExpression::NumericConstant(constant.clone(), constant.ty()),
            None,
        ),
        Expression::QuotedString(qs, _) => (CheckedExpression::QuotedString(qs.clone()), None),
        Expression::CharacterLiteral(c, _) => (CheckedExpression::CharacterConstant(*c), None),
        Expression::Var(v, span) => {
            if let Some(var) = stack.find_var(v) {
                (CheckedExpression::Var(var.clone()), None)
            } else {
                (
                    CheckedExpression::Var(CheckedVariable {
                        name: v.clone(),
                        ty: Type::Unknown,
                        mutable: false,
                    }),
                    Some(JaktError::TypecheckError(
                        "variable not found".to_string(),
                        *span,
                    )),
                )
            }
        }
        Expression::Vector(vec, _) => {
            let mut inner_ty = Type::Unknown;
            let mut output = Vec::new();

            for v in vec {
                let (checked_expr, err) = typecheck_expression(v, stack, project, safety_mode);
                error = error.or(err);

                if inner_ty == Type::Unknown {
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

            (
                CheckedExpression::Vector(output, Type::Vector(Box::new(inner_ty))),
                error,
            )
        }
        Expression::Tuple(items, _) => {
            let mut checked_items = Vec::new();
            let mut checked_types = Vec::new();

            for item in items {
                let (checked_item, err) = typecheck_expression(item, stack, project, safety_mode);
                error = error.or(err);

                checked_types.push(checked_item.ty());
                checked_items.push(checked_item);
            }

            (
                CheckedExpression::Tuple(checked_items, Type::Tuple(checked_types)),
                error,
            )
        }
        Expression::IndexedExpression(expr, idx, _) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);
            error = error.or(err);

            let (checked_idx, err) = typecheck_expression(idx, stack, project, safety_mode);
            error = error.or(err);

            let mut ty = Type::Unknown;

            match checked_expr.ty() {
                Type::Vector(inner_ty) => match checked_idx.ty() {
                    _ if checked_idx.ty().is_integer() => {
                        ty = *inner_ty.clone();
                    }
                    _ => {
                        error = error.or(Some(JaktError::TypecheckError(
                            "index is not an integer".to_string(),
                            idx.span(),
                        )))
                    }
                },
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
                    ty,
                ),
                error,
            )
        }
        Expression::IndexedTuple(expr, idx, span) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);
            error = error.or(err);

            let mut ty = Type::Unknown;

            match checked_expr.ty() {
                Type::Tuple(inner_ty) => match inner_ty.get(*idx) {
                    Some(t) => ty = t.clone(),
                    None => {
                        error = error.or(Some(JaktError::TypecheckError(
                            "tuple index past the end of the tuple".to_string(),
                            *span,
                        )))
                    }
                },
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "tuple index used non-tuple value".to_string(),
                        expr.span(),
                    )))
                }
            }

            (
                CheckedExpression::IndexedTuple(Box::new(checked_expr), *idx, ty),
                error,
            )
        }

        Expression::IndexedStruct(expr, name, span) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);
            error = error.or(err);

            let ty = Type::Unknown;

            match checked_expr.ty() {
                Type::Struct(struct_id) => {
                    let structure = &project.structs[struct_id];

                    for member in &structure.fields {
                        if &member.name == name {
                            return (
                                CheckedExpression::IndexedStruct(
                                    Box::new(checked_expr),
                                    name.to_string(),
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
                CheckedExpression::IndexedStruct(Box::new(checked_expr), name.to_string(), ty),
                error,
            )
        }
        Expression::MethodCall(expr, call, span) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, project, safety_mode);
            error = error.or(err);

            match checked_expr.ty() {
                Type::Struct(struct_id) => {
                    let (checked_call, err) =
                        typecheck_method_call(call, stack, span, project, struct_id, safety_mode);
                    error = error.or(err);

                    let ty = checked_call.ty.clone();
                    (
                        CheckedExpression::MethodCall(Box::new(checked_expr), checked_call, ty),
                        error,
                    )
                }
                Type::String => {
                    let string_struct = stack.find_struct("String");

                    match string_struct {
                        Some(struct_id) => {
                            let (checked_call, err) = typecheck_method_call(
                                call,
                                stack,
                                span,
                                project,
                                struct_id,
                                safety_mode,
                            );
                            error = error.or(err);

                            let ty = checked_call.ty.clone();
                            (
                                CheckedExpression::MethodCall(
                                    Box::new(checked_expr),
                                    checked_call,
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

                            (CheckedExpression::Garbage, error)
                        }
                    }
                }
                Type::Vector(_) => {
                    let string_struct = stack.find_struct("RefVector");

                    match string_struct {
                        Some(struct_id) => {
                            let (checked_call, err) = typecheck_method_call(
                                call,
                                stack,
                                span,
                                project,
                                struct_id,
                                safety_mode,
                            );
                            error = error.or(err);

                            let ty = checked_call.ty.clone();
                            (
                                CheckedExpression::MethodCall(
                                    Box::new(checked_expr),
                                    checked_call,
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

                            (CheckedExpression::Garbage, error)
                        }
                    }
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "no methods available on value".to_string(),
                        expr.span(),
                    )));

                    (CheckedExpression::Garbage, error)
                }
            }
        }

        Expression::Operator(_, span) => (
            CheckedExpression::Garbage,
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
        Expression::Garbage(span) => (
            CheckedExpression::Garbage,
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
    }
}

pub fn typecheck_unary_operation(
    expr: CheckedExpression,
    op: UnaryOperator,
    span: Span,
    stack: &ScopeStack,
    safety_mode: SafetyMode,
) -> (CheckedExpression, Option<JaktError>) {
    let expr_ty = expr.ty();

    match &op {
        UnaryOperator::TypeCast(cast) => {
            let unchecked_type = cast.unchecked_type();
            let (ty, err) = typecheck_typename(&unchecked_type, stack);
            (CheckedExpression::UnaryOp(Box::new(expr), op, ty), err)
        }
        UnaryOperator::Dereference => match expr.ty() {
            Type::RawPtr(x) => {
                if safety_mode == SafetyMode::Unsafe {
                    (CheckedExpression::UnaryOp(Box::new(expr), op, *x), None)
                } else {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, *x),
                        Some(JaktError::TypecheckError(
                            "dereference of raw pointer outside of unsafe block".to_string(),
                            span,
                        )),
                    )
                }
            }
            _ => (
                CheckedExpression::UnaryOp(Box::new(expr), op, Type::Unknown),
                Some(JaktError::TypecheckError(
                    "dereference of a non-pointer value".to_string(),
                    span,
                )),
            ),
        },
        UnaryOperator::RawAddress => {
            let ty = expr.ty();

            (
                CheckedExpression::UnaryOp(Box::new(expr), op, Type::RawPtr(Box::new(ty))),
                None,
            )
        }
        UnaryOperator::LogicalNot => {
            let ty = expr.ty();
            (
                CheckedExpression::UnaryOp(Box::new(expr), UnaryOperator::LogicalNot, ty),
                None,
            )
        }
        UnaryOperator::BitwiseNot => {
            let ty = expr.ty();
            (
                CheckedExpression::UnaryOp(Box::new(expr), UnaryOperator::BitwiseNot, ty),
                None,
            )
        }
        UnaryOperator::Negate => {
            let ty = expr.ty();

            match &ty {
                Type::I8
                | Type::I16
                | Type::I32
                | Type::I64
                | Type::U8
                | Type::U16
                | Type::U32
                | Type::U64
                | Type::F32
                | Type::F64 => (
                    CheckedExpression::UnaryOp(Box::new(expr), UnaryOperator::Negate, ty),
                    None,
                ),
                _ => (
                    CheckedExpression::UnaryOp(Box::new(expr), UnaryOperator::Negate, ty),
                    Some(JaktError::TypecheckError(
                        "negate on non-numeric value".to_string(),
                        span,
                    )),
                ),
            }
        }
        UnaryOperator::PostDecrement
        | UnaryOperator::PostIncrement
        | UnaryOperator::PreDecrement
        | UnaryOperator::PreIncrement => match expr.ty() {
            Type::I8
            | Type::I16
            | Type::I32
            | Type::I64
            | Type::U8
            | Type::U16
            | Type::U32
            | Type::U64
            | Type::F32
            | Type::F64 => {
                if !expr.is_mutable() {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, expr_ty),
                        Some(JaktError::TypecheckError(
                            "increment/decrement of immutable variable".to_string(),
                            span,
                        )),
                    )
                } else {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, expr_ty),
                        None,
                    )
                }
            }
            _ => (
                CheckedExpression::UnaryOp(Box::new(expr), op, expr_ty),
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
) -> (Type, Option<JaktError>) {
    let mut ty = lhs.ty();
    match op {
        BinaryOperator::LogicalAnd | BinaryOperator::LogicalOr => {
            ty = Type::Bool;
        }
        BinaryOperator::Assign
        | BinaryOperator::AddAssign
        | BinaryOperator::SubtractAssign
        | BinaryOperator::MultiplyAssign
        | BinaryOperator::DivideAssign => {
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
    functions: &'a [CheckedFunction],
    stack: &ScopeStack,
    file: &'a Project,
) -> (Option<&'a CheckedFunction>, Option<JaktError>) {
    let mut callee = None;
    let mut error = None;

    if let Some(namespace) = call.namespace.first() {
        // For now, assume class is our namespace
        // In the future, we'll have real namespaces

        if let Some(struct_id) = stack.find_struct(namespace) {
            let structure = &file.structs[struct_id];

            for fun in &structure.methods {
                if fun.name == call.name {
                    callee = Some(fun);
                    break;
                }
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
        for fun in functions {
            if fun.name == call.name {
                callee = Some(fun);
                break;
            }
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
    stack: &mut ScopeStack,
    span: &Span,
    project: &Project,
    safety_mode: SafetyMode,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;
    let mut return_ty = Type::Unknown;

    match call.name.as_str() {
        "println" | "eprintln" => {
            // FIXME: This is a hack since println() and eprintln() are hard-coded into codegen at the moment.
            for arg in &call.args {
                let (checked_arg, err) = typecheck_expression(&arg.1, stack, project, safety_mode);
                error = error.or(err);

                return_ty = Type::Void;

                checked_args.push((arg.0.clone(), checked_arg));
            }
        }
        _ => {
            let (callee, err) = resolve_call(call, span, &project.funs, stack, &project);
            error = error.or(err);

            if let Some(callee) = callee {
                return_ty = callee.return_type.clone();

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
                            typecheck_expression(&call.args[idx].1, stack, project, safety_mode);
                        error = error.or(err);

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

                        let err = try_promote_constant_expr_to_type(
                            &callee.params[idx].variable.ty,
                            &mut checked_arg,
                            &call.args[idx].1.span(),
                        );
                        error = error.or(err);

                        if checked_arg.ty() != callee.params[idx].variable.ty {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Parameter type mismatch".to_string(),
                                call.args[idx].1.span(),
                            )))
                        }

                        checked_args.push((call.args[idx].0.clone(), checked_arg));

                        idx += 1;
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
            ty: return_ty,
        },
        error,
    )
}

pub fn typecheck_method_call(
    call: &Call,
    stack: &mut ScopeStack,
    span: &Span,
    file: &Project,
    struct_id: StructId,
    safety_mode: SafetyMode,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;
    let mut return_ty = Type::Unknown;

    let (callee, err) = resolve_call(call, span, &file.structs[struct_id].methods, stack, &file);
    error = error.or(err);

    if let Some(callee) = callee {
        return_ty = callee.return_type.clone();

        // Check that we have the right number of arguments.
        if callee.params.len() != (call.args.len() + 1) {
            error = error.or(Some(JaktError::TypecheckError(
                "wrong number of arguments".to_string(),
                *span,
            )));
        } else {
            let mut idx = 0;

            // The first index should be the 'this'

            while idx < call.args.len() {
                let (mut checked_arg, err) =
                    typecheck_expression(&call.args[idx].1, stack, file, safety_mode);
                error = error.or(err);

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

                let err = try_promote_constant_expr_to_type(
                    &callee.params[idx + 1].variable.ty,
                    &mut checked_arg,
                    &call.args[idx].1.span(),
                );
                error = error.or(err);

                if checked_arg.ty() != callee.params[idx + 1].variable.ty {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Parameter type mismatch".to_string(),
                        call.args[idx].1.span(),
                    )))
                }

                checked_args.push((call.args[idx].0.clone(), checked_arg));

                idx += 1;
            }
        }
    }

    (
        CheckedCall {
            namespace: Vec::new(),
            name: call.name.clone(),
            args: checked_args,
            ty: return_ty,
        },
        error,
    )
}

pub fn typecheck_typename(
    unchecked_type: &UncheckedType,
    stack: &ScopeStack,
) -> (Type, Option<JaktError>) {
    let mut error = None;

    match unchecked_type {
        UncheckedType::Name(name, span) => match name.as_str() {
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
            "c_char" => (Type::CChar, None),
            "c_int" => (Type::CInt, None),
            "String" => (Type::String, None),
            "bool" => (Type::Bool, None),
            "void" => (Type::Void, None),
            x => {
                let structure = stack.find_struct(x);
                match structure {
                    Some(struct_id) => (Type::Struct(struct_id), None),
                    None => (
                        Type::Unknown,
                        Some(JaktError::TypecheckError("unknown type".to_string(), *span)),
                    ),
                }
            }
        },
        UncheckedType::Empty => (Type::Unknown, None),
        UncheckedType::Vector(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, stack);
            error = error.or(err);

            (Type::Vector(Box::new(inner_ty)), error)
        }
        UncheckedType::Optional(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, stack);
            error = error.or(err);

            (Type::Optional(Box::new(inner_ty)), error)
        }
        UncheckedType::RawPtr(inner, _) => {
            let (inner_ty, err) = typecheck_typename(inner, stack);
            error = error.or(err);

            (Type::RawPtr(Box::new(inner_ty)), error)
        }
    }
}
