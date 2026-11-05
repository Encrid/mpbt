# src/shared/mirror/mirror.c

This file turns the path of a file into the path of its document, and back: `docs/contributing/documentation_style.md`, *The documents*.
It reads no file. It works on the bytes of the paths only.

## The sides

| First folder of a file | First folders of its document |
| --- | --- |
| `include/` | `docs/extern/` |
| `src/` | `docs/intern/` |
| `tools/` | `docs/tools/` |

The document keeps the rest of the path of its file, and adds `.md` after it.
For example, the document of `src/host/main.c` is `docs/intern/host/main.c.md`.

## The paths with no match

- A file of a different first folder has no document, for example `readme.md`.
- A file whose last name is `.gitkeep` has no document. Thus no document has a `.gitkeep` as its file.
- A path of `docs/extern`, `docs/intern` or `docs/tools` that does not end with `.md` is no document.

The parts of `mirror_t` point into the path of the caller, and into constant texts. Thus a call takes no memory, and it cannot fail.

## Functions

| Function | Result |
| --- | --- |
| `mirror_get_document` | The 3 parts, or `false`. |
| `mirror_get_file` | The 3 parts, or `false`. |
