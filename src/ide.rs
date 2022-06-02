use crate::{
    typechecker::{
        CheckedBlock, CheckedExpression, CheckedFunction, CheckedMatchBody, CheckedMatchCase,
        CheckedStatement, FunctionId, Scope, Type, TypeId,
    },
    Project, Span,
};

pub fn find_definition_in_project(project: &Project, span: Span) -> Span {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(span, _)) => span,
        Some(Usage::Call(function_id)) => project.functions[function_id].name_span,
        None => span,
    }
}

pub fn find_typename_in_project(project: &Project, span: Span) -> Option<String> {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(_, type_id)) => Some(project.typename_for_type_id(type_id)),
        Some(Usage::Call(function_id)) => {
            Some(format!("function {}", project.functions[function_id].name))
        }
        None => None,
    }
}

fn completions_for_type_id(project: &Project, type_id: TypeId) -> Vec<String> {
    let mut output = vec![];
    let ty = &project.types[type_id];

    match ty {
        Type::Struct(struct_id) | Type::GenericInstance(struct_id, _) => {
            let structure = &project.structs[*struct_id];

            for field in &structure.fields {
                output.push(field.name.clone())
            }

            let scope = &project.scopes[structure.scope_id];

            for (_, function_id, _) in &scope.functions {
                let function = &project.functions[*function_id];

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
            let result_type_id = project.functions[function_id].return_type_id;
            completions_for_type_id(project, result_type_id)
        }
        None => vec![],
    }
}

pub fn find_span_in_project(project: &Project, span: Span) -> Option<Usage> {
    // lol, for now since vscode is going to send us a url instead
    // of a filepath, let's just assume we are going to look at the file
    // at hand.

    for scope_id in project.file_ids.values() {
        if *scope_id != 0 {
            let scope = &project.scopes[*scope_id];

            return find_span_in_scope(project, scope, span);
        }
    }

    None
}

pub fn find_span_in_scope(project: &Project, scope: &Scope, span: Span) -> Option<Usage> {
    for (_, function_id, _) in &scope.functions {
        let function = &project.functions[*function_id];

        if let Some(usage) = find_span_in_function(project, function, span) {
            return Some(usage);
        }
    }

    for (_, struct_id, _) in &scope.structs {
        let checked_struct = &project.structs[*struct_id];

        let scope = &project.scopes[checked_struct.scope_id];

        if let Some(usage) = find_span_in_scope(project, scope, span) {
            return Some(usage);
        }
    }

    for (_, enum_id, _) in &scope.enums {
        let checked_enum = &project.enums[*enum_id];

        let scope = &project.scopes[checked_enum.scope_id];

        if let Some(usage) = find_span_in_scope(project, scope, span) {
            return Some(usage);
        }
    }

    for child in &scope.children {
        let scope = &project.scopes[*child];

        if let Some(usage) = find_span_in_scope(project, scope, span) {
            return Some(usage);
        }
    }

    None
}

pub fn find_span_in_function(
    project: &Project,
    function: &CheckedFunction,
    span: Span,
) -> Option<Usage> {
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
                Some(usage)
            } else if var_decl.span.contains(span) {
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
                if let Type::Struct(struct_id) = &project.types[type_id] {
                    let structure = &project.structs[*struct_id];

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

pub enum Usage {
    Variable(Span, TypeId),
    Call(FunctionId),
}
