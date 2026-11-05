# src/shared/copy/copy.h

This header declares the copy of a file that keeps its execute bit, and that writes the copy only when it differs.
`steps` copies the files of `beside` and does the action `copy` with it. `compose` copies the deliverable, and `take` copies the files of a dependency.

## Functions

| Function | File |
| --- | --- |
| `copy_file` | `copy.c` |
