/*
 * Copyright 2026 Gary Willoughby
 *
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 */

#ifndef _TOOLS_VTFONTCVT_LINUX_SYS_QUEUE_H
#define	_TOOLS_VTFONTCVT_LINUX_SYS_QUEUE_H

#include_next <sys/queue.h>

#ifndef TAILQ_FOREACH_SAFE
#define	TAILQ_FOREACH_SAFE(var, head, field, tvar)\
	for ((var) = TAILQ_FIRST(head);\
	    (var) != NULL && ((tvar) = TAILQ_NEXT(var, field), 1);\
	    (var) = (tvar))
#endif

#endif /* _TOOLS_VTFONTCVT_LINUX_SYS_QUEUE_H */
