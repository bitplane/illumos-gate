/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 */

#ifndef _CTF_COMPAT_LINUX_H
#define	_CTF_COMPAT_LINUX_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <elf.h>
#include <pthread.h>

/* Types used by the private illumos CTF interfaces. */
typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;
typedef int64_t off64_t;

typedef enum {
	B_FALSE = 0,
	B_TRUE = 1
} boolean_t;

typedef pthread_mutex_t mutex_t;
typedef pthread_cond_t cond_t;
typedef pthread_t thread_t;

extern char *program_invocation_name;

static __inline__ const char *
getexecname(void)
{
	return (program_invocation_name);
}

long long strtonum(const char *, long long, long long, const char **);

#define	USYNC_THREAD	0
#define	LOCK_ERRORCHECK	0
#define	ERRORCHECKMUTEX	PTHREAD_MUTEX_INITIALIZER
#define	mutex_enter(mp)	((void) pthread_mutex_lock(mp))
#define	mutex_exit(mp)	((void) pthread_mutex_unlock(mp))
#define	MUTEX_HELD(mp)	(1)

static __inline__ int
mutex_init(mutex_t *mutex, int type, void *arg)
{
	(void) type;
	(void) arg;
	return (pthread_mutex_init(mutex, NULL));
}

#define	mutex_destroy(mp)	pthread_mutex_destroy(mp)
#define	mutex_lock(mp)		pthread_mutex_lock(mp)
#define	mutex_unlock(mp)	pthread_mutex_unlock(mp)

static __inline__ int
cond_init(cond_t *condition, int type, void *arg)
{
	(void) type;
	(void) arg;
	return (pthread_cond_init(condition, NULL));
}

#define	cond_destroy(cp)	pthread_cond_destroy(cp)
#define	cond_wait(cp, mp)	pthread_cond_wait((cp), (mp))
#define	cond_broadcast(cp)	pthread_cond_broadcast(cp)

static __inline__ int
thr_create(void *stack, size_t size, void *(*start)(void *), void *arg,
    long flags, thread_t *thread)
{
	(void) stack;
	(void) size;
	(void) flags;
	return (pthread_create(thread, NULL, start, arg));
}

static __inline__ int
thr_join(thread_t thread, thread_t *departed, void **status)
{
	if (departed != NULL)
		*departed = thread;
	return (pthread_join(thread, status));
}

static __inline__ size_t
strlcpy(char *dst, const char *src, size_t size)
{
	size_t length = strlen(src);

	if (size != 0) {
		size_t copy = length < size - 1 ? length : size - 1;
		(void) memcpy(dst, src, copy);
		dst[copy] = '\0';
	}

	return (length);
}

static __inline__ size_t
strlcat(char *dst, const char *src, size_t size)
{
	size_t dst_length = strnlen(dst, size);
	size_t src_length = strlen(src);

	if (dst_length < size) {
		size_t available = size - dst_length - 1;
		size_t copy = src_length < available ? src_length : available;

		(void) memcpy(dst + dst_length, src, copy);
		dst[dst_length + copy] = '\0';
	}

	return (dst_length + src_length);
}

/* The native threading interface above satisfies <thread.h>. */
#define	_THREAD_H

/* Linux exposes the ELF interface as <elf.h>, not <sys/elf.h>. */
#define	_SYS_ELF_H

#endif /* _CTF_COMPAT_LINUX_H */
