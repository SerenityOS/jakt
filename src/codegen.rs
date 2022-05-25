/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

use crate::compiler::{UNKNOWN_TYPE_ID, VOID_TYPE_ID};
use crate::typechecker::{
    CheckedCall, CheckedEnum, CheckedEnumVariant, CheckedMatchBody, CheckedMatchCase,
    FunctionGenericParameter, ScopeId,
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
use std::collections::{HashMap, HashSet};

const INDENT_SIZE: usize = 4;

pub fn codegen(project: &Project, scope: &Scope) -> String {
    let mut output = String::new();

    output.push_str("#include <lib.h>\n");

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

    for (_, struct_id, _) in &scope.structs {
        let structure = &project.structs[*struct_id];
        let struct_output = codegen_struct_predecl(structure, project);

        if !struct_output.is_empty() {
            output.push_str(&struct_output);
            output.push('\n');
        }
    }

    for (_, enum_id, _) in &scope.enums {
        let enum_ = &project.enums[*enum_id];
        let enum_output = codegen_enum_predecl(enum_, project);

        if !enum_output.is_empty() {
            output.push_str(&enum_output);
            output.push('\n');
        }
    }

    output.push('\n');

    // Figure out the right order to output the structs
    // This is necessary as C++ requires a type to be defined before it's used as a value type,
    // we can ignore the generic types as they are only resolved when used by other non-generic code.
    let type_dependency_graph = produce_type_dependency_graph(project, scope);
    let mut seen_types = HashSet::new();
    for type_id in type_dependency_graph.keys() {
        let mut traversal = Vec::new();
        postorder_traversal(
            project,
            *type_id,
            &mut seen_types,
            &type_dependency_graph,
            &mut traversal,
        );

        for type_id in traversal {
            let type_ = &project.types[type_id];
            seen_types.insert(type_id);
            match type_ {
                Type::Enum(enum_id) => {
                    let enum_ = &project.enums[*enum_id];
                    let enum_output = codegen_enum(enum_, project);

                    if !enum_output.is_empty() {
                        output.push_str(&enum_output);
                        output.push('\n');
                    }
                }
                Type::Struct(struct_id) => {
                    let structure = &project.structs[*struct_id];
                    let struct_output = codegen_struct(structure, project);

                    if !struct_output.is_empty() {
                        output.push_str(&struct_output);
                        output.push('\n');
                    }
                }
                _ => panic!("Unexpected type in dependency graph: {:?}", type_),
            }
        }
    }

    for (_, struct_id, _) in &scope.structs {
        let structure = &project.structs[*struct_id];
        if seen_types.contains(&structure.type_id) {
            continue;
        }
        let struct_output = codegen_struct(structure, project);

        if !struct_output.is_empty() {
            output.push_str(&struct_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for (_, enum_id, _) in &scope.enums {
        let enum_ = &project.enums[*enum_id];
        if seen_types.contains(&enum_.type_id) {
            continue;
        }
        let enum_output = codegen_enum(enum_, project);
        if !enum_output.is_empty() {
            output.push_str(&enum_output);
            output.push('\n');
        }
    }

    output.push('\n');

    for (_, function_id, _) in &scope.functions {
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

    for (_, function_id, _) in &scope.functions {
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

    for (_, struct_id, _) in &scope.structs {
        let struct_id = *struct_id;
        let structure = &project.structs[struct_id];
        if structure.definition_linkage == DefinitionLinkage::External {
            continue;
        }
        if !structure.generic_parameters.is_empty() {
            continue;
        }

        let scope = &project.scopes[structure.scope_id];
        for (_, function_id, _) in &scope.functions {
            let function = &project.functions[*function_id];
            if function.linkage != FunctionLinkage::ImplicitConstructor {
                let function_output =
                    codegen_function_in_namespace(function, Some(structure.type_id), project);

                output.push_str(&function_output);
                output.push('\n');
            }
        }
    }

    output
}

fn codegen_enum_predecl(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.definition_type == DefinitionType::Class {
        codegen_recursive_enum_predecl(enum_, project)
    } else {
        codegen_nonrecursive_enum_predecl(enum_, project)
    }
}

fn codegen_enum(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.definition_type == DefinitionType::Class {
        codegen_recursive_enum(enum_, project)
    } else {
        codegen_nonrecursive_enum(enum_, project)
    }
}

fn codegen_nonrecursive_enum(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.underlying_type_id.is_some() {
        let type_id = enum_.underlying_type_id.unwrap();
        if is_integer(type_id) {
            let mut output = String::new();

            output.push_str("enum class ");
            output.push_str(&enum_.name);
            output.push_str(": ");
            output.push_str(&codegen_type(type_id, project));
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
                    output.push_str(&codegen_type(member.type_id, project));
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

fn codegen_nonrecursive_enum_predecl(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.underlying_type_id.is_some() {
        let type_id = enum_.underlying_type_id.unwrap();
        if is_integer(type_id) {
            let mut output = String::new();

            output.push_str("enum class ");
            output.push_str(&enum_.name);
            output.push_str(": ");
            output.push_str(&codegen_type(type_id, project));
            output.push_str(";\n");
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
            CheckedEnumVariant::StructLike(name, _, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(";\n");
            }
            CheckedEnumVariant::Untyped(name, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(";\n");
            }
            CheckedEnumVariant::Typed(name, _, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(";\n");
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
    output.push(';');

    output
}

fn codegen_recursive_enum_predecl(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.underlying_type_id.is_some() {
        let type_id = enum_.underlying_type_id.unwrap();
        if is_integer(type_id) {
            let mut output = String::new();

            output.push_str("enum class ");
            output.push_str(&enum_.name);
            output.push_str(": ");
            output.push_str(&codegen_type(type_id, project));
            output.push_str(";\n");
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
            CheckedEnumVariant::StructLike(name, _, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(";\n");
            }
            CheckedEnumVariant::Untyped(name, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(";\n");
            }
            CheckedEnumVariant::Typed(name, _, _) => {
                if is_generic {
                    output.push_str("    template<");
                    output.push_str(template_args.as_str());
                    output.push_str(">\n");
                }
                output.push_str("    struct ");
                output.push_str(name);
                output.push_str(";\n");
            }
            _ => (),
        }
    }
    output.push_str("}\n");

    // Now declare the variant itself.
    if is_generic {
        output.push_str("template<");
        output.push_str(template_args.as_str());
        output.push_str(">\n");
    }
    output.push_str("struct ");
    output.push_str(&enum_.name);
    output.push(';');

    output
}

fn codegen_recursive_enum(enum_: &CheckedEnum, project: &Project) -> String {
    if enum_.underlying_type_id.is_some() {
        let type_id = enum_.underlying_type_id.unwrap();
        if is_integer(type_id) {
            let mut output = String::new();

            output.push_str("enum class ");
            output.push_str(&enum_.name);
            output.push_str(": ");
            output.push_str(&codegen_type(type_id, project));
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
                    output.push_str(&codegen_type(member.type_id, project));
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
    output.push_str("> ");
    if enum_.definition_type == DefinitionType::Class {
        output.push_str(", public RefCounted<");
        output.push_str(&enum_.name);
        if is_generic {
            output.push('<');
            output.push_str(generic_parameter_names.join(", ").as_str());
            output.push('>');
        }
        output.push('>');
    }
    output.push_str(" {\n");

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

    if enum_.definition_type == DefinitionType::Class {
        let mut fully_instantiated_name = enum_.name.clone();
        if is_generic {
            fully_instantiated_name.push('<');
            fully_instantiated_name.push_str(generic_parameter_names.join(", ").as_str());
            fully_instantiated_name.push('>');
        }
        output.push_str(
            "    template<typename V, typename... Args> static auto create(Args&&... args) {\n",
        );
        output.push_str(format!("        return adopt_nonnull_ref_or_enomem(new (nothrow) {}(V(forward<Args>(args)...)));\n", fully_instantiated_name).as_str());
        output.push_str("    }\n");
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
                "class {} : public RefCounted<{}>, public Weakable<{}> {{\n",
                structure.name, structure.name, structure.name
            ));
            // As we should test the visibility before codegen, we take a simple
            // approach to codegen
            output.push_str("  public:\n");

            // Make sure emitted classes always have a vtable.
            output.push_str(&format!("    virtual ~{}() = default;\n", structure.name));
        }
        DefinitionType::Struct => {
            output.push_str(&format!("struct {}", structure.name));
            output.push_str(" {\n");
            output.push_str("  public:\n");
        }
    }

    for field in &structure.fields {
        output.push_str(&codegen_indent(INDENT_SIZE));

        output.push_str(&codegen_type(field.type_id, project));
        output.push(' ');
        output.push_str(&field.name);
        output.push_str(";\n");
    }

    let scope = &project.scopes[structure.scope_id];
    for (_, function_id, _) in &scope.functions {
        let function = &project.functions[*function_id];
        if function.linkage == FunctionLinkage::ImplicitConstructor {
            let function_output = codegen_constructor(function, project);

            output.push_str(&codegen_indent(INDENT_SIZE));
            output.push_str(&function_output);
            output.push('\n');
        } else {
            output.push_str(&codegen_indent(INDENT_SIZE));
            let method_output = if structure.generic_parameters.is_empty() {
                codegen_function_predecl(function, project)
            } else {
                codegen_function(function, project)
            };
            output.push_str(&method_output);
        }
    }

    output.push_str("};");
    output
}

fn codegen_function_predecl(function: &CheckedFunction, project: &Project) -> String {
    let mut output = String::new();

    if function.linkage == FunctionLinkage::External {
        output.push_str("extern ");
    }

    if !function.generic_parameters.is_empty() {
        output.push_str("template <");
    }
    let mut first = true;
    for generic_parameter in &function.generic_parameters {
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
    if !function.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    if function.name == "main" {
        output.push_str("ErrorOr<int>");
    } else {
        if function.is_static() && function.linkage != FunctionLinkage::External {
            output.push_str("static ");
        }
        let return_type = if function.throws {
            format!(
                "ErrorOr<{}>",
                &codegen_type(function.return_type_id, project)
            )
        } else {
            codegen_type(function.return_type_id, project)
        };

        output.push_str(&return_type);
    }
    output.push(' ');
    output.push_str(&function.name);
    output.push('(');

    let mut first = true;
    for param in &function.params {
        if first && param.variable.name == "this" {
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
        output.push_str(&codegen_type(param.variable.type_id, project));
        output.push(' ');
        output.push_str(&param.variable.name);
    }

    if !function.is_static() && !function.is_mutating() {
        output.push_str(") const;");
    } else {
        output.push_str(");");
    }

    output
}

fn codegen_function(function: &CheckedFunction, project: &Project) -> String {
    codegen_function_in_namespace(function, None, project)
}

fn codegen_function_in_namespace(
    function: &CheckedFunction,
    containing_struct: Option<TypeId>,
    project: &Project,
) -> String {
    let mut output = String::new();

    if !function.generic_parameters.is_empty() {
        output.push_str("template <");
    }
    let mut first = true;
    for generic_parameter in &function.generic_parameters {
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
    if !function.generic_parameters.is_empty() {
        output.push_str(">\n");
    }

    if function.name == "main" {
        output.push_str("ErrorOr<int>");
    } else {
        if function.is_static() && containing_struct.is_none() {
            output.push_str("static ");
        }
        let return_type = if function.throws {
            format!(
                "ErrorOr<{}>",
                &codegen_type(function.return_type_id, project)
            )
        } else {
            codegen_type(function.return_type_id, project)
        };

        output.push_str(&return_type);
    }
    output.push(' ');
    let is_main = function.name == "main" && containing_struct.is_none();
    if is_main {
        output.push_str("JaktInternal::main");
    } else {
        let qualifier = containing_struct
            .map(|type_id| codegen_type_possibly_as_namespace(type_id, project, true));
        if let Some(qualifier) = qualifier {
            if !qualifier.is_empty() {
                output.push_str(&qualifier);
                output.push_str("::");
            }
        }
        output.push_str(&function.name);
    }
    output.push('(');

    if is_main && function.params.is_empty() {
        output.push_str("Array<String>");
    }

    let mut first = true;

    for param in &function.params {
        if param.variable.name == "this" {
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

        output.push_str(&codegen_type(param.variable.type_id, project));
        output.push(' ');
        output.push_str(&param.variable.name);
    }
    output.push(')');

    if !function.is_static() && !function.is_mutating() {
        output.push_str(" const");
    }

    output.push_str("\n{\n");
    output.push_str(&codegen_indent(INDENT_SIZE));

    // Put the return type in scope.
    if is_main {
        output.push_str("using _JaktCurrentFunctionReturnType = ErrorOr<int>;\n");
    } else {
        if function.return_type_id == UNKNOWN_TYPE_ID {
            panic!("Function type unknown at codegen time in {}", function.name);
        }
        if function.throws {
            output.push_str(&format!(
                "using _JaktCurrentFunctionReturnType = ErrorOr<{}>;\n",
                codegen_type(function.return_type_id, project)
            ));
        } else {
            output.push_str(&format!(
                "using _JaktCurrentFunctionReturnType = {};\n",
                codegen_type(function.return_type_id, project)
            ));
        }
    }

    let block = codegen_block(
        INDENT_SIZE,
        function
            .block
            .as_ref()
            .expect("Function being generated must be checked"),
        project,
    );
    output.push_str(&block);

    if is_main {
        output.push_str(&codegen_indent(INDENT_SIZE));
        output.push_str("return 0;\n");
    } else if function.throws && function.return_type_id == VOID_TYPE_ID {
        output.push_str(&codegen_indent(INDENT_SIZE));
        output.push_str("return {};\n");
    }

    output.push_str("}\n");

    output
}

fn codegen_constructor(function: &CheckedFunction, project: &Project) -> String {
    let type_id = function.return_type_id;
    let type_ = &project.types[type_id];

    match type_ {
        Type::Struct(struct_id) => {
            let structure = &project.structs[*struct_id];

            if structure.definition_type == DefinitionType::Class {
                let mut output = String::new();

                // First, generate a private constructor:
                output.push_str("private:\n");

                output.push_str(&format!("explicit {}(", function.name));
                let mut first = true;
                for param in &function.params {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }
                    output.push_str(&codegen_type(param.variable.type_id, project));
                    output.push_str("&& a_");
                    output.push_str(&param.variable.name);
                }
                output.push(')');

                if !function.params.is_empty() {
                    output.push_str(": ");
                    let mut first = true;
                    for param in &function.params {
                        if !first {
                            output.push_str(", ");
                        } else {
                            first = false;
                        }
                        output.push_str(&param.variable.name);
                        output.push_str("(move(a_");
                        output.push_str(&param.variable.name);
                        output.push_str("))");
                    }
                }

                output.push_str("{}\n");

                output.push_str("public:\n");
                output.push_str(&format!(
                    "static ErrorOr<NonnullRefPtr<{}>> create",
                    function.name
                ));

                output.push('(');

                let mut first = true;
                for param in &function.params {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    output.push_str(&codegen_type(param.variable.type_id, project));
                    output.push(' ');
                    output.push_str(&param.variable.name);
                }
                output.push_str(&format!(
                    ") {{ auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) {} (",
                    function.name
                ));

                let mut first = true;
                for param in &function.params {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    output.push_str("move(");
                    output.push_str(&param.variable.name);
                    output.push(')');
                }

                output.push_str("))); return o; }");

                output
            } else {
                let mut output = String::new();

                output.push_str(&function.name);
                output.push('(');

                let mut first = true;
                for param in &function.params {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }

                    output.push_str(&codegen_type(param.variable.type_id, project));
                    output.push_str(" a_");
                    output.push_str(&param.variable.name);
                }
                output.push_str(") ");

                if !function.params.is_empty() {
                    output.push(':');
                }

                let mut first = true;
                for param in &function.params {
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
    let type_ = &project.types[type_id];

    match type_ {
        Type::Struct(struct_id) => project.structs[*struct_id].name.clone(),
        _ => panic!("codegen_struct_type on non-struct"),
    }
}

pub fn codegen_namespace_qualifier(scope_id: ScopeId, project: &Project) -> String {
    let mut output = String::new();

    let mut current_scope_id = project.scopes[scope_id].parent;

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
    codegen_type_possibly_as_namespace(type_id, project, false)
}

pub fn codegen_type_possibly_as_namespace(
    type_id: TypeId,
    project: &Project,
    as_namespace: bool,
) -> String {
    let mut output = String::new();
    let ty = &project.types[type_id];

    let weakptr_struct_id = project
        .find_struct_in_scope(0, "WeakPtr")
        .expect("internal error: can't find builtin WeakPtr type");

    match ty {
        Type::RawPtr(type_id) => {
            format!("{}*", codegen_type(*type_id, project))
        }
        Type::GenericInstance(struct_id, inner_type_ids) if *struct_id == weakptr_struct_id => {
            let inner_type_id = inner_type_ids[0];
            if let Type::Struct(struct_id) = project.types[inner_type_id] {
                output.push_str("WeakPtr<");
                output.push_str(&codegen_namespace_qualifier(
                    project.structs[struct_id].scope_id,
                    project,
                ));
                output.push_str(&project.structs[struct_id].name);
                output.push('>');
            }

            output
        }
        Type::GenericInstance(struct_id, inner_type_ids) => {
            output.push_str(&codegen_namespace_qualifier(
                project.structs[*struct_id].scope_id,
                project,
            ));
            output.push_str(&project.structs[*struct_id].name.clone());
            output.push('<');
            let mut first = true;
            for type_id in inner_type_ids {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&codegen_type(*type_id, project));
            }

            output.push('>');
            output
        }
        Type::GenericEnumInstance(enum_id, inner_type_ids) => {
            let mut close_tag = false;
            if !as_namespace && project.enums[*enum_id].definition_type == DefinitionType::Class {
                output.push_str("NonnullRefPtr<");
                let qualifier =
                    codegen_namespace_qualifier(project.enums[*enum_id].scope_id, project);
                if !qualifier.is_empty() {
                    output.push_str("typename ");
                    output.push_str(&qualifier);
                }
                output.push_str(&project.enums[*enum_id].name);
                close_tag = true;
            } else {
                let qualifier =
                    codegen_namespace_qualifier(project.enums[*enum_id].scope_id, project);
                if !qualifier.is_empty() {
                    output.push_str("typename ");
                    output.push_str(&qualifier);
                }
                output.push_str(&project.enums[*enum_id].name);
            }
            output.push('<');
            let mut first = true;
            for type_id in inner_type_ids {
                if !first {
                    output.push_str(", ");
                } else {
                    first = false;
                }

                output.push_str(&codegen_type(*type_id, project));
            }
            output.push('>');
            if close_tag {
                output.push('>');
            }
            output
        }
        Type::Struct(struct_id) => {
            if !as_namespace && project.structs[*struct_id].definition_type == DefinitionType::Class
            {
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
            if !as_namespace && project.enums[*enum_id].definition_type == DefinitionType::Class {
                output.push_str("NonnullRefPtr<");
                let qualifier =
                    codegen_namespace_qualifier(project.enums[*enum_id].scope_id, project);
                if !qualifier.is_empty() {
                    output.push_str("typename ");
                    output.push_str(&qualifier);
                }
                output.push_str(&project.enums[*enum_id].name);
                output.push('>');
            } else {
                let qualifier =
                    codegen_namespace_qualifier(project.enums[*enum_id].scope_id, project);
                if !qualifier.is_empty() {
                    output.push_str("typename ");
                    output.push_str(&qualifier);
                }
                output.push_str(&project.enums[*enum_id].name);
            }

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

    output.push_str(&codegen_indent(indent));
    output.push_str("{\n");

    for stmt in &checked_block.stmts {
        let stmt = codegen_statement(indent + INDENT_SIZE, stmt, project);

        output.push_str(&stmt);
    }

    output.push_str(&codegen_indent(indent));
    output.push_str("}\n");

    output
}

fn codegen_statement(indent: usize, stmt: &CheckedStatement, project: &Project) -> String {
    let mut output = String::new();

    output.push_str(&codegen_indent(indent));

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
            output.push_str(&codegen_type(var_decl.type_id, project));
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
            panic!("Garbage statement in codegen");
        }
    }

    output
}

fn codegen_checked_binary_op(
    indent: usize,
    lhs: &CheckedExpression,
    rhs: &CheckedExpression,
    type_id: TypeId,
    op: &BinaryOperator,
    project: &Project,
) -> String {
    let mut output = String::new();

    output.push_str("JaktInternal::");

    match op {
        BinaryOperator::Add => output.push_str("checked_add"),
        BinaryOperator::Subtract => output.push_str("checked_sub"),
        BinaryOperator::Multiply => output.push_str("checked_mul"),
        BinaryOperator::Divide => output.push_str("checked_div"),
        BinaryOperator::Modulo => output.push_str("checked_mod"),
        _ => panic!(
            "Checked binary operation codegen is not supported for BinaryOperator::{:?}",
            op
        ),
    };

    output.push('<');
    output.push_str(&codegen_type(type_id, project));
    output.push_str(">(");
    output.push_str(&codegen_expr(indent, lhs, project));
    output.push_str(", ");
    output.push_str(&codegen_expr(indent, rhs, project));
    output.push(')');

    output
}

fn codegen_checked_binary_op_assign(
    indent: usize,
    lhs: &CheckedExpression,
    rhs: &CheckedExpression,
    type_id: TypeId,
    op: &BinaryOperator,
    project: &Project,
) -> String {
    let mut output = String::new();

    output.push('{');
    output.push_str("auto& _jakt_ref = ");
    output.push_str(&codegen_expr(indent, lhs, project));
    output.push(';');
    output.push_str("_jakt_ref = JaktInternal::");

    match op {
        BinaryOperator::AddAssign => output.push_str("checked_add"),
        BinaryOperator::SubtractAssign => output.push_str("checked_sub"),
        BinaryOperator::MultiplyAssign => output.push_str("checked_mul"),
        BinaryOperator::DivideAssign => output.push_str("checked_div"),
        BinaryOperator::ModuloAssign => output.push_str("checked_mod"),
        _ => panic!(
            "Checked binary operation assignment codegen is not supported for BinaryOperator::{:?}",
            op
        ),
    };

    output.push('<');
    output.push_str(&codegen_type(type_id, project));
    output.push_str(">(_jakt_ref, ");
    output.push_str(&codegen_expr(indent, rhs, project));
    output.push_str(");");
    output.push('}');

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
            output.push_str("JaktInternal::OptionalNone()");
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
        CheckedExpression::ByteConstant(b, _) => {
            if b.is_ascii() {
                output.push('\'');
                output.push(*b as char);
                output.push('\'');
            } else {
                output.push_str(&format!("0x{:x}", *b));
            }
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
            NumericConstant::F32(value) => {
                output.push_str("static_cast<f32>(");
                output.push_str(&value.to_string());
                output.push(')');
            }
            NumericConstant::F64(value) => {
                output.push_str("static_cast<f64>(");
                output.push_str(&value.to_string());
                output.push(')');
            }
        },
        CheckedExpression::NamespacedVar(ns, var, _) => {
            for ns in ns.iter() {
                if ns.name.is_some() {
                    output.push_str(ns.name.as_ref().unwrap());
                    output.push_str("::");
                }
            }
            output.push_str(&var.name);
        }
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
            if call.name == "print" {
                output.push_str("out(");
                for (i, param) in call.args.iter().enumerate() {
                    output.push_str(&codegen_expr(indent, &param.1, project));
                    if i != call.args.len() - 1 {
                        output.push(',');
                    }
                }
                output.push(')');
            } else if call.name == "println" {
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
                if call.linkage == FunctionLinkage::ImplicitConstructor {
                    let type_id = call.type_id;
                    let ty = &project.types[type_id];

                    output.push_str(&codegen_namespace_path(call, project));
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
                } else if call.linkage == FunctionLinkage::ImplicitEnumConstructor {
                    let type_id = call.type_id;
                    let type_ = &project.types[type_id];
                    match type_ {
                        Type::Enum(enum_id) | Type::GenericEnumInstance(enum_id, _) => {
                            let enum_ = &project.enums[*enum_id];

                            if enum_.definition_type == DefinitionType::Struct {
                                output.push_str("typename ");
                                output.push_str(&codegen_namespace_path(call, project));
                                output.push_str(&call.name);
                            } else {
                                output.push_str(&codegen_namespace_path(call, project));
                                output.push_str("template create<");
                                output.push_str("typename ");
                                output.push_str(&codegen_type_possibly_as_namespace(
                                    type_id, project, true,
                                ));
                                output.push_str("::");
                                output.push_str(&call.name);
                                output.push('>');
                            }
                        }
                        _ => {
                            panic!("internal error: constructor expected enum type")
                        }
                    }
                } else {
                    output.push_str(&codegen_namespace_path(call, project));
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
                x => match &project.types[x.type_id_or_type_var()] {
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
        CheckedExpression::Match(expr, cases, _, return_type_id) => {
            let expr_type = &project.types[expr.type_id_or_type_var()];
            let id = match expr_type {
                Type::GenericEnumInstance(id, _) | Type::Enum(id) => *id,
                _ => {
                    panic!("Expected enum type");
                }
            };
            let enum_ = &project.enums[id];
            let needs_deref = enum_.definition_type == DefinitionType::Class;
            match enum_.underlying_type_id {
                Some(_) => {
                    output.push_str("JAKT_RESOLVE_EXPLICIT_VALUE_OR_RETURN(([&]() -> JaktInternal::ExplicitValueOrReturn<");
                    output.push_str(&codegen_type(*return_type_id, project));
                    output.push_str(", ");
                    output.push_str("_JaktCurrentFunctionReturnType");
                    output.push_str("> { \n");
                    output.push_str("switch (");
                    if needs_deref {
                        output.push('*');
                    }
                    output.push_str(&codegen_expr(indent, expr, project));
                    output.push_str(") {\n");
                    for case in cases {
                        output.push_str("case ");
                        output.push_str(&codegen_type_possibly_as_namespace(
                            expr.type_id_or_type_var(),
                            project,
                            true,
                        ));
                        output.push_str("::");
                        match case {
                            CheckedMatchCase::EnumVariant {
                                variant_name, body, ..
                            } => {
                                output.push_str(variant_name);
                                output.push_str(":\n");
                                output.push_str(&codegen_indent(indent));
                                match body {
                                    CheckedMatchBody::Expression(expr) => {
                                        output.push_str("return JaktInternal::ExplicitValue(");
                                        output.push_str(&codegen_expr(0, expr, project));
                                        output.push_str(");");
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
                    output.push(')');
                    if needs_deref {
                        output.push_str("->");
                    } else {
                        output.push('.');
                    }
                    output.push_str("visit(");
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
                                        output.push_str(&codegen_type_possibly_as_namespace(
                                            *subject_type_id,
                                            project,
                                            true,
                                        ));
                                        output.push_str("::");
                                        output.push_str(name);
                                        output.push_str(
                                            " const& __jakt_match_value) -> JaktInternal::ExplicitValueOrReturn<",
                                        );
                                        output.push_str(&codegen_type(*return_type_id, project));
                                        output.push_str(", ");
                                        output.push_str("_JaktCurrentFunctionReturnType");
                                        output.push('>');
                                        output.push_str(" {\n");
                                        output.push_str("   ");
                                        if !args.is_empty() {
                                            let var = project
                                                .find_var_in_scope(*scope_id, args[0].1.as_str())
                                                .unwrap();
                                            output.push_str(
                                                codegen_type(var.type_id, project).as_str(),
                                            );
                                            output.push_str(" const& ");
                                            output.push_str(args[0].1.as_str());
                                            output.push_str(" = __jakt_match_value.value;\n");
                                        }
                                    }
                                    CheckedEnumVariant::Untyped(name, _) => {
                                        output.push_str("typename ");
                                        output.push_str(&codegen_type_possibly_as_namespace(
                                            *subject_type_id,
                                            project,
                                            true,
                                        ));
                                        output.push_str("::");
                                        output.push_str(name);
                                        output.push_str(
                                            " const& __jakt_match_value) -> JaktInternal::ExplicitValueOrReturn<",
                                        );
                                        output.push_str(&codegen_type(*return_type_id, project));
                                        output.push_str(", ");
                                        output.push_str("_JaktCurrentFunctionReturnType");
                                        output.push('>');
                                        output.push_str(" {\n");
                                    }
                                    CheckedEnumVariant::StructLike(name, _, _) => {
                                        output.push_str("typename ");
                                        output.push_str(&codegen_type_possibly_as_namespace(
                                            *subject_type_id,
                                            project,
                                            true,
                                        ));
                                        output.push_str("::");
                                        output.push_str(name);
                                        output.push_str(
                                            " const& __jakt_match_value) -> JaktInternal::ExplicitValueOrReturn<",
                                        );
                                        output.push_str(&codegen_type(*return_type_id, project));
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
                                                    codegen_type(var.type_id, project).as_str(),
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
                                        output.push_str("\nreturn JaktInternal::ExplicitValue<");
                                        output.push_str(&codegen_type(*return_type_id, project));
                                        output.push_str(">();\n");
                                    }
                                    CheckedMatchBody::Expression(expr) => {
                                        if expr.type_id_or_type_var() == VOID_TYPE_ID {
                                            output.push_str("   return (");
                                            output.push_str(&codegen_expr(
                                                indent + 1,
                                                expr,
                                                project,
                                            ));
                                            output.push_str(
                                                "), JaktInternal::ExplicitValue<void>();\n",
                                            );
                                        } else {
                                            output
                                                .push_str("   return JaktInternal::ExplicitValue(");
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
                    output.push_str("JaktInternal::arithmetic_shift_right(");
                    output.push_str(&codegen_expr(indent, lhs, project));
                    output.push_str(", ");
                    output.push_str(&codegen_expr(indent, rhs, project));
                    output.push(')');
                }
                BinaryOperator::Add
                | BinaryOperator::Subtract
                | BinaryOperator::Multiply
                | BinaryOperator::Divide
                | BinaryOperator::Modulo
                    if is_integer(expr.type_id_or_type_var()) =>
                {
                    output.push_str(&codegen_checked_binary_op(
                        indent,
                        lhs,
                        rhs,
                        expr.type_id_or_type_var(),
                        op,
                        project,
                    ))
                }
                BinaryOperator::AddAssign
                | BinaryOperator::SubtractAssign
                | BinaryOperator::MultiplyAssign
                | BinaryOperator::DivideAssign
                | BinaryOperator::ModuloAssign
                    if is_integer(expr.type_id_or_type_var()) =>
                {
                    output.push_str(&codegen_checked_binary_op_assign(
                        indent,
                        lhs,
                        rhs,
                        expr.type_id_or_type_var(),
                        op,
                        project,
                    ))
                }
                _ => {
                    if *op == BinaryOperator::Assign {
                        if let CheckedExpression::IndexedDictionary(expr, index, ..) = lhs.as_ref()
                        {
                            output.push_str(&codegen_expr(0, expr, project));
                            output.push_str(".set(");
                            output.push_str(&codegen_expr(0, index, project));
                            output.push_str(", ");
                            output.push_str(&codegen_expr(0, rhs, project));
                            output.push_str("))");
                            return output;
                        }
                    }

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
        CheckedExpression::Array(vals, fill_size_expr, _, type_id) => {
            let value_type_id = match &project.types[*type_id] {
                Type::GenericInstance(_, v) => v[0],
                _ => panic!("Internal error: Array doesn't have inner type"),
            };

            if let Some(fill_size_expr) = fill_size_expr {
                output.push_str("(TRY(Array<");
                output.push_str(&codegen_type(value_type_id, project));
                output.push_str(">::filled(");
                output.push_str(&codegen_expr(indent, fill_size_expr, project));
                output.push_str(", ");
                output.push_str(&codegen_expr(indent, vals.first().unwrap(), project));
                output.push_str(")))");
            } else {
                // (Array({1, 2, 3}))
                output.push_str("(Array<");
                output.push_str(&codegen_type(value_type_id, project));
                output.push_str(">({");
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
        CheckedExpression::Dictionary(vals, _, type_id) => {
            // (Dictionary({1, 2, 3}))
            let (key_type_id, value_type_id) = match &project.types[*type_id] {
                Type::GenericInstance(_, v) => (v[0], v[1]),
                _ => panic!("Internal error: Dictionary doesn't have inner type"),
            };

            output.push_str(&format!(
                "(TRY(Dictionary<{}, {}>::create_with_entries({{",
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
            output.push_str("})))");
        }
        CheckedExpression::Set(values, _, type_id) => {
            // (Set({1, 2, 3}))
            let value_type_id = match &project.types[*type_id] {
                Type::GenericInstance(_, v) => v[0],
                _ => panic!("Internal error: Set doesn't have inner type"),
            };

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
                x => match &project.types[x.type_id_or_type_var()] {
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

fn codegen_namespace_path(call: &CheckedCall, project: &Project) -> String {
    let mut output = String::new();
    for (idx, namespace) in call.namespace.iter().enumerate() {
        // hack warning: this is to get around C++'s limitation that a constructor
        // can't be called like other static methods
        if idx == call.namespace.len() - 1 && namespace.name == call.name {
            break;
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

    output
}

fn codegen_indent(indent: usize) -> String {
    " ".repeat(indent)
}

fn extract_dependencies_from(
    project: &Project,
    type_id: TypeId,
    deps: &mut HashSet<TypeId>,
    graph: &HashMap<TypeId, Vec<TypeId>>,
    top_level: bool,
) {
    if let Some(existing_deps) = graph.get(&type_id) {
        for dep in existing_deps {
            deps.insert(*dep);
        }
        return;
    }

    let type_ = &project.types[type_id];
    match type_ {
        Type::GenericInstance(struct_id, _) | Type::Struct(struct_id) => {
            let struct_ = &project.structs[*struct_id];
            if struct_.definition_linkage == DefinitionLinkage::External {
                // This type is defined somewhere else,
                // so we can skip marking it as a dependency.
                return;
            }

            if struct_.definition_type == DefinitionType::Class && !top_level {
                // We store and pass these as pointers, so we don't need to
                // include them in the dependency graph.
                return;
            }

            deps.insert(struct_.type_id);
            // The struct's fields are also dependencies.
            for field in &struct_.fields {
                extract_dependencies_from(project, field.type_id, deps, graph, false);
            }
        }
        Type::GenericEnumInstance(enum_id, _) | Type::Enum(enum_id) => {
            let enum_ = &project.enums[*enum_id];
            if enum_.definition_linkage == DefinitionLinkage::External {
                // This type is defined somewhere else,
                // so we can skip marking it as a dependency.
                return;
            }

            if enum_.definition_type == DefinitionType::Class && !top_level {
                // We store and pass these as pointers, so we don't need to
                // include them in the dependency graph.
                return;
            }

            deps.insert(enum_.type_id);
            if let Some(type_id) = enum_.underlying_type_id {
                extract_dependencies_from(project, type_id, deps, graph, false);
            }

            // The enum variants' types are also dependencies.
            for variant in &enum_.variants {
                match variant {
                    CheckedEnumVariant::Typed(_, type_id, _) => {
                        extract_dependencies_from(project, *type_id, deps, graph, false);
                    }
                    CheckedEnumVariant::StructLike(_, fields, _) => {
                        for field in fields {
                            extract_dependencies_from(project, field.type_id, deps, graph, false);
                        }
                    }
                    _ => {}
                }
            }
        }
        Type::Builtin => {}
        Type::TypeVariable(_) => {}
        Type::RawPtr(_) => {}
    }
}

fn produce_type_dependency_graph(project: &Project, scope: &Scope) -> HashMap<TypeId, Vec<TypeId>> {
    let mut graph = HashMap::new();

    for (_, type_id, _) in &scope.types {
        let mut deps = HashSet::new();
        extract_dependencies_from(project, *type_id, &mut deps, &graph, true);
        graph.insert(*type_id, deps.into_iter().collect());
    }

    graph
}

fn postorder_traversal(
    project: &Project,
    type_id: TypeId,
    visited: &mut HashSet<TypeId>,
    graph: &HashMap<TypeId, Vec<TypeId>>,
    output: &mut Vec<TypeId>,
) {
    if visited.contains(&type_id) {
        return;
    }

    visited.insert(type_id);

    if let Some(deps) = graph.get(&type_id) {
        for dep in deps {
            postorder_traversal(project, *dep, visited, graph, output);
        }
    }

    output.push(type_id);
}
