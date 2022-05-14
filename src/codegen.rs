use crate::{
    parser::{
        BinaryOperator, DefinitionLinkage, DefinitionType, FunctionLinkage, TypeCast, UnaryOperator,
    },
    typechecker::{
        CheckedBlock, CheckedExpression, CheckedFunction, CheckedStatement, CheckedStruct,
        CheckedVariable, NumericConstant, Project, Scope, Type,
    },
};

const INDENT_SIZE: usize = 4;

pub fn codegen(project: &Project, scope: &Scope) -> String {
    let mut output = String::new();

    output.push_str("#include \"runtime/lib.h\"\n");

    for (_, struct_id) in &scope.structs {
        let structure = &project.structs[*struct_id];
        let struct_output = codegen_struct_predecl(structure);

        if !struct_output.is_empty() {
            output.push_str(&struct_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for (_, struct_id) in &scope.structs {
        let structure = &project.structs[*struct_id];
        let struct_output = codegen_struct(structure, project);

        if !struct_output.is_empty() {
            output.push_str(&struct_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for (_, fun_id) in &scope.funs {
        let fun = &project.funs[*fun_id];
        let fun_output = codegen_function_predecl(fun, project);

        if fun.linkage != FunctionLinkage::ImplicitConstructor && fun.name != "main" {
            output.push_str(&fun_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for (_, fun_id) in &scope.funs {
        let fun = &project.funs[*fun_id];
        if fun.linkage == FunctionLinkage::External {
            continue;
        } else if fun.linkage == FunctionLinkage::ImplicitConstructor {
            continue;
        } else {
            let fun_output = codegen_function(fun, project);

            output.push_str(&fun_output);
            output.push('\n');
        }
    }

    output
}

fn codegen_struct_predecl(structure: &CheckedStruct) -> String {
    if structure.definition_linkage == DefinitionLinkage::External {
        String::new()
    } else {
        match structure.definition_type {
            DefinitionType::Class => {
                format!("class {};", structure.name)
            }
            DefinitionType::Struct => {
                format!("struct {};", structure.name)
            }
        }
    }
}

fn codegen_struct(structure: &CheckedStruct, project: &Project) -> String {
    let mut output = String::new();

    if structure.definition_linkage == DefinitionLinkage::External {
        return output;
    }

    match structure.definition_type {
        DefinitionType::Class => {
            output.push_str(&format!("class {} {{\n", structure.name));
            // As we should test the visibility before codegen, we take a simple
            // approach to codegen
            output.push_str("  public:\n");
        }
        DefinitionType::Struct => {
            output.push_str(&format!("struct {} {{\n", structure.name));
            output.push_str("  public:\n");
        }
    }

    for field in &structure.fields {
        output.push_str(&" ".repeat(INDENT_SIZE));

        output.push_str(&codegen_type(&field.ty, project));
        output.push(' ');
        output.push_str(&field.name);
        output.push_str(";\n");
    }

    for (_, fun_id) in &structure.scope.funs {
        let fun = &project.funs[*fun_id];
        if fun.linkage == FunctionLinkage::ImplicitConstructor {
            let fun_output = codegen_constructor(fun, project);

            output.push_str(&" ".repeat(INDENT_SIZE));
            output.push_str(&fun_output);
            output.push('\n');
        } else {
            output.push_str(&" ".repeat(INDENT_SIZE));
            if fun.is_static() {
                output.push_str("static ");
            }
            let method_output = codegen_function(fun, project);
            output.push_str(&method_output);
        }
    }

    output.push_str("};");
    output
}

fn codegen_function_predecl(fun: &CheckedFunction, project: &Project) -> String {
    let mut output = String::new();

    if fun.linkage == FunctionLinkage::External {
        output.push_str("extern ");
    }

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&codegen_type(&fun.return_type, project));
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

        if !param.variable.mutable {
            output.push_str("const ");
        }
        let ty = codegen_type(&param.variable.ty, project);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.variable.name);
    }
    output.push_str(");");

    output
}

fn codegen_function(fun: &CheckedFunction, project: &Project) -> String {
    let mut output = String::new();

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&codegen_type(&fun.return_type, project));
    }
    output.push(' ');
    if fun.name == "main" {
        output.push_str("__jakt_main");
    } else {
        output.push_str(&fun.name);
    }
    output.push('(');

    if fun.name == "main" && fun.params.is_empty() {
        output.push_str("RefVector<String>");
    }

    let mut first = true;
    let mut const_fun = false;

    for param in &fun.params {
        if param.variable.name == "this" {
            const_fun = !param.variable.mutable;
            continue;
        }

        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }

        if !param.variable.mutable {
            output.push_str("const ");
        }

        let ty = codegen_type(&param.variable.ty, project);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.variable.name);
    }
    output.push(')');

    if const_fun {
        output.push_str(" const");
    }

    if fun.name == "main" {
        output.push_str("\n");
        output.push_str("{\n");
        output.push_str(&" ".repeat(INDENT_SIZE));
    }

    let block = codegen_block(INDENT_SIZE, &fun.block, project);
    output.push_str(&block);

    if fun.name == "main" {
        output.push_str(&" ".repeat(INDENT_SIZE));
        output.push_str("return 0;\n}");
    }

    output
}

fn codegen_constructor(fun: &CheckedFunction, project: &Project) -> String {
    let mut output = String::new();

    output.push_str(&fun.name);
    output.push('(');

    let mut first = true;
    for param in &fun.params {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }

        let ty = codegen_type(&param.variable.ty, project);
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

fn codegen_type(ty: &Type, project: &Project) -> String {
    match ty {
        Type::Bool => String::from("bool"),
        Type::String => String::from("String"),
        Type::CChar => String::from("char"),
        Type::CInt => String::from("int"),
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
        Type::RawPtr(ty) => {
            format!("{}*", codegen_type(ty, project))
        }
        Type::Vector(v) => format!("RefVector<{}>", codegen_type(v, project)),
        Type::Tuple(types) => {
            let mut output = "Tuple<".to_string();
            let mut first = true;

            for ty in types {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&codegen_type(ty, project));
            }

            output.push('>');
            output
        }
        Type::Optional(v) => format!("Optional<{}>", codegen_type(v, project)),
        Type::Struct(struct_id) => project.structs[*struct_id].name.clone(),
        Type::Unknown => String::from("auto"),
    }
}

fn codegen_block(indent: usize, checked_block: &CheckedBlock, project: &Project) -> String {
    let mut output = String::new();

    output.push_str("{\n");

    for stmt in &checked_block.stmts {
        let stmt = codegen_statement(indent + INDENT_SIZE, stmt, project);

        output.push_str(&stmt);
    }

    output.push_str(&" ".repeat(indent));
    output.push_str("}\n");

    output
}

fn codegen_statement(indent: usize, stmt: &CheckedStatement, project: &Project) -> String {
    let mut output = String::new();

    output.push_str(&" ".repeat(indent));

    match stmt {
        CheckedStatement::Expression(expr) => {
            let expr = codegen_expr(indent, expr, project);
            output.push_str(&expr);
            output.push_str(";\n");
        }
        CheckedStatement::Defer(statement) => {
            // NOTE: We let the preprocessor generate a unique name for the RAII helper.
            output.push_str("#define __SCOPE_GUARD_NAME __scope_guard_ ## __COUNTER__\n");
            output.push_str("ScopeGuard __SCOPE_GUARD_NAME  ([&] \n");
            output.push_str("#undef __SCOPE_GUARD_NAME\n{");
            output.push_str(&codegen_statement(indent, statement, project));
            output.push_str("});\n");
        }
        CheckedStatement::Return(expr) => {
            let expr = codegen_expr(indent, expr, project);
            output.push_str("return (");
            output.push_str(&expr);
            output.push_str(");\n")
        }
        CheckedStatement::If(cond, block, else_stmt) => {
            let expr = codegen_expr(indent, cond, project);
            output.push_str("if (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = codegen_block(indent, block, project);
            output.push_str(&block);

            if let Some(else_stmt) = else_stmt {
                output.push_str(" else ");
                let else_string = codegen_statement(indent, else_stmt, project);
                output.push_str(&else_string);
            }
        }
        CheckedStatement::While(cond, block) => {
            let expr = codegen_expr(indent, cond, project);
            output.push_str("while (");
            output.push_str(&expr);
            output.push_str(") ");

            let block = codegen_block(indent, block, project);
            output.push_str(&block);
        }
        CheckedStatement::VarDecl(var_decl, expr) => {
            if !var_decl.mutable {
                output.push_str("const ");
            }
            output.push_str(&codegen_type(&var_decl.ty, project));
            output.push(' ');
            output.push_str(&var_decl.name);
            output.push_str(" = ");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(";\n");
        }
        CheckedStatement::Block(checked_block) => {
            let block = codegen_block(indent, checked_block, project);
            output.push_str(&block);
        }
        CheckedStatement::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}

fn codegen_expr(indent: usize, expr: &CheckedExpression, project: &Project) -> String {
    let mut output = String::new();

    match expr {
        CheckedExpression::OptionalNone(_) => {
            output.push_str("{}");
        }
        CheckedExpression::OptionalSome(expr, _) => {
            output.push('(');
            output.push_str(&codegen_expr(indent, expr, project));
            output.push(')');
        }
        CheckedExpression::ForcedUnwrap(expr, _) => {
            output.push('(');
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(".value())");
        }
        CheckedExpression::QuotedString(qs) => {
            output.push_str("String(\"");
            output.push_str(qs);
            output.push_str("\")");
        }
        CheckedExpression::CharacterConstant(c) => {
            output.push('\'');
            output.push(*c);
            output.push('\'');
        }
        CheckedExpression::NumericConstant(constant, _) => match constant {
            NumericConstant::I8(value) => {
                output.push_str("static_cast<i8>(");
                output.push_str(&value.to_string());
                output.push_str(")");
            }
            NumericConstant::I16(value) => {
                output.push_str("static_cast<i16>(");
                output.push_str(&value.to_string());
                output.push_str(")");
            }
            NumericConstant::I32(value) => {
                output.push_str("static_cast<i32>(");
                output.push_str(&value.to_string());
                output.push_str(")");
            }
            NumericConstant::I64(value) => {
                output.push_str("static_cast<i64>(");
                output.push_str(&value.to_string());
                output.push_str("LL)");
            }
            NumericConstant::U8(value) => {
                output.push_str("static_cast<u8>(");
                output.push_str(&value.to_string());
                output.push_str(")");
            }
            NumericConstant::U16(value) => {
                output.push_str("static_cast<u16>(");
                output.push_str(&value.to_string());
                output.push_str(")");
            }
            NumericConstant::U32(value) => {
                output.push_str("static_cast<u32>(");
                output.push_str(&value.to_string());
                output.push_str(")");
            }
            NumericConstant::U64(value) => {
                output.push_str("static_cast<u64>(");
                output.push_str(&value.to_string());
                output.push_str("ULL)");
            }
        },
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
            if call.name == "println" {
                output.push_str("outln(\"{}\", ");
                for param in &call.args {
                    output.push_str(&codegen_expr(indent, &param.1, project));
                }
                output.push(')');
            } else if call.name == "eprintln" {
                output.push_str("warnln(\"{}\", ");
                for param in &call.args {
                    output.push_str(&codegen_expr(indent, &param.1, project));
                }
                output.push(')');
            } else {
                for namespace in &call.namespace {
                    output.push_str(namespace);
                    output.push_str("::")
                }

                output.push_str(&call.name);
                output.push('(');

                let mut first = true;
                for param in &call.args {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    output.push_str(&codegen_expr(indent, &param.1, project));
                }
                output.push(')');
            }
        }
        CheckedExpression::MethodCall(expr, call, ..) => {
            output.push('(');

            output.push('(');
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(")");

            match &**expr {
                CheckedExpression::Var(CheckedVariable { name, .. }) if name == "this" => {
                    output.push_str("->");
                }
                _ => output.push('.'),
            }

            output.push_str(&call.name);
            output.push('(');
            let mut first = true;
            for param in &call.args {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&codegen_expr(indent, &param.1, project));
            }
            output.push_str("))");
        }
        CheckedExpression::UnaryOp(expr, op, ty) => {
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
                UnaryOperator::Dereference => {
                    output.push_str("*");
                }
                UnaryOperator::RawAddress => {
                    output.push_str("&");
                }
                UnaryOperator::LogicalNot => {
                    output.push_str("!");
                }
                UnaryOperator::BitwiseNot => {
                    output.push_str("~");
                }
                UnaryOperator::TypeCast(cast) => {
                    match cast {
                        TypeCast::Fallible(_) => {
                            if ty.is_integer() {
                                output.push_str("fallible_integer_cast");
                            } else {
                                output.push_str("dynamic_cast");
                            }
                        }
                        TypeCast::Infallible(_) => {
                            if ty.is_integer() {
                                output.push_str("infallible_integer_cast");
                            } else {
                                output.push_str("verify_cast");
                            }
                        }
                        TypeCast::Saturating(_) => {
                            if ty.is_integer() {
                                output.push_str("saturating_integer_cast");
                            } else {
                                panic!("Saturating cast on non-integer type");
                            }
                        }
                        TypeCast::Truncating(_) => {
                            if ty.is_integer() {
                                output.push_str("truncating_integer_cast");
                            } else {
                                panic!("Truncating cast on non-integer type");
                            }
                        }
                    }
                    output.push('<');
                    output.push_str(&codegen_type(ty, project));
                    output.push_str(">(");
                }
                _ => {}
            }
            output.push_str(&codegen_expr(indent, expr, project));
            match op {
                UnaryOperator::PostIncrement => {
                    output.push_str("++");
                }
                UnaryOperator::PostDecrement => {
                    output.push_str("--");
                }
                UnaryOperator::TypeCast(_) => {
                    output.push(')');
                }
                _ => {}
            }
            output.push(')');
        }
        CheckedExpression::BinaryOp(lhs, op, rhs, ..) => {
            output.push('(');
            output.push_str(&codegen_expr(indent, lhs, project));
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
                BinaryOperator::BitwiseAndAssign => output.push_str(" &= "),
                BinaryOperator::BitwiseOrAssign => output.push_str(" |= "),
                BinaryOperator::BitwiseXorAssign => output.push_str(" ^= "),
                BinaryOperator::BitwiseLeftShiftAssign => output.push_str(" <<= "),
                BinaryOperator::BitwiseRightShiftAssign => output.push_str(" >>= "),
                BinaryOperator::Equal => output.push_str(" == "),
                BinaryOperator::NotEqual => output.push_str(" != "),
                BinaryOperator::LessThan => output.push_str(" < "),
                BinaryOperator::LessThanOrEqual => output.push_str(" <= "),
                BinaryOperator::GreaterThan => output.push_str(" > "),
                BinaryOperator::GreaterThanOrEqual => output.push_str(" >= "),
                BinaryOperator::LogicalAnd => output.push_str(" && "),
                BinaryOperator::LogicalOr => output.push_str(" || "),
                BinaryOperator::BitwiseAnd => output.push_str(" & "),
                BinaryOperator::BitwiseOr => output.push_str(" | "),
                BinaryOperator::BitwiseXor => output.push_str(" ^ "),
                BinaryOperator::BitwiseLeftShift => output.push_str(" << "),
                BinaryOperator::BitwiseRightShift => output.push_str(" >> "),
            }
            output.push_str(&codegen_expr(indent, rhs, project));
            output.push(')');
        }
        CheckedExpression::Vector(vals, fill_size_expr, _) => {
            if let Some(fill_size_expr) = fill_size_expr {
                output.push_str("(RefVector<");
                output.push_str(&codegen_type(&vals.first().unwrap().ty(), project));
                output.push_str(">::filled(");
                output.push_str(&codegen_expr(indent, fill_size_expr, project));
                output.push_str(", ");
                output.push_str(&codegen_expr(indent, vals.first().unwrap(), project));
                output.push_str("))");
            } else {
                // (RefVector({1, 2, 3}))
                output.push_str("(RefVector({");
                let mut first = true;
                for val in vals {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    output.push_str(&codegen_expr(indent, val, project))
                }
                output.push_str("}))");
            }
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

                output.push_str(&codegen_expr(indent, val, project))
            }
            output.push_str("})");
        }
        CheckedExpression::IndexedExpression(expr, idx, _) => {
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(")[");
            output.push_str(&codegen_expr(indent, idx, project));
            output.push_str("])");
        }
        CheckedExpression::IndexedTuple(expr, idx, _) => {
            // x.get<1>()
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(&format!(").get<{}>())", idx));
        }
        CheckedExpression::IndexedStruct(expr, name, _) => {
            // x.get<1>()
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push(')');
            match &**expr {
                CheckedExpression::Var(CheckedVariable { name, .. }) if name == "this" => {
                    output.push_str("->");
                }
                _ => output.push('.'),
            }

            output.push_str(&format!("{})", name));
        }
        CheckedExpression::Garbage => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}
