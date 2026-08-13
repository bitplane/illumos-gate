/*
 * Native compatibility used while building the illumos link-editor on Linux.
 */

#ifndef _SGS_COMPAT_LINUX_H
#define	_SGS_COMPAT_LINUX_H

#include <stdint.h>
#include <libintl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;
typedef long long longlong_t;
typedef unsigned long long u_longlong_t;

typedef enum {
	B_FALSE = 0,
	B_TRUE = 1
} boolean_t;

typedef pthread_mutex_t mutex_t;
typedef pthread_cond_t cond_t;
typedef pthread_t thread_t;
typedef pthread_rwlock_t rwlock_t;
typedef pthread_key_t thread_key_t;
#define	_SYS_AUXV_H
typedef struct mmapobj_result {
	caddr_t mr_addr;
	size_t mr_msize;
	size_t mr_fsize;
	size_t mr_offset;
	uint_t mr_prot;
	uint_t mr_flags;
} mmapobj_result_t;
typedef struct {
	int a_type;
	union {
		long a_val;
		void *a_ptr;
		void (*a_fcn)(void);
	} a_un;
} auxv_t;

#define	_INT64_TYPE
#define	MR_PADDING	0x1
#define	MR_HDR_ELF	0x2
#define	MR_TYPE_MASK	0x0000ffff
#define	MR_GET_TYPE(value)	((value) & MR_TYPE_MASK)
#define	USYNC_THREAD	0
#define	DEFAULTMUTEX	PTHREAD_MUTEX_INITIALIZER
#define	THR_ONCE_KEY	((thread_key_t)-1)
#define	mutex_lock(mp)	pthread_mutex_lock(mp)
#define	mutex_unlock(mp)	pthread_mutex_unlock(mp)
#define	rw_rdlock(lp)	pthread_rwlock_rdlock(lp)
#define	rw_wrlock(lp)	pthread_rwlock_wrlock(lp)
#define	rw_unlock(lp)	pthread_rwlock_unlock(lp)
#define	RW_LOCK_HELD(lp)	(1)
#define	MUTEX_HELD(mp)	(1)
#define	MAX(a, b)	((a) > (b) ? (a) : (b))

static __inline__ int
mutex_init(mutex_t *mutex, int type, void *arg)
{
	(void) type;
	(void) arg;
	return (pthread_mutex_init(mutex, NULL));
}

static __inline__ int
rwlock_init(rwlock_t *lock, int type, void *arg)
{
	(void) type;
	(void) arg;
	return (pthread_rwlock_init(lock, NULL));
}

static __inline__ int
thr_main(void)
{
	return (syscall(SYS_gettid) == getpid());
}

static __inline__ int
thr_keycreate_once(thread_key_t *key, void (*destructor)(void *))
{
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	int error = 0;

	(void) pthread_mutex_lock(&lock);
	if (*key == THR_ONCE_KEY)
		error = pthread_key_create(key, destructor);
	(void) pthread_mutex_unlock(&lock);
	return (error);
}

#define	thr_setspecific(key, value)	pthread_setspecific((key), (value))

extern int assfail(const char *, const char *, int);

#define	ASSERT(EX)	((void)((EX) || (assfail(#EX, __FILE__, __LINE__), 0)))
#define	ASSERT3P(LEFT, OP, RIGHT)	ASSERT((LEFT) OP (RIGHT))
#define	ASSERT3U(LEFT, OP, RIGHT)	ASSERT((LEFT) OP (RIGHT))
#define	VERIFY(EX)	ASSERT(EX)
#define	VERIFY3S(LEFT, OP, RIGHT)	VERIFY((LEFT) OP (RIGHT))
#define	VERIFY3U(LEFT, OP, RIGHT)	VERIFY((LEFT) OP (RIGHT))
#define	VERIFY3P(LEFT, OP, RIGHT)	VERIFY((LEFT) OP (RIGHT))
#define	VERIFY0(EX)	VERIFY((EX) == 0)
#define	IMPLY(LEFT, RIGHT)	ASSERT(!(LEFT) || (RIGHT))
#define	CTASSERT(EX)	_Static_assert((EX), "compile-time assertion failed")
#define	__GNU_INLINE	__inline__ __attribute__((__gnu_inline__))
#define	MICROSEC	1000000
#define	PAGESIZE	((unsigned long)sysconf(_SC_PAGESIZE))
#define	UID_NOBODY	60001
#define	GID_NOBODY	UID_NOBODY

/* avl.c only needs ASSERT() from these illumos headers on a native host. */
#define	_SYS_DEBUG_H
#define	_SYS_CMN_ERR_H

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

#endif /* _SGS_COMPAT_LINUX_H */
