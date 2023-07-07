#!/bin/bash
gcc src/*.c src/game/*.c src/states/*.c -std=c99 -Wall -Iinclude/ -Llib/ -Wl,-rpath='$ORIGIN/../lib/' -lraylib -ldl -o ./bin/snake