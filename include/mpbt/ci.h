/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_CI_H
    #define MPBT_CI_H

    #include <stdint.h>

    #include "bridge_schema.h"

    #define MPBT_NEEDS_VALUES { \
        MPBT_NEED_DISPLAY = 0x1, \
        MPBT_NEED_VULKAN = 0x2, \
        MPBT_NEED_GL = 0x4 \
    }

BRIDGE_SCHEMA_BITMASK_TYPE(mpbt_needs_t, uint8_t, MPBT_NEEDS_VALUES);
BRIDGE_SCHEMA_BITMASK_DESC(mpbt_needs_t, uint8_t, MPBT_NEEDS_VALUES);

    #define MPBT_CI_FIELDS { \
        mpbt_needs_t needs; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_ci_t, MPBT_CI_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_ci_t, MPBT_CI_FIELDS);

#endif
