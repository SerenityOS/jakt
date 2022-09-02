# Jakt vscode extension

This is the vscode extension for the Jakt language.

There are no pre-packaged versions of this extension, as changes to language and tooling happen frequently.

## Build instructions

Pick a location to install jakt. This should be a local directory, not a global install directory.
```
# For example:
export JAKT_INSTALL=~/.local
# or
export JAKT_INSTALL=$HOME/dev/jakt-install
# or
export JAKT_INSTALL=$PWD/install
```

In the root jakt directory:
```
> cmake --build build -GNinja -DCMAKE_CXX_COMPILER=clang++-14 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$JAKT_INSTALL
> cmake --build build -- install
```

In the editors/vscode directory:
```
> npm install
```

To create the package
```
> npm install vsce -g
> vsce package
```

Then install vscode by switching to the Extensions section on the left, then the `...` at the top middle and choose "Install from VSIX..." and choose the package you just created.

In the settings for jakt under Preferences: Open Settings (UI) from the command palate (cmd/ctrl + shift + p), set the Jakt Compiler: Executable Path to your configured ``$JAKT_INSTALL/bin/jakt``. The $JAKT_INSTALL variable must be manually expanded to an absolute path for the path in the settings field.

Alternatively, modify the ``.vscode/settings.json`` file to have an entry similar to the following:

```
"jaktLanguageServer.compiler.executablePath": "/path/to/jakt-install/bin/jakt"
```
