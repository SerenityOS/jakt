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

use std::{
    path::{Path, PathBuf},
    vec,
};

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::lex,
    parser::{parse_namespace, ParsedNamespace},
    typechecker::{
        typecheck_module, typecheck_namespace_declarations, typecheck_namespace_predecl, Module,
        ModuleId, Project, Scope, ScopeId, Type, TypeId,
    },
};

pub type FileId = usize;

pub const UNKNOWN_TYPE_ID: TypeId = TypeId(ModuleId(0), 0);
pub const VOID_TYPE_ID: TypeId = TypeId(ModuleId(0), 1);
pub const BOOL_TYPE_ID: TypeId = TypeId(ModuleId(0), 2);
pub const I8_TYPE_ID: TypeId = TypeId(ModuleId(0), 3);
pub const I16_TYPE_ID: TypeId = TypeId(ModuleId(0), 4);
pub const I32_TYPE_ID: TypeId = TypeId(ModuleId(0), 5);
pub const I64_TYPE_ID: TypeId = TypeId(ModuleId(0), 6);
pub const U8_TYPE_ID: TypeId = TypeId(ModuleId(0), 7);
pub const U16_TYPE_ID: TypeId = TypeId(ModuleId(0), 8);
pub const U32_TYPE_ID: TypeId = TypeId(ModuleId(0), 9);
pub const U64_TYPE_ID: TypeId = TypeId(ModuleId(0), 10);
pub const F32_TYPE_ID: TypeId = TypeId(ModuleId(0), 11);
pub const F64_TYPE_ID: TypeId = TypeId(ModuleId(0), 12);
pub const CCHAR_TYPE_ID: TypeId = TypeId(ModuleId(0), 13);
pub const CINT_TYPE_ID: TypeId = TypeId(ModuleId(0), 14);
pub const USIZE_TYPE_ID: TypeId = TypeId(ModuleId(0), 15);
// Note: keep STRING_TYPE_ID last as it is how we know how many slots to pre-fill
pub const STRING_TYPE_ID: TypeId = TypeId(ModuleId(0), 16);

pub const PRELUDE_SCOPE_ID: ScopeId = ScopeId(ModuleId(0), 0);

pub struct SourceInfo {
    pub module_id: ModuleId,
    pub file_id: FileId,
    pub path: PathBuf,
    pub content: String,
}

pub struct Compiler {
    include_paths: Vec<PathBuf>,
    pub loaded_files: Vec<SourceInfo>,
}

impl Compiler {
    pub fn new(include_paths: Vec<PathBuf>) -> Self {
        Self {
            include_paths,
            loaded_files: vec![],
        }
    }

    pub fn is_file_loaded(&self, path: &Path) -> bool {
        for info in self.loaded_files.iter() {
            if info.path == path {
                return true;
            }
        }
        false
    }

    pub fn search_for_path(&self, name: &str) -> Option<PathBuf> {
        for path in &self.include_paths {
            let fname = path.join(name).with_extension("jakt");
            if fname.exists() {
                return Some(fname);
            }
        }
        None
    }

    /// return the file id of a file. Loading it if it isn't loaded already.
    pub fn find_or_load_file<P: AsRef<Path> + Clone>(&mut self, p: P) -> Result<FileId, JaktError> {
        if self.is_file_loaded(p.as_ref()) {
            for (idx, info) in self.loaded_files.iter().enumerate() {
                if info.path == p.as_ref() {
                    return Ok(idx);
                }
            }
            unreachable!()
        }
        let content = std::fs::read_to_string(p.clone()).map_err(JaktError::IOError)?;
        self.loaded_files.push(SourceInfo {
            module_id: ModuleId::invalid(),
            file_id: self.loaded_files.len(),
            path: p.as_ref().to_path_buf(),
            content,
        });
        Ok(self.loaded_files.len() - 1)
    }

    pub fn include_prelude(&mut self, project: &mut Project) -> Option<JaktError> {
        let mut error = None;
        let mut module = Module::new(ModuleId(0), "__prelude__".to_string());
        // First, let's make types for all the builtin types
        // This order *must* match the order of the constants the typechecker expects
        module.types.resize(STRING_TYPE_ID.1 + 1, Type::Builtin);

        module.scopes.push(Scope::new(None, false));

        project.modules.push(module);
        project.current_module_index = 0;

        let prelude = Compiler::prelude();

        self.loaded_files.push(SourceInfo {
            module_id: ModuleId(0),
            file_id: self.loaded_files.len(),
            path: PathBuf::new(),
            content: prelude.to_string(),
        });

        // Compile the prelude
        project.checking_prelude = true;

        // Not sure where to put prelude, but we're hoping its parsing is infallible
        let (lexed, _) = lex(0, prelude.as_bytes());
        let (file, _) = parse_namespace(&lexed, &mut 0);

        // Scope ID 0 is the global project-level scope that all files can see
        error = error.or(typecheck_namespace_predecl(
            &file,
            ScopeId(ModuleId(0), 0),
            project,
        ));
        error = error.or(typecheck_namespace_declarations(
            &file,
            ScopeId(ModuleId(0), 0),
            project,
        ));

        project.checking_prelude = false;

        error
    }

    pub fn parse_file(&self, file_id: FileId) -> (ParsedNamespace, Option<JaktError>) {
        let mut error = None;

        let info = &self.loaded_files[file_id];

        let (lexed, err) = lex(file_id, info.content.as_bytes());
        error = error.or(err);

        let (namespace, err) = parse_namespace(&lexed, &mut 0);
        error = error.or(err);

        (namespace, error)
    }

    pub fn check_project(
        &mut self,
        fname: &Path,
        project: &mut Project,
    ) -> (ScopeId, Option<JaktError>) {
        let mut error = None;

        let err = self.include_prelude(project);
        error = error.or(err);

        // find a better way to look this up.
        // TODO: We also want to be able to accept include paths from CLI
        let parent_dir = fname
            .parent()
            .expect("Cannot find parent directory of file");
        self.include_paths.push(parent_dir.to_path_buf());

        // should always be 0
        let file_scope_id = ScopeId(project.current_module().id, 0);

        let file_id = match self.find_or_load_file(fname) {
            Ok(file_id) => file_id,
            Err(e) => return (file_scope_id, Some(e)),
        };

        let (parsed_namespace, err) = self.parse_file(file_id);
        error = error.or(err);

        let scope = Scope::new(Some(PRELUDE_SCOPE_ID), false);
        project.current_module_mut().scopes.push(scope);

        let err = typecheck_module(
            &parsed_namespace,
            project.current_module().id,
            file_scope_id,
            project,
            self,
        );
        error = error.or(err);

        (file_scope_id, error)
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
        let mut project = Project::new();

        let (_, err) = self.check_project(fname, &mut project);
        if let Some(err) = err {
            return Err(err);
        }

        if let Some(err) = check_codegen_preconditions(&project) {
            return Err(err);
        }

        // Hardwire to first file for now
        Ok(codegen(&project))
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        self.loaded_files[file_id].content.as_bytes()
    }

    pub fn get_file_name(&self, file_id: FileId) -> &Path {
        self.loaded_files[file_id].path.as_path()
    }

    pub fn prelude() -> &'static str {
        include_str!("../runtime/prelude.jakt")
    }
}

fn check_codegen_preconditions(project: &Project) -> Option<JaktError> {
    // Make sure all functions have a known return type
    for module in project.modules.iter() {
        for function in module.functions.iter() {
            if function.return_type_id == UNKNOWN_TYPE_ID {
                return Some(JaktError::TypecheckError(
                    format!("Could not infer the return type of function '{}', please explicitly specify it",
                    function.name),
                    function.parsed_function.as_ref().expect("Typechecking non-parsed function").name_span,
                ));
            }
        }
    }

    None
}
