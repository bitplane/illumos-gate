#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Toomas Soome <tsoome@me.com>
# Copyright 2023 OmniOS Community Edition (OmniOSce) Association.
#

CMDDIR=		$(SRC)/cmd/vtfontcvt

include		../Makefile.tools
include		$(CMDDIR)/Makefile.common

VTFONTCVT_NATIVE_LIBS_illumos = libumem.so
NATIVE_LIBS	+= $(VTFONTCVT_NATIVE_LIBS_$(NATIVE_OS))
CPPFLAGS	+= -I$(LZ4)
CPPFLAGS_illumos = -I../../uts/common
CPPFLAGS_linux = -Ilinux -_gcc=-idirafter -_gcc=../../uts/common \
	-_gcc=-include -_gcc=../../uts/common/sys/ccompile.h
CPPFLAGS	+= $(CPPFLAGS_$(NATIVE_OS))
.KEEP_STATE:

all:		$(PROG)

install:	all .WAIT $(ROOTONBLDMACHPROG)

clean:
		$(RM) $(PROG) $(OBJS)

$(PROG):	$(OBJS)
		$(LINK.c) $(OBJS) -o $@ $(LDLIBS)
		$(POST_PROCESS)

%.o:		$(CMDDIR)/%.c
		$(COMPILE.c) -o $@ $<

include		../Makefile.targ
