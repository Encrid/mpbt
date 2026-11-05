# src/shared/archive/archive_tar.c

This file reads a tar in memory, in the form ustar of POSIX, with the records of pax and the long names of GNU.

## The blocks

A tar is blocks of 512 bytes. Each entry has a block of header, then the blocks of its bytes. Two blocks of zeros end the tar.

| Field of the header | Bytes | Value |
| --- | --- | --- |
| name | 0 to 99 | The name, after the prefix of bytes 345 to 499 and a `/`. |
| mode | 100 to 107 | The mode, in octal. |
| size | 124 to 135 | The count of the bytes, in octal. |
| checksum | 148 to 155 | The sum of the bytes of the header, with the checksum as spaces. |
| type | 156 | `0` a file, `5` a folder, `2` a link, `1` a hard link. |
| link | 157 to 256 | The path that a link names. |

`x` is a record of pax for the next entry: its `path` and `linkpath` replace the name and the link. `g` is a record for each entry, and the reader skips it.
`L` holds the long name of the next entry, as GNU writes it.
A wrong checksum, or a size past the end of the bytes, stops the read with a finding.

## Functions

| Function | Result |
| --- | --- |
| `read_tar` | Each entry of a tar, or a finding. |
| `read_octal` | The number of a field in octal. |
| `read_pax` | The path and the link of a record of pax. |
| `is_checked` | Whether the checksum of a header is right. |
