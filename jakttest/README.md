# Jakttest

Jakttest is the test driver we use to test the Jakt compiler with code snippets.
It's also written in Jakt.

## Build dependencies

To build Jakttest you should use the `ninja` build system which will use the provided `build.ninja` file.
It needs the same `clang++` that is required to build any other Jakt file, and `python` 3.6+ to run the
patch script that patches the generated C++ from Jakt code to accept the external C++ code.

As a list:

- `ninja` (or `ninja-build` on some package managers)
- `clang++`

## How to run it?

First, make sure that you have the generated build directory:

```shell
cmake -GNinja -B build -S .
```

Now make sure `jakttest` is built:

```shell
ninja -C build jakttest
```

To run the tests, just use the binary:

```shell
./build/bin/jakttest
```

## On customizing behavior

Jakttest has some options you can pass to it to customize certain behaviors
(number of jobs, temporary directory to use...) that are set to reasonable
defaults, but you can always customize it. To see them all, check the output
of:

```shell
./build/bin/jakttest -h
```

## Test format

Most tests you'll se have a little comment at the top, with **three slashes**:
```jakt
/// Expect:
/// - <tag>: "<escaped output>"
```

These are the currently available tags:
- `output`: Expects the test to compile, succeed execution and output to
  standard output.
- `stderr`: Expects the test to compile, but execution fails and output is
  written to standard error.
- `error`: Expects the test to be rejected by the Jakt compiler, where the given
  output must appear somewhere in its error output.
- `cppincludes`: Adds the directories relative to the test file (separated by `:`) to the include path.
- `link`: Adds C++ files to be compiled alongside the test file (separated by
`:`). The paths are relative to the test file's location.
- `cppexports`: Sets an explicit directory for the exported headers. This directory is relative to the test file's location,
  and will be available in the include path for any other C++ file that is either imported or linked against.
