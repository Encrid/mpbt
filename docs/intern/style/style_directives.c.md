# src/style/style_directives.c

This file checks the directives of a source: the level of each one for G3, and the guard of a header for H2.
It gives each `#define` to `src/style/style_macros.c`.

## The words of a directive

`c_tokens_start_directive` of `src/shared/c_tokens/c_tokens.h` starts a scan of the directive, and `c_tokens_next_code` gives its name and the words after it.
Thus the rules of the directives need no parse of their own.

## G3

The level starts at 0. Each directive with a name after its `#` gets these steps, in the order of the file:

1. `endif`, `else`, `elif`, `elifdef` and `elifndef` lower the level by 1.
2. 4 spaces for each level come before the `#`, and the `#` touches the name. A level below 0 counts as 0.
3. Else the fault is at the directive, with the level that it needs.
4. `if`, `ifdef`, `ifndef`, `else`, `elif`, `elifdef` and `elifndef` raise the level by 1.

## H2

In a file `.h`, the first directive is `#ifndef` and a name. The second one is `#define` and the same name, with no other token.
One of the first 2 directives can be `#pragma once` instead. Else H2 gives a fault at line 1, and the column 0.

## Functions

| Function | Result |
| --- | --- |
| `style_check_directives` | Checks G3 and H2, and gives each `#define` to `style_check_define`. |
| `check_level` | Checks G3 for one directive. |
| `check_guard` | Checks H2. |
