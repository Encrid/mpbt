# src/prose/prose_tags.c

This file checks the tag of each block of code of a document.

## The tags

The tag of a block must be one of the 6 tags of `docs/contributing/documentation_style.md`, *Blocks of code*.
A different tag gives a finding on the line of the first fence of the block, with its message of `docs/extern/mpbt_check.h.md`, *prose*.
A block with no tag has an empty tag, and an empty tag is not one of the 6.

## Functions

| Function | Result |
| --- | --- |
| `prose_check_tags` | A finding for each block whose tag is not in the list. |
