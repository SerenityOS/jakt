use crate::{
    parser::{BinaryOperator, FunctionLinkage, UnaryOperator},
    typechecker::{
        CheckedBlock, CheckedExpression, CheckedFile, CheckedFunction, CheckedStatement,
        CheckedStruct, Type,
    },
};

const INDENT_SIZE: usize = 4;

pub fn translate(file: &CheckedFile) -> String {
    let mut output = String::new();

    output.push_str("#include \"runtime/lib.h\"\n");

    for structure in &file.structs {
        let struct_output = translate_struct_predecl(structure);

        output.push_str(&struct_output);
        output.push('\n');
    }

    output.push('\n');

    for structure in &file.structs {
        let struct_output = translate_struct(structure, file);

        output.push_str(&struct_output);
        output.push('\n');
    }

    output.push('\n');

    for fun in &file.funs {
        let fun_output = translate_function_predecl(fun, file);

        if fun.linkage != FunctionLinkage::ImplicitConstructor {
            output.push_str(&fun_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for fun in &file.funs {
        if fun.linkage == FunctionLinkage::External {
            continue;
        } else if fun.linkage == FunctionLinkage::ImplicitConstructor {
            let fun_output = translate_constructor(fun, file);

            output.push_str(&fun_output);
            output.push('\n');
        } else {
            let fun_output = translate_function(fun, file);

            output.push_str(&fun_output);
            output.push('\n');
        }
    }

    output
}

fn translate_struct_predecl(structure: &CheckedStruct) -> String {
    format!("struct {};", structure.name)
}

fn translate_struct(structure: &CheckedStruct, file: &CheckedFile) -> String {
    let mut output = format!("struct {} {{\n", structure.name);

    for member in &structure.members {
        output.push_str(&" ".repeat(INDENT_SIZE));

        output.push_str(&translate_type(&member.ty, file));
        output.push(' ');
        output.push_str(&member.name);
        output.push_str(";\n");
    }

    // Put together our own constructor
    // eg) Person(String name, i64 age);
    output.push_str(&" ".repeat(INDENT_SIZE));
    output.push_str(&structure.name);
    output.push('(');
    let mut first = true;
    for member in &structure.members {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }
        output.push_str(&translate_type(&member.ty, file));
        output.push(' ');
        output.push_str(&member.name);
    }
    output.push_str(");\n");

    output.push_str("};");
    output
}

fn translate_function_predecl(fun: &CheckedFunction, file: &CheckedFile) -> String {
    let mut output = String::new();

    if fun.linkage == FunctionLinkage::External {
        output.push_str("extern ");
    }

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&translate_type(&fun.return_type, file));
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

        let ty = translate_type(&param.variable.ty, file);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.variable.name);
    }
    output.push_str(");");

    output
}

fn translate_function(fun: &CheckedFunction, file: &CheckedFile) -> String {
    let mut output = String::new();

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&translate_type(&fun.return_type, file));
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

        let ty = translate_type(&param.variable.ty, file);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.variable.name);
    }
    output.push(')');

    let block = translate_block(0, &fun.block, file);
    output.push_str(&block);

    output
}

fn translate_constructor(fun: &CheckedFunction, file: &CheckedFile) -> String {
    let mut output = String::new();

    output.push_str(&translate_type(&fun.return_type, file));
    output.push_str("::");

    output.push_str(&fun.name);
    output.push('(');

    let mut first = true;
    for param in &fun.params {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }

        let ty = translate_type(&param.variable.ty, file);
        output.push_str(&ty);
        output.push_str(" a_");
        output.push_str(&param.variable.name);
    }
    output.push_str("): ");

    let mut first = true;
    for param in &fun.params {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }

        output.push_str(&param.variable.name);
        output.push_str("(a_");
        output.push_str(&param.variable.name);
        output.push(')');
    }

    output.push_str("{}\n");

    output
}

fn translate_type(ty: &Type, file: &CheckedFile) -> String {
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
        Type::Vector(v) => format!("Vector<{}>", translate_type(v, file)),
        Type::Tuple(types) => {
            let mut output = "Tuple<".to_string();
            let mut first = true;

            for ty in types {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&translate_type(ty, file));
            }

            output.push('>');
            output
        }
        Type::Optional(v) => format!("Optional<{}>", translate_type(v, file)),
        Type::Struct(struct_id) => file.structs[*struct_id].name.clone(),
        Type::Unknown => String::from("auto"),
    }
}

fn translate_block(indent: usize, checked_block: &CheckedBlock, file: &CheckedFile) -> String {
    let mut output = String::new();

    output.push_str("{\n");

    for stmt in &checked_block.stmts {
        let stmt = translate_stmt(indent + INDENT_SIZE, stmt, file);

        output.push_str(&stmt);
    }

    output.push_str(&" ".repeat(indent));
    output.push_str("}\n");

    output
}

fn translate_stmt(indent: usize, stmt: &CheckedStatement, file: &CheckedFile) -> String {
    let mut output = String::new();

    output.push_str(&" ".repeat(indent));

    match stmt {
        CheckedStatement::Expression(expr) => {
            let expr = translate_expr(indent, expr, file);
            output.push_str(&expr);
            output.push_str(";\n");
        }
        CheckedStatement::Defer(block) => {
            // NOTE: We let the preprocessor generate a unique name for the RAII helper.
            output.push_str("#define __SCOPE_GUARD_NAME __scope_guard_ ## __COUNTER__\n");
            output.push_str("ScopeGuard __SCOPE_GUARD_NAME  ([&] \n");
            output.push_str("#undef __SCOPE_GUARD_NAME\n");
            output.push_str(&translate_block(indent, block, file));
            output.push_str(");\n");
        }
        CheckedStatement::Return(expr) => {
            let expr = translate_expr(indent, expr, file);
            output.push_str("return (");
            output.push_str(&expr);
            output.push_str(");\n")
        }
        CheckedStatement::If(cond, block, else_stmt) => {
            let expr = translate_expr(indent, cond, file);
            output.push_str("if (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = translate_block(indent, block, file);
            output.push_str(&block);

            if let Some(else_stmt) = else_stmt {
                output.push_str(" else ");
                let else_string = translate_stmt(indent, else_stmt, file);
                output.push_str(&else_string);
            }
        }
        CheckedStatement::While(cond, block) => {
            let expr = translate_expr(indent, cond, file);
            output.push_str("while (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = translate_block(indent, block, file);
            output.push_str(&block);
        }
        CheckedStatement::VarDecl(var_decl, expr) => {
            if !var_decl.mutable {
                output.push_str("const ");
            }
            output.push_str(&translate_type(&var_decl.ty, file));
            output.push(' ');
            output.push_str(&var_decl.name);
            output.push_str(" = ");
            output.push_str(&translate_expr(indent, expr, file));
            output.push_str(";\n");
        }
        CheckedStatement::Block(checked_block) => {
            let block = translate_block(indent, checked_block, file);
            output.push_str(&block);
        }
        CheckedStatement::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}

fn translate_expr(indent: usize, expr: &CheckedExpression, file: &CheckedFile) -> String {
    let mut output = String::new();

    match expr {
        CheckedExpression::OptionalNone(_) => {
            output.push_str("{}");
        }
        CheckedExpression::OptionalSome(expr, _) => {
            output.push('(');
            output.push_str(&translate_expr(indent, expr, file));
            output.push(')');
        }
        CheckedExpression::ForcedUnwrap(expr, _) => {
            output.push('(');
            output.push_str(&translate_expr(indent, expr, file));
            output.push_str(".value())");
        }
        CheckedExpression::QuotedString(qs) => {
            output.push_str("String(\"");
            output.push_str(qs);
            output.push_str("\")");
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
                    output.push_str(&translate_expr(indent, &param.1, file));
                }
                output.push(')');
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

                    output.push_str(&translate_expr(indent, &param.1, file));
                }
                output.push(')');
            }
        }
        CheckedExpression::UnaryOp(expr, op, ..) => {
            output.push('(');
            match op {
                UnaryOperator::PreIncrement => {
                    output.push_str("++");
                }
                UnaryOperator::PreDecrement => {
                    output.push_str("--");
                }
                UnaryOperator::Negate => {
                    output.push_str("-");
                }
                _ => {}
            }
            output.push_str(&translate_expr(indent, expr, file));
            match op {
                UnaryOperator::PostIncrement => {
                    output.push_str("++");
                }
                UnaryOperator::PostDecrement => {
                    output.push_str("--");
                }
                _ => {}
            }
            output.push(')');
        }
        CheckedExpression::BinaryOp(lhs, op, rhs, ..) => {
            output.push('(');
            output.push_str(&translate_expr(indent, lhs, file));
            match op {
                BinaryOperator::Add => output.push_str(" + "),
                BinaryOperator::Subtract => output.push_str(" - "),
                BinaryOperator::Multiply => output.push_str(" * "),
                BinaryOperator::Modulo => output.push_str(" % "),
                BinaryOperator::Divide => output.push_str(" / "),
                BinaryOperator::Assign => output.push_str(" = "),
                BinaryOperator::AddAssign => output.push_str(" += "),
                BinaryOperator::SubtractAssign => output.push_str(" -= "),
                BinaryOperator::MultiplyAssign => output.push_str(" *= "),
                BinaryOperator::ModuloAssign => output.push_str(" %= "),
                BinaryOperator::DivideAssign => output.push_str(" /= "),
                BinaryOperator::Equal => output.push_str(" == "),
                BinaryOperator::NotEqual => output.push_str(" != "),
                BinaryOperator::LessThan => output.push_str(" < "),
                BinaryOperator::LessThanOrEqual => output.push_str(" <= "),
                BinaryOperator::GreaterThan => output.push_str(" > "),
                BinaryOperator::GreaterThanOrEqual => output.push_str(" >= "),
            }
            output.push_str(&translate_expr(indent, rhs, file));
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

                output.push_str(&translate_expr(indent, val, file))
            }
            output.push_str("}))");
        }
        CheckedExpression::Tuple(vals, _) => {
            // (Tuple{1, 2, 3})
            output.push_str("(Tuple{");
            let mut first = true;
            for val in vals {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&translate_expr(indent, val, file))
            }
            output.push_str("})");
        }
        CheckedExpression::IndexedExpression(expr, idx, _) => {
            output.push_str("((");
            output.push_str(&translate_expr(indent, expr, file));
            output.push_str(")[");
            output.push_str(&translate_expr(indent, idx, file));
            output.push_str("])");
        }
        CheckedExpression::IndexedTuple(expr, idx, _) => {
            // x.get<1>()
            output.push_str("((");
            output.push_str(&translate_expr(indent, expr, file));
            output.push_str(&format!(").get<{}>())", idx));
        }
        CheckedExpression::IndexedStruct(expr, name, _) => {
            // x.get<1>()
            output.push_str("((");
            output.push_str(&translate_expr(indent, expr, file));
            output.push_str(&format!(").{})", name));
        }
        CheckedExpression::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}
