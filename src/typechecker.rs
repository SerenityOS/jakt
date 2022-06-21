/*
 * !!! DEPRECATION WARNING !!!
 * We're not doing any more feature development in the rust-based compiler at this point.
 * It'll be limited to bug fixes and necessities only.
 *
 * New features should go into the self-hosted compiler.
 */

/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

use std::collections::{HashMap, HashSet};

use crate::compiler::{PRELUDE_SCOPE_ID, STRING_TYPE_ID};
use crate::parser::{BinaryOperator, MatchBody, MatchCase, ParsedVarDecl, Visibility};
use crate::Compiler;
use crate::{
    compiler::{
        BOOL_TYPE_ID, CCHAR_TYPE_ID, CINT_TYPE_ID, F32_TYPE_ID, F64_TYPE_ID, I16_TYPE_ID,
        I32_TYPE_ID, I64_TYPE_ID, I8_TYPE_ID, U16_TYPE_ID, U32_TYPE_ID, U64_TYPE_ID, U8_TYPE_ID,
        UNKNOWN_TYPE_ID, USIZE_TYPE_ID, VOID_TYPE_ID,
    },
    error::JaktError,
    lexer::Span,
    parser::{
        DefinitionLinkage, DefinitionType, EnumVariant, FunctionLinkage, ParsedBlock, ParsedCall,
        ParsedEnum, ParsedExpression, ParsedFunction, ParsedNamespace, ParsedStatement,
        ParsedStruct, ParsedType, TypeCast, UnaryOperator,
    },
};
use std::os::raw::{c_char, c_int};

#[derive(Debug, Clone, Copy, Hash, PartialEq, Eq, PartialOrd, Ord)]
pub struct ModuleId(pub usize);

impl ModuleId {
    pub fn invalid() -> Self {
        Self(usize::MAX)
    }
}

#[derive(Debug, Clone, Copy, Hash, PartialEq, Eq, PartialOrd, Ord)]
pub struct StructId(pub ModuleId, pub usize);

#[derive(Debug, Clone, Copy, Hash, PartialEq, Eq, PartialOrd, Ord)]
pub struct EnumId(pub ModuleId, pub usize);

#[derive(Debug, Clone, Copy, Hash, PartialEq, Eq, PartialOrd, Ord)]
pub struct FunctionId(pub ModuleId, pub usize);

#[derive(Debug, Clone, Copy, Hash, PartialEq, Eq, PartialOrd, Ord)]
pub struct ScopeId(pub ModuleId, pub usize); // remove ModuleId if it is not needed.

#[derive(Debug, Clone, Copy, Hash, PartialEq, Eq, PartialOrd, Ord)]
pub struct TypeId(pub ModuleId, pub usize);

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum StructOrEnumId {
    Struct(StructId),
    Enum(EnumId),
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum SafetyMode {
    Safe,
    Unsafe,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Type {
    Builtin,
    TypeVariable(String),
    // A GenericInstance is a generic that has known values for its type param
    // For example Foo<Bar> is an instance of the generic Foo<T>
    GenericInstance(StructId, Vec<TypeId>),
    GenericEnumInstance(EnumId, Vec<TypeId>),
    Struct(StructId),
    Enum(EnumId),
    RawPtr(TypeId),
}

pub fn is_integer(type_id: TypeId) -> bool {
    matches!(
        type_id,
        CCHAR_TYPE_ID
            | CINT_TYPE_ID
            | USIZE_TYPE_ID
            | I8_TYPE_ID
            | I16_TYPE_ID
            | I32_TYPE_ID
            | I64_TYPE_ID
            | U8_TYPE_ID
            | U16_TYPE_ID
            | U32_TYPE_ID
            | U64_TYPE_ID
    )
}

pub fn is_floating(type_id: TypeId) -> bool {
    matches!(type_id, F32_TYPE_ID | F64_TYPE_ID)
}

pub fn is_numeric(type_id: TypeId) -> bool {
    is_integer(type_id) || is_floating(type_id)
}

pub fn is_signed(type_id: TypeId) -> bool {
    match type_id {
        // c_char types can be both signed or unsigned values thus we have to check which variant
        // we have here. c_int on the other hand will always be signed.
        CCHAR_TYPE_ID => c_char::MIN < 0,
        USIZE_TYPE_ID | U8_TYPE_ID | U16_TYPE_ID | U32_TYPE_ID | U64_TYPE_ID => false,
        _ => true,
    }
}

pub fn flip_signedness(type_id: TypeId) -> Option<TypeId> {
    match type_id {
        I8_TYPE_ID => Some(U8_TYPE_ID),
        I16_TYPE_ID => Some(U16_TYPE_ID),
        I32_TYPE_ID => Some(U32_TYPE_ID),
        I64_TYPE_ID => Some(U64_TYPE_ID),
        U8_TYPE_ID => Some(I8_TYPE_ID),
        U16_TYPE_ID => Some(I16_TYPE_ID),
        U32_TYPE_ID => Some(I32_TYPE_ID),
        U64_TYPE_ID => Some(I64_TYPE_ID),
        // FIXME: What about the C types?
        _ => None,
    }
}

pub fn get_bits(type_id: TypeId) -> u32 {
    match type_id {
        BOOL_TYPE_ID => 8,
        I8_TYPE_ID => i8::BITS,
        I16_TYPE_ID => i16::BITS,
        I32_TYPE_ID => i32::BITS,
        I64_TYPE_ID => i64::BITS,
        U8_TYPE_ID => u8::BITS,
        U16_TYPE_ID => u16::BITS,
        U32_TYPE_ID => u32::BITS,
        U64_TYPE_ID => u64::BITS,
        F32_TYPE_ID => 32,
        F64_TYPE_ID => 64,
        CCHAR_TYPE_ID => c_char::BITS,
        CINT_TYPE_ID => c_int::BITS,
        USIZE_TYPE_ID => usize::BITS,
        _ => panic!("get_bits not supported for type {}", type_id.1),
    }
}

pub fn can_fit_number(type_id: TypeId, value: &NumberConstant) -> bool {
    match *value {
        NumberConstant::Signed(value) => match type_id {
            CCHAR_TYPE_ID => value >= c_char::MIN as i64 && value <= c_char::MAX as i64,
            CINT_TYPE_ID => value >= c_int::MIN as i64 && value <= c_int::MAX as i64,
            I8_TYPE_ID => value >= i8::MIN as i64 && value <= i8::MAX as i64,
            I16_TYPE_ID => value >= i16::MIN as i64 && value <= i16::MAX as i64,
            I32_TYPE_ID => value >= i32::MIN as i64 && value <= i32::MAX as i64,
            I64_TYPE_ID => true,
            U8_TYPE_ID => value >= 0 && value <= u8::MAX as i64,
            U16_TYPE_ID => value >= 0 && value <= u16::MAX as i64,
            U32_TYPE_ID => value >= 0 && value <= u32::MAX as i64,
            U64_TYPE_ID => value >= 0,
            // FIXME: Don't assume that usize is 64-bit
            USIZE_TYPE_ID => value >= 0,
            _ => false,
        },
        NumberConstant::Unsigned(value) => match type_id {
            I8_TYPE_ID => value <= i8::MAX as u64,
            I16_TYPE_ID => value <= i16::MAX as u64,
            I32_TYPE_ID => value <= i32::MAX as u64,
            I64_TYPE_ID => value <= i64::MAX as u64,
            U8_TYPE_ID => value <= u8::MAX as u64,
            U16_TYPE_ID => value <= u16::MAX as u64,
            U32_TYPE_ID => value <= u32::MAX as u64,
            // FIXME: Don't assume that usize is 64-bit
            USIZE_TYPE_ID => true,
            U64_TYPE_ID => true,
            _ => false,
        },
        NumberConstant::Floating(value) => match type_id {
            F32_TYPE_ID => value >= f32::MIN as f64 && value <= f32::MAX as f64,
            F64_TYPE_ID => true,
            _ => false,
        },
    }
}

// Uses optimal string alignment distance algorithm
// (https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance).
fn number_of_edits_between(a: &str, b: &str) -> usize {
    let a = a.as_bytes();
    let b = b.as_bytes();

    let mut d = Vec::with_capacity(a.len());
    for _ in 0..a.len() {
        d.push(vec![0; b.len()]);
    }

    // Set first element of each row to row_index.
    for (row_index, row) in d.iter_mut().enumerate() {
        row[0] = row_index;
    }

    // Set each column of first row to column_index
    for (column_index, column) in d[0].iter_mut().enumerate() {
        *column = column_index;
    }

    for i in 1..a.len() {
        for j in 1..b.len() {
            let cost = if a[i] == b[j] { 0 } else { 1 };
            let min = std::cmp::min;
            d[i][j] = min(
                min(
                    d[i - 1][j] + 1, // Deletion.
                    d[i][j - 1] + 1, // Insertion.
                ),
                d[i - 1][j - 1] + cost, // Substitution.
            );
            if i > 1 && j > 1 && a[i] == b[j - 1] && a[i - 1] == b[j] {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + 1); // Transposition.
            }
        }
    }
    d[a.len() - 1][b.len() - 1]
}

#[derive(Debug, Clone)]
pub struct Project {
    pub modules: Vec<Module>,
    pub current_module_index: usize,
    pub current_function_index: Option<FunctionId>,
    pub current_struct_type_id: Option<TypeId>,

    pub inside_defer: bool,

    pub checking_prelude: bool,
    pub cached_array_struct_id: Option<StructId>,
    pub cached_dictionary_struct_id: Option<StructId>,
    pub cached_error_struct_id: Option<StructId>,
    pub cached_optional_struct_id: Option<StructId>,
    pub cached_range_struct_id: Option<StructId>,
    pub cached_set_struct_id: Option<StructId>,
    pub cached_tuple_struct_id: Option<StructId>,
    pub cached_weakptr_struct_id: Option<StructId>,

    pub dump_type_hints: bool,
}

#[derive(Debug, Clone)]
pub struct Module {
    pub id: ModuleId,
    pub name: String,
    pub functions: Vec<CheckedFunction>,
    pub structs: Vec<CheckedStruct>,
    pub enums: Vec<CheckedEnum>,
    pub scopes: Vec<Scope>,
    pub types: Vec<Type>,
    pub imports: Vec<ModuleId>,

    pub is_root: bool,
}

impl Module {
    pub fn new(id: ModuleId, name: String) -> Self {
        Self {
            id,
            name,
            functions: vec![],
            structs: vec![],
            enums: vec![],
            scopes: vec![],
            types: vec![],
            imports: vec![],
            is_root: false,
        }
    }

    pub fn is_root(&self) -> bool {
        self.is_root
    }
}

impl Project {
    pub fn new() -> Self {
        // Top-level (project-global) scope has no parent scope
        // and is the parent scope of all file scopes

        Self {
            modules: vec![],
            current_module_index: 0,
            current_function_index: None,
            current_struct_type_id: None,
            inside_defer: false,

            checking_prelude: false,
            cached_array_struct_id: None,
            cached_dictionary_struct_id: None,
            cached_error_struct_id: None,
            cached_optional_struct_id: None,
            cached_range_struct_id: None,
            cached_set_struct_id: None,
            cached_tuple_struct_id: None,
            cached_weakptr_struct_id: None,

            dump_type_hints: false,
        }
    }

    pub fn add_module(&mut self, module_name: String) -> ModuleId {
        let id = ModuleId(self.modules.len());
        self.modules.push(Module::new(id, module_name));
        id
    }

    pub fn set_current_module_root(&mut self) {
        self.current_module_mut().is_root = true;
    }

    pub fn current_module(&self) -> &Module {
        &self.modules[self.current_module_index]
    }

    pub fn current_module_mut(&mut self) -> &mut Module {
        &mut self.modules[self.current_module_index]
    }

    pub fn find_or_add_type_id(&mut self, type_: Type) -> TypeId {
        let module = self.current_module();
        let module_id = module.id;

        for (idx, t) in module.types.iter().enumerate() {
            if t == &type_ {
                return TypeId(module_id, idx);
            }
        }

        for (idx, t) in self.get_module(ModuleId(0)).types.iter().enumerate() {
            if t == &type_ {
                return TypeId(ModuleId(0), idx);
            }
        }

        // in the future, we may want to group related types (like instantiations of the same generic)
        self.current_module_mut().types.push(type_);

        TypeId(module_id, self.current_module().types.len() - 1)
    }

    pub fn find_type_in_prelude(&self, tyname: &'static str) -> TypeId {
        match self
            .get_scope(PRELUDE_SCOPE_ID)
            .types
            .iter()
            .find(|(name, _, _)| name.as_str() == tyname)
        {
            Some((_, id, _)) => *id,
            None => panic!("internal eror: {} buildin definition not found", tyname),
        }
    }

    pub fn find_struct_in_prelude(&self, tyname: &'static str) -> StructId {
        match self
            .get_scope(PRELUDE_SCOPE_ID)
            .structs
            .iter()
            .find(|(name, _, _)| name.as_str() == tyname)
        {
            Some((_, id, _)) => *id,
            None => panic!("internal eror: {} buildin definition not found", tyname),
        }
    }

    pub fn create_scope(&mut self, parent_id: ScopeId, throws: bool) -> ScopeId {
        self.current_module_mut()
            .scopes
            .push(Scope::new(Some(parent_id), throws));

        ScopeId(
            ModuleId(self.current_module_index),
            self.current_module().scopes.len() - 1,
        )
    }

    pub fn add_var_to_scope(
        &mut self,
        scope_id: ScopeId,
        var: CheckedVariable,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = self.get_scope_mut(scope_id);
        for existing_var in &scope.vars {
            if var.name == existing_var.name {
                return Err(JaktError::TypecheckErrorWithHint(
                    format!("redefinition of variable {}", var.name),
                    span,
                    format!("variable {} was first defined here", var.name),
                    existing_var.definition_span,
                ));
            }
        }
        scope.vars.push(var);

        Ok(())
    }

    pub fn find_var_in_scope(&self, scope_id: ScopeId, var: &str) -> Option<CheckedVariable> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for v in &scope.vars {
                if v.name == var {
                    return Some(v.clone());
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn find_most_similar_var_name_in_scope(
        &self,
        scope_id: ScopeId,
        var: &str,
    ) -> Option<String> {
        self.find_most_similar_item_name_in_scope(scope_id, var, |scope: &Scope| -> Vec<String> {
            let mut items = Vec::with_capacity(scope.vars.len());
            for item in &scope.vars {
                items.push(item.name.to_string());
            }
            items
        })
    }

    pub fn add_struct_to_scope(
        &mut self,
        scope_id: ScopeId,
        name: String,
        struct_id: StructId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = self.get_scope_mut(scope_id);
        for (existing_struct, _, definition_span) in &scope.structs {
            if &name == existing_struct {
                return Err(JaktError::TypecheckErrorWithHint(
                    format!("redefinition of struct/class {}", name),
                    span,
                    format!("struct/class {} was first defined here", name),
                    *definition_span,
                ));
            }
        }
        scope.structs.push((name, struct_id, span));

        Ok(())
    }

    pub fn add_enum_to_scope(
        &mut self,
        scope_id: ScopeId,
        name: String,
        enum_id: EnumId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = self.get_scope_mut(scope_id);
        for (existing_enum, _, definition_span) in &scope.enums {
            if &name == existing_enum {
                return Err(JaktError::TypecheckErrorWithHint(
                    format!("redefinition of enum {}", name),
                    span,
                    format!("enum {} was first defined here", name),
                    *definition_span,
                ));
            }
        }
        scope.enums.push((name, enum_id, span));

        Ok(())
    }

    pub fn find_struct_in_scope(&self, scope_id: ScopeId, structure: &str) -> Option<StructId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for s in &scope.structs {
                if s.0 == structure {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    fn find_most_similar_item_name_in_scope<F>(
        &self,
        scope_id: ScopeId,
        item_name: &str,
        item_names_from_scope: F,
    ) -> Option<String>
    where
        F: Fn(&Scope) -> Vec<String>,
    {
        let mut mistakes = None;
        let mut most_similar_name = None;
        let mut scope_id = Some(scope_id);
        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for item in item_names_from_scope(scope) {
                let current_mistakes = number_of_edits_between(&item, item_name);
                if let Some(mistakes) = &mut mistakes {
                    if current_mistakes < *mistakes {
                        *mistakes = current_mistakes;
                        most_similar_name = Some(item);
                    }
                } else {
                    mistakes = Some(current_mistakes);
                    most_similar_name = Some(item);
                }
            }
            scope_id = scope.parent;
        }

        if let Some(mistakes) = mistakes {
            // Surely no one would misspell half the word.
            if mistakes > item_name.len() / 2 {
                return None;
            }
        }

        most_similar_name
    }

    pub fn find_most_similar_struct_name_in_scope(
        &self,
        scope_id: ScopeId,
        structure: &str,
    ) -> Option<String> {
        self.find_most_similar_item_name_in_scope(
            scope_id,
            structure,
            |scope: &Scope| -> Vec<String> {
                let mut items = Vec::with_capacity(scope.structs.len());
                for item in &scope.structs {
                    items.push(item.0.to_string());
                }
                items
            },
        )
    }

    pub fn find_enum_in_scope(&self, scope_id: ScopeId, enum_name: &str) -> Option<EnumId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for e in &scope.enums {
                if e.0 == enum_name {
                    return Some(e.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn find_most_similar_enum_name_in_scope(
        &self,
        scope_id: ScopeId,
        enum_name: &str,
    ) -> Option<String> {
        self.find_most_similar_item_name_in_scope(
            scope_id,
            enum_name,
            |scope: &Scope| -> Vec<String> {
                let mut items = Vec::with_capacity(scope.enums.len());
                for item in &scope.enums {
                    items.push(item.0.to_string());
                }
                items
            },
        )
    }

    // Find the namespace in the current scope, or one of its parents
    // and whether the found import was an import
    pub fn find_namespace_in_scope(
        &self,
        current_scope_id: ScopeId,
        namespace_name: &str,
    ) -> Option<(ScopeId, bool)> {
        let mut scope_id = Some(current_scope_id);

        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for child_scope_id in &scope.children {
                let child_scope = self.get_scope(*child_scope_id);
                if let Some(name) = &child_scope.namespace_name {
                    if name == namespace_name {
                        return Some((*child_scope_id, false));
                    }
                }
            }
            scope_id = scope.parent;
        }

        // if we do not find it then check imports
        let module_id = current_scope_id.0;
        // ScopeId(_, 0) will always be the top level scope for a module.
        // the imports should always be there.
        for (name, id, _) in &self.get_scope(ScopeId(module_id, 0)).imports {
            if name == namespace_name {
                return Some((ScopeId(*id, 0), true));
            }
        }

        None
    }

    pub fn find_most_similar_namespace_name_in_scope(
        &self,
        scope_id: ScopeId,
        namespace_name: &str,
    ) -> Option<String> {
        self.find_most_similar_item_name_in_scope(
            scope_id,
            namespace_name,
            |scope: &Scope| -> Vec<String> {
                let mut items = Vec::new();
                for child_scope_id in &scope.children {
                    let child_scope = self.get_scope(*child_scope_id);
                    if let Some(name) = &child_scope.namespace_name {
                        items.push(name.to_string());
                    }
                }
                items
            },
        )
    }

    // Find namespace in the current scope, but not any of its parents (strictly in the current scope)
    pub fn find_namespace_in_scope_strict(
        &self,
        scope_id: ScopeId,
        namespace_name: &str,
    ) -> Option<StructId> {
        let scope = self.get_scope(scope_id);
        for child_scope_id in &scope.children {
            let child_scope = self.get_scope(*child_scope_id);
            if let Some(name) = &child_scope.namespace_name {
                if name == namespace_name {
                    todo!()
                    // return None
                }
            }
        }

        None
    }

    pub fn add_function_to_scope(
        &mut self,
        scope_id: ScopeId,
        name: String,
        function_id: FunctionId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = self.get_scope_mut(scope_id);

        for (existing_function, _, definition_span) in &scope.functions {
            if &name == existing_function {
                return Err(JaktError::TypecheckErrorWithHint(
                    format!("redefinition of function {}", name),
                    span,
                    format!("function {} was first defined here", name),
                    *definition_span,
                ));
            }
        }
        scope.functions.push((name, function_id, span));

        Ok(())
    }

    pub fn find_function_in_scope(
        &self,
        scope_id: ScopeId,
        function_name: &str,
    ) -> Option<FunctionId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for s in &scope.functions {
                if s.0 == function_name {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn find_most_similar_function_name_in_scope(
        &self,
        scope_id: ScopeId,
        function_name: &str,
    ) -> Option<String> {
        self.find_most_similar_item_name_in_scope(
            scope_id,
            function_name,
            |scope: &Scope| -> Vec<String> {
                let mut items = Vec::with_capacity(scope.functions.len());
                for item in &scope.functions {
                    items.push(item.0.to_string());
                }
                items
            },
        )
    }

    pub fn add_type_to_scope(
        &mut self,
        scope_id: ScopeId,
        type_name: String,
        type_id: TypeId,
        span: Span,
    ) -> Result<(), JaktError> {
        let scope = self.get_scope_mut(scope_id);

        for (existing_type, _, definition_span) in &scope.types {
            if &type_name == existing_type {
                return Err(JaktError::TypecheckErrorWithHint(
                    format!("redefinition of type {}", type_name),
                    span,
                    format!("type {} was first defined here", type_name),
                    *definition_span,
                ));
            }
        }
        scope.types.push((type_name, type_id, span));

        Ok(())
    }

    pub fn find_type_in_scope(&self, scope_id: ScopeId, type_name: &str) -> Option<TypeId> {
        let mut scope_id = Some(scope_id);

        while let Some(current_id) = scope_id {
            let scope = self.get_scope(current_id);
            for s in &scope.types {
                if s.0 == type_name {
                    return Some(s.1);
                }
            }
            scope_id = scope.parent;
        }

        None
    }

    pub fn find_most_similar_type_name_in_scope(
        &self,
        scope_id: ScopeId,
        type_name: &str,
    ) -> Option<String> {
        self.find_most_similar_item_name_in_scope(
            scope_id,
            type_name,
            |scope: &Scope| -> Vec<String> {
                let mut items = Vec::with_capacity(scope.types.len());
                for item in &scope.types {
                    items.push(item.0.to_string());
                }
                items
            },
        )
    }

    pub fn typename_for_type_id(&self, type_id: TypeId) -> String {
        // NOTE: Can't use get_*_struct_id here since it needs a Span.
        let array_struct_id = self.cached_array_struct_id.unwrap();
        let dictionary_struct_id = self.cached_dictionary_struct_id.unwrap();
        let optional_struct_id = self.cached_optional_struct_id.unwrap();
        let range_struct_id = self.cached_range_struct_id.unwrap();
        let set_struct_id = self.cached_set_struct_id.unwrap();
        let tuple_struct_id = self.cached_tuple_struct_id.unwrap();
        let weak_ptr_struct_id = self.cached_weakptr_struct_id.unwrap();

        match self.get_type(type_id) {
            Type::Builtin => match type_id {
                crate::compiler::VOID_TYPE_ID => "void".to_string(),
                crate::compiler::I8_TYPE_ID => "i8".to_string(),
                crate::compiler::I16_TYPE_ID => "i16".to_string(),
                crate::compiler::I32_TYPE_ID => "i32".to_string(),
                crate::compiler::I64_TYPE_ID => "i64".to_string(),
                crate::compiler::U8_TYPE_ID => "u8".to_string(),
                crate::compiler::U16_TYPE_ID => "u16".to_string(),
                crate::compiler::U32_TYPE_ID => "u32".to_string(),
                crate::compiler::U64_TYPE_ID => "u64".to_string(),
                crate::compiler::F32_TYPE_ID => "f32".to_string(),
                crate::compiler::F64_TYPE_ID => "f64".to_string(),
                crate::compiler::USIZE_TYPE_ID => "usize".to_string(),
                crate::compiler::CCHAR_TYPE_ID => "c_char".to_string(),
                crate::compiler::CINT_TYPE_ID => "c_int".to_string(),
                crate::compiler::STRING_TYPE_ID => "String".to_string(),
                crate::compiler::BOOL_TYPE_ID => "bool".to_string(),
                _ => "unknown".to_string(),
            },
            Type::Enum(enum_id) => self.get_enum(*enum_id).name.clone(),
            Type::Struct(struct_id) => self.get_struct(*struct_id).name.clone(),
            Type::GenericEnumInstance(enum_id, type_args) => {
                let mut output = format!("enum {}", self.get_enum(*enum_id).name);

                output.push('<');
                let mut first = true;
                for arg in type_args {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }
                    output.push_str(&self.typename_for_type_id(*arg))
                }
                output.push('>');

                output
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == array_struct_id => {
                format!("[{}]", self.typename_for_type_id(type_args[0]))
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == dictionary_struct_id => {
                format!(
                    "[{}:{}]",
                    self.typename_for_type_id(type_args[0]),
                    self.typename_for_type_id(type_args[1])
                )
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == set_struct_id => {
                format!("{{{}}}", self.typename_for_type_id(type_args[0]))
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == range_struct_id => {
                format!(
                    "{}..{}",
                    self.typename_for_type_id(type_args[0]),
                    self.typename_for_type_id(type_args[0])
                )
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == tuple_struct_id => {
                let mut output = "(".to_string();
                let mut first = true;
                for arg in type_args {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }
                    output.push_str(&self.typename_for_type_id(*arg))
                }
                output.push(')');

                output
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == optional_struct_id => {
                format!("{}?", self.typename_for_type_id(type_args[0]))
            }
            Type::GenericInstance(struct_id, type_args) if *struct_id == weak_ptr_struct_id => {
                format!("weak {}?", self.typename_for_type_id(type_args[0]))
            }
            Type::GenericInstance(struct_id, type_args) => {
                let structure = self.get_struct(*struct_id);
                let mut output = structure.name.clone();
                output.push('<');
                let mut first = true;
                for arg in type_args {
                    if !first {
                        output.push_str(", ");
                    } else {
                        first = false;
                    }
                    output.push_str(&self.typename_for_type_id(*arg))
                }
                output.push('>');

                output
            }
            Type::TypeVariable(name) => name.clone(),
            Type::RawPtr(type_id) => format!("raw {}", self.typename_for_type_id(*type_id)),
        }
    }

    fn get_cached_struct_id(
        &self,
        cached_struct_id: Option<StructId>,
        name: &'static str,
        span: Span,
    ) -> StructId {
        // FIXME: Currently not being able to get an internally used struct ID
        //        causes a panic. In the future it would be nice to report it
        //        as an internal compiler error instead.
        match cached_struct_id {
            Some(id) => Ok(id),
            None => Err(JaktError::TypecheckError(
                format!("can't find builtin {} type", name),
                span,
            )),
        }
        .unwrap()
    }

    pub fn get_module(&self, module_id: ModuleId) -> &Module {
        &self.modules[module_id.0]
    }

    pub fn get_module_mut(&mut self, module_id: ModuleId) -> &mut Module {
        &mut self.modules[module_id.0]
    }

    pub fn get_scope(&self, scope_id: ScopeId) -> &Scope {
        &self.get_module(scope_id.0).scopes[scope_id.1]
    }

    pub fn get_scope_mut(&mut self, scope_id: ScopeId) -> &mut Scope {
        &mut self.get_module_mut(scope_id.0).scopes[scope_id.1]
    }

    pub fn get_type(&self, type_id: TypeId) -> &Type {
        &self.get_module(type_id.0).types[type_id.1]
    }

    pub fn get_struct(&self, struct_id: StructId) -> &CheckedStruct {
        &self.get_module(struct_id.0).structs[struct_id.1]
    }

    pub fn get_struct_mut(&mut self, struct_id: StructId) -> &mut CheckedStruct {
        &mut self.get_module_mut(struct_id.0).structs[struct_id.1]
    }

    pub fn get_enum(&self, enum_id: EnumId) -> &CheckedEnum {
        &self.get_module(enum_id.0).enums[enum_id.1]
    }

    pub fn get_enum_mut(&mut self, enum_id: EnumId) -> &mut CheckedEnum {
        &mut self.get_module_mut(enum_id.0).enums[enum_id.1]
    }

    pub fn get_function(&self, function_id: FunctionId) -> &CheckedFunction {
        &self.get_module(function_id.0).functions[function_id.1]
    }

    pub fn get_function_mut(&mut self, function_id: FunctionId) -> &mut CheckedFunction {
        &mut self.get_module_mut(function_id.0).functions[function_id.1]
    }

    pub fn get_array_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_array_struct_id, "Array", span)
    }

    pub fn get_dictionary_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_dictionary_struct_id, "Dictionary", span)
    }

    pub fn get_error_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_error_struct_id, "Error", span)
    }

    pub fn get_optional_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_optional_struct_id, "Optional", span)
    }

    pub fn get_range_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_range_struct_id, "Range", span)
    }

    pub fn get_set_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_set_struct_id, "Set", span)
    }

    pub fn get_tuple_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_tuple_struct_id, "Tuple", span)
    }

    pub fn get_weakptr_struct_id(&self, span: Span) -> StructId {
        self.get_cached_struct_id(self.cached_weakptr_struct_id, "WeakPtr", span)
    }
}

#[derive(Clone, Debug)]
pub struct CheckedStruct {
    pub name: String,
    pub name_span: Span,
    pub generic_parameters: Vec<TypeId>,
    pub fields: Vec<CheckedVarDecl>,
    pub scope_id: ScopeId,
    pub definition_linkage: DefinitionLinkage,
    pub definition_type: DefinitionType,
    pub type_id: TypeId,
}

#[derive(Clone, Debug)]
pub struct CheckedEnum {
    pub name: String,
    pub generic_parameters: Vec<TypeId>,
    pub variants: Vec<CheckedEnumVariant>,
    pub scope_id: ScopeId,
    pub definition_linkage: DefinitionLinkage,
    pub definition_type: DefinitionType,
    pub underlying_type_id: Option<TypeId>,
    pub span: Span,
    pub type_id: TypeId,
}

#[derive(Clone, Debug)]
pub enum CheckedEnumVariant {
    Untyped(String, Span),
    Typed(String, TypeId, Span),
    WithValue(String, CheckedExpression, Span),
    StructLike(String, Vec<CheckedVarDecl>, Span),
}

#[derive(Clone, Debug)]
pub struct CheckedNamespace {
    pub name: Option<String>,
    pub scope: ScopeId,
}

#[derive(Clone, Debug)]
pub struct CheckedParameter {
    pub requires_label: bool,
    pub variable: CheckedVariable,
}

#[derive(Clone, Debug)]
pub enum FunctionGenericParameter {
    InferenceGuide(TypeId),
    Parameter(TypeId),
}

#[derive(Debug, Clone)]
pub struct CheckedFunction {
    pub name: String,
    pub name_span: Span,
    pub visibility: Visibility,
    pub throws: bool,
    pub return_type_id: TypeId,
    pub return_type_span: Option<Span>,
    pub params: Vec<CheckedParameter>,
    pub generic_parameters: Vec<FunctionGenericParameter>,
    pub function_scope_id: ScopeId,
    pub block: Option<CheckedBlock>,
    pub parsed_function: Option<ParsedFunction>,
    pub linkage: FunctionLinkage,
    pub is_instantiated: bool,
}

impl CheckedFunction {
    pub fn to_parsed_function(&self) -> ParsedFunction {
        self.parsed_function
            .as_ref()
            .expect("to_parsed_function() called on a synthetic function")
            .clone()
    }

    pub fn is_static(&self) -> bool {
        if let Some(param) = self.params.get(0) {
            return param.variable.name != "this";
        }

        true
    }

    pub fn is_mutating(&self) -> bool {
        if !self.is_static() {
            return self.params.first().unwrap().variable.mutable;
        }

        false
    }
}

#[derive(Debug, Clone)]
pub struct CheckedBlock {
    pub stmts: Vec<CheckedStatement>,
    pub scope: ScopeId,
    pub definitely_returns: bool,
    pub yielded_type: Option<TypeId>, // Set if the block yields.
}

impl CheckedBlock {
    pub fn new(scope: ScopeId) -> Self {
        Self {
            stmts: Vec::new(),
            scope,
            definitely_returns: false,
            yielded_type: None,
        }
    }
}

#[derive(Debug, Clone)]
pub struct CheckedVarDecl {
    pub name: String,
    pub type_id: TypeId,
    pub type_span: Option<Span>,
    pub mutable: bool,
    pub span: Span,
    pub visibility: Visibility,
}

#[derive(Clone, Debug)]
pub struct CheckedVariable {
    pub name: String,
    pub type_id: TypeId,
    pub type_span: Option<Span>,
    pub mutable: bool,
    pub visibility: Visibility,
    pub definition_span: Span,
}

#[derive(Debug, Clone)]
pub enum CheckedStatement {
    Expression(CheckedExpression),
    Defer(Box<CheckedStatement>),
    VarDecl(CheckedVarDecl, CheckedExpression),
    If(
        CheckedExpression,
        CheckedBlock,
        Option<Box<CheckedStatement>>, // optional else case
    ),
    Block(CheckedBlock),
    Loop(CheckedBlock),
    While(CheckedExpression, CheckedBlock),
    Return(Option<CheckedExpression>),
    Yield(CheckedExpression),
    Break,
    Continue,
    Throw(CheckedExpression),
    Try(Box<CheckedStatement>, String, CheckedBlock),
    InlineCpp(Vec<String>),
    Garbage,
}

#[derive(Clone, Debug)]
pub enum NumberConstant {
    Signed(i64),
    Unsigned(u64),
    Floating(f64),
}

impl NumberConstant {
    pub fn to_usize(&self) -> usize {
        match self {
            NumberConstant::Signed(value) => *value as usize,
            NumberConstant::Unsigned(value) => *value as usize,
            NumberConstant::Floating(value) => *value as usize,
        }
    }

    pub fn promote(&self, type_id: TypeId) -> (Option<NumericConstant>, TypeId) {
        if !can_fit_number(type_id, self) {
            return (None, UNKNOWN_TYPE_ID);
        }

        let bits = get_bits(type_id);
        let signed = is_signed(type_id);

        let new_constant = match self {
            NumberConstant::Signed(value) => match (bits, signed) {
                (8, false) => NumericConstant::U8(*value as u8),
                (16, false) => NumericConstant::U16(*value as u16),
                (32, false) => NumericConstant::U32(*value as u32),
                (64, false) => NumericConstant::U64(*value as u64),
                (8, true) => NumericConstant::I8(*value as i8),
                (16, true) => NumericConstant::I16(*value as i16),
                (32, true) => NumericConstant::I32(*value as i32),
                (64, true) => NumericConstant::I64(*value as i64),
                _ => panic!("Numeric constants can only be 8, 16, 32, or 64 bits long"),
            },
            NumberConstant::Unsigned(value) => match (bits, signed) {
                (8, false) => NumericConstant::U8(*value as u8),
                (16, false) => NumericConstant::U16(*value as u16),
                (32, false) => NumericConstant::U32(*value as u32),
                (64, false) => NumericConstant::U64(*value as u64),
                (8, true) => NumericConstant::I8(*value as i8),
                (16, true) => NumericConstant::I16(*value as i16),
                (32, true) => NumericConstant::I32(*value as i32),
                (64, true) => NumericConstant::I64(*value as i64),
                _ => panic!("Numeric constants can only be 8, 16, 32, or 64 bits long"),
            },
            NumberConstant::Floating(value) => match (bits, signed) {
                (32, true) => NumericConstant::F32(*value as f32),
                (64, true) => NumericConstant::F64(*value as f64),
                _ => panic!("Floating numeric constants can only be 32, or 64 bits long"),
            },
        };
        (Some(new_constant), type_id)
    }
}

impl From<NumberConstant> for i128 {
    fn from(number: NumberConstant) -> Self {
        match number {
            NumberConstant::Signed(value) => value as i128,
            NumberConstant::Unsigned(value) => value as i128,
            _ => panic!("Not supported for floating numbers"),
        }
    }
}

#[derive(Clone, Debug)]
pub enum NumericConstant {
    I8(i8),
    I16(i16),
    I32(i32),
    I64(i64),
    U8(u8),
    U16(u16),
    U32(u32),
    U64(u64),
    USize(u64),
    F32(f32),
    F64(f64),
}

impl PartialEq for NumericConstant {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (NumericConstant::I8(l), NumericConstant::I8(r)) => l == r,
            (NumericConstant::I16(l), NumericConstant::I16(r)) => l == r,
            (NumericConstant::I32(l), NumericConstant::I32(r)) => l == r,
            (NumericConstant::I64(l), NumericConstant::I64(r)) => l == r,
            (NumericConstant::U8(l), NumericConstant::U8(r)) => l == r,
            (NumericConstant::U16(l), NumericConstant::U16(r)) => l == r,
            (NumericConstant::U32(l), NumericConstant::U32(r)) => l == r,
            (NumericConstant::U64(l), NumericConstant::U64(r)) => l == r,
            (NumericConstant::USize(l), NumericConstant::USize(r)) => l == r,
            (NumericConstant::F32(l), NumericConstant::F32(r)) => l == r,
            (NumericConstant::F64(l), NumericConstant::F64(r)) => l == r,
            _ => false,
        }
    }
}

impl NumericConstant {
    pub fn number_constant(&self) -> Option<NumberConstant> {
        match self {
            NumericConstant::I8(value) => Some(NumberConstant::Signed(*value as i64)),
            NumericConstant::I16(value) => Some(NumberConstant::Signed(*value as i64)),
            NumericConstant::I32(value) => Some(NumberConstant::Signed(*value as i64)),
            NumericConstant::I64(value) => Some(NumberConstant::Signed(*value as i64)),
            NumericConstant::U8(value) => Some(NumberConstant::Unsigned(*value as u64)),
            NumericConstant::U16(value) => Some(NumberConstant::Unsigned(*value as u64)),
            NumericConstant::U32(value) => Some(NumberConstant::Unsigned(*value as u64)),
            NumericConstant::U64(value) => Some(NumberConstant::Unsigned(*value as u64)),
            NumericConstant::USize(value) => Some(NumberConstant::Unsigned(*value as u64)),
            NumericConstant::F32(value) => Some(NumberConstant::Floating(*value as f64)),
            NumericConstant::F64(value) => Some(NumberConstant::Floating(*value as f64)),
        }
    }

    pub fn type_id(&self) -> TypeId {
        match self {
            NumericConstant::I8(_) => I8_TYPE_ID,
            NumericConstant::I16(_) => I16_TYPE_ID,
            NumericConstant::I32(_) => I32_TYPE_ID,
            NumericConstant::I64(_) => I64_TYPE_ID,
            NumericConstant::U8(_) => U8_TYPE_ID,
            NumericConstant::U16(_) => U16_TYPE_ID,
            NumericConstant::U32(_) => U32_TYPE_ID,
            NumericConstant::U64(_) => U64_TYPE_ID,
            NumericConstant::USize(_) => USIZE_TYPE_ID,
            NumericConstant::F32(_) => F32_TYPE_ID,
            NumericConstant::F64(_) => F64_TYPE_ID,
        }
    }
}

fn resolve_type_var(type_var: TypeId, scope_id: ScopeId, project: &Project) -> TypeId {
    let mut type_id = type_var;
    loop {
        if let Type::TypeVariable(type_name) = &project.get_type(type_id) {
            match project.find_type_in_scope(scope_id, type_name) {
                Some(id) => {
                    if type_id == id {
                        return type_id;
                    }
                    type_id = id
                }
                None => return type_id,
            }
        } else {
            return type_id;
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum CheckedTypeCast {
    Fallible(TypeId),
    Infallible(TypeId),
}

impl CheckedTypeCast {
    pub fn type_id_or_type_var(&self) -> TypeId {
        match self {
            CheckedTypeCast::Fallible(type_id) => *type_id,
            CheckedTypeCast::Infallible(type_id) => *type_id,
        }
    }

    pub fn type_id(&self, scope_id: ScopeId, project: &Project) -> TypeId {
        resolve_type_var(self.type_id_or_type_var(), scope_id, project)
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum CheckedUnaryOperator {
    PreIncrement,
    PostIncrement,
    PreDecrement,
    PostDecrement,
    Negate,
    Dereference,
    RawAddress,
    LogicalNot,
    BitwiseNot,
    TypeCast(CheckedTypeCast),
    Is(TypeId),
    IsEnumVariant(String),
}

#[derive(Debug, Clone)]
pub enum CheckedMatchBody {
    Expression(CheckedExpression),
    Block(CheckedBlock),
}

#[derive(Debug, Clone)]
pub enum CheckedMatchCase {
    EnumVariant {
        variant_name: String,
        variant_arguments: Vec<(Option<String>, String, Span)>,
        subject_type_id: TypeId,
        variant_index: usize,
        scope_id: ScopeId,
        body: CheckedMatchBody,
        marker_span: Span,
    },
    Expression {
        expression: Box<CheckedExpression>,
        body: CheckedMatchBody,
        marker_span: Span,
    },
    CatchAll {
        body: CheckedMatchBody,
        marker_span: Span,
    },
}

#[derive(Clone, Debug)]
pub enum CheckedExpression {
    // Standalone
    Boolean(bool, Span),
    NumericConstant(NumericConstant, Span, TypeId),
    QuotedString(String, Span),
    ByteConstant(String, Span),
    CharacterConstant(String, Span),
    UnaryOp(Box<CheckedExpression>, CheckedUnaryOperator, Span, TypeId),
    BinaryOp(
        Box<CheckedExpression>,
        BinaryOperator,
        Box<CheckedExpression>,
        Span,
        TypeId,
    ),
    Tuple(Vec<CheckedExpression>, Span, TypeId),
    Range(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    Array(
        Vec<CheckedExpression>,
        Option<Box<CheckedExpression>>,
        Span,
        TypeId,
    ),
    Dictionary(Vec<(CheckedExpression, CheckedExpression)>, Span, TypeId),
    Set(Vec<CheckedExpression>, Span, TypeId),
    IndexedExpression(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    IndexedDictionary(Box<CheckedExpression>, Box<CheckedExpression>, Span, TypeId),
    IndexedTuple(Box<CheckedExpression>, usize, Span, TypeId),
    IndexedStruct(Box<CheckedExpression>, String, Span, TypeId),

    Match(
        Box<CheckedExpression>,
        Vec<CheckedMatchCase>,
        Span,
        TypeId,
        bool,
    ),

    Call(CheckedCall, Span, TypeId),
    MethodCall(Box<CheckedExpression>, CheckedCall, Span, TypeId),

    NamespacedVar(Vec<CheckedNamespace>, CheckedVariable, Span),
    Var(CheckedVariable, Span),

    OptionalNone(Span, TypeId),
    OptionalSome(Box<CheckedExpression>, Span, TypeId),
    ForcedUnwrap(Box<CheckedExpression>, Span, TypeId),

    Block(Box<CheckedBlock>, Span, TypeId),

    // Parsing error
    Garbage(Span),
}

impl CheckedExpression {
    pub fn type_id_or_type_var(&self) -> TypeId {
        match self {
            CheckedExpression::Boolean(_, _) => BOOL_TYPE_ID,
            CheckedExpression::Call(_, _, type_id) => *type_id,
            CheckedExpression::NumericConstant(_, _, type_id) => *type_id,
            CheckedExpression::QuotedString(_, _) => STRING_TYPE_ID,
            CheckedExpression::ByteConstant(_, _) => U8_TYPE_ID,
            CheckedExpression::CharacterConstant(_, _) => CCHAR_TYPE_ID, // use the C one for now
            CheckedExpression::UnaryOp(_, _, _, type_id) => *type_id,
            CheckedExpression::BinaryOp(_, _, _, _, type_id) => *type_id,
            CheckedExpression::Dictionary(_, _, type_id) => *type_id,
            CheckedExpression::Set(_, _, type_id) => *type_id,
            CheckedExpression::Array(_, _, _, type_id) => *type_id,
            CheckedExpression::Tuple(_, _, type_id) => *type_id,
            CheckedExpression::Range(_, _, _, type_id) => *type_id,
            CheckedExpression::IndexedDictionary(_, _, _, type_id) => *type_id,
            CheckedExpression::IndexedExpression(_, _, _, type_id) => *type_id,
            CheckedExpression::IndexedTuple(_, _, _, type_id) => *type_id,
            CheckedExpression::IndexedStruct(_, _, _, type_id) => *type_id,
            CheckedExpression::MethodCall(_, _, _, type_id) => *type_id,
            CheckedExpression::Var(CheckedVariable { type_id, .. }, _) => *type_id,
            CheckedExpression::NamespacedVar(_, CheckedVariable { type_id, .. }, _) => *type_id,
            CheckedExpression::OptionalNone(_, type_id) => *type_id,
            CheckedExpression::OptionalSome(_, _, type_id) => *type_id,
            CheckedExpression::ForcedUnwrap(_, _, type_id) => *type_id,
            CheckedExpression::Match(_, _, _, type_id, _) => *type_id,
            CheckedExpression::Block(_, _, type_id) => *type_id,
            CheckedExpression::Garbage(_) => UNKNOWN_TYPE_ID,
        }
    }

    pub fn type_id(&self, scope_id: ScopeId, project: &Project) -> TypeId {
        resolve_type_var(self.type_id_or_type_var(), scope_id, project)
    }

    pub fn span(&self) -> Span {
        match self {
            CheckedExpression::Boolean(_, span) => *span,
            CheckedExpression::Call(_, span, _) => *span,
            CheckedExpression::NumericConstant(_, span, _) => *span,
            CheckedExpression::QuotedString(_, span) => *span,
            CheckedExpression::ByteConstant(_, span) => *span,
            CheckedExpression::CharacterConstant(_, span) => *span,
            CheckedExpression::UnaryOp(_, _, span, _) => *span,
            CheckedExpression::BinaryOp(_, _, _, span, _) => *span,
            CheckedExpression::Dictionary(_, span, _) => *span,
            CheckedExpression::Set(_, span, _) => *span,
            CheckedExpression::Array(_, _, span, _) => *span,
            CheckedExpression::Tuple(_, span, _) => *span,
            CheckedExpression::Range(_, _, span, _) => *span,
            CheckedExpression::IndexedDictionary(_, _, span, _) => *span,
            CheckedExpression::IndexedExpression(_, _, span, _) => *span,
            CheckedExpression::IndexedTuple(_, _, span, _) => *span,
            CheckedExpression::IndexedStruct(_, _, span, _) => *span,
            CheckedExpression::MethodCall(_, _, span, _) => *span,
            CheckedExpression::Var(_, span) => *span,
            CheckedExpression::NamespacedVar(_, _, span) => *span,
            CheckedExpression::OptionalNone(span, _) => *span,
            CheckedExpression::OptionalSome(_, span, _) => *span,
            CheckedExpression::ForcedUnwrap(_, span, _) => *span,
            CheckedExpression::Match(_, _, span, _, _) => *span,
            CheckedExpression::Block(_, span, _) => *span,
            CheckedExpression::Garbage(span) => *span,
        }
    }

    pub fn to_number_constant(&self) -> Option<NumberConstant> {
        match self {
            CheckedExpression::NumericConstant(constant, _, _) => constant.number_constant(),
            CheckedExpression::UnaryOp(
                value,
                CheckedUnaryOperator::TypeCast(CheckedTypeCast::Infallible(_)),
                _,
                type_id,
            ) => {
                if !is_integer(*type_id) && !is_floating(*type_id) {
                    return None;
                }
                match &**value {
                    CheckedExpression::NumericConstant(constant, _, _) => {
                        constant.number_constant()
                    }
                    _ => None,
                }
            }
            _ => None,
        }
    }

    pub fn is_mutable(&self) -> bool {
        match self {
            CheckedExpression::Var(var, _) => var.mutable,
            CheckedExpression::IndexedStruct(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedExpression(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedTuple(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::IndexedDictionary(expr, _, _, _) => expr.is_mutable(),
            CheckedExpression::ForcedUnwrap(expr, _, _) => expr.is_mutable(),
            _ => false,
        }
    }

    pub fn definitely_returns(&self) -> bool {
        if let CheckedExpression::Match(_, match_cases, _, _, _) = self {
            // If each case is a block that definitely returns, the whole match expression definitely returns.
            for case in match_cases {
                match case {
                    CheckedMatchCase::EnumVariant { body, .. }
                    | CheckedMatchCase::Expression { body, .. }
                    | CheckedMatchCase::CatchAll { body, .. } => match body {
                        CheckedMatchBody::Block(block) if block.definitely_returns => continue,
                        _ => return false,
                    },
                }
            }
            return true;
        }

        false
    }
}

#[derive(Clone, Debug)]
pub struct ResolvedNamespace {
    pub name: String,
    pub generic_parameters: Option<Vec<TypeId>>,
}

#[derive(Clone, Debug)]
pub struct CheckedCall {
    pub namespace: Vec<ResolvedNamespace>,
    pub name: String,
    pub function_id: Option<FunctionId>,
    pub callee_throws: bool,
    pub args: Vec<(String, CheckedExpression)>,
    pub type_args: Vec<TypeId>,
    pub linkage: FunctionLinkage,
    pub type_id: TypeId,
}

#[derive(Clone, Debug)]
pub struct Scope {
    pub namespace_name: Option<String>,
    pub vars: Vec<CheckedVariable>,
    pub structs: Vec<(String, StructId, Span)>,
    pub functions: Vec<(String, FunctionId, Span)>,
    pub enums: Vec<(String, EnumId, Span)>,
    pub types: Vec<(String, TypeId, Span)>,
    // should only be populated in module/file scopes.
    pub imports: Vec<(String, ModuleId, Span)>,
    pub parent: Option<ScopeId>,
    // Namespaces may also have children that are also namespaces
    pub children: Vec<ScopeId>,
    pub throws: bool,
}

impl Scope {
    pub fn new(parent: Option<ScopeId>, throws: bool) -> Self {
        Self {
            namespace_name: None,
            vars: Vec::new(),
            structs: Vec::new(),
            functions: Vec::new(),
            enums: Vec::new(),
            types: Vec::new(),
            imports: Vec::new(),
            parent,
            children: Vec::new(),
            throws,
        }
    }

    pub fn can_access(own: ScopeId, other: ScopeId, project: &Project) -> bool {
        // We can access another scope if we're either the same scope, or we are a direct children scope of the other scope.
        if own == other {
            true
        } else {
            let mut own_scope = project.get_scope(own);
            while let Some(parent) = own_scope.parent {
                if parent == other {
                    return true;
                }
                own_scope = project.get_scope(parent);
            }
            false
        }
    }
}

/// A trait to collect common namespace member properties.
trait NamespaceMember {
    fn visibility(&self) -> &Visibility;
    fn name(&self) -> String;
    /// e.g. variable, function etc.
    fn kind(&self) -> &'static str;
}

impl NamespaceMember for CheckedVarDecl {
    fn visibility(&self) -> &Visibility {
        &self.visibility
    }

    fn name(&self) -> String {
        self.name.clone()
    }

    fn kind(&self) -> &'static str {
        "variable"
    }
}
impl NamespaceMember for CheckedVariable {
    fn visibility(&self) -> &Visibility {
        &self.visibility
    }

    fn name(&self) -> String {
        self.name.clone()
    }

    fn kind(&self) -> &'static str {
        "variable"
    }
}
impl NamespaceMember for CheckedFunction {
    fn visibility(&self) -> &Visibility {
        &self.visibility
    }

    fn name(&self) -> String {
        self.name.clone()
    }

    fn kind(&self) -> &'static str {
        "function"
    }
}

fn check_accessibility(
    own_scope: ScopeId,
    member_scope: ScopeId,
    member: impl NamespaceMember,
    span: &Span,
    project: &mut Project,
) -> Option<JaktError> {
    match member.visibility() {
        Visibility::Private if !Scope::can_access(own_scope, member_scope, project) => {
            Some(JaktError::TypecheckError(
                format!(
                    "Can't access {} ‘{}’ from scope {:?}, because it is marked private",
                    member.kind(),
                    member.name(),
                    project.get_scope(own_scope).namespace_name,
                ),
                *span,
            ))
        }
        Visibility::Restricted(whitelisted_types, restricted_span) => {
            return match project.current_struct_type_id {
                Some(own_type_id) => {
                    // Only structs/classes can be listed in `restricted()`.
                    if let Type::Struct(struct_id) = project.get_type(own_type_id).clone() {
                        for whitelisted_type in whitelisted_types {
                            let (type_id, err) =
                                typecheck_typename(whitelisted_type, member_scope, project);
                            if err.is_some() {
                                return err;
                            }
                            if type_id == own_type_id {
                                return None;
                            }
                        }

                        Some(JaktError::TypecheckErrorWithHint(
                            format!(
                                "Can't access {} ‘{}’ from ‘{}’, because ‘{2}’ is not in the restricted whitelist",
                                member.kind(),
                                member.name(),
                                project.get_struct(struct_id).name,
                            ),
                            *span,
                            "Whitelist declared here".to_string(),
                            *restricted_span,
                        ))
                    } else {
                        Some(JaktError::TypecheckErrorWithHint(
                            format!(
                                "Can't access {} ‘{}’ from scope ‘{:?}’, because it is not in the restricted whitelist",
                                member.kind(),
                                member.name(),
                                project.get_scope(own_scope).namespace_name,
                            ),
                            *span,
                            "Whitelist declared here".to_string(),
                            *restricted_span,
                        ))
                    }
                }
                _ => Some(JaktError::TypecheckErrorWithHint(
                    format!(
                        "Can't access {} ‘{}’ from scope ‘{:?}’, because it is marked restricted",
                        member.kind(),
                        member.name(),
                        project.get_scope(own_scope).namespace_name,
                    ),
                    *span,
                    "Whitelist declared here".to_string(),
                    *restricted_span,
                )),
            };
        }
        _ => None,
    }
}

pub fn typecheck_namespace_imports(
    parsed_namespace: &ParsedNamespace,
    scope_id: ScopeId,
    project: &mut Project,
    compiler: &mut Compiler,
) -> Option<JaktError> {
    let mut error = None;

    for import in &parsed_namespace.imports {
        match compiler.search_for_path(import.module_name.name.as_str()) {
            Some(p) => match compiler.find_or_load_file(p) {
                Ok(file_id) => {
                    // if the mnodule has not been loaded yet, parse and typecheck it.
                    if compiler.loaded_files[file_id].module_id == ModuleId::invalid() {
                        // make this a helper function
                        let (parsed_namespace, err) = compiler.parse_file(file_id);
                        error = error.or(err);

                        let current_module = project.current_module_index;
                        let scope = Scope::new(Some(PRELUDE_SCOPE_ID), false);
                        let module_id = project.add_module(import.module_name.name.clone());
                        compiler.loaded_files[file_id].module_id = module_id;
                        project.current_module_index = module_id.0;
                        project.current_module_mut().scopes.push(scope);

                        let file_scope_id = ScopeId(module_id, 0);

                        let err =
                            typecheck_module(&parsed_namespace, file_scope_id, project, compiler);
                        error = error.or(err);

                        project.current_module_index = current_module;
                    }

                    let imported_module_id = compiler.loaded_files[file_id].module_id;
                    project
                        .current_module_mut()
                        .imports
                        .push(imported_module_id);

                    if import.import_list.is_empty() {
                        // import the modules as it's own namespace
                        let scope = project.get_scope_mut(scope_id);
                        scope.imports.push((
                            import
                                .alias_name
                                .as_deref()
                                .unwrap_or(import.module_name.name.as_str())
                                .to_string(),
                            imported_module_id,
                            import.module_name.span,
                        ));
                    } else {
                        // importing each name individually
                        // TODO: Don't clone the module if we don't need to
                        let import_scope_id = ScopeId(imported_module_id, 0);

                        for imported_name in &import.import_list {
                            if let Some(id) = project.find_function_in_scope(
                                import_scope_id,
                                imported_name.name.as_str(),
                            ) {
                                if let Err(e) = project.add_function_to_scope(
                                    scope_id,
                                    imported_name.name.clone(),
                                    id,
                                    imported_name.span,
                                ) {
                                    error = error.or(Some(e));
                                }
                            }

                            if let Some(id) = project
                                .find_enum_in_scope(import_scope_id, imported_name.name.as_str())
                            {
                                if let Err(e) = project.add_enum_to_scope(
                                    scope_id,
                                    imported_name.name.clone(),
                                    id,
                                    imported_name.span,
                                ) {
                                    error = error.or(Some(e));
                                }
                            }

                            if let Some(id) = project
                                .find_type_in_scope(import_scope_id, imported_name.name.as_str())
                            {
                                if let Err(e) = project.add_type_to_scope(
                                    scope_id,
                                    imported_name.name.clone(),
                                    id,
                                    imported_name.span,
                                ) {
                                    error = error.or(Some(e));
                                }
                            }

                            if let Some(id) = project
                                .find_struct_in_scope(import_scope_id, imported_name.name.as_str())
                            {
                                if let Err(e) = project.add_struct_to_scope(
                                    scope_id,
                                    imported_name.name.clone(),
                                    id,
                                    imported_name.span,
                                ) {
                                    error = error.or(Some(e));
                                }
                            }
                        }
                    }
                }
                Err(err) => error = error.or(Some(err)),
            },
            None => {
                return Some(JaktError::TypecheckError(
                    format!("Module '{}' not found", import.module_name.name),
                    import.module_name.span,
                ))
            }
        }
    }

    error
}

pub fn typecheck_module(
    parsed_namespace: &ParsedNamespace,
    scope_id: ScopeId,
    project: &mut Project,
    compiler: &mut Compiler,
) -> Option<JaktError> {
    let err = typecheck_namespace_imports(parsed_namespace, scope_id, project, compiler);
    if err.is_some() {
        return err;
    }

    let err = typecheck_namespace_predecl(parsed_namespace, scope_id, project);
    if err.is_some() {
        return err;
    }

    let err = typecheck_namespace_fields(parsed_namespace, scope_id, project);
    if err.is_some() {
        return err;
    }

    let err = typecheck_namespace_declarations(parsed_namespace, scope_id, project);
    if err.is_some() {
        return err;
    }

    None
}

pub fn typecheck_namespace_fields(
    parsed_namespace: &ParsedNamespace,
    scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    for namespace in parsed_namespace.namespaces.iter() {
        if let Some(namespace_name) = &namespace.name {
            // Typecheck struct fields in the named namespaces
            let (namespace_scope_id, _) = project
                .find_namespace_in_scope(scope_id, namespace_name)
                .expect("internal error: can't find previously added namespace");

            error = error.or(typecheck_namespace_fields(
                namespace,
                namespace_scope_id,
                project,
            ));
        } else {
            // Typecheck struct fields in the unnamed namespace
            let namespace_scope_id = project.create_scope(scope_id, false);
            project.get_scope_mut(namespace_scope_id).namespace_name = namespace.name.clone();
            project
                .get_scope_mut(scope_id)
                .children
                .push(namespace_scope_id);

            error = error.or(typecheck_namespace_fields(
                parsed_namespace,
                namespace_scope_id,
                project,
            ))
        }
    }

    for (_, structure) in parsed_namespace.structs.iter().enumerate() {
        let struct_id = project
            .find_struct_in_scope(scope_id, &structure.name)
            .expect("internal error: can't find previously added struct");

        error = error.or(typecheck_struct_fields(structure, struct_id, project));
    }

    error
}

pub fn typecheck_namespace_predecl(
    parsed_namespace: &ParsedNamespace,
    scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let project_struct_len = project.current_module().structs.len();
    let project_enum_len = project.current_module().enums.len();
    let module_id = project.current_module().id;

    for (struct_id, structure) in parsed_namespace.structs.iter().enumerate() {
        // Bring the struct names into scope for future typechecking
        let struct_id = StructId(module_id, struct_id + project_struct_len);
        project
            .current_module_mut()
            .types
            .push(Type::Struct(struct_id));

        let struct_type_id = TypeId(module_id, project.current_module().types.len() - 1);
        if let Err(err) = project.add_type_to_scope(
            scope_id,
            structure.name.clone(),
            struct_type_id,
            structure.span,
        ) {
            error = error.or(Some(err));
        }

        // Add a placeholder entry, this will be replaced later.
        project.current_module_mut().structs.push(CheckedStruct {
            name: structure.name.clone(),
            name_span: structure.name_span,
            generic_parameters: vec![],
            fields: vec![],
            scope_id: ScopeId(ModuleId(0), 0),
            definition_linkage: structure.definition_linkage,
            definition_type: structure.definition_type,
            type_id: struct_type_id,
        });
    }

    for (enum_id, enum_) in parsed_namespace.enums.iter().enumerate() {
        // Bring the enum names into scope for future typechecking
        let enum_id = EnumId(module_id, enum_id + project_enum_len);
        project.current_module_mut().types.push(Type::Enum(enum_id));

        let enum_type_id = TypeId(module_id, project.current_module_mut().types.len() - 1);
        if let Err(err) =
            project.add_type_to_scope(scope_id, enum_.name.clone(), enum_type_id, enum_.name_span)
        {
            error = error.or(Some(err));
        }

        // Add a placeholder entry, this will be replaced later.
        project.current_module_mut().enums.push(CheckedEnum {
            definition_linkage: enum_.definition_linkage,
            definition_type: if enum_.is_boxed {
                DefinitionType::Class
            } else {
                DefinitionType::Struct
            },
            generic_parameters: vec![],
            name: enum_.name.clone(),
            scope_id: ScopeId(ModuleId(0), 0),
            span: enum_.name_span,
            type_id: enum_type_id,
            underlying_type_id: None,
            variants: vec![],
        })
    }

    for namespace in parsed_namespace.namespaces.iter() {
        // Find all predeclarations in namespaces that are children of this namespace
        if namespace.name.is_some() {
            let namespace_scope_id = project.create_scope(scope_id, false);
            project.get_scope_mut(namespace_scope_id).namespace_name = namespace.name.clone();
            project
                .get_scope_mut(scope_id)
                .children
                .push(namespace_scope_id);
            let err = typecheck_namespace_predecl(namespace, namespace_scope_id, project);
            error = error.or(err);
        }
    }

    for (struct_id, structure) in parsed_namespace.structs.iter().enumerate() {
        // Typecheck the protype of the struct
        let struct_id = StructId(module_id, struct_id + project_struct_len);

        if let Some(err) = typecheck_struct_predecl(structure, struct_id, scope_id, project) {
            error = error.or(Some(err));
        }
    }

    for (enum_id, enum_) in parsed_namespace.enums.iter().enumerate() {
        // Typecheck the protype of the enum
        let enum_id = EnumId(module_id, enum_id + project_enum_len);

        if let Some(err) = typecheck_enum_predecl(enum_, enum_id, scope_id, project) {
            error = error.or(Some(err));
        }
    }

    for (enum_id, enum_) in parsed_namespace.enums.iter().enumerate() {
        let enum_id = EnumId(module_id, enum_id + project_enum_len);
        // Finish typechecking the full enum
        error = error.or(typecheck_enum(
            enum_,
            enum_id,
            project.find_type_in_scope(scope_id, &enum_.name).unwrap(),
            project.get_enum(enum_id).scope_id,
            scope_id,
            project,
        ));
    }

    for function in &parsed_namespace.functions {
        // Ensure we know the function prototypes ahead of time, so that
        // and calls can find and resolve to them
        error = error.or(typecheck_function_predecl(
            function, scope_id, None, project,
        ));
    }

    error
}

pub fn typecheck_namespace_declarations(
    parsed_namespace: &ParsedNamespace,
    scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    for namespace in parsed_namespace.namespaces.iter() {
        if let Some(namespace_name) = &namespace.name {
            // Finish typecheck of the named namespaces
            let (namespace_scope_id, _) = project
                .find_namespace_in_scope(scope_id, namespace_name)
                .expect("internal error: can't find previously added namespace");

            let err = typecheck_namespace_declarations(namespace, namespace_scope_id, project);
            error = error.or(err);
        } else {
            // Create a typecheck the unnamed namespace (aka a block scope)

            let namespace_scope_id = project.create_scope(scope_id, false);
            project.get_scope_mut(namespace_scope_id).namespace_name = namespace.name.clone();
            project
                .get_scope_mut(scope_id)
                .children
                .push(namespace_scope_id);
            typecheck_namespace_predecl(namespace, namespace_scope_id, project);
            error = error.or(typecheck_namespace_declarations(
                parsed_namespace,
                namespace_scope_id,
                project,
            ))
        }
    }

    // for (_, enum_) in parsed_namespace.enums.iter().enumerate() {
    //     // Finish typechecking the full enum
    //     let enum_id = project
    //         .find_enum_in_scope(scope_id, &enum_.name)
    //         .expect("internal error: can't find enum that has been previous added");

    //     error = error.or(typecheck_enum(
    //         enum_,
    //         enum_id,
    //         project.enums[enum_id].type_id,
    //         project.enums[enum_id].scope_id,
    //         scope_id,
    //         project,
    //     ));
    // }

    for (_, structure) in parsed_namespace.structs.iter().enumerate() {
        // Finish typechecking the full struct (including methods)
        let struct_id = project
            .find_struct_in_scope(scope_id, &structure.name)
            .expect("internal error: can't find struct that has been previous added");

        error = error.or(typecheck_struct(structure, struct_id, scope_id, project));
    }

    for (_, function) in parsed_namespace.functions.iter().enumerate() {
        // Typecheck the function bodies'
        let function_id = project
            .find_function_in_scope(scope_id, &function.name)
            .expect("internal error: can't find function that has been previous added");
        project.current_function_index = Some(function_id);
        error = error.or(typecheck_function(function, scope_id, project));
        project.current_function_index = None;
    }

    error
}

fn typecheck_enum_predecl(
    enum_: &ParsedEnum,
    enum_id: EnumId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let enum_scope_id = project.create_scope(parent_scope_id, false);
    let mut generic_parameters = Vec::new();
    let module_id = project.current_module().id;

    if enum_.variants.is_empty() {
        error = error.or(Some(JaktError::ParserErrorWithHint(
            "Empty enums are not allowed".to_string(),
            enum_.name_span,
            "Add at least one enum variant".to_string(),
            enum_.name_span,
        )));
    }

    for (generic_parameter, parameter_span) in &enum_.generic_parameters {
        project
            .current_module_mut()
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let parameter_type_id = TypeId(
            ModuleId(project.current_module_index),
            project.current_module().types.len() - 1,
        );
        if let Err(err) = project.add_type_to_scope(
            enum_scope_id,
            generic_parameter.to_string(),
            parameter_type_id,
            *parameter_span,
        ) {
            error = error.or(Some(err));
        }

        generic_parameters.push(parameter_type_id);
    }

    let (type_id, type_error) = typecheck_typename(&enum_.underlying_type, enum_scope_id, project);
    error = error.or(type_error);

    let underlying_type_id = if type_id == UNKNOWN_TYPE_ID {
        None
    } else {
        Some(type_id)
    };

    let enum_type_id = project
        .find_type_in_scope(parent_scope_id, &enum_.name)
        .expect("Enum must exist before predeclaration");

    project.current_module_mut().enums[enum_id.1] = CheckedEnum {
        name: enum_.name.clone(),
        generic_parameters,
        variants: Vec::new(),
        scope_id: enum_scope_id,
        definition_linkage: enum_.definition_linkage,
        definition_type: if enum_.is_boxed {
            DefinitionType::Class
        } else {
            DefinitionType::Struct
        },
        underlying_type_id,
        span: enum_.name_span,
        type_id: enum_type_id,
    };

    match project.add_enum_to_scope(
        parent_scope_id,
        enum_.name.clone(),
        enum_id,
        enum_.name_span,
    ) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    for function in &enum_.methods {
        let method_scope_id = project.create_scope(enum_scope_id, function.throws);
        let block_scope_id = project.create_scope(method_scope_id, function.throws);

        let is_generic =
            !enum_.generic_parameters.is_empty() || !function.generic_parameters.is_empty();

        let mut checked_function = CheckedFunction {
            name: function.name.clone(),
            name_span: function.name_span,
            params: vec![],
            throws: function.throws,
            return_type_id: UNKNOWN_TYPE_ID,
            return_type_span: None,
            visibility: function.visibility.clone(),
            function_scope_id: method_scope_id,
            generic_parameters: vec![],
            block: Some(CheckedBlock::new(block_scope_id)),
            parsed_function: Some(function.clone()),
            linkage: function.linkage,
            is_instantiated: !is_generic,
        };

        project
            .current_module_mut()
            .functions
            .push(checked_function.clone());
        let function_id = FunctionId(
            ModuleId(project.current_module_index),
            project.current_module().functions.len() - 1,
        );
        let previous_index = project.current_function_index;
        project.current_function_index = Some(function_id);

        let mut generic_parameters = vec![];

        for (generic_parameter, parameter_span) in &function.generic_parameters {
            project
                .current_module_mut()
                .types
                .push(Type::TypeVariable(generic_parameter.to_string()));
            let type_var_type_id = TypeId(module_id, project.current_module().types.len() - 1);

            generic_parameters.push(FunctionGenericParameter::Parameter(type_var_type_id));

            if !function.must_instantiate {
                if let Err(err) = project.add_type_to_scope(
                    method_scope_id,
                    generic_parameter.to_string(),
                    type_var_type_id,
                    *parameter_span,
                ) {
                    error = error.or(Some(err));
                }
            }
        }

        checked_function.generic_parameters = generic_parameters;
        let check_scope = if is_generic {
            Some(project.create_scope(method_scope_id, checked_function.throws))
        } else {
            None
        };

        for param in &function.params {
            if param.variable.name == "this" {
                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    type_id: enum_type_id,
                    type_span: Some(param.variable.span),
                    mutable: param.variable.mutable,
                    visibility: Visibility::Public,
                    definition_span: param.variable.span,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });

                if let Some(check_scope) = check_scope {
                    let _ = project.add_var_to_scope(
                        check_scope,
                        checked_variable,
                        param.variable.span,
                    );
                }
            } else {
                let (param_type, err) =
                    typecheck_typename(&param.variable.parsed_type, method_scope_id, project);
                error = error.or(err);

                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    type_id: param_type,
                    type_span: param.variable.parsed_type.span(),
                    mutable: param.variable.mutable,
                    visibility: Visibility::Public,
                    definition_span: param.variable.span,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });

                if let Some(check_scope) = check_scope {
                    let _ = project.add_var_to_scope(
                        check_scope,
                        checked_variable,
                        param.variable.span,
                    );
                }
            }
        }

        if let Err(err) = project.add_function_to_scope(
            enum_scope_id,
            function.name.clone(),
            FunctionId(
                project.current_module().id,
                project.current_module().functions.len() - 1,
            ),
            enum_.name_span,
        ) {
            error = error.or(Some(err));
        }

        let (function_return_type_id, err) =
            typecheck_typename(&function.return_type, method_scope_id, project);
        error = error.or(err);

        checked_function.return_type_id = function_return_type_id;
        if is_generic {
            let (block, _) = typecheck_block(
                &function.block,
                check_scope
                    .expect("Generic method with generic parameters must have a check scope"),
                project,
                SafetyMode::Safe,
            );

            let return_type_id = if function_return_type_id == UNKNOWN_TYPE_ID {
                if let Some(CheckedStatement::Return(Some(ret))) = block.stmts.last() {
                    ret.type_id(method_scope_id, project)
                } else {
                    VOID_TYPE_ID
                }
            } else {
                resolve_type_var(function_return_type_id, parent_scope_id, project)
            };

            checked_function.block = Some(block);
            checked_function.return_type_id = return_type_id;
        }

        project.current_module_mut().functions[function_id.1] = checked_function;
        project.current_function_index = previous_index;
    }

    error
}

fn typecheck_enum(
    enum_: &ParsedEnum,
    enum_id: EnumId,
    enum_type_id: TypeId,
    enum_scope_id: ScopeId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    // Check enum variants and resolve them if needed.
    let mut variants = Vec::new();

    let mut next_constant_value: Option<u64> = Some(0);
    let mut seen_names = HashSet::new();

    let cast_to_underlying =
        |x: ParsedExpression, project: &mut Project| -> (CheckedExpression, Option<JaktError>) {
            let span = x.span();
            let expression = ParsedExpression::UnaryOp(
                Box::new(x),
                UnaryOperator::TypeCast(TypeCast::Infallible(enum_.underlying_type.clone())),
                span,
            );
            typecheck_expression(&expression, enum_scope_id, project, SafetyMode::Safe, None)
        };

    let underlying_type_id = project.get_enum(enum_id).underlying_type_id;

    for variant in &enum_.variants {
        match &variant {
            EnumVariant::Untyped(name, span) => {
                if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    if underlying_type_id.is_some() {
                        if next_constant_value.is_none() {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Missing enum variant value, the enum underlying type is not numeric, and so all enum variants must have explicit values".to_string(),
                                *span,
                            )));
                        } else {
                            let (checked_expression, type_error) = cast_to_underlying(
                                ParsedExpression::NumericConstant(
                                    NumericConstant::U64(next_constant_value?),
                                    *span,
                                ),
                                project,
                            );
                            error = error.or(type_error);

                            variants.push(CheckedEnumVariant::WithValue(
                                name.clone(),
                                checked_expression,
                                *span,
                            ));
                            next_constant_value = Some(next_constant_value? + 1);

                            // This has a value, so generate a "variable" for it.
                            let err = project
                                .add_var_to_scope(
                                    enum_scope_id,
                                    CheckedVariable {
                                        name: name.clone(),
                                        type_id: enum_type_id,
                                        type_span: Some(*span),
                                        mutable: false,
                                        visibility: Visibility::Public,
                                        definition_span: *span,
                                    },
                                    *span,
                                )
                                .err();
                            error = error.or(err);
                        }
                    } else {
                        variants.push(CheckedEnumVariant::Untyped(name.clone(), *span));
                    }

                    if project
                        .find_function_in_scope(enum_scope_id, name.as_str())
                        .is_none()
                    {
                        let function_scope_id =
                            project.create_scope(parent_scope_id, enum_.is_boxed);
                        let block_scope_id =
                            project.create_scope(function_scope_id, enum_.is_boxed);

                        let checked_constructor = CheckedFunction {
                            name: name.clone(),
                            name_span: *span,
                            throws: enum_.is_boxed,
                            return_type_id: enum_type_id,
                            return_type_span: None,
                            params: vec![],
                            function_scope_id,
                            // Enum variant constructors are always visible.
                            visibility: Visibility::Public,
                            generic_parameters: enum_
                                .generic_parameters
                                .iter()
                                .map(|x| {
                                    FunctionGenericParameter::InferenceGuide(
                                        project
                                            .find_type_in_scope(enum_scope_id, x.0.as_str())
                                            .unwrap(),
                                    )
                                })
                                .collect(),
                            block: Some(CheckedBlock::new(block_scope_id)),
                            parsed_function: None,
                            linkage: FunctionLinkage::ImplicitEnumConstructor,
                            is_instantiated: true,
                        };

                        project
                            .current_module_mut()
                            .functions
                            .push(checked_constructor);

                        if let Err(err) = project.add_function_to_scope(
                            enum_scope_id,
                            name.clone(),
                            FunctionId(
                                project.current_module().id,
                                project.current_module().functions.len() - 1,
                            ),
                            *span,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                }
            }
            EnumVariant::WithValue(name, value, span) => {
                if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    let (checked_expression, type_error) =
                        cast_to_underlying((*value).clone(), project);
                    match checked_expression.to_number_constant() {
                        Some(constant) => {
                            next_constant_value = Some(constant.to_usize() as u64 + 1);
                        }
                        None => {
                            error = error.or(Some(JaktError::TypecheckError(
                                format!(
                                    "Enum variant '{}' in enum '{}' has a non-constant value: {:?}",
                                    name, enum_.name, checked_expression
                                ),
                                *span,
                            )));
                        }
                    }
                    error = error.or(type_error);

                    variants.push(CheckedEnumVariant::WithValue(
                        name.clone(),
                        checked_expression,
                        *span,
                    ));

                    // This has a value, so generate a "variable" for it.
                    let err = project
                        .add_var_to_scope(
                            enum_scope_id,
                            CheckedVariable {
                                name: name.clone(),
                                type_id: enum_type_id,
                                type_span: Some(*span),
                                mutable: false,
                                visibility: Visibility::Public,
                                definition_span: *span,
                            },
                            *span,
                        )
                        .err();
                    error = error.or(err);
                }
            }
            EnumVariant::StructLike(name, members, span) => {
                if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    let mut member_names = HashSet::new();
                    let mut checked_members = Vec::new();
                    for member in members {
                        if member_names.contains(&member.name) {
                            error = error.or(Some(JaktError::TypecheckError(
                                format!(
                                    "Enum variant '{}' has a member named '{}' more than once",
                                    name, member.name
                                ),
                                *span,
                            )));
                        } else {
                            member_names.insert(member.name.clone());
                            let (decl, type_error) =
                                typecheck_typename(&member.parsed_type, enum_scope_id, project);
                            error = error.or(type_error);
                            checked_members.push(CheckedVarDecl {
                                name: member.name.clone(),
                                type_id: decl,
                                type_span: member.parsed_type.span(),
                                mutable: member.mutable,
                                span: member.span,
                                visibility: member.visibility.clone(),
                            })
                        }
                    }

                    variants.push(CheckedEnumVariant::StructLike(
                        name.clone(),
                        checked_members.clone(),
                        *span,
                    ));

                    if project
                        .find_function_in_scope(enum_scope_id, name.as_str())
                        .is_none()
                    {
                        // Generate a constructor
                        let constructor_params = checked_members
                            .iter()
                            .map(|member| CheckedParameter {
                                requires_label: true,
                                variable: CheckedVariable {
                                    name: member.name.clone(),
                                    type_id: member.type_id,
                                    type_span: Some(*span),
                                    mutable: false,
                                    visibility: member.visibility.clone(),
                                    definition_span: *span,
                                },
                            })
                            .collect();

                        let function_scope_id =
                            project.create_scope(parent_scope_id, enum_.is_boxed);
                        let block_scope_id =
                            project.create_scope(function_scope_id, enum_.is_boxed);

                        let checked_constructor = CheckedFunction {
                            name: name.clone(),
                            name_span: *span,
                            throws: enum_.is_boxed,
                            return_type_id: enum_type_id,
                            return_type_span: None,
                            params: constructor_params,
                            visibility: Visibility::Public,
                            function_scope_id,
                            generic_parameters: enum_
                                .generic_parameters
                                .iter()
                                .map(|x| {
                                    FunctionGenericParameter::InferenceGuide(
                                        project
                                            .find_type_in_scope(enum_scope_id, x.0.as_str())
                                            .unwrap(),
                                    )
                                })
                                .collect(),
                            block: Some(CheckedBlock::new(block_scope_id)),
                            parsed_function: None,
                            linkage: FunctionLinkage::ImplicitEnumConstructor,
                            is_instantiated: true,
                        };

                        project
                            .current_module_mut()
                            .functions
                            .push(checked_constructor);

                        if let Err(err) = project.add_function_to_scope(
                            enum_scope_id,
                            name.clone(),
                            FunctionId(
                                project.current_module().id,
                                project.current_module().functions.len() - 1,
                            ),
                            *span,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                }
            }
            EnumVariant::Typed(name, unchecked_type, span) => {
                if !matches!(enum_.underlying_type, ParsedType::Empty) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Enum variants cannot have a type if the enum has an underlying type"
                            .to_string(),
                        *span,
                    )));
                } else if seen_names.contains(name) {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!("Enum variant '{}' is defined more than once", name),
                        *span,
                    )));
                } else {
                    seen_names.insert(name.clone());
                    let (checked_type, type_error) =
                        typecheck_typename(unchecked_type, enum_scope_id, project);
                    error = error.or(type_error);

                    variants.push(CheckedEnumVariant::Typed(name.clone(), checked_type, *span));

                    if project
                        .find_function_in_scope(enum_scope_id, name.as_str())
                        .is_none()
                    {
                        // Generate a constructor
                        let constructor_params = vec![CheckedParameter {
                            requires_label: false,
                            variable: CheckedVariable {
                                name: "value".to_string(),
                                type_id: checked_type,
                                type_span: Some(*span),
                                mutable: false,
                                visibility: Visibility::Public,
                                definition_span: *span,
                            },
                        }];
                        let function_scope_id =
                            project.create_scope(parent_scope_id, enum_.is_boxed);
                        let block_scope_id =
                            project.create_scope(function_scope_id, enum_.is_boxed);

                        let checked_constructor = CheckedFunction {
                            name: name.clone(),
                            name_span: *span,
                            throws: enum_.is_boxed,
                            return_type_id: enum_type_id,
                            return_type_span: None,
                            params: constructor_params,
                            visibility: Visibility::Public,
                            function_scope_id,
                            generic_parameters: enum_
                                .generic_parameters
                                .iter()
                                .map(|x| {
                                    FunctionGenericParameter::InferenceGuide(
                                        project
                                            .find_type_in_scope(enum_scope_id, x.0.as_str())
                                            .unwrap(),
                                    )
                                })
                                .collect(),
                            block: Some(CheckedBlock::new(block_scope_id)),
                            parsed_function: None,
                            linkage: FunctionLinkage::ImplicitEnumConstructor,
                            is_instantiated: true,
                        };

                        project
                            .current_module_mut()
                            .functions
                            .push(checked_constructor);

                        if let Err(err) = project.add_function_to_scope(
                            enum_scope_id,
                            name.clone(),
                            FunctionId(
                                project.current_module().id,
                                project.current_module().functions.len() - 1,
                            ),
                            *span,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                }
            }
        }
    }

    project.current_module_mut().enums[enum_id.1].variants = variants;

    for function in &enum_.methods {
        error = error.or(typecheck_method(
            function,
            project,
            StructOrEnumId::Enum(enum_id),
        ));
    }

    error
}

fn typecheck_struct_predecl(
    structure: &ParsedStruct,
    struct_id: StructId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let struct_type_id = project.find_or_add_type_id(Type::Struct(struct_id));
    project.current_struct_type_id = Some(struct_type_id);

    let struct_scope_id = project.create_scope(parent_scope_id, false);

    match project.add_struct_to_scope(
        parent_scope_id,
        structure.name.clone(),
        struct_id,
        structure.span,
    ) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    let mut generic_parameters = vec![];

    let is_extern = structure.definition_linkage == DefinitionLinkage::External;

    project.current_module_mut().structs[struct_id.1] = CheckedStruct {
        name: structure.name.clone(),
        name_span: structure.name_span,
        generic_parameters: vec![],
        fields: Vec::new(),
        scope_id: struct_scope_id,
        definition_linkage: structure.definition_linkage,
        definition_type: structure.definition_type,
        type_id: struct_type_id,
    };

    for (generic_parameter, parameter_span) in &structure.generic_parameters {
        project
            .current_module_mut()
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let parameter_type_id = TypeId(
            project.current_module().id,
            project.current_module().types.len() - 1,
        );

        generic_parameters.push(parameter_type_id);

        if let Err(err) = project.add_type_to_scope(
            struct_scope_id,
            generic_parameter.to_string(),
            parameter_type_id,
            *parameter_span,
        ) {
            error = error.or(Some(err));
        }
    }

    project.current_module_mut().structs[struct_id.1].generic_parameters =
        generic_parameters.clone();

    for function in &structure.methods {
        let method_scope_id = project.create_scope(struct_scope_id, function.throws);
        let block_scope_id = project.create_scope(method_scope_id, function.throws);

        let is_generic =
            !structure.generic_parameters.is_empty() || !function.generic_parameters.is_empty();

        let mut checked_function = CheckedFunction {
            name: function.name.clone(),
            name_span: function.name_span,
            params: vec![],
            throws: function.throws,
            return_type_id: UNKNOWN_TYPE_ID,
            return_type_span: function.return_type_span,
            visibility: function.visibility.clone(),
            function_scope_id: method_scope_id,
            generic_parameters: vec![],
            block: Some(CheckedBlock::new(block_scope_id)),
            parsed_function: Some(function.clone()),
            linkage: function.linkage,
            is_instantiated: !is_generic || is_extern,
        };

        project
            .current_module_mut()
            .functions
            .push(checked_function.clone());
        let function_id = FunctionId(
            project.current_module().id,
            project.current_module().functions.len() - 1,
        );
        let previous_index = project.current_function_index;
        project.current_function_index = Some(function_id);

        let mut generic_parameters = vec![];

        let check_scope = if is_generic {
            Some(project.create_scope(method_scope_id, function.throws))
        } else {
            None
        };

        for (generic_parameter, parameter_span) in &function.generic_parameters {
            project
                .current_module_mut()
                .types
                .push(Type::TypeVariable(generic_parameter.to_string()));
            let type_var_type_id = TypeId(
                project.current_module().id,
                project.current_module().types.len() - 1,
            );

            generic_parameters.push(FunctionGenericParameter::Parameter(type_var_type_id));
            if let Err(err) = project.add_type_to_scope(
                method_scope_id,
                generic_parameter.to_string(),
                type_var_type_id,
                *parameter_span,
            ) {
                error = error.or(Some(err));
            }
        }

        checked_function.generic_parameters = generic_parameters;

        for param in &function.params {
            if param.variable.name == "this" {
                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    type_id: struct_type_id,
                    type_span: Some(param.variable.span),
                    mutable: param.variable.mutable,
                    visibility: Visibility::Public,
                    definition_span: param.variable.span,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });

                if let Some(check_scope) = check_scope {
                    let _ = project.add_var_to_scope(
                        check_scope,
                        checked_variable,
                        param.variable.span,
                    );
                }
            } else {
                let (param_type, err) =
                    typecheck_typename(&param.variable.parsed_type, method_scope_id, project);
                error = error.or(err);

                let checked_variable = CheckedVariable {
                    name: param.variable.name.clone(),
                    type_id: param_type,
                    type_span: param.variable.parsed_type.span(),
                    mutable: param.variable.mutable,
                    visibility: Visibility::Public,
                    definition_span: param.variable.span,
                };

                checked_function.params.push(CheckedParameter {
                    requires_label: param.requires_label,
                    variable: checked_variable.clone(),
                });

                if let Some(check_scope) = check_scope {
                    let _ = project.add_var_to_scope(
                        check_scope,
                        checked_variable,
                        param.variable.span,
                    );
                }
            }
        }

        if let Err(err) = project.add_function_to_scope(
            struct_scope_id,
            function.name.clone(),
            FunctionId(
                project.current_module().id,
                project.current_module().functions.len() - 1,
            ),
            structure.span,
        ) {
            error = error.or(Some(err));
        }

        let (function_return_type_id, err) =
            typecheck_typename(&function.return_type, method_scope_id, project);
        error = error.or(err);

        checked_function.return_type_id = function_return_type_id;
        if is_generic {
            let (block, _) = typecheck_block(
                &function.block,
                check_scope
                    .expect("Generic method with generic parameters must have a check scope"),
                project,
                SafetyMode::Safe,
            );

            let return_type_id = if function_return_type_id == UNKNOWN_TYPE_ID {
                if let Some(CheckedStatement::Return(Some(ret))) = block.stmts.last() {
                    ret.type_id(method_scope_id, project)
                } else {
                    VOID_TYPE_ID
                }
            } else {
                resolve_type_var(function_return_type_id, parent_scope_id, project)
            };

            checked_function.block = Some(block);
            checked_function.return_type_id = return_type_id;
        }

        project.current_module_mut().functions[function_id.1] = checked_function;
        project.current_function_index = previous_index;
    }

    project.current_module_mut().structs[struct_id.1].generic_parameters = generic_parameters;

    if project.checking_prelude {
        // Cache various well-known struct IDs as they're used internally in
        // other Jakt code.
        if project.cached_array_struct_id == None && structure.name == "Array" {
            project.cached_array_struct_id = Some(struct_id);
        } else if project.cached_dictionary_struct_id == None && structure.name == "Dictionary" {
            project.cached_dictionary_struct_id = Some(struct_id);
        } else if project.cached_error_struct_id == None && structure.name == "Error" {
            project.cached_error_struct_id = Some(struct_id);
        } else if project.cached_optional_struct_id == None && structure.name == "Optional" {
            project.cached_optional_struct_id = Some(struct_id);
        } else if project.cached_range_struct_id == None && structure.name == "Range" {
            project.cached_range_struct_id = Some(struct_id);
        } else if project.cached_set_struct_id == None && structure.name == "Set" {
            project.cached_set_struct_id = Some(struct_id);
        } else if project.cached_tuple_struct_id == None && structure.name == "Tuple" {
            project.cached_tuple_struct_id = Some(struct_id);
        } else if project.cached_weakptr_struct_id == None && structure.name == "WeakPtr" {
            project.cached_weakptr_struct_id = Some(struct_id);
        }
    }

    project.current_struct_type_id = None;

    error
}

fn typecheck_struct_fields(
    structure: &ParsedStruct,
    struct_id: StructId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let mut fields = Vec::new();

    let checked_struct_scope_id = project.get_struct(struct_id).scope_id;
    let struct_type_id = project.find_or_add_type_id(Type::Struct(struct_id));
    project.current_struct_type_id = Some(struct_type_id);

    for unchecked_member in &structure.fields {
        let (checked_member_type, err) = typecheck_typename(
            &unchecked_member.parsed_type,
            checked_struct_scope_id,
            project,
        );
        error = error.or(err);

        fields.push(CheckedVarDecl {
            name: unchecked_member.name.clone(),
            type_id: checked_member_type,
            type_span: unchecked_member.parsed_type.span(),
            mutable: unchecked_member.mutable,
            span: unchecked_member.span,
            visibility: unchecked_member.visibility.clone(),
        });
    }

    project.get_struct_mut(struct_id).fields = fields;

    error
}

fn typecheck_struct(
    structure: &ParsedStruct,
    struct_id: StructId,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let checked_struct_scope_id = project.get_struct(struct_id).scope_id;
    let struct_type_id = project.find_or_add_type_id(Type::Struct(struct_id));
    let module_id = project.current_module().id;
    project.current_struct_type_id = Some(struct_type_id);

    if let Some(constructor_id) =
        project.find_function_in_scope(checked_struct_scope_id, &structure.name)
    {
        if structure.definition_type == DefinitionType::Class
            && structure.definition_linkage == DefinitionLinkage::External
        {
            // XXX: The parser always sets the linkage type of an extern class'
            //      constructor to External, but we actually want to call the
            //      class' ::create function, just like we do with a
            //      ImplicitConstructor class.
            project.get_function_mut(constructor_id).linkage =
                FunctionLinkage::ExternalClassConstructor;
        }
    } else if structure.definition_linkage != DefinitionLinkage::External {
        // No constructor found, so let's make one

        let mut constructor_params = Vec::new();
        for field in &project.get_struct(struct_id).fields {
            constructor_params.push(CheckedParameter {
                requires_label: true,
                variable: CheckedVariable {
                    name: field.name.clone(),
                    type_id: field.type_id,
                    type_span: None,
                    mutable: field.mutable,
                    // This is the constructor parameter, not the field. It can be public.
                    visibility: Visibility::Public,
                    definition_span: field.span,
                },
            });
        }

        let contructor_can_throw = structure.definition_type == DefinitionType::Class;
        let function_scope_id = project.create_scope(parent_scope_id, contructor_can_throw);
        let block_scope_id = project.create_scope(function_scope_id, contructor_can_throw);

        let checked_constructor = CheckedFunction {
            name: structure.name.clone(),
            name_span: structure.name_span,
            throws: structure.definition_type == DefinitionType::Class,
            return_type_id: struct_type_id,
            return_type_span: None,
            params: constructor_params,
            // The default constructor is public.
            visibility: Visibility::Public,
            function_scope_id,
            generic_parameters: vec![],
            block: Some(CheckedBlock::new(block_scope_id)),
            parsed_function: None,
            linkage: FunctionLinkage::ImplicitConstructor,
            is_instantiated: true,
        };

        // Internal constructor
        project
            .current_module_mut()
            .functions
            .push(checked_constructor);

        // Add constructor to the struct's scope
        if let Err(err) = project.add_function_to_scope(
            checked_struct_scope_id,
            structure.name.clone(),
            FunctionId(module_id, project.current_module().functions.len() - 1),
            structure.span,
        ) {
            error = error.or(Some(err));
        }
    }

    for function in &structure.methods {
        error = error.or(typecheck_method(
            function,
            project,
            StructOrEnumId::Struct(struct_id),
        ));
    }

    project.current_struct_type_id = None;
    error
}

fn typecheck_function_predecl(
    function: &ParsedFunction,
    parent_scope_id: ScopeId,
    this_arg_type_id: Option<TypeId>,
    project: &mut Project,
) -> Option<JaktError> {
    let mut error = None;

    let function_scope_id = project.create_scope(parent_scope_id, function.throws);
    let block_scope_id = project.create_scope(function_scope_id, function.throws);
    let module_id = project.current_module().id;

    let is_generic = if let Some(type_id) = this_arg_type_id {
        if let Type::GenericInstance(_, _) = project.get_type(type_id) {
            true
        } else {
            !function.generic_parameters.is_empty()
        }
    } else {
        !function.generic_parameters.is_empty()
    };

    let mut checked_function = CheckedFunction {
        name: function.name.clone(),
        name_span: function.name_span,
        params: vec![],
        throws: function.throws,
        return_type_id: UNKNOWN_TYPE_ID,
        return_type_span: function.return_type_span,
        visibility: function.visibility.clone(),
        function_scope_id,
        generic_parameters: vec![],
        block: Some(CheckedBlock::new(block_scope_id)),
        parsed_function: Some(function.clone()),
        linkage: function.linkage,
        is_instantiated: !is_generic,
    };
    project
        .current_module_mut()
        .functions
        .push(checked_function.clone());
    let function_id = FunctionId(module_id, project.current_module_mut().functions.len() - 1);
    let checked_function_scope_id = checked_function.function_scope_id;

    let previous_index = project.current_function_index;
    project.current_function_index = Some(function_id);

    let mut generic_parameters = vec![];

    for (generic_parameter, parameter_span) in &function.generic_parameters {
        project
            .current_module_mut()
            .types
            .push(Type::TypeVariable(generic_parameter.to_string()));
        let type_var_type_id = TypeId(
            project.current_module().id,
            project.current_module().types.len() - 1,
        );

        generic_parameters.push(FunctionGenericParameter::Parameter(type_var_type_id));

        if !function.must_instantiate || function.linkage == FunctionLinkage::External {
            if let Err(err) = project.add_type_to_scope(
                checked_function_scope_id,
                generic_parameter.to_string(),
                type_var_type_id,
                *parameter_span,
            ) {
                error = error.or(Some(err));
            }
        }
    }

    checked_function.generic_parameters = generic_parameters;
    let check_scope = if !is_generic {
        None
    } else {
        Some(project.create_scope(function_scope_id, function.throws))
    };

    let first = true;
    for param in &function.params {
        let (mut param_type, err) =
            typecheck_typename(&param.variable.parsed_type, function_scope_id, project);
        error = error.or(err);

        if first && param.variable.name == "this" {
            param_type = this_arg_type_id.unwrap_or(param_type);
        }

        let checked_variable = CheckedVariable {
            name: param.variable.name.clone(),
            type_id: param_type,
            type_span: param.variable.parsed_type.span(),
            mutable: param.variable.mutable,
            visibility: Visibility::Public,
            definition_span: param.variable.span,
        };

        checked_function.params.push(CheckedParameter {
            requires_label: param.requires_label,
            variable: checked_variable.clone(),
        });

        if let Some(check_scope) = check_scope {
            let _ = project.add_var_to_scope(check_scope, checked_variable, param.variable.span);
        }
    }

    let (function_return_type_id, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    checked_function.return_type_id = function_return_type_id;

    if !function.generic_parameters.is_empty() {
        let (block, _) = typecheck_block(
            &function.block,
            check_scope.expect("Generic function with generic parameters must have a check scope"),
            project,
            SafetyMode::Safe,
        );

        let return_type_id = if function_return_type_id == UNKNOWN_TYPE_ID {
            if let Some(CheckedStatement::Return(Some(ret))) = block.stmts.last() {
                ret.type_id(function_scope_id, project)
            } else {
                VOID_TYPE_ID
            }
        } else {
            resolve_type_var(function_return_type_id, parent_scope_id, project)
        };

        checked_function.block = Some(block);
        checked_function.return_type_id = return_type_id;
    }

    *project.get_function_mut(function_id) = checked_function;

    project.current_function_index = previous_index;

    match project.add_function_to_scope(
        parent_scope_id,
        function.name.clone(),
        function_id,
        function.name_span,
    ) {
        Ok(_) => {}
        Err(err) => error = error.or(Some(err)),
    }

    error
}

fn typecheck_and_specialize_generic_function(
    function_id: FunctionId,
    generic_arguments: Vec<TypeId>,
    parent_scope_id: ScopeId,
    this_type_id: Option<TypeId>,
    generic_substitutions: &HashMap<TypeId, TypeId>,
    project: &mut Project,
) -> Option<JaktError> {
    let function = project.get_function(function_id);
    let module_id = project.current_module().id;

    // Now we can actually resolve it, let's gooooo
    let function_id = FunctionId(module_id, project.current_module().functions.len());
    let mut function = function.to_parsed_function();
    let scope_id = project.create_scope(parent_scope_id, function.throws);
    let mut error = None;

    if function.generic_parameters.len() != generic_arguments.len() {
        return Some(JaktError::TypecheckError(
            format!(
                "Generic function {} expects {} generic arguments, but {} were given",
                function.name,
                function.generic_parameters.len(),
                generic_arguments.len()
            ),
            function.name_span,
        ));
    }

    let span = function.name_span;
    for (k, v) in generic_substitutions {
        if let Type::TypeVariable(name) = &project.get_type(*k) {
            let name_copy = name.clone();
            if let Err(err) = project.add_type_to_scope(scope_id, name_copy, *v, span) {
                error = error.or(Some(err));
            };
        }
    }

    function.must_instantiate = true;

    project.current_function_index = Some(function_id);

    let err = typecheck_function_predecl(&function, scope_id, this_type_id, project);
    error = error.or(err);

    let err = typecheck_function(&function, scope_id, project);
    error = error.or(err);

    project.current_function_index = None;

    let function = project.get_function_mut(function_id);
    function.is_instantiated = true;
    function.function_scope_id = scope_id;

    error
}

fn typecheck_function(
    function: &ParsedFunction,
    parent_scope_id: ScopeId,
    project: &mut Project,
) -> Option<JaktError> {
    if !function.generic_parameters.is_empty() && !function.must_instantiate {
        return None;
    }

    let mut error = None;

    let function_id = project
        .find_function_in_scope(parent_scope_id, &function.name)
        .expect("Internal error: missing previously defined function");

    if function.name == "main" {
        error = typecheck_jakt_main(function);
    }
    let checked_function = project.get_function_mut(function_id);
    let function_scope_id = checked_function.function_scope_id;
    let function_linkage = checked_function.linkage;

    let mut param_vars = Vec::new();
    for param in &checked_function.params {
        param_vars.push(param.variable.clone());
    }

    for variable in param_vars.into_iter() {
        let err = project
            .add_var_to_scope(function_scope_id, variable, function.name_span)
            .err();
        error = error.or(err);
    }

    // Do this once to resolve concrete types (if any)
    let (function_return_type_id, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    let checked_function = project.get_function_mut(function_id);
    checked_function.return_type_id = function_return_type_id;

    let (block, err) = typecheck_block(
        &function.block,
        function_scope_id,
        project,
        SafetyMode::Safe,
    );
    error = error.or(err);

    // typecheck the return type again to resolve any generics.
    let (function_return_type_id, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type_id = if function_return_type_id == UNKNOWN_TYPE_ID {
        if let Some(CheckedStatement::Return(Some(ret))) = block.stmts.last() {
            ret.type_id(function_scope_id, project)
        } else {
            VOID_TYPE_ID
        }
    } else {
        resolve_type_var(function_return_type_id, parent_scope_id, project)
    };

    if function_linkage != FunctionLinkage::External
        && return_type_id != VOID_TYPE_ID
        && !block.definitely_returns
    {
        // FIXME: Use better span
        error = error.or(Some(JaktError::TypecheckError(
            "Control reaches end of non-void function".to_string(),
            function.name_span,
        )));
    }

    let checked_function = project.get_function_mut(function_id);

    checked_function.block = Some(block);
    checked_function.return_type_id = return_type_id;

    error
}

fn typecheck_jakt_main(function: &ParsedFunction) -> Option<JaktError> {
    let param_type_error = Some(JaktError::TypecheckError(
        "Main function must take a single array of strings as its parameter".to_string(),
        function.name_span,
    ));

    if function.params.len() > 1 {
        return param_type_error;
    }

    if !function.params.is_empty() {
        match &function.params[0].variable.parsed_type {
            ParsedType::Array(parsed_type, _) => match &**parsed_type {
                ParsedType::Empty => {}
                ParsedType::Name(name, _) if name == "String" => {}
                _ => return param_type_error,
            },
            _ => return param_type_error,
        };
    }

    let return_type_error = Some(JaktError::TypecheckError(
        "Main function must return c_int".to_string(),
        function.name_span,
    ));
    match &function.return_type {
        ParsedType::Empty => {}
        ParsedType::Name(name, _) if name == "c_int" => {}
        _ => return return_type_error,
    }
    None
}

fn typecheck_method(
    function: &ParsedFunction,
    project: &mut Project,
    parent_id: StructOrEnumId,
) -> Option<JaktError> {
    let mut error = None;

    let (parent_generic_parameters, scope_id, definition_linkage) = match parent_id {
        StructOrEnumId::Struct(struct_id) => {
            let structure = project.get_struct_mut(struct_id);
            let parent_generic_parameters = &structure.generic_parameters;
            let scope_id = structure.scope_id;
            let definition_linkage = structure.definition_linkage;
            (parent_generic_parameters, scope_id, definition_linkage)
        }
        StructOrEnumId::Enum(enum_id) => {
            let enum_ = project.get_enum_mut(enum_id);
            let parent_generic_parameters = &enum_.generic_parameters;
            let scope_id = enum_.scope_id;
            let definition_linkage = enum_.definition_linkage;
            (parent_generic_parameters, scope_id, definition_linkage)
        }
    };

    if (!function.generic_parameters.is_empty() || !parent_generic_parameters.is_empty())
        && !function.must_instantiate
    {
        return None;
    }

    let structure_scope_id = scope_id;
    let structure_linkage = definition_linkage;

    let method_id = project.find_function_in_scope(structure_scope_id, &function.name);

    let method_id = method_id
        .expect("Internal error: we just pushed the checked function, but it's not present");

    let checked_function = project.get_function(method_id);
    let function_scope_id = checked_function.function_scope_id;

    let mut param_vars = Vec::new();
    for param in &checked_function.params {
        param_vars.push(param.variable.clone());
    }

    for variable in param_vars.into_iter() {
        let err = project
            .add_var_to_scope(function_scope_id, variable, function.name_span)
            .err();
        error = error.or(err);
    }

    // Set current function index before a block type check so that
    // method return type is checked against its implementation
    project.current_function_index = Some(method_id);

    let (block, err) = typecheck_block(
        &function.block,
        function_scope_id,
        project,
        SafetyMode::Safe,
    );
    error = error.or(err);

    let (function_return_type_id, err) =
        typecheck_typename(&function.return_type, function_scope_id, project);
    error = error.or(err);

    // If the return type is unknown, and the function starts with a return statement,
    // we infer the return type from its expression.
    let return_type_id = if function_return_type_id == UNKNOWN_TYPE_ID {
        if let Some(CheckedStatement::Return(Some(ret))) = block.stmts.first() {
            ret.type_id(function_scope_id, project)
        } else {
            VOID_TYPE_ID
        }
    } else {
        function_return_type_id
    };

    if structure_linkage != DefinitionLinkage::External
        && return_type_id != VOID_TYPE_ID
        && !block.definitely_returns
    {
        // FIXME: Use better span
        error = error.or(Some(JaktError::TypecheckError(
            "Control reaches end of non-void function".to_string(),
            function.name_span,
        )));
    }

    let checked_function = project.get_function_mut(method_id);

    checked_function.block = Some(block);
    checked_function.return_type_id = return_type_id;

    error
}

pub fn statement_definitely_returns(stmt: &CheckedStatement) -> bool {
    match stmt {
        CheckedStatement::Return(_) => true,
        CheckedStatement::If(CheckedExpression::Boolean(true, _), then_block, _) => {
            then_block.definitely_returns
        }
        CheckedStatement::If(_, then_block, Some(else_stmt)) => {
            then_block.definitely_returns && statement_definitely_returns(else_stmt.as_ref())
        }
        CheckedStatement::Block(block) => block.definitely_returns,
        CheckedStatement::Loop(block) => block.definitely_returns,
        CheckedStatement::While(_, block) => block.definitely_returns,
        CheckedStatement::Expression(match_expr @ CheckedExpression::Match(..)) => {
            match_expr.definitely_returns()
        }
        _ => false,
    }
}

pub fn typecheck_block(
    block: &ParsedBlock,
    parent_scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedBlock, Option<JaktError>) {
    let mut error = None;

    let parent_throws = project.get_scope(parent_scope_id).throws;
    let block_scope_id = project.create_scope(parent_scope_id, parent_throws);
    let mut checked_block = CheckedBlock::new(block_scope_id);
    let mut generic_inferences = HashMap::new();

    for stmt in &block.stmts {
        let (checked_stmt, err) = typecheck_statement(stmt, block_scope_id, project, safety_mode);
        error = error.or(err);

        if statement_definitely_returns(&checked_stmt) {
            checked_block.definitely_returns = true;
        }

        if let (ParsedStatement::Yield(_, span), CheckedStatement::Yield(expr)) =
            (stmt, &checked_stmt)
        {
            let type_ = expr.type_id(block_scope_id, project);
            if let Some(yielded_type) = checked_block.yielded_type {
                let err = check_types_for_compat(
                    yielded_type,
                    type_,
                    &mut generic_inferences,
                    *span,
                    project,
                );
                error = error.or(err);
            } else {
                checked_block.yielded_type = Some(type_);
            }
        }

        checked_block.stmts.push(checked_stmt);
    }

    if let Some(type_id) = checked_block.yielded_type {
        checked_block.yielded_type = Some(substitute_typevars_in_type(
            type_id,
            &generic_inferences,
            project,
        ));
    }

    (checked_block, error)
}

fn find_yield_span_in_block(block: &ParsedBlock) -> Option<Span> {
    for stmt in &block.stmts {
        if let ParsedStatement::Yield(_, span) = stmt {
            return Some(*span);
        }
    }

    None
}

pub fn typecheck_statement(
    stmt: &ParsedStatement,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedStatement, Option<JaktError>) {
    let mut error = None;

    match stmt {
        ParsedStatement::Try(stmt, error_name, error_span, catch_block) => {
            let try_scope_id = project.create_scope(scope_id, true);
            let (checked_stmt, err) = typecheck_statement(stmt, try_scope_id, project, safety_mode);
            error = error.or(err);

            let error_struct_id = project.get_error_struct_id(*error_span);
            let error_decl = CheckedVariable {
                name: error_name.clone(),
                mutable: false,
                type_id: project.find_or_add_type_id(Type::Struct(error_struct_id)),
                type_span: None,
                visibility: Visibility::Public,
                definition_span: *error_span,
            };

            let catch_scope_id = project.create_scope(scope_id, false);

            let err = project
                .add_var_to_scope(catch_scope_id, error_decl, *error_span)
                .err();
            error = error.or(err);

            let (checked_catch_block, err) =
                typecheck_block(catch_block, catch_scope_id, project, safety_mode);
            error = error.or(err);
            (
                CheckedStatement::Try(
                    Box::new(checked_stmt),
                    error_name.clone(),
                    checked_catch_block,
                ),
                error,
            )
        }
        ParsedStatement::Throw(expr) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let error_struct_type_id = project.find_type_in_prelude("Error");

            if checked_expr.type_id(scope_id, project) != error_struct_type_id {
                error = error.or(Some(JaktError::TypecheckError(
                    "throw expression does not produce an error".to_string(),
                    expr.span(),
                )));
            }

            let scope = project.get_scope(scope_id);
            if !scope.throws {
                error = error.or(Some(JaktError::TypecheckError(
                    "Throw statement needs to be in a try statement or a function marked as throws"
                        .to_string(),
                    expr.span(),
                )));
            }

            (CheckedStatement::Throw(checked_expr), error)
        }
        ParsedStatement::For((iterator_name, iterator_span), range_expr, block) => {
            if let Some(span) = find_yield_span_in_block(block) {
                error = error.or(Some(JaktError::TypecheckError(
                    "a 'for' loop block is not allowed to yield values".to_string(),
                    span,
                )))
            }
            // Translate `for x in expr { body }` to
            // block {
            //     let (mutable) _magic = expr
            //     loop {
            //         let x = _magic.next()
            //         if not x.has_value() {
            //             break
            //         }
            //         let iterator_name = x!
            //         body
            //     }
            // }
            //
            // The only restrictions placed on the iterator are such:
            //     1- Must respond to .next(); the mutability of the iterator is inferred from .next()'s signature
            //     2- The result of .next() must be an Optional.

            let (iterable_expr, err) =
                typecheck_expression(range_expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let iterable_type = project.get_type(iterable_expr.type_id(scope_id, project));
            let mut iterable_should_be_mutable = false;
            // Requirement 1: Iterator must have a .next() method
            //                This currently limits it to structs and classes.
            // Right now we do a single pass check, and check generic functions at declaration time (as opposed to doing so at instantiation time)
            // so we have to pretend it's okay if we don't know the iterable type right now.
            match iterable_type {
                Type::TypeVariable(_) => {
                    // Since we're not sure, just make it mutable.
                    iterable_should_be_mutable = true;
                }
                Type::GenericInstance(struct_id, _) | Type::Struct(struct_id) => {
                    let struct_ = project.get_struct(*struct_id);
                    let next_method_function_id =
                        project.find_function_in_scope(struct_.scope_id, "next");
                    if let Some(next_method_function_id) = next_method_function_id {
                        let next_method_function = project.get_function(next_method_function_id);
                        // Check whether we need to make the iterator mutable
                        if next_method_function.is_mutating() {
                            iterable_should_be_mutable = true;
                        }
                    } else {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Iterator must have a .next() method".into(),
                            range_expr.span(),
                        )));
                    }
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Iterator must have a .next() method".into(),
                        *iterator_span,
                    )));
                }
            }

            let rewritten_statement = ParsedStatement::Block(ParsedBlock {
                stmts: vec![
                    // let (mutable) _magic = expr
                    ParsedStatement::VarDecl(
                        ParsedVarDecl {
                            name: "_magic".to_string(),
                            parsed_type: ParsedType::Empty,
                            mutable: iterable_should_be_mutable,
                            span: *iterator_span,
                            inlay_position: None,
                            visibility: Visibility::Public,
                        },
                        range_expr.clone(),
                    ),
                    // loop {
                    ParsedStatement::Loop(ParsedBlock {
                        stmts: vec![
                            // let x = _magic.next()
                            ParsedStatement::VarDecl(
                                ParsedVarDecl {
                                    name: "_magic_value".to_string(),
                                    parsed_type: ParsedType::Empty,
                                    mutable: iterable_should_be_mutable,
                                    span: *iterator_span,
                                    inlay_position: None,
                                    visibility: Visibility::Public,
                                },
                                ParsedExpression::MethodCall(
                                    Box::new(ParsedExpression::Var(
                                        "_magic".to_string(),
                                        *iterator_span,
                                    )),
                                    ParsedCall {
                                        name: "next".to_string(),
                                        namespace: vec![],
                                        args: vec![],
                                        type_args: vec![],
                                    },
                                    *iterator_span,
                                ),
                            ),
                            // if not x.has_value() {
                            ParsedStatement::If(
                                ParsedExpression::UnaryOp(
                                    Box::new(ParsedExpression::MethodCall(
                                        Box::new(ParsedExpression::Var(
                                            "_magic_value".to_string(),
                                            *iterator_span,
                                        )),
                                        ParsedCall {
                                            name: "has_value".to_string(),
                                            namespace: vec![],
                                            args: vec![],
                                            type_args: vec![],
                                        },
                                        *iterator_span,
                                    )),
                                    UnaryOperator::LogicalNot,
                                    *iterator_span,
                                ),
                                ParsedBlock {
                                    stmts: vec![
                                        // break
                                        ParsedStatement::Break,
                                    ],
                                },
                                None,
                            ),
                            // let iterator_name = x!
                            ParsedStatement::VarDecl(
                                ParsedVarDecl {
                                    name: iterator_name.to_string(),
                                    parsed_type: ParsedType::Empty,
                                    mutable: iterable_should_be_mutable,
                                    span: *iterator_span,
                                    inlay_position: Some(*iterator_span),
                                    visibility: Visibility::Public,
                                },
                                ParsedExpression::ForcedUnwrap(
                                    Box::new(ParsedExpression::Var(
                                        "_magic_value".to_string(),
                                        *iterator_span,
                                    )),
                                    *iterator_span,
                                ),
                            ),
                            // body
                            ParsedStatement::Block(block.clone()),
                        ],
                    }),
                ],
            });

            let (statement, err) =
                typecheck_statement(&rewritten_statement, scope_id, project, safety_mode);
            error = error.or(err);
            (statement, error)
        }
        ParsedStatement::Continue => (CheckedStatement::Continue, None),
        ParsedStatement::Break => (CheckedStatement::Break, None),
        ParsedStatement::Expression(expr) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);

            (CheckedStatement::Expression(checked_expr), err)
        }
        ParsedStatement::Defer(statement, span) => {
            let was_inside_defer = project.inside_defer;
            project.inside_defer = true;
            let (checked_statement, mut err) =
                typecheck_statement(statement, scope_id, project, safety_mode);

            if let CheckedStatement::Block(block) = &checked_statement {
                if block.yielded_type.is_some() {
                    err = err.or(Some(JaktError::TypecheckError(
                        "‘yield’ inside ‘defer’ is meaningless".to_string(),
                        *span,
                    )));
                }
            }

            project.inside_defer = was_inside_defer;

            (CheckedStatement::Defer(Box::new(checked_statement)), err)
        }
        ParsedStatement::UnsafeBlock(block) => {
            let (checked_block, err) =
                typecheck_block(block, scope_id, project, SafetyMode::Unsafe);

            (CheckedStatement::Block(checked_block), err)
        }
        ParsedStatement::VarDecl(var_decl, init) => {
            let (mut lhs_type_id, typename_err) =
                typecheck_typename(&var_decl.parsed_type, scope_id, project);
            error = error.or(typename_err);

            let (mut checked_expression, err) =
                typecheck_expression(init, scope_id, project, safety_mode, Some(lhs_type_id));
            error = error.or(err);

            let rhs_type_id = checked_expression.type_id(scope_id, project);

            if lhs_type_id == UNKNOWN_TYPE_ID && rhs_type_id != UNKNOWN_TYPE_ID {
                lhs_type_id = rhs_type_id;
            }

            let err = try_promote_constant_expr_to_type(
                lhs_type_id,
                &mut checked_expression,
                &init.span(),
            );
            error = error.or(err);

            let weakptr_struct_id = project.get_weakptr_struct_id(var_decl.span);
            let optional_struct_id = project.get_optional_struct_id(var_decl.span);

            match project.get_type(lhs_type_id) {
                Type::GenericInstance(struct_id, type_args) if *struct_id == weakptr_struct_id => {
                    if !var_decl.mutable {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Weak reference must be mutable".into(),
                            var_decl.span,
                        )));
                    }
                    if lhs_type_id != rhs_type_id
                        && type_args[0] != rhs_type_id
                        && rhs_type_id != UNKNOWN_TYPE_ID
                    {
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            checked_expression.span(),
                        )));
                    }
                }
                Type::GenericInstance(struct_id, type_args) if *struct_id == optional_struct_id => {
                    if lhs_type_id != rhs_type_id
                        && type_args[0] != rhs_type_id
                        && rhs_type_id != UNKNOWN_TYPE_ID
                    {
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            checked_expression.span(),
                        )));
                    }
                }
                Type::Builtin => {
                    let is_rhs_zero = match checked_expression.to_number_constant() {
                        Some(c) => match c {
                            NumberConstant::Signed(v) => v == 0,
                            NumberConstant::Unsigned(v) => v == 0,
                            NumberConstant::Floating(v) => v == 0.0,
                        },
                        None => false,
                    };

                    if !(is_numeric(lhs_type_id) && is_rhs_zero)
                        && is_integer(lhs_type_id) ^ is_integer(rhs_type_id)
                    {
                        return (
                            CheckedStatement::Garbage,
                            Some(JaktError::TypecheckError(
                                format!(
                                    "Type mismatch: expected ‘{}’, but got ‘{}’",
                                    project.typename_for_type_id(lhs_type_id),
                                    project.typename_for_type_id(rhs_type_id),
                                ),
                                checked_expression.span(),
                            )),
                        );
                    }
                }
                _ => {}
            }

            let checked_var_decl = CheckedVarDecl {
                name: var_decl.name.clone(),
                type_id: lhs_type_id,
                type_span: var_decl.parsed_type.span(),
                span: var_decl.span,
                mutable: var_decl.mutable,
                visibility: var_decl.visibility.clone(),
            };

            if project.dump_type_hints {
                if let Some(inlay_position) = var_decl.inlay_position {
                    println!(
                        "{{\"type\": \"hint\", \"file_id\": {}, \"position\": {}, \"typename\": \"{}\" }}",
                        inlay_position.file_id,
                        inlay_position.end,
                        project.typename_for_type_id(lhs_type_id)
                    );
                }
            }

            let err = project
                .add_var_to_scope(
                    scope_id,
                    CheckedVariable {
                        name: checked_var_decl.name.clone(),
                        type_id: checked_var_decl.type_id,
                        type_span: None,
                        mutable: checked_var_decl.mutable,
                        visibility: checked_var_decl.visibility.clone(),
                        definition_span: checked_var_decl.span,
                    },
                    checked_var_decl.span,
                )
                .err();
            error = error.or(err);

            (
                CheckedStatement::VarDecl(checked_var_decl, checked_expression),
                error,
            )
        }
        ParsedStatement::If(cond, block, else_stmt) => {
            let (checked_cond, err) =
                typecheck_expression(cond, scope_id, project, safety_mode, None);
            error = error.or(err);

            if checked_cond.type_id(scope_id, project) != BOOL_TYPE_ID {
                error = error.or(Some(JaktError::TypecheckError(
                    "Condition must be a boolean expression".to_string(),
                    checked_cond.span(),
                )));
            }

            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);
            if checked_block.yielded_type.is_some() {
                error = error.or(Some(JaktError::TypecheckError(
                    "an 'if' block is not allowed to yield values".to_string(),
                    find_yield_span_in_block(block)
                        .expect("must have a yield if the block yields values"),
                )))
            }

            let else_output;
            if let Some(else_stmt) = else_stmt {
                let (checked_stmt, err) =
                    typecheck_statement(else_stmt, scope_id, project, safety_mode);
                error = error.or(err);

                else_output = Some(Box::new(checked_stmt));
            } else {
                else_output = None;
            }

            (
                CheckedStatement::If(checked_cond, checked_block, else_output),
                error,
            )
        }
        ParsedStatement::Loop(block) => {
            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);
            if checked_block.yielded_type.is_some() {
                error = error.or(Some(JaktError::TypecheckError(
                    "a 'loop' block is not allowed to yield values".to_string(),
                    find_yield_span_in_block(block)
                        .expect("must have a yield if the block yields values"),
                )))
            }

            (CheckedStatement::Loop(checked_block), error)
        }
        ParsedStatement::While(cond, block) => {
            let (checked_cond, err) =
                typecheck_expression(cond, scope_id, project, safety_mode, None);
            error = error.or(err);

            if checked_cond.type_id(scope_id, project) != BOOL_TYPE_ID {
                error = error.or(Some(JaktError::TypecheckError(
                    "Condition must be a boolean expression".to_string(),
                    checked_cond.span(),
                )));
            }

            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);

            if checked_block.yielded_type.is_some() {
                error = error.or(Some(JaktError::TypecheckError(
                    "a 'while' block is not allowed to yield values".to_string(),
                    find_yield_span_in_block(block)
                        .expect("must have a yield if the block yields values"),
                )))
            }

            (CheckedStatement::While(checked_cond, checked_block), error)
        }
        ParsedStatement::Return(expr, span) => {
            let mut checked_expr = None;
            if let Some(expr) = expr {
                let (output, err) = typecheck_expression(
                    expr,
                    scope_id,
                    project,
                    safety_mode,
                    project
                        .current_function_index
                        .map(|i| project.get_function(i).return_type_id),
                );
                checked_expr = Some(output);
                error = error.or(err);
            }

            if project.inside_defer {
                error = error.or(Some(JaktError::TypecheckError(
                    "‘return’ is not allowed inside ‘defer’".to_string(),
                    *span,
                )));
            }

            (CheckedStatement::Return(checked_expr), error)
        }
        ParsedStatement::Yield(expr, _) => {
            let (output, err) = typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            (CheckedStatement::Yield(output), error)
        }
        ParsedStatement::Block(block) => {
            let (checked_block, mut err) = typecheck_block(block, scope_id, project, safety_mode);
            if checked_block.yielded_type.is_some() {
                err = err.or(Some(JaktError::TypecheckError(
                    "A block used as a statement cannot yield values, as the value cannot be observed in any way".to_string(),
                    find_yield_span_in_block(block).expect("must have a yield if the block yields values"),

                )))
            }

            (CheckedStatement::Block(checked_block), err)
        }
        ParsedStatement::InlineCpp(block, span) => {
            if safety_mode == SafetyMode::Safe {
                return (
                    CheckedStatement::InlineCpp(vec![]),
                    Some(JaktError::TypecheckError(
                        "Use of inline cpp block outside of unsafe block".to_string(),
                        *span,
                    )),
                );
            }

            let mut strings: Vec<String> = vec![];

            for statement in &block.stmts {
                match statement {
                    ParsedStatement::Expression(ParsedExpression::QuotedString(string, _)) => {
                        strings.push(string.clone())
                    }
                    _ => {
                        return (
                            CheckedStatement::InlineCpp(vec![]),
                            Some(JaktError::TypecheckError(
                                "Expected block of strings".to_string(),
                                *span,
                            )),
                        );
                    }
                }
            }
            (CheckedStatement::InlineCpp(strings), None)
        }
        ParsedStatement::Garbage => (CheckedStatement::Garbage, None),
    }
}

pub fn try_promote_constant_expr_to_type(
    lhs_type_id: TypeId,
    checked_rhs: &mut CheckedExpression,
    span: &Span,
) -> Option<JaktError> {
    if !is_integer(lhs_type_id) {
        return None;
    }
    if let Some(rhs_constant) = checked_rhs.to_number_constant() {
        if let (Some(new_constant), new_type_id) = rhs_constant.promote(lhs_type_id) {
            *checked_rhs = CheckedExpression::NumericConstant(new_constant, *span, new_type_id);
        } else {
            return Some(JaktError::TypecheckError(
                "Integer promotion failed".to_string(),
                *span,
            ));
        }
    }

    None
}

pub fn typecheck_match_body(
    body: &MatchBody,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
    generic_parameters: &mut HashMap<TypeId, TypeId>,
    final_result_type: &mut Option<TypeId>,
    span: Span,
) -> (CheckedMatchBody, Option<JaktError>) {
    let mut error = None;
    let body = match body {
        MatchBody::Block(block) => {
            let (checked_block, err) = typecheck_block(block, scope_id, project, safety_mode);
            error = error.or(err);
            if !checked_block.definitely_returns {
                let block_type_id = checked_block.yielded_type.unwrap_or(VOID_TYPE_ID);
                match final_result_type {
                    Some(type_id) => {
                        if let Some(err) = check_types_for_compat(
                            block_type_id,
                            *type_id,
                            generic_parameters,
                            span,
                            project,
                        ) {
                            error = error.or(Some(err));
                        }
                    }
                    None => {
                        *final_result_type = Some(block_type_id);
                    }
                }
            }
            if let Some(type_id) = checked_block.yielded_type {
                CheckedMatchBody::Expression(CheckedExpression::Block(
                    Box::new(checked_block),
                    span,
                    type_id,
                ))
            } else {
                CheckedMatchBody::Block(checked_block)
            }
        }
        MatchBody::Expression(expr) => {
            let (body, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, *final_result_type);
            error = error.or(err);
            let span = expr.span();
            match final_result_type {
                Some(type_id) => {
                    if let Some(err) = check_types_for_compat(
                        body.type_id(scope_id, project),
                        *type_id,
                        generic_parameters,
                        span,
                        project,
                    ) {
                        error = error.or(Some(err));
                    }
                }
                None => {
                    *final_result_type = Some(body.type_id(scope_id, project));
                }
            }
            CheckedMatchBody::Expression(body)
        }
    };
    (body, error)
}

pub fn typecheck_expression(
    expr: &ParsedExpression,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
    type_hint: Option<TypeId>,
) -> (CheckedExpression, Option<JaktError>) {
    let mut error = None;

    match expr {
        ParsedExpression::Range(start_expr, end_expr, span) => {
            let (mut checked_start, err) =
                typecheck_expression(start_expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let (mut checked_end, err) =
                typecheck_expression(end_expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            // If the range starts or ends at a constant number, we try promoting the constant to the
            // type of the other end. This makes ranges like `0..array.size()` (as the 0 becomes 0uz).
            let err = try_promote_constant_expr_to_type(
                checked_start.type_id(scope_id, project),
                &mut checked_end,
                span,
            );
            error = error.or(err);
            let err = try_promote_constant_expr_to_type(
                checked_end.type_id(scope_id, project),
                &mut checked_start,
                span,
            );
            error = error.or(err);

            if checked_start.type_id(scope_id, project) != checked_end.type_id(scope_id, project) {
                error = error.or(Some(JaktError::TypecheckError(
                    "Range start and end must be the same type".to_string(),
                    *span,
                )))
            }

            let range_struct_id = project.get_range_struct_id(*span);
            let type_ = Type::GenericInstance(
                range_struct_id,
                vec![checked_start.type_id(scope_id, project)],
            );
            let type_id = project.find_or_add_type_id(type_);

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::Range(
                    Box::new(checked_start),
                    Box::new(checked_end),
                    *span,
                    type_id,
                ),
                error,
            )
        }
        ParsedExpression::BinaryOp(lhs, op, rhs, span) => {
            let (checked_lhs, err) =
                typecheck_expression(lhs, scope_id, project, safety_mode, None);
            error = error.or(err);

            let (mut checked_rhs, err) =
                typecheck_expression(rhs, scope_id, project, safety_mode, None);
            error = error.or(err);

            let err = try_promote_constant_expr_to_type(
                checked_lhs.type_id(scope_id, project),
                &mut checked_rhs,
                span,
            );
            error = error.or(err);

            // TODO: actually do the binary operator typecheck against safe operations
            // For now, use a type we know
            let (type_id, err) = typecheck_binary_operation(
                &checked_lhs,
                op,
                &checked_rhs,
                scope_id,
                *span,
                project,
            );
            error = error.or(err);

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::BinaryOp(
                    Box::new(checked_lhs),
                    op.clone(),
                    Box::new(checked_rhs),
                    *span,
                    type_id,
                ),
                error,
            )
        }
        ParsedExpression::UnaryOp(expr, op, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let checked_op = match op {
                UnaryOperator::PreIncrement => CheckedUnaryOperator::PreIncrement,
                UnaryOperator::PostIncrement => CheckedUnaryOperator::PostIncrement,
                UnaryOperator::PreDecrement => CheckedUnaryOperator::PreDecrement,
                UnaryOperator::PostDecrement => CheckedUnaryOperator::PostDecrement,
                UnaryOperator::Negate => CheckedUnaryOperator::Negate,
                UnaryOperator::Dereference => CheckedUnaryOperator::Dereference,
                UnaryOperator::RawAddress => CheckedUnaryOperator::RawAddress,
                UnaryOperator::LogicalNot => CheckedUnaryOperator::LogicalNot,
                UnaryOperator::BitwiseNot => CheckedUnaryOperator::BitwiseNot,
                UnaryOperator::Is(unchecked_type) => {
                    let (type_id, err) = typecheck_typename(unchecked_type, scope_id, project);
                    loop {
                        if type_id == UNKNOWN_TYPE_ID && err.is_some() {
                            // Let's assume it's an enum variant
                            if let ParsedType::Name(name, _) = unchecked_type {
                                let type_id = checked_expr.type_id(scope_id, project);
                                if let Type::Enum(enum_id) = project.get_type(type_id) {
                                    let enum_ = project.get_enum(*enum_id);
                                    let exists =
                                        enum_.variants.iter().any(|variant| match variant {
                                            CheckedEnumVariant::StructLike(var_name, _, _)
                                            | CheckedEnumVariant::Typed(var_name, _, _)
                                            | CheckedEnumVariant::Untyped(var_name, _) => {
                                                name == var_name
                                            }
                                            _ => false,
                                        });
                                    if !exists {
                                        error = error.or(Some(JaktError::TypecheckError(
                                            format!(
                                                "Enum variant {} does not exist on {}",
                                                name,
                                                project.typename_for_type_id(type_id)
                                            ),
                                            *span,
                                        )));
                                    }
                                    break CheckedUnaryOperator::IsEnumVariant(name.clone());
                                }
                            }
                        }

                        error = error.or(err);
                        break CheckedUnaryOperator::Is(type_id);
                    }
                }
                UnaryOperator::TypeCast(cast) => {
                    let (type_id, err) =
                        typecheck_typename(&cast.unchecked_type(), scope_id, project);
                    error = error.or(err);
                    let checked_cast = match cast {
                        TypeCast::Fallible(_) => CheckedTypeCast::Fallible(type_id),
                        TypeCast::Infallible(_) => CheckedTypeCast::Infallible(type_id),
                    };
                    CheckedUnaryOperator::TypeCast(checked_cast)
                }
            };

            let (checked_expr, err) = typecheck_unary_operation(
                checked_expr,
                checked_op,
                *span,
                scope_id,
                project,
                safety_mode,
            );
            error = error.or(err);

            (checked_expr, error)
        }
        ParsedExpression::OptionalNone(span) => (
            CheckedExpression::OptionalNone(*span, UNKNOWN_TYPE_ID),
            None,
        ),
        ParsedExpression::OptionalSome(expr, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            let type_id = checked_expr.type_id(scope_id, project);

            let optional_type =
                Type::GenericInstance(project.get_optional_struct_id(*span), vec![type_id]);
            let optional_type_id = project.find_or_add_type_id(optional_type);

            (
                CheckedExpression::OptionalSome(Box::new(checked_expr), *span, optional_type_id),
                err,
            )
        }
        ParsedExpression::ForcedUnwrap(expr, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);

            let type_ = project.get_type(checked_expr.type_id(scope_id, project));

            let optional_struct_id = project.get_optional_struct_id(*span);
            let weakptr_struct_id = project.get_weakptr_struct_id(*span);

            let (type_id, err) = match type_ {
                Type::GenericInstance(struct_id, inner_type_ids)
                    if struct_id == &optional_struct_id || struct_id == &weakptr_struct_id =>
                {
                    (inner_type_ids[0], None)
                }
                _ => (
                    UNKNOWN_TYPE_ID,
                    err.or(Some(JaktError::TypecheckError(
                        "Forced unwrap only works on Optional".to_string(),
                        expr.span(),
                    ))),
                ),
            };
            error = error.or(err);

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::ForcedUnwrap(Box::new(checked_expr), *span, type_id),
                error,
            )
        }
        ParsedExpression::Boolean(b, span) => (CheckedExpression::Boolean(*b, *span), None),
        ParsedExpression::Call(call, span) => {
            let (checked_call, err) = typecheck_call(
                call,
                scope_id,
                span,
                project,
                None,
                None,
                safety_mode,
                type_hint,
                false,
            );
            error = error.or(err);

            let (type_id, err) = unify_with_type(checked_call.type_id, type_hint, *span, project);
            error = error.or(err);

            (CheckedExpression::Call(checked_call, *span, type_id), error)
        }
        ParsedExpression::NumericConstant(constant, span) => {
            // FIXME: Don't ignore type hint unification errors
            let (type_id, _) = unify_with_type(constant.type_id(), type_hint, *span, project);

            (
                CheckedExpression::NumericConstant(constant.clone(), *span, type_id),
                None,
            )
        }
        ParsedExpression::QuotedString(qs, span) => {
            let (_, err) = unify_with_type(STRING_TYPE_ID, type_hint, *span, project);

            (CheckedExpression::QuotedString(qs.clone(), *span), err)
        }
        ParsedExpression::ByteLiteral(b, span) => {
            let (_, err) = unify_with_type(U8_TYPE_ID, type_hint, *span, project);

            (CheckedExpression::ByteConstant(b.clone(), *span), err)
        }
        ParsedExpression::CharacterLiteral(c, span) => {
            let (_, err) = unify_with_type(CCHAR_TYPE_ID, type_hint, *span, project);

            (CheckedExpression::CharacterConstant(c.clone(), *span), err)
        }
        ParsedExpression::Var(v, span) => {
            if let Some(var) = project.find_var_in_scope(scope_id, v) {
                let (_, err) = unify_with_type(var.type_id, type_hint, *span, project);

                (CheckedExpression::Var(var, *span), err)
            } else if let Some(most_similar_var) =
                project.find_most_similar_var_name_in_scope(scope_id, v)
            {
                (
                    CheckedExpression::Var(
                        CheckedVariable {
                            name: v.clone(),
                            type_id: type_hint.unwrap_or(UNKNOWN_TYPE_ID),
                            type_span: None,
                            mutable: false,
                            visibility: Visibility::Public,
                            definition_span: *span,
                        },
                        *span,
                    ),
                    Some(JaktError::TypecheckErrorWithHint(
                        format!("variable '{}' not found", v),
                        *span,
                        format!("Did you mean '{}'?", most_similar_var),
                        *span,
                    )),
                )
            } else {
                (
                    CheckedExpression::Var(
                        CheckedVariable {
                            name: v.clone(),
                            type_id: type_hint.unwrap_or(UNKNOWN_TYPE_ID),
                            type_span: None,
                            mutable: false,
                            visibility: Visibility::Public,
                            definition_span: *span,
                        },
                        *span,
                    ),
                    Some(JaktError::TypecheckError(
                        format!("variable '{}' not found", v),
                        *span,
                    )),
                )
            }
        }
        ParsedExpression::NamespacedVar(v, ns, span) => {
            let scopes = ns.iter().fold(vec![Some(scope_id)], |mut scopes, ns| {
                let scope = scopes.last().unwrap().and_then(|scope_id|
                    // Could either be a namespace or an enum with an underlying type, prefer the namespace.
                    project
                        .find_namespace_in_scope(scope_id, ns)
                        .or_else(||
                            project
                                .find_enum_in_scope(scope_id, ns)
                                .map(|id| (project.get_enum(id).scope_id, false))
                        ));

                scopes.push(scope.map(|(scope, _)| scope));
                scopes
            });

            let scope = *scopes.last().unwrap();
            let checked_namespace = scopes
                .iter()
                .zip(ns.iter())
                .map(|(scope, ns)| CheckedNamespace {
                    name: Some(ns.clone()),
                    scope: scope.unwrap(),
                })
                .collect();

            match scope {
                Some(variable_scope_id) => {
                    if let Some(var) = project.find_var_in_scope(variable_scope_id, v) {
                        (
                            CheckedExpression::NamespacedVar(checked_namespace, var.clone(), *span),
                            check_accessibility(scope_id, variable_scope_id, var, span, project),
                        )
                    } else {
                        // Check if there's a constructor with this name.

                        let implicit_constructor_call = ParsedCall {
                            namespace: ns.clone(),
                            name: v.clone(),
                            args: Vec::new(),
                            type_args: Vec::new(),
                        };

                        let (checked_call, err) = typecheck_call(
                            &implicit_constructor_call,
                            scope_id,
                            span,
                            project,
                            None,
                            None,
                            safety_mode,
                            type_hint,
                            true,
                        );
                        error = error.or(err);

                        let (type_id, err) =
                            unify_with_type(checked_call.type_id, type_hint, *span, project);
                        error = error.or(err);

                        if error.is_none() {
                            (CheckedExpression::Call(checked_call, *span, type_id), error)
                        } else {
                            (
                                CheckedExpression::NamespacedVar(
                                    checked_namespace,
                                    CheckedVariable {
                                        name: v.clone(),
                                        type_id: type_hint.unwrap_or(UNKNOWN_TYPE_ID),
                                        type_span: None,
                                        mutable: false,
                                        visibility: Visibility::Public,
                                        definition_span: *span,
                                    },
                                    *span,
                                ),
                                Some(JaktError::TypecheckError(
                                    format!("variable '{}' not found", v),
                                    *span,
                                )),
                            )
                        }
                    }
                }
                None => (
                    CheckedExpression::NamespacedVar(
                        checked_namespace,
                        CheckedVariable {
                            name: v.clone(),
                            type_id: type_hint.unwrap_or(UNKNOWN_TYPE_ID),
                            type_span: None,
                            mutable: false,
                            visibility: Visibility::Public,
                            definition_span: *span,
                        },
                        *span,
                    ),
                    Some(JaktError::TypecheckError(
                        "namespace not found".to_string(),
                        *span,
                    )),
                ),
            }
        }
        ParsedExpression::Array(vec, fill_size_expr, span) => {
            let mut inner_type_id = UNKNOWN_TYPE_ID;
            let mut inner_type_span: Option<Span> = None;
            let mut output = Vec::new();

            let array_struct_id = project.get_array_struct_id(*span);
            let mut inner_hint = None;
            if let Some(hint) = type_hint {
                if let Type::GenericInstance(hint_struct_id, hint_inner_types) =
                    project.get_type(hint)
                {
                    if hint_struct_id == &array_struct_id {
                        inner_hint = Some(hint_inner_types[0]);
                    }
                }
            }

            let mut checked_fill_size_expr = None;
            if let Some(fill_size_expr) = fill_size_expr {
                let (checked_expr, err) =
                    typecheck_expression(fill_size_expr, scope_id, project, safety_mode, None);
                checked_fill_size_expr = Some(Box::new(checked_expr));
                error = error.or(err);
            }

            for v in vec {
                let (checked_expr, err) =
                    typecheck_expression(v, scope_id, project, safety_mode, inner_hint);
                error = error.or(err);

                let current_value_type_id = checked_expr.type_id(scope_id, project);

                if inner_type_id == UNKNOWN_TYPE_ID {
                    if current_value_type_id == VOID_TYPE_ID {
                        error = error.or(Some(JaktError::TypecheckError(
                            "cannot create an array with values of type void".to_string(),
                            v.span(),
                        )))
                    }

                    inner_type_id = current_value_type_id;
                    inner_type_span = Some(v.span());
                } else if inner_type_id != current_value_type_id {
                    let array_type_name = project.typename_for_type_id(inner_type_id);
                    error = error.or(Some(JaktError::TypecheckErrorWithHint(
                        format!(
                            "type '{}' does not match type '{}' of previous values in array",
                            project.typename_for_type_id(current_value_type_id),
                            array_type_name
                        ),
                        v.span(),
                        format!(
                            "array was inferred to store type '{}' here",
                            array_type_name
                        ),
                        inner_type_span.unwrap(),
                    )))
                }

                output.push(checked_expr);
            }

            if inner_type_id == UNKNOWN_TYPE_ID {
                if let Some(hint_inner_type) = inner_hint {
                    inner_type_id = hint_inner_type
                } else if type_hint == Some(UNKNOWN_TYPE_ID) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Cannot infer generic type for Array<T>".to_string(),
                        *span,
                    )))
                }
            }

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(array_struct_id, vec![inner_type_id]));

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::Array(output, checked_fill_size_expr, *span, type_id),
                error,
            )
        }
        ParsedExpression::Set(values, span) => {
            let mut inner_type_id = UNKNOWN_TYPE_ID;
            let mut inner_type_span: Option<Span> = None;
            let mut output = Vec::new();

            let set_struct_id = project.get_set_struct_id(*span);
            let mut inner_hint = None;
            if let Some(hint) = type_hint {
                if let Type::GenericInstance(hint_struct_id, hint_inner_types) =
                    project.get_type(hint)
                {
                    if hint_struct_id == &set_struct_id {
                        inner_hint = Some(hint_inner_types[0]);
                    }
                }
            }

            for value in values {
                let (checked_value, err) =
                    typecheck_expression(value, scope_id, project, safety_mode, inner_hint);
                error = error.or(err);

                let current_value_type_id = checked_value.type_id(scope_id, project);

                if inner_type_id == UNKNOWN_TYPE_ID {
                    if current_value_type_id == VOID_TYPE_ID {
                        error = error.or(Some(JaktError::TypecheckError(
                            "cannot create a set with values of type void".to_string(),
                            value.span(),
                        )))
                    }

                    inner_type_id = current_value_type_id;
                    inner_type_span = Some(value.span());
                } else if inner_type_id != current_value_type_id {
                    let set_type_name = project.typename_for_type_id(inner_type_id);
                    error = error.or(Some(JaktError::TypecheckErrorWithHint(
                        format!(
                            "type '{}' does not match type '{}' of previous values in set",
                            project.typename_for_type_id(current_value_type_id),
                            set_type_name
                        ),
                        value.span(),
                        format!("set was inferred to store type '{}' here", set_type_name),
                        inner_type_span.unwrap(),
                    )))
                }
                output.push(checked_value);
            }

            if inner_type_id == UNKNOWN_TYPE_ID {
                if let Some(hint_inner_type) = inner_hint {
                    inner_type_id = hint_inner_type
                } else if type_hint == Some(UNKNOWN_TYPE_ID) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Cannot infer generic type for Set<T>".to_string(),
                        *span,
                    )))
                }
            }

            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(set_struct_id, vec![inner_type_id]));

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (CheckedExpression::Set(output, *span, type_id), error)
        }
        ParsedExpression::Dictionary(kv_pairs, span) => {
            let mut key_type_id = UNKNOWN_TYPE_ID;
            let mut key_type_span: Option<Span> = None;
            let mut value_type_id = UNKNOWN_TYPE_ID;
            let mut value_type_span: Option<Span> = None;
            let mut output = Vec::new();

            let dictionary_struct_id = project.get_dictionary_struct_id(*span);
            let mut key_hint = None;
            let mut value_hint = None;
            if let Some(hint) = type_hint {
                if let Type::GenericInstance(hint_struct_id, hint_inner_types) =
                    project.get_type(hint)
                {
                    if hint_struct_id == &dictionary_struct_id {
                        key_hint = Some(hint_inner_types[0]);
                        value_hint = Some(hint_inner_types[1]);
                    }
                }
            }

            for (key, value) in kv_pairs {
                let (checked_key, err) =
                    typecheck_expression(key, scope_id, project, safety_mode, key_hint);
                error = error.or(err);

                let current_key_type_id = checked_key.type_id(scope_id, project);

                let (checked_value, err) =
                    typecheck_expression(value, scope_id, project, safety_mode, value_hint);
                error = error.or(err);

                let current_value_type_id = checked_value.type_id(scope_id, project);

                if (key_type_id, value_type_id) == (UNKNOWN_TYPE_ID, UNKNOWN_TYPE_ID) {
                    if current_key_type_id == VOID_TYPE_ID {
                        error = error.or(Some(JaktError::TypecheckError(
                            "cannot create a dictionary with keys of type void".to_string(),
                            key.span(),
                        )))
                    }

                    if current_value_type_id == VOID_TYPE_ID {
                        error = error.or(Some(JaktError::TypecheckError(
                            "cannot create a dictionary with values of type void".to_string(),
                            value.span(),
                        )))
                    }

                    key_type_id = current_key_type_id;
                    key_type_span = Some(key.span());
                    value_type_id = current_value_type_id;
                    value_type_span = Some(value.span());
                } else {
                    if key_type_id != current_key_type_id {
                        let key_type_name = project.typename_for_type_id(key_type_id);
                        error = error.or(Some(JaktError::TypecheckErrorWithHint(
                            format!(
                                "type '{}' does not match type '{}' of previous keys in dictionary",
                                project.typename_for_type_id(current_key_type_id),
                                key_type_name
                            ),
                            key.span(),
                            format!(
                                "dictionary was inferred to store keys of type '{}' here",
                                key_type_name
                            ),
                            key_type_span.unwrap(),
                        )))
                    }

                    if value_type_id != current_value_type_id {
                        let value_type_name = project.typename_for_type_id(value_type_id);
                        error = error.or(Some(JaktError::TypecheckErrorWithHint(
                            format!("type '{}' does not match type '{}' of previous values in dictionary", project.typename_for_type_id(current_value_type_id), value_type_name),
                            value.span(),
                            format!("dictionary was inferred to store values of type '{}' here", value_type_name),
                            value_type_span.unwrap(),
                        )))
                    }
                }

                output.push((checked_key, checked_value));
            }

            if key_type_id == UNKNOWN_TYPE_ID {
                if let Some(key_hint) = key_hint {
                    key_type_id = key_hint;
                } else if type_hint == Some(UNKNOWN_TYPE_ID) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Cannot infer key type for Dictionary<K, V>".to_string(),
                        *span,
                    )))
                }
            }

            if value_type_id == UNKNOWN_TYPE_ID {
                if let Some(value_hint) = value_hint {
                    value_type_id = value_hint;
                } else if type_hint == Some(UNKNOWN_TYPE_ID) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "Cannot infer value type for Dictionary".to_string(),
                        *span,
                    )))
                }
            }

            let type_id = project.find_or_add_type_id(Type::GenericInstance(
                dictionary_struct_id,
                vec![key_type_id, value_type_id],
            ));

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (CheckedExpression::Dictionary(output, *span, type_id), error)
        }
        ParsedExpression::Tuple(items, span) => {
            let mut checked_items = Vec::new();
            let mut checked_types = Vec::new();

            for item in items {
                let (checked_item, err) =
                    typecheck_expression(item, scope_id, project, safety_mode, None);
                error = error.or(err);

                if checked_item.type_id(scope_id, project) == VOID_TYPE_ID {
                    error = error.or(Some(JaktError::TypecheckError(
                        "cannot create a tuple that contains a value of type void".to_string(),
                        item.span(),
                    )))
                }

                checked_types.push(checked_item.type_id(scope_id, project));
                checked_items.push(checked_item);
            }

            let tuple_struct_id = project.get_tuple_struct_id(*span);
            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(tuple_struct_id, checked_types));

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::Tuple(checked_items, *span, type_id),
                error,
            )
        }
        ParsedExpression::IndexedExpression(expr, idx, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let (checked_idx, err) =
                typecheck_expression(idx, scope_id, project, safety_mode, None);
            error = error.or(err);

            let mut expr_type_id = UNKNOWN_TYPE_ID;

            let array_struct_id = project.get_array_struct_id(*span);
            let dict_struct_id = project.get_dictionary_struct_id(*span);

            let type_ = project.get_type(checked_expr.type_id(scope_id, project));

            match type_ {
                Type::GenericInstance(parent_struct_id, inner_type_ids)
                    if parent_struct_id == &array_struct_id =>
                {
                    match checked_idx.type_id(scope_id, project) {
                        _ if is_integer(checked_idx.type_id(scope_id, project)) => {
                            expr_type_id = inner_type_ids[0];
                        }

                        _ => {
                            error = error.or(Some(JaktError::TypecheckError(
                                "index is not an integer".to_string(),
                                idx.span(),
                            )))
                        }
                    }

                    let (expr_type_id, err) =
                        unify_with_type(expr_type_id, type_hint, *span, project);
                    error = error.or(err);

                    (
                        CheckedExpression::IndexedExpression(
                            Box::new(checked_expr),
                            Box::new(checked_idx),
                            *span,
                            expr_type_id,
                        ),
                        error,
                    )
                }
                Type::GenericInstance(parent_struct_id, inner_type_ids)
                    if parent_struct_id == &dict_struct_id =>
                {
                    expr_type_id = inner_type_ids[1];

                    let (expr_type_id, err) =
                        unify_with_type(expr_type_id, type_hint, *span, project);
                    error = error.or(err);

                    (
                        CheckedExpression::IndexedDictionary(
                            Box::new(checked_expr),
                            Box::new(checked_idx),
                            *span,
                            expr_type_id,
                        ),
                        error,
                    )
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "index used on value that can't be indexed".to_string(),
                        expr.span(),
                    )));

                    let (expr_type_id, err) =
                        unify_with_type(expr_type_id, type_hint, *span, project);
                    error = error.or(err);

                    (
                        CheckedExpression::IndexedExpression(
                            Box::new(checked_expr),
                            Box::new(checked_idx),
                            *span,
                            expr_type_id,
                        ),
                        error,
                    )
                }
            }
        }
        ParsedExpression::IndexedTuple(expr, idx, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let mut type_id = UNKNOWN_TYPE_ID;

            let tuple_struct_id = project.get_tuple_struct_id(*span);
            let checked_expr_type_id = project.get_type(checked_expr.type_id(scope_id, project));
            match checked_expr_type_id {
                Type::GenericInstance(parent_struct_id, inner_type_ids)
                    if parent_struct_id == &tuple_struct_id =>
                {
                    match inner_type_ids.get(*idx) {
                        Some(t) => type_id = *t,
                        None => {
                            error = error.or(Some(JaktError::TypecheckError(
                                "tuple index past the end of the tuple".to_string(),
                                *span,
                            )))
                        }
                    }
                }
                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        "tuple index used non-tuple value".to_string(),
                        expr.span(),
                    )))
                }
            }

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::IndexedTuple(Box::new(checked_expr), *idx, *span, type_id),
                error,
            )
        }
        ParsedExpression::Match(expr, cases, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let mut checked_cases = Vec::new();
            let type_ = project.get_type(checked_expr.type_id(scope_id, project));
            let subject_type_id = checked_expr.type_id(scope_id, project);
            let mut generic_parameters = match type_ {
                Type::GenericEnumInstance(enum_id, inner_type_ids) => {
                    let enum_ = project.get_enum(*enum_id);
                    enum_
                        .generic_parameters
                        .iter()
                        .zip(inner_type_ids.iter())
                        .fold(HashMap::new(), |mut acc, (param, type_id)| {
                            acc.insert(*param, *type_id);
                            acc
                        })
                }
                _ => HashMap::new(),
            };
            let mut final_result_type: Option<TypeId> = None;
            let mut all_variants_are_constants = true;

            match type_ {
                Type::Enum(enum_id) | Type::GenericEnumInstance(enum_id, _) => {
                    let enum_ = project.get_enum(*enum_id);
                    let enum_name = enum_.name.clone();
                    let enum_id = *enum_id;
                    let mut seen_catch_all = false;
                    let mut catch_all_span = None;
                    let mut covered_variants = HashSet::new();
                    for case in cases {
                        match &case {
                            MatchCase::CatchAll { body, marker_span } => {
                                if seen_catch_all {
                                    error = error.or(Some(JaktError::TypecheckError(
                                        "multiple catch-all cases in match are not allowed"
                                            .to_string(),
                                        *marker_span,
                                    )));
                                } else {
                                    catch_all_span = Some(*marker_span);
                                    seen_catch_all = true;
                                }

                                let (body, err) = typecheck_match_body(
                                    body,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    &mut generic_parameters,
                                    &mut final_result_type,
                                    *marker_span,
                                );
                                error = error.or(err);

                                checked_cases.push(CheckedMatchCase::CatchAll {
                                    body,
                                    marker_span: *marker_span,
                                });
                            }
                            MatchCase::Expression {
                                matched_expression,
                                body,
                                marker_span,
                            } => {
                                let (checked_expr, err) = typecheck_expression(
                                    matched_expression,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    Some(subject_type_id),
                                );
                                error = error.or(err);
                                if checked_expr.to_number_constant().is_none() {
                                    all_variants_are_constants = false;
                                }

                                // FIXME: In the future, we should really make this a "does it satisfy some trait" check.
                                //        For now, we just check that the types are equal.
                                if let Some(err) = check_types_for_compat(
                                    checked_expr.type_id(scope_id, project),
                                    subject_type_id,
                                    &mut generic_parameters,
                                    *marker_span,
                                    project,
                                ) {
                                    error = error.or(Some(err));
                                }

                                let (body, err) = typecheck_match_body(
                                    body,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    &mut generic_parameters,
                                    &mut final_result_type,
                                    *marker_span,
                                );
                                error = error.or(err);

                                checked_cases.push(CheckedMatchCase::Expression {
                                    body,
                                    expression: Box::new(checked_expr),
                                    marker_span: *marker_span,
                                });
                            }
                            MatchCase::EnumVariant {
                                variant_name: name,
                                variant_arguments: args,
                                arguments_span: arg_span,
                                body,
                                marker_span,
                            } => {
                                let mut name = name.clone();
                                if name.len() == 1 {
                                    name.insert(0, (enum_name.clone(), name[0].1));
                                }

                                if name.is_empty() {
                                    continue;
                                }

                                if name[0].0 != enum_name {
                                    error = error.or(Some(JaktError::TypecheckError(
                                        format!(
                                            "match case '{}' does not match enum '{}'",
                                            name[0].0, enum_name
                                        ),
                                        name[0].1,
                                    )));
                                    continue;
                                }

                                let variant_index: usize;
                                let mut vars = Vec::new();
                                let enum_ = project.get_enum(enum_id);
                                let constructor_name = &name[1].0;
                                let variant = (*enum_).variants.iter().find(|v| match v {
                                    CheckedEnumVariant::WithValue(name, _, _)
                                    | CheckedEnumVariant::Untyped(name, _)
                                    | CheckedEnumVariant::Typed(name, _, _)
                                    | CheckedEnumVariant::StructLike(name, _, _)
                                        if name == constructor_name =>
                                    {
                                        true
                                    }

                                    _ => false,
                                });
                                match variant {
                                    None => {
                                        error = error.or(Some(JaktError::TypecheckError(
                                            format!(
                                                "match case '{}' does not match enum '{}'",
                                                name[0].0, enum_name
                                            ),
                                            name[1].1,
                                        )));
                                        return (
                                            CheckedExpression::Match(
                                                Box::new(checked_expr),
                                                checked_cases,
                                                *span,
                                                // FIXME: Figure this out.
                                                UNKNOWN_TYPE_ID,
                                                false,
                                            ),
                                            error,
                                        );
                                    }
                                    Some(variant) => {
                                        match variant {
                                            CheckedEnumVariant::Untyped(name, _) => {
                                                covered_variants.insert(name.clone());
                                                if !args.is_empty() {
                                                    error =
                                                        error.or(Some(JaktError::TypecheckError(
                                                            format!(
                                                            "match case '{}' cannot have arguments",
                                                            name
                                                        ),
                                                            *arg_span,
                                                        )));
                                                }
                                            }
                                            CheckedEnumVariant::Typed(name, type_id, span) => {
                                                covered_variants.insert(name.clone());
                                                if !args.is_empty() {
                                                    if args.len() != 1 {
                                                        error = error.or(Some(JaktError::TypecheckError(
                                                            format!(
                                                                "match case '{}' must have exactly one argument",
                                                                name
                                                            ),
                                                            *arg_span,
                                                        )));
                                                    }
                                                    let span = *span;

                                                    let type_id = substitute_typevars_in_type(
                                                        *type_id,
                                                        &generic_parameters,
                                                        project,
                                                    );
                                                    if project.dump_type_hints {
                                                        println!(
                                                            "{{\"type\": \"hint\", \"file_id\": {}, \"position\": {}, \"typename\": \"{}\" }}",
                                                            args[0].2.file_id,
                                                            args[0].2.end,
                                                            project.typename_for_type_id(type_id)
                                                        );
                                                    }
                                                    vars.push((
                                                        CheckedVariable {
                                                            name: args[0].1.clone(),
                                                            type_id,
                                                            type_span: None,
                                                            mutable: false,
                                                            visibility: Visibility::Public,
                                                            definition_span: span,
                                                        },
                                                        span,
                                                    ));
                                                }
                                            }
                                            CheckedEnumVariant::WithValue(name, _, _) => {
                                                covered_variants.insert(name.clone());
                                                if !args.is_empty() {
                                                    error =
                                                        error.or(Some(JaktError::TypecheckError(
                                                            format!(
                                                            "match case '{}' cannot have arguments",
                                                            name
                                                        ),
                                                            *arg_span,
                                                        )));
                                                }
                                            }
                                            CheckedEnumVariant::StructLike(
                                                variant_name,
                                                fields,
                                                _,
                                            ) => {
                                                covered_variants.insert(variant_name.clone());
                                                // Make the borrow checker shut up
                                                let variant_name = variant_name.clone();
                                                let fields = fields.clone();

                                                let mut names_seen = HashMap::new();
                                                for arg in args {
                                                    let name = &arg.0;
                                                    if name.is_none()
                                                        && !fields
                                                            .iter()
                                                            .any(|field| field.name == arg.1)
                                                    {
                                                        error = error.or(Some(JaktError::TypecheckError(
                                                            format!("match case argument '{}' for struct-like enum variant cannot be anon", arg.1),
                                                            *arg_span,
                                                        )));
                                                        continue;
                                                    }
                                                    let name =
                                                        name.as_ref().unwrap_or(&arg.1).clone();
                                                    if names_seen.contains_key(&name) {
                                                        error = error.or(Some(JaktError::TypecheckError(
                                                            format!(
                                                                "match case argument '{}' is already defined",
                                                                name
                                                            ),
                                                            *arg_span,
                                                        )));
                                                        continue;
                                                    }

                                                    names_seen.insert(name.clone(), ());
                                                    let field_data = fields
                                                        .iter()
                                                        .find(|f| f.name == name)
                                                        .map(|f| (f.type_id, f.span));

                                                    let field_data =
                                                        if let Some((field_data, field_span)) =
                                                            field_data
                                                        {
                                                            Some((
                                                                substitute_typevars_in_type(
                                                                    field_data,
                                                                    &generic_parameters,
                                                                    project,
                                                                ),
                                                                field_span,
                                                            ))
                                                        } else {
                                                            field_data
                                                        };

                                                    match field_data {
                                                        Some((type_id, span)) => {
                                                            if project.dump_type_hints {
                                                                println!(
                                                                    "{{\"type\": \"hint\", \"file_id\": {}, \"position\": {}, \"typename\": \"{}\" }}",
                                                                    arg.2.file_id,
                                                                    arg.2.end,
                                                                    project.typename_for_type_id(type_id)
                                                                );
                                                            }

                                                            vars.push((
                                                                CheckedVariable {
                                                                    name: arg.1.clone(),
                                                                    type_id,
                                                                    type_span: None,
                                                                    mutable: false,
                                                                    visibility: Visibility::Public,
                                                                    definition_span: span,
                                                                },
                                                                span,
                                                            ))
                                                        }
                                                        None => {
                                                            error = error.or(Some(JaktError::TypecheckError(
                                                                format!("match case argument '{}' does not exist in struct-like enum variant '{}'", name, variant_name),
                                                                *arg_span,
                                                            )));
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        // Look these up again to appease the borrow checker
                                        let enum_ = project.get_enum(enum_id);
                                        let variant = (*enum_)
                                            .variants
                                            .iter()
                                            .find(|v| {
                                                matches!(v,
                                                        CheckedEnumVariant::WithValue(name, ..)
                                                        | CheckedEnumVariant::Untyped(name, _)
                                                        | CheckedEnumVariant::Typed(name, ..)
                                                        | CheckedEnumVariant::StructLike(name, ..)
                                                    if name == constructor_name)
                                            })
                                            .unwrap();
                                        variant_index = enum_
                                            .variants
                                            .iter()
                                            .position(|p| std::ptr::eq(p, variant))
                                            .unwrap();
                                    }
                                };

                                let parent_throws = project.get_scope(scope_id).throws;
                                let new_scope_id = project.create_scope(scope_id, parent_throws);
                                for (var, span) in vars {
                                    let err =
                                        project.add_var_to_scope(new_scope_id, var, span).err();
                                    error = error.or(err);
                                }

                                let (checked_body, err) = typecheck_match_body(
                                    body,
                                    new_scope_id,
                                    project,
                                    safety_mode,
                                    &mut generic_parameters,
                                    &mut final_result_type,
                                    *marker_span,
                                );
                                error = error.or(err);
                                checked_cases.push(CheckedMatchCase::EnumVariant {
                                    variant_name: name[1].0.clone(),
                                    variant_arguments: (*args).clone(),
                                    subject_type_id,
                                    variant_index,
                                    scope_id: new_scope_id,
                                    body: checked_body,
                                    marker_span: *marker_span,
                                });
                            }
                        }
                    }

                    // Check if all the variants are matched
                    let enum_ = project.get_enum(enum_id);
                    let missing_variants = enum_
                        .variants
                        .iter()
                        .map(|v| match v {
                            CheckedEnumVariant::WithValue(name, ..)
                            | CheckedEnumVariant::Untyped(name, ..)
                            | CheckedEnumVariant::Typed(name, ..)
                            | CheckedEnumVariant::StructLike(name, ..) => name.as_str(),
                        })
                        .filter(|name| !covered_variants.contains(*name))
                        .collect::<Vec<_>>();

                    match (missing_variants.is_empty(), seen_catch_all) {
                        (false, false) => {
                            error = error.or(Some(JaktError::TypecheckErrorWithHint(
                                format!(
                                    "match expression is not exhaustive, missing variants are: {}",
                                    missing_variants.join(", ")
                                ),
                                *span,
                                "add an irrefutable 'else' pattern or handle the missing variants"
                                    .to_string(),
                                expr.span(),
                            )));
                        }
                        (true, true) => {
                            error = error.or(Some(JaktError::TypecheckErrorWithHint(
                                "all variants are covered, but an irrefutable pattern is also present".to_string(),
                                *span,
                                "remove this pattern".to_string(),
                                catch_all_span.unwrap(),
                            )));
                        }
                        _ => {}
                    }
                }
                _ => {
                    let mut is_enum_match = false;
                    let mut is_value_match = false;
                    let mut seen_catch_all = false;
                    for case in cases {
                        match case {
                            MatchCase::EnumVariant {
                                marker_span,
                                body,
                                variant_name,
                                variant_arguments,
                                ..
                            } => {
                                if is_value_match {
                                    error = error.or(Some(JaktError::TypecheckError(
                                        "Cannot have an enum match case in a match expression containing value matches".to_string(),
                                        *marker_span,
                                    )));
                                }
                                is_enum_match = true;

                                // We don't know what the enum type is, but we have the type var for it, so generate a generic enum match.
                                // note that this will be fully checked when this match expression is actually instantiated.

                                let (body, err) = typecheck_match_body(
                                    body,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    &mut generic_parameters,
                                    &mut final_result_type,
                                    *marker_span,
                                );
                                error = error.or(err);

                                if let Some(type_id) = final_result_type {
                                    if type_id == UNKNOWN_TYPE_ID {
                                        final_result_type = None;
                                    }
                                }

                                if !variant_name.is_empty() {
                                    checked_cases.push(CheckedMatchCase::EnumVariant {
                                        variant_name: variant_name.last().unwrap().0.clone(),
                                        subject_type_id,
                                        variant_arguments: variant_arguments.clone(),
                                        variant_index: 0,
                                        scope_id,
                                        body,
                                        marker_span: *marker_span,
                                    });
                                }
                            }
                            MatchCase::CatchAll { body, marker_span } => {
                                if seen_catch_all {
                                    error = error.or(Some(JaktError::TypecheckError(
                                        "Cannot have multiple catch-all match cases".to_string(),
                                        *marker_span,
                                    )));
                                } else {
                                    seen_catch_all = true;
                                }

                                let (body, err) = typecheck_match_body(
                                    body,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    &mut generic_parameters,
                                    &mut final_result_type,
                                    *marker_span,
                                );
                                error = error.or(err);
                                checked_cases.push(CheckedMatchCase::CatchAll {
                                    body,
                                    marker_span: *marker_span,
                                });
                            }
                            MatchCase::Expression {
                                matched_expression,
                                body,
                                marker_span,
                            } => {
                                if is_enum_match {
                                    error = error.or(Some(JaktError::TypecheckError(
                                        "Cannot have a value match case in a match expression containing enum matches".to_string(),
                                        *marker_span,
                                    )));
                                    continue;
                                }
                                is_value_match = true;
                                let (checked_expr, err) = typecheck_expression(
                                    matched_expression,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    Some(subject_type_id),
                                );
                                error = error.or(err);
                                if checked_expr.to_number_constant().is_none() {
                                    all_variants_are_constants = false;
                                }

                                // FIXME: In the future, we should really make this a "does it satisfy some trait" check.
                                //        For now, we just check that the types are equal.
                                if let Some(err) = check_types_for_compat(
                                    checked_expr.type_id(scope_id, project),
                                    subject_type_id,
                                    &mut generic_parameters,
                                    *marker_span,
                                    project,
                                ) {
                                    error = error.or(Some(err));
                                }

                                let (body, err) = typecheck_match_body(
                                    body,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    &mut generic_parameters,
                                    &mut final_result_type,
                                    *marker_span,
                                );
                                error = error.or(err);

                                checked_cases.push(CheckedMatchCase::Expression {
                                    body,
                                    expression: Box::new(checked_expr),
                                    marker_span: *marker_span,
                                });
                            }
                        }
                    }

                    if is_value_match && !seen_catch_all {
                        error = error.or(Some(JaktError::TypecheckError(
                            "match expression is not exhaustive, a value match must contain an irrefutable 'else' pattern".to_string(),
                            *span,
                        )));
                    }
                }
            }

            let mut err: Option<JaktError> = None;
            final_result_type = final_result_type.map(|p| {
                let (ty, unification_error) = unify_with_type(p, type_hint, *span, project);
                err = unification_error;
                ty
            });
            error = error.or(err);

            (
                CheckedExpression::Match(
                    Box::new(checked_expr),
                    checked_cases,
                    *span,
                    final_result_type.unwrap_or(VOID_TYPE_ID),
                    all_variants_are_constants,
                ),
                error,
            )
        }
        ParsedExpression::IndexedStruct(expr, name, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            let type_id = UNKNOWN_TYPE_ID;

            let checked_expr_type_id = checked_expr.type_id(scope_id, project);
            let checked_expr_type = project.get_type(checked_expr_type_id);
            match checked_expr_type {
                Type::GenericInstance(struct_id, _) | Type::Struct(struct_id) => {
                    let structure = project.get_struct(*struct_id);

                    for member in &structure.fields {
                        if &member.name == name {
                            let struct_id = *struct_id;
                            let member = member.clone();
                            let resolved_type_id =
                                resolve_type_var(member.type_id, scope_id, project);
                            let (unified_type, _) =
                                unify_with_type(resolved_type_id, type_hint, *span, project);

                            let structure = project.get_struct(struct_id);
                            return (
                                CheckedExpression::IndexedStruct(
                                    Box::new(checked_expr),
                                    name.to_string(),
                                    *span,
                                    unified_type,
                                ),
                                check_accessibility(
                                    scope_id,
                                    structure.scope_id,
                                    member,
                                    span,
                                    project,
                                ),
                            );
                        }
                    }

                    error = error.or(Some(JaktError::TypecheckError(
                        format!("unknown member of struct: {}.{}", structure.name, name),
                        *span,
                    )));
                }

                _ => {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!(
                            "Member field access on value of non-struct type ‘{}’",
                            project.typename_for_type_id(checked_expr_type_id)
                        ),
                        *span,
                    )));
                }
            }

            let (type_id, err) = unify_with_type(type_id, type_hint, *span, project);
            error = error.or(err);

            (
                CheckedExpression::IndexedStruct(
                    Box::new(checked_expr),
                    name.to_string(),
                    *span,
                    type_id,
                ),
                error,
            )
        }
        ParsedExpression::MethodCall(expr, call, span) => {
            let (checked_expr, err) =
                typecheck_expression(expr, scope_id, project, safety_mode, None);
            error = error.or(err);

            if checked_expr.type_id(scope_id, project) == STRING_TYPE_ID {
                // Special-case the built-in so we don't accidentally find the user's definition
                let string_struct = project.find_struct_in_prelude("String");

                let (checked_call, err) = typecheck_call(
                    call,
                    scope_id,
                    span,
                    project,
                    Some(&checked_expr),
                    Some(StructOrEnumId::Struct(string_struct)),
                    safety_mode,
                    type_hint,
                    false,
                );
                error = error.or(err);

                let (type_id, err) =
                    unify_with_type(checked_call.type_id, type_hint, *span, project);
                error = error.or(err);

                (
                    CheckedExpression::MethodCall(
                        Box::new(checked_expr),
                        checked_call,
                        *span,
                        type_id,
                    ),
                    error,
                )
            } else {
                let checked_expr_type = project.get_type(checked_expr.type_id(scope_id, project));
                match checked_expr_type {
                    Type::Struct(id) => {
                        let id = StructOrEnumId::Struct(*id);
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(id),
                            safety_mode,
                            type_hint,
                            false,
                        );
                        error = error.or(err);

                        let (type_id, err) =
                            unify_with_type(checked_call.type_id, type_hint, *span, project);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                type_id,
                            ),
                            error,
                        )
                    }
                    Type::Enum(id) => {
                        let id = StructOrEnumId::Enum(*id);
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(id),
                            safety_mode,
                            type_hint,
                            false,
                        );
                        error = error.or(err);

                        let (type_id, err) =
                            unify_with_type(checked_call.type_id, type_hint, *span, project);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                type_id,
                            ),
                            error,
                        )
                    }
                    Type::GenericInstance(id, _) => {
                        let id = StructOrEnumId::Struct(*id);
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(id),
                            safety_mode,
                            type_hint,
                            false,
                        );
                        error = error.or(err);

                        let (type_id, err) =
                            unify_with_type(checked_call.type_id, type_hint, *span, project);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                type_id,
                            ),
                            error,
                        )
                    }
                    Type::GenericEnumInstance(id, _) => {
                        // ignore the inner types for now, but we'll need them in the future
                        let id = StructOrEnumId::Enum(*id);
                        let (checked_call, err) = typecheck_call(
                            call,
                            scope_id,
                            span,
                            project,
                            Some(&checked_expr),
                            Some(id),
                            safety_mode,
                            type_hint,
                            false,
                        );
                        error = error.or(err);

                        let (type_id, err) =
                            unify_with_type(checked_call.type_id, type_hint, *span, project);
                        error = error.or(err);

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                checked_call,
                                *span,
                                type_id,
                            ),
                            error,
                        )
                    }
                    _ => {
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "no methods available on value (type: {})",
                                project
                                    .typename_for_type_id(checked_expr.type_id(scope_id, project))
                            ),
                            expr.span(),
                        )));

                        // Generate something usable, in case we're generating generic code.
                        let checked_args = call
                            .args
                            .iter()
                            .map(|arg| {
                                let (checked_arg, err) = typecheck_expression(
                                    &arg.1,
                                    scope_id,
                                    project,
                                    safety_mode,
                                    None,
                                );
                                if let Some(err) = err {
                                    error = Some(err);
                                }

                                (arg.0.clone(), checked_arg)
                            })
                            .collect();

                        (
                            CheckedExpression::MethodCall(
                                Box::new(checked_expr),
                                CheckedCall {
                                    name: call.name.to_string(),
                                    args: checked_args,
                                    function_id: None,
                                    type_id: UNKNOWN_TYPE_ID,
                                    callee_throws: false,
                                    linkage: FunctionLinkage::Internal,
                                    namespace: vec![],
                                    type_args: vec![],
                                },
                                *span,
                                UNKNOWN_TYPE_ID,
                            ),
                            error,
                        )
                    }
                }
            }
        }

        ParsedExpression::Operator(_, span) => (
            CheckedExpression::Garbage(*span),
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
        ParsedExpression::Garbage(span) => (
            CheckedExpression::Garbage(*span),
            Some(JaktError::TypecheckError(
                "garbage in expression".to_string(),
                *span,
            )),
        ),
    }
}

pub fn typecheck_unary_operation(
    expr: CheckedExpression,
    op: CheckedUnaryOperator,
    span: Span,
    scope_id: ScopeId,
    project: &mut Project,
    safety_mode: SafetyMode,
) -> (CheckedExpression, Option<JaktError>) {
    let expr_type_id = expr.type_id(scope_id, project);
    let expr_type = project.get_type(expr_type_id);

    match &op {
        CheckedUnaryOperator::Is(type_id) => (
            CheckedExpression::UnaryOp(
                Box::new(expr),
                CheckedUnaryOperator::Is(*type_id),
                span,
                BOOL_TYPE_ID,
            ),
            None,
        ),
        CheckedUnaryOperator::IsEnumVariant(name) => (
            CheckedExpression::UnaryOp(
                Box::new(expr),
                CheckedUnaryOperator::IsEnumVariant(name.clone()),
                span,
                BOOL_TYPE_ID,
            ),
            None,
        ),
        CheckedUnaryOperator::TypeCast(cast) => (
            CheckedExpression::UnaryOp(
                Box::new(expr),
                op.clone(),
                span,
                cast.type_id(scope_id, project),
            ),
            None,
        ),
        CheckedUnaryOperator::Dereference => match expr_type {
            Type::RawPtr(x) => {
                if safety_mode == SafetyMode::Unsafe {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, *x),
                        None,
                    )
                } else {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, *x),
                        Some(JaktError::TypecheckError(
                            "dereference of raw pointer outside of unsafe block".to_string(),
                            span,
                        )),
                    )
                }
            }
            _ => (
                CheckedExpression::UnaryOp(Box::new(expr), op, span, UNKNOWN_TYPE_ID),
                Some(JaktError::TypecheckError(
                    "dereference of a non-pointer value".to_string(),
                    span,
                )),
            ),
        },
        CheckedUnaryOperator::RawAddress => {
            let type_id = expr.type_id(scope_id, project);

            let type_id = project.find_or_add_type_id(Type::RawPtr(type_id));
            (
                CheckedExpression::UnaryOp(Box::new(expr), op, span, type_id),
                None,
            )
        }
        CheckedUnaryOperator::LogicalNot => {
            let type_id = expr.type_id(scope_id, project);
            (
                CheckedExpression::UnaryOp(
                    Box::new(expr),
                    CheckedUnaryOperator::LogicalNot,
                    span,
                    type_id,
                ),
                None,
            )
        }
        CheckedUnaryOperator::BitwiseNot => {
            let type_id = expr.type_id(scope_id, project);
            (
                CheckedExpression::UnaryOp(
                    Box::new(expr),
                    CheckedUnaryOperator::BitwiseNot,
                    span,
                    type_id,
                ),
                None,
            )
        }
        CheckedUnaryOperator::Negate => {
            let type_id = expr.type_id(scope_id, project);

            match type_id {
                crate::compiler::I8_TYPE_ID
                | crate::compiler::I16_TYPE_ID
                | crate::compiler::I32_TYPE_ID
                | crate::compiler::I64_TYPE_ID
                | crate::compiler::U8_TYPE_ID
                | crate::compiler::U16_TYPE_ID
                | crate::compiler::U32_TYPE_ID
                | crate::compiler::U64_TYPE_ID
                | crate::compiler::F32_TYPE_ID
                | crate::compiler::F64_TYPE_ID
                | crate::compiler::CINT_TYPE_ID => {
                    // FIXME: This at least allows us to check out-of-bounds constants at compile time.
                    //        We should expand it to check any compile-time known value.
                    if let CheckedExpression::NumericConstant(ref number, span, type_id) = expr {
                        // Flipping the sign on a small enough unsigned constant is fine. We'll change the type to the signed variant.
                        if is_integer(type_id) && !is_signed(type_id) {
                            // FIXME: What about integer types whose signedness we can't yet flip?
                            let flipped_sign_type = flip_signedness(type_id).unwrap();
                            let negated_value = -i128::from(number.number_constant().unwrap());
                            if !can_fit_number(
                                flipped_sign_type,
                                &NumberConstant::Signed(negated_value as i64),
                            )
                                // This is the case if the above "as i64" overflows.
                                || negated_value < i64::MIN.into()
                            {
                                (
                                    CheckedExpression::Garbage(span),
                                    Some(JaktError::TypecheckError(
                                        // FIXME: Print this more nicely
                                        format!(
                                            "Literal {:?} too small for unsigned integer type {}",
                                            number.number_constant().unwrap(),
                                            project.typename_for_type_id(type_id)
                                        ),
                                        span,
                                    )),
                                )
                            } else {
                                (
                                    CheckedExpression::NumericConstant(
                                        match flipped_sign_type {
                                            I8_TYPE_ID => NumericConstant::I8(negated_value as i8),
                                            I16_TYPE_ID => {
                                                NumericConstant::I16(negated_value as i16)
                                            }
                                            I32_TYPE_ID => {
                                                NumericConstant::I32(negated_value as i32)
                                            }
                                            I64_TYPE_ID => {
                                                NumericConstant::I64(negated_value as i64)
                                            }
                                            U8_TYPE_ID => NumericConstant::U8(negated_value as u8),
                                            U16_TYPE_ID => {
                                                NumericConstant::U16(negated_value as u16)
                                            }
                                            U32_TYPE_ID => {
                                                NumericConstant::U32(negated_value as u32)
                                            }
                                            U64_TYPE_ID => {
                                                NumericConstant::U64(negated_value as u64)
                                            }
                                            _ => unreachable!(),
                                        },
                                        span,
                                        flipped_sign_type,
                                    ),
                                    None,
                                )
                            }
                        } else {
                            (
                                CheckedExpression::UnaryOp(
                                    Box::new(expr),
                                    CheckedUnaryOperator::Negate,
                                    span,
                                    type_id,
                                ),
                                None,
                            )
                        }
                    } else {
                        (
                            CheckedExpression::UnaryOp(
                                Box::new(expr),
                                CheckedUnaryOperator::Negate,
                                span,
                                type_id,
                            ),
                            None,
                        )
                    }
                }
                _ => (
                    CheckedExpression::UnaryOp(
                        Box::new(expr),
                        CheckedUnaryOperator::Negate,
                        span,
                        type_id,
                    ),
                    Some(JaktError::TypecheckError(
                        "negate on non-numeric value".to_string(),
                        span,
                    )),
                ),
            }
        }
        CheckedUnaryOperator::PostDecrement
        | CheckedUnaryOperator::PostIncrement
        | CheckedUnaryOperator::PreDecrement
        | CheckedUnaryOperator::PreIncrement => match expr.type_id(scope_id, project) {
            crate::compiler::I8_TYPE_ID
            | crate::compiler::I16_TYPE_ID
            | crate::compiler::I32_TYPE_ID
            | crate::compiler::I64_TYPE_ID
            | crate::compiler::U8_TYPE_ID
            | crate::compiler::U16_TYPE_ID
            | crate::compiler::U32_TYPE_ID
            | crate::compiler::U64_TYPE_ID
            | crate::compiler::F32_TYPE_ID
            | crate::compiler::F64_TYPE_ID
            | crate::compiler::USIZE_TYPE_ID
            | crate::compiler::CCHAR_TYPE_ID
            | crate::compiler::CINT_TYPE_ID => {
                if !expr.is_mutable() {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, expr_type_id),
                        Some(JaktError::TypecheckError(
                            "Increment/decrement of immutable variable".to_string(),
                            span,
                        )),
                    )
                } else {
                    (
                        CheckedExpression::UnaryOp(Box::new(expr), op, span, expr_type_id),
                        None,
                    )
                }
            }
            _ => (
                CheckedExpression::UnaryOp(Box::new(expr), op, span, expr_type_id),
                Some(JaktError::TypecheckError(
                    "unary operation on non-numeric value".to_string(),
                    span,
                )),
            ),
        },
    }
}

fn unify_with_type(
    found_type: TypeId,
    expected_type: Option<TypeId>,
    span: Span,
    project: &mut Project,
) -> (TypeId, Option<JaktError>) {
    if let Some(hint) = expected_type {
        if hint == UNKNOWN_TYPE_ID {
            return (found_type, None);
        }

        let mut generic_interface = HashMap::new();
        let err = check_types_for_compat(hint, found_type, &mut generic_interface, span, project);
        if err.is_some() {
            return (found_type, err);
        }

        return (
            substitute_typevars_in_type(found_type, &generic_interface, project),
            None,
        );
    }

    (found_type, None)
}

pub fn typecheck_binary_operation(
    lhs: &CheckedExpression,
    op: &BinaryOperator,
    rhs: &CheckedExpression,
    scope_id: ScopeId,
    span: Span,
    project: &mut Project,
) -> (TypeId, Option<JaktError>) {
    let lhs_type_id = lhs.type_id(scope_id, project);
    let rhs_type_id = rhs.type_id(scope_id, project);

    let mut type_id = lhs.type_id(scope_id, project);
    match op {
        BinaryOperator::NoneCoalescing | BinaryOperator::NoneCoalescingAssign => {
            // 1. LHS must be Optional<T>.
            // 2. RHS must be Optional<T> or T.
            // 3. Resulting type is Optional<T> or T, respectively.

            // if an assignment, the LHS must be a mutable variable.
            if matches!(op, BinaryOperator::NoneCoalescingAssign) {
                match lhs {
                    CheckedExpression::Var(variable, var_span) => {
                        if !variable.mutable {
                            return (
                                UNKNOWN_TYPE_ID,
                                Some(JaktError::TypecheckErrorWithHint(
                                    "left-hand side of ??= must be a mutable variable".to_string(),
                                    *var_span,
                                    "This variable isn't marked as mutable".to_string(),
                                    variable.definition_span,
                                )),
                            );
                        }
                    }
                    _ => {
                        return (
                            UNKNOWN_TYPE_ID,
                            Some(JaktError::TypecheckError(
                                "left-hand side of ??= must be a variable".to_string(),
                                span,
                            )),
                        );
                    }
                }
            }

            match project.get_type(lhs_type_id) {
                Type::GenericInstance(struct_id, generic_parameters)
                    if *struct_id == project.get_optional_struct_id(span) =>
                {
                    // Success: LHS is T? and RHS is T?.
                    if lhs_type_id == rhs_type_id {
                        return (lhs_type_id, None);
                    }

                    // Extract T from Optional<T>.
                    let inner_type_id = generic_parameters[0];

                    if inner_type_id == rhs_type_id {
                        // Success: LHS is T? and RHS is T.
                        return (inner_type_id, None);
                    }
                }
                _ => {
                    return (
                        lhs_type_id,
                        Some(JaktError::TypecheckErrorWithHint(
                            format!(
                                "None coalescing (??) with incompatible types (‘{}’ and ‘{}’)",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                            "Left side of ?? must be an Optional but isn't".to_string(),
                            lhs.span(),
                        )),
                    );
                }
            }

            return (
                lhs_type_id,
                Some(JaktError::TypecheckError(
                    format!(
                        "None coalescing (??) with incompatible types (‘{}’ and ‘{}’)",
                        project.typename_for_type_id(lhs_type_id),
                        project.typename_for_type_id(rhs_type_id),
                    ),
                    span,
                )),
            );
        }
        BinaryOperator::LessThan
        | BinaryOperator::LessThanOrEqual
        | BinaryOperator::GreaterThan
        | BinaryOperator::GreaterThanOrEqual
        | BinaryOperator::Equal
        | BinaryOperator::NotEqual => {
            if lhs_type_id != rhs_type_id {
                return (
                    lhs_type_id,
                    Some(JaktError::TypecheckError(
                        format!(
                            "Binary comparison operation between incompatible types (‘{}’ and ‘{}’)",
                            project.typename_for_type_id(lhs_type_id),
                            project.typename_for_type_id(rhs_type_id)
                        ),
                        span,
                    )),
                );
            }

            type_id = BOOL_TYPE_ID;
        }
        BinaryOperator::LogicalAnd | BinaryOperator::LogicalOr => {
            if lhs_type_id != BOOL_TYPE_ID {
                return (
                    lhs.type_id(scope_id, project),
                    Some(JaktError::TypecheckError(
                        "left side of logical binary operation is not a boolean".to_string(),
                        span,
                    )),
                );
            }

            if rhs_type_id != BOOL_TYPE_ID {
                return (
                    rhs.type_id(scope_id, project),
                    Some(JaktError::TypecheckError(
                        "right side of logical binary operation is not a boolean".to_string(),
                        span,
                    )),
                );
            }

            type_id = BOOL_TYPE_ID;
        }
        BinaryOperator::Assign => {
            if !lhs.is_mutable() {
                return (
                    lhs_type_id,
                    Some(JaktError::TypecheckError(
                        "Assignment to immutable variable".to_string(),
                        span,
                    )),
                );
            }

            if let CheckedExpression::OptionalNone(_, _) = rhs {
                // if the right expression is None then the left expression must be an optional
                let lhs_type = project.get_type(lhs_type_id);
                let optional_struct_id = project.find_struct_in_prelude("Optional");

                if let Type::GenericInstance(struct_id, _) = lhs_type {
                    if *struct_id == optional_struct_id {
                        return (lhs_type_id, None);
                    }
                }
            }

            let (type_id, err) =
                unify_with_type(rhs_type_id, Some(lhs_type_id), rhs.span(), project);

            if err.is_some() {
                return (
                    type_id,
                    Some(JaktError::TypecheckError(
                        format!(
                            "Assignment between incompatible types (‘{}’ and ‘{}’)",
                            project.typename_for_type_id(lhs_type_id),
                            project.typename_for_type_id(rhs_type_id),
                        ),
                        span,
                    )),
                );
            } else {
                return (type_id, None);
            }
        }
        BinaryOperator::AddAssign
        | BinaryOperator::SubtractAssign
        | BinaryOperator::MultiplyAssign
        | BinaryOperator::DivideAssign
        | BinaryOperator::ModuloAssign
        | BinaryOperator::BitwiseAndAssign
        | BinaryOperator::BitwiseOrAssign
        | BinaryOperator::BitwiseXorAssign
        | BinaryOperator::BitwiseLeftShiftAssign
        | BinaryOperator::BitwiseRightShiftAssign => {
            // This branch can be the same as the above BinaryOp::Assign branch.
            // unify_with_type uses check_types_for_compact which does the same
            // as below.
            let weakptr_struct_id = project.get_weakptr_struct_id(span);

            if let Type::GenericInstance(struct_id, inner_type_ids) = project.get_type(lhs_type_id)
            {
                if *struct_id == weakptr_struct_id {
                    let inner_type_id = inner_type_ids[0];
                    if let Type::Struct(lhs_struct_id) = project.get_type(inner_type_id) {
                        match project.get_type(rhs_type_id) {
                            Type::Struct(rhs_struct_id) if lhs_struct_id == rhs_struct_id => {
                                return (lhs_type_id, None);
                            }
                            _ => {}
                        }
                    }
                }
            }

            if lhs_type_id != rhs_type_id {
                return (
                    lhs_type_id,
                    Some(JaktError::TypecheckError(
                        format!(
                            "Assignment between incompatible types (‘{}’ and ‘{}’)",
                            project.typename_for_type_id(lhs_type_id),
                            project.typename_for_type_id(rhs_type_id),
                        ),
                        span,
                    )),
                );
            }

            if !lhs.is_mutable() {
                return (
                    lhs_type_id,
                    Some(JaktError::TypecheckError(
                        "Assignment to immutable variable".to_string(),
                        span,
                    )),
                );
            }
        }
        BinaryOperator::Add
        | BinaryOperator::Subtract
        | BinaryOperator::Multiply
        | BinaryOperator::Divide
        | BinaryOperator::Modulo => {
            if lhs_type_id != rhs_type_id {
                return (
                    lhs_type_id,
                    Some(JaktError::TypecheckError(
                        format!(
                            "Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)",
                            project.typename_for_type_id(lhs_type_id),
                            project.typename_for_type_id(rhs_type_id),
                        ),
                        span,
                    )),
                );
            }

            type_id = lhs_type_id;
        }
        _ => {}
    }

    (type_id, None)
}

pub fn resolve_call(
    call: &ParsedCall,
    namespaces: &mut [ResolvedNamespace],
    span: &Span,
    scope_id: ScopeId,
    project: &mut Project,
    must_be_enum_constructor: bool,
) -> (Option<FunctionId>, Option<JaktError>) {
    let mut callee = None;
    let mut error = None;

    let mut current_scope_id = scope_id;

    // Resolve namespaces from left to right.
    for (idx, scope_name) in call.namespace.iter().enumerate() {
        if let Some((scope_id, is_import)) =
            project.find_namespace_in_scope(current_scope_id, scope_name)
        {
            if is_import {
                namespaces[idx].name = project.get_module(scope_id.0).name.clone();
            }
            current_scope_id = scope_id;
            continue;
        }
        if let Some(struct_id) = project.find_struct_in_scope(current_scope_id, scope_name) {
            let structure = project.get_struct(struct_id);
            current_scope_id = structure.scope_id;
            if !structure.generic_parameters.is_empty() {
                // FIXME: This doesn't look right.
                namespaces[0].generic_parameters = Some(structure.generic_parameters.clone());
            }
            continue;
        }
        if let Some(enum_id) = project.find_enum_in_scope(current_scope_id, scope_name) {
            let enum_ = project.get_enum(enum_id);
            current_scope_id = enum_.scope_id;
            if !enum_.generic_parameters.is_empty() {
                // FIXME: This doesn't look right.
                namespaces[0].generic_parameters = Some(enum_.generic_parameters.clone());
            }
            continue;
        }

        let similar_name =
            project.find_most_similar_namespace_name_in_scope(current_scope_id, scope_name);
        let similar_name = similar_name
            .or(project.find_most_similar_struct_name_in_scope(current_scope_id, scope_name));
        let similar_name = similar_name
            .or(project.find_most_similar_enum_name_in_scope(current_scope_id, scope_name));
        if let Some(similar_name) = similar_name {
            error = error.or(Some(JaktError::TypecheckErrorWithHint(
                format!(
                    "Not a namespace, enum, class, or struct: ‘{}’",
                    call.namespace.join("::")
                ),
                *span,
                format!("Did you mean '{}'?", similar_name),
                *span,
            )));
        }

        error = error.or(Some(JaktError::TypecheckError(
            format!(
                "Not a namespace, enum, class, or struct: ‘{}’",
                call.namespace.join("::")
            ),
            *span,
        )));
    }

    // 1. Look for a function with this name.
    if let Some(function_id) = project.find_function_in_scope(current_scope_id, &call.name) {
        if !must_be_enum_constructor
            || project.get_function(function_id).linkage == FunctionLinkage::ImplicitEnumConstructor
        {
            callee = Some(function_id);
            return (callee, error);
        }
    }

    if must_be_enum_constructor {
        error = error.or(Some(JaktError::TypecheckError(
            format!("No such enum constructor ‘{}’", &call.name),
            *span,
        )));
        return (callee, error);
    }

    // 2. Look for a struct, class or enum constructor with this name.
    if let Some(struct_id) = project.find_struct_in_scope(current_scope_id, &call.name) {
        let structure = project.get_struct(struct_id);
        if let Some(function_id) = project.find_function_in_scope(structure.scope_id, &call.name) {
            return (Some(function_id), error);
        }
        return (callee, error);
    }

    if let Some(enum_id) = project.find_enum_in_scope(current_scope_id, &call.name) {
        let enum_ = project.get_enum(enum_id);
        if let Some(function_id) = project.find_function_in_scope(enum_.scope_id, &call.name) {
            return (Some(function_id), error);
        }
        return (callee, error);
    }

    let similar_name =
        project.find_most_similar_function_name_in_scope(current_scope_id, &call.name);
    let similar_name = similar_name
        .or(project.find_most_similar_struct_name_in_scope(current_scope_id, &call.name));
    let similar_name =
        similar_name.or(project.find_most_similar_enum_name_in_scope(current_scope_id, &call.name));
    if let Some(similar_name) = similar_name {
        error = error.or(Some(JaktError::TypecheckErrorWithHint(
            format!("Call to unknown function: ‘{}’", &call.name),
            *span,
            format!("Did you mean '{}'?", similar_name),
            *span,
        )));
    }

    error = error.or(Some(JaktError::TypecheckError(
        format!("call to unknown function: {}", &call.name),
        *span,
    )));

    (callee, error)
}

pub fn typecheck_call(
    call: &ParsedCall,
    caller_scope_id: ScopeId,
    span: &Span,
    project: &mut Project,
    this_expr: Option<&CheckedExpression>,
    parent_id: Option<StructOrEnumId>,
    safety_mode: SafetyMode,
    type_hint: Option<TypeId>,
    must_be_enum_constructor: bool,
) -> (CheckedCall, Option<JaktError>) {
    let mut checked_args = Vec::new();
    let mut error = None;
    let mut return_type_id = UNKNOWN_TYPE_ID;
    let mut linkage = FunctionLinkage::Internal;
    let mut generic_substitutions = HashMap::new();
    let mut type_args = vec![];
    let mut callee_throws = false;
    let mut resolved_namespaces = call
        .namespace
        .iter()
        .map(|n| ResolvedNamespace {
            name: n.clone(),
            generic_parameters: None,
        })
        .collect::<Vec<_>>();

    let callee_scope_id = match parent_id {
        Some(StructOrEnumId::Struct(struct_id)) => {
            // We are a method, so let's look up the scope id for our struct
            project.get_struct(struct_id).scope_id
        }
        Some(StructOrEnumId::Enum(enum_id)) => project.get_enum(enum_id).scope_id,
        _ => caller_scope_id,
    };

    let mut generic_checked_function_to_instantiate = None;
    let mut maybe_this_type_id = None;
    let mut function_id = None;

    match call.name.as_str() {
        "print" | "println" | "eprint" | "eprintln" | "format"
            if !must_be_enum_constructor && parent_id.is_none() =>
        {
            // FIXME: This is a hack since println() and eprintln() are hard-coded into codegen at the moment.
            for arg in &call.args {
                let (checked_arg, err) =
                    typecheck_expression(&arg.1, caller_scope_id, project, safety_mode, None);
                error = error.or(err);

                let result_type_id = substitute_typevars_in_type(
                    checked_arg.type_id(callee_scope_id, project),
                    &generic_substitutions,
                    project,
                );

                if result_type_id == VOID_TYPE_ID {
                    error = error.or(Some(JaktError::TypecheckError(
                        "println/eprintln can't take void values".into(),
                        *span,
                    )));
                }

                if call.name == "format" {
                    callee_throws = true; // `format` always throws
                    return_type_id = STRING_TYPE_ID;
                } else {
                    return_type_id = VOID_TYPE_ID;
                }

                checked_args.push((arg.0.clone(), checked_arg));
            }
        }
        _ => {
            let (callee, err) = resolve_call(
                call,
                &mut resolved_namespaces,
                span,
                callee_scope_id,
                project,
                must_be_enum_constructor,
            );
            error = error.or(err);

            function_id = callee;

            if let Some(callee_id) = callee {
                let callee = project.get_function(callee_id);
                if !callee.is_instantiated {
                    generic_checked_function_to_instantiate = Some(callee_id);
                }
                callee_throws = callee.throws;
                return_type_id = callee.return_type_id;
                linkage = callee.linkage;

                let scope_containing_callee = project
                    .get_scope(callee.function_scope_id)
                    .parent
                    .expect("Function should have a parent scope");

                // Make sure we are allowed to access this method.
                error = error.or(check_accessibility(
                    caller_scope_id,
                    scope_containing_callee,
                    callee.clone(),
                    span,
                    project,
                ));

                // If the user gave us explicit type arguments, let's use them in our substitutions
                for (idx, type_arg) in call.type_args.iter().enumerate() {
                    let (checked_type, err) =
                        typecheck_typename(type_arg, caller_scope_id, project);
                    error = error.or(err);

                    let callee = project.get_function(callee_id);
                    if callee.generic_parameters.len() <= idx {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Trying to access generic parameter out of bounds".to_string(),
                            *span,
                        )));
                        continue;
                    }

                    // Find the associated type variable for this parameter, we'll use it in substitution
                    let typevar_type_id = match callee.generic_parameters[idx] {
                        FunctionGenericParameter::InferenceGuide(typevar_type_id)
                        | FunctionGenericParameter::Parameter(typevar_type_id) => typevar_type_id,
                    };

                    generic_substitutions.insert(typevar_type_id, checked_type);
                }

                // If this is a method, let's also add the types we know from our 'this' pointer
                if let Some(this_expr) = this_expr {
                    let type_id = this_expr.type_id(callee_scope_id, project);
                    maybe_this_type_id = Some(type_id);
                    let param_type = project.get_type(type_id);

                    if let Type::GenericInstance(struct_id, args) = param_type {
                        let structure = project.get_struct(*struct_id);

                        let mut idx = 0;

                        while idx < structure.generic_parameters.len() {
                            generic_substitutions
                                .insert(structure.generic_parameters[idx], args[idx]);
                            idx += 1;
                        }
                    }

                    let callee = project.get_function(callee_id);
                    // Make sure that our call doesn't have a 'this' pointer to a static callee
                    if callee.is_static() {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Cannot call static method on an instance of an object".to_string(),
                            *span,
                        )));
                    }

                    if callee.is_mutating() && !this_expr.is_mutable() {
                        error = error.or(Some(JaktError::TypecheckError(
                            "Cannot call mutating method on an immutable object instance"
                                .to_string(),
                            *span,
                        )));
                    }
                }

                // This will be 0 for functions or 1 for instance methods, because of the
                // 'this' ptr
                let arg_offset = if this_expr.is_some() { 1 } else { 0 };

                // Check that we have the right number of arguments.
                let callee = project.get_function(callee_id);

                if callee.params.len() != (call.args.len() + arg_offset) {
                    error = error.or(Some(JaktError::TypecheckError(
                        "wrong number of arguments".to_string(),
                        *span,
                    )));
                } else {
                    let mut idx = 0;

                    while idx < call.args.len() {
                        let param = &project.get_function(callee_id).params[idx + arg_offset];
                        let type_hint = param.variable.type_id;
                        let (mut checked_arg, err) = typecheck_expression(
                            &call.args[idx].1,
                            caller_scope_id,
                            project,
                            safety_mode,
                            Some(type_hint),
                        );
                        error = error.or(err);

                        // Borrowchecker workaround: since we need project to be mutable above, we
                        // need to let go of the previous callee and then look it up again
                        let (callee, _) = resolve_call(
                            call,
                            &mut resolved_namespaces,
                            span,
                            callee_scope_id,
                            project,
                            false,
                        );
                        let callee_id = callee
                            .expect("internal error: previously resolved call is now unresolved");

                        let callee = project.get_function(callee_id);

                        if let ParsedExpression::Var(var_name, _) = &call.args[idx].1 {
                            if var_name != &callee.params[idx + arg_offset].variable.name
                                && callee.params[idx + arg_offset].requires_label
                                && call.args[idx].0 != callee.params[idx + arg_offset].variable.name
                            {
                                error = error.or(Some(JaktError::TypecheckError(
                                    "Wrong parameter name in argument label".to_string(),
                                    call.args[idx].1.span(),
                                )));
                            }
                        } else if callee.params[idx + arg_offset].requires_label
                            && call.args[idx].0 != callee.params[idx + arg_offset].variable.name
                        {
                            error = error.or(Some(JaktError::TypecheckError(
                                "Wrong parameter name in argument label".to_string(),
                                call.args[idx].1.span(),
                            )));
                        }

                        let lhs_type_id = callee.params[idx + arg_offset].variable.type_id;

                        let err =
                            try_promote_constant_expr_to_type(lhs_type_id, &mut checked_arg, span);
                        error = error.or(err);

                        let lhs_type_id = callee.params[idx + arg_offset].variable.type_id;
                        let rhs_type_id = checked_arg.type_id(callee_scope_id, project);

                        if let Some(err) = check_types_for_compat(
                            lhs_type_id,
                            rhs_type_id,
                            &mut generic_substitutions,
                            call.args[idx].1.span(),
                            project,
                        ) {
                            error = error.or(Some(err));
                        }

                        checked_args.push((call.args[idx].0.clone(), checked_arg));

                        idx += 1;
                    }
                }

                // We've now seen all the arguments and should be able to substitute the return type, if it's contains a
                // type variable. For the moment, we'll just checked to see if it's a type variable.
                if let Some(type_hint) = type_hint {
                    check_types_for_compat(
                        return_type_id,
                        type_hint,
                        &mut generic_substitutions,
                        *span,
                        project,
                    );
                }
                return_type_id =
                    substitute_typevars_in_type(return_type_id, &generic_substitutions, project);

                resolved_namespaces = resolved_namespaces
                    .iter()
                    .map(|n| ResolvedNamespace {
                        name: n.name.clone(),
                        generic_parameters: n.generic_parameters.as_ref().map(|p| {
                            p.iter()
                                .map(|type_id| {
                                    substitute_typevars_in_type(
                                        *type_id,
                                        &generic_substitutions,
                                        project,
                                    )
                                })
                                .collect()
                        }),
                    })
                    .collect();

                let callee = project.get_function(callee_id);
                for generic_typevar in &callee.generic_parameters {
                    if let FunctionGenericParameter::Parameter(id) = generic_typevar {
                        if let Some(substitution) = generic_substitutions.get(id) {
                            type_args.push(*substitution)
                        } else {
                            error = error.or(Some(JaktError::TypecheckError(
                                "not all generic parameters have known types".into(),
                                *span,
                            )))
                        }
                    }
                }
            } else {
                error = error.or(Some(JaktError::TypecheckError(
                    format!("Could not resolve call to {}", call.name),
                    *span,
                )))
            }
        }
    }

    if callee_throws && !project.get_scope(caller_scope_id).throws {
        error = error.or(
            Some(JaktError::TypecheckError(
                "Call to function that may throw needs to be in a try statement or a function marked as throws".to_string(),
                *span,
            ))
        );
    }

    if let Some(function_id) = generic_checked_function_to_instantiate {
        // Clear the generic parameters and typecheck in the fully specialised scope.
        maybe_this_type_id = maybe_this_type_id
            .map(|id| substitute_typevars_in_type(id, &generic_substitutions, project));

        let err = typecheck_and_specialize_generic_function(
            function_id,
            type_args.clone(),
            callee_scope_id,
            maybe_this_type_id,
            &generic_substitutions,
            project,
        );
        error = error.or(err);
    }

    (
        CheckedCall {
            namespace: resolved_namespaces,
            name: call.name.clone(),
            function_id,
            callee_throws,
            args: checked_args,
            type_args,
            linkage,
            type_id: return_type_id,
        },
        error,
    )
}

pub fn substitute_typevars_in_type(
    type_id: TypeId,
    generic_inferences: &HashMap<TypeId, TypeId>,
    project: &mut Project,
) -> TypeId {
    let mut result = substitute_typevars_in_type_helper(type_id, generic_inferences, project);

    loop {
        let fixed_point = substitute_typevars_in_type_helper(type_id, generic_inferences, project);

        if fixed_point == result {
            break;
        } else {
            result = fixed_point;
        }
    }

    result
}

fn substitute_typevars_in_type_helper(
    type_id: TypeId,
    generic_inferences: &HashMap<TypeId, TypeId>,
    project: &mut Project,
) -> TypeId {
    let type_ = project.get_type(type_id);
    match type_ {
        Type::TypeVariable(_) => {
            if let Some(replacement) = generic_inferences.get(&type_id) {
                return *replacement;
            }
        }
        Type::GenericInstance(struct_id, args) => {
            let struct_id = *struct_id;
            let mut new_args = args.clone();

            for arg in &mut new_args {
                *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
            }

            return project.find_or_add_type_id(Type::GenericInstance(struct_id, new_args));
        }
        Type::GenericEnumInstance(enum_id, args) => {
            let enum_id = *enum_id;
            let mut new_args = args.clone();

            for arg in &mut new_args {
                *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
            }

            return project.find_or_add_type_id(Type::GenericEnumInstance(enum_id, new_args));
        }
        Type::Struct(struct_id) => {
            let struct_id = *struct_id;
            let structure = project.get_struct(struct_id);

            if !structure.generic_parameters.is_empty() {
                let mut new_args = structure.generic_parameters.clone();

                for arg in &mut new_args {
                    *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
                }

                return project.find_or_add_type_id(Type::GenericInstance(struct_id, new_args));
            }
        }
        Type::Enum(enum_id) => {
            let enum_id = *enum_id;
            let enum_ = project.get_enum(enum_id);

            if !enum_.generic_parameters.is_empty() {
                let mut new_args = enum_.generic_parameters.clone();

                for arg in &mut new_args {
                    *arg = substitute_typevars_in_type(*arg, generic_inferences, project);
                }

                return project.find_or_add_type_id(Type::GenericEnumInstance(enum_id, new_args));
            }
        }
        Type::RawPtr(type_id) => {
            let type_ = Type::RawPtr(substitute_typevars_in_type(
                *type_id,
                generic_inferences,
                project,
            ));
            return project.find_or_add_type_id(type_);
        }
        _ => {}
    }

    type_id
}

pub fn check_types_for_compat(
    lhs_type_id: TypeId,
    rhs_type_id: TypeId,
    generic_inferences: &mut HashMap<TypeId, TypeId>,
    span: Span,
    project: &Project,
) -> Option<JaktError> {
    let mut error = None;
    let lhs_type = project.get_type(lhs_type_id);

    let optional_struct_id = project.get_optional_struct_id(span);
    let weak_ptr_struct_id = project.get_weakptr_struct_id(span);

    // This skips the type compatibility check if assigning a T to a T? or to a
    // weak T? without going through `Some`.
    if let Type::GenericInstance(lhs_struct_id, args) = lhs_type {
        if (*lhs_struct_id == optional_struct_id || *lhs_struct_id == weak_ptr_struct_id)
            && args.first().map_or(false, |arg_id| *arg_id == rhs_type_id)
        {
            return None;
        }
    }

    match lhs_type {
        Type::TypeVariable(_) => {
            // If the call expects a generic type variable, let's see if we've already seen it
            if let Some(seen_type_id) = generic_inferences.get(&lhs_type_id) {
                // We've seen this type variable assigned something before
                // we should error if it's incompatible.

                if rhs_type_id != *seen_type_id {
                    error = error.or(Some(JaktError::TypecheckError(
                        format!(
                            "Type mismatch: expected ‘{}’, but got ‘{}’",
                            project.typename_for_type_id(*seen_type_id),
                            project.typename_for_type_id(rhs_type_id),
                        ),
                        span,
                    )))
                }
            } else {
                // We haven't seen this type variable before, so go ahead
                // and give it an actual type during this call
                generic_inferences.insert(lhs_type_id, rhs_type_id);
            }
        }
        Type::GenericEnumInstance(lhs_enum_id, lhs_args) => {
            let lhs_args = lhs_args.clone();
            let rhs_type = project.get_type(rhs_type_id);
            match rhs_type {
                Type::GenericEnumInstance(rhs_enum_id, rhs_args) => {
                    let rhs_args = rhs_args.clone();
                    if lhs_enum_id == rhs_enum_id {
                        // Same enum, so check the generic arguments

                        let lhs_enum = project.get_enum(*lhs_enum_id);
                        if rhs_args.len() != lhs_args.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_enum.name
                                ),
                                span,
                            ));
                        }

                        let mut idx = 0;

                        while idx < lhs_args.len() {
                            let lhs_arg_type_id = lhs_args[idx];
                            let rhs_arg_type_id = rhs_args[idx];

                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::GenericInstance(lhs_struct_id, lhs_args) => {
            let lhs_args = lhs_args.clone();
            let rhs_type = project.get_type(rhs_type_id);
            match rhs_type {
                Type::GenericInstance(rhs_struct_id, rhs_args) => {
                    if lhs_struct_id == rhs_struct_id {
                        let rhs_args = rhs_args.clone();
                        // Same struct, perhaps this is an instantiation of it

                        let lhs_struct = project.get_struct(*lhs_struct_id);
                        if rhs_args.len() != lhs_args.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_struct.name
                                ),
                                span,
                            ));
                        }

                        let mut idx = 0;

                        while idx < lhs_args.len() {
                            let lhs_arg_type_id = lhs_args[idx];
                            let rhs_arg_type_id = rhs_args[idx];

                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    } else {
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                        )))
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::Enum(lhs_enum_id) => {
            if rhs_type_id == lhs_type_id {
                // They're the same type, might be okay to just leave now
                return None;
            }

            let rhs_type = project.get_type(rhs_type_id);
            match rhs_type {
                Type::GenericEnumInstance(rhs_enum_id, rhs_args) => {
                    let rhs_args = rhs_args.clone();
                    if lhs_enum_id == rhs_enum_id {
                        let lhs_enum = &project.get_enum(*lhs_enum_id);
                        if rhs_args.len() != lhs_enum.generic_parameters.len() {
                            return Some(JaktError::TypecheckError(
                                format!(
                                    "mismatched number of generic parameters for {}",
                                    lhs_enum.name
                                ),
                                span,
                            ));
                        }

                        let lhs_enum_generic_parameters = lhs_enum.generic_parameters.clone();

                        let mut idx = 0;

                        while idx < rhs_args.len() {
                            let lhs_arg_type_id = lhs_enum_generic_parameters[idx];
                            let rhs_arg_type_id = rhs_args[idx];

                            if let Some(err) = check_types_for_compat(
                                lhs_arg_type_id,
                                rhs_arg_type_id,
                                generic_inferences,
                                span,
                                project,
                            ) {
                                return Some(err);
                            }
                            idx += 1;
                        }
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::Struct(lhs_struct_id) => {
            if rhs_type_id == lhs_type_id {
                // They're the same type, might be okay to just leave now
                return None;
            }

            let rhs_type = project.get_type(rhs_type_id);
            match rhs_type {
                Type::GenericInstance(rhs_struct_id, args) if lhs_struct_id == rhs_struct_id => {
                    let args = args.clone();
                    // Same struct, perhaps this is an instantiation of it

                    let lhs_struct = project.get_struct(*lhs_struct_id);
                    if args.len() != lhs_struct.generic_parameters.len() {
                        return Some(JaktError::TypecheckError(
                            format!(
                                "mismatched number of generic parameters for {}",
                                lhs_struct.name
                            ),
                            span,
                        ));
                    }

                    let mut idx = 0;

                    let lhs_arg_type_id = lhs_struct.generic_parameters[idx];
                    let rhs_arg_type_id = args[idx];

                    while idx < args.len() {
                        if let Some(err) = check_types_for_compat(
                            lhs_arg_type_id,
                            rhs_arg_type_id,
                            generic_inferences,
                            span,
                            project,
                        ) {
                            return Some(err);
                        }
                        idx += 1;
                    }
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        // They're the same type, might be okay to just leave now
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        Type::RawPtr(lhs_type_id) => {
            let lhs_type_id = *lhs_type_id;
            if rhs_type_id == lhs_type_id {
                // They're the same type, might be okay to just leave now
                return None;
            }

            let rhs_type = project.get_type(rhs_type_id);
            match rhs_type {
                Type::RawPtr(rhs_type_id) => {
                    let rhs_type_id = *rhs_type_id;
                    error = error.or(check_types_for_compat(
                        lhs_type_id,
                        rhs_type_id,
                        generic_inferences,
                        span,
                        project,
                    ));
                }
                _ => {
                    if rhs_type_id != lhs_type_id {
                        error = error.or(Some(JaktError::TypecheckError(
                            format!(
                                "Type mismatch: expected ‘{}’, but got ‘{}’",
                                project.typename_for_type_id(lhs_type_id),
                                project.typename_for_type_id(rhs_type_id),
                            ),
                            span,
                        )))
                    }
                }
            }
        }
        _ => {
            if rhs_type_id != lhs_type_id {
                error = error.or(Some(JaktError::TypecheckError(
                    format!(
                        "Type mismatch: expected ‘{}’, but got ‘{}’",
                        project.typename_for_type_id(lhs_type_id),
                        project.typename_for_type_id(rhs_type_id),
                    ),
                    span,
                )))
            }
        }
    }

    error
}

pub fn typecheck_typename(
    unchecked_type: &ParsedType,
    scope_id: ScopeId,
    project: &mut Project,
) -> (TypeId, Option<JaktError>) {
    let mut error = None;

    match unchecked_type {
        ParsedType::NamespacedName(name, namespaces, generic_parameters, span) => {
            let mut current_namespace_scope_id = scope_id;
            for namespace in namespaces {
                if let Some(namespace_scope_id) =
                    project.find_namespace_in_scope(current_namespace_scope_id, namespace)
                {
                    current_namespace_scope_id = namespace_scope_id.0;
                } else {
                    return (
                        UNKNOWN_TYPE_ID,
                        Some(JaktError::TypecheckError(
                            format!("Unknown namespace '{}'", namespace),
                            *span,
                        )),
                    );
                }
            }

            let (generic_parameters, err) =
                generic_parameters
                    .iter()
                    .fold((Vec::new(), error), |mut acc, x| {
                        let (type_id, err) =
                            typecheck_typename(x, current_namespace_scope_id, project);
                        acc.0.push(type_id);
                        acc.1 = acc.1.or(err);
                        acc
                    });

            error = err;

            let synthetic_typename = if generic_parameters.is_empty() {
                ParsedType::Name(name.clone(), *span)
            } else {
                ParsedType::GenericResolvedType(name.clone(), generic_parameters, *span)
            };
            let (type_id, err) =
                typecheck_typename(&synthetic_typename, current_namespace_scope_id, project);
            error = error.or(err);

            (type_id, error)
        }
        ParsedType::Name(name, span) => match name.as_str() {
            "i8" => (I8_TYPE_ID, None),
            "i16" => (I16_TYPE_ID, None),
            "i32" => (I32_TYPE_ID, None),
            "i64" => (I64_TYPE_ID, None),
            "u8" => (U8_TYPE_ID, None),
            "u16" => (U16_TYPE_ID, None),
            "u32" => (U32_TYPE_ID, None),
            "u64" => (U64_TYPE_ID, None),
            "f32" => (F32_TYPE_ID, None),
            "f64" => (F64_TYPE_ID, None),
            "c_char" => (CCHAR_TYPE_ID, None),
            "c_int" => (CINT_TYPE_ID, None),
            "usize" => (USIZE_TYPE_ID, None),
            "String" => (STRING_TYPE_ID, None),
            "bool" => (BOOL_TYPE_ID, None),
            "void" => (VOID_TYPE_ID, None),
            x => {
                let type_id = project.find_type_in_scope(scope_id, x);
                match type_id {
                    Some(type_id) => (type_id, None),
                    None => {
                        if let Some(similar_name) =
                            project.find_most_similar_type_name_in_scope(scope_id, x)
                        {
                            (
                                UNKNOWN_TYPE_ID,
                                Some(JaktError::TypecheckErrorWithHint(
                                    format!("Unknown type ‘{}’", x),
                                    *span,
                                    format!("Did you mean '{}'?", similar_name),
                                    *span,
                                )),
                            )
                        } else {
                            (
                                UNKNOWN_TYPE_ID,
                                Some(JaktError::TypecheckError(
                                    format!("Unknown type ‘{}’", x),
                                    *span,
                                )),
                            )
                        }
                    }
                }
            }
        },
        ParsedType::Empty => (UNKNOWN_TYPE_ID, None),
        ParsedType::Tuple(inner_types, span) => {
            let mut checked_types = Vec::new();
            for inner_type in inner_types {
                let (type_id, err) = typecheck_typename(inner_type, scope_id, project);
                error = error.or(err);
                checked_types.push(type_id);
            }

            let tuple_struct_id = project.get_tuple_struct_id(*span);
            // FIXME: Tuple is not a generic type since we don't have variadic generics yet, however
            // we don't actually check if the stuct_id is actually generic or not, so the type checking
            // works as expected for now.
            let type_id =
                project.find_or_add_type_id(Type::GenericInstance(tuple_struct_id, checked_types));

            (type_id, error)
        }
        ParsedType::Array(inner, span) => {
            let (inner_type_id, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let vector_struct_id = project.get_array_struct_id(*span);
            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(vector_struct_id, vec![inner_type_id]));

            (type_id, error)
        }
        ParsedType::Dictionary(key, value, span) => {
            let (key_type_id, err) = typecheck_typename(key, scope_id, project);
            error = error.or(err);
            let (value_type_id, err) = typecheck_typename(value, scope_id, project);
            error = error.or(err);

            let dictionary_struct_id = project.get_dictionary_struct_id(*span);
            let type_id = project.find_or_add_type_id(Type::GenericInstance(
                dictionary_struct_id,
                vec![key_type_id, value_type_id],
            ));

            (type_id, error)
        }
        ParsedType::Set(inner, span) => {
            let (inner_type_id, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let set_struct_id = project.get_set_struct_id(*span);
            let type_id = project
                .find_or_add_type_id(Type::GenericInstance(set_struct_id, vec![inner_type_id]));

            (type_id, error)
        }
        ParsedType::Optional(inner, span) => {
            let (inner_type_id, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let optional_struct_id = project.get_optional_struct_id(*span);

            let type_id = project.find_or_add_type_id(Type::GenericInstance(
                optional_struct_id,
                vec![inner_type_id],
            ));

            (type_id, error)
        }
        ParsedType::WeakPtr(inner, span) => {
            let (inner_type_id, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let weakptr_struct_id = project.get_weakptr_struct_id(*span);

            let type_id = project.find_or_add_type_id(Type::GenericInstance(
                weakptr_struct_id,
                vec![inner_type_id],
            ));

            (type_id, error)
        }
        ParsedType::RawPtr(inner, _) => {
            let (inner_type_id, err) = typecheck_typename(inner, scope_id, project);
            error = error.or(err);

            let type_id = project.find_or_add_type_id(Type::RawPtr(inner_type_id));

            (type_id, error)
        }
        ParsedType::GenericResolvedType(name, checked_inner_types, span) => {
            let struct_id = project.find_struct_in_scope(scope_id, name);
            let checked_inner_types = checked_inner_types.clone();

            if let Some(struct_id) = struct_id {
                (
                    project
                        .find_or_add_type_id(Type::GenericInstance(struct_id, checked_inner_types)),
                    error,
                )
            } else {
                let enum_id = project.find_enum_in_scope(scope_id, name);
                if let Some(enum_id) = enum_id {
                    (
                        project.find_or_add_type_id(Type::GenericEnumInstance(
                            enum_id,
                            checked_inner_types,
                        )),
                        error,
                    )
                } else {
                    (
                        UNKNOWN_TYPE_ID,
                        Some(JaktError::TypecheckError(
                            format!("could not find {}", name),
                            *span,
                        )),
                    )
                }
            }
        }
        ParsedType::GenericType(name, inner_types, span) => {
            let mut checked_inner_types = vec![];

            for inner_type in inner_types {
                let (inner_type_id, err) = typecheck_typename(inner_type, scope_id, project);
                error = error.or(err);

                checked_inner_types.push(inner_type_id);
            }
            typecheck_typename(
                &ParsedType::GenericResolvedType(name.clone(), checked_inner_types, *span),
                scope_id,
                project,
            )
        }
    }
}
