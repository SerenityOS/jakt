/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#[macro_use]
extern crate lazy_static;

use std::path::PathBuf;
use std::{env::temp_dir, ffi::OsString, fs::create_dir, io::Write, process::Command};

use jakt::{Compiler, JaktError};

static COMMON_ARGS: &[&str] = &[
    "-I",
    ".",
    "-I",
    "runtime",
    "-std=c++20",
    "-Wno-user-defined-literals",
    "-Wno-unqualified-std-cast-call",
    "-DJAKT_CONTINUE_ON_PANIC",
];

lazy_static! {
    static ref PCH_FILENAME: OsString = {
        let mut pch_filename = temp_dir();
        pch_filename.push(format!("Jakt-{}", uuid::Uuid::new_v4()));
        create_dir(&pch_filename).expect("Failed to create temporary directory for PCH.");
        pch_filename.push("lib.h.pch");

        let status = Command::new("clang++")
            .arg("-x")
            .arg("c++-header")
            .arg("runtime/lib.h")
            .arg("-o")
            .arg(&pch_filename)
            .arg("-fpch-instantiate-templates")
            .args(COMMON_ARGS)
            .status()
            .expect("Failed to launch compiler for PCH generation.");

        assert!(status.success(), "PCH generation should succeed.");

        pch_filename.into_os_string()
    };
}

fn parse_quoted_string(s: &str) -> Result<String, JaktError> {
    let s = s.trim();
    if !s.starts_with('"') || !s.ends_with('"') {
        return Err(JaktError::StringError("Expected quoted string".into()));
    }

    let data = &s[1..s.len() - 1];
    let mut result = String::new();
    let mut last_index = 0;
    for (i, _) in data.match_indices('\\') {
        result.push_str(&data[last_index..i]);
        let escaped_char = data
            .get(i + 1..i + 2)
            .ok_or(JaktError::StringError(format!(
                "Expected escaped character at offset {}",
                i
            )))?;
        match escaped_char {
            "\"" => result.push('"'),
            "\\" => result.push('\\'),
            "a" => result.push('\x07'),
            "b" => result.push('\x08'),
            "f" => result.push('\x0c'),
            "n" => result.push('\n'),
            "r" => result.push('\r'),
            "t" => result.push('\t'),
            "v" => result.push('\x0b'),
            c => {
                return Err(JaktError::StringError(format!(
                    "Unknown escape sequence: \\{}",
                    c
                )))
            }
        }
        last_index = i + 2;
    }

    result.push_str(&data[last_index..]);

    Ok(result)
}

fn find_results(
    path: &PathBuf,
) -> Result<(Option<String>, Option<String>, Option<String>), JaktError> {
    let mut output = None;
    let mut error = None;
    let mut stderr = None;

    if let Ok(contents) = std::fs::read_to_string(path) {
        let contents = contents.replace("\r\n", "\n");
        let lines = contents.lines();
        let expect_lines = lines.take_while(|line| line.starts_with("/// "));

        static SEEN_MARKER: i32 = 1;
        static SEEN_OUTPUT: i32 = 2;
        static SEEN_ERROR: i32 = 4;
        static SEEN_STDERR: i32 = 8;

        let mut state = 0;
        for line in expect_lines {
            if state & SEEN_MARKER == 0 {
                if line.starts_with("/// Expect:") {
                    state |= SEEN_MARKER;
                    if line
                        .split_once(':')
                        .unwrap()
                        .1
                        .trim_start()
                        .starts_with("Skip")
                    {
                        // Not a test.
                        return Ok((None, None, None));
                    }
                    continue;
                } else {
                    break;
                }
            }

            if state & SEEN_OUTPUT == 0 && line.starts_with("/// - output: ") {
                output = Some(parse_quoted_string(
                    line.trim_start_matches("/// - output: "),
                )?);
                state |= SEEN_OUTPUT;
                continue;
            }

            if state & SEEN_ERROR == 0 && line.starts_with("/// - error: ") {
                error = Some(parse_quoted_string(
                    line.trim_start_matches("/// - error: "),
                )?);
                state |= SEEN_ERROR;
                continue;
            }

            if state & SEEN_STDERR == 0 && line.starts_with("/// - stderr: ") {
                stderr = Some(parse_quoted_string(
                    line.trim_start_matches("/// - stderr: "),
                )?);
                state |= SEEN_STDERR;
                continue;
            }

            break;
        }
    }

    if output.is_none() && error.is_none() && stderr.is_none() {
        let mut output_path = path.clone();
        output_path.set_extension("out");

        let mut error_output_path = path.clone();
        error_output_path.set_extension("error");

        let mut stderr_output_path = path.clone();
        stderr_output_path.set_extension("error_out");

        if output_path.exists() {
            output = Some(std::fs::read_to_string(&output_path)?.replace("\r\n", "\n"));
        }

        if error_output_path.exists() {
            error = Some(std::fs::read_to_string(&error_output_path)?.replace("\r\n", "\n"));
        }

        if stderr_output_path.exists() {
            stderr = Some(std::fs::read_to_string(&stderr_output_path)?.replace("\r\n", "\n"));
        }
    }

    Ok((output, error, stderr))
}

fn test_samples(path: &str) -> Result<(), JaktError> {
    for sample in std::fs::read_dir(path).expect("if this fails, the repo or harness is broken") {
        let sample = sample.expect("if this fails, the filesytem is having issues");

        let path = sample.path();

        if let Some(ext) = path.extension() {
            if ext == "jakt" {
                // Great, we found a test file
                let (expected_output, expected_error, expected_stderr) = find_results(&path)?;

                if expected_output.is_none()
                    && expected_error.is_none()
                    && expected_stderr.is_none()
                {
                    // No expectations, skip it
                    continue;
                }

                // We have an output to compare to, let's do it.
                let mut compiler = Compiler::new(Vec::new());
                let cpp_string = compiler.convert_to_cpp(&path);

                let cpp_string = match cpp_string {
                    Ok(cpp_string) => {
                        if expected_error.is_some() {
                            let expected_error_msg = expected_error.unwrap();
                            let expected_error_msg = expected_error_msg.replace('\r', "");
                            let expected_error_msg = expected_error_msg.replace('\n', "");

                            panic!(
                                "\r\nTest: {:?}\r\nExpected error not created: {}",
                                path, expected_error_msg,
                            );
                        }
                        cpp_string
                    }
                    Err(err) => {
                        if expected_error.is_some() {
                            let expected_error_msg = expected_error.unwrap();
                            let expected_error_msg = expected_error_msg.replace('\r', "");
                            let expected_error_msg = expected_error_msg.replace('\n', "");

                            let returned_error = format!("{:#?}", err);

                            assert!(
                                returned_error.contains(&expected_error_msg),
                                "\r\nTest: {:?}\r\nReturned error: {}\r\nExpected error: {}",
                                path,
                                returned_error,
                                expected_error_msg,
                            );
                            continue;
                        } else {
                            println!("Test failed: {:?}", path);
                            return Err(err);
                        }
                    }
                };

                let uuid = uuid::Uuid::new_v4();

                let mut cpp_filename = temp_dir();
                cpp_filename.push(format!("output{}.cpp", uuid));

                {
                    let mut cpp_file = std::fs::File::create(&cpp_filename)?;
                    cpp_file.write_all(cpp_string.as_bytes())?;
                }

                let mut exe_name = temp_dir();
                exe_name.push(format!("output{}", uuid));

                let status = Command::new("clang++")
                    .arg(&cpp_filename)
                    .arg("-o")
                    .arg(&exe_name)
                    .arg("-include-pch")
                    .arg(&*PCH_FILENAME)
                    .args(COMMON_ARGS)
                    .output()?;

                if !status.status.success() {
                    println!("{}", String::from_utf8_lossy(&status.stdout));
                    println!("{}", String::from_utf8_lossy(&status.stderr));
                }
                assert!(status.status.success());

                let binary_run = Command::new(&exe_name).output()?;

                let binary_output = String::from_utf8_lossy(&binary_run.stdout).to_string();
                let binary_output = binary_output.replace("\r\n", "\n");

                let binary_stderr_output = String::from_utf8_lossy(&binary_run.stderr).to_string();
                let binary_stderr_output = binary_stderr_output.replace("\r\n", "\n");

                let baseline_text = expected_output;
                let baseline_text = baseline_text.map(|text| text.replace("\r\n", "\n"));

                let baseline_stderr_text = expected_stderr;
                let baseline_stderr_text =
                    baseline_stderr_text.map(|text| text.replace("\r\n", "\n"));

                let mut stderr_checked = false;
                if let Some(baseline_stderr_text) = baseline_stderr_text {
                    assert!(
                        // Because runtime assertion text depends on file name, C++ library line names etc., the exact stderr text is both unpredictable and volatile.
                        // Therefore, stderr checks allow to only check for some substring of the actual output,
                        // where we can e.g. put in the exact assertion text we are checking for.
                        // This is still vulnerable to changes in the assertion expression, but we do need to check for something.
                        // It looks like the best solution right now.
                        binary_stderr_output.contains(&baseline_stderr_text),
                        "\r\n Test (stderr): {}",
                        path.to_string_lossy()
                    );
                    stderr_checked = true;
                }

                // If we checked stderr, we're not required to check stdout.
                if !stderr_checked && baseline_text.is_some() {
                    assert_eq!(
                        binary_output,
                        baseline_text.unwrap(),
                        "\r\nTest: {}",
                        path.to_string_lossy()
                    );
                }
            }
        }
    }

    Ok(())
}

#[test]
fn test_basics() -> Result<(), JaktError> {
    test_samples("samples/basics")
}

#[test]
fn test_control_flow() -> Result<(), JaktError> {
    test_samples("samples/control_flow")
}

#[test]
fn test_functions() -> Result<(), JaktError> {
    test_samples("samples/functions")
}

#[test]
fn test_math() -> Result<(), JaktError> {
    test_samples("samples/math")
}

#[test]
fn test_variables() -> Result<(), JaktError> {
    test_samples("samples/variables")
}

#[test]
fn test_arrays() -> Result<(), JaktError> {
    test_samples("samples/arrays")
}

#[test]
fn test_strings() -> Result<(), JaktError> {
    test_samples("samples/strings")
}

#[test]
fn test_optional() -> Result<(), JaktError> {
    test_samples("samples/optional")
}

#[test]
fn test_tuples() -> Result<(), JaktError> {
    test_samples("samples/tuples")
}

#[test]
fn test_structs() -> Result<(), JaktError> {
    test_samples("samples/structs")
}

#[test]
fn test_classes() -> Result<(), JaktError> {
    test_samples("samples/classes")
}

#[test]
fn test_pointers() -> Result<(), JaktError> {
    test_samples("samples/pointers")
}

#[test]
fn test_boolean() -> Result<(), JaktError> {
    test_samples("samples/boolean")
}

#[test]
fn test_ranges() -> Result<(), JaktError> {
    test_samples("samples/ranges")
}

#[test]
fn test_dictionaries() -> Result<(), JaktError> {
    test_samples("samples/dictionaries")
}

#[test]
fn test_generics() -> Result<(), JaktError> {
    test_samples("samples/generics")
}

#[test]
fn test_enums() -> Result<(), JaktError> {
    test_samples("samples/enums")
}

#[test]
fn test_inline_cpp() -> Result<(), JaktError> {
    test_samples("samples/inline_cpp")
}

#[test]
fn test_parser() -> Result<(), JaktError> {
    test_samples("tests/parser")
}

#[test]
fn test_typechecker() -> Result<(), JaktError> {
    test_samples("tests/typechecker")
}

#[test]
fn test_sets() -> Result<(), JaktError> {
    test_samples("samples/sets")
}

#[test]
fn test_namespaces() -> Result<(), JaktError> {
    test_samples("samples/namespaces")
}

#[test]
fn test_weak() -> Result<(), JaktError> {
    test_samples("samples/weak")
}

#[test]
fn test_codegen() -> Result<(), JaktError> {
    test_samples("tests/codegen")
}

#[test]
fn test_match() -> Result<(), JaktError> {
    test_samples("samples/match")
}

#[test]
fn test_imports() -> Result<(), JaktError> {
    test_samples("samples/imports")
}

#[test]
fn test_modules() -> Result<(), JaktError> {
    test_samples("samples/modules")
}

#[test]
fn test_selfhost() -> Result<(), JaktError> {
    test_samples("selfhost")
}

#[test]
fn test_apps() -> Result<(), JaktError> {
    test_samples("samples/apps")
}
