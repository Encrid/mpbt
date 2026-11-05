# src/layout/layout_names.c

This file checks that each name of each path is in snake case: `docs/contributing/coding_style.md`, *O4 - The names of the files and of the folders*.

## The names

The first part of a name in snake case has one byte or more: lower-case letters, digits and `_`.
Each extension after it is a `.`, then one byte or more: lower-case letters and digits.
`is_snake` reads the bytes of a name one by one, in this order.

A tool needs 5 names that start with a dot: `.github`, `.gitattributes`, `.gitignore`, `.gitkeep` and `.toolchain`. These names are no fault.
The files of `tests` and of `third_party` can have each name, so the check reads none of their paths.

## Functions

| Function | Result |
| --- | --- |
| `layout_check_names` | A finding for each name of a path that is not in snake case. |
| `is_snake` | Whether a name is in snake case. |
| `is_dotted` | Whether a name is one of the 5 names with a dot. |
