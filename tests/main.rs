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

                if output_path.exists() || error_output_path.exists() {
                    // We have an output to compare to, let's do it.
                    let mut compiler = Compiler::new();
                    let cpp_string = compiler.convert_to_cpp(&path);

                    let cpp_string = match cpp_string {
                        Ok(cpp_string) => {
                            if error_output_path.exists() {
                                let expected_error_msg =
                                    std::fs::read_to_string(&error_output_path)?;
                                let expected_error_msg = expected_error_msg.replace("\r", "");
                                let expected_error_msg = expected_error_msg.replace("\n", "");

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
                                let expected_error_msg = expected_error_msg.replace("\r", "");
                                let expected_error_msg = expected_error_msg.replace("\n", "");

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
                        .output()?;

                    assert!(status.status.success());

                    let binary_run = Command::new(&exe_name).output()?;

                    let binary_output = String::from_utf8_lossy(&binary_run.stdout).to_string();
                    let binary_output = binary_output.replace("\r\n", "\n");

                    let baseline_text = std::fs::read_to_string(&output_path)?;
                    let baseline_text = baseline_text.replace("\r\n", "\n");

                    assert_eq!(
                        binary_output,
                        baseline_text,
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
fn test_vectors() -> Result<(), JaktError> {
    test_samples("samples/vectors")
}

#[test]
fn test_strings() -> Result<(), JaktError> {
    test_samples("samples/strings")
}
