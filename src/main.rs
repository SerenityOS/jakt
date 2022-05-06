use std::path::PathBuf;

use jakt::{Compiler, JaktError, Span};

fn main() -> Result<(), JaktError> {
    let mut parser = Compiler::new();

    for arg in std::env::args_os().skip(1) {
        match parser.compile(&PathBuf::from(&arg)) {
            Ok(_) => {
                println!("success");
            }
            Err(err) => match err {
                JaktError::IOError(ioe) => println!("IO Error: {}", ioe),
                JaktError::ParserError(msg, span) => display_error(&parser, &msg, span),
                JaktError::TypecheckError(msg, span) => display_error(&parser, &msg, span),
            },
        }
    }

    Ok(())
}

fn display_error(parser: &Compiler, msg: &str, span: Span) {
    println!("Error: {}", msg);
    println!("-----");

    let file_contents = parser.get_file_contents(span.file_id);

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
