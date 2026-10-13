# Appimage Manager (Rust)
## Version Alpha-2.1.1

# What is It?
A Simple Appimage Manager in GTK4.0

# Install Dependencies
## Debian/Ubuntu
```sh
sudo apt install build-essential pkg-config cargo rustc rustfmt rust-clippy libgtk-4-dev libglib2.0-dev libcairo2-dev libpango1.0-dev libgdk-pixbuf-2.0-dev libgraphene-1.0-dev libadwaita-1-dev
```

## Fedora
```sh
sudo dnf install gcc pkgconf-pkg-config cargo rust rustfmt clippy rust-src gtk4-devel glib2-devel cairo-devel pango-devel gdk-pixbuf2-devel graphene-devel libadwaita-devel
```

## Arch
```sh
sudo pacman -S base-devel pkgconf rust rust-src gtk4 glib2 cairo pango gdk-pixbuf2 graphene libadwaita
```

## NixOS
Already have a "shell.nix" in Project<br>
```sh
nix-shell
```

# Compile
Run:<br>
```sh
cargo build --release
```
The exit path is "target/release/appimage-manager"

# Extra
This project was a "shell.nix" file, for NixOS Development (Although it is one of the few systems where AppImages don't work. But I Develop This application in NixOS btw)<br>
This project is in Alpha release, so the code is officialy not good enough.<br>
In future releases this will change. I will impruve the code to turn them more efficient.<br>
