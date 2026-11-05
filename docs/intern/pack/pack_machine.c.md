# src/pack/pack_machine.c

This file refuses a deliverable whose files hold a folder of this machine: `docs/extern/mpbt_compose.h.md`, *The zip*.

## The steps

1. The 2 folders are `{root}` and `{build}`, which `read` gives as whole paths.
2. Each of the 2 folders has 2 forms: with `/` between its parts, and with `\` between them.
3. `path_read` reads each file of the deliverable from `{dist}`, in the order of the names. A file that does not read is a fault.
4. The first file that holds a form is a fault, with its message of `docs/extern/mpbt_compose.h.md`, *Messages*.

The message of a file that does not read is in `docs/extern/mpbt_command.h.md`, *Messages*.

Thus no zip holds, for example, a library that names a different library by its path on the machine that built it.

## Functions

| Function | Result |
| --- | --- |
| `pack_scan_files` | 0 when no file holds a form, or 1 after a fault. |
| `get_forms` | The 4 forms of the 2 folders. |
| `has_form` | Whether the bytes of a file hold a form. |
