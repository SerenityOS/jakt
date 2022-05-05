use std::io::Write;

use crate::{
    codegen::translate,
    error::JaktError,
    lexer::lex,
    parser::{parse_file, ParsedFile},
};

pub type FileId = usize;

pub struct Compiler {
    raw_files: Vec<(String, Vec<u8>)>,
    parsed_files: Vec<(String, ParsedFile)>,
}

impl Compiler {
    pub fn new() -> Self {
        Self {
            raw_files: Vec::new(),
            parsed_files: Vec::new(),
        }
    }

    pub fn compile(&mut self, fname: &str) -> Result<(), JaktError> {
        let contents = std::fs::read(fname)?;

        self.raw_files.push((fname.to_string(), contents));

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

        let cpp_file = translate(&file);

        let mut out_file = std::fs::File::create("output.cpp")?;
        out_file.write_all(cpp_file.as_bytes())?;

        // TODO: do something with this
        self.parsed_files.push((fname.to_string(), file));

        Ok(())
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        &self.raw_files[file_id].1
    }
}
