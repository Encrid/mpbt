# src/text/text_retired.c

This file finds each place of a retired word of `mpbt:Retired` in a file.

## A whole word

The check compares the bytes of the word with the bytes of the file. An upper-case letter of ASCII is the same as its lower-case letter.
A place is a whole word if the byte before it and the byte after it are no part of a word.
A part of a word is a letter, a digit, `_`, or a byte that is not ASCII.
Thus the word `use` is not in `user`, and not in `reuse`.

The finding quotes the word as the file writes it, and the new word if `mpbt:Retired` gives one.

## Functions

| Function | Result |
| --- | --- |
| `text_check_retired` | A finding for each place of a retired word in a file. |
| `is_word_byte` | Whether a byte can be a part of a word. |
