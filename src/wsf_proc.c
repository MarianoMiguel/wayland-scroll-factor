#define _GNU_SOURCE

#include "wsf_proc.h"

#include <stdio.h>
#include <string.h>

static const char *wsf_basename(const char *path) {
	const char *slash = strrchr(path, '/');

	if (slash == NULL) {
		return path;
	}

	return slash + 1;
}

static bool wsf_read_comm(char *buf, size_t len) {
	FILE *file = fopen("/proc/self/comm", "r");

	if (file == NULL) {
		return false;
	}

	if (fgets(buf, (int) len, file) == NULL) {
		fclose(file);
		return false;
	}

	fclose(file);

	buf[strcspn(buf, "\n")] = '\0';
	return true;
}

static bool wsf_read_cmdline(char *buf, size_t len) {
	FILE *file = fopen("/proc/self/cmdline", "r");
	size_t read_len = 0;

	if (file == NULL) {
		return false;
	}

	read_len = fread(buf, 1, len - 1, file);
	fclose(file);

	if (read_len == 0) {
		return false;
	}

	buf[read_len] = '\0';
	return true;
}

bool wsf_proc_name(char *buf, size_t len) {
	char cmdline[256];
	const char *name = NULL;

	if (buf == NULL || len == 0) {
		return false;
	}

	buf[0] = '\0';

	if (wsf_read_comm(buf, len)) {
		return true;
	}

	if (!wsf_read_cmdline(cmdline, sizeof(cmdline))) {
		return false;
	}

	name = wsf_basename(cmdline);
	strncpy(buf, name, len - 1);
	buf[len - 1] = '\0';
	return true;
}

bool wsf_proc_is_target(const char *target) {
	char comm[256];
	char cmdline[256];

	if (target == NULL || target[0] == '\0') {
		return false;
	}

	if (wsf_read_comm(comm, sizeof(comm))) {
		if (strcmp(comm, target) == 0) {
			return true;
		}
	}

	if (wsf_read_cmdline(cmdline, sizeof(cmdline))) {
		const char *name = wsf_basename(cmdline);
		if (strcmp(name, target) == 0) {
			return true;
		}
	}

	return false;
}
