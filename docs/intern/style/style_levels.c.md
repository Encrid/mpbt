# src/style/style_levels.c

This file gives the level and the depth at the walk of a body, and checks where each statement starts: L1 and L2 of `docs/contributing/coding_style.md`.

## The level and the depth

- The level is the `level` of the last block, plus 1 after a `case` of that block, plus `extra`.
- The depth is the count of the open blocks with `control`, plus `extra`.

Each level takes 4 columns. Thus a statement of level 1 starts at column 5.

## The start of a statement

`style_start_line` checks the first token of a statement, of a control, of a `case` or of a `{`:

1. If the token is first on its line, L2 needs the column 4 times its level, plus 1.
2. The fault of L2 gives the indent, which is the column less 1, and the level.
3. Else, if the last statement ended on the line, the token is a fault of L1.

`style_take_case` clears `in_case`, and checks the `case` at the level of its block. Then it sets `in_case`, and skips to the `:`.

## Functions

| Function | Result |
| --- | --- |
| `style_get_level` | The level at the walk. |
| `style_get_depth` | The depth of the branches at the walk. |
| `style_start_line` | Checks where a statement starts, and gives its line. |
| `style_push_block` | Opens a block. `false` if the stack cannot grow. |
| `style_take_case` | Checks a `case` or a `default`, and gives the token after its `:`. |
