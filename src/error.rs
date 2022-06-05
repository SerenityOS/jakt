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

use crate::lexer::Span;

#[derive(Debug)]
pub enum JaktError {
    IOError(std::io::Error),
    StringError(String),
    ParserError(String, Span),
    ParserErrorWithHint(String, Span, String, Span),
    ValidationError(String, Span),
    TypecheckError(String, Span),
    TypecheckErrorWithHint(String, Span, String, Span),
}

impl From<std::io::Error> for JaktError {
    fn from(x: std::io::Error) -> Self {
        JaktError::IOError(x)
    }
}
