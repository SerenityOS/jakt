/*
 * !!! DEPRECATION WARNING !!!
 * We're not doing any more feature development in the rust-based compiler at this point.
 * It'll be limited to bug fixes and necessities only.
 *
 * New features should go into the self-hosted compiler.
 */

/*
 * Copyright (c) 2022, JT <jt@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#![deny(clippy::all)]
#![allow(clippy::or_fun_call)]
#![allow(clippy::too_many_arguments)]
#![allow(clippy::new_without_default)]
#![allow(clippy::enum_variant_names)]
#![allow(clippy::never_loop)]

extern crate core;

pub use compiler::Compiler;
pub use error::JaktError;
pub use ide::{
    find_definition_in_project, find_dot_completions_in_project, find_type_definition_in_project,
    find_typename_in_project,
};
pub use lexer::Span;
pub use typechecker::Project;

mod codegen;
mod compiler;
mod error;
mod ide;
mod lexer;
mod parser;
mod typechecker;

