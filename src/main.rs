/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

use std::{io, io::Write, path::PathBuf, process::exit, process::Command};

use pico_args::Arguments;

use jakt::{find_definition_in_project, Compiler, JaktError, Project, Span};

fn main() -> Result<(), JaktError> {
    let arguments = parse_arguments();

    let binary_directory = match &arguments.binary_directory {
        Some(dir) => dir.clone(),
        None => {
            let mut dir = std::env::current_dir().expect("Current directory unusable!");
            dir.push("build");
            dir
        }
    };
    std::fs::create_dir_all(&binary_directory)?;

    let mut compiler = Compiler::new(arguments.include_paths.clone());

    let mut first_error = None;

    if let Some(index) = arguments.goto_def_index {
        let mut project = Project::new();

        for file in &arguments.input_files {
            compiler.check_project(file, &mut project);
        }

        // FIXME: use file_id: 1 for now
        let result = find_definition_in_project(&project, Span::new(1, index, index));

        println!("{{\"start\": {}, \"end\": {}}}", result.start, result.end);
    } else if arguments.check_only {
        let mut project = Project::new();
        for file in &arguments.input_files {
            match compiler.check_project(file, &mut project) {
                (_, Some(err)) => {
                    match &err {
                        JaktError::IOError(ioe) => println!("IO Error: {}", ioe),
                        JaktError::StringError(se) => println!("Error: {}", se),
                        JaktError::ParserError(msg, span) => {
                            display_error(&arguments, &compiler, msg, *span)
                        }
                        JaktError::TypecheckError(msg, span) => {
                            display_error(&arguments, &compiler, msg, *span)
                        }
                        JaktError::ValidationError(msg, span) => {
                            display_error(&arguments, &compiler, msg, *span)
                        }
                        JaktError::TypecheckErrorWithHint(
                            error_msg,
                            error_span,
                            hint_msg,
                            hint_span,
                        )
                        | JaktError::ParserErrorWithHint(
                            error_msg,
                            error_span,
                            hint_msg,
                            hint_span,
                        ) => {
                            display_error(&arguments, &compiler, error_msg, *error_span);
                            display_hint(&arguments, &compiler, hint_msg, *hint_span);
                        }
                    }
                    first_error = first_error.or(Some(err));
                }
                (_, None) => {}
            }
        }
    } else {
        for file in &arguments.input_files {
            match compiler.convert_to_cpp(file) {
                Ok(str) => {
                    let mut out_filepath = binary_directory.clone();
                    out_filepath.push(file.file_name().unwrap());
                    out_filepath.set_extension("cpp");
                    let mut out_file = std::fs::File::create(out_filepath.clone())?;
                    out_file.write_all(str.as_bytes())?;

                    let path_as_string =
                        |path: &PathBuf| path.clone().into_os_string().into_string().unwrap();

                    if arguments.prettify_cpp_source {
                        let cpp_source = path_as_string(&out_filepath);
                        let default_clang_format_path = PathBuf::from("clang-format");
                        let clang_format_output = Command::new(
                            arguments
                                .clang_format_path
                                .as_ref()
                                .unwrap_or(&default_clang_format_path),
                        )
                        .args(["-i", &cpp_source])
                        .output()?;
                        io::stderr().write_all(&clang_format_output.stderr)?;
                    }

                    if !arguments.emit_source_only {
                        let input_cpp = path_as_string(&out_filepath);

                        let output_executable;
                        #[cfg(target_os = "windows")]
                        {
                            output_executable = path_as_string(&out_filepath.with_extension("exe"));
                        }
                        #[cfg(not(target_os = "windows"))]
                        {
                            output_executable = path_as_string(&out_filepath.with_extension(""));
                        }

                        let runtime_path = if let Some(ref runtime_path) = arguments.runtime_path {
                            path_as_string(runtime_path)
                        } else {
                            String::from("runtime")
                        };
                        let default_cxx_compiler_path = PathBuf::from("clang++");
                        let clang_output = Command::new(
                            arguments
                                .cxx_compiler_path
                                .as_ref()
                                .unwrap_or(&default_cxx_compiler_path),
                        )
                        .args([
                            "-fcolor-diagnostics",
                            "-std=c++20",
                            // Don't complain about unsupported -W flags below.
                            "-Wno-unknown-warning-option",
                            // Sometimes our generated C++ has a lot of harmless parentheses.
                            "-Wno-parentheses-equality",
                            // These warnings if enabled create loads of unnecessary noise:
                            "-Wno-unqualified-std-cast-call",
                            "-Wno-user-defined-literals",
                            // This warning can happen for functions like fopen which Windows has deprecated but others not.
                            // Specifically, it will happen if clang uses the MSVC runtime and/or linker.
                            "-Wno-deprecated-declarations",
                            "-I",
                            &runtime_path,
                            &input_cpp,
                            "-o",
                            &output_executable,
                        ])
                        .output()?;
                        io::stderr().write_all(&clang_output.stderr)?;
                    }
                }
                Err(err) => {
                    match &err {
                        JaktError::IOError(ioe) => println!("IO Error: {}", ioe),
                        JaktError::StringError(se) => println!("Error: {}", se),
                        JaktError::ParserError(msg, span) => {
                            display_error(&arguments, &compiler, msg, *span)
                        }
                        JaktError::TypecheckError(msg, span) => {
                            display_error(&arguments, &compiler, msg, *span)
                        }
                        JaktError::ValidationError(msg, span) => {
                            display_error(&arguments, &compiler, msg, *span)
                        }
                        JaktError::TypecheckErrorWithHint(
                            error_msg,
                            error_span,
                            hint_msg,
                            hint_span,
                        )
                        | JaktError::ParserErrorWithHint(
                            error_msg,
                            error_span,
                            hint_msg,
                            hint_span,
                        ) => {
                            display_error(&arguments, &compiler, error_msg, *error_span);
                            display_hint(&arguments, &compiler, hint_msg, *hint_span);
                        }
                    }
                    first_error = first_error.or(Some(err));
                }
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
const USAGE: &str = "usage: jakt [-h,-S] [OPTIONS] [FILES...]";

// FIXME: Once format is stable as a const function, include USAGE in this string.
const HELP: &str = "\
Flags:
  -h,--help                     Print this help and exit.
  -p,--prettify-cpp-source      Run emitted C++ source through clang-format.
  -S,--emit-cpp-source-only     Only emit the generated C++ source, do not compile.
  -c,--check-only               Only check the code for errors
  -j,--json-errors              Emit machine-readable (JSON) errors

Options:
  -o,--binary-dir PATH          Output directory for compiled files.
                                Defaults to $PWD/build.
  -C,--cxx-compiler-path PATH   Path of the C++ compiler to use when compiling the generated sources.
                                Defaults to clang++.
  -F,--clang-format-path PATH   Path to clang-format executable.
                                Defaults to clang-format.
  -R,--runtime-path PATH        Path of the Jakt runtime headers.
                                Defaults to $PWD/runtime.
  -I,--include-path PATH        Add an include path for imported Jakt files.
                                Can be specified multiple times.
  -g,--goto-def INDEX           Return the span for the definition at index.

Arguments:
  FILES...                      List of files to compile. The outputs are
                                `<input-filename>.cpp` in the binary directory.
";

#[derive(Debug)]
struct JaktArguments {
    binary_directory: Option<PathBuf>,
    input_files: Vec<PathBuf>,
    include_paths: Vec<PathBuf>,
    emit_source_only: bool,
    check_only: bool,
    json_errors: bool,
    goto_def_index: Option<usize>,
    cxx_compiler_path: Option<PathBuf>,
    prettify_cpp_source: bool,
    clang_format_path: Option<PathBuf>,
    runtime_path: Option<PathBuf>,
}

/// Exits if the arguments are invalid or the user doesn't want to run Jakt (e.g. help output)
fn parse_arguments() -> JaktArguments {
    let mut pico_arguments = Arguments::from_env();
    if pico_arguments.contains(["-h", "--help"]) {
        println!("{}\n\n{}", USAGE, HELP);
        exit(0);
    }
    let emit_source_only = pico_arguments.contains(["-S", "--emit-cpp-source-only"]);
    let prettify_cpp_source = pico_arguments.contains(["-p", "--prettify-cpp-source"]);

    let check_only = pico_arguments.contains(["-c", "--check-only"]);
    let json_errors = pico_arguments.contains(["-j", "--json-errors"]);

    let convert_to_pathbuf = |s: &str| -> Result<PathBuf, &'static str> { Ok(s.into()) };
    let include_paths = pico_arguments
        .values_from_fn(["-I", "--include-path"], convert_to_pathbuf)
        .unwrap_or_default();

    let mut arguments = JaktArguments {
        binary_directory: None,
        input_files: Vec::new(),
        include_paths,
        emit_source_only,
        check_only,
        json_errors,
        goto_def_index: None,
        cxx_compiler_path: None,
        prettify_cpp_source,
        clang_format_path: None,
        runtime_path: None,
    };

    let mut get_path_arg = |keys| {
        pico_arguments
            .opt_value_from_os_str(keys, |s| -> Result<PathBuf, &'static str> { Ok(s.into()) })
    };

    if let Ok(binary_directory) = get_path_arg(["-o", "--binary-dir"]) {
        arguments.binary_directory = binary_directory;
    }

    if let Ok(cxx_compiler_path) = get_path_arg(["-C", "--cxx-compiler-path"]) {
        arguments.cxx_compiler_path = cxx_compiler_path;
    }

    if let Ok(clang_format_path) = get_path_arg(["-F", "--clang-format-path"]) {
        arguments.clang_format_path = clang_format_path;
    }

    if let Ok(runtime_path) = get_path_arg(["-R", "--runtime-path"]) {
        arguments.runtime_path = runtime_path;
    }

    if let Ok(Some(index)) = get_path_arg(["-g", "--goto-def"]) {
        if let Ok(val) = index.to_string_lossy().parse::<usize>() {
            arguments.goto_def_index = Some(val);
        }
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

#[derive(Debug)]
enum MessageSeverity {
    Hint,
    Error,
}

impl MessageSeverity {
    pub fn name(&self) -> String {
        match self {
            MessageSeverity::Hint => "Hint".to_string(),
            MessageSeverity::Error => "Error".to_string(),
        }
    }

    pub fn ansi_color_code(&self) -> String {
        match self {
            MessageSeverity::Hint => "94".to_string(),  // Bright Blue
            MessageSeverity::Error => "31".to_string(), // Red
        }
    }
}

fn display_message_with_span(
    severity: MessageSeverity,
    compiler: &Compiler,
    msg: &str,
    span: Span,
) {
    println!("{}: {}", severity.name(), msg);

    let file_contents = compiler.get_file_contents(span.file_id);
    let file_name = compiler.get_file_name(span.file_id);

    let line_spans = line_spans(file_contents);

    let mut line_index = 0;
    let largest_line_number = line_spans.len();

    let width = format!("{}", largest_line_number).len();

    while line_index < line_spans.len() {
        if span.start >= line_spans[line_index].0 && span.start <= line_spans[line_index].1 {
            let column_index = span.start - line_spans[line_index].0;
            println!(
                "{} \u{001b}[33m{}:{}:{}\u{001b}[0m",
                "-".repeat(width + 3),
                file_name,
                line_index + 1,
                column_index + 1
            );
            if line_index > 0 {
                print_source_line(
                    &severity,
                    file_contents,
                    line_spans[line_index - 1],
                    span,
                    line_index - 1,
                    largest_line_number,
                );
            }
            print_source_line(
                &severity,
                file_contents,
                line_spans[line_index],
                span,
                line_index,
                largest_line_number,
            );

            print!(
                "{}",
                " ".repeat(span.start - line_spans[line_index].0 + width + 4)
            );
            println!(
                "\u{001b}[{}m^- {}\u{001b}[0m",
                severity.ansi_color_code(),
                msg
            );

            while line_index < line_spans.len() && span.end > line_spans[line_index].0 {
                line_index += 1;
                if line_index >= line_spans.len() {
                    break;
                }
                print_source_line(
                    &severity,
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

    println!("\u{001b}[0m{}", "-".repeat(width + 3));
}

fn display_message_with_span_json(severity: MessageSeverity, msg: &str, span: Span) {
    println!(
        "{{\"message\": \"{}\", \"severity\": \"{:?}\", \"span\": {{\"start\": {}, \"end\": {}}}}}",
        msg, severity, span.start, span.end
    );
}

fn display_error(arguments: &JaktArguments, compiler: &Compiler, msg: &str, span: Span) {
    if arguments.json_errors {
        display_message_with_span_json(MessageSeverity::Error, msg, span)
    } else {
        display_message_with_span(MessageSeverity::Error, compiler, msg, span)
    }
}

fn display_hint(arguments: &JaktArguments, compiler: &Compiler, msg: &str, span: Span) {
    if arguments.json_errors {
        display_message_with_span_json(MessageSeverity::Hint, msg, span)
    } else {
        display_message_with_span(MessageSeverity::Hint, compiler, msg, span)
    }
}

fn print_source_line(
    severity: &MessageSeverity,
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

            print!("\u{001b}[{}m{}", severity.ansi_color_code(), c as char)
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
