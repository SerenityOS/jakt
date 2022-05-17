use crate::{
    compiler,
    parser::{BinaryOperator, DefinitionLinkage, DefinitionType, FunctionLinkage},
    typechecker::{
        is_integer, CheckedBlock, CheckedExpression, CheckedFunction, CheckedStatement,
        CheckedStruct, CheckedTypeCast, CheckedUnaryOperator, CheckedVariable, NumericConstant,
        Project, Scope, Type, TypeId,
    },
};

const INDENT_SIZE: usize = 4;

pub fn codegen(project: &Project, scope: &Scope) -> String {
    let mut output = String::new();

    output.push_str("#include \"runtime/lib.h\"\n");

    for (_, struct_id) in &scope.structs {
        let structure = &project.structs[*struct_id];
        let struct_output = codegen_struct_predecl(structure, project);

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

fn codegen_struct_predecl(structure: &CheckedStruct, project: &Project) -> String {
    if structure.definition_linkage == DefinitionLinkage::External {
        String::new()
    } else {
        let mut output = String::new();

        if !structure.generic_parameters.is_empty() {
            output.push_str("template <");
        }
        let mut first = true;
        for generic_parameter in &structure.generic_parameters {
            if !first {
                output.push_str(", ");
            } else {
                first = false;
            }
            output.push_str("typename ");
            output.push_str(&codegen_type(*generic_parameter, project))
        }
        if !structure.generic_parameters.is_empty() {
            output.push_str(">\n");
        }
        match structure.definition_type {
            DefinitionType::Class => {
                output.push_str(&format!("class {};", structure.name));
            }
            DefinitionType::Struct => {
                output.push_str(&format!("struct {};", structure.name));
            }
        }

        output
    }
}

fn codegen_struct(structure: &CheckedStruct, project: &Project) -> String {
    let mut output = String::new();

    if structure.definition_linkage == DefinitionLinkage::External {
        return output;
    }
    if !structure.generic_parameters.is_empty() {
        output.push_str("template <");
    }
    let mut first = true;
    for generic_parameter in &structure.generic_parameters {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }
        output.push_str("typename ");
        output.push_str(&codegen_type(*generic_parameter, project))
    }
    if !structure.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    match structure.definition_type {
        DefinitionType::Class => {
            output.push_str(&format!(
                "class {} : public RefCounted<{}> {{\n",
                structure.name, structure.name
            ));
            // As we should test the visibility before codegen, we take a simple
            // approach to codegen
            output.push_str("  public:\n");

            // Make sure emitted classes always have a vtable.
            output.push_str(&format!("    virtual ~{}() = default;", structure.name));
        }
        DefinitionType::Struct => {
            output.push_str(&format!("struct {}", structure.name));
            output.push_str(" {\n");
            output.push_str("  public:\n");
        }
    }

    for field in &structure.fields {
        output.push_str(&" ".repeat(INDENT_SIZE));

        output.push_str(&codegen_type(field.ty, project));
        output.push(' ');
        output.push_str(&field.name);
        output.push_str(";\n");
    }

    let scope = &project.scopes[structure.scope_id];
    for (_, fun_id) in &scope.funs {
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

    if !fun.generic_parameters.is_empty() {
        output.push_str("template <");
    }
    let mut first = true;
    for generic_parameter in &fun.generic_parameters {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }
        output.push_str("typename ");
        output.push_str(&codegen_type(*generic_parameter, project))
    }
    if !fun.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&codegen_type(fun.return_type, project));
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
        let ty = codegen_type(param.variable.ty, project);
        output.push_str(&ty);
        output.push(' ');
        output.push_str(&param.variable.name);
    }
    output.push_str(");");

    output
}

fn codegen_function(fun: &CheckedFunction, project: &Project) -> String {
    let mut output = String::new();

    if !fun.generic_parameters.is_empty() {
        output.push_str("template <");
    }
    let mut first = true;
    for generic_parameter in &fun.generic_parameters {
        if !first {
            output.push_str(", ");
        } else {
            first = false;
        }
        output.push_str("typename ");
        output.push_str(&codegen_type(*generic_parameter, project))
    }
    if !fun.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    if fun.name == "main" {
        output.push_str("int");
    } else {
        output.push_str(&codegen_type(fun.return_type, project));
    }
    output.push(' ');
    if fun.name == "main" {
        output.push_str("__jakt_main");
    } else {
        output.push_str(&fun.name);
    }
    output.push('(');

    if fun.name == "main" && fun.params.is_empty() {
        output.push_str("Array<String>");
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

        let ty = codegen_type(param.variable.ty, project);
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
    let type_id = fun.return_type;
    let ty = &project.types[type_id];

    match ty {
        Type::Struct(struct_id) => {
            let structure = &project.structs[*struct_id];

            if structure.definition_type == DefinitionType::Class {
                let mut output = format!("static NonnullRefPtr<{}> create", fun.name);

                output.push('(');

                let mut first = true;
                for param in &fun.params {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    let ty = codegen_type(param.variable.ty, project);
                    output.push_str(&ty);
                    output.push(' ');
                    output.push_str(&param.variable.name);
                }
                output.push_str(&format!(") {{ auto o = adopt_ref(*new {}); ", fun.name));

                for param in &fun.params {
                    output.push_str("o->");
                    output.push_str(&param.variable.name);
                    output.push_str(" = ");
                    output.push_str(&param.variable.name);
                    output.push_str("; ");
                }

                output.push_str("return o; }");

                output
            } else {
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

                    let ty = codegen_type(param.variable.ty, project);
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
        }
        _ => {
            panic!("internal error: call to a constructor, but not a struct/class type")
        }
    }
}

fn codegen_struct_type(type_id: TypeId, project: &Project) -> String {
    let ty = &project.types[type_id];

    match ty {
        Type::Struct(struct_id) => project.structs[*struct_id].name.clone(),
        _ => panic!("codegen_struct_type on non-struct"),
    }
}

fn codegen_type(type_id: TypeId, project: &Project) -> String {
    let ty = &project.types[type_id];
    match ty {
        Type::RawPtr(ty) => {
            format!("{}*", codegen_type(*ty, project))
        }
        Type::GenericInstance(struct_id, inner_tys) => {
            let mut output = project.structs[*struct_id].name.clone();
            output.push('<');
            let mut first = true;
            for ty in inner_tys {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&codegen_type(*ty, project));
            }

            output.push('>');
            output
        }
        Type::Struct(struct_id) => {
            if project.structs[*struct_id].definition_type == DefinitionType::Class {
                format!("NonnullRefPtr<{}>", project.structs[*struct_id].name)
            } else {
                project.structs[*struct_id].name.clone()
            }
        }
        Type::Builtin => match type_id {
            compiler::USIZE_TYPE_ID => String::from("size_t"),
            compiler::BOOL_TYPE_ID => String::from("bool"),
            compiler::STRING_TYPE_ID => String::from("String"),
            compiler::CCHAR_TYPE_ID => String::from("char"),
            compiler::CINT_TYPE_ID => String::from("int"),
            compiler::I8_TYPE_ID => String::from("i8"),
            compiler::I16_TYPE_ID => String::from("i16"),
            compiler::I32_TYPE_ID => String::from("i32"),
            compiler::I64_TYPE_ID => String::from("i64"),
            compiler::U8_TYPE_ID => String::from("u8"),
            compiler::U16_TYPE_ID => String::from("u16"),
            compiler::U32_TYPE_ID => String::from("u32"),
            compiler::U64_TYPE_ID => String::from("u64"),
            compiler::F32_TYPE_ID => String::from("f32"),
            compiler::F64_TYPE_ID => String::from("f64"),
            compiler::VOID_TYPE_ID => String::from("void"),
            _ => String::from("auto"),
        },
        Type::TypeVariable(name) => name.clone(),
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
        CheckedStatement::For(iterator_name, range_expr, block) => {
            output.push_str("{ auto&& _range = ");
            output.push_str(&codegen_expr(indent, range_expr, project));
            output.push_str("; for(auto ");
            output.push_str(iterator_name);
            output.push(' ');
            output.push_str(" = _range.start;");
            output.push_str(iterator_name);
            output.push_str("!= _range.end;");
            output.push_str(iterator_name);
            output.push_str("++");
            output.push_str(") {");
            output.push_str(&codegen_block(indent, block, project));
            output.push_str("}}");
        }
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
            //output.push_str(&codegen_type(var_decl.ty, project));
            output.push_str("auto ");
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
        CheckedExpression::Range(start_expr, end_expr, _, type_id) => {
            let index_type;

            let ty = &project.types[*type_id];
            match ty {
                Type::GenericInstance(_, v) => {
                    index_type = v[0];
                }
                _ => {
                    panic!("Interal error: range expression doesn't have Range type");
                }
            }

            output.push_str("(");
            output.push_str(&codegen_type(*type_id, project));
            output.push_str("{");
            output.push_str("static_cast<");
            output.push_str(&codegen_type(index_type, project));
            output.push_str(">(");
            output.push_str(&codegen_expr(indent, start_expr, project));
            output.push_str("),static_cast<");
            output.push_str(&codegen_type(index_type, project));
            output.push_str(">(");
            output.push_str(&codegen_expr(indent, end_expr, project));
            output.push_str(")})");
        }
        CheckedExpression::OptionalNone(_, _) => {
            output.push_str("{}");
        }
        CheckedExpression::OptionalSome(expr, _, _) => {
            output.push('(');
            output.push_str(&codegen_expr(indent, expr, project));
            output.push(')');
        }
        CheckedExpression::ForcedUnwrap(expr, _, _) => {
            output.push('(');
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(".value())");
        }
        CheckedExpression::QuotedString(qs, _) => {
            output.push_str("String(\"");
            output.push_str(qs);
            output.push_str("\")");
        }
        CheckedExpression::CharacterConstant(c, _) => {
            output.push('\'');
            output.push(*c);
            output.push('\'');
        }
        CheckedExpression::NumericConstant(constant, _, _) => match constant {
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
            NumericConstant::USize(value) => {
                output.push_str("static_cast<size_t>(");
                output.push_str(&value.to_string());
                output.push_str("ULL)");
            }
        },
        CheckedExpression::Var(var, ..) => {
            output.push_str(&var.name);
        }
        CheckedExpression::Boolean(bool, _) => {
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
                for (idx, namespace) in call.namespace.iter().enumerate() {
                    // hack warning: this is to get around C++'s limitation that a constructor
                    // can't be called like other static methods
                    if idx == call.namespace.len() - 1 && namespace == &call.name {
                        break;
                    }
                    output.push_str(namespace);
                    output.push_str("::")
                }

                if call.linkage == FunctionLinkage::ImplicitConstructor {
                    let type_id = call.ty;
                    let ty = &project.types[type_id];
                    match ty {
                        Type::Struct(struct_id) => {
                            let structure = &project.structs[*struct_id];

                            if structure.definition_type == DefinitionType::Class {
                                output.push_str(&call.name);
                                output.push_str("::");
                                output.push_str("create");
                            } else {
                                output.push_str(&call.name);
                            }
                        }
                        _ => {
                            panic!("internal error: constructor expected class or struct type")
                        }
                    }
                } else {
                    output.push_str(&call.name);
                }

                if !call.type_args.is_empty() {
                    output.push('<');
                    let mut first = true;
                    for type_arg in &call.type_args {
                        if !first {
                            output.push_str(", ")
                        } else {
                            first = false;
                        }

                        output.push_str(&codegen_type(*type_arg, project));
                    }
                    output.push('>');
                }

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
                CheckedExpression::Var(CheckedVariable { name, .. }, _) if name == "this" => {
                    output.push_str("->");
                }
                x => match &project.types[x.ty()] {
                    Type::RawPtr(_) => {
                        output.push_str("->");
                    }
                    Type::Struct(struct_id) => {
                        let structure = &project.structs[*struct_id];

                        if structure.definition_type == DefinitionType::Class {
                            output.push_str("->");
                        } else {
                            output.push('.');
                        }
                    }
                    _ => {
                        output.push('.');
                    }
                },
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
        CheckedExpression::UnaryOp(expr, op, _, type_id) => {
            output.push('(');
            match op {
                CheckedUnaryOperator::PreIncrement => {
                    output.push_str("++");
                }
                CheckedUnaryOperator::PreDecrement => {
                    output.push_str("--");
                }
                CheckedUnaryOperator::Negate => {
                    output.push_str("-");
                }
                CheckedUnaryOperator::Dereference => {
                    output.push_str("*");
                }
                CheckedUnaryOperator::RawAddress => {
                    output.push_str("&");
                }
                CheckedUnaryOperator::LogicalNot => {
                    output.push_str("!");
                }
                CheckedUnaryOperator::BitwiseNot => {
                    output.push_str("~");
                }
                CheckedUnaryOperator::Is(type_id) => {
                    output.push_str("is<");
                    output.push_str(&codegen_struct_type(*type_id, project));
                    output.push_str(">(");
                }
                CheckedUnaryOperator::TypeCast(cast) => {
                    match cast {
                        CheckedTypeCast::Fallible(_) => {
                            if is_integer(*type_id) {
                                output.push_str("fallible_integer_cast");
                            } else {
                                output.push_str("dynamic_cast");
                            }
                        }
                        CheckedTypeCast::Infallible(_) => {
                            if is_integer(*type_id) {
                                output.push_str("infallible_integer_cast");
                            } else {
                                output.push_str("verify_cast");
                            }
                        }
                        CheckedTypeCast::Saturating(_) => {
                            if is_integer(*type_id) {
                                output.push_str("saturating_integer_cast");
                            } else {
                                panic!("Saturating cast on non-integer type");
                            }
                        }
                        CheckedTypeCast::Truncating(_) => {
                            if is_integer(*type_id) {
                                output.push_str("truncating_integer_cast");
                            } else {
                                panic!("Truncating cast on non-integer type");
                            }
                        }
                    }
                    output.push('<');
                    output.push_str(&codegen_type(*type_id, project));
                    output.push_str(">(");
                }
                _ => {}
            }
            output.push_str(&codegen_expr(indent, expr, project));
            match op {
                CheckedUnaryOperator::PostIncrement => {
                    output.push_str("++");
                }
                CheckedUnaryOperator::PostDecrement => {
                    output.push_str("--");
                }
                CheckedUnaryOperator::TypeCast(_) | CheckedUnaryOperator::Is(_) => {
                    output.push(')');
                }
                _ => {}
            }
            output.push(')');
        }
        CheckedExpression::BinaryOp(lhs, op, rhs, ..) => {
            output.push('(');

            match op {
                BinaryOperator::ArithmeticRightShift => {
                    output.push_str("__arithmetic_shift_right(");
                    output.push_str(&codegen_expr(indent, lhs, project));
                    output.push_str(", ");
                    output.push_str(&codegen_expr(indent, rhs, project));
                    output.push(')');
                }
                _ => {
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
                        BinaryOperator::ArithmeticLeftShift => output.push_str(" << "),
                        BinaryOperator::BitwiseLeftShift => output.push_str(" << "),
                        BinaryOperator::BitwiseRightShift => output.push_str(" >> "),
                        _ => {}
                    }
                    output.push_str(&codegen_expr(indent, rhs, project));
                }
            }
            output.push(')');
        }
        CheckedExpression::Array(vals, fill_size_expr, _, _) => {
            if let Some(fill_size_expr) = fill_size_expr {
                output.push_str("(Array<");
                output.push_str(&codegen_type(vals.first().unwrap().ty(), project));
                output.push_str(">::filled(");
                output.push_str(&codegen_expr(indent, fill_size_expr, project));
                output.push_str(", ");
                output.push_str(&codegen_expr(indent, vals.first().unwrap(), project));
                output.push_str("))");
            } else {
                // (Array({1, 2, 3}))
                output.push_str("(Array({");
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
        CheckedExpression::Tuple(vals, _, _) => {
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
        CheckedExpression::IndexedExpression(expr, idx, _, _) => {
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(")[");
            output.push_str(&codegen_expr(indent, idx, project));
            output.push_str("])");
        }
        CheckedExpression::IndexedTuple(expr, idx, _, _) => {
            // x.get<1>()
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(&format!(").get<{}>())", idx));
        }
        CheckedExpression::IndexedStruct(expr, name, _, _) => {
            // x.foo or x->foo
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push(')');

            match &**expr {
                CheckedExpression::Var(CheckedVariable { name, .. }, _) if name == "this" => {
                    output.push_str("->");
                }
                x => match &project.types[x.ty()] {
                    Type::RawPtr(_) => {
                        output.push_str("->");
                    }
                    Type::Struct(struct_id) => {
                        let structure = &project.structs[*struct_id];

                        if structure.definition_type == DefinitionType::Class {
                            output.push_str("->");
                        } else {
                            output.push('.');
                        }
                    }
                    _ => {
                        output.push('.');
                    }
                },
            }

            output.push_str(&format!("{})", name));
        }
        CheckedExpression::Garbage(_) => {
            // Incorrect parse/typecheck
            // Probably shouldn't be able to get to this point?
        }
    }

    output
}
