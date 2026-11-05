# src/layout/layout.c

The exports of the module `layout` are in this file. Its system checks where each file of the project is, the names of its path, and its document.
The messages are in `docs/extern/mpbt_check.h.md`, *layout*.

## The manifest

`mpbt:layout@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.
`read` writes `mpbt:LayoutCheck` from `[check]`: `docs/extern/mpbt_check.h.md`, *The grants*. With no value, it names no guide.

## The components

`world_declare` declares each type with its descriptor of `include/mpbt_file.h`, `include/mpbt_check.h` or `include/mpbt_finding.h`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:LayoutCheck` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.
With `BRIDGE_SWEEP`, no empty entity stays after the last unload, and an entity that carries more components stays.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `layout` | `check` | `mpbt:File`, with `BRIDGE_READ` and `BRIDGE_AND`. `mpbt:LayoutCheck`, with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

The changes of `layout` name `mpbt:Finding`, which it attaches.

## The steps

1. `world_rows` walks the rows of `mpbt:File`: `docs/intern/shared/world/world.h.md`. Its visit `take_files` keeps each path and its bytes.
2. `bridge_native_get_single` gives `mpbt:LayoutCheck`.
3. `files_sort` sorts the files by path, so that `files_find` finds a path: `docs/intern/shared/files/files.c.md`.
4. `layout_check_paths` checks the place of each file, and the needed paths.
5. `layout_check_names` checks each name of each path.
6. `layout_check_documents` checks the document of each file, and the file of each document.

Each finding has the check `layout`, and the path that its message names first.
`finding_write` and `finding_format` write the findings: `docs/intern/shared/finding/finding.h.md`.
No memory gives the status 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0, or the status of the refusal. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_layout` | 0, also after a finding. |
| `take_files` | The files of the project and the guides, in a `layout_t`. |
