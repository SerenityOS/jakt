# Jakttest

Jakttest is the test driver we use to test the Jakt compiler with code snippets.
It's also written in Jakt.

## Build dependencies

Jakttest is built along with Jakt and therefore needs the same dependencies.
See [Jakt's build instructions](../documentation/cmake-bootstrap.md) for more
information.

## Running Jakttest

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
./build/jakttest
```

## On customizing behavior

Jakttest has some options you can pass to it to customize certain behaviors
(number of jobs, temporary directory to use...) that are set to reasonable
defaults, but you can always customize it. To see them all, check the output
of:

```shell
./build/jakttest -h
```

## Test format

Most tests you'll se have a little comment at the top, with **three slashes**:
```jakt
/// Expect:
/// - <tag>: "<escaped output>"
```

There are currently three available tags:
- `output`: Expects the test to compile, succeed execution and output to
  stdandard output.
- `stderr`: Expects the test to compile, but execution fails and output is
  written to stdandard error.
- `error`: Expects the test to be rejected by the Jakt compiler, where the given
  output must appear somewhere in its error output.
