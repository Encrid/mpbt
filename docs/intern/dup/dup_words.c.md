# src/dup/dup_words.c

This file reads the sentences of one document, and gives the words that `dup` compares.

## The words of a sentence

1. `markdown_next_unit`, `markdown_next_sentence` and `markdown_next_word` give each word of each sentence.
2. A code span whose text ends with `.md` is a citation, and gives no word.
3. The heading between asterisks after a citation gives no word either.
4. Each other code span gives each piece of its text between spaces and `|`, as a word of that span.
5. The bytes of a word before, between and after its code spans make words of their own.
6. A word keeps only its letters and digits, in lower case. A word that keeps nothing is dropped.

A citation points to a fact, and does not state it. Thus 2 documents can cite the same heading.
A passage stays inside one sentence. Thus 2 sentences that follow each other never make one passage.
A block of code holds no sentence, so a block of examples or of quotes holds no passage.

## Functions

| Function | Result |
| --- | --- |
| `dup_read_words` | Adds the sentences and the words of a document to the scope. |
| `add_span` | Adds the words of one code span. |
| `add_word` | Adds one word, in lower case, with only its letters and digits. |
| `skip_citation` | Moves past a citation and its heading. |
