# src/style/style_words.c

This file puts a name of C into the classes that the rules use.

## The classes

| Class | Names |
| --- | --- |
| Keyword | `if`, `while`, `for`, `switch`, `else`, `do`, `return`, `sizeof`, `case`, `default`, `goto`, `break`, `continue`, `alignof`, `static_assert` and `typeof`. |
| Word of a type | `void`, `char`, `short`, `int`, `long`, `float`, `double`, `bool`, `auto`, `size_t`, `ptrdiff_t`, `signed` and `unsigned`. A name that ends with `_t` is one too, and so is the name after `struct`, `enum` or `union`. |
| Qualifier | `static`, `const`, `constexpr`, `volatile`, `register`, `thread_local`, `extern` and `inline`. |
| Snake case | A lower-case letter or `_` first, then only lower-case letters, digits and `_`. |
| Upper case | An upper-case letter or `_` first, then only upper-case letters, digits and `_`. |

`style_is_type_word` gets the index of the token, because the token before a name can make it a word of a type.
The other functions get the bytes of the name.

## Functions

| Function | Result |
| --- | --- |
| `style_is_keyword` | `true` for a keyword. |
| `style_is_type_word` | `true` for a word of a type. |
| `style_is_qualifier` | `true` for a qualifier. |
| `style_is_snake` | `true` for a name in snake case. |
| `style_is_upper` | `true` for a name in upper case. |
