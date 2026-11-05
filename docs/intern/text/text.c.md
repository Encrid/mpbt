# src/text/text.c

This file gives the exports of the module `text`: `bridge_init`, `bridge_shutdown`, `bridge_reload` and its system. The system checks each file for characters that are not ASCII, comments, retired words and refused calls, and each script for its legal notice.
The messages are in `docs/extern/mpbt_check.h.md`, *text*.

## The manifest

`mpbt:text@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.
`read` writes `mpbt:TextCheck` from `[check]`: `docs/extern/mpbt_check.h.md`, *The grants*.

## The components

Each descriptor is in the header of its type, in `include`. The table is the order of the calls of `world_declare`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:TextCheck` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Retired` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Project` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_command_name_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `text` | `check` | `mpbt:File`, `mpbt:Retired`, `mpbt:TextCheck`, `mpbt:Project` and `mpbt:Command`, each with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

A file and a retired word are on different entities, so no term is of `BRIDGE_AND`.
The changes of `text` name `mpbt:Finding`.

## The steps

1. `world_rows` walks the rows. Its visit, `take_rows`, keeps each file and each retired word.
2. `bridge_native_get_single` gives the 3 singletons. A singleton with no value counts as zeros.
3. `text_read_lists` reads the refused names of each list of `refuse`.
4. `text_check_file` checks each file with the checks that its path asks for.

Each finding has the check `text`, the path of its file, and its line. A list that does not read gives a finding with no path.
`finding_write` and `finding_format` write the findings: `docs/intern/shared/finding/finding.h.md`.
No memory gives the status 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0, or the status of the refusal. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_text` | 0, also after a finding. |
| `take_rows` | The files, the retired words and the settings, in a `text_t`. |
