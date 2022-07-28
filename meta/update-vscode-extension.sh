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

# build the new version of the compiler
echo "Building the most recent version of the jakt compiler"
cmake -B build -GNinja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=RelWithDebInfo && ninja -C build

# build new vsix
cd ./editors/vscode || error_and_exit "Failed to navigate to vscode directory"
npx vsce package
NEW_VSIX_PATH=$(find . -maxdepth 1 -type f -name "*.vsix" -exec realpath {} +)
cd - || error_and_exit "Failed to navigate back to project root"

# install new vsix
code --install-extension "$NEW_VSIX_PATH"

if code --list-extensions | grep -q jakt
then
    echo "Successfully updated."
    echo -e "\033[33m" # Yellow text color
    echo -e "Make sure you set the \`Jakt Language Server > Compiler: Executable Path\` to \`build/jakt_stage3\`.\n"
    echo -e "\033[0m" # reset text color
else
    echo "Something went wrong"
fi
