use std::path::Path;

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::lex,
    parser::parse_namespace,
    typechecker::{typecheck_namespace, Project, Scope, Type},
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
    raw_files: Vec<(String, Vec<u8>)>,
}

impl Compiler {
    pub fn new() -> Self {
        Self {
            raw_files: Vec::new(),
        }
    }

    pub fn include_prelude(&mut self, project: &mut Project) -> Option<JaktError> {
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
        let (file, _) = parse_namespace(&lexed, &mut 0);

        // Scope ID 0 is the global project-level scope that all files can see
        typecheck_namespace(&file, 0, project)
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
        let mut project = Project::new();

        let err = self.include_prelude(&mut project);
        if let Some(err) = err {
            return Err(err);
        }

        let contents = std::fs::read(fname)?;

        self.raw_files
            .push((fname.to_string_lossy().to_string(), contents));

        let (lexed, err) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );

        if let Some(err) = err {
            return Err(err);
        }

        let (file, err) = parse_namespace(&lexed, &mut 0);

        if let Some(err) = err {
            return Err(err);
        }

        let scope = Scope::new(Some(0));
        project.scopes.push(scope);

        let file_scope_id = project.scopes.len() - 1;

        let err = typecheck_namespace(&file, file_scope_id, &mut project);

        if let Some(err) = err {
            return Err(err);
        }

        // Hardwire to first file for now
        Ok(codegen(&project, &project.scopes[file_scope_id]))
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        &self.raw_files[file_id].1
    }

    pub fn prelude() -> Vec<u8> {
        include_bytes!("../runtime/prelude.jakt").to_vec()
    }
}
