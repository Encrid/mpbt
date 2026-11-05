/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_COMMAND_H
    #define MPBT_COMMAND_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_COMMAND_NAME_VALUES { \
        MPBT_COMMAND_FETCH = 1, \
        MPBT_COMMAND_BUILD = 2, \
        MPBT_COMMAND_PACK = 3, \
        MPBT_COMMAND_JOIN = 4, \
        MPBT_COMMAND_TEST = 5, \
        MPBT_COMMAND_CHECK = 6, \
        MPBT_COMMAND_CLEAN = 7, \
        MPBT_COMMAND_DISTCLEAN = 8, \
        MPBT_COMMAND_CLA = 9, \
        MPBT_COMMAND_RUNNER = 10 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_command_name_t, uint8_t,
    MPBT_COMMAND_NAME_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_command_name_t, uint8_t,
    MPBT_COMMAND_NAME_VALUES);

    #define MPBT_OPTIONS_VALUES { \
        MPBT_OPTION_ROOT = 0x1, \
        MPBT_OPTION_TARGET = 0x2, \
        MPBT_OPTION_PART = 0x4, \
        MPBT_OPTION_TAG = 0x8, \
        MPBT_OPTION_DEBUG = 0x10, \
        MPBT_OPTION_OUT = 0x20, \
        MPBT_OPTION_SET = 0x40, \
        MPBT_OPTION_LEAVE = 0x80, \
        MPBT_OPTION_BREAK = 0x100, \
        MPBT_OPTION_FILTER = 0x200, \
        MPBT_OPTION_COPIES = 0x400, \
        MPBT_OPTION_ROUNDS = 0x800, \
        MPBT_OPTION_BRANCHES = 0x1000, \
        MPBT_OPTION_LEAKS = 0x2000, \
        MPBT_OPTION_COMMITS = 0x4000, \
        MPBT_OPTION_DECIDE = 0x8000 \
    }

BRIDGE_SCHEMA_BITMASK_TYPE(mpbt_options_t, uint32_t, MPBT_OPTIONS_VALUES);
BRIDGE_SCHEMA_BITMASK_DESC(mpbt_options_t, uint32_t, MPBT_OPTIONS_VALUES);

    #define MPBT_COMMAND_FIELDS { \
        bridge_text_t root; \
        bridge_text_t target; \
        bridge_text_t out; \
        bridge_text_t parts; \
        bridge_text_t tag; \
        bridge_text_t sets; \
        bridge_text_t leave; \
        bridge_text_t filter; \
        bridge_text_t commits; \
        bridge_text_t decide; \
        uint32_t copies; \
        uint32_t rounds; \
        mpbt_options_t options; \
        mpbt_command_name_t name; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_command_t, MPBT_COMMAND_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_command_t, MPBT_COMMAND_FIELDS);

#endif
