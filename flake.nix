{
  description = "The Jakt Programming Language";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }: utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };

      clang_18 = pkgs.clang_18;

      jakt = pkgs.callPackage
        ({ callPackage, symlinkJoin, makeWrapper }:
          let
            jakt-unwrapped = callPackage ./jakt.nix { inherit clang_18; };
          in
          symlinkJoin {
            name = "jakt";

            paths = [ jakt-unwrapped ];
            nativeBuildInputs = [ makeWrapper ];

            postBuild = ''
              wrapProgram $out/bin/jakt_stage0 \
                --prefix PATH : ${clang_18}/bin

              wrapProgram $out/bin/jakt_stage1 \
                --prefix PATH : ${clang_18}/bin
            '';

            passthru.unwrapped = jakt-unwrapped;
          })
        { };
    in
    {
      packages.jakt-unwrapped = jakt.unwrapped;
      packages.jakt = jakt;
      packages.default = jakt;

      devShells.default = pkgs.mkShell {
        packages =
          let
            inherit (jakt.unwrapped) buildInputs nativeBuildInputs;
          in
          buildInputs ++ nativeBuildInputs;
      };
    });
}
