# src/shared/mirror/mirror.h

This header declares how the path of a file of `include`, `src` or `tools` gives the path of its document, and back.
The checks `layout` and `cover` use it.

## mirror_t

A path that `mirror_t` gives has 3 parts, one after the other:

| Field | Value |
| --- | --- |
| `folder`, `folder_len` | The first folders of the path, with the `/` after them, for example `docs/intern/`. |
| `rest`, `rest_len` | The rest of the path that the caller gives, after its first folder, and with no `.md`. |
| `end`, `end_len` | `.md` for the path of a document, or no bytes for the path of a file. |

## Functions

| Function | Result |
| --- | --- |
| `mirror_get_document` | From a file: `true` and its document, in 3 parts. `false` for a file with no document. |
| `mirror_get_file` | From a document: `true` and its file, in 3 parts. `false` for a path that is no document. |
