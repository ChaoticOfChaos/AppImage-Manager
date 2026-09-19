{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    nativeBuildInputs = with pkgs; [
        pkg-config
        gcc
    ];

    buildInputs = with pkgs; [
        gtkmm4
    ];
}
