/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_TARGET_H
    #define MPBT_TARGET_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_TARGET_FIELDS { \
        bridge_text_t name; \
        bool here; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_target_t, MPBT_TARGET_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_target_t, MPBT_TARGET_FIELDS);

    #define MPBT_SYSTEM_VALUES { \
        MPBT_SYSTEM_EVERY = 1, \
        MPBT_SYSTEM_POSIX = 2, \
        MPBT_SYSTEM_WINDOWS = 3 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_system_t, uint8_t, MPBT_SYSTEM_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_system_t, uint8_t, MPBT_SYSTEM_VALUES);

#endif
