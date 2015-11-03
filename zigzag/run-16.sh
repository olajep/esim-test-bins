#!/bin/bash
ROWS=4
COLS=4
epiphany-elf-sim -f 0x808 -r $ROWS -c $COLS zigzag16
