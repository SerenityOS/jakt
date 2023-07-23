# Jakt vscode extension

This is the vscode extension for the Jakt language.

There are no pre-packaged versions of this extension, as changes to language and tooling happen frequently.

## Build instructions

Pick a location to install jakt. This should be a local directory, not a global install directory.

```bash
# For example:
export JAKT_INSTALL=~/.local
# or
export JAKT_INSTALL=$HOME/dev/jakt-install
# or
export JAKT_INSTALL=$PWD/install
```

In the root jakt directory:

```bash
# Configure the cmake project to use clang
cmake -S . -B build -GNinja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$JAKT_INSTALL

# Run the build inside the build directory
cmake --build build -- install
```

In the editors/vscode directory:

```bash
npm install
```

To create the package

```bash
npx vsce package
```

Then install vscode by switching to the Extensions section on the left, then the `...` at the top middle and choose "Install from VSIX..." and choose the package you just created.

In the settings for jakt under Preferences: Open Settings (UI) from the command palate (cmd/ctrl + shift + p), set the Jakt Compiler: Executable Path to your configured `/path/to/bin/jakt`. This must be an absolute path, you cannot use $JAKT_INSTALL here.

Alternatively, modify the `.vscode/settings.json` file to have an entry similar to the following:

```
"jaktLanguageServer.compiler.executablePath": "/path/to/jakt-install/bin/jakt"
```
