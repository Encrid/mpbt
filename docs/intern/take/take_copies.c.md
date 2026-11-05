# src/take/take_copies.c

This file checks each file of each list, and then writes the copies: `docs/extern/mpbt_dependency.h.md`, *[[dependency]]*.

## The checks

`take_check_copies` gives each pair of `files` of each dependency that `take` took to `check_file`:

1. If `path_read` reads the copy `<into>/<file>`, and its digest is the digest of the list, the next file follows.
2. A file `<from>/<file>` that `path_read` does not read stops the run.
3. A file whose digest is not the digest of the list stops the run.
4. Else the file and its copy go into `copies` of `take_t`.

`get_digest` makes the digest of the bytes in 4 calls: `sha256_start`, `sha256_add`, `sha256_end` and `sha256_get_hex`.
The messages are in `docs/extern/mpbt_dependency.h.md`, *Messages*.

## The copies

`take_write_copies` runs only after each check of each dependency passed. Thus a file that a list refuses changes no file.
`copy_file` of `src/shared/copy/copy.h` writes each copy, with the execute bit of its file, and makes the folder of the copy.
If `copy_file` gives -1, the run stops with a finding for the copy: `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `take_check_copies` | `true` and the copies to write, or `false` and a finding. |
| `take_write_copies` | `true` after each copy, or `false` and a finding. |
| `check_file` | `true` for a file that its list allows, or `false` and the finding. |
| `get_digest` | The SHA-256 digest of bytes, as 64 hexadecimal characters. |
