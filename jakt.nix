{ stdenv
, fetchFromGitHub
, clang_18
, cmake
, ninja
, pkg-config
, python3
}:

let
  serenity = fetchFromGitHub {
    owner = "serenityos";
    repo = "serenity";
    rev = "05e78dabdbceea46bae7dca52b63dc0a115e7b52"; # latest at the time
    hash = "sha256-ymXQ68Uib1xP4eGPuxm3vRgAIhrVK4rmHdGLfuvsOJU=";
  };
in
stdenv.mkDerivation {
  name = "jakt-unwrapped";
  src = ./.;

  nativeBuildInputs = [
    pkg-config
    cmake
    ninja
  ];

  buildInputs = [
    clang_18
    python3
  ];

  cmakeFlags = [
    "-DCMAKE_CXX_COMPILER=${clang_18}/bin/clang++"
    "-DSERENITY_SOURCE_DIR=${serenity}"
    "-DCMAKE_INSTALL_BINDIR=bin"
  ];
}
