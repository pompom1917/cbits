/*
 * (C) 2026, Pompom
 *
 * Copying and distribution of this file, with or without modification, are
 * permitted in any medium without royalty, provided the copyright notice and
 * this notice are preserved. This file is offered as-is, without any warranty.
 */
 
#ifndef ERR_H
#define ERR_H

extern _Bool had_error,
             err_colour;

_Noreturn void fatal(const char *, ...);
void error(const char *, ...);
void warn(const char *, ...);

#endif
