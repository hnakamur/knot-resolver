/*  Copyright (C) CZ.NIC, z.s.p.o. <knot-resolver@labs.nic.cz>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "lib/selection.h"

void iter_local_state_alloc(struct knot_mm *mm, void **local_state);
void iter_choose_transport(struct kr_query *qry, struct kr_transport **transport);
void iter_error(struct kr_query *qry, const struct kr_transport *transport,
		enum kr_selection_error sel_error);
void iter_update_rtt(struct kr_query *qry, const struct kr_transport *transport,
		     unsigned rtt);
