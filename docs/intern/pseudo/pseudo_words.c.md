# src/pseudo/pseudo_words.c

This file holds the words of the profile in one table, and gives the entry of a word.

## The words

```text
types       INTEGER REAL CHAR STRING BOOLEAN DATE U8 U16 U32 U64 I8 I16 I32 I64 F32 F64
operators   = <> < <= > >= + - * / & DIV MOD AND OR
starts      TYPE IF ELSE CASE FOR WHILE REPEAT PROCEDURE FUNCTION
ends        ENDTYPE ELSE ENDIF ENDCASE NEXT ENDWHILE UNTIL ENDPROCEDURE ENDFUNCTION
alone       ELSE ENDIF ENDTYPE ENDCASE ENDWHILE REPEAT ENDPROCEDURE ENDFUNCTION
others      DECLARE CONSTANT THEN OF OTHERWISE TO STEP RETURNS CALL RETURN BYREF BYVAL NOT TRUE FALSE ARRAY
```

Each word of these lines is a keyword. A word of `alone` makes a line by itself.

## The blocks

| Start | End |
| --- | --- |
| `TYPE` | `ENDTYPE` |
| `IF` | `ELSE` or `ENDIF` |
| `ELSE` | `ENDIF` |
| `CASE` | `ENDCASE` |
| `FOR` | `NEXT`, then the variable of the `FOR` |
| `WHILE` | `ENDWHILE` |
| `REPEAT` | `UNTIL` |
| `PROCEDURE` | `ENDPROCEDURE` |
| `FUNCTION` | `ENDFUNCTION` |

## The refused words

`pseudo_find_refused` gives the first token of a line that the profile refuses, and the form of its message.

| Token | Form |
| --- | --- |
| `//` | `comments` |
| The arrow of the guide, U+2190 | `the arrow of the guide: write <-` |
| `:=` | `:=, write <-` |
| `INPUT`, `OUTPUT` | `input and output` |
| `OPENFILE`, `READFILE`, `WRITEFILE`, `CLOSEFILE`, `SEEK`, `GETRECORD`, `PUTRECORD`, `EOF` | `file handling` |
| `CLASS`, `ENDCLASS`, `INHERITS`, `NEW`, `SUPER`, `PUBLIC`, `PRIVATE` | `classes and objects` |

The form goes into its message of `docs/extern/mpbt_check.h.md`, *pseudo*. A refused word is no keyword.

## Functions

| Function | Result |
| --- | --- |
| `pseudo_get_word` | The entry of a word in the table, or none. |
| `pseudo_find_refused` | The first refused token of a line, and its form, or none. |
