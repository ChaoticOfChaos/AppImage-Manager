#!/bin/bash
g++ main.cpp -o main.bin -std=c++17 $(pkg-config --cflags --libs gtkmm-4.0)
