use crate::{
    error::JaktError,
    parser::{
        Block, Call, Expression, Function, Operator, Parameter, ParsedFile, Span, Statement, Type,
        VarDecl, Variable,
    },
};

#[derive(Clone)]
pub struct CheckedFile {
    pub checked_functions: Vec<CheckedFunction>,
}

impl CheckedFile {
    pub fn new() -> Self {
        Self {
            checked_functions: Vec::new(),
        }
    }
}

#[derive(Clone)]
pub struct CheckedFunction {
    pub name: String,
    pub return_type: Type,
    pub params: Vec<Parameter>,
    pub block: CheckedBlock,
}

#[derive(Clone)]
pub struct CheckedBlock {
    pub stmts: Vec<CheckedStatement>,
}

impl CheckedBlock {
    pub fn new() -> Self {
        Self { stmts: Vec::new() }
    }
}

#[derive(Clone)]
pub enum CheckedStatement {
    Expression(CheckedExpression),
    Defer(CheckedBlock),
    VarDecl(VarDecl, CheckedExpression),
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
pub enum CheckedExpression {
    // Standalone
    Boolean(bool),
    Call(CheckedCall, Type),
    Int64(i64),
    QuotedString(String),
    BinaryOp(
        Box<CheckedExpression>,
        Box<Operator>,
        Box<CheckedExpression>,
        Type,
    ),
    Vector(Vec<CheckedExpression>, Type),
    IndexedExpression(Box<CheckedExpression>, Box<CheckedExpression>, Type),
    Var(Variable),

    // Parsing error
    Garbage,
}

impl CheckedExpression {
    pub fn ty(&self) -> Type {
        match self {
            CheckedExpression::Boolean(_) => Type::Bool,
            CheckedExpression::Call(_, ty) => ty.clone(),
            CheckedExpression::Int64(_) => Type::I64,
            CheckedExpression::QuotedString(_) => Type::String,
            CheckedExpression::BinaryOp(_, _, _, ty) => ty.clone(),
            CheckedExpression::Vector(_, ty) => ty.clone(),
            CheckedExpression::IndexedExpression(_, _, ty) => ty.clone(),
            CheckedExpression::Var(Variable { ty, .. }) => ty.clone(),
            CheckedExpression::Garbage => Type::Unknown,
        }
    }
}

#[derive(Clone, Debug)]
pub struct CheckedCall {
    pub name: String,
    pub args: Vec<(String, CheckedExpression)>,
    pub ty: Type,
}

#[derive(Clone)]
pub struct Stack {
    pub frames: Vec<StackFrame>,
}

impl Stack {
    pub fn new() -> Self {
        Self { frames: Vec::new() }
    }
    pub fn push_frame(&mut self) {
        self.frames.push(StackFrame::new())
    }

    pub fn pop_frame(&mut self) {
        self.frames.pop();
    }

    pub fn add_var(&mut self, var: Variable, span: Span) -> Result<(), JaktError> {
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

    pub fn find_var(&self, var: &str) -> Option<Variable> {
        for frame in self.frames.iter().rev() {
            for v in &frame.vars {
                if v.name == var {
                    return Some(v.clone());
                }
            }
        }

        None
    }
}

#[derive(Clone)]
pub struct StackFrame {
    vars: Vec<Variable>,
}

impl StackFrame {
    pub fn new() -> Self {
        Self { vars: Vec::new() }
    }
}

pub fn typecheck_file(file: &ParsedFile) -> (CheckedFile, Option<JaktError>) {
    let mut stack = Stack::new();

    typecheck_file_helper(file, &mut stack)
}

fn typecheck_file_helper(file: &ParsedFile, stack: &mut Stack) -> (CheckedFile, Option<JaktError>) {
    let mut output = CheckedFile::new();
    let mut error = None;

    for fun in &file.funs {
        let (checked_fun, err) = typecheck_fun(fun, stack, &file);
        error = error.or(err);

        output.checked_functions.push(checked_fun);
    }

    (output, error)
}

fn typecheck_fun(
    fun: &Function,
    stack: &mut Stack,
    file: &ParsedFile,
) -> (CheckedFunction, Option<JaktError>) {
    let mut error = None;

    stack.push_frame();

    for param in &fun.params {
        if let Err(err) = stack.add_var(param.variable.clone(), fun.name_span) {
            error = error.or(Some(err));
        }
    }

    let (block, err) = typecheck_block(&fun.block, stack, file);
    error = error.or(err);

    stack.pop_frame();

    let output = CheckedFunction {
        name: fun.name.clone(),
        params: fun.params.clone(),
        return_type: fun.return_type.clone(),
        block,
    };

    (output, error)
}

pub fn typecheck_block(
    block: &Block,
    stack: &mut Stack,
    file: &ParsedFile,
) -> (CheckedBlock, Option<JaktError>) {
    let mut error = None;
    let mut checked_block = CheckedBlock::new();

    stack.push_frame();

    for stmt in &block.stmts {
        let (checked_stmt, err) = typecheck_statement(stmt, stack, file);
        error = error.or(err);

        checked_block.stmts.push(checked_stmt);
    }

    stack.pop_frame();

    (checked_block, error)
}

pub fn typecheck_statement(
    stmt: &Statement,
    stack: &mut Stack,
    file: &ParsedFile,
) -> (CheckedStatement, Option<JaktError>) {
    let mut error = None;

    match stmt {
        Statement::Expression(expr) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, file);

            (CheckedStatement::Expression(checked_expr), err)
        }
        Statement::Defer(block) => {
            let (checked_block, err) = typecheck_block(block, stack, file);

            (CheckedStatement::Defer(checked_block), err)
        }
        Statement::VarDecl(var_decl, init) => {
            let (checked_expression, err) = typecheck_expression(init, stack, file);
            error = error.or(err);

            let mut var_decl = var_decl.clone();

            if var_decl.ty == Type::Unknown {
                // Use the initializer to get our type
                var_decl.ty = checked_expression.ty();
            }

            // Taking this out for now until we have better number type support
            // } else if var_decl.ty != checked_expression.ty() {
            //     error = error.or(Some(JaktError::TypecheckError(
            //         "mismatch between declaration and initializer".to_string(),
            //         init.span(),
            //     )));
            // }

            if let Err(err) = stack.add_var(
                Variable {
                    name: var_decl.name.clone(),
                    ty: var_decl.ty.clone(),
                    mutable: var_decl.mutable,
                },
                var_decl.span,
            ) {
                error = error.or(Some(err));
            }

            (
                CheckedStatement::VarDecl(var_decl.clone(), checked_expression),
                error,
            )
        }
        Statement::If(cond, block, else_stmt) => {
            let (checked_cond, err) = typecheck_expression(cond, stack, file);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, stack, file);
            error = error.or(err);

            let else_output;
            if let Some(else_stmt) = else_stmt {
                let (checked_stmt, err) = typecheck_statement(else_stmt, stack, file);
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
            let (checked_cond, err) = typecheck_expression(cond, stack, file);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, stack, file);
            error = error.or(err);

            (CheckedStatement::While(checked_cond, checked_block), error)
        }
        Statement::Return(expr) => {
            let (output, err) = typecheck_expression(expr, stack, file);

            (CheckedStatement::Return(output), err)
        }
        Statement::Block(block) => {
            let (checked_block, err) = typecheck_block(block, stack, file);
            (CheckedStatement::Block(checked_block), err)
        }
        Statement::Garbage => (CheckedStatement::Garbage, None),
    }
}

pub fn typecheck_expression(
    expr: &Expression,
    stack: &mut Stack,
    file: &ParsedFile,
) -> (CheckedExpression, Option<JaktError>) {
    let mut error = None;

    match expr {
        Expression::BinaryOp(lhs, op, rhs) => {
            let (checked_lhs, err) = typecheck_expression(lhs, stack, file);
            error = error.or(err);

            let op_span = op.span();

            let op = match &**op {
                Expression::Operator(operator, _) => operator.clone(),
                _ => panic!("Need more robust operator error handling"),
            };

            let (checked_rhs, err) = typecheck_expression(rhs, stack, file);
            error = error.or(err);

            error = error.or(typecheck_operation(
                &checked_lhs,
                &op,
                &checked_rhs,
                op_span,
            ));

            // TODO: actually do the binary operator typecheck against safe operations
            // For now, use a type we know
            let ty = checked_lhs.ty();
            (
                CheckedExpression::BinaryOp(
                    Box::new(checked_lhs),
                    Box::new(op),
                    Box::new(checked_rhs),
                    ty,
                ),
                error,
            )
        }
        Expression::Boolean(b, _) => (CheckedExpression::Boolean(*b), None),
        Expression::Call(call, span) => {
            let (checked_call, err) = typecheck_call(call, stack, span, file);

            (CheckedExpression::Call(checked_call, Type::Unknown), err)
        }
        Expression::Int64(i, _) => (CheckedExpression::Int64(*i), None),
        Expression::QuotedString(qs, _) => (CheckedExpression::QuotedString(qs.clone()), None),
        Expression::Var(v, span) => {
            if let Some(var) = stack.find_var(v) {
                (CheckedExpression::Var(var.clone()), None)
            } else {
                (
                    CheckedExpression::Var(Variable {
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
                let (checked_expr, err) = typecheck_expression(v, stack, file);
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
        Expression::IndexedExpression(expr, idx, _) => {
            let (checked_expr, err) = typecheck_expression(expr, stack, file);
            error = error.or(err);

            let (checked_idx, err) = typecheck_expression(idx, stack, file);
            error = error.or(err);

            let mut ty = Type::Unknown;

            match checked_expr.ty() {
                Type::Vector(inner_ty) => match checked_idx.ty() {
                    Type::I64 => {
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

pub fn typecheck_operation(
    lhs: &CheckedExpression,
    op: &Operator,
    rhs: &CheckedExpression,
    span: Span,
) -> Option<JaktError> {
    match op {
        Operator::Assign
        | Operator::AddAssign
        | Operator::SubtractAssign
        | Operator::MultiplyAssign
        | Operator::DivideAssign => {
            let lhs_ty = lhs.ty();
            let rhs_ty = rhs.ty();

            if lhs_ty != rhs_ty {
                return Some(JaktError::TypecheckError(
                    format!(
                        "assignment between incompatible types ({:?} and {:?})",
                        lhs_ty, rhs_ty
                    ),
                    span,
                ));
            }

            match lhs {
                CheckedExpression::Var(var) => {
                    if !var.mutable {
                        return Some(JaktError::TypecheckError(
                            "assignment to immutable variable".to_string(),
                            span,
                        ));
                    }
                }
                _ => {}
            }
        }
        _ => {}
    }

    None
}

pub fn resolve_call<'a>(
    call: &Call,
    span: &Span,
    file: &'a ParsedFile,
) -> (Option<&'a Function>, Option<JaktError>) {
    let mut callee = None;
    let mut error = None;

    // FIXME: Support function overloading.
    for fun in &file.funs {
        if fun.name == call.name {
            callee = Some(fun);
            break;
        }
    }

    if callee.is_none() {
        error = Some(JaktError::TypecheckError(
            "call to unknown function".to_string(),
            *span,
        ));
    }

    (callee, error)
}

pub fn typecheck_call(
    call: &Call,
    stack: &mut Stack,
    span: &Span,
    file: &ParsedFile,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;

    match call.name.as_str() {
        "print" => {
            // FIXME: This is a hack since print() is hard-coded into codegen at the moment.
            for arg in &call.args {
                let (checked_arg, err) = typecheck_expression(&arg.1, stack, file);
                error = error.or(err);

                checked_args.push((arg.0.clone(), checked_arg));
            }
        }
        _ => {
            let (callee, err) = resolve_call(call, span, file);
            error = error.or(err);

            if let Some(callee) = callee {
                // Check that we have the right number of arguments.
                if callee.params.len() != call.args.len() {
                    error = error.or(Some(JaktError::TypecheckError(
                        "wrong number of arguments".to_string(),
                        *span,
                    )));
                } else {
                    let mut idx = 0;

                    while idx < call.args.len() {
                        let (checked_arg, err) =
                            typecheck_expression(&call.args[idx].1, stack, file);
                        error = error.or(err);

                        if callee.params[idx].requires_label
                            && call.args[idx].0 != callee.params[idx].variable.name
                        {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Wrong parameter name in argument label".to_string(),
                                call.args[idx].1.span(),
                            )));
                        }

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
            name: call.name.clone(),
            args: checked_args,
            ty: Type::Unknown,
        },
        error,
    )
}
