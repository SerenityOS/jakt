# The jakt programming language

**jakt** is a memory-safe systems programming language.

It transpiles to C++ for easy integration with existing C++ codebases.

**NOTE:** The language is under heavy development.

## Usage

```
jakt file.jakt
lang++ -std=c++20 -Iruntime -Wno-user-defined-literals output.cpp
```

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

In **jakt**, there are three pointer types:

- [ ] **T** (Strong pointer to reference-counted class `T`.)
- [ ] **weak T?** (Weak pointer to reference-counted class `T`. Becomes empty on pointee destruction.)
- [x] **raw T** (Raw pointer to arbitrary type `T`. Only usable in `unsafe` blocks.)

Null pointers are not possible in safe mode, but pointers can be wrapped in `Optional`, i.e `Optional<T>` or `T?` for short.

Note that **weak** pointers must always be wrapped in `Optional`. There is no **weak T**, only **weak T?**.

## Math safety

- Integer overflow (both signed and unsigned) is a runtime error.
- Numeric values are not automatically coerced to `int`. All casts must be explicit.

For cases where silent integer overflow is desired, there are explicit functions that provide this functionality.

## Code readability

Far more time is spent reading code than writing it. For that reason, **jakt** puts a high emphasis on readability.

Some of the features that encourage more readable programs:

- [x] Immutable by default.
- [x] Argument labels in call expressions (`object.function(width: 10, height: 5)`)
- [ ] Inferred `enum` scope. (You can say `Foo` instead of `MyEnum::Foo`).
- [ ] Pattern matching with `match`.
- [ ] Optional chaining (`foo?.bar?.baz` (fallible) and `foo!.bar!.baz` (infallible))
- [x] `defer` statements.
- [x] Pointers are always dereferenced with `.` (never `->`)
- [ ] Trailing closure parameters can be passed outside the call parentheses.
- [ ] Error propagation with `ErrorOr<T>` return type and dedicated `try` / `must` keywords.

## Function calls

When calling a function, you must specify the name of each argument as you're passing it:

```
rect.set_size(width: 640, height: 480);
```

There are two exceptions to this:

- [x] If the parameter in the function declaration is declared as `anon`, omitting the argument label is allowed.
- [ ] When passing a variable with the same name as the parameter.

## Structures and classes

There are two main ways to declare a structure in Jakt: `struct` and `class`.

### `struct`

Basic syntax:

```jakt
struct Point {
    x: i64
    y: i64
}
```

Structs in Jakt have *value semantics*:
- Variables that contain a struct always have a unique instance of the struct.
- Copying a `struct` instance always makes a deep copy.

```jakt
let a = Point(x: 10, y: 5)
let b = a
// "b" is a deep copy of "a", they do not refer to the same Point
```

**jakt** generates a default constructor for structs. It takes all fields by name. For the `Point` struct above, it looks like this:

```jakt
Point(x: i64, y: i64)
```

Struct members are *public* by default.

### `class`

Same basic syntax as `struct`:
```
class Size {
    width: i64
    height: i64

    pub fun area(this) => width * height
}
```

Classes in Jakt have *reference semantics*:
- Copying a `class` instance (aka an "object") copies a reference to the object.
- All objects are reference-counted by default. This ensures that objects don't get accessed after being deleted.

Class members are *private* by default.

### Member functions

Both structs and classes can have member functions.

There are three kinds of member functions:

**Static member functions** don't require an object to call. They have no `this` parameter.

```jakt
class Foo {
    fun func() => println("Hello!")
}

// Foo::func() can be called without an object.
Foo::func()
```

**Non-mutating member functions** require an object to be called, but cannot mutate the object. The first parameter is `this`.

```jakt
class Foo {
    fun func(this) => println("Hello!")
}

// Foo::func() can only be called on an instance of Foo.
let x = Foo()
x.func()
```

**Mutating member functions** require an object to be called, and may modify the object. The first parameter is `mut this`.
```jakt
class Foo {
    x: i64

    fun set(mut this, anon x: i64) {
        this.x = x
    }
}

// Foo::set() can only be called on a mutable Foo:
let mut foo = Foo(x: 3)
foo.set(9)
```

## Arrays

Dynamic arrays are provided via a built-in `RefVector<T>` type. They can grow and shrink at runtime.

`RefVector` is memory safe:
- Out-of-bounds will panic the program with a runtime error.
- Slices of a `RefVector` keep the underlying data alive via automatic reference counting.

### Declaring arrays

```jakt
// Function that takes a RefVector<i64> and returns a RefVector<String>
fun foo(numbers: [i64]) -> [String] {
    ...
}
```

### Shorthand for creating arrays

```jakt
// RefVector<i64> with 256 elements, all initialized to 0.
let values = [0; 256]

// RefVector<String> with 3 elements: "foo", "bar" and "baz".
let values = ["foo", "bar", "baz"]
```

## Type casts

There are four built-in casting operators in **jakt**.

### Casts for all types

- `as? T`: Returns an `Optional<T>`, empty if the source value isn't convertible to `T`.
- `as! T`: Returns a `T`, aborts the program if the source value isn't convertible to `T`.

### Casts specific to numeric types

- `as truncated T`: Returns a `T` with out-of-range values truncated in a manner specific to each type.
- `as saturated T`: Returns a `T` with the out-of-range values saturated to the minimum or maximum value possible for `T`.

