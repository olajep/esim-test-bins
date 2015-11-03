#!/bin/bash
ROWS=32
COLS=24
epiphany-elf-sim -f 0x808 -r $ROWS -c $COLS zigzag768
