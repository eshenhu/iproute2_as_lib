OBJ=test.o

include ../iproute2/config.mk

IPROUTE2_PREFIX := ../iproute2

VER = $(shell cd $(IPROUTE2_PREFIX) && git describe --abbrev=0 --tags | cut -c2-)

CC := gcc
HOSTCC ?= $(CC)
DEFINES += -D_GNU_SOURCE
# Turn on transparent support for LFS
DEFINES += -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
CCOPTS = -O2
WFLAGS := -Wall -Wstrict-prototypes  -Wmissing-prototypes
WFLAGS += -Wmissing-declarations -Wold-style-definition -Wformat=2

CFLAGS := $(WFLAGS) $(CCOPTS) -I../include -I$(IPROUTE2_PREFIX)/include  -I$(IPROUTE2_PREFIX)/include/uapi $(DEFINES) $(CFLAGS)

LDLIBS += libiproute2.so.$(VER) -ldl 
LDFLAGS += -Wl,-export-dynamic -L $(IPROUTE2_PREFIX)/lib/

TARGETS=demo

all: $(TARGETS)

demo: $(OBJ)
	cp -f $(IPROUTE2_PREFIX)/lib/libiproute2.so.$(VER) ./
	$(QUIET_LINK)$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@
