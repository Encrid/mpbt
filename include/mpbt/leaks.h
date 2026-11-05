/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_LEAKS_H
    #define MPBT_LEAKS_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"
    #include "mpbt/target.h"

    #define MPBT_LEAKS_FIELDS { \
        bridge_text_t memory; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_leaks_t, MPBT_LEAKS_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_leaks_t, MPBT_LEAKS_FIELDS);

    #define MPBT_LEAK_PAIR_FIELDS { \
        bridge_text_t take; \
        bridge_text_t give; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_leak_pair_t, MPBT_LEAK_PAIR_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_leak_pair_t, MPBT_LEAK_PAIR_FIELDS);

    #define MPBT_LEAK_KIND_FIELDS { \
        bridge_text_t name; \
        bridge_text_t takes; \
        bridge_text_t gives; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_leak_kind_t, MPBT_LEAK_KIND_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_leak_kind_t, MPBT_LEAK_KIND_FIELDS);

    #define MPBT_LEAK_EXCEPTION_FIELDS { \
        bridge_text_t case_name; \
        bridge_text_t kind; \
        bridge_text_t why; \
        mpbt_system_t system; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_leak_exception_t, MPBT_LEAK_EXCEPTION_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_leak_exception_t, MPBT_LEAK_EXCEPTION_FIELDS);

#endif
