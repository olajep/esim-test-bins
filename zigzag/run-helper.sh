#!/bin/bash
set -e
function kill_children {
    sleep 1
    for p in $(jobs -p); do
        kill $p &>/dev/null || true;
    done;
    wait &> /dev/null;
    rm -f /dev/shm/esim.$(id -u)
    exit 1;
}


[[ $1 == "" ]] && (echo usage: $0 PROGRAM; exit 1)
PROGRAM=$1

which epiphany-elf-run &>/dev/null ||
    (echo Need epiphany-elf-run in path; exit 1)

DEFAULT_ROWS=4
DEFAULT_COLS=4
DEFAULT_FIRST_CORE=0x808
DEFAULT_EXT_RAM_SIZE=32
DEFAULT_EXT_RAM_BASE=0x8e000000

ROWS=${ROWS-$DEFAULT_ROWS}
COLS=${COLS-$DEFAULT_COLS}
FIRST_CORE=${FIRST_CORE-$DEFAULT_FIRST_CORE}
EXT_RAM_SIZE=${EXT_RAM_SIZE-$DEFAULT_EXT_RAM_SIZE}
EXT_RAM_BASE=${EXT_RAM_BASE-$DEFAULT_EXT_RAM_BASE}

# Adjust LEADER if both first row and col are 0. (No core can have id 0)
if ( [[ $FIRST_CORE -eq 0 ]] ); then
    LEADER=0x1
else
    LEADER=$FIRST_CORE
fi

FIRST_ROW=$[$FIRST_CORE/64]
FIRST_COL=$[$FIRST_CORE%64]
LEADER_ROW=$[$LEADER/64]
LEADER_COL=$[$LEADER%64]

MESH_CFG="--e-rows ${ROWS} --e-cols ${COLS} --e-first-core ${FIRST_CORE} \
          --e-ext-ram-size ${EXT_RAM_SIZE} --e-ext-ram-base ${EXT_RAM_BASE}"


# Create log dir
mkdir -p log

# Make sure we kill child processes before we exit
trap "trap '' INT TERM EXIT;kill_children" INT TERM EXIT

# Run all sim processes except LEADER core in background
for r in $(seq $FIRST_ROW $[$FIRST_ROW+$ROWS-1]);do
  for c in $(seq $FIRST_COL $[$FIRST_COL+$COLS-1]); do
    coreid=$(printf "0x%0.3x" $[$r*64 + $c])
    if ( [[ $coreid -eq 0 ]] ); then continue; fi

    if ! ( [[ $r -eq $LEADER_ROW ]] && [[ $c -eq $LEADER_COL ]] ) ; then
      epiphany-elf-run \
        -v --e-coreid $coreid $MESH_CFG $PROGRAM &> log/log.$coreid &
    fi
  done
done


# Run LEADER core in foreground
coreid=$(printf "0x%0.3x" $LEADER)
epiphany-elf-run \
  -v --e-coreid $coreid $MESH_CFG $PROGRAM 2>&1 | tee log/log.$coreid


# Wait for child processes to exit
wait &>/dev/null
