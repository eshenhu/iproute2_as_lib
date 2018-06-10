OBJ_BIN=ip_bin.o

SRC_LIB=ip_api.c
OBJ_LIB=ip_api.o

include ../iproute2/config.mk

IPROUTE2_PREFIX := ../iproute2

VER = $(shell cd $(IPROUTE2_PREFIX) && git describe --abbrev=0 --tags | cut -c2-)

CC := g++
HOSTCC ?= $(CC)
DEFINES += -D_GNU_SOURCE
# Turn on transparent support for LFS
DEFINES += -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
CCOPTS = -O2 
WFLAGS := -Wall 
WFLAGS += -Wmissing-declarations -Wformat=2

CFLAGS := $(WFLAGS) $(CCOPTS) -I../include -I$(IPROUTE2_PREFIX)/include  -I$(IPROUTE2_PREFIX)/include/uapi $(DEFINES) $(CFLAGS)

LDLIBS += libiproute2.so.$(VER) -ldl 
LDFLAGS += -Wl,-export-dynamic -L $(IPROUTE2_PREFIX)/lib/

TARGETS=ip

all: $(TARGETS)

ip: $(OBJ_BIN)
	cp -f $(IPROUTE2_PREFIX)/lib/libiproute2.so.$(VER) ./
	$(QUIET_LINK)$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@
	strip $@

lib: $(OBJ_LIB)
	$(CC) -shared -fPIC -o libiproute2_api.so.$(VER) $(OBJ_LIB) -lc
	strip libiproute2_api.so.$(VER) 

clean:
	rm -rf $(TARGETS)
	rm -rf *.o
	rm -rf libiproute2.so.$(VER)
	rm -rf libiproute2_api.so.$(VER)
