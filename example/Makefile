OBJ_RAW=ip_api.o test_raw.o
OBJ_BIN=ip_bin.o

include ../iproute2/config.mk

IPROUTE2_PREFIX := ../iproute2

VER = $(shell cd $(IPROUTE2_PREFIX) && git describe --abbrev=0 --tags | cut -c2-)

CC := g++
HOSTCC ?= $(CC)
DEFINES += -D_GNU_SOURCE
# Turn on transparent support for LFS
DEFINES += -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE

CCOPTS = -O2 -std=c++11
WFLAGS := -Wall 
WFLAGS += -Wmissing-declarations -Wformat=2

CFLAGS := $(WFLAGS) $(CCOPTS) -I../include -I$(IPROUTE2_PREFIX)/include  -I$(IPROUTE2_PREFIX)/include/uapi $(DEFINES) $(CFLAGS)

LDLIBS += libiproute2.so.$(VER) -ldl 
LDFLAGS += -Wl,-export-dynamic -L $(IPROUTE2_PREFIX)/lib/

TARGETS=test_raw

all: $(TARGETS)

test_raw: $(OBJ_RAW)
	cp -f $(IPROUTE2_PREFIX)/lib/libiproute2.so.$(VER) ./
	$(QUIET_LINK)$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -rf *.o
	rm -rf $(TARGETS)