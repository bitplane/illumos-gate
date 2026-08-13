/* Native Linux implementation of the system information used by SGS. */

#ifndef _SYS_SYSTEMINFO_H
#define	_SYS_SYSTEMINFO_H

#include <stddef.h>
#include <string.h>

#define	SI_MACHINE	5
#define	SI_PLATFORM	513
#define	SI_ISALIST	514

#ifndef SYS_NMLN
#define	SYS_NMLN	257
#endif

static __inline__ long
illumos_sysinfo(int command, char *buffer, long count)
{
	const char *value;
	size_t length;

	switch (command) {
	case SI_MACHINE:
	case SI_PLATFORM:
		value = "i86pc";
		break;
	case SI_ISALIST:
		value = "amd64 i386";
		break;
	default:
		return (-1);
	}

	length = strlen(value) + 1;
	if (count > 0) {
		size_t copy = length < (size_t)count ? length : (size_t)count;

		(void) memcpy(buffer, value, copy);
		buffer[copy - 1] = '\0';
	}

	return ((long)length);
}

#define	sysinfo	illumos_sysinfo

#endif /* _SYS_SYSTEMINFO_H */
