# src/cover/cover_names.c

This file reads the public names of a header, with the tokens of `c_tokens_next_code`.

## The declarations

`cover_read_names` reads the tokens of the file scope with `c_tokens_next_code`. It also ignores each attribute between `[[` and `]]`.
A declaration goes from the end of the last one to its `;`, or to the `{` of its body.

| Declaration | Its public names | Example |
| --- | --- | --- |
| A directive | The names of `cover_read_macro` | `#define SAMPLE_MAX(a, b) ((a) > (b) ? (a) : (b))` |
| A call of a macro of `mpbt:Make` | The name of `cover_read_make` | `SAMPLE_MAKE_DESC(sample_point_t, SAMPLE_POINT_FIELDS);` |
| A prototype, or a function `static inline` | The name before the first `(` | `int sample_add(int a, int b);` |
| A `constexpr` | The last name before the `=` | `constexpr int SAMPLE_SIZE = 4;` |
| An `enum` with a body | Each constant of the body | `enum sample_kind : uint8_t { SAMPLE_ONE = 1 };` |
| A `struct` or a `union` with a body | Its name, and each field of the body | `typedef struct { int x; } sample_point_t;` |

A function needs a name before its own name, and no `=` before its `(`. Thus `int (*f)(void);` is no function.
A declaration with `typedef` and with no body has no public name, for example a pointer to a function.
The name of a layout is the name after its `}`. With no such name, it is the tag after `struct` or `union`.

## The text in braces

`cover_read_inside` reads the tokens between 2 braces, also the tokens of a layout inside a layout:

- A text with a `;` holds fields. Each `;` ends a field, and the field is the name between `(*` and `)`, else the last name before the `;`.
- Each other text holds constants. Each `,` ends a constant, and the constant is the first name of its item.

Thus a bit field and an array give their names, and a number is no name.

## Functions

| Function | Result |
| --- | --- |
| `cover_read_names` | The public names of a header, in `names`. |
| `read_declaration` | The public names of one declaration. |
| `read_layout` | The name and the fields of a layout. |
| `cover_read_inside` | The fields or the constants between 2 braces. |
