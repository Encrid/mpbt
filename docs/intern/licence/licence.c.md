# src/licence/licence.c

This file has the exports of the module `licence`. Its system checks `license`, `cla.md`, the notices of `third_party`, and the files that say that all rights are reserved.
The messages are in `docs/extern/mpbt_check.h.md`, *dup, cover and licence*.

## The manifest

`mpbt:licence@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

`world_declare` declares the 2 types with their descriptors, from `include/mpbt_file.h` and `include/mpbt_finding.h`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `licence` | `check` | `mpbt:File`, with `BRIDGE_READ` and `BRIDGE_AND`. |

The changes of `licence` name `mpbt:Finding`.

## The steps

1. `take_files` is the visit of `world_rows`: it keeps each file of the rows, with its path and its bytes.
2. `files_sort` puts them in the order of their paths, for `files_find`: `docs/intern/shared/files/files.c.md`.
3. `licence_check_text` compares `license` with the published text.
4. `licence_check_reserved` reads each other file for a text that reserves all rights.
5. `licence_check_notices` checks the sources of `third_party`, `cla.md`, and the readme.

Each finding has the check `licence`. Only the finding of reserved rights has a path and a line.
`finding_write` and `finding_format` write the findings: `docs/intern/shared/finding/finding.h.md`.
No memory gives the status 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0, or the status of the refusal. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_licence` | 0, also after a finding. |
| `take_files` | The files of the project, in a `licence_t`. |
