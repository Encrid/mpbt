/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_KIND_H
    #define MPBT_KIND_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_KIND_FIELDS { \
        bridge_text_t name; \
        bridge_text_t output; \
        bridge_text_t flags; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_kind_t, MPBT_KIND_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_kind_t, MPBT_KIND_FIELDS);

    #define MPBT_STEP_LIST_VALUES { \
        MPBT_STEP_LIST_STEPS = 1, \
        MPBT_STEP_LIST_UNLINKED = 2 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_step_list_t, uint8_t, MPBT_STEP_LIST_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_step_list_t, uint8_t, MPBT_STEP_LIST_VALUES);

    #define MPBT_STEP_ACTIONS_VALUES { \
        MPBT_STEP_RUN = 0x1, \
        MPBT_STEP_SECTION = 0x2, \
        MPBT_STEP_CONTAINS = 0x4, \
        MPBT_STEP_COPY = 0x8, \
        MPBT_STEP_RENAME = 0x10 \
    }

BRIDGE_SCHEMA_BITMASK_TYPE(mpbt_step_actions_t, uint8_t,
    MPBT_STEP_ACTIONS_VALUES);
BRIDGE_SCHEMA_BITMASK_DESC(mpbt_step_actions_t, uint8_t,
    MPBT_STEP_ACTIONS_VALUES);

    #define MPBT_STEP_FIELDS { \
        uint64_t owner; \
        bridge_text_t run; \
        bridge_text_t cwd; \
        bridge_text_t section; \
        bridge_text_t text; \
        bridge_text_t contains; \
        bridge_text_t copy; \
        bridge_text_t rename; \
        uint32_t order; \
        mpbt_step_list_t list; \
        mpbt_step_actions_t actions; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_step_t, MPBT_STEP_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_step_t, MPBT_STEP_FIELDS);

#endif
