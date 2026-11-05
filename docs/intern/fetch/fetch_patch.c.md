# src/fetch/fetch_patch.c

This file applies a patch to the files of the folder `top` of a source: `docs/extern/mpbt_source.h.md`, *fetch*.

## The parts

1. `fetch_patch` reads the patch with `path_read` of `src/shared/path/path.h`, and removes each `\r` before a `\n`. Thus the line ends of Windows give the same patch.
2. Each line that starts with `diff --git ` starts a part. A part changes one file.
3. The line `+++ b/<file>` of a part names its file, below `top`.
4. `apply_part` reads that file with `path_read`, and makes a line of each run of bytes up to a `\n`.

## The hunks

A hunk starts with a line `@@ -<line>,<count> +<line>,<count> @@`. A count that is not there is 1.
`read_hunk` takes the lines of the hunk until the old lines and the new lines reach their counts:

| The line starts with | Old lines | New lines |
| --- | --- | --- |
| A space, or the line is empty | Yes | Yes |
| `-` | Yes | No |
| `+` | No | Yes |
| `\` | No | No |

`apply_part` applies the hunks of a part in their order, with a shift of 0 at the start:

1. `is_at` compares the old lines with the file, from the line of the hunk plus the shift.
2. If one line differs, the patch does not apply, and the run stops.
3. Else the new lines replace the old lines, and the shift grows by the new lines less the old lines.

After the last hunk, `os_file_write` writes the lines again, with a `\n` between 2 lines.
The message is in `docs/extern/mpbt_source.h.md`, *Messages*.
If a file of a part does not read or write, the run stops: `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `fetch_patch` | `true` after each part of a patch, or `false` and a finding. |
| `apply_part` | `true` when each hunk of a part applies, else `false` and the finding. |
| `read_hunk` | The old lines and the new lines of one hunk. |
| `is_at` | Whether the old lines are in the file at a line. |
