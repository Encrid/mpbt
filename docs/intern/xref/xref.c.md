# src/xref/xref.c

This file is the module `xref`. Its system checks that each file `.md` cites only files and headings that are there.
The messages are in `docs/extern/mpbt_check.h.md`, *xref*.

## The manifest

`mpbt:xref@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

With `world_declare`, the 2 declarations take `mpbt_file_t_desc` and `mpbt_finding_t_desc`, in this order.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `xref` | `check` | `mpbt:File`: `BRIDGE_READ`, `BRIDGE_AND`. | `mpbt:Finding` |

The name `xref` comes from `CHECKS_NAMES`.

## The steps

1. `world_rows` gives each row of `mpbt:File`, and the system keeps it as a `files_item_t`.
2. `files_sort` sorts the items, so that `files_find` finds a path.
3. `xref_read_documents` reads the document of each file `.md`.
4. For each file `.md` outside `tests`, `xref_check_spans` checks its citations and its paths.
5. Then `xref_check_references` checks each reference to a heading of the same file.
6. `xref_free_documents` gives the documents back.

A file `.md` of `tests` is data of a case, and can hold a fault on purpose. Thus `xref` does not check it, as `xref.py` did not.

`finding_write` writes each finding. No memory gives the status 1.

## The findings

| Field | Value |
| --- | --- |
| `check` | `xref`. |
| `path` | The `path` of the document. |
| `text` | The message. |
| `line` | Where the citation, the path or the reference starts. |
| `column` | 0. |

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares 2 types, and then the system `xref`. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_xref` | The findings of the citations of the files `.md`. |
