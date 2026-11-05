# src/prose/prose_units.c

This file counts the words of each sentence, and the sentences of each unit of a document.

## The limits

| Count | Its limit in `mpbt:ProseCheck` |
| --- | --- |
| The words of a sentence in a step | `step` |
| The words of each other sentence | `sentence` |
| The sentences of a unit | `paragraph` |

`read` writes these limits from `[prose]`: `docs/extern/mpbt_check.h.md`, *[prose]*. The file holds no limit of its own.

## The steps

1. `markdown_next_unit` gives each unit of the document, and `markdown_next_sentence` each sentence of the unit.
2. `markdown_next_word` gives the words of the sentence, and the file counts them.
3. A sentence with more words than its limit gives a finding on the line where it starts.
4. A unit with more sentences than its limit gives a finding on its first line.

The messages are in `docs/extern/mpbt_check.h.md`, *prose*.

## Functions

| Function | Result |
| --- | --- |
| `prose_check_units` | A finding for each sentence and each unit that is too long. |
| `check_sentences` | The findings of the sentences of one unit, and their count. |
