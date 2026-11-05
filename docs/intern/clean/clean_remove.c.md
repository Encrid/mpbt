# src/clean/clean_remove.c

This file removes each entry of the output folder that does not stay. It goes down only into a folder that holds a path that stays.

## The steps

`clean_remove` does these steps on one folder, from the output folder down:

1. `read_names` reads each name with `os_folder_read_entry`, then `os_folder_close` closes the folder.
2. A name whose path is a path that stays keeps its entry.
3. A folder that holds a path that stays gets the same steps, one level down.
4. `os_path_remove` removes each other entry, with all that it holds. A read-only entry goes too.

The folder closes before the first removal. Thus a read of a folder ends before a removal changes the folder.
The depth of the walk is the depth of the deepest path that stays.

## The errors

The first fault stops the walk, and some entries can be gone already. `clean_remove` then gives `false`, with the text of the fault.

| Fault | Text |
| --- | --- |
| `os_folder_open` gives `nullptr`. | The message for a folder that does not list. |
| `os_path_remove` gives -1. | The message for a path that does not go. |
| A name does not fit in memory. | No text. Then `bridge_clean` gives 1. |

The messages are in `docs/extern/mpbt_command.h.md`, *Messages*. Each one names the path that failed.

## Functions

| Function | Result |
| --- | --- |
| `clean_remove` | `true` after the walk, or `false` and the text of the fault. |
| `read_names` | The names of a folder in one `buffer_t`, each with a zero byte after it. |
| `is_kept` | Whether a path inside the output folder is a path that stays. |
| `holds_kept` | Whether a folder holds a path that stays. |
