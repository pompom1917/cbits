/*
 * (C) 2026, Pompom
 *
 * Copying and distribution of this file, with or without modification, are
 * permitted in any medium without royalty, provided the copyright notice and
 * this notice are preserved. This file is offered as-is, without any warranty.
 */

#ifndef CUNIT_H
#define CUNIT_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(__STDC__) || __STDC_VERSION__ < 201112L
	#error "Standard C11 or later required"
#endif

#define TEST(name)   _Bool test__##name(void)
#define RUN(name)    do {                                                 \
                     cu__success =                                        \
                     (test__##name()?1:(cu__failed++, 0)) && cu__success; \
                     cu__total++;} while(0)
#define FAIL(msg)    do {cu__fail(__func__+6, (msg)); return 0;} while(0)
#define SUCCEED()    do {cu__succeed(__func__+6); return 1;} while(0)
#define ASSERT(expr) do {if (!cu__assert((expr), #expr, __func__+6))   \
                     return 0;}                                        \
                     while(0)

#define CU_BEGIN()  _Bool cu__success = 1; long long cu__total = 0, \
                    cu__failed = 0;
#define CU_REPORT() return cu__report(cu__success, cu__total, cu__failed)

static inline int
cu__report(_Bool success, long long total, long long failed)
{
	if (success) {
		fprintf(stderr,
		        "[cunit] all tests passed\n");
		return EXIT_SUCCESS;
	} else {
		fprintf(stderr,
		        "[cunit] failure: %lld of %lld tests failed\n",
		        failed, total);
		return EXIT_FAILURE;
	}
}

static inline _Bool
cu__assert(_Bool expr, const char *expr_s, const char *name)
{
	if (!expr)
		fprintf(stderr,
		        "[cunit] assertion failed: `%s` in test `%s`\n",
		        expr_s, name);
	return expr;
}

static inline void
cu__fail(const char *name, const char *msg)
{
	fprintf(stderr, "[cunit] test `%s` failed: %s\n", name, msg);
}

static inline void
cu__succeed(const char *name)
{
	fprintf(stderr, "[cunit] test `%s` passed\n", name);
}

#endif
