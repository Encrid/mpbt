# src/c23/c23_scan.c

This file reads the tokens of one file of C, and gives each token of the code to the forms of `src/c23/c23_spellings.c`.
The check reads the files `.c` and `.h` of `docs/extern/mpbt_file.h.md`, *The files of the project*.

## The steps

1. `c23_check_file` returns at once for a path that does not end with `.c` or `.h`.
2. A scan of `c_tokens_start` reads the file, and `c_tokens_next_code` gives its tokens one by one.
3. That function skips the spaces, the line ends and the comments. Thus no form reads the text of a comment.
4. `push_token` puts each token but a directive into the window. Then `c23_match_code` reads the window.
5. A directive goes to `c23_match_directive`, and then to `scan_directive`.

A string is one token. Thus a form does not find a name in the text of a string.

## The tokens of a directive

`scan_directive` starts a second scan with `c_tokens_start_directive`, and each token goes into a new window that `c23_match_code` reads.
Thus a name such as `NULL` in the text of a macro is a fault too.
The second scan gives each token the line and the column that it has in the file.

## Functions

| Function | Result |
| --- | --- |
| `c23_check_file` | Reads one file, and finds each older spelling. |
| `push_token` | Adds a token to a window, and drops the oldest one from a full window. |
| `scan_directive` | Reads the tokens of one directive. |
