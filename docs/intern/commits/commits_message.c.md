# src/commits/commits_message.c

This file checks the message of each commit of the output of `git log`, by the rules of `docs/contributing/commits.md`.

## The commits

1. A zero byte ends each commit. A commit with only white space is not a commit.
2. The line ends at the two ends of a commit are no part of it.
3. The short name of the commit goes to its first line end.
4. The message is the rest, without the white space at its start and at its end.

## The rules

1. The message has 1 line: it holds no line end.
2. The line is `<type>(<scope>): <description>`, or `<type>: <description>`.
3. The type holds letters, digits and `_`. The scope holds one byte or more, with no space and no parenthesis.
4. The description starts with a byte that is not a space.
5. The type is one of the types that `docs/contributing/commits.md` gives.
6. The description has at most 20 words. A word is a run of bytes with no white space.

A line of a different form gets no check of its type and of its words.
Each finding names its commit, in the form of `docs/extern/mpbt_check.h.md`, *commits*.

## Functions

| Function | Result |
| --- | --- |
| `commits_check_log` | A finding for each fault of each message of the log. |
| `check_message` | The findings of one message. |
| `read_line` | The type and the description of a line, or no form. |
| `count_words` | How many words a description has. |
