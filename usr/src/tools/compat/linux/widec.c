/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version 1.0
 * of the CDDL.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

static char *
widec_format(const char *format)
{
	char *translated = strdup(format);
	char *cursor;

	if (translated == NULL)
		return (NULL);

	for (cursor = translated; *cursor != '\0'; cursor++) {
		if (cursor[0] == '%' && cursor[1] == '%') {
			cursor++;
			continue;
		}
		if (cursor[0] == '%' && cursor[1] == 'w' && cursor[2] == 's')
			cursor[1] = 'l';
	}

	return (translated);
}

int
widec_vfprintf(FILE *stream, const char *format, va_list args)
{
	char *translated = widec_format(format);
	int result;

	if (translated == NULL)
		return (-1);
	result = vfprintf(stream, translated, args);
	free(translated);
	return (result);
}

int
widec_fprintf(FILE *stream, const char *format, ...)
{
	va_list args;
	int result;

	va_start(args, format);
	result = widec_vfprintf(stream, format, args);
	va_end(args);
	return (result);
}

int
wsprintf(wchar_t *destination, const char *format, ...)
{
	char *text;
	va_list args;
	int length;

	va_start(args, format);
	length = vasprintf(&text, format, args);
	va_end(args);
	if (length < 0)
		return (-1);

	if (mbstowcs(destination, text, (size_t)length + 1) == (size_t)-1) {
		free(text);
		return (-1);
	}

	free(text);
	return (length);
}
