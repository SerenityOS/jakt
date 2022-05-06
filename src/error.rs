use crate::parser::Span;

#[derive(Debug)]
pub enum JaktError {
    IOError(std::io::Error),
    ParserError(String, Span),
    TypecheckError(String, Span),
}

impl From<std::io::Error> for JaktError {
    fn from(x: std::io::Error) -> Self {
        JaktError::IOError(x)
    }
}
