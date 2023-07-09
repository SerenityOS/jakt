# Jakt Quick Reference

Yak shaving describes working on a seemingly important intermediary activity which may or may not actually help solve a [problem](https://duckduckgo.com/?q=malcolm+in+the+middle+hal+light+bulb). This document aims to help avoid reinventing the wheel in your Jakt project by providing a quick overview of the language. It is not a complete language reference, but a handy starting point.

Check the main README.md and the "samples" directory in this repository for some additional detail. If you've still got questions, the `#jakt` channel on the SerenityOS Discord is the best place to start.

## Preprocessor

```jakt

// Comment to end of line

import foo                          // Import foo.jakt
import foo { bar }                  // Selectively import bar from foo
import foo as baz                   // Imported foo becomes baz
import extern c "myfile.h" { ... }  // Import C library from within search path
import extern "vector" { ... }      // Import C++ header "vector"

comptime foo(...) -> T { ... }      // Function executed at compile time, calls replaced with results

```

## Literals

```jakt

255, 0o377, 0xff            // Default (32-bit) integers (decimal, octal, hex)
-100i8, 240u8               // 8-bit (char) integers (signed, unsigned)
-2000i16, 30000u16          // 16-bit (short, int) integers (signed, unsigned)
-200000i32, 10000000u32     // 32-bit (long) integers (signed, unsigned)
-1i64, 1u64                 // 64-bit (long long) integers (signed, unsigned)
0.1, 42f32, 123_456.78f64   // Floating point numbers
0b1000000, 0b1011           // Binary literals
b'a'                        // Byte literal
c'a'                        // C character literal
'a'                         // Unicode code point literal
true, false                 // Only valid boolean (bool) states
[10,20,30]                  // Array
["a": 1, "b": 2]            // Dictionary
{1,2,3,4,5}                 // Set
("a", 2, true)              // Tuple with 3 elements
"Why, hello friends!"       // String
```

## Declarations

```jakt
let foo = 10                          // Immutable variable, inferred type
let foo:u8 = 255                      // Immutable variable, type u8
mut foo:i32 = 12345                   // Mutable variable, type i32
let b:bool = true                     // Boolean variable (immutable), true or false
let x = [1, 2, 3]                     // Array with 3 entries (immutable)
let v = [85; 3]                       // Array with 3 entries, initialized to 85 (immutable)
mut x: [i32] = []                     // Mutable empty array of type i32

let foo:i64? = 123                    // Optional, value is None otherwise 
let bar = foo! + 2                    // Program continues if ? is None, aborts if ! is None
let baz = Some(foo)                   // Returns 123. Some() returns value if present
foo = None
println("{}", foo ?? 0)               // Returns 0. ?? none-coalesces an optional, returns left if it has a value, right if not  

enum Apple { GrannySmith }            // Apple is an enum type with a single constructor GrannySmith

enum SimpleWithType {                 // Enum constructors can have independent types
    A(i32)
    B(x: u32, y: u32)
}

enum UnderlyingType: i32 {            // Enums can be declared with an underlying numeric type
    Zero
    One = 1
    ItsAllMadeUp = 10
}

let food: Apple = Apple::GrannySmith  // Assign enum value to variable

let foo = ("a", 2, true)              // Tuple, foo.0 == "a", .1 == 2, .2 == true

struct Person {                       // Struct declaration, all members are default public
    name: String
    age: i64
}

class Person {                        // Class declaration, all members are default private
    public name: String
    age: i64
}

namespace Greeters {}                 // Namespace, declarations within accessed via Greeters::

trait SomeTrait {                     // Define a trait
    fn something(this) -> u64         // No default implementation
    fn other_thing(this) -> void {    // Default implementation
        println("The other thing!")
    }
}
struct S implements(SomeTrait) {      // let foo = S() will have foo.something(), .other_thing
    fn something(this) -> u64 {       // Must implement, other_thing can be left as default
        return 12345
    }
}                                         
```

## Arrays  

```jakt

mut x: [i32] = [1,2,3]
x[0]                                    // Arrays are zero indexed
x.insert(before_index: 0, value: 0i32)  // Insert before .size or existing index
for y in x {                            //
    println("{}",y)                     // Iteration using the iteration protocols
}                                       //    Iterable<T> and IntoIterator<T>
x.push(10i32)                           // Append to the end
let v = x.pop()                         // Retrieve and remove last entry
let q = x.contains(20i32)               // True/false search
let z = x[2..4]                         // New slice array from x

```

## Control flow

```jakt

{                          
    let x = 4                       // Scope of x is from declaration to end of block
}

if x { a }                          // If x is true, evaluate a
else if y { b }                     // If not x and y (optional, may be repeated)
else { c }                          // If not x and not y (optional)

break                               // Jump out of while, do, or for loop, or switch
return x                            // Return x from function to caller
continue                            // Immediately moves to next loop iteration
abort()                             // Ends program execution

fn t() -> String {
  if false { return "WHF!" }
  abort()                           // Compiler won't complain about lack of return
}

fn toss(anon value: i32) throws {   // Keyword "throws" identifies a function which may raise an exception
    throw Error::from_errno(value)  // Throw an AK::Error
}

try toss(1234) catch error {        // try/catch pair will branch when "toss" raises exception
	println("Caught {}", error.code())
}

fn no_throw() throws -> Foo {
    return Foo(x: 123)
}
println("{}", (try no_throw())?.x)  // try works as an expression as well

mut i = 0
loop {                              // Easy loop
  if i == 5 {
    break
  }
  println("{}", i)                  // 0, 1, 2, 3, 4
  i++
}

while x { a }                       // Repeat definition "a" 0 or more times while x is true

{
  defer { println("b") }            // Execute contents of block upon leaving the lexical scope
  println("a")
}                                   // Output is "a\nb\n"

guard <boolean expression> else {   // Guard interrupts flow if expression evaluates false
	return                            // Guard must return, break, continue, or throw
}

fn test1(anon x: i64) throws -> String {  // Function containing guard must throw
    guard x == 1 else {
        return "FAIL"                     // Guard returns the function type
    }
    return "PASS"
}

guard foo is T else {}              // "is" keyword can be used to evaluate type

match i + 1 {                       // Use "match" to evaluate multiple possibilities
	(1) => println("PASS")  
	(2) => println("PASS")
	else => println("FAIL")           // Else required when all outcomes aren't defined
}

enum Foo { Bar, Baz }
let i: i32? = match a {             // Match can assign a value
	Foo::Bar => 2
	Foo::Baz => None                  // No "else" required as all enum entries are covered
}

```

## Functions

```jakt

fn f(x: i32, y: i32) -> i64   // f is a function taking two i32s and returning an i64
fn f()                        // f is a function taking no arguments
fn f(a: i32 = 0)              // f() is equivalent to f(a: 0)

fn f() { statements }         // Function definition, as a block
fn f() -> i32 => 42           // Function definition, short "arrow" form (immediate return)

let foo = 123i32
f(a: foo)                     // Parameter name must be specified
let a = 123i32
f(a)                          // ... unless the passed variable and parameter have the same name

fn h(anon a: i32) -> void
h(foo)                        // ... or if "anon" is specified
```

## Expressions

```jakt

T::X                        // Name X defined in class T
N::X                        // Name X defined in namespace N
::X                         // Global name X

t.x                         // Member x of struct or class t
p.x                         // Member x of struct or class pointed to by p

a[i]                        // i'th element of array a
f(x,y)                      // Call to function f with arguments x and y
T(x,y)                      // Object of class T initialized with x and y

x++                         // Add 1 to x, evaluates to original x (postfix)
x--                         // Subtract 1 from x, evaluates to original x
++x                         // Add 1 to x, evaluates to new value (prefix)
--x                         // Subtract 1 from x, evaluates to new value

x as? T                     // Cast to type T, empty if not convertible
x as! T                     // Cast to type T, aborts if not convertible

~x                          // Bitwise complement of x
!x                          // true if x is 0, else false (1 or 0 in C)
-x                          // Unary minus
+x                          // Unary plus (default)

&T                          // Immutable reference to value of type T
&mut T                      // Mutable reference to value of type T

&foo                        // Immutable reference to variable foo
&mut foo                    // Mutable reference to variable foo
*p                          // Contents of address p (dereference)
                            // The Jakt compiler automatically dereferences unambiguously correct uses of a reference
                            // Manual dereferencing is normally only required when the reference is being stored or passed to functions

raw T                       // Raw pointer to arbitrary type T, only in unsafe {} blocks
weak T                      // Weak pointer to reference counted T, becomes empty on T destruction

1..10                       // Range 1 to 10 (1,2,3,4,5,6,7,8,9)
1..10.inclusive()           // Range inclusive of final value (1,2,3,4,5,6,7,8,9,10)
1..                         // Range from 1 until end / largest value
..2                         // Range from beginning / smallest value until 2

x = y                       // Assign y to x, returns new value of x  
x + y                       // Add
x - y                       // Subtract, or number of elements from *x to *y
x * y                       // Multiply
x / y                       // Divide (integers round toward 0)
x % y                       // Modulo (result has sign of x)
x += y                      // x = x + y, also -= *= /= <<= >>= &= |= ^=

x << y                      // x shifted y bits to left (x * pow(2, y))
x >> y                      // x shifted y bits to right (x / pow(2, y))

x < y                       // Less than
x <= y                      // Less than or equal to
x > y                       // Greater than
x >= y                      // Greater than or equal to

x & y                       // Bitwise and (3 & 6 is 2)
x ^ y                       // Bitwise exclusive or (3 ^ 6 is 5)
x | y                       // Bitwise or (3 | 6 is 7)

x and y                     // x and then y
x or y                      // x or else y
not x                       // x is not true

```

## Classes

```jakt

class T {                   // A new type
private                     // Function/variable accessible only to T's member functions
public                      // Accessible to all

  x: i32                    // Member data

  fn f() -> void {}         // Static member function
  fn h(this) -> void {}     // Does not modify any data members
  fn j(mut this) -> void {} // Modifies data members

	fn init() throws -> T {   // Function to initialize and return type T, name is arbitrary
		return T(x: 0)          // As no parameters are accepted, defaults must be provided
	}

	fn init2(x: i32) throws -> T {
		return T(x)             // Accepts x as parameter to initialize T
	}

    restricted(A) fn secrets() {}    // Function only accessible by class A
	
};

.x = x                      // this is address of self (means x=x;)
T::l()                      // Call to static member
let t = T::init(x: 10)      // Create object t, specifying member data
t.f();                      // Call method f on object t

class Parent {              // Inheritance 
    public fn greet(this) => println("I am the parent")
}
class Child: Parent {
}
let child = Child()
child.greet()               // Output is "I am the parent"
```

## Generics

```jakt

class Foo<T> {              // Type of x passed during creation defines type
    public x: T
}
let f = Foo(x: 100)

class Foo<T> {              // Use generics with a class method
	public fn test(this, anon x: T) => x
}
let instance: A<String> = A()

struct Test {               // Generics with a static method
  fn test<T>(foo: T) -> T {
    return foo;
  }
}
println("{}", Test::test(foo: 1));
println("{}", Test::test<i64>(foo: 1)); // Explicit definition of type

```
  
## Strings

```jakt

let x = "Well, hello friends"  // In-place creation
x.contains("goodbye")          // False
x.contains("hello")            // True
x.length()                     // 19
x.is_empty()                   // False

let y = 0
let z = 1000
let a = format("{} {}", y, z)  // String formatter, a="0 1000"

mut s = StringBuilder::create()
s.append("String")
s.append_c_string("123".c_string())
println("{}", s.to_string())   // Output "String123"
```

Broad content ideas based on the <a href=https://github.com/mortennobel/cpp-cheatsheet>C++ cheatsheet</a> by Morten Nobel-Jørgensen.