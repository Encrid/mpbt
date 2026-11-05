# src/cover/cover_macros.c

This file gives the public names that a macro has, and the name that a call of a macro of `mpbt:Make` makes.

## The macros

`cover_read_macro` reads a directive through the scan of `c_tokens_start_directive`:

1. A directive that is not `define` has no public name.
2. A name with a `(` just after it is a macro with arguments. Its name is public.
3. A name with a text in braces after it is a macro of a text. Its name is public.
4. Each name that `cover_read_inside` reads between the braces of that text is public too.
5. Each other macro has no public name, for example the guard of a header.

`docs/contributing/coding_style.md`, *H3 - The macros*, tells what the text of a macro is.

## The calls

`mpbt:Make` holds the macros of `[check.makes]`: `docs/extern/mpbt_check.h.md`, *[check]*.
A declaration that starts with the name of such a macro, then `(` and a name, gives a public name.
The public name is that first argument, then the `suffix` of the macro.
`cover` reads no call of a macro that `mpbt:Make` does not hold.

## Functions

| Function | Result |
| --- | --- |
| `cover_read_macro` | The public names of a directive `#define`. |
| `cover_read_make` | The public name that a call of a macro of `mpbt:Make` makes. |
