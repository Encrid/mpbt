# src/text/text_calls.c

This file finds each call of a refused name in the code: the files `.c` and `.h` of `src` and of `include`.

## A call

`c_tokens_start` and `c_tokens_next` give the tokens of the file.
A call is a token of a name, then the mark `(`, with a token of spaces or nothing between them.
A name in a comment or in a string is a part of that token, so it is no call.
`bsearch` finds the name among the refused names. The finding of a refused name has its line, and the path of its list.

## Functions

| Function | Result |
| --- | --- |
| `text_check_calls` | A finding for each call of a refused name. |
| `get_list` | The path of the list that refuses a name, or no path. |
