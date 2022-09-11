# Jakt coding style

For low-level styling (spaces, parentheses, brace placement, etc), all code should be formatted with `cargo fmt`.

This document describes the coding style for the Jakt compiler. All new code should conform to this style.

This is a living document, and will change as we eventually rewrite the compiler in Jakt, and as the Jakt language develops.


### Names

A combination of PascalCase and snake\_case. Use PascalCase (Capitalize the first letter, including all letters in an acronym) in a class, struct, or namespace name. Use snake\_case (all lowercase, with underscores separating words) for variable and function names.

###### Right:

```rust
struct Entry;
pub fn the_answer() -> u64 {
    let answer: u64 = 42;
    answer
}
```

###### Wrong:

```rust
struct data;
pub fn MIME_Type() -> &'static str {
    let mimeType = "text/html";
    mimeType
}
```

Use full words, except in the rare case where an abbreviation would be more canonical and easier to understand.

###### Right:

```rust
let character_size: usize;
let length: usize;
let tab_index: i16; // More canonical.
```

###### Wrong:

```rust
let char_size: usize;
let len: usize;
let tabulation_index: i16; // Goofy.
```

Where the most suitable name is a reserved word (for example `type`) append an underscore.

###### Right:

```rust
let type_ = calculate_type(foo);
```

###### Wrong:

```rust
let ty = calculate_type(foo);
```

Use descriptive verbs in function names.

###### Right:

```rust
pub fn convert_to_ascii(...) -> bool {}
```

###### Wrong:

```rust
pub fn to_ascii(...) -> bool {}
```

When there are two getters for a variable, and one of them automatically makes sure the requested object is instantiated, prefix that getter function with `ensure_`. As it ensures that an object is created, it should consequently also return a reference, not a pointer.

###### Right:

```rust
pub fn inode() -> Option<&Inode> {}
pub fn ensure_inode() -> &Inode {}
```

###### Wrong:

```rust
pub fn inode() -> &Inode {}
pub fn ensure_inode() -> Option<&Inode> {}
```

Enum members should use InterCaps with an initial capital letter.

### Comments

Make comments look like sentences by starting with a capital letter and ending with a period (punctuation). One exception may be end of line comments like this `if x == y { // false for NaN`.

Use FIXME: or TODO: (without attribution) to denote items that need to be addressed in the future.

###### Right:

```rust
draw_jpg(); // FIXME: Make this code handle jpg in addition to the png support.
draw_jpg(); // TODO: Make this code handle jpg in addition to the png support.
```

###### Wrong:

```rust
draw_jpg(); // FIXME(joe): Make this code handle jpg in addition to the png support.
draw_jpg(); // TODO(joe): Make this code handle jpg in addition to the png support.
```

Explain *why* the code does something. The code itself should already say what is happening.

###### Right:

```rust
i += 1; // Go to the next page.
```

###### Even better:

```rust
page_index += 1;
```

###### Wrong:

```rust
i += 1; // Increment i.
```

### Error messages

Try to keep error messages short and clear, while still providing enough information to be useful.

Capitalize the start of the first word of each error message that is displayed to the user. Do not end the message with a period.

Type names and code excerpts should be wrapped in ‘ `'LEFT SINGLE QUOTATION MARK' (U+2018)` and ’ `'RIGHT SINGLE QUOTATION MARK' (U+2019)`.

If there is a category for the error, follow it with a colon and space, and begin the rest of the message with a lowercase letter. For internal errors, the category is "Internal error".

##### Right:

```
"Type mismatch: expected ‘String’, but got ‘i64’"
"Binary arithmetic operation between incompatible types (‘String’ and ‘i64’)"
"Internal error: expression stack empty"
```

##### Wrong:

```
"type mismatch: Expected String, but got i64."
"Binary arithmetic operation between incompatible types"
"Something went wrong! :^("
```
