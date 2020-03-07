#!/bin/bash

g++ gggtkmmsplash.cpp -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`

