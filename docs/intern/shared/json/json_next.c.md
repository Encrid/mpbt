# src/shared/json/json_next.c

This file gives the tokens of a document in their order, and holds only a window of its bytes.
A syntax tree of zig can have 300 MB for a source of 3 KB, so the reader never holds the whole document.

## The window

`refill` moves the bytes that are not read yet to the start of `window`, then asks `fill` for up to 64 KiB more.
A token that does not fit makes the window grow. Thus a long string costs memory only while it is read.

## The steps of `json_next`

1. It skips the spaces, the tabs and the line ends.
2. It reads one byte. That byte decides the token.
3. After `,` or `:`, it reads the next token. A key is a text before `:` in an object.
4. It keeps `depth`, and gives `JSON_DONE` at the end of the value at the top.

A token starts with a brace, a bracket, a quote, a digit, `-`, `t`, `f` or `n`.
A byte that no token can start, or the end of the bytes inside a value, gives `JSON_FAULT` and its offset.

## Functions

| Function | Result |
| --- | --- |
| `json_open` | A reader at the start of a document. |
| `json_next` | The next token. |
| `refill` | More bytes in the window. |
| `read_word` | `true`, `false` or `null`. |
| `read_number` | The text of a number. |
