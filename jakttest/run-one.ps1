# Run one jakt test

# https://github.com/microsoft/vswhere/wiki/Start-Developer-Command-Prompt#using-powershell
$installationPath = Invoke-Expression "& '${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe' -prerelease -latest -property installationPath"

# https://developercommunity.visualstudio.com/t/x64-developer-powershell-for-vs-2019/943058#T-N1062776
Import-Module "$installationPath\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell -VsInstallPath "$installationPath" -DevCmdArguments '-arch=x64 -no_logo'

cd $Args[0]

# Since we're running the output binary from a different
# working directory, we need the full path of the binary.
$temp_dir = resolve-path $Args[1]
$file = $Args[2]

$jakt_args = @("$file",
    "-B",
    "$temp_dir",
    "-o",
    "output",
    "-S"
)

# Generate C++ code
$jakt_process = Start-Process .\build\jakt.exe -ArgumentList $jakt_args -RedirectStandardError "$temp_dir\compile_jakt.err" -PassThru -Wait -NoNewWindow
if ($jakt_process.ExitCode -ne 0) {
	exit 3
}

$clang_args = @( "-fcolor-diagnostics",
    "--target=x86_64-pc-windows-msvc",
    "-std=c++20",
    "-Wno-unknown-warning-option",
    "-Wno-trigraphs",
    "-Wno-parentheses-equality",
    "-Wno-unqualified-std-cast-call",
    "-Wno-user-defined-literals",
    "-Wno-deprecated-declarations",
    "-Wno-unknown-attributes",
    "-fuse-ld=lld",
    "-fno-exceptions",
    "-O0",
    "-Iruntime",
    "-DJAKT_CONTINUE_ON_PANIC",
    "-o",
    "$temp_dir/output.exe",
    "$temp_dir\output.cpp"
)

$clang_process = Start-Process clang++ -ArgumentList $clang_args -RedirectStandardError "$temp_dir\compile_cpp.err" -PassThru -Wait -NoNewWindow

if ($clang_process.ExitCode -ne 0) {
	exit 2
}

# Run the executable inside the parent directory of the test file
cd (Get-Item $file).DirectoryName
$test_process = Start-Process "$temp_dir\output.exe" -RedirectStandardOutput "$temp_dir\runtest.out" -RedirectStandardError "$temp_dir\runtest.err" -PassThru -Wait -NoNewWindow

if ($test_process.ExitCode -ne 0) {
	exit 1
}

