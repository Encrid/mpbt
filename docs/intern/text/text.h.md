# src/text/text.h

This private header declares `text_t`, `text_scan_t` and `text_token_t`, and the functions that the files of `src/text` share.

## text_t

`text_t` holds what the check `text` reads in one run.

| Field | Value |
| --- | --- |
| `files` | A `files_item_t` for each file of `mpbt:File`. |
| `count` | How many files `files` holds. |
| `unicode` | `unicode` of `mpbt:TextCheck`: one pattern on each line. |
| `refuse` | `refuse` of `mpbt:TextCheck`: the path of one list on each line. |
| `retired` | The word and the new word of each `mpbt:Retired`. |
| `notice` | `notice` of `mpbt:Project`: the text of `.toolchain/header.txt`. |
| `root` | `root` of `mpbt:Command`: the folder of the project. |
| `lists` | The bytes of each list of `refuse`, as `path_read` gives them. |
| `names` | Each refused name, with the path of its list, in the order of the names. The bytes of a name are in `lists`. |

## text_scan_t

A scan of a script, as `text_script.c` reads it.

| Field | Value |
| --- | --- |
| `bytes`, `len` | The bytes of the script. |
| `at`, `line` | The position of the next token, and its line from 1. |

## text_token_t

One token of a script: `text_script_tokens.c`.

| Field | Value |
| --- | --- |
| `kind` | A string, a comment, `(`, `)`, `[` or `{`, `]` or `}`, `;`, a line end, each other token, or the end of the script. |
| `line` | The line of the first byte of the token. |
| `plain` | `true` for a string with no prefix, or with only the letters `r`, `R`, `u` and `U` in its prefix. |

## Functions

| Function | File |
| --- | --- |
| `text_check_file` | `text_file.c` |
| `text_check_ascii` | `text_ascii.c` |
| `text_check_script` | `text_script.c` |
| `text_next_token` | `text_script_tokens.c` |
| `text_check_hashes`, `text_check_markup` | `text_comment.c` |
| `text_check_retired` | `text_retired.c` |
| `text_read_lists`, `text_compare_names` | `text_refuse.c` |
| `text_check_calls` | `text_calls.c` |
