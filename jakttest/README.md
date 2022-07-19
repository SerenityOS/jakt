# Jakttest

Jakttest is the test driver we use to test the Jakt compiler with code snippets.
It's also written in Jakt.

## Build dependencies

To build Jakttest you should use the `ninja` build system which will use the provided `build.ninja` file.
It needs the same `clang++` that is required to build any other Jakt file, and `python` 3.6+ to run the
patch script that patches the generated C++ from Jakt code to accept the external C++ code.

As a list:

- `ninja` (or `ninja-build` on some package managers)
- `python` version `3.6+`
- `clang++`

## How to run it?

If you've never used Jakttest before or you transitioned from a commit older
than [`c232f03`](https://github.com/SerenityOS/jakt/commit/c232f03570247d947a1bfb6373e6d41b3b9219a7),
you'll have to first run the following to generate the binary:

```shell
ninja -C jakttest
```

Once done, Jakttest will try to update automatically, switching the running
binary on the fly if the executable has been updated, so you always run the
tests with the correct Jakttest.

To run the tests, just use the binary:

```shell
./jakttest/build/jakttest
```

## On customizing behavior

Jakttest has some options you can pass to it to customize certain behaviors
(number of jobs, temporary directory to use...) that are set to reasonable
defaults, but you can always customize it. To see them all, check the output
of:

```shell
./jakttest/build/jakttest -h
```
