# src/fetch/fetch.h

This private header gives the state of a run of `fetch`, an archive in memory, and the functions that the files of `src/fetch` share.

## fetch_t

`fetch_t` is the state of one run of a system of `fetch`. It lives until the system returns.

| Field | Value |
| --- | --- |
| `api` | The entries of Bridge and the bases of the 2 memories, from BB-Native. |
| `root`, `zig`, `home` | The values of `{root}`, `{zig}` and `{home}`, from the rows of `mpbt:Variable`. |
| `sources` | The rows of `mpbt:Source`, in their order: *fetch_source_t*. |
| `count` | How many rows `sources` holds. |
| `finding` | The place of the findings of `fetch`: its slot of `mpbt:Finding`, and the check `fetch`. |
| `findings` | The number of findings of this run. |

## fetch_source_t

One row of `mpbt:Source`. Each field points to the bytes of its `bridge_text_t` in the shared memory, which stay for the whole phase.

| Field | Value |
| --- | --- |
| `name`, `url`, `sha256`, `into`, `top` | The texts of the row. |
| `patches` | The list of the patches. |

## fetch_archive_t

An archive that `fetch_download` gave, and that `fetch_unpack` puts into a folder.

| Field | Value |
| --- | --- |
| `name` | The last name of its address. It gives the form of the archive, and the name in the messages. |
| `bytes` | The bytes of the archive, in a `buffer_t`. |
| `folder` | The folder that gets the files. |
| `top` | A folder of the archive whose entries go into `folder` with no `top` before their names, or no bytes. |

Only zig gives a `top`: its archive holds one folder, and the program goes into the folder `zig` with no folder between.

## Functions

| Function | File |
| --- | --- |
| `fetch_get_world`, `fetch_free_world` | `fetch_world.c` |
| `fetch_zig` | `fetch_zig.c` |
| `fetch_sources`, `fetch_check_fetched` | `fetch_sources.c` |
| `fetch_download` | `fetch_download.c` |
| `fetch_unpack` | `fetch_unpack.c` |
| `fetch_patch` | `fetch_patch.c` |
