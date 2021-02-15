/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(C) 2021 Marvell.
 */

/**
 * @file
 *
 * ODP Proto Stats
 */

#ifndef ODP_API_SPEC_PROTO_STATS_H_
#define ODP_API_SPEC_PROTO_STATS_H_
#include <odp/visibility_begin.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup odp_proto_stats
 *  @{
 */

/**
 * @def ODP_PROTO_STATS_INVALID
 * Invalid proto stats handle
 */

/** ODP proto stats id */
typedef enum odp_proto_stats_id_t {
	/** Tx proto stats id ODP_PROTO_STATS_ID_TX_*
	 *
	 * - All the below modes are associated to packet stats and accounting
	 *   on Tx of a packet via Packet IO. Packet IO pktout config
	 *   `odp_pktout_config_opt_t::bit::proto_stats` needs to be enabled for
	 *   the offload to work.
	 * - For each of the below mode, proto stats object needs to be associated
	 *   on per-packet basis using `odp_packet_proto_stats_set(pkt, stat)`
	 *   for stats update to be enabled for that packet.
	 * - Default behaviour is stats update is disabled.
	 *
	 * @see odp_packet_proto_stats_set()
	 */

	/** Packet sent count */
	ODP_PROTO_STATS_ID_TX_PKT,
	/** Packet drop count */
	ODP_PROTO_STATS_ID_TX_PKT_DROP,
	/** Packet sent Octet counter 0 */
	ODP_PROTO_STATS_ID_TX_OCT_COUNT0,
	/** Packet drop Octet counter 0 */
	ODP_PROTO_STATS_ID_TX_OCT_COUNT0_DROP,
	/** Packet sent octet counter 1 */
	ODP_PROTO_STATS_ID_TX_OCT_COUNT1,
	/** Packet drop octet counter 1 */
	ODP_PROTO_STATS_ID_TX_OCT_COUNT1_DROP,
	/** Max */
	ODP_PROTO_STATS_ID_MAX,
} odp_proto_stats_id_t;

/** ODP proto stats params */
typedef struct odp_proto_stats_param_t {
	/** Stats id mask
	 *
	 * Each bit corresponds to one ODP_PROTO_STATS_ID_* and
	 * bit position is same as ODP_PROTO_STATS_ID_*.
	 */
	uint64_t stats_mask;
} odp_proto_stats_param_t;

/**
 * Proto stats capabilities
 */
typedef struct odp_proto_stats_capa_t {
	/** Supported proto stats id mask
	 *
	 * A bit is set at position ODP_PROTO_STATS_ID_*,
	 * when that proto stats id is supported.
	 */
	uint64_t stats_mask_supported;

	/** ODP_PROTO_STATS_ID_TX_* flags */
	struct {
		/** Packet adjust support for ODP_PROTO_STATS_ID_TX_OCT_COUNT0
		 *
		 * By default octet counter is updated using `odp_packet_len()`.  When adjust
		 * is supported and octet count updated in statistics is `odp_packet_len() +
		 * OCT_COUNT0_ADJ` where `OCT_COUNT0_ADJ` is set using
		 * odp_packet_proto_stats_oct_set().
		 *
		 * @see odp_packet_proto_stats_oct_set()
		 */
		odp_bool_t oct_count0_adj;

		/** Per-Packet enable/disable for ODP_PROTO_STATS_ID_TX_OCT_COUNT0
		 *
		 * Normally when proto stats object is created with
		 * ODP_PROTO_STATS_ID_TX_OCT_COUNT0, octet counter 0 updates are enabled for packets
		 * associated with stats object. This capability says if additionally octet
		 * counter 0 update alone can be disabled for this packet while keeping all other
		 * updates enabled.
		 *
		 * @see odp_packet_proto_stats_oct_set()
		 */
		odp_bool_t oct_count0_ctrl;

		/** Packet adjust support for ODP_PROTO_STATS_ID_TX_OCT_COUNT1
		 *
		 * By default octet counter is updated using `odp_packet_len()`.  When adjust is
		 * supported and octet count updated in statistics is
		 * `odp_packet_len() + OCT_COUNT1_ADJ` where `OCT_COUNT1_ADJ` is set using
		 * odp_packet_proto_stats_oct_set().
		 *
		 * @see odp_packet_proto_stats_oct_set()
		 */
		odp_bool_t oct_count1_adj;

		/** Per-Packet enable/disable control for ODP_PROTO_STATS_ID_TX_OCT_COUNT1
		 *
		 * Normally when proto stats object is created with
		 * ODP_PROTO_STATS_ID_TX_OCT_COUNT1, octet counter 1 updates are enabled for packets
		 * associated with stats object. This capability says if additionally octet
		 * counter 1 update alone be disabled for this packet alone using
		 * odp_packet_proto_stats_oct_set().
		 *
		 * @see odp_packet_proto_stats_oct_set()
		 */
		odp_bool_t oct_count1_ctrl;
	} tx;
} odp_proto_stats_capa_t;

/**
 * Initialize proto stats parameters
 *
 * Initialize an odp_proto_stats_param_t to its default values.
 *
 * @param param   Proto stats parameter pointer.
 */
void odp_proto_stats_init(odp_proto_stats_param_t *param);

/**
 * Get proto stats capability
 *
 * Get proto stats capability of supported modes.
 *
 * @param capa Pointer where capabilities are updated.
 */
void odp_proto_stats_capa(odp_proto_stats_capa_t *capa);

/**
 * Create a proto stats object
 *
 * Create a proto stats object with given name and mode.
 * Semantics of each mode is associated with that mode.
 *
 * @param name  Object name
 * @param param Proto stats parameters
 *
 * @return Proto stats object handle
 */
odp_proto_stats_t odp_proto_stats_create(const char *name, const odp_proto_stats_param_t *param);

/**
 * Lookup a proto stats object by name
 *
 * Lookup an already created proto stats object by name.
 *
 * @param name Proto stats object name
 *
 * @return Proto stats object handle
 */
odp_proto_stats_t odp_proto_stats_lookup(const char *name);

/**
 * Destroy a proto stats object
 *
 * Destroy a proto stats object already created.
 *
 * @param stat Proto stats handle
 *
 * @retval 0 on success
 * @retval <0 on failure
 */
int odp_proto_stats_destroy(odp_proto_stats_t stat);

/**
 * Get proto stats counter by id
 *
 * Get current value of statistics counter by stat id.
 *
 * @param stat Proto stat object handle
 * @param id   Stats counter identifier to return the value.
 *
 * @return Stats counter value
 * @retval Unknown value if stats id is not valid for the object.
 */
uint64_t odp_proto_stats(odp_proto_stats_t stat, odp_proto_stats_id_t id);

/** ODP proto stats counters */
typedef struct odp_proto_stats_data_t {
	/** Array of counters */
	uint64_t counter[ODP_PROTO_STATS_ID_MAX];
} odp_proto_stats_data_t;

/**
 * Get all proto stats counters
 *
 * Get current values of all counters of the proto stats object. Only the counters
 * enabled on the proto stats object will have valid value in odp_proto_stats_data_t
 * and rest of the counters will be uninitialized.
 *
 * @param      stat   Proto stats object handle
 * @param[out] data   Pointer to structure where all the stats counters
 *                    are returned.
 *
 * @retval =0 on success
 * @retval <0 on failure
 */
int odp_proto_stats_all(odp_proto_stats_t stat, odp_proto_stats_data_t *data);

/**
 * Print proto stats object info on console.
 *
 * Print implementation-defined proto stats debug information to the console.
 *
 * @param stat Proto stats object handle
 */
void odp_proto_stats_print(odp_proto_stats_t stat);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#include <odp/visibility_end.h>
#endif
