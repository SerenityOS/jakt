#!/usr/bin/env bash

error_and_exit () {
    MESSAGE=$1
    echo "$MESSAGE"
    exit
}

echo "Updating vscode extension"

# navigate to root of project
SRIPT_FULL_PATH=$(realpath -- "$0")
SCRIPT_DIR=$(dirname -- "$SRIPT_FULL_PATH")
PROJECT_ROOT=$SCRIPT_DIR/..
cd "$PROJECT_ROOT" || error_and_exit "Failed to navigate to project root"

# delete old vsix if it exists
VSIX_FILE=$(find ./editors/vscode -maxdepth 1 -type f -name "*.vsix")
if [ -n "$VSIX_FILE" ]
then
    echo "Found VSIX. Removing it."
    for f in $VSIX_FILE; do
        rm "$f"
    done
fi

# uninstall old version of extension if needed
if code --list-extensions | grep -q jakt
then
    echo "Found extension. Uninstalling it."
    code --uninstall-extension JT.jakt
fi

# build and install the new version of the compiler
echo "Building and installing most recent version of jakt compiler"
cmake --build build -- install

# build new vsix
cd ./editors/vscode || error_and_exit "Failed to navigate to vscode directory"
npm i
( cd client; npm i; )

npx vsce package
NEW_VSIX_PATH=$(find . -maxdepth 1 -type f -name "*.vsix" -exec realpath {} +)
cd - || error_and_exit "Failed to navigate back to project root"

# install new vsix
code --install-extension "$NEW_VSIX_PATH"

if code --list-extensions | grep -q jakt
then
    echo "Successfully updated"
else
    echo "Something went wrong"
fi
