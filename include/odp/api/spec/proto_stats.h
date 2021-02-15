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

/** ODP proto stats params */
typedef struct odp_proto_stats_param_t {
} odp_proto_stats_param_t;

/**
 * Proto stats capabilities
 */
typedef struct odp_proto_stats_capability_t {
} odp_proto_stats_capability_t;

/**
 * Initialize proto stats parameters
 *
 * Initialize an odp_proto_stats_param_t to its default values.
 * By default all the statistics are disabled.
 *
 * @param param   Proto stats parameter pointer.
 */
void odp_proto_stats_param_init(odp_proto_stats_param_t *param);

/**
 * Get proto stats capability
 *
 * Get supported protocol statistics and metadata.
 *
 * @param capa Pointer where capabilities are updated.
 */
void odp_proto_stats_capability(odp_proto_stats_capability_t *capa);

/**
 * Create a proto stats object
 *
 * Create a proto stats object with given name and parameters.
 *
 * @param name  Object name
 * @param param Proto stats parameters
 *
 * @return Proto stats object handle
 * @retval ODP_PROTO_STATS_INVALID on failure
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
 * @retval ODP_PROTO_STATS_INVALID on failure
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

/** ODP proto stats counters */
typedef struct odp_proto_stats_data_t {
} odp_proto_stats_data_t;

/**
 * Get all proto stats counters
 *
 * Get current values of all counters of the proto stats object.
 * The values of counters that are not enabled in the proto stats object are undefined.
 *
 * @param      stat   Proto stats object handle
 * @param[out] data   Pointer to a caller allocated structure where the statistics will
 *                    be written to.
 *
 * @retval =0 on success
 * @retval <0 on failure
 */
int odp_proto_stats(odp_proto_stats_t stat, odp_proto_stats_data_t *data);

/**
 * Print proto stats object info to ODP log.
 *
 * Print implementation-defined proto stats debug information to ODP log.
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
