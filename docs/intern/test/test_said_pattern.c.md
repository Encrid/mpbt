# src/test/test_said_pattern.c

This file makes the pattern of a message of the code for `src/shared/regex`. A conversion of the message matches each text on one line.

## The steps

1. `read_conversion` finds each conversion of the message. The bytes between 2 conversions are a part.
2. `add_escaped` adds the bytes of each part to the pattern, with a `\` before each mark of the grammar.
3. In place of each conversion, the pattern gets a set of each byte but the line end, then `*`.
4. `%%` gives one `%`. A `%` with no conversion after it stays a byte.
5. The count of the bytes of the parts is the count of the own characters.

The marks are `\`, `.`, `[`, `]`, `(`, `)`, `|`, `*`, `+`, `?`, `{`, `}`, `^` and `$`: `docs/intern/shared/regex/regex_parse.c.md`, *The grammar*.
No letter gets a `\`, so the pattern holds no form that the parse refuses.
Thus a document can write `<name>` in the place of a conversion: `docs/contributing/documentation_style.md`, *The messages of the code*.

## A conversion

A conversion is `%`, then these parts in this order, then one of the letters `diouxXcsfgeEp`:

| Part | Bytes |
| --- | --- |
| Flags | Each of `-`, `+`, a space, `#` and `0`, as many times as they come. |
| Width | `*`, or digits. It can be absent. |
| Precision | `.`, then `*` or digits. It can be absent. |
| Length | `hh`, `h`, `ll`, `l`, `z`, `j` or `t`. It can be absent. |

## Functions

| Function | Result |
| --- | --- |
| `test_make_said_pattern` | The pattern of a message, and the count of its own characters. |
| `read_conversion` | The length of the conversion at a `%`, or 0. |
| `add_escaped` | Adds the bytes of a part to the pattern. |
