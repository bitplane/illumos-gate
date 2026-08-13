/* Native Linux services normally supplied to libld by illumos libc. */

#include <stdarg.h>
#include <stdio.h>

#include <sgs.h>

void
veprintf(Lm_list *list, Error error, const char *format, va_list arguments)
{
	(void) list;
	(void) error;
	(void) vfprintf(stderr, format, arguments);
	(void) fputc('\n', stderr);
}

void
eprintf(Lm_list *list, Error error, const char *format, ...)
{
	va_list arguments;

	va_start(arguments, format);
	veprintf(list, error, format, arguments);
	va_end(arguments);
}
