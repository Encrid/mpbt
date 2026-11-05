# src/shared/path/path_join.c

This file puts a path after a folder when the path is not whole, for example a path of the config after `{root}`: `docs/extern/mpbt_project.h.md`, *Variables*.

## The steps

1. `path_is_whole` tells whether a path starts at a root: `/`, `\`, or a drive of Windows such as `C:`.
2. `path_join` clears the `buffer_t` of the caller.
3. A whole path goes into the buffer as it is.
4. Else the buffer gets the folder, a `/`, then the path. An empty path gives the folder alone.
5. Each `\` of the result becomes `/`, so a path has one form on each system.

The folder of a path of the config is `{root}`, which `read` makes whole. Thus each module starts a relative path in the same folder.
The folder of the program, from `os_get_program_path`, is the folder of the other paths, for example `zig` and `toolchain`.

## Functions

| Function | Result |
| --- | --- |
| `path_join` | `true` and the joined path, or `false` with no memory. |
| `path_is_whole` | Whether a path starts at a root. |
