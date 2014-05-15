#!/bin/bash
#ERUN_PATH=
# Trailing / important
#ERUN_PATH=~/usr/esdk/bin/


# Upper leftmost core started last
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x809 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.809 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x80a --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.80a &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x80b --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.80b &

${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x848 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.848 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x849 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.849 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x84a --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.84a &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x84b --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.84b &

${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x888 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.888 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x889 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.889 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x88a --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.88a &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x88b --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.88b &

${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x8c8 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.8c8 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x8c9 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.8c9 &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x8ca --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.8ca &
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x8cb --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag &> log.8cb &

# Upper leftmost core
${ERUN_PATH}epiphany-elf-run -v --e-coreid 0x808 --e-rows 4 --e-cols 4 --e-first-core 0x808 zigzag 2>&1 | tee log.808
