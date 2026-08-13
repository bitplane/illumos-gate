#
# Native symbol table dumper used while building illumos archives.
#

PROG =		nm

include		../../Makefile.tools
include		$(SRC)/cmd/sgs/Makefile.com
include		../Makefile.com

OBJS =		objs/nm.o
LDLIBS =	-L../libconv -L../libelf -lconv -lelf
NATIVE_LIBS +=	libc.so

include		$(SRC)/Makefile.native

.KEEP_STATE:

install: $(ROOTONBLDMACHPROG)

$(PROG): $(OBJS)
	$(LINK.c) $(OBJS) -o $@ $(LDLIBS)
	$(POST_PROCESS)

$(OBJS): objs

objs:
	-@ mkdir -p $@

objs/%.o: $(SRC)/cmd/sgs/nm/common/%.c
	$(COMPILE.c) -o $@ $<
	$(POST_PROCESS_O)

POST_PROCESS =	:
