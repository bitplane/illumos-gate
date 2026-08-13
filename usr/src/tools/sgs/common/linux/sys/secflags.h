/*
 * Native SGS tools need the secflags types exposed by conv.h, but not the
 * illumos process-selection interfaces pulled in by the target header.
 */

#ifndef _SYS_SECFLAGS_H
#define	_SYS_SECFLAGS_H

#include <stdint.h>

typedef uint64_t secflagset_t;

typedef enum {
	PROC_SEC_ASLR = 0,
	PROC_SEC_FORBIDNULLMAP,
	PROC_SEC_NOEXECSTACK
} secflag_t;

extern secflagset_t secflag_to_bit(secflag_t);

#endif /* _SYS_SECFLAGS_H */
