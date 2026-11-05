# src/style/style_fault.c

This file takes each fault that a rule finds, and writes its finding with `finding_vformat` if no exception excuses it.
`src/shared/finding/finding.h` writes the finding: `docs/extern/mpbt_finding.h.md`, *The report*.

## The format of a fault

Each rule gives a format of `printf` that starts with the rule and a space. The message of `docs/extern/mpbt_check.h.md`, *style*, comes after them.
Thus the text of each finding names its rule, and the code states the rule of a fault one time only.

## The steps

1. After `failed` is set, `style_add_fault` drops each fault.
2. The rule of the fault is the bytes of the format before its first space.
3. A fault with no function gets the function that holds its line: `find_function`.
4. If `style_is_excused` accepts the fault, the fault gives no finding.
5. Else `finding_vformat` writes the finding at the place of the fault, with `place` of the run.

A function holds the lines from the line before its first token to the line of its closing bracket.
Thus a comment just above a function belongs to the function too.

## The place

| Field of `finding_t` | Value |
| --- | --- |
| `check` | `style`, from `CHECKS_NAMES`. |
| `path` | The path of the `mpbt:File` under check. |
| `line`, `column` | The place of the token of the fault. A fault with no token, as F3 or G1, has the column 0. |

## Functions

| Function | Result |
| --- | --- |
| `style_add_fault` | Writes the finding of a fault that no exception excuses. |
| `find_function` | The name of the function that holds a line, or `STYLE_NONE`. |
