use crate::compiler::{UNKNOWN_TYPE_ID, VOID_TYPE_ID};
use crate::typechecker::{
    CheckedEnum, CheckedEnumVariant, CheckedMatchBody, CheckedMatchCase, FunctionGenericParameter,
    ScopeId,
};
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

    output.push_str(&codegen_namespace(project, scope));

    output
}

fn codegen_namespace(project: &Project, scope: &Scope) -> String {
    let mut output = String::new();

    // Output the namespaces (and their children)
    for child_scope_id in &scope.children {
        // For now, require children of the current namespace to have names before being emitted
        let child_scope = &project.scopes[*child_scope_id];
        if let Some(name) = &child_scope.namespace_name {
            output.push_str(&format!("namespace {} {{\n", name));
            output.push_str(&codegen_namespace(project, child_scope));
            output.push_str("}\n");
        }
    }

    for (_, struct_id) in &scope.structs {
        let structure = &project.structs[*struct_id];
        let struct_output = codegen_struct_predecl(structure, project);

        if !struct_output.is_empty() {
            output.push_str(&struct_output);
            output.push('\n');
        }
    }

    for (_, enum_id) in &scope.enums {
        let enum_ = &project.enums[*enum_id];
        let enum_output = codegen_enum_predecl(enum_, project);

        if !enum_output.is_empty() {
            output.push_str(&enum_output);
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

    for (_, function_id) in &scope.functions {
        let function = &project.functions[*function_id];
        if function.linkage == FunctionLinkage::ImplicitEnumConstructor {
            continue;
        }

        let function_output = codegen_function_predecl(function, project);

        if function.linkage != FunctionLinkage::ImplicitConstructor && function.name != "main" {
            output.push_str(&function_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for (_, function_id) in &scope.functions {
        let function = &project.functions[*function_id];
        if function.linkage == FunctionLinkage::External
            || function.linkage == FunctionLinkage::ImplicitConstructor
            || function.linkage == FunctionLinkage::ImplicitEnumConstructor
        {
            continue;
        } else {
            let function_output = codegen_function(function, project);

            output.push_str(&function_output);
            output.push('\n');
        }
    }

    output
}
fn codegen_enum_predecl(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.underlying_type.is_some() {
        let ty = enum_.underlying_type.unwrap();
        if is_integer(ty) {
            let mut output = String::new();

            output.push_str("enum class ");
            output.push_str(&enum_.name);
            output.push_str(": ");
            output.push_str(&codegen_type(ty, project));
            output.push_str(" {\n");
            for variant in &enum_.variants {
                match variant {
                    CheckedEnumVariant::Untyped(name, _) => {
                        output.push_str("    ");
                        output.push_str(name);
                        output.push_str(",\n");
                    }
                    CheckedEnumVariant::WithValue(name, value, _) => {
                        output.push_str("    ");
                        output.push_str(name);
                        output.push_str(" = ");
                        output.push_str(&codegen_expr(0, value, project));
                        output.push_str(",\n");
                    }
                    _ => unreachable!(),
                }
            }
            output.push_str("};\n");
            return output;
        } else {
            todo!("Enums with a non-integer underlying type")
        }
    }

    // These are all Variant<Ts...>, make a new namespace and define the variant types first.
    let is_generic = !enum_.generic_parameters.is_empty();
    let generic_parameter_names = enum_
        .generic_parameters
        .iter()
        .map(|p| match &project.types[*p] {
            Type::TypeVariable(name) => name.clone(),
            _ => unreachable!(),
        })
        .collect::<Vec<_>>();
    let template_args = generic_parameter_names
        .iter()
        .map(|p| "typename ".to_string() + p)
        .collect::<Vec<_>>()
        .join(", ");

    let mut output = String::new();
    output.push_str("namespace ");
    output.push_str(&enum_.name);
    output.push_str("_Details {\n");
    for variant in &enum_.variants {
        match variant {
            CheckedEnumVariant::StructLike(name, members, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(" {\n");
                for member in members {
                    output.push_str("        ");
                    output.push_str(&codegen_type(member.ty, project));
                    output.push(' ');
                    output.push_str(&member.name);
                    output.push_str(";\n");
                }
                output.push('\n');
                output.push_str("        template<");
                for i in 0..members.len() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    output.push_str("typename _MemberT");
                    output.push_str(&i.to_string());
                }
                output.push_str(">\n");
                output.push_str("        ");
                output.push_str(name);
                output.push('(');
                for i in 0..members.len() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    output.push_str("_MemberT");
                    output.push_str(&i.to_string());
                    output.push_str("&& member_");
                    output.push_str(&i.to_string());
                }
                output.push_str("):\n");
                for (i, member) in members.iter().enumerate() {
                    output.push_str("            ");
                    output.push_str(&member.name);
                    output.push_str("{ forward<_MemberT");
                    output.push_str(&i.to_string());
                    output.push_str(">(member_");
                    output.push_str(&i.to_string());
                    output.push_str(")}");
                    if i < members.len() - 1 {
                        output.push_str(",\n");
                    } else {
                        output.push('\n');
                    }
                }
                output.push_str("    {}\n");
                output.push_str("};\n");
            }
            CheckedEnumVariant::Untyped(name, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(" {};\n");
            }
            CheckedEnumVariant::Typed(name, type_id, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(" {\n");
                output.push_str("        ");
                output.push_str(&codegen_type(*type_id, project));
                output.push_str(" value;\n");
                output.push('\n');
                output.push_str("        template<typename... Args>\n");
                output.push_str("        ");
                output.push_str(name);
                output.push_str("(Args&&... args): ");
                output.push_str(" value { forward<Args>(args)... } {}\n");
                output.push_str("    };\n");
            }
            _ => (),
        }
    }
    output.push_str("}\n");

    // Now define the variant itself.
    if is_generic {
        output.push_str("template<");
        output.push_str(template_args.as_str());
        output.push_str(">\n");
    }
    output.push_str("struct ");
    output.push_str(&enum_.name);
    output.push_str(" : public Variant<");
    let mut variant_args = String::new();
    let mut first = true;
    let mut variant_names = Vec::new();
    for variant in &enum_.variants {
        if first {
            first = false;
        } else {
            variant_args.push_str(", ");
        }
        match variant {
            CheckedEnumVariant::StructLike(name, _, _)
            | CheckedEnumVariant::Untyped(name, _)
            | CheckedEnumVariant::Typed(name, _, _) => {
                variant_args.push_str(&enum_.name);
                variant_args.push_str("_Details::");
                variant_args.push_str(name);
                variant_names.push(name.clone());
                if is_generic {
                    variant_args.push('<');
                    variant_args.push_str(generic_parameter_names.join(", ").as_str());
                    variant_args.push('>');
                }
            }
            _ => unreachable!(),
        }
    }

    output.push_str(&variant_args);
    output.push_str("> {\n");

    output.push_str("    using Variant<");
    output.push_str(&variant_args);
    output.push_str(">::Variant;\n");

    for name in &variant_names {
        output.push_str("    using ");
        output.push_str(name);
        output.push_str(" = ");
        output.push_str(&enum_.name);
        output.push_str("_Details::");
        output.push_str(name);
        if is_generic {
            output.push('<');
            output.push_str(generic_parameter_names.join(", ").as_str());
            output.push('>');
        }
        output.push_str(";\n");
    }

    output.push_str("};\n");

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
    for (_, function_id) in &scope.functions {
        let function = &project.functions[*function_id];
        if function.linkage == FunctionLinkage::ImplicitConstructor {
            let function_output = codegen_constructor(function, project);

            output.push_str(&" ".repeat(INDENT_SIZE));
            output.push_str(&function_output);
            output.push('\n');
        } else {
            output.push_str(&" ".repeat(INDENT_SIZE));
            if function.is_static() {
                output.push_str("static ");
            }
            let method_output = codegen_function(function, project);
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
        let id = match generic_parameter {
            FunctionGenericParameter::InferenceGuide(id)
            | FunctionGenericParameter::Parameter(id) => *id,
        };
        output.push_str(&codegen_type(id, project))
    }
    if !fun.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    if fun.name == "main" {
        output.push_str("ErrorOr<int>");
    } else {
        let return_type = if fun.throws {
            format!("ErrorOr<{}>", &codegen_type(fun.return_type, project))
        } else {
            codegen_type(fun.return_type, project)
        };

        output.push_str(&return_type);
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
        let id = match generic_parameter {
            FunctionGenericParameter::InferenceGuide(id)
            | FunctionGenericParameter::Parameter(id) => *id,
        };
        output.push_str(&codegen_type(id, project))
    }
    if !fun.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    if fun.name == "main" {
        output.push_str("ErrorOr<int>");
    } else {
        let return_type = if fun.throws {
            format!("ErrorOr<{}>", &codegen_type(fun.return_type, project))
        } else {
            codegen_type(fun.return_type, project)
        };

        output.push_str(&return_type);
    }
    output.push(' ');
    if fun.name == "main" {
        output.push_str("_jakt_main");
    } else {
        output.push_str(&fun.name);
    }
    output.push('(');

    if fun.name == "main" && fun.params.is_empty() {
        output.push_str("Array<String>");
    }

    let mut first = true;
    let mut const_function = false;

    for param in &fun.params {
        if param.variable.name == "this" {
            const_function = !param.variable.mutable;
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

    if const_function {
        output.push_str(" const");
    }

    if fun.name == "main" {
        output.push('\n');
        output.push_str("{\n");
        output.push_str(&" ".repeat(INDENT_SIZE));
    }

    // Put the return type in scope.
    if fun.name == "main" {
        output.push_str("using _JaktCurrentFunctionReturnType = ErrorOr<int>;\n");
    } else {
        let return_type = fun.return_type;
        if return_type == UNKNOWN_TYPE_ID {
            panic!("Function type unknown at codegen time in {}", fun.name);
        }
        output.push_str("{\n");
        if fun.throws {
            output.push_str(&format!(
                "using _JaktCurrentFunctionReturnType = ErrorOr<{}>;\n",
                codegen_type(fun.return_type, project)
            ));
        } else {
            output.push_str(&format!(
                "using _JaktCurrentFunctionReturnType = {};\n",
                codegen_type(fun.return_type, project)
            ));
        }
    }

    let block = codegen_block(INDENT_SIZE, &fun.block, project);
    output.push_str(&block);

    if fun.name == "main" {
        output.push_str(&" ".repeat(INDENT_SIZE));
        output.push_str("return 0;\n");
    }

    output.push_str("}\n");

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
                output.push_str(") ");

                if !fun.params.is_empty() {
                    output.push(':');
                }

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

pub fn codegen_namespace_qualifier(scope_id: ScopeId, project: &Project) -> String {
    let mut output = String::new();

    let mut current_scope_id = project.scopes[scope_id].parent.clone();

    while let Some(current) = current_scope_id {
        // Walk backward, prepending the parents with names to the current output
        if let Some(namespace_name) = &project.scopes[current].namespace_name {
            output.insert_str(0, &format!("{}::", namespace_name));
        }

        current_scope_id = project.scopes[current].parent;
    }

    output
}

pub fn codegen_type(type_id: TypeId, project: &Project) -> String {
    let mut output = String::new();
    let ty = &project.types[type_id];
    match ty {
        Type::RawPtr(ty) => {
            format!("{}*", codegen_type(*ty, project))
        }
        Type::GenericInstance(struct_id, inner_tys) => {
            output.push_str(&codegen_namespace_qualifier(
                project.structs[*struct_id].scope_id,
                project,
            ));
            output.push_str(&project.structs[*struct_id].name.clone());
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
        Type::GenericEnumInstance(enum_id, inner_tys) => {
            output.push_str(&codegen_namespace_qualifier(
                project.enums[*enum_id].scope_id,
                project,
            ));
            output.push_str(&project.enums[*enum_id].name);
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
                output.push_str("NonnullRefPtr<");
                output.push_str(&codegen_namespace_qualifier(
                    project.structs[*struct_id].scope_id,
                    project,
                ));
                output.push_str(&project.structs[*struct_id].name);
                output.push('>');
            } else {
                output.push_str(&codegen_namespace_qualifier(
                    project.structs[*struct_id].scope_id,
                    project,
                ));
                output.push_str(&project.structs[*struct_id].name);
            }

            output
        }
        Type::Enum(enum_id) => {
            output.push_str(&codegen_namespace_qualifier(
                project.enums[*enum_id].scope_id,
                project,
            ));
            output.push_str(&project.enums[*enum_id].name);

            output
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
        CheckedStatement::Try(stmt, error_name, catch_block) => {
            output.push('{');
            output.push_str("auto _jakt_try_result = [&]() -> ErrorOr<void> {");
            output.push_str(&codegen_statement(indent, stmt, project));
            output.push(';');
            output.push_str("return {};");
            output.push_str("}();");
            output.push_str("if (_jakt_try_result.is_error()) {");
            output.push_str("auto ");
            output.push_str(error_name);
            output.push_str(" = _jakt_try_result.release_error();");
            output.push_str(&codegen_block(indent, catch_block, project));
            output.push('}');
            output.push('}');
        }
        CheckedStatement::Throw(expr) => {
            output.push_str("return ");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push(';');
        }
        CheckedStatement::Continue => {
            output.push_str("continue;");
        }
        CheckedStatement::Break => {
            output.push_str("break;");
        }
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
            output.push_str("ScopeGuard __SCOPE_GUARD_NAME ([&] \n");
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
        CheckedStatement::Loop(block) => {
            output.push_str("for (;;) {");
            let block = codegen_block(indent, block, project);
            output.push_str(&block);
            output.push('}');
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
            output.push_str(&codegen_type(var_decl.ty, project));
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
        CheckedStatement::InlineCpp(strings) => {
            for string in strings {
                output.push_str(&string.replace("\\\"", "\"").replace("\\\\", "\\"))
            }
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
            let ty = &project.types[*type_id];
            let index_type = match ty {
                Type::GenericInstance(_, v) => v[0],
                _ => panic!("Interal error: range expression doesn't have Range type"),
            };

            output.push('(');
            output.push_str(&codegen_type(*type_id, project));
            output.push('{');
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
                output.push(')');
            }
            NumericConstant::I16(value) => {
                output.push_str("static_cast<i16>(");
                output.push_str(&value.to_string());
                output.push(')');
            }
            NumericConstant::I32(value) => {
                output.push_str("static_cast<i32>(");
                output.push_str(&value.to_string());
                output.push(')');
            }
            NumericConstant::I64(value) => {
                output.push_str("static_cast<i64>(");
                output.push_str(&value.to_string());
                output.push_str("LL)");
            }
            NumericConstant::U8(value) => {
                output.push_str("static_cast<u8>(");
                output.push_str(&value.to_string());
                output.push(')');
            }
            NumericConstant::U16(value) => {
                output.push_str("static_cast<u16>(");
                output.push_str(&value.to_string());
                output.push(')');
            }
            NumericConstant::U32(value) => {
                output.push_str("static_cast<u32>(");
                output.push_str(&value.to_string());
                output.push(')');
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
            if call.callee_throws {
                output.push_str("TRY(");
            }
            if call.name == "println" {
                output.push_str("outln(");
                for (i, param) in call.args.iter().enumerate() {
                    output.push_str(&codegen_expr(indent, &param.1, project));
                    if i != call.args.len() - 1 {
                        output.push(',');
                    }
                }
                output.push(')');
            } else if call.name == "eprintln" {
                output.push_str("warnln(");
                for (i, param) in call.args.iter().enumerate() {
                    output.push_str(&codegen_expr(indent, &param.1, project));
                    if i != call.args.len() - 1 {
                        output.push(',');
                    }
                }
                output.push(')');
            } else {
                for (idx, namespace) in call.namespace.iter().enumerate() {
                    // hack warning: this is to get around C++'s limitation that a constructor
                    // can't be called like other static methods
                    if idx == call.namespace.len() - 1 && namespace.name == call.name {
                        break;
                    }
                    if call.linkage == FunctionLinkage::ImplicitEnumConstructor {
                        output.push_str("typename ");
                    }
                    output.push_str(namespace.name.as_str());
                    if let Some(params) = &namespace.generic_parameters {
                        output.push('<');
                        for (i, param) in params.iter().enumerate() {
                            output.push_str(&codegen_type(*param, project));
                            if i != params.len() - 1 {
                                output.push(',');
                            }
                        }
                        output.push('>');
                    }
                    output.push_str("::")
                }

                if call.linkage == FunctionLinkage::ImplicitConstructor {
                    let type_id = call.ty;
                    let ty = &project.types[type_id];
                    match ty {
                        Type::Struct(struct_id) | Type::GenericInstance(struct_id, _) => {
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
            if call.callee_throws {
                output.push(')');
            }
        }
        CheckedExpression::MethodCall(expr, call, ..) => {
            if call.callee_throws {
                output.push_str("TRY(");
            }

            output.push('(');

            output.push('(');
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

            if call.callee_throws {
                output.push(')');
            }
        }
        CheckedExpression::Match(expr, cases, _, return_ty) => {
            let expr_type = &project.types[expr.ty()];
            let id = match expr_type {
                Type::GenericEnumInstance(id, _) | Type::Enum(id) => *id,
                _ => {
                    panic!("Expected enum type");
                }
            };
            let enum_ = &project.enums[id];
            match enum_.underlying_type {
                Some(_) => {
                    output.push_str("JAKT_RESOLVE_EXPLICIT_VALUE_OR_RETURN(([&]() -> _JaktExplicitValueOrReturn<");
                    output.push_str(&codegen_type(*return_ty, project));
                    output.push_str(", ");
                    output.push_str("_JaktCurrentFunctionReturnType");
                    output.push_str("> { \n");
                    output.push_str("switch (");
                    output.push_str(&codegen_expr(indent, expr, project));
                    output.push_str(") {\n");
                    for case in cases {
                        output.push_str("case ");
                        output.push_str(&codegen_type(expr.ty(), project));
                        output.push_str("::");
                        match case {
                            CheckedMatchCase::EnumVariant {
                                variant_name, body, ..
                            } => {
                                output.push_str(variant_name);
                                output.push_str(":\n");
                                output.push_str(&" ".repeat(indent));
                                match body {
                                    CheckedMatchBody::Expression(expr) => {
                                        output.push_str("return _JaktExplicitReturn(");
                                        output.push_str(&codegen_expr(0, expr, project));
                                        output.push(')');
                                    }
                                    CheckedMatchBody::Block(block) => {
                                        output.push_str(&codegen_block(indent, block, project));
                                        output.push_str("break;\n");
                                    }
                                }
                            }
                        }
                        output.push('\n');
                    }
                    output.push_str("}\n");
                    output.push_str("}()))");
                }
                None => {
                    output.push_str("JAKT_RESOLVE_EXPLICIT_VALUE_OR_RETURN((");
                    output.push_str(&codegen_expr(indent, expr, project));
                    output.push_str(").visit(");
                    let mut first = true;
                    for case in cases {
                        if !first {
                            output.push_str(", ");
                        } else {
                            first = false;
                        }
                        output.push_str("[&] (");
                        match case {
                            CheckedMatchCase::EnumVariant {
                                variant_name: _,
                                variant_arguments: args,
                                subject_type_id,
                                variant_index,
                                scope_id,
                                body,
                            } => {
                                let type_ = &project.types[*subject_type_id];
                                let enum_id = match type_ {
                                    Type::GenericEnumInstance(id, _) | Type::Enum(id) => id,
                                    _ => panic!("Expected enum type"),
                                };

                                let enum_ = &project.enums[*enum_id];
                                let variant = &enum_.variants[*variant_index];
                                match variant {
                                    CheckedEnumVariant::Typed(name, _, _) => {
                                        output.push_str("typename ");
                                        output.push_str(&codegen_type(*subject_type_id, project));
                                        output.push_str("::");
                                        output.push_str(name);
                                        output.push_str(
                                            " const& __jakt_match_value) -> _JaktExplicitValueOrReturn<",
                                        );
                                        output.push_str(&codegen_type(*return_ty, project));
                                        output.push_str(", ");
                                        output.push_str("_JaktCurrentFunctionReturnType");
                                        output.push('>');
                                        output.push_str(" {\n");
                                        output.push_str("   ");
                                        if !args.is_empty() {
                                            let var = project
                                                .find_var_in_scope(*scope_id, args[0].1.as_str())
                                                .unwrap();
                                            output.push_str(codegen_type(var.ty, project).as_str());
                                            output.push_str(" const& ");
                                            output.push_str(args[0].1.as_str());
                                            output.push_str(" = __jakt_match_value.value;\n");
                                        }
                                    }
                                    CheckedEnumVariant::Untyped(name, _) => {
                                        output.push_str("typename ");
                                        output.push_str(&codegen_type(*subject_type_id, project));
                                        output.push_str("::");
                                        output.push_str(name);
                                        output.push_str(
                                            " const& __jakt_match_value) -> _JaktExplicitValueOrReturn<",
                                        );
                                        output.push_str(&codegen_type(*return_ty, project));
                                        output.push_str(", ");
                                        output.push_str("_JaktCurrentFunctionReturnType");
                                        output.push('>');
                                        output.push_str(" {\n");
                                    }
                                    CheckedEnumVariant::StructLike(name, _, _) => {
                                        output.push_str("typename ");
                                        output.push_str(&codegen_type(*subject_type_id, project));
                                        output.push_str("::");
                                        output.push_str(name);
                                        output.push_str(
                                            " const& __jakt_match_value) -> _JaktExplicitValueOrReturn<",
                                        );
                                        output.push_str(&codegen_type(*return_ty, project));
                                        output.push_str(", ");
                                        output.push_str("_JaktCurrentFunctionReturnType");
                                        output.push('>');
                                        output.push_str(" {\n");

                                        if !args.is_empty() {
                                            for arg in args {
                                                let var = project
                                                    .find_var_in_scope(*scope_id, &arg.1)
                                                    .unwrap();
                                                output.push_str(
                                                    codegen_type(var.ty, project).as_str(),
                                                );
                                                output.push_str(" const& ");
                                                output.push_str(arg.1.as_str());
                                                output.push_str(" = __jakt_match_value.");
                                                output.push_str(arg.0.as_ref().unwrap());
                                                output.push_str(";\n");
                                            }
                                        }
                                    }
                                    CheckedEnumVariant::WithValue(_, _, _) => unreachable!(),
                                }

                                match body {
                                    CheckedMatchBody::Block(block) => {
                                        output.push_str(&codegen_block(indent + 1, block, project));
                                        output.push_str("\nreturn _JaktExplicitValue<");
                                        output.push_str(&codegen_type(*return_ty, project));
                                        output.push_str(">();\n");
                                    }
                                    CheckedMatchBody::Expression(expr) => {
                                        if expr.ty() == VOID_TYPE_ID {
                                            output.push_str("   return (");
                                            output.push_str(&codegen_expr(
                                                indent + 1,
                                                expr,
                                                project,
                                            ));
                                            output.push_str("), _JaktExplicitValue<void>();\n");
                                        } else {
                                            output.push_str("   return _JaktExplicitValue(");
                                            output.push_str(&codegen_expr(
                                                indent + 1,
                                                expr,
                                                project,
                                            ));
                                            output.push_str(");\n");
                                        }
                                    }
                                }
                            }
                        }
                        output.push_str("}\n");
                    }
                    output.push(')');
                    output.push(')');
                }
            }
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
                    output.push('-');
                }
                CheckedUnaryOperator::Dereference => {
                    output.push('*');
                }
                CheckedUnaryOperator::RawAddress => {
                    output.push('&');
                }
                CheckedUnaryOperator::LogicalNot => {
                    output.push('!');
                }
                CheckedUnaryOperator::BitwiseNot => {
                    output.push('~');
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
                BinaryOperator::NoneCoalescing => {
                    output.push_str(&codegen_expr(indent, lhs, project));
                    output.push_str(".value_or_lazy_evaluated([&] { return ");
                    output.push_str(&codegen_expr(indent, rhs, project));
                    output.push_str("; })");
                }
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
                output.push_str("(TRY(Array<");
                output.push_str(&codegen_type(vals.first().unwrap().ty(), project));
                output.push_str(">::filled(");
                output.push_str(&codegen_expr(indent, fill_size_expr, project));
                output.push_str(", ");
                output.push_str(&codegen_expr(indent, vals.first().unwrap(), project));
                output.push_str(")))");
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
        CheckedExpression::Dictionary(vals, _, _) => {
            // (Dictionary({1, 2, 3}))
            let key_type_id = vals[0].0.ty();
            let value_type_id = vals[0].1.ty();

            output.push_str(&format!(
                "(Dictionary<{}, {}>({{",
                codegen_type(key_type_id, project),
                codegen_type(value_type_id, project),
            ));
            let mut first = true;
            for (key, value) in vals {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push('{');
                output.push_str(&codegen_expr(indent, key, project));
                output.push_str(", ");
                output.push_str(&codegen_expr(indent, value, project));
                output.push('}');
            }
            output.push_str("}))");
        }
        CheckedExpression::Set(values, _, _) => {
            // (Set({1, 2, 3}))
            let value_type_id = values.first().unwrap().ty();

            output.push_str(&format!(
                "(Set<{}>({{",
                codegen_type(value_type_id, project),
            ));
            let mut first = true;
            for value in values {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }
                output.push_str(&codegen_expr(indent, value, project));
            }
            output.push_str("}))");
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
        CheckedExpression::IndexedDictionary(expr, idx, _, _) => {
            output.push_str("((");
            output.push_str(&codegen_expr(indent, expr, project));
            output.push_str(").get(");
            output.push_str(&codegen_expr(indent, idx, project));
            output.push_str(").value())");
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
