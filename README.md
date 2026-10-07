# Bits Manipulation Cryptography
## Version Alpha-1.0.0

# What is It?
A Simple Appimage Manager in GTK4.0

# Dependencies
- C++17
- gcc
- gtkmm4

# How to Compile
You Can Use The Built-in Script to Compile<br>
Or can use this command to compile:<br>
```sh
g++ main.cpp -o AppImage-Manager.bin -std=c++17 $(pkg-config --cflags --libs gtkmm-4.0)
```
Also has a debug script, which can automatically execute the application (But delete binary when application is closed)<br>

# Extra
This project was a "shell.nix" file, for NixOS Development (Although it is one of the few systems where AppImages don't work. But I Develop This application in NixOS btw)<br>
This project is in Alpha release, so the code is officialy not good enough.<br>
In future releases this will change. I will impruve the code to turn them more efficient.<br>
