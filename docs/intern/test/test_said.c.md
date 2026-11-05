# src/test/test_said.c

This file checks the messages of the code after a full run in which each case passed: `docs/extern/mpbt_case.h.md`, *The messages of the code*.

## The steps

1. `path_read` reads `{out}/said.txt`. If the file does not open, a finding tells to run `test` first, and the check stops.
2. `join_docs` joins the bytes of `readme.md` and of each `mpbt:File` in `docs/extern`, with a line end between 2 files.
3. `test_find_messages` gives each message of each file `.c` or `.h` of `src` and `include`, with its line.
4. `test_make_said_pattern` gives the pattern and the own characters of the message. Fewer than 6 skip the message.
5. A pattern that `regex_search` does not find in `said.txt` gives a finding: no case wrote the message.
6. A pattern that it does not find in the joined documents gives a finding: no document quotes it.

Each finding has the path and the line of its message, and its text from `docs/extern/mpbt_case.h.md`, *Messages*.
The writers are the lines of `writers` of `mpbt:Tests`. Each file but `said.txt` comes from the world, and not from the disk.

## Functions

| Function | Result |
| --- | --- |
| `test_check_said` | `true`, or `false` if a call failed with no message. |
| `join_docs` | The text of the documents that can quote a message. |
| `check_file` | Checks each message of one file. |
| `check_message` | Checks one message, and keeps its findings. |
