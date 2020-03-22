#!/bin/bash

echo g++ colorgrid.cpp -Wall -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`

g++ colorgrid.cpp -Wall -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`

