# src/shared/c_tokens/c_tokens_literal.c

This file reads a number, a string and a character to their end.

## A number

A number is a number of the preprocessor: a digit, or `.` and a digit, then each letter, digit, `_`, `.` and `'` that follows.
A `+` or a `-` after `e`, `E`, `p` or `P` stays in the number. Thus `0x1p-3` and `1'000` are one token each.

## A string and a character

The token goes from its quote to the next quote of the same kind that no `\` escapes.
A line end before that quote ends the token, as an unclosed string. The check `style` then reports the line.
A prefix `u8`, `u`, `U` or `L` is a part of the token.

## Functions

| Function | Result |
| --- | --- |
| `read_number` | A number of the preprocessor. |
| `read_quoted` | A string or a character, to its end quote. |
