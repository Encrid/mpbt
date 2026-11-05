/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_FAIL_H
    #define MPBT_FAIL_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_FAIL_CALL_FIELDS { \
        bridge_text_t function; \
        bridge_text_t value; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_fail_call_t, MPBT_FAIL_CALL_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_fail_call_t, MPBT_FAIL_CALL_FIELDS);

#endif
