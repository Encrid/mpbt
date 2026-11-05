# src/pseudo/pseudo_block.c

This file checks the lines of one block of pseudo code, with a stack of the blocks that are open.

## The steps

For each line of the block, `check_line` does these steps:

1. A line with a refused token gives its finding, and the check of the line stops there.
2. A line with no token is not checked.
3. The level of the line is the count of the open blocks. A line that ends a block has one level less.
4. The indent is the count of spaces at the start of the line. It must be 3 for each level.
5. In a `TYPE`, each line is `DECLARE` or `ENDTYPE`. In a `CASE`, each line but `ENDCASE` is a clause.
6. A clause after the clause `OTHERWISE` of its `CASE` gives a finding.
7. Each other line is a statement. The statement or the clause takes each token of the line.
8. A line with no form of the profile names its first keyword in lower case, if it holds one.
9. A word that ends a block must end the open block. `NEXT` and its name end a `FOR` of that name.
10. A word that starts a block opens a new block.

At the end of the block of code, each block that is still open gives a finding.
With no open block, a message names the block `none`. The messages are in `docs/extern/mpbt_check.h.md`, *pseudo*.

## The stack

The stack starts with the entry `none`. It takes one more entry for each line of the block, because a line opens one block at most.

## Functions

| Function | Result |
| --- | --- |
| `pseudo_check_block` | A finding for each fault of the lines of a block. |
| `check_line` | The findings of one line. |
| `check_form` | `true` if the line has a form of the profile. |
| `open_block` | Puts a block on the stack. |
| `close_block` | Takes the open block off the stack, or gives the finding of an end that does not match. |
