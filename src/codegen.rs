use crate::{
    parser::{Operator, Type},
    typechecker::{
        CheckedBlock, CheckedExpression, CheckedFile, CheckedFunction, CheckedStatement,
    },
};

const INDENT_SIZE: usize = 4;

pub fn translate(file: &CheckedFile) -> String {
    let mut output = String::new();

    output.push_str("#include \"runtime/lib.h\"\n");

    for fun in &file.checked_functions {
        let fun_output = translate_function_predecl(fun);

        output.push_str(&fun_output);
        output.push('\n');
    }

    for fun in &file.checked_functions {
        let fun_output = translate_function(fun);

        output.push_str(&fun_output);
        output.push('\n');
    }

    output
}

fn translate_function(fun: &CheckedFunction) -> String {
    let mut output = String::new();

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&translate_type(&fun.return_type));
    }
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

        let ty = translate_type(&param.ty);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.name);
    }
    output.push(')');

    let block = translate_block(0, &fun.block);
    output.push_str(&block);

    output
}

fn translate_function_predecl(fun: &CheckedFunction) -> String {
    let mut output = String::new();

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&translate_type(&fun.return_type));
    }
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

        let ty = translate_type(&param.ty);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.name);
    }
    output.push_str(");");

    output
}

fn translate_type(ty: &Type) -> String {
    match ty {
        Type::Bool => String::from("bool"),
        Type::String => String::from("String"),
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
        Type::Vector(v) => format!("Vector<{}>", translate_type(v)),
        Type::Unknown => String::from("auto"),
    }
}

fn translate_block(indent: usize, checked_block: &CheckedBlock) -> String {
    let mut output = String::new();

    output.push_str("{\n");

    for stmt in &checked_block.stmts {
        let stmt = translate_stmt(indent + INDENT_SIZE, stmt);

        output.push_str(&stmt);
    }

    output.push_str(&" ".repeat(indent));
    output.push_str("}\n");

    output
}

fn translate_stmt(indent: usize, stmt: &CheckedStatement) -> String {
    let mut output = String::new();

    output.push_str(&" ".repeat(indent));

    match stmt {
        CheckedStatement::Expression(expr) => {
            let expr = translate_expr(indent, expr);
            output.push_str(&expr);
            output.push_str(";\n");
        }
        CheckedStatement::Defer(block) => {
            // NOTE: We let the preprocessor generate a unique name for the RAII helper.
            output.push_str("#define __SCOPE_GUARD_NAME __scope_guard_ ## __COUNTER__\n");
            output.push_str("ScopeGuard __SCOPE_GUARD_NAME  ([&] \n");
            output.push_str("#undef __SCOPE_GUARD_NAME\n");
            output.push_str(&translate_block(indent, block));
            output.push_str(");\n");
        }
        CheckedStatement::Return(expr) => {
            let expr = translate_expr(indent, expr);
            output.push_str("return (");
            output.push_str(&expr);
            output.push_str(");\n")
        }
        CheckedStatement::If(cond, block, else_stmt) => {
            let expr = translate_expr(indent, cond);
            output.push_str("if (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = translate_block(indent, block);
            output.push_str(&block);

            if let Some(else_stmt) = else_stmt {
                output.push_str(" else ");
                let else_string = translate_stmt(indent, else_stmt);
                output.push_str(&else_string);
            }
        }
        CheckedStatement::While(cond, block) => {
            let expr = translate_expr(indent, cond);
            output.push_str("while (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = translate_block(indent, block);
            output.push_str(&block);
        }
        CheckedStatement::VarDecl(var_decl, expr) => {
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
        CheckedStatement::Block(checked_block) => {
            let block = translate_block(indent, checked_block);
            output.push_str(&block);
        }
        CheckedStatement::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}

fn translate_expr(indent: usize, expr: &CheckedExpression) -> String {
    let mut output = String::new();

    match expr {
        CheckedExpression::QuotedString(qs) => {
            output.push('"');
            output.push_str(qs);
            output.push('"');
        }
        CheckedExpression::Int64(int64) => {
            output.push_str("static_cast<i64>(");
            output.push_str(&int64.to_string());
            output.push_str("LL)");
        }
        CheckedExpression::Var(var, ..) => {
            output.push_str(&var.name);
        }
        CheckedExpression::Boolean(bool) => {
            if *bool {
                output.push_str("true");
            } else {
                output.push_str("false");
            }
        }
        CheckedExpression::Call(call, ..) => {
            if call.name == "print" {
                output.push_str("outln(\"{}\", ");
                for param in &call.args {
                    output.push_str(&translate_expr(indent, &param.1));
                }
                output.push_str(")");
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
        CheckedExpression::BinaryOp(lhs, op, rhs, ..) => {
            output.push('(');
            output.push_str(&translate_expr(indent, lhs));
            match **op {
                Operator::Add => output.push_str(" + "),
                Operator::Subtract => output.push_str(" - "),
                Operator::Multiply => output.push_str(" * "),
                Operator::Divide => output.push_str(" / "),
                Operator::Assign => output.push_str(" = "),
                Operator::AddAssign => output.push_str(" += "),
                Operator::SubtractAssign => output.push_str(" -= "),
                Operator::MultiplyAssign => output.push_str(" *= "),
                Operator::DivideAssign => output.push_str(" /= "),
                Operator::Equal => output.push_str(" == "),
                Operator::NotEqual => output.push_str(" != "),
                Operator::LessThan => output.push_str(" < "),
                Operator::LessThanOrEqual => output.push_str(" <= "),
                Operator::GreaterThan => output.push_str(" > "),
                Operator::GreaterThanOrEqual => output.push_str(" >= "),
            }
            output.push_str(&translate_expr(indent, rhs));
            output.push(')');
        }
        CheckedExpression::Vector(vals, _) => {
            // (Vector({1, 2, 3}))
            output.push_str("(Vector({");
            let mut first = true;
            for val in vals {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&translate_expr(indent, val))
            }
            output.push_str("}))");
        }
        CheckedExpression::IndexedExpression(expr, idx, _) => {
            output.push_str("((");
            output.push_str(&translate_expr(indent, expr));
            output.push_str(")[");
            output.push_str(&translate_expr(indent, idx));
            output.push_str("])");
        }
        CheckedExpression::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}
