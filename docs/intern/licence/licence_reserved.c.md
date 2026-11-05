# src/licence/licence_reserved.c

This file finds the first place in a file that says that all rights are reserved.

## The text

The text is the words `all rights` and `reserved`, in upper or lower case, with only white space between them.
The code holds the 2 parts of the text apart. Thus no source of mpbt holds the text itself.

## The files

The check reads each file of the project, but not these files:

- `license`, which holds the text of the licence;
- the files of `third_party`, which keep the notices of their holders;
- the files of `tests`, as `docs/extern/mpbt_file.h.md`, *The files of the project*, tells;
- a file with the byte 0 in its first 4096 bytes, because it is not text.

A file gets one finding at most, with the line of its first place.

## Functions

| Function | Result |
| --- | --- |
| `licence_check_reserved` | A finding for each file that says that all rights are reserved. |
| `find_reserved` | The position of the first place of the text, or none. |
