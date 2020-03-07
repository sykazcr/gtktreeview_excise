#!/bin/bash

echo g++ gggtkmmsplash.cpp -Wall -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`

g++ gggtkmmsplash.cpp -Wall -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`

