# Fast will break some prgrams, but without it some will fail to compile.
LDF     ?= /opt/adapteva/esdk/bsps/current/fast.ldf
#LDF     ?= /opt/adapteva/esdk/bsps/current/internal.ldf
# Optimizations will break some programs
#CFLAGS   = -DROWS=63 -DCOLS=64 -DFIRST_CORE=0x40 -g -O0 -Wall -Wno-unused -Werror -ffast-math -falign-functions=16
#CFLAGS   = -DROWS=4 -DCOLS=4 -DFIRST_CORE=0x808 -g -O0 -Wall -Wno-unused -Werror -ffast-math -falign-functions=16
CFLAGS   += -g -O0 -Wall -Wno-unused -Werror -ffast-math -falign-functions=8
CC       = e-gcc
LDFLAGS  = -T$(LDF)
LDLIBS   = -le-lib

SRCS     = $(shell find . -name "*.c")
BINS     = $(SRCS:.c=)

all: $(BINS)

clean:
	rm -f $(BINS) zigzag/log.8*

