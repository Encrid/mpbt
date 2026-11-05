# src/xref/xref.h

This private header declares `xref_t`, the files that `xref` knows and their documents, and the functions of `src/xref`.

## xref_t

| Field | Value |
| --- | --- |
| `api`, `check` | The entries of Bridge, and `xref` of `CHECKS_NAMES` for the findings. |
| `files`, `count` | The rows of `mpbt:File`, sorted by `files_sort`, each one a `files_item_t`. |
| `docs` | One `markdown_doc_t` for each item: the document of a file `.md`, and zeros for each other file. |

## Functions

| Function | File |
| --- | --- |
| `xref_read_documents`, `xref_find_document`, `xref_free_documents` | `xref_documents.c` |
| `xref_check_spans`, `xref_read_citation` | `xref_spans.c` |
| `xref_check_references` | `xref_references.c` |
