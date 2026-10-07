#!/bin/bash
g++ main.cpp -o AppImage-Manager.bin -std=c++17 $(pkg-config --cflags --libs gtkmm-4.0)
