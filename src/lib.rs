#![allow(clippy::or_fun_call)]
#![allow(clippy::too_many_arguments)]
#![allow(clippy::new_without_default)]
#![allow(clippy::enum_variant_names)]

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
