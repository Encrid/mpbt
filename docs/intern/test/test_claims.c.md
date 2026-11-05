# src/test/test_claims.c

This file tells whether each claim of a table holds for the end of a command: `docs/extern/mpbt_case.h.md`, *Claims*.
The claims of the case judge the command, and the claims of the helper judge the helper.

## The claims

`stated` of the table tells which claims it states. A bit that is not set gives no test.

| Bit | It holds if |
| --- | --- |
| `MPBT_CLAIM_STATUS` | `status` of the end is `status`. |
| `MPBT_CLAIM_STATUS_NOT` | `status` of the end is not `status_not`. |
| `MPBT_CLAIM_LINE` | `has_lines`: each text is a whole line of the output, between 2 line ends, or at an end of the output. |
| `MPBT_CLAIM_HAS` | `has_texts`: the output holds each text. |
| `MPBT_CLAIM_LACKS` | `lacks_texts`: no text of `lacks` is in the output. |
| `MPBT_CLAIM_MATCHES`, `MPBT_CLAIM_MATCHES_NOT` | `test_hold_patterns` tells it. |
| `MPBT_CLAIM_ORDER` | `is_in_order`: each text matches a line, after the line of the text before it. |
| `MPBT_CLAIM_OUTPUT`, `MPBT_CLAIM_FILES` | `test_hold_output` and `test_hold_files` tell it. |

The variables of the copy go into each text first.
`is_in_order` compares a text with a line, after it cuts the spaces and the tabs at the start and at the end of the line. The text keeps its own spaces.

## The rules

Each `mpbt:TestRule` whose `exempt` does not name the group adds its `lacks` to the texts of `lacks_texts`.
The rules apply to the command and to the helper, also when the table states no `lacks`: `docs/extern/mpbt_case.h.md`, *Rules*.

## Functions

| Function | Result |
| --- | --- |
| `test_hold_claims` | `true` if each claim of the table holds, or `false`. A fault of the variables also gives `false`, and keeps the fault. |
| `has_lines` | Whether each text is a whole line of the output. |
| `has_texts` | Whether the output holds each text. |
| `lacks_texts` | Whether no text of the list and of the rules is in the output. |
| `is_in_order` | Whether the texts match lines of the output, in their order. |
