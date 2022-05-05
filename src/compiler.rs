use std::io::Write;

use crate::{
    error::JaktError,
    lexer::lex,
    parser::{parse_file, Block, Expression, Function, ParsedFile},
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

        let lexed = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        )?;

        let file = parse_file(&lexed)?;

        let cpp_file = self.translate(&file);

        let mut out_file = std::fs::File::create("output.cpp")?;
        out_file.write_all(cpp_file.as_bytes())?;

        // TODO: do something with this
        self.parsed_files.push((fname.to_string(), file));

        Ok(())
    }

    fn translate(&self, file: &ParsedFile) -> String {
        let mut output = String::new();

        output.push_str("#include<stdio.h>\n");

        for fun in &file.funs {
            let fun_output = self.translate_function(fun);

            output.push_str(&fun_output);
            output.push('\n');
        }

        output
    }

    fn translate_function(&self, fun: &Function) -> String {
        let mut output = String::new();

        output.push_str("void ");
        output.push_str(&fun.name);
        output.push_str("()");

        let block = self.translate_block(&fun.block);
        output.push_str(&block);

        output
    }

    fn translate_block(&self, block: &Block) -> String {
        let mut output = String::new();

        output.push_str("{\n");

        for expr in &block.stmts {
            let expr = self.translate_expr(expr);

            output.push_str(&expr);
            output.push_str(";\n");
        }

        output.push_str("}\n");

        output
    }

    fn translate_expr(&self, expr: &Expression) -> String {
        let mut output = String::new();

        match expr {
            Expression::QuotedString(qs) => {
                output.push('"');
                output.push_str(qs);
                output.push('"');
            }
            Expression::Call(call) => {
                if call.name == "print" {
                    output.push_str("printf");
                } else {
                    output.push_str(&call.name);
                }
                output.push('(');
                for param in &call.params {
                    output.push_str(&self.translate_expr(&param.1));
                }
                output.push(')');
            }
        }

        output
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        &self.raw_files[file_id].1
    }
}
