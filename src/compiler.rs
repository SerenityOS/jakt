/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

use std::path::{Path, PathBuf};

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::{lex, Span},
    parser::{parse_namespace, ParsedNamespace},
    typechecker::{
        typecheck_namespace_declarations, typecheck_namespace_predecl, Project, Scope, Type,
    },
};

pub type FileId = usize;

pub const UNKNOWN_TYPE_ID: usize = 0;
pub const VOID_TYPE_ID: usize = 1;
pub const BOOL_TYPE_ID: usize = 2;
pub const I8_TYPE_ID: usize = 3;
pub const I16_TYPE_ID: usize = 4;
pub const I32_TYPE_ID: usize = 5;
pub const I64_TYPE_ID: usize = 6;
pub const U8_TYPE_ID: usize = 7;
pub const U16_TYPE_ID: usize = 8;
pub const U32_TYPE_ID: usize = 9;
pub const U64_TYPE_ID: usize = 10;
pub const F32_TYPE_ID: usize = 11;
pub const F64_TYPE_ID: usize = 12;
pub const CCHAR_TYPE_ID: usize = 13;
pub const CINT_TYPE_ID: usize = 14;
pub const USIZE_TYPE_ID: usize = 15;
// Note: keep STRING_TYPE_ID last as it is how we know how many slots to pre-fill
pub const STRING_TYPE_ID: usize = 16;

pub struct Compiler {
    include_paths: Vec<PathBuf>,
    raw_files: Vec<(String, Vec<u8>)>,
}

impl Compiler {
    pub fn new(include_paths: Vec<PathBuf>) -> Self {
        Self {
            include_paths,
            raw_files: Vec::new(),
        }
    }

    fn include_file(&mut self, fname: &Path) -> (ParsedNamespace, Option<JaktError>) {
        let contents = std::fs::read(fname).unwrap();
        self.raw_files
            .push((fname.to_string_lossy().to_string(), contents));

        let (lexed, err) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );

        if err.is_some() {
            return (ParsedNamespace::new(), err);
        }

        parse_namespace(&lexed, &mut 0, self)
    }

    pub fn find_and_include_module(
        &mut self,
        module_name: &str,
        span: Span,
    ) -> (ParsedNamespace, Option<JaktError>) {
        for path in &self.include_paths {
            let fname = path.join(module_name).with_extension("jakt");
            if fname.exists() {
                return self.include_file(&fname);
            }
        }
        return (
            ParsedNamespace::new(),
            Some(JaktError::ParserError(
                format!("Module '{}' not found", module_name),
                span,
            )),
        );
    }

    pub fn include_prelude(&mut self, project: &mut Project) -> Option<JaktError> {
        let mut error = None;
        // First, let's make types for all the builtin types
        // This order *must* match the order of the constants the typechecker expects
        project.types.resize(STRING_TYPE_ID + 1, Type::Builtin);

        let prelude = Compiler::prelude();

        // Not sure where to put prelude, but we're hoping its parsing is infallible
        self.raw_files.push(("<prelude>".to_string(), prelude));

        // Compile the prelude
        let (lexed, _) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );
        let (file, _) = parse_namespace(&lexed, &mut 0, self);

        // Scope ID 0 is the global project-level scope that all files can see
        error = error.or(typecheck_namespace_predecl(&file, 0, project));
        error = error.or(typecheck_namespace_declarations(&file, 0, project));

        error
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
        let mut project = Project::new();

        let err = self.include_prelude(&mut project);
        if let Some(err) = err {
            return Err(err);
        }

        // TODO: We also want to be able to accept include paths from CLI
        let parent_dir = fname
            .parent()
            .expect("Cannot find parent directory of file");
        self.include_paths.push(parent_dir.to_path_buf());

        let (file, err) = self.include_file(fname);

        if let Some(err) = err {
            return Err(err);
        }

        let scope = Scope::new(Some(0), false);
        project.scopes.push(scope);

        let file_scope_id = project.scopes.len() - 1;

        let err = typecheck_namespace_predecl(&file, file_scope_id, &mut project);
        if let Some(err) = err {
            return Err(err);
        }

        let err = typecheck_namespace_declarations(&file, file_scope_id, &mut project);
        if let Some(err) = err {
            return Err(err);
        }

        if let Some(err) = check_codegen_preconditions(&project) {
            return Err(err);
        }

        // Hardwire to first file for now
        Ok(codegen(&project, &project.scopes[file_scope_id]))
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        &self.raw_files[file_id].1
    }

    pub fn get_file_name(&self, file_id: FileId) -> &String {
        &self.raw_files[file_id].0
    }

    pub fn prelude() -> Vec<u8> {
        include_bytes!("../runtime/prelude.jakt").to_vec()
    }
}

fn check_codegen_preconditions(project: &Project) -> Option<JaktError> {
    // Make sure all functions have a known return type
    for function in &project.functions {
        if function.return_type_id == UNKNOWN_TYPE_ID {
            return Some(JaktError::TypecheckError(
                format!("Could not infer the return type of function '{}', please explicitly specify it",
                function.name),
                function.parsed_function.as_ref().expect("Typechecking non-parsed function").name_span,
            ));
        }
    }

    None
}
