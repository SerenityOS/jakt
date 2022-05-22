use std::{path::PathBuf, process::exit};

use pico_args::Arguments;

use jakt::{Compiler, JaktError, Span};

fn main() -> Result<(), JaktError> {
    let arguments = parse_arguments();

    let mut compiler = Compiler::new();
    let mut first_error = None;

    for file in arguments.input_files {
        match compiler.compile(&file) {
            Ok(_) => {}
            Err(err) => {
                match &err {
                    JaktError::IOError(ioe) => println!("IO Error: {}", ioe),
                    JaktError::ParserError(msg, span) => display_error(&compiler, msg, *span),
                    JaktError::TypecheckError(msg, span) => display_error(&compiler, msg, *span),
                    JaktError::ValidationError(msg, span) => display_error(&compiler, msg, *span),
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

/// Make sure to keep these up-to-date if you're adding arguments.
const USAGE: &str = "usage: jakt [-h] [FILES...]";

// FIXME: Once format is stable as a const function, include USAGE in this string.
const HELP: &str = "\
Flags:
  -h, --help           Print this help and exit 

Options:
  FILES...             List of files to compile. The output is `output.cpp`
                       in the cwd.
";

#[derive(Debug)]
struct JaktArguments {
    input_files: Vec<PathBuf>,
}

/// Exits if the arguments are invalid or the user doesn't want to run Jakt (e.g. help output)
fn parse_arguments() -> JaktArguments {
    let mut pico_arguments = Arguments::from_env();
    if pico_arguments.contains(["-h", "--help"]) {
        println!("{}\n\n{}", USAGE, HELP);
        exit(0);
    }

    let mut arguments = JaktArguments {
        input_files: Vec::new(),
    };

    while let Ok(filename) = pico_arguments.free_from_str::<PathBuf>() {
        if !filename.exists() {
            eprintln!(
                "jakt: error: file '{}' not found or inaccessible",
                filename.to_string_lossy()
            );
            exit(1);
        }
        arguments.input_files.push(filename);
    }

    let extra_arguments = pico_arguments.finish();
    if !extra_arguments.is_empty() {
        eprintln!(
            "jakt: error: extra arguments {}",
            extra_arguments
                .iter()
                .map(|os_string| format!("'{}'", os_string.to_string_lossy()))
                .collect::<Vec<_>>()
                .join(", ")
        )
    } else if arguments.input_files.is_empty() {
        println!("{}", USAGE);
        exit(0);
    }

    arguments
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
    println!();
    println!("\u{001b}[0m-----");
}
