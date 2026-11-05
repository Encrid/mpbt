# src/style/style.h

This private header declares what the files of `src/style` share: the slots, the state of a run, and the functions.
The rules are in `docs/contributing/coding_style.md`, and their messages in `docs/extern/mpbt_check.h.md`, *style*.

## The constants

| Constant | Value |
| --- | --- |
| `STYLE_SLOT_FILE`, `STYLE_SLOT_EXCEPTION`, `STYLE_SLOT_PROJECT`, `STYLE_SLOT_LIMITS`, `STYLE_SLOT_FINDING` | 0, 1, 2, 3 and 4. |
| `STYLE_NONE` | `UINT32_MAX`: no token, no function or no count. |

`world_declare` numbers the types of a module from 0, in the order of their names. Thus each slot is the place of its type in `init`.

## style_run_t

The state of one run of the system. It is on the stack of the system, so the module keeps nothing between 2 runs.

| Field | Value |
| --- | --- |
| `api` | The table of BB-Native. |
| `place` | The `finding_t` of the run: the slot of `mpbt:Finding`, the check `style`, and the path of the file under check. |
| `limits` | The `mpbt_style_check_t` of `mpbt:StyleCheck`: `columns`, `lines`, `functions`, `arguments`, `branches` and `depth`. |
| `notice` | The bytes of `.toolchain/header.txt`, from `mpbt:Project`. |
| `exceptions` | Each `style_exception_t` of the run. |
| `names` | The names of the headers, in order, for G5: `src/style/style_names.c`. |
| `source` | The `style_source_t` of the file under check. |
| `functions` | The `style_function_t` of each function of that file. |
| `statements` | The first token and the last token of each statement of its file scope. |
| `failed` | `true` after a buffer could not grow. |

Each list is a `buffer_t` of its items. A new file clears the lists of the last file, and keeps their memory.
The limits are the keys of `[style]`, or their defaults: `docs/extern/mpbt_check.h.md`, *[style]*.

## style_source_t

| Field | Value |
| --- | --- |
| `path` | The `bridge_text_t` of the path of the `mpbt:File`. |
| `text`, `len` | The bytes of the file, in the shared memory. |
| `header` | `true` for a file `.h`. |
| `tokens` | The names, numbers, strings, characters and marks of the file, each a `c_token_t`. |
| `pairs` | The other bracket of each bracket of `tokens`, by its index. `STYLE_NONE` for each other token. |
| `comments` | The comments, each a `c_token_t`. |
| `directives` | The directives, each a `c_token_t`. |
| `lines` | The offset of the first byte of each line. |

## style_function_t

A function that the file defines. Each field but `macro` is an index of `tokens`.

| Field | Value |
| --- | --- |
| `first` | The first token of the definition. |
| `name` | The name, or for a function that a macro makes, the one token in the parentheses of the macro. |
| `open`, `close` | The parentheses of the parameters. |
| `body`, `end` | The brackets of the body. |
| `macro` | `true` if a macro makes the function, for example `BRIDGE_NATIVE(init)`. |

## style_exception_t

| Field | Value |
| --- | --- |
| `rule`, `path`, `why` | The texts of one `mpbt:StyleException`. |
| `glob` | The bytes of `path` before its first `:`: the glob of the file, for `glob_match`. |
| `function` | The bytes of `path` after its first `:`, or no bytes. |
| `count` | The count of the faults that the exception excused. |

## style_fault_t

| Field | Value |
| --- | --- |
| `line`, `column` | The place of the fault. The column is 0 for a fault with no token. |
| `function` | The token of the name of the function of the fault, or `STYLE_NONE`. |

## style_body_t

The state of the walk of one body, for the files `style_body.c`, `style_levels.c`, `style_control.c` and `style_statement.c`.

| Field | Value |
| --- | --- |
| `function` | The function of the body. |
| `blocks` | The open blocks, a stack of `style_block_t`. |
| `extra` | The levels of the controls with no brackets whose statement is still to come. |
| `chains` | For each level, the count of the branches of its last `if`. |
| `declared` | The line of the `;` of the last declaration at the start of the body, or 0. |
| `coded` | `true` after the first statement that is not a declaration. |
| `ended` | The line of the `;` of the last statement, or 0 after a bracket or a control. |

## style_block_t

| Field | Value |
| --- | --- |
| `level` | The level of the statements of the block. |
| `opened` | The level of the token that opened the block. Its closing bracket takes this level. |
| `in_case` | `true` after a `case` or a `default` of the block. The statements after it take one level more. |
| `control` | `true` if the block is the body of a control. It then counts in the depth of C1. |
| `is_do` | `true` if the block is the body of a `do`. |

## The kinds

`style_statement_kind_t` is an enum of `uint32_t`: the kinds of a statement of the file scope, as `style_outside.c` gives them.

| Constant | The statement |
| --- | --- |
| `STYLE_TYPEDEF` | Starts with `typedef`. |
| `STYLE_TYPE` | Declares a `struct`, an `enum` or a `union` with its members. |
| `STYLE_PROTOTYPE` | Declares a function. |
| `STYLE_VARIABLE` | Declares a variable. |
| `STYLE_OTHER` | Each other statement. |

`style_token_kind_t` is an enum of `uint32_t`: the kinds of a token of a body, as `style_body.c` gives them.
Its constants are `STYLE_CLOSE`, `STYLE_OPEN`, `STYLE_LABEL`, `STYLE_CASE`, `STYLE_CONTROL` and `STYLE_STATEMENT`, from 0, since they are the indexes of an array of handlers.

## Functions

| Function | File |
| --- | --- |
| `style_check_file`, `style_has_suffix` | `style_file.c` |
| `style_read_source` | `style_source.c` |
| `style_find_scope` | `style_scope.c` |
| `style_is_text`, `style_touch`, `style_count_top`, `style_count_marks`, `style_has_word` | `style_tokens.c` |
| `style_is_keyword`, `style_is_type_word`, `style_is_qualifier`, `style_is_snake`, `style_is_upper` | `style_words.c` |
| `style_check_lines`, `style_is_empty_line` | `style_lines.c` |
| `style_check_spaces` | `style_spaces.c` |
| `style_check_operators` | `style_operators.c` |
| `style_check_directives` | `style_directives.c` |
| `style_check_define` | `style_macros.c` |
| `style_check_outside` | `style_outside.c` |
| `style_get_declared`, `style_is_constant` | `style_declaration.c` |
| `style_check_parameters`, `style_check_pointers`, `style_check_prototypes` | `style_parameters.c` |
| `style_read_names`, `style_is_declared` | `style_names.c` |
| `style_check_function` | `style_function.c` |
| `style_walk_body` | `style_body.c` |
| `style_get_level`, `style_get_depth`, `style_start_line`, `style_push_block`, `style_take_case` | `style_levels.c` |
| `style_check_control` | `style_control.c` |
| `style_check_statement` | `style_statement.c` |
| `style_read_exceptions`, `style_is_excused`, `style_end_exceptions` | `style_exceptions.c` |
| `style_add_fault` | `style_fault.c` |
