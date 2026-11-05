# src/shared/regex/regex_parse.c

This file reads a pattern into a tree of nodes, and refuses each form that is not in the subset of mpbt.

## The grammar

```text
alternation  sequence ( "|" sequence )*
sequence     repeat*
repeat       atom ( "*" | "+" | "?" | "{" m "}" | "{" m "," "}" | "{" m "," n "}" )?
atom         byte | "." | class | "(" alternation ")" | "^" | "$" | "\b" | escape
```

A byte is each byte of the pattern that is not a mark of the grammar. A mark becomes a byte after `\`.
`\d`, `\w`, `\s` and `\D`, `\W`, `\S` are classes of `regex_class.c`.

## The refusals

The parse stops at the first form that is not in the subset, and names it for the message of `docs/extern/mpbt_case.h.md`.

| Form | Example |
| --- | --- |
| A group with `?` after `(` | `(?=x)`, `(?:x)` |
| A back reference | `\1` |
| A lazy repeat | `*?`, `+?`, `??` |
| An escape of a letter that has no meaning here | `\A`, `\Z`, `\B` |
| A repeat with nothing to repeat | `*x` |

## Functions

| Function | Result |
| --- | --- |
| `regex_parse` | The tree of a pattern, or the refused form. |
| `parse_alternation` | The node of an alternation. |
| `parse_sequence` | The node of a sequence. |
| `parse_repeat` | The node of a repeat. |
| `parse_atom` | The node of one atom. |
