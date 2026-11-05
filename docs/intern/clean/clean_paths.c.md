# src/clean/clean_paths.c

This file finds the output folder, and the paths that `clean` keeps in it: `docs/extern/mpbt_command.h.md`, *The commands*.

## The paths that stay

`clean` keeps what mpbt and `fetch` put into the output folder. Thus the next build downloads nothing again.

- The program mpbt, from `os_get_program_path`. A `nullptr` of that call has no message of its own, so `bridge_clean` gives 1.
- The folders `zig`, `toolchain` and `zig-cache` beside the program.
- The folder `into` of each `mpbt:Source`: `docs/extern/mpbt_source.h.md`, *[[source]]*.

`distclean` keeps nothing, so `clean_get_paths` gives it no path that stays.

## The steps

1. `world_rows` gives the rows of `mpbt:Variable`. Those of `MPBT_SCOPE_PROJECT` give `{build}` and `{root}`.
2. `os_path_entry` tells whether a folder is at `{build}`. Without one, `clean_get_paths` stops there.
3. `os_path_whole` makes `{build}` and `{root}` whole. `clean_is_inside` and `clean_is_same` then tell whether the output folder holds the root.
4. For `clean`, `world_rows` gives each `mpbt:Source`, and `path_join` starts a relative `into` in `{root}`.
5. `path_join` also joins `zig`, `toolchain` and `zig-cache` to the folder of the program.
6. `add_kept` skips a path that `os_path_entry` does not find, because nothing is there to keep.
7. `add_kept` makes each other path whole, and skips it if it is not inside the output folder.
8. The list keeps the rest of each path after the output folder and its separator.

On Linux and macOS, `os_path_whole` gives a real path, and it needs the path to be there. Thus step 6 comes before step 7.
A path that is there and does not become whole, in step 3 or 7, is a fault. Its text is the general message of a path that the system does not read: `docs/extern/mpbt_command.h.md`, *Messages*.

## The comparison

`clean_is_same` takes `/` and `\` as one separator, and ignores the case of the ASCII letters, on each system.
The file systems of Windows and of macOS ignore the case of a name by default. Thus a path matches in each of its spellings.
On Linux, a false match only keeps an entry, or refuses a clean. It never removes an entry that must stay.
`clean_is_inside` compares in the same way: a path is inside a folder if it starts with the folder and a separator.

## Functions

| Function | Result |
| --- | --- |
| `clean_get_paths` | `true` and the paths. On a fault, `false` and its text. |
| `clean_free_paths` | Gives the memory of the paths back. |
| `clean_is_same` | Whether 2 paths name the same entry, with the rules of *The comparison*. |
| `clean_is_inside` | Whether a path is inside a folder, with the same rules. |
| `add_kept` | Adds one path that stays, if it is there and inside the output folder. |
