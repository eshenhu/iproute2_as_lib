VER = $(shell cd ./iproute2 && git describe --abbrev=0 --tags | cut -c2-)

#include ./iproute2/config.mk

test:
	echo "make test $(VER)"
	$(MAKE) $(MFLAGS) -C example

lib:substitution
	echo "make library"	
	make -C iproute2 -f Makefile.0 libiproute2

substitution:
	echo "making sbustitution"
	cp -f include/ip.h iproute2/include/
	sed 's/main/main_entry_point/g' iproute2/ip/ip.c > iproute2/ip/ip_as_lib.c	
	sed -i -e '/#include "color.h"/a #include "ip.h"' iproute2/ip/ip_as_lib.c
	sed 's/ip\.o/ip_as_lib\.o/g' iproute2/ip/Makefile > iproute2/ip/Makefile.0
	sed -i -e '$$alibiproute2: $$(IPOBJ) $$(LIBNETLINK)\n\t$$(QUIET_LINK)$$(CC) $$^ $$(LDFLAGS) -shared -fPIC -o ../lib/libiproute2.so.$(VER) $$(LDLIBS)' iproute2/ip/Makefile.0
	sed -i '/^LDFLAGS/s/$$/ -fPIC/' iproute2/ip/Makefile.0
	
	cp iproute2/Makefile iproute2/Makefile.0
	sed -i -e '/^CFLAGS/a CFLAGS += -fPIC' iproute2/Makefile.0
	sed -i -e '$$alibiproute2:config.mk\n\t$$(MAKE) $$(MFLAGS) -C lib \n\t$$(MAKE) -C ip clean\n\t$$(MAKE) $$(MFLAGS) -C ip -f Makefile.0 libiproute2' iproute2/Makefile.0
