# src/dup/dup_runs.c

This file keeps each run of 8 words of a scope, with the places that hold it.

## The table

A sentence of `n` words has `n - 7` runs: one at each of its first `n - 7` words.
The table holds each run one time, and its key is the 8 words of the run.
The hash of a key is FNV-1a of 64 bits, over the 8 words with a space between 2 words. 2 keys with the same hash are compared word for word.
The table doubles its room when it is half full.

## Places

A place of a run is a document and the first line of a unit. A unit that holds a run 2 times gives one place.
Each place also keeps a set of code spans. Each run adds one item to the set: the code span that holds its 8 words, or no span.

## Functions

| Function | Result |
| --- | --- |
| `dup_add_runs` | Adds each run of 8 words of a sentence, with its place. |
| `dup_find_run` | The places of a run, or none. |
| `hash_run` | The hash of 8 words. |
| `grow_table` | The table with twice its room. |
