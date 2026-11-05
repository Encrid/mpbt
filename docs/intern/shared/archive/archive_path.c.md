# src/shared/archive/archive_path.c

This file decides the form of an archive, and refuses a path that leaves the folder of the archive.

## The form

| End of the name | Form |
| --- | --- |
| `.zip` | A zip. |
| `.tar` | A tar. |
| `.tar.gz` | A tar inside gzip. |
| `.tar.xz` | A tar inside xz. |

Each other name has no form, and `fetch` stops with a finding.

## A path inside the folder

`archive_is_inside` cuts a path at each `/` and each `\`. It refuses the path in each of these cases:

- it is empty, or it starts with `/` or `\`;
- it starts with a letter and `:`, as a drive of Windows does;
- one of its parts is `..`.

The target of a link goes through the same test, after the folder of the link.
The message is in `docs/extern/mpbt_source.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `archive_get_form` | The form of an archive, or none. |
| `archive_is_inside` | Whether a path stays inside. |
