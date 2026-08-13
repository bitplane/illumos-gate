#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License, Version 1.0 only
# (the "License").  You may not use this file except in compliance
# with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 1996 by Sun Microsystems, Inc.
# All rights reserved.

include		../../Makefile.tools
include		$(SRC)/cmd/sgs/ld/Makefile.com
include		../Makefile.com

NATIVE_LD_UMEM_illumos =	-lumem
NATIVE_LD_UMEM_linux =
NATIVE_LD_LIBS_illumos =	libumem.so
NATIVE_LD_LIBS_linux =

LDLIBS =	$(NATIVE_LD_UMEM_$(NATIVE_OS)) -L../libconv \
		-L$(ROOTONBLDLIBMACH64) -lld -lelf -lconv
NATIVE_LIBS +=	libc.so $(NATIVE_LD_LIBS_$(NATIVE_OS))
MAPFILES =	$(SRCDIR)/common/mapfile-intf
RPATH =		'-R$$ORIGIN/../../lib/$(MACH)/64'

include		$(SRC)/Makefile.master.64
include		$(SRC)/Makefile.native

install: $(ROOTONBLDMACH64PROG)

.KEEP_STATE:

include		$(SGSHOME)/ld/Makefile.targ

NATIVE_LD_RPATH_illumos =
NATIVE_LD_RPATH_linux =	-_gcc=-Wl,-rpath,'$$ORIGIN/../../lib/$(MACH)/64'
LDFLAGS +=	$(NATIVE_LD_RPATH_$(NATIVE_OS))

POST_PROCESS_illumos =	$(PROCESS_COMMENT) $@ ; $(PROCESS_CTF) ; \
			$(STRIP_STABS) ; $(ELFSIGN_OBJECT)
POST_PROCESS_linux =	:
POST_PROCESS =		$(POST_PROCESS_$(NATIVE_OS))
