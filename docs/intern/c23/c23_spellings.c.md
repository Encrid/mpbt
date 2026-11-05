# src/c23/c23_spellings.c

This file holds the older spellings that C23 replaces, and finds them in the tokens: `docs/contributing/coding_style.md`, *C23*.
Each newer spelling is the text of its row in `docs/extern/mpbt_check.h.md`, *c23*.

## The forms of the code

`c23_match_code` reads the window after each new token, and looks for a form that ends with that token.

| Form | Tokens |
| --- | --- |
| A name | `NULL`, `_Bool`, `_Alignof`, `_Alignas`, `_Static_assert`, `_Thread_local`, `THREAD_LOCAL`, `_Noreturn`, `__attribute__` or `__declspec`. |
| An `enum` with no name | `enum`, then `{` or `:`. |
| An `enum` with no width | `enum`, a name, then `{`. |
| `(void)name;` | `(`, `void`, `)`, a name, then `;`. |
| `= {0};` | `=`, `{`, the number `0`, `}`, then `;`. |

The table of `c23_spelling_t` holds the names, and each one is a whole token. Thus `MY_NULL` is no fault.
An `enum` with a name, `:` and a type is the newer spelling, so its `{` makes no fault.

## The forms of a directive

`c23_match_directive` reads the first tokens of a directive with `c_tokens_start_directive` and `c_tokens_next_code`. Thus the spaces and the comments between them do not count.

| Form | Tokens |
| --- | --- |
| `#include <stdbool.h>` | `include`, then `<`, `stdbool`, `.`, `h` and `>`. |
| A macro for a number | `define`, a name that no `(` touches, then a number. Each `-`, `+` and `(` before the number is a part of the form. |

## The findings

`finding_format` of `src/shared/finding/finding.h` writes each finding, at the first token of its form. The text is the older text, 2 spaces, `->`, 2 spaces, and the newer spelling.
The older text has the names of the file, with one space between its words. Thus each text is one line.

| Form | Older text |
| --- | --- |
| A name | The name. |
| An `enum` with no name | `enum {`, or `enum :`. |
| An `enum` with no width | `enum`, the name, then `{`. |
| `(void)name;` | `(void)`, the name, then `;` with no space. |
| `= {0};` | `= {0};`. |
| `#include <stdbool.h>` | `#include <stdbool.h>`. |
| A macro for a number | `#define` and the name of the macro. |

## Functions

| Function | Result |
| --- | --- |
| `c23_match_code` | Writes a finding if the window ends with a form of the code. |
| `c23_match_directive` | Writes a finding if a directive has a form of a directive. |
| `match_enum` | The first token of a form of `enum` at the end of the window, or `C23_WINDOW`. |
| `match_void` | `true` if the window ends with `(void)name;`. |
| `match_zero` | `true` if the window ends with `= {0};`. |
