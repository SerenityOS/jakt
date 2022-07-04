/*
 * !!! DEPRECATION WARNING !!!
 * We're not doing any more feature development in the rust-based compiler at this point.
 * It'll be limited to bug fixes and necessities only.
 *
 * New features should go into the self-hosted compiler.
 */

use std::collections::HashSet;
use std::fmt::Write;

use crate::{
    parser::{DefinitionType, FunctionLinkage, Visibility},
    typechecker::{
        CheckedBlock, CheckedEnum, CheckedEnumVariant, CheckedExpression, CheckedFunction,
        CheckedMatchBody, CheckedMatchCase, CheckedStatement, CheckedStruct,
        FunctionGenericParameter, FunctionId, Module, NumberConstant, Scope, ScopeId, Type, TypeId,
    },
    Project, Span,
};

pub fn find_definition_in_project(project: &Project, span: Span) -> Span {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(span, _, _, _, _, _, _)) => span,
        Some(Usage::Call(function_id)) => project.get_function(function_id).name_span,
        Some(Usage::Typename(type_id)) => find_type_definition_for_type_id(project, type_id, span),
        Some(Usage::NameSet(_)) => span,
        Some(Usage::EnumVariant(span, _, _, _, _)) => span,
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
        Some(Usage::Variable(span, _, type_id, _, _, _, _)) => {
            find_type_definition_for_type_id(project, type_id, span)
        }
        Some(Usage::Call(function_id)) => project.get_function(function_id).name_span,
        Some(Usage::Typename(type_id)) => find_type_definition_for_type_id(project, type_id, span),
        Some(Usage::NameSet(_)) => span,
        Some(Usage::EnumVariant(span, _, _, _, _)) => span,
        None => span,
    }
}

pub fn find_typename_in_project(project: &Project, span: Span) -> Option<String> {
    match find_span_in_project(project, span) {
        Some(Usage::Variable(
            _,
            name,
            type_id,
            mutability,
            var_type,
            visibility,
            struct_type_id,
        )) => Some(get_var_signature(
            project,
            &name,
            type_id,
            mutability,
            var_type,
            visibility,
            struct_type_id,
        )),
        Some(Usage::Call(function_id)) => Some(get_function_signature(project, function_id)),
        Some(Usage::Typename(type_id)) => Some(get_type_signature(project, type_id)),
        Some(Usage::NameSet(names)) => Some(names.join(" | ")),
        Some(Usage::EnumVariant(_, name, enum_name, params, value)) => Some(
            get_enum_variant_signature(project, name, enum_name, params, value),
        ),
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
        Some(Usage::Variable(_, _, type_id, _, _, _, _)) => {
            completions_for_type_id(project, type_id)
        }
        Some(Usage::Call(function_id)) => {
            let result_type_id = project.get_function(function_id).return_type_id;
            completions_for_type_id(project, result_type_id)
        }
        Some(Usage::NameSet(_)) => vec![],
        Some(Usage::Typename(_)) => vec![],
        Some(Usage::EnumVariant(_, _, _, _, _)) => vec![],
        None => vec![],
    }
}

pub fn find_span_in_project(project: &Project, span: Span) -> Option<Usage> {
    // lol, for now since vscode is going to send us a url instead
    // of a filepath, let's just assume we are going to look at the file
    // at hand.

    for module in project.modules.iter().skip(1) {
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
            CheckedEnumVariant::StructLike(name, fields, variant_span) => {
                for field in fields {
                    if let Some(type_span) = field.type_span {
                        if type_span.contains(span) {
                            return Some(Usage::Typename(field.type_id));
                        }
                    }
                }

                if variant_span.contains(span) {
                    return Some(Usage::EnumVariant(
                        *variant_span,
                        name.clone(),
                        checked_enum.type_id,
                        enum_variant_fields(variant),
                        None,
                    ));
                }
            }
            CheckedEnumVariant::Typed(name, _, variant_span) => {
                if variant_span.contains(span) {
                    return Some(Usage::EnumVariant(
                        *variant_span,
                        name.clone(),
                        checked_enum.type_id,
                        enum_variant_fields(variant),
                        None,
                    ));
                }
            }
            CheckedEnumVariant::Untyped(name, variant_span) => {
                if variant_span.contains(span) {
                    return Some(Usage::EnumVariant(
                        *variant_span,
                        name.clone(),
                        checked_enum.type_id,
                        vec![],
                        None,
                    ));
                }
            }
            CheckedEnumVariant::WithValue(name, expr, variant_span) => {
                if let Some(usage) = find_span_in_expression(project, expr, span) {
                    return Some(usage);
                }

                if variant_span.contains(span) {
                    return Some(Usage::EnumVariant(
                        *variant_span,
                        name.clone(),
                        checked_enum.type_id,
                        vec![],
                        expr.to_number_constant(),
                    ));
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
        CheckedStatement::Return(Some(expr)) | CheckedStatement::Throw(expr) => {
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
                let mutability = if var_decl.mutable {
                    Mutability::Mutable
                } else {
                    Mutability::Immutable
                };
                Some(Usage::Variable(
                    var_decl.span,
                    var_decl.name.clone(),
                    var_decl.type_id,
                    mutability,
                    VarType::Variable,
                    VarVisibility::DoesNotApply,
                    None,
                ))
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
        CheckedStatement::Return(..) => None,
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
                        let visibility = match field.visibility {
                            Visibility::Public => VarVisibility::Public,
                            Visibility::Private => VarVisibility::Private,
                            Visibility::Restricted(_, _) => VarVisibility::Restricted,
                        };

                        if &field.name == field_name {
                            return Some(Usage::Variable(
                                field.span,
                                field_name.clone(),
                                field.type_id,
                                Mutability::DoesNotApply,
                                VarType::Field,
                                visibility,
                                Some(type_id),
                            ));
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
                        variant_name,
                        variant_arguments: _,
                        subject_type_id: _,
                        variant_index: _,
                        scope_id: _,
                        body,
                        marker_span,
                    } => {
                        if marker_span.contains(span) {
                            let type_id = expr.type_id_or_type_var();

                            return Some(get_enum_variant_usage_from_type_id_and_name(
                                project,
                                type_id,
                                variant_name.clone(),
                            ));
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
                    CheckedMatchCase::Expression {
                        expression, body, ..
                    } => {
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
                    CheckedMatchCase::CatchAll { body, marker_span } => {
                        if marker_span.contains(span) {
                            let all_cases = match project.get_type(expr.type_id_or_type_var()) {
                                Type::Enum(enum_id) | Type::GenericEnumInstance(enum_id, _) => {
                                    let enum_ = project.get_enum(*enum_id);
                                    Some(
                                        enum_
                                            .variants
                                            .iter()
                                            .map(|v| match v {
                                                CheckedEnumVariant::StructLike(name, _, _)
                                                | CheckedEnumVariant::Typed(name, _, _)
                                                | CheckedEnumVariant::WithValue(name, _, _)
                                                | CheckedEnumVariant::Untyped(name, _) => name,
                                            })
                                            .collect::<HashSet<_>>(),
                                    )
                                }
                                _ => None,
                            };

                            if all_cases.is_none() {
                                return Some(Usage::NameSet(vec!["else (expression)".to_string()]));
                            }

                            let all_cases = all_cases.unwrap();

                            let covered_cases = cases
                                .iter()
                                .flat_map(|x| match x {
                                    CheckedMatchCase::CatchAll { .. } => None,
                                    CheckedMatchCase::EnumVariant { variant_name, .. } => {
                                        Some(variant_name)
                                    }
                                    CheckedMatchCase::Expression { .. } => None,
                                })
                                .collect::<std::collections::HashSet<_>>();

                            let remaining = covered_cases
                                .symmetric_difference(&all_cases)
                                .map(|x| (*x).clone())
                                .collect::<Vec<_>>();

                            if remaining.is_empty() {
                                return None;
                            }

                            return Some(Usage::NameSet(remaining));
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
            for (_, arg) in &call.args {
                if let Some(usage) = find_span_in_expression(project, arg, span) {
                    return Some(usage);
                }
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
                let mutability = if var.mutable {
                    Mutability::Mutable
                } else {
                    Mutability::Immutable
                };

                return Some(Usage::Variable(
                    var.definition_span,
                    var.name.clone(),
                    var.type_id,
                    mutability,
                    VarType::Variable,
                    VarVisibility::DoesNotApply,
                    None,
                ));
            }
        }
        CheckedExpression::NamespacedVar(namespaces, var, var_span) => {
            if var_span.contains(span)
                && !namespaces.is_empty()
                && namespaces.last().unwrap().name.is_some()
            {
                let enum_id = project.find_enum_in_scope(
                    namespaces.last().unwrap().scope,
                    namespaces.last().unwrap().name.as_ref().unwrap(),
                );

                if let Some(enum_id) = enum_id {
                    let enum_ = project.get_enum(enum_id);

                    return Some(get_enum_variant_usage_from_type_id_and_name(
                        project,
                        enum_.type_id,
                        var.name.clone(),
                    ));
                }
            }
        }
        _ => {}
    }

    None
}

pub fn get_function_signature(project: &Project, function_id: FunctionId) -> String {
    let function = project.get_function(function_id);

    match function.linkage {
        FunctionLinkage::ImplicitEnumConstructor => {
            let type_id = function.return_type_id;
            let name = function.name.clone();
            return get_enum_variant_signature_from_type_id_and_name(project, type_id, name);
        }
        FunctionLinkage::ImplicitConstructor => {
            return get_constructor_signature(project, function_id);
        }
        _ => {}
    }

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
            let _ = write!(generic_parameters, "{}{}", seperator, generic_type);
            is_first_param = false;
        }

        generic_parameters.push('>');
    }

    let mut parameters = String::new();
    is_first_param = true;

    for param in &function.params {
        let anon = if !param.requires_label { "anon " } else { "" };
        let mutable = if param.variable.mutable { "mut " } else { "" };

        let mut variable_type = project.typename_for_type_id(param.variable.type_id);
        if variable_type != "void" {
            variable_type.insert_str(0, ": ");
        } else {
            variable_type.clear();
        }

        let seperator = if is_first_param { "" } else { ", " };
        let _ = write!(
            parameters,
            "{}{}{}{}{}",
            seperator, anon, mutable, param.variable.name, variable_type
        );
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

pub fn get_var_signature(
    project: &Project,
    name: &String,
    var_type_id: TypeId,
    mutability: Mutability,
    var_type: VarType,
    visibility: VarVisibility,
    struct_type_id: Option<TypeId>,
) -> String {
    match var_type {
        VarType::Variable => {
            let mut_string = match mutability {
                Mutability::Mutable => "mut",
                Mutability::Immutable => "let",
                _ => "",
            };
            let type_name = get_type_signature(project, var_type_id);
            format!("{} {}: {}", mut_string, name, type_name)
        }
        VarType::Field => {
            let record_string =
                struct_type_id.map(|struct_type_id| get_type_signature(project, struct_type_id));
            let visibility_string = match visibility {
                VarVisibility::Public => "public ",
                VarVisibility::Private => "private ",
                _ => "",
            };
            let type_name = get_type_signature(project, var_type_id);

            if let Some(record_string) = record_string {
                format!(
                    "{}\\n\\t{}{}: {}",
                    &record_string, visibility_string, name, type_name
                )
            } else {
                format!("{}{}: {}", visibility_string, name, type_name)
            }
        }
    }
}

pub fn get_type_signature(project: &Project, type_id: TypeId) -> String {
    let array_struct_id = project.cached_array_struct_id.unwrap();
    let dictionary_struct_id = project.cached_dictionary_struct_id.unwrap();
    let optional_struct_id = project.cached_optional_struct_id.unwrap();
    let range_struct_id = project.cached_range_struct_id.unwrap();
    let set_struct_id = project.cached_set_struct_id.unwrap();
    let tuple_struct_id = project.cached_tuple_struct_id.unwrap();
    let weak_ptr_struct_id = project.cached_weakptr_struct_id.unwrap();

    match project.get_type(type_id) {
        Type::Builtin => project.typename_for_type_id(type_id),
        Type::GenericInstance(struct_id, params) => {
            if *struct_id == array_struct_id {
                if params.is_empty() {
                    "[]".to_string()
                } else {
                    format!("[{}]", get_type_signature(project, params[0]))
                }
            } else if *struct_id == dictionary_struct_id {
                if params.len() < 2 {
                    "[:]".to_string()
                } else {
                    format!(
                        "[{}: {}]",
                        get_type_signature(project, params[0]),
                        get_type_signature(project, params[1])
                    )
                }
            } else if *struct_id == optional_struct_id {
                if params.is_empty() {
                    "".to_string()
                } else {
                    format!("{}?", get_type_signature(project, params[0]))
                }
            } else if *struct_id == range_struct_id {
                if params.is_empty() {
                    "..".to_string()
                } else {
                    // Ranges probably only make sense for builtin types, but if not we use the format
                    // struct MyRangeStruct..MyRangeStruct
                    format!(
                        "{}..{}",
                        get_type_signature(project, params[0]),
                        project.typename_for_type_id(params[0])
                    )
                }
            } else if *struct_id == set_struct_id {
                if params.is_empty() {
                    "".to_string()
                } else {
                    format!("{{{}}}", get_type_signature(project, params[0]))
                }
            } else if *struct_id == tuple_struct_id {
                let mut output = "(".to_string();

                let mut first = true;
                for param in params.iter() {
                    if first {
                        first = false;
                    } else {
                        output.push_str(", ");
                    }

                    output.push_str(&get_type_signature(project, *param));
                }
                output.push(')');
                output
            } else if *struct_id == weak_ptr_struct_id {
                if params.is_empty() {
                    "".to_string()
                } else {
                    format!("weak {}?", get_type_signature(project, params[0]))
                }
            } else {
                let struct_ = project.get_struct(*struct_id);
                let mut output = match struct_.definition_type {
                    DefinitionType::Class => "class ",
                    DefinitionType::Struct => "struct ",
                }
                .to_string();
                output.push_str(&struct_.name);
                output.push('<');
                let mut first = true;
                for param in params.iter() {
                    if first {
                        first = false;
                    } else {
                        output.push_str(", ");
                    }

                    output.push_str(&get_type_signature(project, *param));
                }
                output.push('>');
                output
            }
        }
        Type::Struct(struct_id) => {
            let struct_type = match project.get_struct(*struct_id).definition_type {
                DefinitionType::Class => "class",
                DefinitionType::Struct => "struct",
            };
            format!("{} {}", struct_type, &project.get_struct(*struct_id).name)
        }
        Type::Enum(enum_id) => {
            let is_boxed = project.get_enum(*enum_id).definition_type == DefinitionType::Class;
            let mut output = String::new();
            if is_boxed {
                output.push_str("boxed ");
            }
            output.push_str("enum ");
            output.push_str(&project.get_enum(*enum_id).name);
            output
        }
        Type::GenericEnumInstance(enum_id, params) => {
            let is_boxed = project.get_enum(*enum_id).definition_type == DefinitionType::Class;
            let mut output = String::new();
            if is_boxed {
                output.push_str("boxed ");
            }
            output.push_str("enum ");
            output.push_str(&project.get_enum(*enum_id).name);
            output.push('<');
            let mut first = true;
            for param in params.iter() {
                if first {
                    first = false;
                } else {
                    output.push_str(", ");
                }

                output.push_str(&get_type_signature(project, *param));
            }
            output.push('>');
            output
        }
        _ => project.typename_for_type_id(type_id),
    }
}

fn get_enum_variant_signature(
    project: &Project,
    name: String,
    type_id: TypeId,
    params: Vec<(Option<String>, TypeId)>,
    value: Option<NumberConstant>,
) -> String {
    let mut output = get_type_signature(project, type_id);
    output.push_str("::");
    output.push_str(&name);
    if !params.is_empty() {
        output.push('(');
        let mut first = true;
        for (param_name, param_type_id) in params.iter() {
            if first {
                first = false;
            } else {
                output.push_str(", ");
            }

            if let Some(param_name) = param_name {
                output.push_str(param_name);
                output.push_str(": ");
            }

            output.push_str(&project.typename_for_type_id(*param_type_id));
        }
        output.push(')');
    }
    if let Some(value) = value {
        output.push_str(" = ");
        let value_string = match value {
            NumberConstant::Signed(value) => format!("{}", value),
            NumberConstant::Unsigned(value) => format!("{}", value),
            NumberConstant::Floating(value) => format!("{}", value),
        };
        output.push_str(&value_string);
    }
    output
}

fn get_enum_variant_signature_from_type_id_and_name(
    project: &Project,
    type_id: TypeId,
    name: String,
) -> String {
    let module: &Module = &project.modules[type_id.0 .0];
    let enum_ = module
        .enums
        .iter()
        .find(|e| e.type_id == type_id)
        .expect("could not find enum");
    let checked_enum_variant = enum_
        .variants
        .iter()
        .find(|v| match v {
            CheckedEnumVariant::Untyped(v_name, _)
            | CheckedEnumVariant::Typed(v_name, _, _)
            | CheckedEnumVariant::WithValue(v_name, _, _)
            | CheckedEnumVariant::StructLike(v_name, _, _) => *v_name == name,
        })
        .expect("could not find variant");
    let params = enum_variant_fields(checked_enum_variant);
    let value = match checked_enum_variant {
        CheckedEnumVariant::WithValue(_, expr, _) => expr.to_number_constant(),
        _ => None,
    };

    get_enum_variant_signature(project, name, type_id, params, value)
}

fn get_enum_variant_usage_from_type_id_and_name(
    project: &Project,
    type_id: TypeId,
    name: String,
) -> Usage {
    let module: &Module = &project.modules[type_id.0 .0];
    let enum_ = module
        .enums
        .iter()
        .find(|e| e.type_id == type_id)
        .expect("could not find enum");
    let checked_enum_variant = enum_
        .variants
        .iter()
        .find(|v| match v {
            CheckedEnumVariant::Untyped(v_name, _)
            | CheckedEnumVariant::Typed(v_name, _, _)
            | CheckedEnumVariant::WithValue(v_name, _, _)
            | CheckedEnumVariant::StructLike(v_name, _, _) => *v_name == name,
        })
        .expect("could not find variant");
    let variant_fields = enum_variant_fields(checked_enum_variant);
    let value = match checked_enum_variant {
        CheckedEnumVariant::WithValue(_, expr, _) => expr.to_number_constant(),
        _ => None,
    };
    let span = match checked_enum_variant {
        CheckedEnumVariant::Untyped(_, span)
        | CheckedEnumVariant::Typed(_, _, span)
        | CheckedEnumVariant::WithValue(_, _, span)
        | CheckedEnumVariant::StructLike(_, _, span) => *span,
    };

    Usage::EnumVariant(span, name, type_id, variant_fields, value)
}

fn enum_variant_fields(checked_enum_variant: &CheckedEnumVariant) -> Vec<(Option<String>, TypeId)> {
    match checked_enum_variant {
        CheckedEnumVariant::StructLike(_, fields, _) => fields
            .iter()
            .map(|var_decl| (Some(var_decl.name.clone()), var_decl.type_id))
            .collect(),
        CheckedEnumVariant::Typed(_, type_id, _) => vec![(None, *type_id)],
        CheckedEnumVariant::Untyped(_, _) => vec![],
        CheckedEnumVariant::WithValue(_, _, _) => vec![],
    }
}

fn get_constructor_signature(project: &Project, constructor_function_id: FunctionId) -> String {
    let function = project.get_function(constructor_function_id);
    let type_id = function.return_type_id;
    let module: &Module = &project.modules[type_id.0 .0];
    let struct_ = module
        .structs
        .iter()
        .find(|s| s.type_id == type_id)
        .expect("could not find enum");

    let mut output = get_type_signature(project, type_id);

    output.push('(');
    let mut first = true;
    for field in struct_.fields.iter() {
        if first {
            first = false;
        } else {
            output.push_str(", ");
        }
        if field.mutable {
            output.push_str("mut ");
        }
        write!(
            &mut output,
            "{}: {}",
            &field.name,
            project.typename_for_type_id(field.type_id)
        )
        .expect("writing failed");
    }
    output.push(')');
    output
}

pub enum Mutability {
    DoesNotApply,
    Immutable,
    Mutable,
}

pub enum VarType {
    Variable,
    Field,
}

pub enum VarVisibility {
    DoesNotApply,
    Public,
    Private,
    Restricted, // TODO: add more info
}

pub enum Usage {
    Variable(
        Span,
        String,
        TypeId,
        Mutability,
        VarType,
        VarVisibility,
        Option<TypeId>,
    ),
    Call(FunctionId),
    Typename(TypeId),
    NameSet(Vec<String>),
    EnumVariant(
        Span,
        String,
        TypeId,
        Vec<(Option<String>, TypeId)>,
        Option<NumberConstant>,
    ),
}
