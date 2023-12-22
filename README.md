# The Jakt programming language

**Jakt** (pronounced [yakt](https://commons.wikimedia.org/wiki/File:Sv-jakt.ogg)) is a memory-safe systems programming language.

It currently transpiles to C++.

**NOTE:** The language is under heavy development.

**NOTE** If you're cloning to a Windows PC (not WSL), make sure that your Git client keeps the line endings as `\n`. You can set this as a global config via `git config --global core.autocrlf false`.

## Usage
The transpilation to C++ requires `clang`. Make sure you have that installed.
```
jakt file.jakt
./build/file
```

## Building
See [here](documentation/cmake-bootstrap.md).

## Goals

1. Memory safety
2. Code readability
3. Developer productivity
4. Executable performance
5. Fun!

## Memory safety

The following strategies are employed to achieve memory safety:
- Automatic reference counting
- Strong typing
- Bounds checking
- No raw pointers in safe mode

In **Jakt**, there are three pointer types:

- [x] **T** (Strong pointer to reference-counted class `T`.)
- [x] **weak T** (Weak pointer to reference-counted class `T`. Becomes empty on pointee destruction.)
- [x] **raw T** (Raw pointer to arbitrary type `T`. Only usable in `unsafe` blocks.)

Null pointers are not possible in safe mode, but pointers can be wrapped in `Optional`, i.e `Optional<T>` or `T?` for short.

## Math safety

- [x] Integer overflow (both signed and unsigned) is a runtime error.
- [x] Numeric values are not automatically coerced to `int`. All casts must be explicit.

For cases where silent integer overflow is desired, there are explicit functions that provide this functionality.

## Code readability

Far more time is spent reading code than writing it. For that reason, **Jakt** puts a high emphasis on readability.

Some of the features that encourage more readable programs:

- [x] Immutable by default.
- [x] Argument labels in call expressions (`object.function(width: 10, height: 5)`)
- [ ] Inferred `enum` scope. (You can say `Foo` instead of `MyEnum::Foo`).
- [x] Pattern matching with `match`.
- [x] Optional chaining (`foo?.bar?.baz` (fallible) and `foo!.bar!.baz` (infallible))
- [x] None coalescing for optionals (`foo ?? bar` yields `foo` if `foo` has a value, otherwise `bar`)
- [x] `defer` statements.
- [x] Pointers are always dereferenced with `.` (never `->`)
- [x] Trailing closure parameters can be passed outside the call parentheses.
- [ ] Error propagation with `ErrorOr<T>` return type and dedicated `try` / `must` keywords.

## Code reuse

Jakt is flexible in how a project can be structured with a built-in module system.

```jakt
import a                                // (1)
import a { use_cool_things }            // (2)
import fn()                             // (3)
import relative foo::bar                // (4)
import relative parent::foo::baz        // (5)
import relative parent(3)::foo::baz     // (6)
```

1. Import a module from the same directory as the file.
1. Import only `use_cool_things()` from module `a`.
1. Imports can be calculated at compile time. See [Comptime Imports](#comptime-imports)
1. Import a module using the relative keyword when the module is a sub path of the directory containing the file.
1. Import a module in a parent path one directory up from the file.
1. Syntactic sugar for importing a module three parent paths up from the file.

### The Jakt Standard Library

Jakt has a Standard Library that is accessed using the `jakt::` namespace:

```jakt
import jakt::arguments
import jakt::libc::io { system }
```

The Jakt Standard Library is in its infancy, so please consider making a contribution!

## Function calls

When calling a function, you must specify the name of each argument as you're passing it:

```jakt
rect.set_size(width: 640, height: 480)
```

There are two exceptions to this:

- [x] If the parameter in the function declaration is declared as `anon`, omitting the argument label is allowed.
- [x] When passing a variable with the same name as the parameter.

## Structures and classes

There are two main ways to declare a structure in **Jakt**: `struct` and `class`.

### `struct`

Basic syntax:

```jakt
struct Point {
    x: i64
    y: i64
}
```

Structs in **Jakt** have *value semantics*:
- Variables that contain a struct always have a unique instance of the struct.
- Copying a `struct` instance always makes a deep copy.

```jakt
let a = Point(x: 10, y: 5)
let b = a
// "b" is a deep copy of "a", they do not refer to the same Point
```

**Jakt** generates a default constructor for structs. It takes all fields by name. For the `Point` struct above, it looks like this:

```jakt
Point(x: i64, y: i64)
```

Struct members are *public* by default.

### `class`

- [x] basic class support
- [x] private-by-default members
- [x] inheritance
- [ ] class-based polymorphism (assign child instance to things requiring the parent type)
- [ ] `Super` type
- [ ] `Self` type

Same basic syntax as `struct`:
```
class Size {
    width: i64
    height: i64

    public fn area(this) => .width * .height
}
```

Classes in **Jakt** have *reference semantics*:
- Copying a `class` instance (aka an "object") copies a reference to the object.
- All objects are reference-counted by default. This ensures that objects don't get accessed after being deleted.

Class members are *private* by default.

### Member functions

Both structs and classes can have member functions.

There are three kinds of member functions:

**Static member functions** don't require an object to call. They have no `this` parameter.

```jakt
class Foo {
    fn func() => println("Hello!")
}

// Foo::func() can be called without an object.
Foo::func()
```

**Non-mutating member functions** require an object to be called, but cannot mutate the object. The first parameter is `this`.

```jakt
class Foo {
    fn func(this) => println("Hello!")
}

// Foo::func() can only be called on an instance of Foo.
let x = Foo()
x.func()
```

**Mutating member functions** require an object to be called, and may modify the object. The first parameter is `mut this`.
```jakt
class Foo {
    x: i64

    fn set(mut this, anon x: i64) {
        this.x = x
    }
}

// Foo::set() can only be called on a mut Foo:
mut foo = Foo(x: 3)
foo.set(9)
```

### Shorthand for accessing member variables

To reduce repetitive `this.` spam in methods, the shorthand `.foo` expands to `this.foo`.

## Strings

Strings are provided in the language mainly as the type `String`, which is a reference-counted (and heap-allocated) string type.
String literals are written with double quotes, like `"Hello, world!"`.

### Overloaded string literals

String literals are of type `String` by default; however, they can be used to implicitly construct any type that implements the `FromStringLiteral` (or `ThrowingFromStringLiteral`) trait. In the language prelude, currently only `StringView` implements this trait, which can be used only to refer to strings with a static lifetime:
```jakt
let foo: StringView = "foo" // This string is not allocated on the heap, and foo is only a fat pointer to the static string.
```

Overloaded string literals can be used by providing a type hint, whether by explicit type annotations, or by passing the literal to a function that expects a specific type:
```jakt
struct NotString implements(FromStringLiteral) {
    fn from_string_literal(anon string: StringView) -> NotString => NotString()
}

fn test(x: NotString) {}

fn main() {
    let foo: NotString = "foo"
    test(x: "Some string literal")
}
```

## Arrays

Dynamic arrays are provided via a built-in `Array<T>` type. They can grow and shrink at runtime.

`Array` is memory safe:
- Out-of-bounds will panic the program with a runtime error.
- Slices of an `Array` keep the underlying data alive via automatic reference counting.

### Declaring arrays

```jakt
// Function that takes an Array<i64> and returns an Array<String>
fn foo(numbers: [i64]) -> [String] {
    ...
}
```

### Shorthand for creating arrays

```jakt
// Array<i64> with 256 elements, all initialized to 0.
let values = [0; 256]

// Array<String> with 3 elements: "foo", "bar" and "baz".
let values = ["foo", "bar", "baz"]
```

## Dictionaries

- [x] Creating dictionaries
- [x] Indexing dictionaries
- [x] Assigning into indexes (aka lvalue)

```jakt
fn main() {
    let dict = ["a": 1, "b": 2]

    println("{}", dict["a"])
}
```

### Declaring dictionaries

```jakt
// Function that takes a Dictionary<i64, String> and returns an Dictionary<String, bool>
fn foo(numbers: [i64:String]) -> [String:bool] {
    ...
}
```

### Shorthand for creating dictionaries

```jakt
// Dictionary<String, i64> with 3 entries.
let values = ["foo": 500, "bar": 600, "baz": 700]
```

## Sets

- [x] Creating sets
- [x] Reference semantics

```jakt
fn main() {
    let set = {1, 2, 3}

    println("{}", set.contains(1))
    println("{}", set.contains(5))
}
```

## Tuples

- [x] Creating tuples
- [x] Index tuples
- [x] Tuple types

```
fn main() {
    let x = ("a", 2, true)

    println("{}", x.1)
}
```

## Enums and Pattern Matching

- [x] Enums as sum-types
- [x] Generic enums
- [x] Enums as names for values of an underlying type
- [x] `match` expressions
- [x] Enum scope inference in `match` arms
- [x] Yielding values from match blocks
- [ ] Nested `match` patterns
- [ ] Traits as `match` patterns
- [ ] Support for interop with the `?`, `??` and `!` operators

```jakt
enum MyOptional<T> {
    Some(T)
    None
}

fn value_or_default<T>(anon x: MyOptional<T>, default: T) -> T {
    return match x {
        Some(value) => {
            let stuff = maybe_do_stuff_with(value)
            let more_stuff = stuff.do_some_more_processing()
            yield more_stuff
        }
        None => default
    }
}

enum Foo {
    StructLikeThingy (
        field_a: i32
        field_b: i32
    )
}

fn look_at_foo(anon x: Foo) -> i32 {
    match x {
        StructLikeThingy(field_a: a, field_b) => {
            return a + field_b
        }
    }
}

enum AlertDescription: i8 {
    CloseNotify = 0
    UnexpectedMessage = 10
    BadRecordMAC = 20
    // etc
}

// Use in match:
fn do_nothing_in_particular() => match AlertDescription::CloseNotify {
    CloseNotify => { ... }
    UnexpectedMessage => { ... }
    BadRecordMAC => { ... }
}
```

## Generics

- [x] Generic types
- [x] Constant generics (minimal support)
- [ ] Constant generics (full support)
- [x] Generic type inference
- [x] Traits

**Jakt** supports both generic structures and generic functions.

```jakt
fn id<T>(anon x: T) -> T {
    return x
}

fn main() {
    let y = id(3)

    println("{}", y + 1000)
}
```

```jakt
struct Foo<T> {
    x: T
}

fn main() {
    let f = Foo(x: 100)

    println("{}", f.x)
}
```

```jakt
struct MyArray<T, comptime U> {
    // NOTE: There is currently no way to access the value 'U', referring to 'U' is only valid as the type at the moment.
    data: [T]
}
```

## Namespaces

- [x] Namespace support for functions and struct/class/enum
- [ ] Deep namespace support

```
namespace Greeters {
    fn greet() {
        println("Well, hello friends")
    }
}

fn main() {
    Greeters::greet()
}
```

## Type casts

There are two built-in casting operators in **Jakt**.

- `as? T`: Returns an `Optional<T>`, empty if the source value isn't convertible to `T`.
- `as! T`: Returns a `T`, aborts the program if the source value isn't convertible to `T`.

The `as` cast can do these things (note that the implementation may not agree yet):
- Casts to the same type are infallible and pointless, so might be forbidden in the future.
- If the source type is _unknown_, the cast is valid as a type assertion.
- If both types are primitive, a safe conversion is done.
    - Integer casts will fail if the value is out of range. This means that promotion casts like i32 -> i64 are infallible.
    - Float -> Integer casts truncate the decimal point (?)
    - Integer -> Float casts resolve to the closest value to the integer representable by the floating-point type (?). If the integer value is too large, they resolve to infinity (?)
    - Any primitive -> bool will create `true` for any value except 0, which is `false`.
    - bool -> any primitive will do `false -> 0` and `true -> 1`, even for floats.
- If the types are two different pointer types (see above), the cast is essentially a no-op. A cast to `T` will increment the reference count as expected; that's the preferred way of creating a strong reference from a weak reference. A cast from and to `raw T` is unsafe.
- If the types are part of the same type hierarchy (i.e. one is a child type of another):
    - A child can be cast to its parent infallibly.
    - A parent can be cast to a child, but this will check the type at runtime and fail if the object was not of the child type or one of its subtypes.
- If the types are incompatible, a user-defined cast is attempted to be used. The details here are not decided yet.
- If nothing works, the cast will not even compile.

Additional casts are available in the standard library. Two important ones are `as_saturated` and `as_truncated`, which cast integral values while saturating to the boundaries or truncating bits, respectively.

## Traits

To make generics a bit more powerful and expressive, you can add additional information to them:

```jakt
trait Hashable<Output> {
    fn hash(self) -> Output
}

class Foo implements(Hashable<i64>) {
    fn hash(self) => 42
}
```

Traits can be used to add constraints to generic types, but also provide default implementations based on a minimal set of requirements - for instance:

```jakt
trait Fancy {
    fn do_something(this) -> void
    fn do_something_twice(this) -> void {
        .do_something()
        .do_something()
    }
}

struct Boring implements(Fancy) {
    fn do_something(this) -> void {
        println("I'm so boring")
    }

    // Note that we don't have to implement `do_something_twice` here, because it has a default implementation.
}

struct Better implements(Fancy) {
    fn do_something(this) -> void {
        println("I'm not boring")
    }

    // However, a custom implementation is still valid.
    fn do_something_twice(this) -> void {
        println("I'm not boring, but I'm doing it twice")
    }
}
```

Traits can have methods that reference other traits as types, which can be used to describe a hierarchy of traits:

```jakt
trait ConstIterable<T> {
    fn next(this) -> T?
}

trait IntoIterator<T> {
    // Note how the return type is a reference to the ConstIterable trait (and not a concrete type)
    fn iterator(this) -> ConstIterable<T>
}
```

### Operator Overloading and Traits

Operators are implemented as traits, and can be overloaded by implementing them on a given type:

```jakt
struct Foo implements(Add<Foo, Foo>) {
    x: i32

    fn add(this, anon rhs: Foo) -> Foo {
        return Foo(x: .x + other.x)
    }
}
```

The relationship between operators and traits is as follows (Note that `@` is used as a placeholder for any binary operator's name or sigil):

| Operator | Trait | Method Name | Derived From Method |
|----------|-------|-------------|---------------------|
| `+` | `Add` | `add` | - |
| `-` | `Subtract` | `subtract` | - |
| `*` | `Multiply` | `multiply` | - |
| `/` | `Divide` | `divide` | - |
| `%` | `Modulo` | `modulo` | - |
| `<` | `Compare` | `less_than` | `compare` |
| `>` | `Compare` | `greater_than` | `compare` |
| `<=` | `Compare` | `less_than_or_equal` | `compare` |
| `>=` | `Compare` | `greater_than_or_equal` | `compare` |
| `==` | `Equal` | `equals` | - |
| `!=` | `Equal` | `not_equals` | `equals` |
| `@=` | `@Assignment` | `@_assign` | - |

Other operators have not yet been converted to traits, decided on, or implemented:

| Operator | Description | Status |
|----------|-------------|--------|
| `&` | Bitwise And | Not Decided |
| `\|` | Bitwise Or | Not Decided |
| `^` | Bitwise Xor | Not Decided |
| `~` | Bitwise Not | Not Decided |
| `<<` | Bitwise Shift Left | Not Decided |
| `>>` | Bitwise Shift Right | Not Decided |
| `and` | Logical And | Not Decided |
| `or` | Logical Or | Not Decided |
| `not` | Logical Not | Not Decided |
| `=` | Assignment | Not Decided |

## Safety analysis

**(Not yet implemented)**

To keep things safe, there are a few kinds of analysis we'd like to do (non-exhaustive):

* Preventing overlapping of method calls that would collide with each other. For example, creating an iterator over a container, and while that's live, resizing the container
* Using and manipulating raw pointers
* Calling out to C code that may have side effects

## Error handling

Functions that can fail with an error instead of returning normally are marked with the `throws` keyword:

```jakt
fn task_that_might_fail() throws -> usize {
    if problem {
        throw Error::from_errno(EPROBLEM)
    }
    ...
    return result
}

fn task_that_cannot_fail() -> usize {
    ...
    return result
}
```

Unlike languages like C++ and Java, errors don't unwind the call stack automatically. Instead, they bubble up to the nearest caller.

If nothing else is specified, calling a function that `throws` from within a function that `throws` will implicitly bubble errors.

### Syntax for catching errors

If you want to catch errors locally instead of letting them bubble up to the caller, use a `try`/`catch` construct like this:

```jakt
try {
    task_that_might_fail()
} catch error {
    println("Caught error: {}", error)
}
```

There's also a shorter form:

```jakt
try task_that_might_fail() catch error {
    println("Caught error: {}", error)
}
```

### Rethrowing errors

**(Not yet implemented)**

## Inline C++

For better interoperability with existing C++ code, as well as situations where the capabilities of **Jakt** within `unsafe` blocks are not powerful enough, the possibility of embedding inline C++ code into the program exists in the form of `cpp` blocks:

```jakt
mut x = 0
unsafe {
    cpp {
        "x = (i64)&x;"
    }
}
println("{}", x)
```

## References

Values and objects can be passed by reference in some situations where it's provably safe to do so.

A reference is either immutable (default) or mutable.

### Reference type syntax

- `&T` is an immutable reference to a value of type `T`.
- `&mut T` is a mutable reference to a value of type `T`.

### Reference expression syntax

- `&foo` creates an immutable reference to the variable `foo`.
- `&mut foo` creates a mutable reference to the variable `foo`.

### Dereferencing a reference

To "get the value out" of a reference, it must be dereferenced using the `*` operator, however the compiler will automatically dereference references if the dereferencing is the single unambiguous correct use of the reference (in practice, manual dereferencing is only required where the reference is being stored or passed to functions).

```jakt
fn sum(a: &i64, b: &i64) -> i64 {
    return a + b
    // Or with manual dereferencing:
    return *a + *b
}

fn test() {
    let a = 1
    let b = 2
    let c = sum(&a, &b)
}
```

For mutable references to structs, you'll need to wrap the dereference in parentheses in order to do a field access:

```jakt
struct Foo {
    x: i64
}
fn zero_out(foo: &mut Foo) {
    foo.x = 0
    // Or with manual dereferencing:
    (*foo).x = 0
}
```

### References (first version) feature list:

- [x] Reference types
- [x] Reference function parameters
- [x] Local reference variables with basic lifetime analysis
- [x] No references in structs
- [x] No references in return types
- [x] No mutable references to immutable values
- [x] Allow `&foo` and `&mut foo` without argument label for parameters named `foo`
- [x] Auto-dereference references where applicable

### References TODO:

- [ ] (`unsafe`) references and raw pointers bidirectionally convertible
- [ ] No capture-by-reference in persistent closures

### Closures (first version) feature list:

- [x] Function as parameter to function
- [x] Functions as variables
- [x] No returning functions from functions
- [x] Lambdas can throw
- [x] Explicit captures

### Closures TODO:

- [] Return function from function

## Compiletime Execution

Compiletime Function Execution (or CTFE) in Jakt allows the execution of any jakt function at compiletime, provided that the result value
may be synthesized using its fields - currently this only disallows a few prelude objects that cannot be constructed by their fields (like Iterator objects and StringBuilders).

Any regular Jakt function can be turned into a compiletime function by replacing the `function` keyword in its declaration with the `comptime` keyword, which will force all calls to that specific function to be evaluated at compile time.

### Invocation Restrictions

Comptime functions may only be invoked by constant expressions; this restriction includes the `this` object of methods.

### Throwing in a comptime context

Throwing behaves the same way as normal error control flow does, if the error leaves the comptime context (by reaching the original callsite), it will be promoted to a compilation error.

### Side effects

Currently all prelude functions with side effects behave the same as they would in runtime. This allows e.g. pulling in files into the binary; some functions may be changed later to perform more useful actions.

## Comptime imports

It is possible to design custom import handling based on data available at compile time. An excellent example of this in the Jakt compiler is the [Platform Module](https://github.com/SerenityOS/jakt/blob/main/selfhost/os.jakt#L41).

See a smaller example in the [comptime imports sample](https://github.com/SerenityOS/jakt/blob/main/samples/modules/comptime_imports.jakt).

### Comptime TODO

- [ ] Implement execution of all Jakt expressions
