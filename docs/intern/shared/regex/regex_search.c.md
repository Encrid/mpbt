# src/shared/regex/regex_search.c

This file finds a program in a text. It goes through the text one time, so its time grows only with the length of the text and of the program.

## The search

The search keeps 2 lists of steps: the steps that wait for the byte at the position, and the steps for the next byte.

1. At each position, the steps of the program start again at step 0. Thus the pattern can start at each position.
2. `add` follows each `SPLIT` and each `JUMP`, and checks `BEGIN`, `END` and `WORD` at the position. A step that is in a list already is not added again.
3. Each `BYTE` or `SET` that matches the byte puts the next step into the list of the next byte.
4. A `MATCH` in a list ends the search: the pattern is in the text.

At the end of the text, no `MATCH` means that the pattern is not in the text.
A step enters a list at most one time for each position. Thus the search costs at most the count of the steps for each byte of the text.
Each matching method that goes back, such as the one of Python, can cost more in some patterns: https://swtch.com/~rsc/regexp/regexp1.html.

## Functions

| Function | Result |
| --- | --- |
| `regex_search` | Whether the pattern is in the text. |
| `add` | Adds a step and the steps that it reaches with no byte. |
| `step_byte` | The steps of the next byte. |
