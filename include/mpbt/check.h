/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_CHECK_H
    #define MPBT_CHECK_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_TEXT_CHECK_FIELDS { \
        bridge_text_t unicode; \
        bridge_text_t refuse; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_text_check_t, MPBT_TEXT_CHECK_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_text_check_t, MPBT_TEXT_CHECK_FIELDS);

    #define MPBT_LAYOUT_CHECK_FIELDS { \
        bridge_text_t guides; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_layout_check_t, MPBT_LAYOUT_CHECK_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_layout_check_t, MPBT_LAYOUT_CHECK_FIELDS);

    #define MPBT_RETIRED_FIELDS { \
        bridge_text_t word; \
        bridge_text_t text; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_retired_t, MPBT_RETIRED_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_retired_t, MPBT_RETIRED_FIELDS);

    #define MPBT_MAKE_FIELDS { \
        bridge_text_t macro; \
        bridge_text_t suffix; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_make_t, MPBT_MAKE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_make_t, MPBT_MAKE_FIELDS);

    #define MPBT_STYLE_EXCEPTION_FIELDS { \
        bridge_text_t rule; \
        bridge_text_t path; \
        bridge_text_t why; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_style_exception_t,
    MPBT_STYLE_EXCEPTION_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_style_exception_t,
    MPBT_STYLE_EXCEPTION_FIELDS);

#endif
