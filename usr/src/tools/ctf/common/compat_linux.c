/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version 1.0
 * of the CDDL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

void
assfail(const char *assertion, const char *filename, int line)
{
	(void) fprintf(stderr, "%s:%d: assertion failed: %s\n", filename, line,
	    assertion);
	abort();
}

void
assfail3(const char *assertion, uintmax_t left, const char *op,
    uintmax_t right, const char *filename, int line)
{
	(void) fprintf(stderr,
	    "%s:%d: assertion failed: %s (%#jx %s %#jx)\n",
	    filename, line, assertion, left, op, right);
	abort();
}

long long
strtonum(const char *value, long long minimum, long long maximum,
    const char **error)
{
	long long result = 0;
	char *end;
	const char *message = NULL;
	int saved_errno = 0;

	if (minimum > maximum) {
		message = "invalid";
		saved_errno = EINVAL;
	} else {
		errno = 0;
		result = strtoll(value, &end, 10);
		if (value == end || *end != '\0') {
			message = "invalid";
			saved_errno = EINVAL;
		} else if ((result == LLONG_MIN && errno == ERANGE) ||
		    result < minimum) {
			message = "too small";
			saved_errno = ERANGE;
		} else if ((result == LLONG_MAX && errno == ERANGE) ||
		    result > maximum) {
			message = "too large";
			saved_errno = ERANGE;
		}
	}

	if (error != NULL)
		*error = message;
	if (message != NULL) {
		errno = saved_errno;
		return (0);
	}

	return (result);
}
