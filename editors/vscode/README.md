# Jakt vscode extension

This is the vscode extension for the Jakt language.

There are no pre-packaged versions of this extension, as changes to language and tooling happen frequently.

## Build instructions

In the root jakt directory:
```
> cargo install --path .
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
