# src/shared/variables/variables_expand.c

This file replaces each variable of a text with its value, into a `buffer_t`.

## The form of a variable

A variable is `{`, a name, then `}`. A name starts with a lower-case letter or `_`, and holds lower-case letters, digits and `_`.
A list variable inside a text has a separator: `{`, the name, `:`, the separator, then `}`. The separator holds no brace, and mpbt keeps its bytes as they are.
Each other `{` is a byte of the text.

## The steps

```pseudo
PROCEDURE expand_text(text : STRING)
   DECLARE at : INTEGER
   at <- 1
   WHILE at <= LENGTH(text)
      IF is_variable(text, at) THEN
         CALL expand_one(text, at)
         at <- next_after_variable(text, at)
      ELSE
         CALL add_byte(text, at)
         at <- at + 1
      ENDIF
   ENDWHILE
ENDPROCEDURE
```

`expand_one` finds the entry of the name. A text value is expanded in its turn. A list value is joined with the separator, after each item is expanded.
`expand_one` keeps the names that it is expanding on a stack. A name that is already on the stack holds itself, and the expansion stops with a finding.
The messages are in `docs/extern/mpbt_project.h.md`, *Messages*.

## The names of a later phase

The caller gives the list of the names that a later phase gives. For example, a build gives `{name}` and `{work}`, and a case gives `{case}` and `{port}`.
`expand_one` writes such a variable as it is, with its braces and its separator.
Thus `read` keeps them, for example in a key of a target, and the later phase replaces them: `docs/extern/mpbt_project.h.md`, *Variables*.

## The limits

The stack holds each name one time, so its depth is at most the count of the variables.

## Functions

| Function | Result |
| --- | --- |
| `variables_expand` | `true` and the text, or `false` and a finding. It keeps each name of the list of a later phase. |
| `expand_one` | One variable, replaced. |
| `join_list` | The items of a list, with the separator between them. |
