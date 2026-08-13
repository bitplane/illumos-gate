/*
 * Copyright 2026 Gary Willoughby
 *
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 */

#ifndef _TOOLS_VTFONTCVT_LINUX_SYS_SYSMACROS_H
#define	_TOOLS_VTFONTCVT_LINUX_SYS_SYSMACROS_H

#include <stdint.h>
#include_next <sys/sysmacros.h>

#ifndef __DECONST
#define	__DECONST(type, var)	((type)(uintptr_t)(const void *)(var))
#endif

#endif /* _TOOLS_VTFONTCVT_LINUX_SYS_SYSMACROS_H */
