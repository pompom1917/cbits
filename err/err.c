/*
 * (C) 2026, Pompom
 *
 * Copying and distribution of this file, with or without modification, are
 * permitted in any medium without royalty, provided the copyright notice and
 * this notice are preserved. This file is offered as-is, without any warranty.
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <unistd.h>

#include "err.h"

#define RED(s)    ("\x1b[1;31m" s "\x1b[0m")
#define YELLOW(s) ("\x1b[1;33m" s "\x1b[0m")

bool had_error,
     err_colour = true;

static bool iscolour(void);

noreturn void
fatal(const char *fmt, ...)
{
	va_list l;

	va_start(l, fmt);
	fprintf(stderr, "%s ", iscolour() ? RED("fatal:"):"fatal:");
	vfprintf(stderr, fmt, l);
	va_end(l);
	exit(EXIT_FAILURE);
}

void
error(const char *fmt, ...)
{
	va_list l;

	va_start(l, fmt);
	fprintf(stderr, "%s ", iscolour() ? RED("error:"):"error:");
	vfprintf(stderr, fmt, l);
	had_error = true;
	va_end(l);
}

void
warn(const char *fmt, ...)
{
	va_list l;

	va_start(l, fmt);
	fprintf(stderr, "%s ", iscolour() ? YELLOW("warning:"):"warning:");
	vfprintf(stderr, fmt, l);
	va_end(l);
}

static bool
iscolour(void)
{
	return isatty(2) && err_colour; /* check if stdout is a terminal */
}
