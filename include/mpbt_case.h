/*
** Copyright (C) 2026 Enkrid
**
** Under the GNU Affero General Public License, version 3 only: see license.
*/
#ifndef MPBT_CASE_H
    #define MPBT_CASE_H

    #include <stdint.h>

    #include "bridge_abi.h"
    #include "bridge_schema.h"

    #define MPBT_TESTS_FIELDS { \
        bridge_text_t cases; \
        bridge_text_t writers; \
        uint32_t timeout; \
        uint32_t copies; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_tests_t, MPBT_TESTS_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_tests_t, MPBT_TESTS_FIELDS);

    #define MPBT_TEST_RULE_FIELDS { \
        bridge_text_t lacks; \
        bridge_text_t exempt; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_test_rule_t, MPBT_TEST_RULE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_test_rule_t, MPBT_TEST_RULE_FIELDS);

    #define MPBT_CASE_FIELDS { \
        bridge_text_t group; \
        bridge_text_t name; \
        uint32_t index; \
        bool alone; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_case_t, MPBT_CASE_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_case_t, MPBT_CASE_FIELDS);

    #define MPBT_RUN_FIELDS { \
        bridge_text_t run; \
        bridge_text_t env; \
        bridge_text_t unset; \
        bridge_text_t input; \
        bridge_text_t files; \
        bridge_text_t folders; \
        bridge_text_t fail; \
        bridge_text_t helper_run; \
        bridge_text_t helper_wait; \
        bridge_text_t helper_input; \
        bool ignore_interrupt; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_run_t, MPBT_RUN_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_run_t, MPBT_RUN_FIELDS);

    #define MPBT_FALSE_VARIANT_FIELDS { \
        uint64_t owner; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_false_variant_t, MPBT_FALSE_VARIANT_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_false_variant_t, MPBT_FALSE_VARIANT_FIELDS);

    #define MPBT_CLAIM_KEYS_VALUES { \
        MPBT_CLAIM_STATUS = 0x1, \
        MPBT_CLAIM_STATUS_NOT = 0x2, \
        MPBT_CLAIM_LINE = 0x4, \
        MPBT_CLAIM_HAS = 0x8, \
        MPBT_CLAIM_LACKS = 0x10, \
        MPBT_CLAIM_MATCHES = 0x20, \
        MPBT_CLAIM_MATCHES_NOT = 0x40, \
        MPBT_CLAIM_ORDER = 0x80, \
        MPBT_CLAIM_OUTPUT = 0x100, \
        MPBT_CLAIM_FILES = 0x200 \
    }

BRIDGE_SCHEMA_BITMASK_TYPE(mpbt_claim_keys_t, uint16_t,
    MPBT_CLAIM_KEYS_VALUES);
BRIDGE_SCHEMA_BITMASK_DESC(mpbt_claim_keys_t, uint16_t,
    MPBT_CLAIM_KEYS_VALUES);

    #define MPBT_CLAIMS_FIELDS { \
        bridge_text_t line; \
        bridge_text_t has; \
        bridge_text_t lacks; \
        bridge_text_t matches; \
        bridge_text_t matches_not; \
        bridge_text_t order; \
        bridge_text_t output; \
        bridge_text_t files; \
        int32_t status; \
        int32_t status_not; \
        mpbt_claim_keys_t stated; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_claims_t, MPBT_CLAIMS_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_claims_t, MPBT_CLAIMS_FIELDS);
BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_helper_claims_t, MPBT_CLAIMS_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_helper_claims_t, MPBT_CLAIMS_FIELDS);

    #define MPBT_SIGNAL_VALUES { \
        MPBT_SIGNAL_INTERRUPT = 1, \
        MPBT_SIGNAL_TERMINATION = 2, \
        MPBT_SIGNAL_HANG_UP = 3 \
    }

BRIDGE_SCHEMA_ENUM_TYPE(mpbt_signal_t, uint8_t, MPBT_SIGNAL_VALUES);
BRIDGE_SCHEMA_ENUM_DESC(mpbt_signal_t, uint8_t, MPBT_SIGNAL_VALUES);

    #define MPBT_SCRIPT_ACTIONS_VALUES { \
        MPBT_SCRIPT_WAIT = 0x1, \
        MPBT_SCRIPT_PUT = 0x2, \
        MPBT_SCRIPT_REMOVE = 0x4, \
        MPBT_SCRIPT_TYPE = 0x8, \
        MPBT_SCRIPT_CLOSE = 0x10, \
        MPBT_SCRIPT_SIGNAL = 0x20, \
        MPBT_SCRIPT_PAUSE = 0x40 \
    }

BRIDGE_SCHEMA_BITMASK_TYPE(mpbt_script_actions_t, uint8_t,
    MPBT_SCRIPT_ACTIONS_VALUES);
BRIDGE_SCHEMA_BITMASK_DESC(mpbt_script_actions_t, uint8_t,
    MPBT_SCRIPT_ACTIONS_VALUES);

    #define MPBT_SCRIPT_STEP_FIELDS { \
        uint64_t owner; \
        bridge_text_t wait; \
        bridge_text_t put; \
        bridge_text_t remove; \
        bridge_text_t type; \
        double pause; \
        uint32_t order; \
        mpbt_signal_t signal; \
        mpbt_script_actions_t actions; \
    }

BRIDGE_SCHEMA_STRUCT_TYPE(mpbt_script_step_t, MPBT_SCRIPT_STEP_FIELDS);
BRIDGE_SCHEMA_STRUCT_DESC(mpbt_script_step_t, MPBT_SCRIPT_STEP_FIELDS);

#endif
