# src/join/join.h

The files of `join` share this header: the state of a call, the entries of a zip, and the functions.

## join_state_t

| Field | Value |
| --- | --- |
| `command` | The value of `mpbt:Command`. |
| `rows` | The rows of `mpbt:Variable`, `mpbt:Target` and `mpbt:Part`. |
| `fault` | The first fault of the call, or no bytes. The system writes it with `finding_write`. |

## join_entries_t

The entries of the new zip: an `archive_entry_t` for each entry of each zip of a target, with a copy of its bytes.

| Field | Value |
| --- | --- |
| `entries` | The entries, in the order of the targets, and of the entries in each zip. |
| `count` | The count of the entries. |
| `target` | The name of the target whose zip `archive_read` reads now. |

## Functions

| Function | File |
| --- | --- |
| `join_declare` | `join_world.c` |
| `join_read_world` | `join_world.c` |
| `join_write_zip` | `join_zip.c` |
