# src/test/test_probe_condition.c

This file puts the probe of one condition around its bytes, also when an edge is in a macro.
The rules of a macro are in `docs/extern/mpbt_branches.h.md`, *test --branches*.

## The steps

1. A condition that `is_logical` finds gets no probe. Each of its 2 operands gets its own.
2. `get_edge` gives the byte and the path of each edge. The end adds the length of its last token.
3. An edge in an argument of a macro moves to the name of the call. That needs an offset in the expansion.
4. An edge that stays in a macro gives a branch that is not measured. So does a condition of `test_is_partial`.
5. The start and the end must be in one file of the project. Else the condition gets no probe.
6. An end in a macro moves past the `)` of its call: `find_call_end`.
7. The probe keeps the 2 bytes and the depth of the condition.

`is_logical` looks through `ParenExpr`, `ImplicitCastExpr` and a `UnaryOperator` with `!`. Then it finds a `BinaryOperator` with `&&` or `||`.
`find_call_end` reads the bytes that `files_find` gives for the file, after the name. It skips spaces and tabs, then counts the parentheses up to the `)` that closes the first one.
A name with no `(` after it is a macro with no arguments, such as `UINT32_MAX`. Its probe goes after the name.

## test_get_place

`test_get_place` gives the byte and the path of a location:

| Location | Result |
| --- | --- |
| None | None. |
| In a macro, with `is_macro_arg`, or with no offset in its expansion | The mark of a macro, and the path of the expansion. |
| In a macro | The byte of the expansion. |
| With an offset | The offset, then the length of the token for an end. |

## Functions

| Function | Result |
| --- | --- |
| `test_probe_condition` | The probe of a condition, or the branch that is not measured. |
| `test_get_place` | The byte and the path of a location, as *test_get_place* tells. |
| `get_edge` | The byte and the path of one edge of a condition. |
| `find_call_end` | The byte after the call of a macro, or the byte after its name. |
| `is_logical` | Whether a condition is a test with `&&` or `||`. |
