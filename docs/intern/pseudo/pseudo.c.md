# src/pseudo/pseudo.c

This file is the module `pseudo`. Its system checks each block of pseudo code of the documents against the profile.
The profile is in `docs/contributing/documentation_style.md`, *Blocks of code*. The messages are in `docs/extern/mpbt_check.h.md`, *pseudo*.

## The manifest

`mpbt:pseudo@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

`bridge_init` gives `mpbt:File` the slot 0 and `mpbt:Finding` the slot 1, with `world_declare` and the descriptors of their headers.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `pseudo` | `check` | `mpbt:File`: `BRIDGE_READ`, `BRIDGE_AND`. | `mpbt:Finding` |

The name `pseudo` comes from `CHECKS_NAMES`.

## The steps

1. `world_rows` gives each row of `mpbt:File`. The system keeps each path that `markdown_is_document` accepts.
2. `markdown_read` gives the blocks of the document.
3. For each block with the tag `pseudo`, `pseudo_check_block` checks the lines between its 2 fences.
4. The room for the tokens holds one token for each byte of the longest line of the block.

`finding_write` writes each finding. No memory gives the status 1.

## The findings

| Field | Value |
| --- | --- |
| `check` | `pseudo`. |
| `path` | The `path` of the document. |
| `text` | The message. |
| `line` | The line in the document. |
| `column` | 0. |

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares 2 types, then the system `pseudo`. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_pseudo` | The findings of the blocks of pseudo code. |
