#!/usr/bin/env bash

gcc `pkg-config --cflags gtk+-3.0` -Wall -g -D_DEFAULT_SOURCE --std=c99 -Iheaders/ *.c -lm `pkg-config --libs gtk+-3.0`

./a.out