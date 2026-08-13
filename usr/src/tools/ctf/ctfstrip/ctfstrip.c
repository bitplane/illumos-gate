/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 */

/*
 * Copyright 2011 Jason King.  All rights reserved.
 * Copyright (c) 2018, Joyent, Inc.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <err.h>
#include <spawn.h>

#ifdef CTF_HOST_LINUX
#define	MCS	"/usr/bin/objcopy"
#else
#define	MCS	"/usr/bin/mcs"
#endif

#define	ELFLEN 4
static const char elf_signature[] = "\177ELF";
static posix_spawnattr_t attr;
#ifdef CTF_HOST_LINUX
static const char *cmd[] = { MCS, "--remove-section=.SUNW_ctf", NULL, NULL };
#define	CMD_FILE_INDEX	2
#else
static const char *cmd[] = { MCS, "-d", "-n", ".SUNW_ctf", NULL, NULL };
#define	CMD_FILE_INDEX	4
#endif

extern char **environ;

static int check_file(const char *, mode_t *);
static int fix_file(const char *, mode_t);
static void usage(const char *);

int
main(int argc, const char **argv)
{
	const char **p;
	int rc = 0;
	mode_t mode;

	if (argc < 2)
		usage(argv[0]);

	rc = posix_spawnattr_init(&attr);
	if (rc != 0) {
		errx(EXIT_FAILURE, "Spawn attribute initialization failed: %s",
		    strerror(rc));
	}

	for (p = argv + 1; *p != NULL; p++) {
		if (!check_file(*p, &mode))
			continue;
		if (!fix_file(*p, mode))
			rc = 1;
	}

	return (rc);
}

static int
check_file(const char *filename, mode_t *mode)
{
	char elfbuf[4];
	struct stat sb;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		warn("Unable to open %s", filename);
		return (0);
	}

	if (fstat(fd, &sb) == -1) {
		warn("stat(2) failed on %s", filename);
		(void) close(fd);
		return (0);
	}

	if (!S_ISREG(sb.st_mode)) {
		warnx("%s is not a regular file", filename);
		(void) close(fd);
		return (0);
	}

	if (sb.st_size < ELFLEN) {
		warnx("%s is not an ELF file", filename);
		(void) close(fd);
		return (0);
	}

	if (read(fd, elfbuf, ELFLEN) != ELFLEN) {
		warn("Error reading %s", filename);
		(void) close(fd);
		return (0);
	}

	if (strncmp(elfbuf, elf_signature, ELFLEN) != 0) {
		warnx("%s is not an ELF file", filename);
		(void) close(fd);
		return (0);
	}

	*mode = sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
	(void) close(fd);
	return (1);
}

static int
fix_file(const char *filename, mode_t mode)
{
	pid_t pid;
	int rc;
	int stat = 0;

	if ((mode & S_IWUSR) == 0) {
		if (chmod(filename, mode | S_IWUSR) == -1) {
			warn("failed to make %s writable", filename);
			return (0);
		}
	}

	cmd[CMD_FILE_INDEX] = filename;
	if ((rc = posix_spawn(&pid, MCS, NULL, &attr,
	    (char *const *)cmd, environ)) != 0) {
		warnx("could not exec %s: %s", MCS, strerror(rc));
		return (0);
	}

	(void) waitpid(pid, &stat, 0);
	if (!WIFEXITED(stat) || WEXITSTATUS(stat) != 0) {
		warnx("Removing CTF information from %s failed", filename);
		return (0);
	}

	if ((mode & S_IWUSR) == 0) {
		if (chmod(filename, mode) == -1) {
			warn("could not reset permissions of %s", filename);
			return (0);
		}
	}

	return (1);
}

static void
usage(const char *name)
{
	(void) fprintf(stderr, "Usage: %s file...\n", name);
	exit(EXIT_FAILURE);
}
