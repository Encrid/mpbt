# src/style/style_control.c

This file checks one control of a body: `if`, `while`, `for`, `switch`, `else` or `do`. The rules are L1, L4, C1 and C2 of `docs/contributing/coding_style.md`.

## The steps

1. `style_start_line` checks where the control starts. An `else` with `if` after it is one control.
2. For a control with a condition, `check_condition` reads the tokens between its parentheses.
3. `count_branch` counts the branches of the chain of `if` at the level of the control.
4. A control that does not start with `else` is one depth more. A depth above the limit `depth` is a fault of C1.
5. `check_control_bracket` checks the token after the head: after the condition, or after `else` or `do`.

## The rules

| Rule | Fault |
| --- | --- |
| L1 | The condition of `if`, `else if`, `while` or `switch` holds `=`. The condition of a `for` can hold it. |
| C2 | The condition holds 2 `?` or more. |
| C1 | `if` starts a chain of 1 branch, and each `else` adds 1. The first branch past the limit `branches` is the one fault of the chain. |
| L4 | The `{` after the head is not on the line where the head ends. Or a token of the code comes after the `{` on its line. |
| L1 | With no `{`, a token on the line where the head ends starts the statement of the control. A `;` there is no fault. |

A fault of L4 is at the `{`, and the fault of a chain at the `else` past the limit. Each other fault is at the first token of the control.
A `{` opens a block with `control`, one level deeper. With no `{`, `extra` gives one level to the statement that comes next.

## Functions

| Function | Result |
| --- | --- |
| `style_check_control` | Checks a control, and gives the token after its head. |
| `check_condition` | Checks L1 and C2 in a condition. |
| `count_branch` | Counts one branch of a chain, and checks C1. |
| `check_control_bracket` | Checks L4 or L1 after the head, and opens the block. |
