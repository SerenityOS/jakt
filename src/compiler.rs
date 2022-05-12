use std::{io::Write, path::Path};

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::lex,
    parser::parse_file,
    typechecker::{typecheck_file, CheckedFile},
};

pub type FileId = usize;

pub struct Compiler {
    raw_files: Vec<(String, Vec<u8>)>,
    checked_files: Vec<(String, CheckedFile)>,
}

impl Compiler {
    pub fn new() -> Self {
        let prelude = Compiler::prelude();
        let mut raw_files = Vec::new();
        let mut checked_files = Vec::new();

        // Not sure where to put prelude, but we're hoping its parsing is infallible
        raw_files.push(("<prelude>".to_string(), prelude));

        // Compile the prelude
        let (lexed, _) = lex(raw_files.len() - 1, &raw_files[raw_files.len() - 1].1);
        let (file, _) = parse_file(&lexed);
        let (file, _) = typecheck_file(&file, &CheckedFile::new());

        checked_files.push(("<prelude>".to_string(), file));
        Self {
            raw_files,
            checked_files,
        }
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
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

        let (file, err) = typecheck_file(&file, &self.checked_files[0].1);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        // TODO: do something with this
        self.checked_files
            .push((fname.to_string_lossy().to_string(), file.clone()));

        Ok(codegen(&file))
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
    fun split(this, anon c: char) -> [String] {}
    fun characters(this) -> raw char {}
    fun to_lowercase(this) -> String {}
    fun to_uppercase(this) -> String {}
    fun is_empty(this) -> bool {}
    fun length(this) -> i64 {}
}

extern class Vector {
    fun size(this) -> i64 {}
}

"#
        .as_bytes()
        .to_vec()
    }
}
