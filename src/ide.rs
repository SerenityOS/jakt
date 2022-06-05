use crate::{
    typechecker::{
        CheckedBlock, CheckedEnum, CheckedEnumVariant, CheckedExpression, CheckedFunction,
        CheckedMatchBody, CheckedMatchCase, CheckedStatement, CheckedStruct,
        FunctionGenericParameter, FunctionId, Scope, ScopeId, Type, TypeId,
    },
    Project, Span,
};

pub fn find_definition_in_project(project: &Project, span: Span) -> Span {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(span, _)) => span,
        Some(Usage::Call(function_id)) => project.get_function(function_id).name_span,
        Some(Usage::Typename(type_id)) => find_type_definition_for_type_id(project, type_id, span),
        None => span,
    }
}

fn find_type_definition_for_type_id(project: &Project, type_id: TypeId, span: Span) -> Span {
    let array_struct_id = project.cached_array_struct_id.unwrap();
    let dictionary_struct_id = project.cached_dictionary_struct_id.unwrap();
    let optional_struct_id = project.cached_optional_struct_id.unwrap();
    let range_struct_id = project.cached_range_struct_id.unwrap();
    let set_struct_id = project.cached_set_struct_id.unwrap();
    let tuple_struct_id = project.cached_tuple_struct_id.unwrap();
    let weak_ptr_struct_id = project.cached_weakptr_struct_id.unwrap();

    match project.get_type(type_id) {
        Type::Builtin => span,
        Type::GenericInstance(struct_id, params) => {
            if [
                array_struct_id,
                optional_struct_id,
                range_struct_id,
                set_struct_id,
                tuple_struct_id,
                weak_ptr_struct_id,
            ]
            .contains(struct_id)
            {
                find_type_definition_for_type_id(project, params[0], span)
            } else if struct_id == &dictionary_struct_id {
                find_type_definition_for_type_id(project, params[1], span)
            } else {
                project.get_struct(*struct_id).name_span
            }
        }
        Type::Struct(struct_id) => project.get_struct(*struct_id).name_span,
        Type::GenericEnumInstance(enum_id, _) | Type::Enum(enum_id) => {
            project.get_enum(*enum_id).span
        }
        Type::RawPtr(type_id) => find_type_definition_for_type_id(project, *type_id, span),
        Type::TypeVariable(_) => span,
    }
}

pub fn find_type_definition_in_project(project: &Project, span: Span) -> Span {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(span, type_id)) => {
            find_type_definition_for_type_id(project, type_id, span)
        }
        Some(Usage::Call(function_id)) => project.get_function(function_id).name_span,
        Some(Usage::Typename(type_id)) => find_type_definition_for_type_id(project, type_id, span),
        None => span,
    }
}

pub fn find_typename_in_project(project: &Project, span: Span) -> Option<String> {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(_, type_id)) => Some(project.typename_for_type_id(type_id)),
        Some(Usage::Call(function_id)) => Some(get_function_signature(project, function_id)),
        Some(Usage::Typename(type_id)) => Some(project.typename_for_type_id(type_id)),
        None => None,
    }
}

fn completions_for_type_id(project: &Project, type_id: TypeId) -> Vec<String> {
    let mut output = vec![];
    let ty = project.get_type(type_id);

    let add_function = |function_id: FunctionId, output: &mut Vec<String>| {
        let function = project.get_function(function_id);

        if let Some(param) = function.params.first() {
            if param.variable.name == "this" {
                let mut full_call = function.name.clone();
                let mut first = true;
                full_call.push('(');
                for param in function.params.iter().skip(1) {
                    if !first {
                        full_call.push_str(", ");
                    } else {
                        first = false;
                    }
                    full_call.push_str(&param.variable.name);
                }
                full_call.push(')');

                output.push(full_call)
            }
        } else {
            output.push(format!("{}()", function.name.clone()));
        }
    };

    match ty {
        Type::Enum(enum_id) => {
            let enum_ = project.get_enum(*enum_id);

            let scope = project.get_scope(enum_.scope_id);
            for (_, function_id, _) in &scope.functions {
                add_function(*function_id, &mut output);
            }
        }
        Type::Struct(struct_id) | Type::GenericInstance(struct_id, _) => {
            let structure = project.get_struct(*struct_id);

            for field in &structure.fields {
                output.push(field.name.clone())
            }

            let scope = project.get_scope(structure.scope_id);
            for (_, function_id, _) in &scope.functions {
                add_function(*function_id, &mut output);
            }
        }
        _ => {}
    }

    output
}

pub fn find_dot_completions_in_project(project: &Project, span: Span) -> Vec<String> {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(_, type_id)) => completions_for_type_id(project, type_id),
        Some(Usage::Call(function_id)) => {
            let result_type_id = project.get_function(function_id).return_type_id;
            completions_for_type_id(project, result_type_id)
        }
        Some(Usage::Typename(_)) => vec![],
        None => vec![],
    }
}

pub fn find_span_in_project(project: &Project, span: Span) -> Option<Usage> {
    // lol, for now since vscode is going to send us a url instead
    // of a filepath, let's just assume we are going to look at the file
    // at hand.

    for module in project.modules.iter() {
        let scope = project.get_scope(ScopeId(module.id, 0));

        return find_span_in_scope(project, scope, span);
    }

    None
}

pub fn find_span_in_scope(project: &Project, scope: &Scope, span: Span) -> Option<Usage> {
    for var in &scope.vars {
        if let Some(type_span) = var.type_span {
            if type_span.contains(span) {
                return Some(Usage::Typename(var.type_id));
            }
        }
    }

    for (_, function_id, _) in &scope.functions {
        let function = project.get_function(*function_id);

        if let Some(usage) = find_span_in_function(project, function, span) {
            return Some(usage);
        }
    }

    for (_, struct_id, _) in &scope.structs {
        let checked_struct = project.get_struct(*struct_id);

        if let Some(usage) = find_span_in_struct(project, checked_struct, span) {
            return Some(usage);
        }
    }

    for (_, enum_id, _) in &scope.enums {
        let checked_enum = project.get_enum(*enum_id);

        if let Some(usage) = find_span_in_enum(project, checked_enum, span) {
            return Some(usage);
        }
    }

    for child in &scope.children {
        let scope = project.get_scope(*child);

        if let Some(usage) = find_span_in_scope(project, scope, span) {
            return Some(usage);
        }
    }

    None
}

pub fn find_span_in_enum(
    project: &Project,
    checked_enum: &CheckedEnum,
    span: Span,
) -> Option<Usage> {
    let scope = project.get_scope(checked_enum.scope_id);

    for variant in &checked_enum.variants {
        match variant {
            CheckedEnumVariant::StructLike(_, fields, _) => {
                for field in fields {
                    if let Some(type_span) = field.type_span {
                        if type_span.contains(span) {
                            return Some(Usage::Typename(field.type_id));
                        }
                    }
                }
            }
            CheckedEnumVariant::Typed(_, type_id, variant_span) => {
                if variant_span.contains(span) {
                    return Some(Usage::Typename(*type_id));
                }
            }
            CheckedEnumVariant::Untyped(_, _) => {}
            CheckedEnumVariant::WithValue(_, expr, _) => {
                if let Some(usage) = find_span_in_expression(project, expr, span) {
                    return Some(usage);
                }
            }
        }
    }

    if let Some(usage) = find_span_in_scope(project, scope, span) {
        return Some(usage);
    }

    None
}

pub fn find_span_in_struct(
    project: &Project,
    checked_struct: &CheckedStruct,
    span: Span,
) -> Option<Usage> {
    let scope = project.get_scope(checked_struct.scope_id);

    for field in &checked_struct.fields {
        if let Some(type_span) = field.type_span {
            if type_span.contains(span) {
                return Some(Usage::Typename(field.type_id));
            }
        }
    }

    if let Some(usage) = find_span_in_scope(project, scope, span) {
        return Some(usage);
    }

    None
}

pub fn find_span_in_function(
    project: &Project,
    function: &CheckedFunction,
    span: Span,
) -> Option<Usage> {
    if let Some(return_type_span) = function.return_type_span {
        if return_type_span.contains(span) {
            return Some(Usage::Typename(function.return_type_id));
        }
    }

    for param in &function.params {
        if let Some(param_type_span) = param.variable.type_span {
            if param_type_span.contains(span) {
                return Some(Usage::Typename(param.variable.type_id));
            }
        }
    }

    if let Some(block) = &function.block {
        return find_span_in_block(project, block, span);
    }

    None
}

pub fn find_span_in_block(project: &Project, block: &CheckedBlock, span: Span) -> Option<Usage> {
    for stmt in &block.stmts {
        if let Some(usage) = find_span_in_statement(project, stmt, span) {
            return Some(usage);
        }
    }

    None
}

pub fn find_span_in_statement(
    project: &Project,
    statement: &CheckedStatement,
    span: Span,
) -> Option<Usage> {
    match statement {
        CheckedStatement::Block(block) => find_span_in_block(project, block, span),
        CheckedStatement::Defer(deferred) => find_span_in_statement(project, deferred, span),
        CheckedStatement::Expression(expr) => find_span_in_expression(project, expr, span),
        CheckedStatement::If(expr, block, stmt) => {
            if let Some(usage) = find_span_in_expression(project, expr, span) {
                Some(usage)
            } else if let Some(usage) = find_span_in_block(project, block, span) {
                Some(usage)
            } else if let Some(stmt) = stmt {
                find_span_in_statement(project, stmt, span)
            } else {
                None
            }
        }
        CheckedStatement::InlineCpp(_) => None,
        CheckedStatement::Loop(block) => find_span_in_block(project, block, span),
        CheckedStatement::Return(expr) | CheckedStatement::Throw(expr) => {
            find_span_in_expression(project, expr, span)
        }
        CheckedStatement::Try(stmt, _, block) => {
            if let Some(usage) = find_span_in_statement(project, stmt, span) {
                Some(usage)
            } else {
                find_span_in_block(project, block, span)
            }
        }
        CheckedStatement::VarDecl(var_decl, expr) => {
            if let Some(usage) = find_span_in_expression(project, expr, span) {
                return Some(usage);
            } else if let Some(type_span) = var_decl.type_span {
                if type_span.contains(span) {
                    return Some(Usage::Typename(var_decl.type_id));
                }
            }

            if var_decl.span.contains(span) {
                Some(Usage::Variable(var_decl.span, var_decl.type_id))
            } else {
                None
            }
        }
        CheckedStatement::While(expr, block) => {
            if let Some(usage) = find_span_in_expression(project, expr, span) {
                Some(usage)
            } else {
                find_span_in_block(project, block, span)
            }
        }
        CheckedStatement::Yield(expr) => find_span_in_expression(project, expr, span),
        CheckedStatement::Break => None,
        CheckedStatement::Continue => None,
        CheckedStatement::Garbage => None,
    }
}

pub fn find_span_in_expression(
    project: &Project,
    expression: &CheckedExpression,
    span: Span,
) -> Option<Usage> {
    match expression {
        CheckedExpression::Array(elems, repeat, _, _) => {
            for elem in elems {
                if let Some(usage) = find_span_in_expression(project, elem, span) {
                    return Some(usage);
                }

                if let Some(repeat) = repeat {
                    return find_span_in_expression(project, repeat, span);
                }
            }
        }
        CheckedExpression::BinaryOp(lhs, _, rhs, _, _) => {
            if let Some(usage) = find_span_in_expression(project, lhs, span) {
                return Some(usage);
            }
            if let Some(usage) = find_span_in_expression(project, rhs, span) {
                return Some(usage);
            }
        }
        CheckedExpression::Block(block, _, _) => return find_span_in_block(project, block, span),
        CheckedExpression::Call(call, call_span, _) => {
            for (_, arg) in &call.args {
                if let Some(usage) = find_span_in_expression(project, arg, span) {
                    return Some(usage);
                }
            }
            if call_span.contains(span) {
                if let Some(function_id) = call.function_id {
                    return Some(Usage::Call(function_id));
                } else {
                    return None;
                }
            }
        }
        CheckedExpression::Dictionary(items, _, _) => {
            for (key, value) in items {
                if let Some(usage) = find_span_in_expression(project, key, span) {
                    return Some(usage);
                }

                if let Some(usage) = find_span_in_expression(project, value, span) {
                    return Some(usage);
                }
            }
        }
        CheckedExpression::IndexedExpression(obj, expr, _, _) => {
            if let Some(usage) = find_span_in_expression(project, obj, span) {
                return Some(usage);
            }

            if let Some(usage) = find_span_in_expression(project, expr, span) {
                return Some(usage);
            }
        }
        CheckedExpression::IndexedStruct(expr, field_name, index_span, _) => {
            if let Some(usage) = find_span_in_expression(project, expr, span) {
                return Some(usage);
            }

            if index_span.contains(span) {
                let type_id = expr.type_id_or_type_var();
                if let Type::Struct(struct_id) = project.get_type(type_id) {
                    let structure = project.get_struct(*struct_id);

                    for field in &structure.fields {
                        if &field.name == field_name {
                            return Some(Usage::Variable(field.span, field.type_id));
                        }
                    }
                }
            }
        }
        CheckedExpression::IndexedDictionary(key, value, _, _) => {
            if let Some(usage) = find_span_in_expression(project, key, span) {
                return Some(usage);
            }

            if let Some(usage) = find_span_in_expression(project, value, span) {
                return Some(usage);
            }
        }
        CheckedExpression::Match(expr, cases, _, _, _) => {
            for case in cases {
                match case {
                    CheckedMatchCase::EnumVariant {
                        variant_name: _,
                        variant_arguments: _,
                        subject_type_id: _,
                        variant_index: _,
                        scope_id: _,
                        body,
                    } => match body {
                        CheckedMatchBody::Block(block) => {
                            if let Some(usage) = find_span_in_block(project, block, span) {
                                return Some(usage);
                            }
                        }
                        CheckedMatchBody::Expression(expr) => {
                            if let Some(usage) = find_span_in_expression(project, expr, span) {
                                return Some(usage);
                            }
                        }
                    },
                    CheckedMatchCase::Expression { expression, body } => {
                        if let Some(usage) = find_span_in_expression(project, expression, span) {
                            return Some(usage);
                        }

                        match body {
                            CheckedMatchBody::Block(block) => {
                                if let Some(usage) = find_span_in_block(project, block, span) {
                                    return Some(usage);
                                }
                            }
                            CheckedMatchBody::Expression(expr) => {
                                if let Some(usage) = find_span_in_expression(project, expr, span) {
                                    return Some(usage);
                                }
                            }
                        }
                    }
                    CheckedMatchCase::CatchAll { body } => match body {
                        CheckedMatchBody::Block(block) => {
                            if let Some(usage) = find_span_in_block(project, block, span) {
                                return Some(usage);
                            }
                        }
                        CheckedMatchBody::Expression(expr) => {
                            if let Some(usage) = find_span_in_expression(project, expr, span) {
                                return Some(usage);
                            }
                        }
                    },
                }
            }

            if let Some(usage) = find_span_in_expression(project, expr, span) {
                return Some(usage);
            }
        }
        CheckedExpression::ForcedUnwrap(expr, _, _) => {
            if let Some(usage) = find_span_in_expression(project, expr, span) {
                return Some(usage);
            }
        }
        CheckedExpression::UnaryOp(expr, _, _, _) => {
            if let Some(usage) = find_span_in_expression(project, expr, span) {
                return Some(usage);
            }
        }
        CheckedExpression::MethodCall(object, call, method_span, _) => {
            if let Some(usage) = find_span_in_expression(project, object, span) {
                return Some(usage);
            }
            if method_span.contains(span) {
                if let Some(function_id) = call.function_id {
                    return Some(Usage::Call(function_id));
                } else {
                    return None;
                }
            } else {
                return None;
            }
        }
        CheckedExpression::Var(var, var_span) => {
            if var_span.contains(span) {
                return Some(Usage::Variable(var.definition_span, var.type_id));
            }
        }
        _ => {}
    }

    None
}

pub fn get_function_signature(project: &Project, function_id: FunctionId) -> String {
    let function = project.get_function(function_id);

    let mut generic_parameters = String::new();
    let mut is_first_param = true;

    if !function.generic_parameters.is_empty() {
        generic_parameters.push('<');

        for parameter in &function.generic_parameters {
            let generic_type = match parameter {
                FunctionGenericParameter::InferenceGuide(type_id) => {
                    project.typename_for_type_id(*type_id)
                }
                FunctionGenericParameter::Parameter(type_id) => {
                    project.typename_for_type_id(*type_id)
                }
            };
            let seperator = if is_first_param { "" } else { ", " };
            generic_parameters.push_str(&format!("{}{}", seperator, generic_type));
            is_first_param = false;
        }

        generic_parameters.push('>');
    }

    let mut parameters = String::new();
    is_first_param = true;

    for param in &function.params {
        let anon = if !param.requires_label { "anon " } else { "" };
        let mutable = if param.variable.mutable {
            "mutable "
        } else {
            ""
        };

        let mut variable_type = project.typename_for_type_id(param.variable.type_id);
        if variable_type != "void" {
            variable_type.insert_str(0, ": ");
        } else {
            variable_type.clear();
        }

        let seperator = if is_first_param { "" } else { ", " };
        parameters.push_str(&format!(
            "{}{}{}{}{}",
            seperator, anon, mutable, param.variable.name, variable_type
        ));
        is_first_param = false;
    }

    let throws = if function.throws { " throws" } else { "" };

    let mut returns = project.typename_for_type_id(function.return_type_id);
    if returns != "void" {
        returns.insert_str(0, " -> ");
    } else {
        returns.clear();
    }

    format!(
        "function {}{}({}){}{}",
        function.name, generic_parameters, parameters, throws, returns
    )
}

pub enum Usage {
    Variable(Span, TypeId),
    Call(FunctionId),
    Typename(TypeId),
}
