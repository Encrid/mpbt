# src/xref/xref_documents.c

This file reads the document of each file `.md` of the project, and finds the file and the document of a path.

## The documents

The items of `files` are in the order of `files_sort`.
`xref_read_documents` reads the document of each item whose path ends with `.md`, into `docs` at the index of the item.
`xref_find_document` finds a path with `files_find`. The index of its item then gives its document.

A path names a file of the project only if `files_find` finds it. The files of `tests` are among them: `docs/extern/mpbt_file.h.md`, *The files of the project*.
Thus a document can cite a file of `tests`, and a heading of a file `.md` of `tests`.

## Functions

| Function | Result |
| --- | --- |
| `xref_read_documents` | `true` after the document of each file `.md`, or `false` with no memory. |
| `xref_find_document` | The item of a path and its document, or none. |
| `xref_free_documents` | Gives the documents back. |
