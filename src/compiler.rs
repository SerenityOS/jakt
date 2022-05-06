use std::{io::Write, path::Path};

use crate::{
    codegen::translate,
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
        Self {
            raw_files: Vec::new(),
            checked_files: Vec::new(),
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

        let (file, err) = typecheck_file(&file);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        // TODO: do something with this
        self.checked_files
            .push((fname.to_string_lossy().to_string(), file.clone()));

        Ok(translate(&file))
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
}
