# src/commits/commits_git.c

This file finds git, runs it with `run_command`, and gives what git tells: `docs/intern/shared/run/run.c.md`.

## A run of git

`os_path_find` gives the path of the program git. That path is the program of each run.
Each run gets the root as its folder, the errors apart from the output, and no time limit.

| Arguments | Result |
| --- | --- |
| `rev-parse --show-prefix` | Status 0 and one empty line: the root is the top folder of the repository. |
| `rev-parse --verify -q HEAD` | Status 0: the repository has a commit. |
| `log -z --format=%h%n%B <range>` | The commits of the range. Each commit is its short name, a line end and its message, then a zero byte. |

## The errors

The findings are in `docs/extern/mpbt_check.h.md`, *commits*, and in `docs/extern/mpbt_command.h.md`, *Messages*.

1. If `os_path_find` gives no path, the finding tells that this machine has no git.
2. If a run did not start, the finding names the path of git as the program.
3. If `log` gives a status that is not 0, the finding names the range.
4. Its error is the text of the errors of git, with no white space before or after it.
5. A status of `rev-parse` that is not 0 tells that no repository is there.

## Functions

| Function | Result |
| --- | --- |
| `commits_find_git` | The path of git, or a finding. |
| `commits_has_head` | Whether the root is the top of a repository that has a commit. |
| `commits_read_log` | The output of `git log`, or a finding. |
| `run_git` | The result of `run_command` for git and its arguments. |
