{ pkgs ? import <nixpkgs> { }, }:
pkgs.mkShell {
  packages = with pkgs; [ bear ];

  nativeBuildInputs = with pkgs; [
    pkg-config
    llvmPackages_latest.clang
    gcc_latest
  ];

  buildInputs = with pkgs; [ gtest gbenchmark llvmPackages_13.openmp ];
}
