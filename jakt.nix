{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell
{
  name = "jakt";

  nativeBuildInputs = with pkgs; [
    pkgconfig
    cmake
    ninja
    python3
    clang_14
  ];
}
