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
BINS     += zigzag/zigzag16 zigzag/zigzag64 zigzag/zigzag768 zigzag/zigzag4095

ZIGZAG_16_CFLAGS    = -DROWS=4  -DCOLS=4  -DFIRST_CORE=0x808
ZIGZAG_64_CFLAGS    = -DROWS=8  -DCOLS=8  -DFIRST_CORE=0x808
ZIGZAG_768_CFLAGS   = -DROWS=32 -DCOLS=24 -DFIRST_CORE=0x808
ZIGZAG_4095_CFLAGS  = -DROWS=64 -DCOLS=64 -DFIRST_CORE=0
ZIGZAG_4095_LDFLAGS = -T./zigzag/extraminternal.ldf

all: $(BINS)

zigzag/zigzag16: zigzag/zigzag.c
	$(CC) -o $@ $(ZIGZAG_16_CFLAGS) $(CFLAGS) $< $(LDLIBS) -Wl,$(LDFLAGS)

zigzag/zigzag64: zigzag/zigzag.c
	$(CC) -o $@ $(ZIGZAG_64_CFLAGS) $(CFLAGS) $< $(LDLIBS) -Wl,$(LDFLAGS)

zigzag/zigzag768: zigzag/zigzag.c
	$(CC) -o $@ $(ZIGZAG_768_CFLAGS) $(CFLAGS) $< $(LDLIBS) -Wl,$(LDFLAGS)

zigzag/zigzag4095: zigzag/zigzag.c
	$(CC) -o $@ $(ZIGZAG_4095_CFLAGS) $(CFLAGS) $< $(LDLIBS) -Wl,$(ZIGZAG_4095_LDFLAGS)

clean:
	rm -f $(BINS) zigzag/log/log.*

