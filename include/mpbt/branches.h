/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_BRANCHES_H
    #define MPBT_BRANCHES_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"
    #include "mpbt/target.h"

    #define MPBT_SIDE_VALUES { \
        MPBT_SIDE_TRUE = 1, \
        MPBT_SIDE_FALSE = 2, \
        MPBT_SIDE_FUNCTION = 3, \
        MPBT_SIDE_CASE = 4 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_side_t, uint8_t, MPBT_SIDE_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_side_t, uint8_t, MPBT_SIDE_VALUES);

    #define MPBT_BRANCH_EXCEPTION_FIELDS { \
        bridge_text_t path; \
        bridge_text_t why; \
        uint32_t line; \
        uint32_t col; \
        mpbt_side_t side; \
        mpbt_system_t system; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_branch_exception_t,
    MPBT_BRANCH_EXCEPTION_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_branch_exception_t,
    MPBT_BRANCH_EXCEPTION_FIELDS);

#endif
