#ifndef WSF_PROC_H
#define WSF_PROC_H

#include <stdbool.h>
#include <stddef.h>

bool wsf_proc_name(char *buf, size_t len);
bool wsf_proc_is_target(const char *target);

#endif
