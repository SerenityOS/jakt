use std::{io::Write, path::Path};

use crate::{
    codegen::codegen,
    error::JaktError,
    lexer::lex,
    parser::parse_file,
    typechecker::{typecheck_file, Project, Scope, Type},
};

pub type FileId = usize;

pub const UNKNOWN_TYPE_ID: usize = 0;
pub const VOID_TYPE_ID: usize = 1;
pub const BOOL_TYPE_ID: usize = 2;
pub const I8_TYPE_ID: usize = 3;
pub const I16_TYPE_ID: usize = 4;
pub const I32_TYPE_ID: usize = 5;
pub const I64_TYPE_ID: usize = 6;
pub const U8_TYPE_ID: usize = 7;
pub const U16_TYPE_ID: usize = 8;
pub const U32_TYPE_ID: usize = 9;
pub const U64_TYPE_ID: usize = 10;
pub const F32_TYPE_ID: usize = 11;
pub const F64_TYPE_ID: usize = 12;
pub const CCHAR_TYPE_ID: usize = 13;
pub const CINT_TYPE_ID: usize = 14;
pub const USIZE_TYPE_ID: usize = 15;
// Note: keep STRING_TYPE_ID last as it is how we know how many slots to pre-fill
pub const STRING_TYPE_ID: usize = 16;

pub struct Compiler {
    raw_files: Vec<(String, Vec<u8>)>,
}

impl Compiler {
    pub fn new() -> Self {
        Self {
            raw_files: Vec::new(),
        }
    }

    pub fn include_prelude(&mut self, project: &mut Project) -> Option<JaktError> {
        // First, let's make types for all the builtin types
        // This order *must* match the order of the constants the typechecker expects
        project.types.resize(STRING_TYPE_ID + 1, Type::Builtin);

        let prelude = Compiler::prelude();

        // Not sure where to put prelude, but we're hoping its parsing is infallible
        self.raw_files.push(("<prelude>".to_string(), prelude));

        // Compile the prelude
        let (lexed, _) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );
        let (file, _) = parse_file(&lexed);

        // Scope ID 0 is the global project-level scope that all files can see
        typecheck_file(&file, 0, project)
    }

    pub fn convert_to_cpp(&mut self, fname: &Path) -> Result<String, JaktError> {
        let mut project = Project::new();

        let err = self.include_prelude(&mut project);
        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        let contents = std::fs::read(fname)?;

        self.raw_files
            .push((fname.to_string_lossy().to_string(), contents));

        let (lexed, err) = lex(
            self.raw_files.len() - 1,
            &self.raw_files[self.raw_files.len() - 1].1,
        );

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        let (file, err) = parse_file(&lexed);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        let scope = Scope::new(Some(0));
        project.scopes.push(scope);

        let file_scope_id = project.scopes.len() - 1;

        let err = typecheck_file(&file, file_scope_id, &mut project);

        match err {
            Some(err) => {
                return Err(err);
            }
            _ => {}
        }

        // Hardwire to first file for now
        Ok(codegen(&project, &project.scopes[file_scope_id]))
    }

    pub fn compile(&mut self, fname: &Path) -> Result<(), JaktError> {
        let cpp_string = self.convert_to_cpp(fname)?;

        let mut out_file = std::fs::File::create("output.cpp")?;
        out_file.write_all(cpp_string.as_bytes())?;

        Ok(())
    }

    pub fn get_file_contents(&self, file_id: FileId) -> &[u8] {
        &self.raw_files[file_id].1
    }

    pub fn prelude() -> Vec<u8> {
        r#"
extern class String {
    function split(this, anon c: c_char) -> [String]
    function characters(this) -> raw c_char
    function reverse(this) -> String
    function to_lowercase(this) -> String
    function to_uppercase(this) -> String
    function to_snakecase(this) -> String
    function to_titlecase(this) -> String
    function to_int(this) -> i32?
    function to_uint(this) -> u32?
    function is_whitespace(this) -> bool
    function hash(this) -> u32
    function substring(this, start: usize, length: usize) -> String
    function repeated(character: c_char, count: usize) -> String
    function is_empty(this) -> bool
    function length(this) -> usize
}

extern class Array<T> {
    function is_empty(this) -> bool
    function size(this) -> usize
    function capacity(this) -> usize
    function ensure_capacity(this, anon capacity: usize)
    function add_capacity(this, anon capacity: usize)
    function resize(mut this, anon size: usize)
    function push(mut this, anon value: T)
    function pop(mut this) -> T?
}

extern class Optional<T> {
    function has_value(this) -> bool
    function value(this) -> T
    function value_or(this, anon x: T) -> T
    function Optional<S>(anon x: S) -> Optional<S>
}

extern class Dictionary<K, V> {
    function get(this, anon key: K) -> V?
    function contains(this, anon key: K) -> bool
    function set(mut this, key: K, value: V)
    function remove(mut this, anon key: K) -> bool
    function ensure_capacity(mut this, anon capacity: usize)
    function clear(mut this)
    function size(this) -> usize
    function capacity(this) -> usize
    function keys(this) -> [K]
    function hash(this) -> u32
    function Dictionary<A, B>() -> Dictionary<A, B>
 }

extern class Tuple {}

extern class Range {}

"#
        .as_bytes()
        .to_vec()
    }
}
