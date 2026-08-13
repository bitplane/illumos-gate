#
# Native archive editor used while building illumos objects.
#

include		../../Makefile.tools
include		$(SRC)/cmd/sgs/ar/Makefile.com
include		../Makefile.com

SGSMSGCOM =	$(SRC)/cmd/sgs/ar/common/ar.msg
SGSMSGALL =	$(SGSMSGCOM)

LDLIBS =	-L../libconv -L../libelf -lconv -lelf
NATIVE_LIBS +=	libc.so

include		$(SRC)/Makefile.native

.KEEP_STATE:

install: $(ROOTONBLDMACHPROG)

include		$(SGSHOME)/ar/Makefile.targ

NATIVE_AR_RPATH_illumos =
NATIVE_AR_RPATH_linux =	-_gcc=-Wl,-rpath,'$$ORIGIN/../../lib/$(MACH)/64'
LDFLAGS +=	$(NATIVE_AR_RPATH_$(NATIVE_OS))

objs/%.o: $(SRC)/cmd/sgs/ar/common/%.c
		$(COMPILE.c) -o $@ $<
		$(POST_PROCESS_O)

POST_PROCESS =	:
