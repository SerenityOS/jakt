#![allow(clippy::or_fun_call)]

extern crate core;

mod codegen;
mod compiler;
mod error;
mod lexer;
mod parser;
mod typechecker;

pub use compiler::Compiler;
pub use error::JaktError;
pub use lexer::Span;
