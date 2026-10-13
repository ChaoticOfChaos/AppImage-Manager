{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    nativeBuildInputs = with pkgs; [
        pkg-config
        cargo
        rustc
        rustfmt
        clippy
        wrapGAppsHook4
    ];

    buildInputs = with pkgs; [
        gtk4
        glib
        cairo
        pango
        gdk-pixbuf
        graphene
        libadwaita
    ];

    RUST_SRC_PATH="${pkgs.rustPlatform.rustLibSrc}";
}
