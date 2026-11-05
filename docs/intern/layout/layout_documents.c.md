# src/layout/layout_documents.c

This file checks that each file of `include`, `src` and `tools` has its document, and that each document has its file: `docs/contributing/documentation_style.md`, *The documents*.

## The documents

`mirror_get_document` and `mirror_get_file` give the 2 sides of each pair: `docs/intern/shared/mirror/mirror.c.md`, *The sides*.
`files_find` tells whether the path that they give is a file of the project.
A file of `tests` has no document: `docs/extern/mpbt_file.h.md`, *The files of the project*.

## The steps

1. Each file of `include`, `src` and `tools` needs its document among the files of the project.
2. That document starts with the line `# <path>`, where `<path>` names the file.
3. A `\r` before the end of that line is no part of the line.
4. Each file of `docs/extern`, `docs/intern` or `docs/tools` whose name ends with `.md` is a document.
5. Each document needs its file among the files of the project.

The findings are in `docs/extern/mpbt_check.h.md`, *layout*.

## Functions

| Function | Result |
| --- | --- |
| `layout_check_documents` | A finding for each file with no document, for each document with no file, and for each wrong first line. |
| `check_first_line` | A finding if the first line of a document does not name its file. |
