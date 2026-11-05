# src/shared/json/json_write.c

This file writes the record of the agreement: a list of objects, each with the keys `day`, `name` and `pull_request`.

## The form

`json_write_object` sorts the pairs of an object by their keys, byte by byte, then writes them.
Thus 2 writes of one record give the same bytes, and a change of the record shows as one line in git.
Each item of a list starts on its own line, indented by 2 spaces.
A string gets an escape for `"`, `\` and each byte below 32. Each other byte stays as it is, so UTF-8 stays UTF-8.

## Functions

| Function | Result |
| --- | --- |
| `json_write_object` | Writes an object, with its keys in order. |
| `json_write_list_start` | Opens a list. |
| `json_write_list_end` | Closes a list. |
| `write_string` | Writes a string, with its escapes. |
| `sort_pairs` | Puts the pairs in the order of their keys. |
