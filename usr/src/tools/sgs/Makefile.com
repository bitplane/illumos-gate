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

# Copyright 2019, Richard Lowe.

CPPFLAGS =	-I. -I$(SRCDIR) -I$(SRCDIR)/common \
	$(NATIVE_SGS_COMPAT_INCLUDES) \
	-I$(SGSHOME)/include -I$(SGSHOME)/include/$(MACH) \
	-I../include $(CPPFLAGS.native) $(NATIVE_SGS_COMPAT) \
	$(NATIVE_SGS_TARGET_INCLUDES) \
	-I$(ELFCAP) -DNATIVE_BUILD

# Native linker tools do not carry target CTF in their intermediate objects.
POST_PROCESS_O=	:
LDFLAGS=	$(LDFLAGS_$(NATIVE_OS))
LDCHECKS=	$(LDCHECKS_$(NATIVE_OS))
DYNFLAGS=	$(DYNFLAGS_$(NATIVE_OS))
