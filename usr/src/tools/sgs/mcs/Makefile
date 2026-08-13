#
# Native object-file comment editor used while building illumos objects.
#

include		../../Makefile.tools
include		$(SRC)/cmd/sgs/mcs/Makefile.com
include		../Makefile.com

NATIVEOBJS =	assfail.o
OBJS =		$(COMOBJS:%=objs/%) $(SGSCOMMONOBJ:%=objs/%) \
		$(NATIVEOBJS:%=objs/%)
LDLIBS =	-L../libconv -L../libelf -lconv -lelf
NATIVE_LIBS +=	libc.so

include		$(SRC)/Makefile.native

.KEEP_STATE:

ROOTONBLDMACHSTRIP = $(ROOTONBLDBINMACH)/strip

install: $(ROOTONBLDMACHPROG) $(ROOTONBLDMACHSTRIP)

$(ROOTONBLDMACHSTRIP): $(ROOTONBLDMACHPROG)
	$(RM) $@
	$(SYMLINK) mcs $@

include		$(SGSHOME)/mcs/Makefile.targ

NATIVE_MCS_RPATH_illumos =
NATIVE_MCS_RPATH_linux =	-_gcc=-Wl,-rpath,'$$ORIGIN/../../lib/$(MACH)/64'
LDFLAGS +=	$(NATIVE_MCS_RPATH_$(NATIVE_OS))

$(OBJS): objs

objs:
		-@ mkdir -p $@

objs/%.o: $(SRC)/cmd/sgs/mcs/common/%.c
		$(COMPILE.c) -o $@ $<
		$(POST_PROCESS_O)

objs/alist.o: $(SGSCOMMON)/alist.c
		$(COMPILE.c) -o $@ $(SGSCOMMON)/alist.c
		$(POST_PROCESS_O)

objs/assfail.o: $(SGSCOMMON)/assfail.c
		$(COMPILE.c) -o $@ $(SGSCOMMON)/assfail.c
		$(POST_PROCESS_O)

POST_PROCESS =	:
