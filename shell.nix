{ pkgs ? import <nixpkgs> { }, }:
pkgs.mkShell {
  packages = with pkgs; [ gdb lldb ];

  nativeBuildInputs = with pkgs; [
    cmake
    pkg-config
    llvmPackages_latest.clang
    gcc_latest
  ];

  buildInputs = with pkgs; [ gtest gbenchmark ];
}
