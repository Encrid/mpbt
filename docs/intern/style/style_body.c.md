# src/style/style_body.c

This file walks the tokens of the body of a function, and keeps its blocks in a `style_body_t`.
The rules of the layout are in `docs/contributing/coding_style.md`, *L - The layout in a function*.

## The walk

The walk starts with one block of level 1: the body itself.
At each token, `get_token_kind` gives the kind of the first test that holds. The handler of the kind takes the token, and gives the next token of the walk.

| Kind | Token | Handler |
| --- | --- | --- |
| `STYLE_CLOSE` | `}` | `close_block` |
| `STYLE_OPEN` | `{` | `open_block` |
| `STYLE_LABEL` | A name that is not `case` or `default`, then `:`, on a line where no statement ended. | `skip_label` |
| `STYLE_CASE` | `case` or `default` | `style_take_case` |
| `STYLE_CONTROL` | `if`, `while`, `for`, `switch`, `else` or `do` | `style_check_control` |
| `STYLE_STATEMENT` | Each other token. | `style_check_statement` |

The handlers are an array, in the order of the kinds. Thus the walk has no long chain of `if`.

## The blocks

- `open_block` checks the `{` as the start of a statement, then opens a block one level deeper.
- `skip_label` skips the name and its `:`. A label has no level to check.
- `close_block` closes the last block, but never the body itself.
- The `}` must be first on its line: L4. It must also be at the level of the token that opened its block: L2.
- After the `}` of a `do`, the `while` and its condition belong to the `do`.
- After each other `}`, a token on its line must be `else`: L4.

## Functions

| Function | Result |
| --- | --- |
| `style_walk_body` | Walks the body of a function. |
| `get_token_kind` | The kind of a token. |
| `close_block` | Checks a `}`, closes its block, and gives the next token. |
| `open_block` | Checks a `{`, opens a block, and gives the next token. |
| `skip_label` | The token after a label. |
