# src/shared/zig/zig.h

This header holds the pin of zig: its version, the form of its address, and the archive for each target of a machine.
The values are those of `docs/extern/mpbt_source.h.md`, *zig*. `read` checks the version of `{zig}` with them, and `fetch` gets the archive.

## The constants

| Constant | Type | Value |
| --- | --- | --- |
| `ZIG_VERSION` | `char [7]` | `0.17.0`, with a zero byte after it. |
| `ZIG_ARCHIVE_COUNT` | `size_t` | 6, the count of the rows of `ZIG_ARCHIVES`. |
| `ZIG_ARCHIVES` | `zig_archive_t [ZIG_ARCHIVE_COUNT]` | One row for each target of the table of the header of the sources. |

Each constant is a `constexpr`. A `constexpr` of C23 holds no pointer that is not null, so each text is an array of `char`.
The pin needs no file of code to link: each file that includes the header has it. Thus `read` and `fetch` compare the same version.

## zig_archive_t

| Field | Value |
| --- | --- |
| `target` | The name of the target of the machine, with a zero byte after it. |
| `host` | The text `<host>` of the address, for example `x86_64-linux`. |
| `format` | `zip` or `tar.xz`. |
| `sha256` | The SHA-256 digest of the archive: 64 lower-case hexadecimal characters and a zero byte. |

## Functions

| Function | File |
| --- | --- |
| `zig_find_archive` | `zig.c` |
| `zig_add_address` | `zig.c` |
