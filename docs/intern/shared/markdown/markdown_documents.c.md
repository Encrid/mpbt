# src/shared/markdown/markdown_documents.c

This file tells which files are the documents that `prose`, `pseudo` and `dup` read.

## The documents

The documents are those of `docs/contributing/documentation_style.md`, *The documents*:

| Path | Documents |
| --- | --- |
| `readme.md` | The readme. |
| `docs/<path>.md` | Each file `.md` of `docs`, in each of its folders. |
| `.toolchain/docs/<path>.md` | Each file `.md` of `.toolchain/docs`, in each of its folders. |

`cla.md` and `license` are legal texts. Thus these checks do not read them.
A file `.md` of `tests` is no document, because it is data of a case.

## Functions

| Function | Result |
| --- | --- |
| `markdown_is_document` | `true` if the path is a document. |
