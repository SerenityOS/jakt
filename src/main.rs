use std::{io::Write, path::PathBuf, process::exit};

use pico_args::Arguments;

use jakt::{Compiler, JaktError, Span};

fn main() -> Result<(), JaktError> {
    let arguments = parse_arguments();

    let binary_directory = match arguments.binary_directory {
        Some(dir) => dir,
        None => {
            let mut dir = std::env::current_dir().expect("Current directory unusable!");
            dir.push("build");
            dir
        }
    };
    std::fs::create_dir_all(&binary_directory)?;

    let mut compiler = Compiler::new();

    let mut first_error = None;

    for file in arguments.input_files {
        match compiler.convert_to_cpp(&file) {
            Ok(str) => {
                let mut out_filepath = binary_directory.clone();
                out_filepath.push(file.file_name().unwrap());
                out_filepath.set_extension("cpp");
                let mut out_file = std::fs::File::create(out_filepath)?;
                out_file.write_all(str.as_bytes())?;
            }
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

    if first_error.is_some() {
        std::process::exit(1)
    } else {
        Ok(())
    }
}

/// Make sure to keep these up-to-date if you're adding arguments.
const USAGE: &str = "usage: jakt [-h] [OPTIONS] [FILES...]";

// FIXME: Once format is stable as a const function, include USAGE in this string.
const HELP: &str = "\
Flags:
  -h,--help              Print this help and exit

Options:
  -o,--binary-dir PATH   Output directory for compiled files.
                         Defaults to $PWD/build.

Arguments:
  FILES...               List of files to compile. The outputs are
                         `<input-filename>.cpp` in the binary directory.
";

#[derive(Debug)]
struct JaktArguments {
    binary_directory: Option<PathBuf>,
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
        binary_directory: None,
        input_files: Vec::new(),
    };

    if let Ok(binary_directory) = pico_arguments.opt_value_from_os_str(
        ["-o", "--binary-dir"],
        |s| -> Result<PathBuf, &'static str> { Ok(s.into()) },
    ) {
        arguments.binary_directory = binary_directory;
    }

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

    let file_contents = compiler.get_file_contents(span.file_id);

    let line_spans = line_spans(file_contents);

    let mut line_index = 0;
    let largest_line_number = line_spans.len();

    let width = format!("{}", largest_line_number).len();
    println!("{}", "-".repeat(width + 3));

    while line_index < line_spans.len() {
        if span.start >= line_spans[line_index].0 && span.start < line_spans[line_index].1 {
            if line_index > 0 {
                print_source_line(
                    file_contents,
                    line_spans[line_index - 1],
                    span,
                    line_index - 1,
                    largest_line_number,
                );
            }
            print_source_line(
                file_contents,
                line_spans[line_index],
                span,
                line_index,
                largest_line_number,
            );

            print!(
                "{}",
                " ".repeat(line_spans[line_index].1 - line_spans[line_index].0 + width + 2)
            );
            println!("\u{001b}[31m^- {}\u{001b}[0m", msg);

            while line_index < line_spans.len() && span.end > line_spans[line_index].0 {
                line_index += 1;
                if line_index >= line_spans.len() {
                    break;
                }
                print_source_line(
                    file_contents,
                    line_spans[line_index],
                    span,
                    line_index,
                    largest_line_number,
                );
            }

            break;
        } else {
            line_index += 1
        }
    }

    if span.start == span.end && span.start == file_contents.len() && line_index > 0 {
        print_source_line(
            file_contents,
            line_spans[line_index - 1],
            span,
            line_index - 1,
            largest_line_number,
        );
    }

    println!("\u{001b}[0m{}", "-".repeat(width + 3));
}

fn print_source_line(
    file_contents: &[u8],
    file_span: (usize, usize),
    error_span: Span,
    line_number: usize,
    largest_line_number: usize,
) {
    let mut index = file_span.0;

    let width = format!("{}", largest_line_number).len();

    print!(" {:<width$} | ", line_number);
    while index <= file_span.1 {
        let c;
        if index < file_span.1 {
            c = file_contents[index];
        } else if error_span.start == error_span.end && index == error_span.start {
            c = b'_';
        } else {
            c = b' ';
        }

        if (index >= error_span.start && index < error_span.end)
            || (error_span.start == error_span.end && index == error_span.start)
        {
            // In the error span

            print!("\u{001b}[31m{}", c as char)
        } else {
            print!("\u{001b}[0m{}", c as char)
        }
        index += 1;
    }
    println!();
}

fn line_spans(contents: &[u8]) -> Vec<(usize, usize)> {
    let mut idx = 0;
    let mut output = vec![];

    let mut start = idx;
    while idx < contents.len() {
        if contents[idx] == b'\n' {
            output.push((start, idx));
            start = idx + 1;
        }
        idx += 1;
    }
    if start < idx {
        output.push((start, idx));
    }

    output
}
