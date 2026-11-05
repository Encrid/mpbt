# src/xref/xref_spans.c

This file checks each code span of a document: a citation of a heading of a file, or the path of a file.

## Citations

A citation is a code span, a comma, a space, and a heading between 2 asterisks.
The heading can start on the next line, and it can also hold a line end. Such a line end counts as one space, if no space follows it.
The text of the span must name a file of the project, which `xref_find_document` finds.
That file must have a heading with the text between the asterisks: `markdown_has_heading`.

## Paths

Each other code span is a path if its text has this form:

1. Folders and the name of a file, with a `/` after each folder.
2. Each folder and the name hold only letters, digits, `_`, `.` and `-`.
3. The name holds a `.` that a byte follows, for its extension.
4. The first folder is a folder of the layout: `.github`, `.toolchain`, `docs`, `include`, `src`, `tests`, `third_party` or `tools`.

Thus `xref` does not check a folder, a path in `build`, a name with no folder, or a pattern with `*` or `<`.
A path must name a file of the project, which `files_find` finds.

## Functions

| Function | Result |
| --- | --- |
| `xref_check_spans` | A finding for each citation and each path of a document that names nothing. |
| `xref_read_citation` | The heading of the citation at a code span, or none. |
| `check_path` | A finding if the text of a span is a path that names no file. |
| `is_path` | `true` if a text has the form of a path. |
