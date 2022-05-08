use crate::lexer::Span;

#[derive(Debug)]
pub enum JaktError {
    IOError(std::io::Error),
    ParserError(String, Span),
    ValidationError(String, Span),
    TypecheckError(String, Span),
}

impl From<std::io::Error> for JaktError {
    fn from(x: std::io::Error) -> Self {
        JaktError::IOError(x)
    }
}
