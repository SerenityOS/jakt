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
    ParserError(String, Span),
    ValidationError(String, Span),
    TypecheckError(String, Span),
    TypecheckErrorWithHint(String, Span, String, Span),
}

impl From<std::io::Error> for JaktError {
    fn from(x: std::io::Error) -> Self {
        JaktError::IOError(x)
    }
}
