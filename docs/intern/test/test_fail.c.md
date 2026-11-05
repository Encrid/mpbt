# src/test/test_fail.c

This file gives the calls that can fail, and writes the layer of a source.
The layer makes a call of a listed function fail at its number: `docs/extern/mpbt_fail.h.md`, *The calls that fail*.

## The calls

`test_get_calls` gives `malloc`, `calloc` and `realloc` with the value `nullptr`, then the `function` and the `value` of each `mpbt:FailCall`.
The module `read` refuses a function that is in the list two times. It counts the 3 functions of C as listed.

## The layer of a source

`test_write_layer` gets the bytes of a source, the listed functions that `test_get_used` gives, and their declarations.
A source that uses no listed function gets no layer. Else the layer has 3 parts:

1. The byte of `test_find_included`, where the block starts.
2. The block: `test_write_rename` for each function with the prefix `c23b_f_`, then `test_write_line`.
3. The end of the source: `test_write_pops`, then `write_state`, then `write_wrapper` for each function.

`write_state` writes these parts:

- `c23b_fget`, which reads the number after a key in the variable `C23_FAIL`, with `getenv`, `strstr` and `atoll`.
- For each function, the count `c23b_fc_<name>`, an `_Atomic long long` with `[[gnu::weak, gnu::visibility("hidden")]]`. Thus the linker keeps one count in a program or in a library.
- For each function, `c23b_fs_<name>`: the number of the call that fails.
- A `[[gnu::constructor]]` that sets each number from the key ` <name>=` of `C23_FAIL`. A function with no key gets 0, and never fails.

`write_wrapper` writes the function of the new name. It adds 1 to the count. At the number, it gives the failed value, and else it calls the function.
A listed function whose result is `void` stops the layer, with its finding of `docs/extern/mpbt_fail.h.md`, *Messages*.
`test_write_signed` can stop the layer too: `test_rename.c`.

## Functions

| Function | Result |
| --- | --- |
| `test_get_calls` | The calls that can fail, with their values, or `false` with no memory. |
| `test_write_layer` | The byte, the block and the end of the layer of a source, or `false` after a finding. |
| `write_state` | The reader of `C23_FAIL`, the counts and the numbers. |
| `write_wrapper` | The function of the new name of one listed function. |
