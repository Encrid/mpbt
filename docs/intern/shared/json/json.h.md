# src/shared/json/json.h

This header declares a reader of JSON that gives one token at a time, and a small writer.
The probes, the count and the layer of `test` read the syntax tree that zig writes as JSON. The agreement writes its record as JSON.

## json_reader_t

| Field | Value |
| --- | --- |
| `fill`, `user` | The function that gives the next bytes of the document, and its value. |
| `window`, `at`, `end` | The bytes of the document that the reader holds, and its position in them. |
| `text` | The bytes of the last string or key, with its escapes replaced, in a `buffer_t`. |
| `depth` | The count of the objects and the lists that are open. |

## The tokens

`JSON_OBJECT_START`, `JSON_OBJECT_END`, `JSON_LIST_START`, `JSON_LIST_END`, `JSON_KEY`, `JSON_TEXT`, `JSON_NUMBER`, `JSON_TRUE`, `JSON_FALSE`, `JSON_NULL`, `JSON_DONE` and `JSON_FAULT`.
A number keeps its text, because the tree of zig holds offsets that are wider than a `double` can keep exact.

## json_writer_t

It writes into a `buffer_t`, and keeps for each open object or list whether it holds an item, for its commas.

## Functions

| Function | Result |
| --- | --- |
| `json_open` | Starts a reader on a source of bytes. |
| `json_next` | Gives the next token. |
| `json_skip` | Skips the value that starts at the token. |
| `json_write_object` | Writes an object, with its keys sorted. |
| `json_write_list_start`, `json_write_list_end` | Open and close a list. |
