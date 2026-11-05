# src/style/style_tokens.c

This file answers the questions that the rules ask about the tokens of a source.

## The questions

| Question | Answer |
| --- | --- |
| Is a token this text? | Its bytes are the bytes of the text, and it has no other byte. |
| Do 2 tokens touch? | No byte is between them. |
| How often is a mark in a range, out of the brackets? | The count of the mark at depth 0. Each open bracket of the range adds one depth, and each closing bracket removes one. |
| How often is a mark in a range? | The count of the mark at each depth. |
| Does a range hold a name? | A token of the range is that name. |

A range is a first token and a last token of `tokens`. An answer reads no token out of its range.

## Functions

| Function | Result |
| --- | --- |
| `style_is_text` | `true` if a token holds exactly the bytes of a text. |
| `style_touch` | `true` if no byte is between 2 tokens. |
| `style_count_top` | The count of a mark out of the brackets of a range. |
| `style_count_marks` | The count of a mark in a range. |
| `style_has_word` | `true` if a range holds a name. |
