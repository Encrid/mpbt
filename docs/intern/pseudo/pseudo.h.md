# src/pseudo/pseudo.h

This private header declares the types of the check `pseudo` and the functions of `src/pseudo`.

## pseudo_t

| Field | Value |
| --- | --- |
| `api` | The table of BB-Native for the calls of Bridge. |
| `check` | `pseudo`, as `CHECKS_NAMES` gives it. |
| `path` | The path of the file that holds the blocks. |

## pseudo_token_t

| Field | Value |
| --- | --- |
| `at`, `len` | The bytes of one token of a line. |

## pseudo_line_t

| Field | Value |
| --- | --- |
| `tokens`, `count` | The tokens of the line. |
| `at` | The index of the next token that the parser reads. |

Each function that reads a form of the profile gets a `pseudo_line_t`.
If the next tokens have the form, it moves `at` past them and gives `true`. Else it gives `false`.

## pseudo_open_t

| Field | Value |
| --- | --- |
| `word` | The word that opened the block, or `none` at the base of the stack. After the clause `OTHERWISE`, it is `OTHERWISE`. |
| `name` | For a `FOR`: the token of its variable. |
| `line` | The line of the document where the block starts. |

## pseudo_word_t

| Field | Value |
| --- | --- |
| `text` | The word. |
| `kinds` | Its kinds: *The kinds of a word*. |
| `ends` | For a word that starts a block: the words that end the block. |
| `form` | For a refused word: the form that its message names. |

## The kinds of a word

`kinds` holds a bit for each kind of the word.

| Constant | The word |
| --- | --- |
| `PSEUDO_TYPE` | Is a type of the profile. |
| `PSEUDO_OPERATOR` | Is an operator of 2 operands. |
| `PSEUDO_START` | Starts a block. |
| `PSEUDO_END` | Ends a block. |
| `PSEUDO_ALONE` | Makes a line by itself. |
| `PSEUDO_REFUSED` | Is a text that the profile refuses. |

## Functions

| Function | File |
| --- | --- |
| `pseudo_read_tokens`, `pseudo_get_token`, `pseudo_read_token`, `pseudo_read_name`, `pseudo_is_literal` | `pseudo_tokens.c` |
| `pseudo_get_word`, `pseudo_find_refused` | `pseudo_words.c` |
| `pseudo_read_expression`, `pseudo_read_list`, `pseudo_read_fields` | `pseudo_expression.c` |
| `pseudo_read_type`, `pseudo_read_parameter` | `pseudo_type.c` |
| `pseudo_read_statement`, `pseudo_read_clause` | `pseudo_statement.c` |
| `pseudo_check_block` | `pseudo_block.c` |
