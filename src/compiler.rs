use std::{io::Write, path::Path};

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::lex,
    parser::parse_file,
    typechecker::{typecheck_file, Project, Scope, Type},
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

    pub fn include_prelude(&mut self, project: &mut Project) {
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
        let (file, _) = parse_file(&lexed);

        // Scope ID 0 is the global project-level scope that all files can see
        typecheck_file(&file, 0, project);
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
        let mut project = Project::new();

        self.include_prelude(&mut project);

        let contents = std::fs::read(fname)?;

        self.raw_files
            .push((fname.to_string_lossy().to_string(), contents));

        let (lexed, err) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        let (file, err) = parse_file(&lexed);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        let scope = Scope::new(Some(0));
        project.scopes.push(scope);

        let file_scope_id = project.scopes.len() - 1;

        let err = typecheck_file(&file, file_scope_id, &mut project);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        // Hardwire to first file for now
        Ok(codegen(&project, &project.scopes[file_scope_id]))
    }

    pub fn compile(&mut self, fname: &Path) -> Result<(), JaktError> {
        let cpp_string = self.convert_to_cpp(fname)?;

        let mut out_file = std::fs::File::create("output.cpp")?;
        out_file.write_all(cpp_string.as_bytes())?;

        Ok(())
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        &self.raw_files[file_id].1
    }

    pub fn prelude() -> Vec<u8> {
        r#"
extern class String {
    fun split(this, anon c: c_char) -> [String] {}
    fun characters(this) -> raw c_char {}
    fun to_lowercase(this) -> String {}
    fun to_uppercase(this) -> String {}
    fun is_empty(this) -> bool {}
    fun length(this) -> i64 {}
}

extern class RefVector<T> {
    fun size(this) -> i64 {}
    fun resize(mut this, anon size: i64) {}
    fun pop(mut this) -> T? {}
}

extern class Optional<T> {}

extern class Tuple {}

extern class Range {}

"#
        .as_bytes()
        .to_vec()
    }
}
