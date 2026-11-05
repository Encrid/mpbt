/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_DEPENDENCY_H
    #define MPBT_DEPENDENCY_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_DEPENDENCY_FIELDS { \
        bridge_text_t name; \
        bridge_text_t from; \
        bridge_text_t list; \
        bridge_text_t into; \
        bridge_text_t make; \
        bool optional; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_dependency_t, MPBT_DEPENDENCY_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_dependency_t, MPBT_DEPENDENCY_FIELDS);

    #define MPBT_AGREE_FIELDS { \
        bridge_text_t keys; \
        uint32_t length; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_agree_t, MPBT_AGREE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_agree_t, MPBT_AGREE_FIELDS);

#endif
