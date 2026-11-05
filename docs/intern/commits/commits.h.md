# src/commits/commits.h

This private header declares the functions that the files of `src/commits` share.
The module has no type of its own: `run_command` gives each output of git.

## Functions

| Function | File |
| --- | --- |
| `commits_find_git` | `commits_git.c` |
| `commits_has_head` | `commits_git.c` |
| `commits_read_log` | `commits_git.c` |
| `commits_check_log` | `commits_message.c` |
