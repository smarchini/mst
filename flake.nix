{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/master";
  };

  outputs = { self, nixpkgs }:
    let
      pkgsFor = system: import nixpkgs { inherit system; };
      targetSystems = [ "x86_64-linux" ];
    in
    {
      devShells = nixpkgs.lib.genAttrs targetSystems (system:
        let
          pkgs = pkgsFor system;
          mkShellNative = pkgs.mkShell.override { stdenv = pkgs.stdenvAdapters.impureUseNativeOptimizations pkgs.gcc12Stdenv; };
        in
        {
          default = mkShellNative {
            packages = with pkgs; [
              gcc_latest
              llvmPackages_latest.clang

              gtest
              gbenchmark
            ];
          };
        });
    };
}
