/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_ARTIFACT_H
    #define MPBT_ARTIFACT_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_ARTIFACT_FIELDS { \
        bridge_text_t name; \
        bridge_text_t kind; \
        bridge_text_t sources; \
        bridge_text_t include; \
        bridge_text_t defines; \
        bridge_text_t flags; \
        bridge_text_t link; \
        bridge_text_t beside; \
        bridge_text_t manifest; \
        bridge_text_t folder; \
        bridge_text_t target; \
        bridge_text_t part; \
        bool test; \
        bool path; \
        bool unstamped; \
        uint32_t order; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_artifact_t, MPBT_ARTIFACT_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_artifact_t, MPBT_ARTIFACT_FIELDS);

    #define MPBT_BUILT_FIELDS { \
        bridge_text_t output; \
        bridge_text_t files; \
        bool linked; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_built_t, MPBT_BUILT_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_built_t, MPBT_BUILT_FIELDS);

#endif
