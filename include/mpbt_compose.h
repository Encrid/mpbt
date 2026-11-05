/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_COMPOSE_H
    #define MPBT_COMPOSE_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_COMPOSE_FIELDS { \
        bridge_text_t name; \
        bridge_text_t from; \
        bridge_text_t headers; \
        bridge_text_t into; \
        bridge_text_t assets; \
        bridge_text_t part; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_compose_t, MPBT_COMPOSE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_compose_t, MPBT_COMPOSE_FIELDS);

    #define MPBT_PART_FIELDS { \
        bridge_text_t part; \
        bridge_text_t name; \
        bridge_text_t folder; \
        bridge_text_t uses; \
        bridge_text_t third_party; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_part_t, MPBT_PART_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_part_t, MPBT_PART_FIELDS);

    #define MPBT_PACKAGE_FIELDS { \
        bridge_text_t part; \
        bridge_text_t proof; \
        bridge_text_t link; \
        bridge_text_t include; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_package_t, MPBT_PACKAGE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_package_t, MPBT_PACKAGE_FIELDS);

    #define MPBT_DELIVERABLE_FIELDS { \
        bridge_text_t part; \
        bridge_text_t files; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_deliverable_t, MPBT_DELIVERABLE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_deliverable_t, MPBT_DELIVERABLE_FIELDS);

#endif
