use crate::parser::{Block, Expression, Function, ParsedFile, Statement, Type};

pub fn translate(file: &ParsedFile) -> String {
    let mut output = String::new();

    output.push_str("#include \"runtime/lib.h\"\n");
    output.push_str("#include<stdio.h>\n");

    for fun in &file.funs {
        let fun_output = translate_function_predecl(fun);

        output.push_str(&fun_output);
        output.push('\n');
    }

    for fun in &file.funs {
        let fun_output = translate_function(fun);

        output.push_str(&fun_output);
        output.push('\n');
    }

    output
}

fn translate_function(fun: &Function) -> String {
    let mut output = String::new();

    output.push_str(&translate_type(&fun.return_type));
    output.push(' ');
    output.push_str(&fun.name);
    output.push('(');

    let mut first = true;
    for param in &fun.params {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }

        let ty = translate_type(&param.1);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.0);
    }
    output.push(')');

    let block = translate_block(&fun.block);
    output.push_str(&block);

    output
}

fn translate_function_predecl(fun: &Function) -> String {
    let mut output = String::new();

    output.push_str(&translate_type(&fun.return_type));
    output.push(' ');
    output.push_str(&fun.name);
    output.push('(');

    let mut first = true;
    for param in &fun.params {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }

        let ty = translate_type(&param.1);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.0);
    }
    output.push_str(");");

    output
}

fn translate_type(ty: &Type) -> String {
    match ty {
        Type::String => String::from("char*"),
        Type::I8 => String::from("i8"),
        Type::I16 => String::from("i16"),
        Type::I32 => String::from("i32"),
        Type::I64 => String::from("i64"),
        Type::U8 => String::from("u8"),
        Type::U16 => String::from("u16"),
        Type::U32 => String::from("u32"),
        Type::U64 => String::from("u64"),
        Type::F32 => String::from("f32"),
        Type::F64 => String::from("f64"),
        Type::Void => String::from("void"),
    }
}

fn translate_block(block: &Block) -> String {
    let mut output = String::new();

    output.push_str("{\n");

    for stmt in &block.stmts {
        let stmt = translate_stmt(stmt);

        output.push_str(&stmt);
    }

    output.push_str("}\n");

    output
}

fn translate_stmt(stmt: &Statement) -> String {
    let mut output = String::new();
    match stmt {
        Statement::Expression(expr) => {
            let expr = translate_expr(&expr);
            output.push_str(&expr)
        }
        Statement::Defer(block) => {
            // NOTE: We let the preprocessor generate a unique name for the RAII helper.
            output.push_str("#define __SCOPE_GUARD_NAME __scope_guard_ ## __COUNTER__\n");
            output.push_str("ScopeGuard __SCOPE_GUARD_NAME  ([&] \n");
            output.push_str("#undef __SCOPE_GUARD_NAME\n");
            output.push_str(&translate_block(block));
            output.push_str(")");
        }
        Statement::Return(expr) => {
            let expr = translate_expr(&expr);
            output.push_str("return (");
            output.push_str(&expr);
            output.push_str(");\n")
        }
        Statement::VarDecl(var_decl, expr) => {
            if !var_decl.mutable {
                output.push_str("const ");
            }
            output.push_str(&translate_type(&var_decl.ty));
            output.push(' ');
            output.push_str(&var_decl.name);
            output.push_str(" = ");
            output.push_str(&translate_expr(expr));
            output.push_str(";\n");
        }
    }

    output.push_str(";\n");

    output
}

fn translate_expr(expr: &Expression) -> String {
    let mut output = String::new();

    match expr {
        Expression::QuotedString(qs) => {
            output.push('"');
            output.push_str(qs);
            output.push('"');
        }
        Expression::Int64(int64) => {
            output.push_str(&int64.to_string());
        }
        Expression::Var(var) => {
            output.push_str(&var.to_string());
        }
        Expression::Call(call) => {
            if call.name == "print" {
                output.push_str("printf");
            } else {
                output.push_str(&call.name);
            }
            output.push('(');
            for param in &call.args {
                output.push_str(&translate_expr(&param.1));
            }
            output.push(')');
        }
    }

    output
}
