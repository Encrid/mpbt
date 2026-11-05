# src/test/test_count_write.c

This file gives the text of a source with its count. Each counted function that the source uses gets a new name, and a function of that name counts.

## The text of a source

1. The text ends with one line end.
2. The block of the layer, then the block of each counted name, go at the byte of `test_find_included`.
3. A callback that the source defines gets its block after the line of the end of its definition. Thus each later use counts, also as a pointer.
4. `test_write_line` follows each block.
5. The end of the text gets `test_write_pops` of the counted names, the counts, then `write_wrapped` for each name.
6. The end of the layer, then the writer of `write_writer`, close the text.

The counts are `c23b_l_kept`, an array of `_Atomic long long`. Each kind has a count, and the last count is that of a size of 0 for `realloc`.

## The function that counts

`write_wrapped` writes the start with `test_write_signed` and the prefix `c23b_l_`, after `test_fit_effects`. Then:

1. Each give at an argument, or at the value that an argument points to, goes before the call.
2. The call of the old function follows, and keeps its result.
3. A take, and a give at `result`, read their values after the call.
4. The function gives the result of the call.

`write_move` writes the function of `realloc`: a size of 0 adds 1 to the last count. A null pointer with a result that is not null adds 1 to `memory`.
`write_tested` writes the test of one value: `__builtin_memcmp` of the value with an empty value of its type. A take adds 1 when it is not zero, and a give takes 1 away.
A place `*<n>` reads the value only if the argument `n` is not null.

## The writer

`write_writer` writes a `[[gnu::destructor]]`. At the exit of the program, or at the close of a library, it writes one line for the source.
The line is the path of the source, then the counts with a space before each one, then `\n`. One append writes the whole line, so parallel programs do not mix their lines.
It writes to the file of `C23_LEAKS` with the low-level calls of the system, and writes nothing if the variable is not there.

On macOS, a `[[gnu::constructor]]` opens its own library again with `RTLD_NOLOAD` and `RTLD_NODELETE`, which `dladdr` finds.
Thus the code of a library that `dlclose` closed stays in place for its destructor.
The constructor names `dladdr` and `dlopen` with names of its own, and includes no header for them.

## Functions

| Function | Result |
| --- | --- |
| `test_write_counted` | The text of a source with its count, inside its layer, or `false` after a finding. |
| `write_wrapped` | The function that counts the calls of one function. |
| `write_move` | The function that counts the calls of `realloc`. |
| `write_tested` | The test of one value of an effect. |
| `write_writer` | The destructor that writes the counts, and the constructor of macOS. |
