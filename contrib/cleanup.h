/*  Copyright (C) CZ.NIC, z.s.p.o. <knot-dns@labs.nic.cz>
 *  SPDX-License-Identifier: GPL-3.0-or-later
*/
/**
 * Cleanup attributes.
 * @cond internal
 */
#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define auto_free __attribute__((cleanup(_cleanup_free)))
static inline void _cleanup_free(const void *p) {
	free(*(char **)p);
}
#define auto_close __attribute__((cleanup(_cleanup_close)))
static inline void _cleanup_close(int *p) {
	if (*p != -1) close(*p);
}
#define auto_fclose __attribute__((cleanup(_cleanup_fclose)))
static inline void _cleanup_fclose(FILE **p) {
	if (*p) fclose(*p);
}
/* @endcond */
