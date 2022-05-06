use crate::parser::{Block, Expression, Function, Operator, ParsedFile, Statement, Type};

const INDENT_SIZE: usize = 4;

pub fn translate(file: &ParsedFile) -> String {
    let mut output = String::new();

    output.push_str("#include \"runtime/lib.h\"\n");
    output.push_str("#include<iostream>\n");

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

    let block = translate_block(0, &fun.block);
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

fn translate_block(indent: usize, block: &Block) -> String {
    let mut output = String::new();

    output.push_str("{\n");

    for stmt in &block.stmts {
        let stmt = translate_stmt(indent + INDENT_SIZE, stmt);

        output.push_str(&stmt);
    }

    output.push_str("}\n");

    output
}

fn translate_stmt(indent: usize, stmt: &Statement) -> String {
    let mut output = String::new();

    output.push_str(&std::iter::repeat(' ').take(indent).collect::<String>());

    match stmt {
        Statement::Expression(expr) => {
            let expr = translate_expr(indent, &expr);
            output.push_str(&expr);
            output.push_str(";\n");
        }
        Statement::Defer(block) => {
            // NOTE: We let the preprocessor generate a unique name for the RAII helper.
            output.push_str("#define __SCOPE_GUARD_NAME __scope_guard_ ## __COUNTER__\n");
            output.push_str("ScopeGuard __SCOPE_GUARD_NAME  ([&] \n");
            output.push_str("#undef __SCOPE_GUARD_NAME\n");
            output.push_str(&translate_block(indent, block));
            output.push_str(");\n");
        }
        Statement::Return(expr) => {
            let expr = translate_expr(indent, &expr);
            output.push_str("return (");
            output.push_str(&expr);
            output.push_str(");\n")
        }
        Statement::If(cond, block) => {
            let expr = translate_expr(indent, &cond);
            output.push_str("if (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = translate_block(indent, block);
            output.push_str(&block);
        }
        Statement::While(cond, block) => {
            let expr = translate_expr(indent, &cond);
            output.push_str("while (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = translate_block(indent, block);
            output.push_str(&block);
        }
        Statement::VarDecl(var_decl, expr) => {
            if !var_decl.mutable {
                output.push_str("const ");
            }
            output.push_str(&translate_type(&var_decl.ty));
            output.push(' ');
            output.push_str(&var_decl.name);
            output.push_str(" = ");
            output.push_str(&translate_expr(indent, expr));
            output.push_str(";\n");
        }
        Statement::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}

fn translate_expr(indent: usize, expr: &Expression) -> String {
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
        Expression::Boolean(bool) => {
            if *bool {
                output.push_str("true");
            } else {
                output.push_str("false");
            }
        }
        Expression::Call(call) => {
            if call.name == "print" {
                output.push_str("std::cout << ");
                output.push('(');
                for param in &call.args {
                    output.push_str(&translate_expr(indent, &param.1));
                }
                output.push_str(") << std::endl");
            } else {
                output.push_str(&call.name);
                output.push('(');

                let mut first = true;
                for param in &call.args {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    output.push_str(&translate_expr(indent, &param.1));
                }
                output.push(')');
            }
        }
        Expression::BinaryOp(lhs, op, rhs) => {
            output.push('(');
            output.push_str(&translate_expr(indent, lhs));
            match **op {
                Expression::Operator(Operator::Add) => output.push_str(" + "),
                Expression::Operator(Operator::Subtract) => output.push_str(" - "),
                Expression::Operator(Operator::Multiply) => output.push_str(" * "),
                Expression::Operator(Operator::Divide) => output.push_str(" / "),
                Expression::Operator(Operator::Assign) => output.push_str(" = "),
                Expression::Operator(Operator::Equal) => output.push_str(" == "),
                Expression::Operator(Operator::NotEqual) => output.push_str(" != "),
                Expression::Operator(Operator::LessThan) => output.push_str(" < "),
                Expression::Operator(Operator::LessThanOrEqual) => output.push_str(" <= "),
                Expression::Operator(Operator::GreaterThan) => output.push_str(" > "),
                Expression::Operator(Operator::GreaterThanOrEqual) => output.push_str(" >= "),

                _ => {
                    panic!("Cannot codegen garbage operator")
                }
            }
            output.push_str(&translate_expr(indent, rhs));
            output.push(')');
        }
        Expression::Garbage | Expression::Operator(_) => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}
