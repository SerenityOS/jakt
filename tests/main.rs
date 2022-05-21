use std::{env::temp_dir, io::Write, process::Command};

use jakt::{Compiler, JaktError};

fn test_samples(path: &str) -> Result<(), JaktError> {
    for sample in std::fs::read_dir(path).expect("if this fails, the repo or harness is broken") {
        let sample = sample.expect("if this fails, the filesytem is having issues");

        let path = sample.path();

        if let Some(ext) = path.extension() {
            if ext == "jakt" {
                // Great, we found test file
                let mut output_path = path.clone();
                output_path.set_extension("out");

                let mut error_output_path = path.clone();
                error_output_path.set_extension("error");

                let mut stderr_output_path = path.clone();
                stderr_output_path.set_extension("error_out");

                if output_path.exists() || error_output_path.exists() || stderr_output_path.exists()
                {
                    // We have an output to compare to, let's do it.
                    let mut compiler = Compiler::new();
                    let cpp_string = compiler.convert_to_cpp(&path);

                    let cpp_string = match cpp_string {
                        Ok(cpp_string) => {
                            if error_output_path.exists() {
                                let expected_error_msg =
                                    std::fs::read_to_string(&error_output_path)?;
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
                            if error_output_path.exists() {
                                let expected_error_msg =
                                    std::fs::read_to_string(&error_output_path)?;
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

                    let pwd = std::env::current_dir()?;

                    let mut runtime_dir = std::env::current_dir()?;
                    runtime_dir.push("runtime");

                    let mut exe_name = temp_dir();
                    exe_name.push(format!("output{}", uuid));

                    let status = Command::new("clang++")
                        .arg(&cpp_filename)
                        .arg("-I")
                        .arg(pwd)
                        .arg("-I")
                        .arg(runtime_dir)
                        .arg("-o")
                        .arg(&exe_name)
                        .arg("-std=c++20")
                        .arg("-Wno-user-defined-literals")
                        .arg("-DJAKT_CONTINUE_ON_PANIC")
                        .output()?;

                    if !status.status.success() {
                        println!("{}", String::from_utf8_lossy(&status.stdout));
                        println!("{}", String::from_utf8_lossy(&status.stderr));
                    }
                    assert!(status.status.success());

                    let binary_run = Command::new(&exe_name).output()?;

                    let binary_output = String::from_utf8_lossy(&binary_run.stdout).to_string();
                    let binary_output = binary_output.replace("\r\n", "\n");

                    let binary_stderr_output =
                        String::from_utf8_lossy(&binary_run.stderr).to_string();
                    let binary_stderr_output = binary_stderr_output.replace("\r\n", "\n");

                    let baseline_text = std::fs::read_to_string(&output_path);
                    let baseline_text =
                        baseline_text.and_then(|text| Ok(text.replace("\r\n", "\n")));

                    let baseline_stderr_text = std::fs::read_to_string(&stderr_output_path);
                    let baseline_stderr_text =
                        baseline_stderr_text.and_then(|text| Ok(text.replace("\r\n", "\n")));

                    let mut stderr_checked = false;
                    if let Ok(baseline_stderr_text) = baseline_stderr_text {
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
                    if !stderr_checked || baseline_text.is_ok() {
                        assert_eq!(
                            binary_output,
                            baseline_text?,
                            "\r\nTest: {}",
                            path.to_string_lossy()
                        );
                    }
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
