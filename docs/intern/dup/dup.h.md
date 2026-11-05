# src/dup/dup.h

This private header declares `dup_t`, the words of one scope of documents, and the functions that `src/dup` shares between its files.

## dup_t

| Field | Value |
| --- | --- |
| `api`, `check` | The `bridge_api_t`, and `dup` from `CHECKS_NAMES`. |
| `documents`, `document_count` | The documents of the scope as `files_item_t`, in the order of `files_sort`. |
| `words`, `word_count` | The words of all the sentences of the scope, in their order. |
| `sentences`, `sentence_count` | The sentences of the scope. |
| `bytes` | A `buffer_t` with the text of each word and of each code span. |
| `runs` | The table of the runs of 8 words: `docs/intern/dup/dup_runs.c.md`, *The table*. |

## dup_word_t

| Field | Value |
| --- | --- |
| `at`, `len` | The word in `bytes`, in lower case, with only letters and digits. |
| `span`, `span_len` | The text of its code span in `bytes`, or no bytes outside a code span. |

## dup_sentence_t

| Field | Value |
| --- | --- |
| `document` | The index of its document in `documents`. |
| `line` | The first line of its unit. |
| `first`, `count` | Its words in `words`. |

## Functions

| Function | File |
| --- | --- |
| `dup_read_words` | `dup_words.c` |
| `dup_add_runs`, `dup_find_run` | `dup_runs.c` |
| `dup_find_passages` | `dup_passages.c` |
