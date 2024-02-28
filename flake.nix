{
  description = "The Jakt Programming Language";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }: utils.lib.eachDefaultSystem (system: let
    pkgs = import nixpkgs { inherit system; };

    jakt = pkgs.callPackage ({ callPackage, symlinkJoin, makeWrapper, clang_16 }: let
      jakt-unwrapped = callPackage ./jakt.nix {};
    in symlinkJoin {
      name = "jakt";

      paths = [ jakt-unwrapped ];
      nativeBuildInputs = [ makeWrapper ];

      postBuild = ''
        wrapProgram $out/bin/jakt_stage0 \
          --prefix PATH : ${clang_16}/bin

        wrapProgram $out/bin/jakt_stage1 \
          --prefix PATH : ${clang_16}/bin
      '';

      passthru.unwrapped = jakt-unwrapped;
    }) {};
  in {
    packages.jakt-unwrapped = jakt.unwrapped;
    packages.jakt = jakt;
    packages.default = jakt;

    devShells.default = pkgs.mkShell {
      packages = let
        inherit (jakt.unwrapped) buildInputs nativeBuildInputs;
      in buildInputs ++ nativeBuildInputs;
    };
  });
}
