/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_PROJECT_H
    #define MPBT_PROJECT_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_PROJECT_FIELDS { \
        bridge_text_t name; \
        bridge_text_t notice; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_project_t, MPBT_PROJECT_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_project_t, MPBT_PROJECT_FIELDS);

    #define MPBT_VALUE_KIND_VALUES { \
        MPBT_VALUE_TEXT = 1, \
        MPBT_VALUE_LIST = 2 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_value_kind_t, uint8_t, MPBT_VALUE_KIND_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_value_kind_t, uint8_t, MPBT_VALUE_KIND_VALUES);

    #define MPBT_SCOPE_VALUES { \
        MPBT_SCOPE_PROJECT = 1, \
        MPBT_SCOPE_TARGET = 2 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_scope_t, uint8_t, MPBT_SCOPE_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_scope_t, uint8_t, MPBT_SCOPE_VALUES);

    #define MPBT_VARIABLE_FIELDS { \
        bridge_text_t name; \
        bridge_text_t target; \
        bridge_text_t value; \
        mpbt_value_kind_t kind; \
        mpbt_scope_t scope; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_variable_t, MPBT_VARIABLE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_variable_t, MPBT_VARIABLE_FIELDS);

#endif
