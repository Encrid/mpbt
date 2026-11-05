/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_SOURCE_H
    #define MPBT_SOURCE_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_SOURCE_FIELDS { \
        bridge_text_t name; \
        bridge_text_t url; \
        bridge_text_t sha256; \
        bridge_text_t into; \
        bridge_text_t top; \
        bridge_text_t patches; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_source_t, MPBT_SOURCE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_source_t, MPBT_SOURCE_FIELDS);

#endif
