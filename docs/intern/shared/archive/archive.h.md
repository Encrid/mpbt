# src/shared/archive/archive.h

This header declares the reader and the writer of archives. They work on bytes in memory, so the callers do each read and each write of a file.
`fetch` unpacks the sources and zig. `pack` and `join` write the zips. The archives are those of `docs/extern/mpbt_source.h.md`, *fetch*.

## archive_entry_t

| Field | Value |
| --- | --- |
| `name` | The path of the entry in the archive, with `/`. |
| `kind` | A file, a folder, a link, or a hard link. |
| `mode` | The bits of the mode, for example the execute bits. |
| `bytes`, `len` | The bytes of a file. |
| `target` | The path that a link names. |

## Functions

| Function | Result |
| --- | --- |
| `archive_get_form` | Gives the form of an archive from the end of its name. |
| `archive_read` | Gives each entry of an archive to a function of the caller. |
| `archive_zip_make` | Writes a zip of entries into a `buffer_t`. |
| `archive_is_inside` | Tells whether a path stays inside the folder of the archive. |
