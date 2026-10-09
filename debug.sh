#!/bin/bash

clear

g++ main.cpp -o main.bin -std=c++17 $(pkg-config --cflags --libs gtkmm-4.0)
./main.bin
echo $?

rm ./main.bin
