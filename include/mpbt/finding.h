/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_FINDING_H
    #define MPBT_FINDING_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_FINDING_FIELDS { \
        bridge_text_t check; \
        bridge_text_t path; \
        bridge_text_t text; \
        uint32_t line; \
        uint32_t column; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_finding_t, MPBT_FINDING_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_finding_t, MPBT_FINDING_FIELDS);

#endif
