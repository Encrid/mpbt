# src/prose/prose.c

This file is the module `prose`. Its system counts the words of each sentence of the documents, and checks their blocks and the readme.
The messages are in `docs/extern/mpbt_check.h.md`, *prose*.

## The manifest

`mpbt:prose@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings of Bridge: its limits come from `mpbt:ProseCheck`.

## The components

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Project` | Read: `name` | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:ProseCheck` | Read: the limits | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

`bridge_init` declares the 4 types with `world_declare`, in the order of the table. Thus the slot of each type is its row, from 0.
The descriptors come from `include/mpbt_file.h`, `include/mpbt_project.h`, `include/mpbt_check.h` and `include/mpbt_finding.h`.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `prose` | `check` | `mpbt:File`: `BRIDGE_READ`, `BRIDGE_AND`. `mpbt:Project` and `mpbt:ProseCheck`: `BRIDGE_READ`, `BRIDGE_OPTIONAL`. | `mpbt:Finding` |

The name `prose` comes from `CHECKS_NAMES`. A singleton is on no entity, so the terms of the 2 singletons are optional.

## The steps

1. `world_rows` gives each row of `mpbt:File`. `bridge_native_get_single` gives `mpbt:Project` and `mpbt:ProseCheck`.
2. For each file that `markdown_is_document` names, `markdown_read` reads the bytes.
3. `prose_check_tags` checks the tag of each block, and `prose_check_units` counts the sentences and their words.
4. For `readme.md`, `prose_check_readme` also checks the title, the description and the sections.
5. `markdown_free` gives the document back before the next file.

`finding_write` writes each finding. No memory gives the status 1.

## The findings

| Field | Value |
| --- | --- |
| `check` | `prose`. |
| `path` | The `path` of the file. |
| `text` | The message. |
| `line` | The line of the fault. |
| `column` | 0. |

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares the 4 types, then the system `prose`. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_prose` | The findings of the prose of all the documents. |
