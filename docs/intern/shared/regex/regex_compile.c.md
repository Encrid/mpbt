# src/shared/regex/regex_compile.c

This file turns the tree of a pattern into the steps of a program, by the construction of Thompson.

## The steps of a program

| Step | It matches |
| --- | --- |
| `BYTE` | One byte. |
| `SET` | One byte of a set. |
| `SPLIT` | Goes on at 2 steps at once. |
| `JUMP` | Goes on at a step. |
| `BEGIN` | The start of the text. |
| `END` | The end of the text, or a line end that is the last byte. |
| `WORD` | A border between a byte of `\w` and a byte that is not of `\w`. |
| `MATCH` | The pattern is found. |

`*`, `+` and `?` become a `SPLIT` and a `JUMP`.
`{m,n}` becomes `m` copies of the atom, then `n - m` copies, each one behind a `SPLIT`. `{m,}` becomes `m` copies, then the steps of `*`.

## The limits

A program has at most 65536 steps. A pattern with more stops the cases before the first one: `docs/extern/mpbt_case.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `regex_compile` | The program of a pattern. |
| `emit` | Adds one step. |
| `compile_node` | The steps of one node. |
| `compile_repeat` | The steps of a repeat. |
