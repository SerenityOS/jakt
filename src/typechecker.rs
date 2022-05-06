use crate::{
    error::JaktError,
    parser::{Block, Call, Expression, Function, Operator, ParsedFile, Statement, Type, VarDecl},
};

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

pub struct CheckedFunction {
    pub name: String,
    pub return_type: Type,
    pub params: Vec<(String, Type)>,
    pub block: CheckedBlock,
}

pub struct CheckedBlock {
    pub stmts: Vec<CheckedStatement>,
}

impl CheckedBlock {
    pub fn new() -> Self {
        Self { stmts: Vec::new() }
    }
}
pub enum CheckedStatement {
    Expression(CheckedExpression),
    Defer(CheckedBlock),
    VarDecl(VarDecl, CheckedExpression),
    If(CheckedExpression, CheckedBlock),
    While(CheckedExpression, CheckedBlock),
    Return(CheckedExpression),
    Garbage,
}

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
    Var(String, Type),

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
            CheckedExpression::Var(_, ty) => ty.clone(),
            CheckedExpression::Garbage => Type::Unknown,
        }
    }
}

pub struct CheckedCall {
    pub name: String,
    pub args: Vec<(String, CheckedExpression)>,
    pub ty: Type,
}

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

    pub fn add_var(&mut self, var: (String, Type)) {
        if let Some(frame) = self.frames.last_mut() {
            frame.vars.push(var);
        }
    }

    pub fn find_var(&self, var: &str) -> Option<Type> {
        for frame in self.frames.iter().rev() {
            for v in &frame.vars {
                if v.0 == var {
                    return Some(v.1.clone());
                }
            }
        }

        None
    }
}

pub struct StackFrame {
    vars: Vec<(String, Type)>,
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
        let (checked_fun, err) = typecheck_fun(fun, stack);
        error = error.or(err);

        output.checked_functions.push(checked_fun);
    }

    (output, error)
}

fn typecheck_fun(fun: &Function, stack: &mut Stack) -> (CheckedFunction, Option<JaktError>) {
    let mut error = None;

    stack.push_frame();

    for param in &fun.params {
        stack.add_var(param.clone());
    }

    let (block, err) = typecheck_block(&fun.block, stack);
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

pub fn typecheck_block(block: &Block, stack: &mut Stack) -> (CheckedBlock, Option<JaktError>) {
    let mut error = None;
    let mut checked_block = CheckedBlock::new();

    stack.push_frame();

    for stmt in &block.stmts {
        let (checked_stmt, err) = typecheck_statement(stmt, stack);
        error = error.or(err);

        checked_block.stmts.push(checked_stmt);
    }

    stack.pop_frame();

    (checked_block, error)
}

pub fn typecheck_statement(
    stmt: &Statement,
    stack: &mut Stack,
) -> (CheckedStatement, Option<JaktError>) {
    let mut error = None;

    match stmt {
        Statement::Expression(expr) => {
            let (checked_expr, err) = typecheck_expression(expr, stack);

            (CheckedStatement::Expression(checked_expr), err)
        }
        Statement::Defer(block) => {
            let (checked_block, err) = typecheck_block(block, stack);

            (CheckedStatement::Defer(checked_block), err)
        }
        Statement::VarDecl(var_decl, init) => {
            let (checked_expression, err) = typecheck_expression(init, stack);
            error = error.or(err);

            let mut var_decl = var_decl.clone();

            if var_decl.ty == Type::Unknown {
                // Use the initializer to get our type
                var_decl.ty = checked_expression.ty();
            } else if var_decl.ty != checked_expression.ty() {
                error = error.or(Some(JaktError::TypecheckError(
                    "mismatch between declaration and initializer".to_string(),
                    init.span(),
                )));
            }

            stack.add_var((var_decl.name.clone(), var_decl.ty.clone()));

            (
                CheckedStatement::VarDecl(var_decl.clone(), checked_expression),
                error,
            )
        }
        Statement::If(cond, block) => {
            let (checked_cond, err) = typecheck_expression(cond, stack);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, stack);
            error = error.or(err);

            (CheckedStatement::If(checked_cond, checked_block), error)
        }
        Statement::While(cond, block) => {
            let (checked_cond, err) = typecheck_expression(cond, stack);
            error = error.or(err);

            let (checked_block, err) = typecheck_block(block, stack);
            error = error.or(err);

            (CheckedStatement::While(checked_cond, checked_block), error)
        }
        Statement::Return(expr) => {
            let (output, err) = typecheck_expression(expr, stack);

            (CheckedStatement::Return(output), err)
        }
        Statement::Garbage => (CheckedStatement::Garbage, None),
    }
}

pub fn typecheck_expression(
    expr: &Expression,
    stack: &mut Stack,
) -> (CheckedExpression, Option<JaktError>) {
    let mut error = None;

    match expr {
        Expression::BinaryOp(lhs, op, rhs) => {
            let (checked_lhs, err) = typecheck_expression(lhs, stack);
            error = error.or(err);

            let op = match &**op {
                Expression::Operator(operator, _) => operator.clone(),
                _ => panic!("Need more robust operator error handling"),
            };

            let (checked_rhs, err) = typecheck_expression(rhs, stack);
            error = error.or(err);

            // TODO: actually do the binary operator typecheck against safe operations
            (
                CheckedExpression::BinaryOp(
                    Box::new(checked_lhs),
                    Box::new(op),
                    Box::new(checked_rhs),
                    Type::Unknown,
                ),
                error,
            )
        }
        Expression::Boolean(b, _) => (CheckedExpression::Boolean(*b), None),
        Expression::Call(call, ..) => {
            let (checked_call, err) = typecheck_call(call, stack);

            (CheckedExpression::Call(checked_call, Type::Unknown), err)
        }
        Expression::Int64(i, _) => (CheckedExpression::Int64(*i), None),
        Expression::QuotedString(qs, _) => (CheckedExpression::QuotedString(qs.clone()), None),
        Expression::Var(v, span) => {
            if let Some(ty) = stack.find_var(v) {
                (CheckedExpression::Var(v.clone(), ty.clone()), None)
            } else {
                (
                    CheckedExpression::Var(v.clone(), Type::Unknown),
                    Some(JaktError::TypecheckError(
                        "variable not found".to_string(),
                        *span,
                    )),
                )
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

pub fn typecheck_call(call: &Call, stack: &mut Stack) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;

    for arg in &call.args {
        let (checked_arg, err) = typecheck_expression(&arg.1, stack);
        error = error.or(err);

        checked_args.push((arg.0.clone(), checked_arg));
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
