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
