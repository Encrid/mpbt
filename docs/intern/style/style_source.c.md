# src/style/style_source.c

This file reads one file of C into the `style_source_t` of the run, with the shared tokenizer of `src/shared/c_tokens/c_tokens.h`.

## The steps

1. `c_tokens_next` gives each token of the file in turn, from the scan that `c_tokens_start` starts.
2. `keep_token` puts a comment into `comments`, and a directive into `directives`.
3. It puts each name, number, string, character and mark into `tokens`.
4. Each line end adds the offset of the next line to `lines`. The first line starts at 0.
5. `pair_brackets` gives each bracket of `tokens` the index of its other bracket.

Spaces and line ends go into no list. The rules of the code read `tokens`, so no rule of the code reads a comment or the text of a string.

## The guard of C++

A header can open `extern "C" {` for C++, and close it with `}` after `#ifdef __cplusplus`.
`is_cplusplus` keeps these tokens out of `tokens`, so that the brackets of C++ change no level:

- `extern`, the string `"C"`, then `{`;
- a `}` that is first on the line after a directive that holds `__cplusplus`.

## The brackets

`pair_brackets` keeps a stack of the open brackets `(`, `[` and `{`.
An open bracket that nothing closes gets the last token. A closing bracket with no open bracket gets the first token.
Thus a jump to the other bracket always stays in the file.

## Functions

| Function | Result |
| --- | --- |
| `style_read_source` | `true` and the lists of a file, or `false` with no memory. |
| `keep_token` | Puts one token into its list. |
| `is_cplusplus` | `true` if a token is a part of the guard of C++. |
| `pair_brackets` | `true` and `pairs`, or `false` if the stack cannot grow. |
