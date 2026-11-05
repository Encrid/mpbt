# src/test/test_rename.c

This file writes the texts that give a function of a source a new name. Then the function of that name can wrap each call.

## The block of a new name

For the name `free` and the prefix `c23b_l_`, `test_write_rename` writes this block:

```c
[[maybe_unused]] static typeof(free) c23b_l_free;
#pragma push_macro("free")
#undef free
#define free c23b_l_free
```

The block comes at the byte of `test_find_included`, or after the definition of a callback.
Each later use of the name calls the function of the new name, also a use of the name as a pointer.
After the blocks, `test_write_line` writes `#line` and the number of the next line. Thus each error keeps the line of the source.
At the end of the source, `test_write_pops` writes `#pragma pop_macro` for each name. Thus the name means its function again there.

## The start of the function of a new name

`test_write_signed` writes the start of the function of the new name, and the call of the old function in it, in these steps:

1. It stops on a `variadic` declaration, with its finding of `docs/extern/mpbt_leaks.h.md`, *Messages*.
2. Parameter `n` is `typeof(<spelled type>) a<n>`, from `a0`. A function with no parameter gets `void`.
3. The result is `typeof(((typeof(<name>) *)nullptr)((<type>){}, ...))`, with one empty value for each parameter.
4. The call is `(<name>)(a0, a1, ...)`. The parentheses keep a macro with arguments of the same name out of the call.

The result is the type of a call through a pointer to the function. Thus a builtin that gives `size_t`, such as `fread`, builds too.

## Functions

| Function | Result |
| --- | --- |
| `test_write_rename` | Adds the block of one new name. |
| `test_write_pops` | Adds a `#pragma pop_macro` for each name. |
| `test_write_signed` | Adds the start of the function of a new name, and gives the call, or `false` after the finding. |
| `test_write_line` | Adds a `#line` with the number of the line of a byte. |
