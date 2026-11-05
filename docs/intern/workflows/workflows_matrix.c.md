# src/workflows/workflows_matrix.c

This file reads the names of the matrix of a workflow. It reads only the lines that name a target, and no other part of YAML.

## A line of the matrix

A line names a target of the matrix if it has these parts, in this order:

1. Spaces or tabs, or nothing.
2. The text `- target: `, with one space after the colon.
3. A name: one byte or more, with no space, no tab and no line end.
4. Spaces or tabs, or nothing, then the end of the line or of the file.

A `\r` before the line end counts as a space. Each other line names no target.
Thus the line `pull_request_target:` of a workflow names no target.

## Functions

| Function | Result |
| --- | --- |
| `workflows_read_matrix` | The names of the matrix, in the order of their lines. |
| `read_name` | The name of one line, or no name. |
