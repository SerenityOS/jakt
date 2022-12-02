{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell
{
  name = "jakt";

  nativeBuildInputs = with pkgs; [
    pkgconfig
    cmake
    ninja
    clang_14
  ];
}
