#!/bin/bash
ROWS=8
COLS=8
epiphany-elf-sim -f 0x808 -r $ROWS -c $COLS zigzag64
