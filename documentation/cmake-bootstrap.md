# Bootstapping with CMake

The included CMakeLists.txt at the top level of the project provides cross-platform build rules for
auto-bootstrapping the compiler all the way to stage 3. The build takes advantage of the [Corrosion](https://github.com/corrosion-rs/corrosion) library for building the Rust-based compiler and exposing it as an imported target to CMake.

For reference, the stages:

Stage 1: Rust-based compiler. This compiler, written in Rust, is able to parse Jakt source code and output C++ code.

Stage 2: Jakt selfhost compiler. This compiler, written in Jakt, is compiled with the Stage 1 compiler and outputs C++.

Stage 3: Jakt selfhost compiler. This is the same Jakt source code as the Stage 2 compiler, but compiled with the Stage 2 compiler. It outputs C++.

All the stages are compiled with the provided CMAKE_CXX_COMPILER.


## Building the bootstrapped compilers

Provide a suitable CMake invocation. Note that a clang version >= 13 is required.

```sh
cmake -B build -GNinja -DCMAKE_CXX_COMPILER=clang++-14
```

Invoke the specified generator

```sh
cmake --build build
# OR
ninja -C build
```

If you want to install the compilers to a location of your choice, provide an install prefix at your favorite location.

```sh
cmake -B build -GNinja -DCMAKE_CXX_COMPILER=clang++-14 -DCMAKE_INSTALL_PREFIX=jakt-install
ninja -C build install
```

If you want to enable optimizations, be sure to set [CMAKE_BUILD_TYPE](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html?highlight=cmake_build_type).
