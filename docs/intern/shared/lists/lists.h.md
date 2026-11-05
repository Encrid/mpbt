# src/shared/lists/lists.h

This header declares the functions that write and read a list or a map in the form of `docs/extern/mpbt_project.h.md`, *Lists and maps*.
Each module of mpbt uses them for the lists of its components, and for the lists of its settings.

## lists_item_t

An item that a module gives to `lists_write`:

| Field | Value |
| --- | --- |
| `bytes` | The bytes of the item. |
| `len` | The count of these bytes. |

## Functions

| Function | Result |
| --- | --- |
| `lists_get_size` | Gives the bytes that one `alloc` needs for a list. |
| `lists_write` | Writes a list into bytes of the arena. |
| `lists_get_count` | Gives the count of the items. |
| `lists_get_item` | Gives one item of a list. |
| `lists_find` | Gives the value of a key of a map. |
| `lists_get_line` | Gives the next line of a list of a setting. |
