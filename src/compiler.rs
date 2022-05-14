use std::{io::Write, path::Path};

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::lex,
    parser::parse_file,
    typechecker::{typecheck_file, Project, ScopeStack},
};

pub type FileId = usize;

pub struct Compiler {
    raw_files: Vec<(String, Vec<u8>)>,
}

impl Compiler {
    pub fn new() -> Self {
        Self {
            raw_files: Vec::new(),
        }
    }

    pub fn include_prelude(&mut self, project: &mut Project, stack: &mut ScopeStack) {
        let prelude = Compiler::prelude();

        // Not sure where to put prelude, but we're hoping its parsing is infallible
        self.raw_files.push(("<prelude>".to_string(), prelude));

        // Compile the prelude
        let (lexed, _) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );
        let (file, _) = parse_file(&lexed);

        typecheck_file(&file, stack, project);
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
        let mut project = Project::new();
        let mut stack = ScopeStack::new();

        self.include_prelude(&mut project, &mut stack);

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

        let err = typecheck_file(&file, &mut stack, &mut project);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        Ok(codegen(
            &project,
            stack
                .frames
                .first()
                .expect("internal error: missing global scope"),
        ))
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

extern class RefVector {
    fun size(this) -> i64 {}
    fun resize(mut this, anon size: u64) {}
}

"#
        .as_bytes()
        .to_vec()
    }
}
