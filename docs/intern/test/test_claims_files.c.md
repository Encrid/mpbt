# src/test/test_claims_files.c

This file tells whether the claims `output` and `files` hold. Each one reads a file from the disk after the end of the command.

## The claims

| Claim | It holds if |
| --- | --- |
| `output` | The file of `output`, from the root, is there, and its bytes are the bytes of the output. |
| `files` | For each path, the file is there, and its bytes hold the text of the path. |

The paths and the texts are those of the copy. `path_join` gives the place of each path on the disk, as `test_place.c` does.
`path_read` reads each file. A file that does not open makes the claim false, as a file that is not there does.
The bytes of a file count with no `\r`, as the output does. Thus a file that git gives with `\r\n` on Windows still matches.

## Functions

| Function | Result |
| --- | --- |
| `test_hold_output` | Whether the output is the text of its file. |
| `test_hold_files` | Whether each file holds its text. |
