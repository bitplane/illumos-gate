/* SGS only consumes the illumos utsname field size on a native Linux host. */

#ifndef _SYS_UTSNAME_H
#define	_SYS_UTSNAME_H

#ifndef SYS_NMLN
#define	SYS_NMLN	257
#endif

#define	LINUX_UTS_NMLEN	65

struct utsname {
	char sysname[LINUX_UTS_NMLEN];
	char nodename[LINUX_UTS_NMLEN];
	char release[LINUX_UTS_NMLEN];
	char version[LINUX_UTS_NMLEN];
	char machine[LINUX_UTS_NMLEN];
	char domainname[LINUX_UTS_NMLEN];
};

extern int uname(struct utsname *);

#endif /* _SYS_UTSNAME_H */
