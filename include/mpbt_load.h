/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_LOAD_H
    #define MPBT_LOAD_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_LOAD_FROM_VALUES { \
        MPBT_LOAD_ARTIFACT = 1, \
        MPBT_LOAD_FILE = 2 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_load_from_t, uint8_t, MPBT_LOAD_FROM_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_load_from_t, uint8_t, MPBT_LOAD_FROM_VALUES);

    #define MPBT_LOAD_FIELDS { \
        bridge_text_t artifact; \
        bridge_text_t file; \
        bridge_text_t keys; \
        bridge_text_t phases; \
        bridge_text_t config; \
        mpbt_load_from_t from; \
        uint32_t order; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_load_t, MPBT_LOAD_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_load_t, MPBT_LOAD_FIELDS);

#endif
