/*  Copyright (C) CZ.NIC, z.s.p.o. <knot-resolver@labs.nic.cz>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <libknot/packet/pkt.h>

/** High numbers in NSEC3 iterations don't really help security
 *
 * ...so we avoid doing all the work.  The value is a current compromise;
 * zones shooting over get downgraded to insecure status.
 *
 * Original restriction wasn't that strict:
   https://datatracker.ietf.org/doc/html/rfc5155#section-10.3
 * but there is discussion about officially lowering the limits:
   https://tools.ietf.org/id/draft-hardaker-dnsop-nsec3-guidance-02.html#section-2.3
 */
#define KR_NSEC3_MAX_ITERATIONS 150

/**
 * Name error response check (RFC5155 7.2.2).
 * @note No RRSIGs are validated.
 * @param pkt        Packet structure to be processed.
 * @param section_id Packet section to be processed.
 * @param sname      Name to be checked.
 * @return           0 or error code.
 */
int kr_nsec3_name_error_response_check(const knot_pkt_t *pkt, knot_section_t section_id,
                                       const knot_dname_t *sname);

/**
 * Wildcard answer response check (RFC5155 7.2.6).
 * @param pkt          Packet structure to be processed.
 * @param section_id   Packet section to be processed.
 * @param sname        Name to be checked.
 * @param trim_to_next Number of labels to remove to obtain next closer name.
 * @return             0 or error code:
 *                     KNOT_ERANGE - NSEC3 RR that covers a wildcard
 *                     has been found, but has opt-out flag set;
 *                     otherwise - error.
 * Records over KR_NSEC3_MAX_ITERATIONS are skipped, so you probably get kr_error(ENOENT).
 */
int kr_nsec3_wildcard_answer_response_check(const knot_pkt_t *pkt, knot_section_t section_id,
                                            const knot_dname_t *sname, int trim_to_next);

/**
 * Authenticated denial of existence according to RFC5155 8.5 and 8.7.
 * @note No RRSIGs are validated.
 * @param pkt        Packet structure to be processed.
 * @param section_id Packet section to be processed.
 * @param sname      Queried domain name.
 * @param stype      Queried type.
 * @return           0 or error code:
 *                   DNSSEC_NOT_FOUND - neither ds nor nsec records
 *                   were not found.
 *                   KNOT_ERANGE - denial of existence can't be proven
 *                   due to opt-out, otherwise - bogus.
 */
int kr_nsec3_no_data(const knot_pkt_t *pkt, knot_section_t section_id,
                     const knot_dname_t *sname, uint16_t stype);

/**
 * Referral to unsigned subzone check (RFC5155 8.9).
 * @note 	     No RRSIGs are validated.
 * @param pkt        Packet structure to be processed.
 * @return           0 or error code:
 *                   KNOT_ERANGE - denial of existence can't be proven
 *                   due to opt-out.
 *                   EEXIST - ds record was found.
 *                   EINVAL - bogus.
 */
int kr_nsec3_ref_to_unsigned(const knot_pkt_t *pkt);

/**
 * Checks whether supplied NSEC3 RR matches the supplied name and NS type.
 * @param nsec3 NSEC3 RR.
 * @param name  Name to be checked.
 * @param type  Type to be checked.  Only use with NS!  TODO
 * @return      0 or error code.
 */
int kr_nsec3_matches_name_and_type(const knot_rrset_t *nsec3,
				   const knot_dname_t *name, uint16_t type);
