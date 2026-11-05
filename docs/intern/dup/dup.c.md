# src/dup/dup.c

This file is the module `dup`. Its system finds each passage of 8 words or more that 2 documents of one scope hold.
A passage in 2 documents is one fact in 2 places, and one of the 2 places can become false.
The message is in `docs/extern/mpbt_check.h.md`, *dup, cover and licence*.

## The manifest

`mpbt:dup@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

`world_declare` takes the descriptor of each type from its header, `include/mpbt_file.h` or `include/mpbt_finding.h`.

## The scopes

| Scope | Documents |
| --- | --- |
| The project | `readme.md` and the documents of `docs` |
| The toolchain | The documents of `.toolchain/docs` |

`dup` never compares a document of one scope with a document of the other. A project does not change `.toolchain/docs`, so it cannot fix such a pair.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `dup` | `check` | `mpbt:File`: `BRIDGE_READ`, `BRIDGE_AND`. | `mpbt:Finding` |

The name `dup` comes from `CHECKS_NAMES`.

## The steps

1. `world_rows` gives each row of `mpbt:File`. Each row that `markdown_is_document` names goes into its scope.
2. `files_sort` puts the documents of each scope in the order of their paths.
3. For each document of a scope, `markdown_read` and `dup_read_words` read its sentences.
4. `dup_add_runs` puts each run of 8 words of the scope into the table of runs.
5. `dup_find_passages` gives each passage of the scope to `finding_write`.

No memory gives the status 1.

## The findings

| Field | Value |
| --- | --- |
| `check` | `dup`. |
| `path` | No bytes: a passage has 2 places or more. |
| `text` | The places and the passage: `docs/intern/dup/dup_passages.c.md`, *The text of a finding*. |
| `line`, `column` | 0. |

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares the 2 types and the system `dup`. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_dup` | The findings of the passages of both scopes. |
