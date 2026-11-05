# src/fetch/fetch_unpack.c

This file puts each entry of an archive into a folder, with its mode: `docs/extern/mpbt_source.h.md`, *fetch*.

## The steps

1. `archive_get_form` gives the form of the archive from its name.
2. `archive_read` gives each entry to `put_entry`, in the order of the archive.
3. `archive_is_inside` refuses a name that leaves the folder, and the target of a link that leaves it.
4. With a `top`, an entry outside `top` stays out, and an entry inside it loses `top` and its `/`.
5. A folder goes in with `os_folder_make`. A file goes in with `os_file_write`, after `os_folder_make` of its folder.
6. `put_entry` keeps each link and each hard link for the end. Then `put_links` makes them.

A name that leaves the folder stops the run with its message of `docs/extern/mpbt_source.h.md`, *Messages*.
When the system makes no file or no folder of an entry, the run stops: `docs/extern/mpbt_command.h.md`, *Messages*.

## The modes

A file with an execute bit in its mode gets `executable` of `os_file_write`. Thus a program of an archive can run on Linux and on macOS.
Windows has no execute bit, so the mode changes nothing there.

## The links

A link can name a file that comes later in the archive. Thus `put_links` runs after the last entry.

- `os_link_make` makes a link with the target of the entry.
- If `os_link_make` fails, `copy_file` of `src/shared/copy/copy.h` copies the file of the target to the path of the link, with its execute bit. That happens on Windows with no Developer Mode.
- A hard link names an earlier entry of the archive. `copy_file` copies that file too, because the layer makes no hard link.
- A target that is not there gives no copy, as a link to nothing gives no bytes.

A name with no form stops the run before step 2, with its message of `docs/extern/mpbt_source.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `fetch_unpack` | `true` after each entry, or `false` and a finding. |
| `put_entry` | Puts one entry into the folder, or keeps a link for the end. |
| `put_links` | `true` after each link, or `false` with no memory. |
