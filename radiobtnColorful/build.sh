#!/bin/bash

echo g++ radiott.cpp -Wall -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`

g++ radiott.cpp -Wall -g3 -O0 -o view.elf `pkg-config gtkmm-3.0 --cflags --libs`
