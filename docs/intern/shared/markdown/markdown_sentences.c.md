# src/shared/markdown/markdown_sentences.c

This file cuts a unit into sentences, and a sentence into words, for the counts of `prose` and the runs of `dup`.

## Sentences

A sentence starts at the first byte of the unit that is not a space.
It ends after a `.`, a `!` or a `?` that a space or the end of the unit follows. With no such mark, it ends at the end of the unit.
A tab and a line end count as spaces. A code span holds no end of a sentence, because its bytes are code.

## Words

A word is a run of bytes between 2 spaces, or between a space and an end of the sentence.
A space inside a code span does not cut the run. Thus `prose` counts a code span and the bytes that touch it as one word.
A run counts as a word only if it holds a letter, a digit or a code span.

## Functions

| Function | Result |
| --- | --- |
| `markdown_next_sentence` | `true` and the bytes of the next sentence, or `false` at the end of the unit. |
| `markdown_next_word` | `true` and the bytes of the next word, or `false` at the end of the sentence. |
