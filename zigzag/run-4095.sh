#!/bin/bash
ROWS=64
COLS=64
epiphany-elf-sim --ext-ram-size 0 --ext-ram-base 0 -f 0 -r $ROWS -c $COLS zigzag4095
