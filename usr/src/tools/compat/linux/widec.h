/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version 1.0
 * of the CDDL.
 */

#ifndef _TOOLS_LINUX_WIDEC_H
#define	_TOOLS_LINUX_WIDEC_H

#include <wchar.h>
#include <stdarg.h>
#include <stdio.h>

#define	wscpy	wcscpy
#define	wslen	wcslen
#define	wscmp	wcscmp
#define	wcsetno(c)	((c) <= 0x7f ? 0 : 1)
#define	watoi(s)	((int)wcstol((s), NULL, 10))

extern int wsprintf(wchar_t *, const char *, ...);
extern int widec_fprintf(FILE *, const char *, ...);
extern int widec_vfprintf(FILE *, const char *, va_list);

#define	fprintf	widec_fprintf
#define	vfprintf	widec_vfprintf

#endif /* _TOOLS_LINUX_WIDEC_H */
