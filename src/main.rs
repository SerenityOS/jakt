use std::path::PathBuf;

use jakt::{Compiler, JaktError, Span};

fn main() -> Result<(), JaktError> {
    let mut compiler = Compiler::new();
    let mut first_error = None;

    for arg in std::env::args_os().skip(1) {
        match compiler.compile(&PathBuf::from(&arg)) {
            Ok(_) => {
                println!("success");
            }
            Err(err) => {
                match &err {
                    JaktError::IOError(ioe) => println!("IO Error: {}", ioe),
                    JaktError::ParserError(msg, span) => display_error(&compiler, &msg, *span),
                    JaktError::TypecheckError(msg, span) => display_error(&compiler, &msg, *span),
                    JaktError::ValidationError(msg, span) => display_error(&compiler, &msg, *span),
                }
                first_error = first_error.or(Some(err));
            }
        }
    }

    if let Some(error) = first_error {
        Err(error)
    } else {
        Ok(())
    }
}

fn display_error(compiler: &Compiler, msg: &str, span: Span) {
    println!("Error: {}", msg);
    println!("-----");

    let file_contents = compiler.get_file_contents(span.file_id);

    let mut index = 0;

    while index <= file_contents.len() {
        let c;
        if index < file_contents.len() {
            c = file_contents[index];
        } else if span.start == span.end && index == span.start {
            c = b'_';
        } else {
            c = b' ';
        }

        if (index >= span.start && index < span.end)
            || (span.start == span.end && index == span.start)
        {
            // In the error span

            print!("\u{001b}[31m{}", c as char)
        } else {
            print!("\u{001b}[0m{}", c as char)
        }
        index += 1;
    }
    println!("");
    println!("\u{001b}[0m-----");
}
