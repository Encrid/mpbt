/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_FILE_H
    #define MPBT_FILE_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_FILE_FIELDS { \
        bridge_text_t path; \
        bridge_text_t bytes; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_file_t, MPBT_FILE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_file_t, MPBT_FILE_FIELDS);

#endif
