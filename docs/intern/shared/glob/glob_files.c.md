# src/shared/glob/glob_files.c

This file walks the folders below a root, and keeps each file that a glob of a list matches. `glob_match` tells each match.

## The walk

1. The names of a glob before its first name with a `*` give the first folder of the walk.
2. A glob with no `*` names one file. `os_path_entry` tells whether that file is there.
3. `os_folder_open` and `os_folder_read_entry` read each folder of the walk. The walk goes down into each entry that is a folder.
4. A glob with no name `**` has a fixed count of names. Thus the walk goes no deeper than that count.
5. Each file whose path from the root matches the glob is kept. A folder that does not open gives no file.

## The order

The order is that of `docs/extern/mpbt_project.h.md`, *Globs*. `files_compare` sorts the files of each glob.
The globs come in the order of the list. A file that an earlier glob gave does not come again.
Thus a file that 2 globs match comes one time, and a build does not compile a source two times.

## The result

`glob_files` writes each path into a `buffer_t`: from the root, with `/` between its names, and with a zero byte after it.
It gives the count of the paths, or -1 with no memory.

## The limits

The walk goes down 64 folders at most. A link to a folder above it makes a loop, and this limit ends the loop.
Thus a file that is more than 64 folders below the root is not found.

## Functions

| Function | Result |
| --- | --- |
| `glob_files` | The count of the files that match the globs, or -1. |
| `get_start` | The first folder of the walk of a glob. |
| `walk_folder` | Keeps each file of a folder that matches a glob, and walks each folder in it. |
| `keep_first` | Removes each path that an earlier glob gave. |
