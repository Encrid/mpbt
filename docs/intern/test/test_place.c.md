# src/test/test_place.c

This file gives a copy an empty folder, then writes the texts of `files` and fills the folders of `folders`.
The keys are in `docs/extern/mpbt_case.h.md`, *[[case]]*.

## The steps

1. `os_path_remove` removes the folder of the copy with all that it holds, and `os_folder_make` makes it again.
2. For each path of `folders`, `os_folder_make` makes the folder.
3. `copy_file` copies the file of each item of its list into it, with the name of the file.
4. For each path of `files`, `test_write_file` writes the text, as the case gives it.

Each path and each text gets the variables of the copy. `path_join` of `src/shared/path/path.h` then puts `{root}` before a path that is not absolute.
`test_find_item` gives the file of each item: the file of an artifact, or a file of the project.
If `copy_file` gives -1, the copy keeps the fault about a file that mpbt cannot read: `docs/extern/mpbt_command.h.md`, *Messages*.
The text of a file keeps its bytes, so a line end stays `\n` on each system.

## test_write_file

`test_write_file` makes the folder of a file with `os_folder_make`, then writes the bytes with `os_file_write`, with no execute bit.
The runs also write `said.txt`, the file of the hits and the copies of the tree with it.

## Functions

| Function | Result |
| --- | --- |
| `test_place` | `true`, or `false` with the fault of the copy. |
| `test_write_file` | `true` after the write, or `false`. |
| `fill_folders` | The folders of the use, with their items. |
| `write_files` | The files of the use. |
