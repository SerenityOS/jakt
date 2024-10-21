# How Jakt avoids code duplication in pattern matching codegen

## Current solution

Typechecker walks the patterns to get the type information out of them as it
did before, but instead of adding binding variables to a scope, it adds
them to a `BindingKeyBuilder`. Typechecker "submits" bindings to the builder,
which then produces a `BindingKey` that tells us whether the set of bindings
that were declared already exist within the same pattern group.

Since we don't want to be passing a lot of state regarding the match to helper
functions like `.typecheck_match_variant`, `BindingKeyBuilder` only contains a
reference to the slice of cases that have been declared and refer to the same
`ParsedMatchBody`. Remember that it could be multiple due to Constraint 1.

To enforce that the set of cases checked by `BindingKeyBuilder` are the correct
set, and that context is not lost when reading through the long loop bodies of
`.typecheck_match`, all the state regarding match typecheck is in
`MatchBuilder`. This struct has two functionalities:

1.  It will not let us create a `BindingKeyBuilder` until we provide a proof
    that we have started a case. Such proof tracks the start of the case
    slice that `BindingKeyBuilder` should use. This is in place to avoid copy-paste
    mishaps, since the logic for traversing the matches is big and changes depending on
    the type to be matched.

2.  When finishing a pattern, we give it a `BindingKey` along a match body and
    said pattern, and it will register the pattern into the `CheckedMatchCase`
    that the `BindingKey` tells it to. The parsed body will be (re-)typechecked
    against the bindings for this finished pattern only when the bindings of the
    new pattern have different types than the rest of the previously checked
    patterns.

`BindingKeyBuilder` keeps track of what bindings were declared by the
typechecker, in case we have to generate a new `CheckedMatchBody`, and the set
of candidates that could match the set of bindings that have been submitted.

Since `BindingKeyBuilder` works in a binding-per-binding basis, we could have
multiple sets that match the partial set of bindings. The `finish()` method is
called when the build is done, so we know that there are no more bindings
flying in and we can make a final pass on our candidates, selecting only the
`CheckedMatchCase` that has the same amount of bindings as what we've gathered
so far.

The usage of `BindingKeyBuilder` helps us reduce the amount of dictionaries
that are created and deleted during the typechecking phase, since builders that
stay in their `Empty` state do not contain references to empty
dictionaries.


## Constraints

The solution above is designed to feed codegen with more information on the
structure of matches, avoid duplicate work whenever possible and keep
correctness while doing so.

We can summarize these features in two constraints, discussed in this section
after a brief on pattern matching terminology.

### Terminology


```jakt
match <expr> {
    <pat1>(<binding1>...) | <pat2>(<binding2>...) => <body1>
    <pat3> => <body2>
}
```

- `expr` is the "matched value", or "value". It is the value we wish to branch
on.
- `pat1`, `pat2` and `pat3` are "patterns". They are different structures that
the matched value may conform to.
- `binding1` and `binding2` are "bindings". They are variables that extract
different parts of the structure that the value is checked to conform to. We
can then use those variables inside `<body1>`.
- `body1` and `body2` are "bodies". They are the pieces of code that we want to
execute on certain cases.
- `pat1` and `pat2` form a "pattern group". Matching either of them will branch
to the code specified in `<body1>`.
- Pattern groups and bodies together form a "case". Each case has a single body
and a group of patterns.


### Constraint 1: Multiple binding types

Jakt allows us to use bindings of different types in the same pattern group, as
long as the body typechecks against both "versions" of the bindings. For an
illustration, take this valid Jakt sample:

```jakt
enum TypedPair {
    I32(a: i32, b: i32)
    U64(a: u64, b: u64)
}


fn get_pair() -> TypedPair { ... }

fn main() {
    match get_pair() {
        I32(a, b) | U64(a, b) => {
            let result = a + b
            eprintln("result: {}", result)
        }
    }
}
```

Notice that the first body of the match accepts both types of `a` and `b`
(`i32` and `u64`):

- `a + b` typechecks as long as the type of `a` implements `Add` with `b` as its RHS.
- `eprintln` accepts both result types.

According to the rule above, this sample should typecheck and always print the
added result.

We want to generate the minimal amount of code that contains both versions of
the branching, meaning that paths for both `I32` and `U64` should get their
`result` to be `i32` and `u64` respectively.

When generating the code for that to work, even though we're lenient on the
user, we still have to separate the code path that uses `u64` from the code
path that uses `i32`. Since we generate C++ code, we can rely on C++'s
substitution power for things like calls to overloaded functions, but wherever
we have to fully specify the type of `a`, `b` or `result` we will have to
generate two versions of the bodies.

### Constraint 2: Multiple patterns, same binding types, only one body

Take the following samples:

#### Constraint 2.1: Multiple patterns with bindings
```jakt
enum Foo {
    Bar(i32)
    Baz
}

fn get_foo() -> Foo { ... }

fn main() {
    match get_foo() {
        Bar(x) | Baz default(x = 1i32) {
            // ... long code using `x`
        }
    }
}
```

#### Constraint 2.2: Multiple patterns with no bindings
```jakt
enum Answer {
    Is42
    IsNot42(actual_value: u32)
    IsNot42AndNoValue
}

fn get_answer() -> Answer { ... }

fn main() {
    match get_answer() {
        Is42 => {
            // long body 1
        }
        IsNot42 | IsNot42AndNoValue => {
            // long body 2
        }
    }
}
```

In both cases, we want Jakt to ideally only generate the long bodies once.

## Previous solutions

This is not the first iteration of pattern matching codegen, and the
constraints above are modelled against features and problems of previous
iterations. In this section we explain how each iteration works at a high level
and how they motivate the constraints.

### First solution

The first implementation ran through all of the cases, typechecking the body
for each of the patterns and submitting a new case per pattern, with their
respective body.

When generating code for a `match`, codegen sees a `CheckedExpression::Match`
containing a list of `CheckedMatchCase`s. Each `CheckedMatchCase` contains exactly one
pattern and one body that uses the bindings declared within said pattern.

The problem with this solution is that it effectively duplicates the body as
many times as patterns exist in the same group. However, the overhead on
typechecking the body was not the main issue: Codegen would receive the bodies
already duplicated, severely limiting what could be done at the codegen stage.
Take into account that the codegen stage has the most complete version of the
program that Jakt can have, since it needs all the concrete types that are used
in order to generate working C++.
In #1597 we can see that a ~300 line Jakt function
(`typecheck_binary_operation`) is compiled to ~5500 lines of C++ code! That
happened because the bodies for each case are large, and the bodies were
duplicated many times.

Constraint 2 ensures that similar functions to `typecheck_binary_operation` do
not make the C++ compiler sift through repeating bodies if it's not
necessary.

### A partial improvement (#1597)

PR #1597 addressed Constraint 2.1 by keeping the shared relationship between
the patterns inside a pattern group and the body they jump to. This enables
codegen to find pattern groups that have no bindings on them and easily group
them by concatenating `case` labels or concatenating boolean expressions with
`||`.

Now each `CheckedMatchCase` contains a list of `CheckedMatchPattern` and one
body that uses the bindings declared within said pattern. The implementation
typechecks all bodies like the last version, but only selects the last checked
body.

The problem with this approach is that now the typechecker portion of this
solution does not respect Constraint 1, since the last checked body is not
enough to represent the case if bindings from the same parsed pattern group
have different binding types.

This causes `tests/codegen/match_enum_same_body_different_impl.jakt` to fail,
since it codegens a call to `maybe_templated<JaktArray<i32>>` on all cases, when
the first two cases of the enum should use the overloaded versions of
`maybe_templated`.

### Latest solution

With this iteration, Constraint 2.1 is not addressed yet, but it satisfies
Constraint 1 and Constraint 2.2. Typechecker now keeps the grouping, but
re-generates the bodies when the types don't match.

Each `CheckedMatchCase` contains a list of `CheckedMatchPattern`, a set of
bindings `[String:VarId]` and a body where those bindings are used. All the
patterns in this `CheckedMatchCase` are known to have the same set of bindings
as the case.

#### Why is this solution better?

From the typechecker's side, it's obvious: it avoids creating `Scope`s and
`CheckedMatchBody`s and `CheckedExpressions` and you name it. A quick glance to
performance counters while typechecking selfhost [^1] reveals that this
solution has a memory usage peak that is 20 MB lower than the previous
solution, and is around ~14% faster.
The memory usage improvement happens partly because `Scope`s are refcounted
(`class`) and they are eternally stored in their respective `Module.scopes`
array. Since we don't create them, they don't linger anymore.

From codegen's side, it's certainly better than #1597 since it addresses
Constraint 1, which is more important than Constraint 2 because now codegen is
correct. As discussed below, this solution will generate "false duplicates"
because it backs off without analyzing the exact problem at hand. The amount of
duplicates that it will generate with respect to #1597 due to having to comply
with Constraint 1 is not easy to estimate.

#### Why is it not ideal?

The reason Constraint 1 fails with #1597's solution is very specific: The types
of the bindings are mentioned inside the body.

An ideal solution would not duplicate bodies that don't mention the types
inside the body implementation when driving them into codegen, or at least
avoid duplicating the parts that don't depend on the binding types
syntactically. That will generate even less C++ code, although the final result
will still have to go through code duplication through template instantiations
or overloads.

This solution would require a lot of machinery that is not yet in place to
typecheck the body and extract what variables (external to the body) each
statement depends on, and decide how much of it has to be duplicated in either
codegen or typechecker, or a mix of both. I didn't go with this solution
because it seemed too complex of a change with not that big of a benefit.
Perhaps we can place it in the backburner and take its potential into account
when doing a similar extraction system in other places.

I still haven't measured or calculated how many "false duplicates" the
non-ideal algorithm will generate, but I can estimate that whatever amount that
is it will not be very different from the ideal solution, since the difference
boils down to the cases that have patterns with different binding types but
could use some method of overloading in codegen (`auto` in lambda and/or
function overloading) that is significant to the compile time of that piece of
code, meaning that the separation made things worse.

---

[^1]: Used the program from https://github.com/andrewrk/poop with the following command:
    `poop -d 15000 './stage1_main -R runtime selfhost/main.jakt' './build/bin/jakt_stage2 -R runtime selfhost/main.jakt'`.
    `./stage1_main` is stage1 from https://github.com/SerenityOS/jakt/commit/d65f014cc54b986f629fe676d914af01d442b9f7
