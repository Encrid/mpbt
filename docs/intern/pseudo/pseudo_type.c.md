# src/pseudo/pseudo_type.c

This file reads a type and a parameter.

## Types

A type is one of these:

1. A word of `types`: `docs/intern/pseudo/pseudo_words.c.md`, *The words*.
2. `ARRAY`, `[`, the bounds of each dimension with a comma between them, `]`, `OF`, and a type.
3. A name whose upper case is no word of `types`. Thus `integer` is no type, but `fault_t` is one.

The bounds of a dimension are an expression, `:`, and an expression, for example `1:64`.

## Parameters

A parameter is `BYREF` or `BYVAL` if it comes, a name, `:`, and a type.

## Functions

| Function | Result |
| --- | --- |
| `pseudo_read_type` | `true` after a type. |
| `pseudo_read_parameter` | `true` after a parameter. |
| `read_bounds` | `true` after the bounds of one dimension. |
