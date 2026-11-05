# src/cla/cla_event.c

This file reads the pull request and the comment from the event of GitHub, as data: `docs/extern/mpbt_command.h.md`, *The agreement*.

## The steps

1. `os_env_get` gives `GITHUB_EVENT_PATH`, the file of the event, and `path_read` reads the whole file.
2. An event of a pull request holds `pull_request`, and `read_pull` takes the 3 values of it.
3. An event of a comment holds `issue.number`. `cla_call` sends `GET` for that pull request.
4. Then `read_pull` takes the 3 values of the answer.
5. `read_comment` takes `comment.user.login` and `comment.body`, when the event has a comment.

| Value | In an event of a pull request | In the answer of `GET` |
| --- | --- | --- |
| The author | `pull_request.user.login` | `user.login` |
| The number | `pull_request.number` | `number` |
| The last commit | `pull_request.head.sha` | `head.sha` |

`cla_get_text` gives each value. mpbt only reads these values, and runs nothing that the pull request holds.

## The faults

| Fault | Name |
| --- | --- |
| `GITHUB_EVENT_PATH` is not there. | The fault of the environment. |
| `path_read` cannot read the file. | The fault of the event file. |
| The event lacks a value of the table. | The fault of the event. |
| The answer of `GET` lacks a value of the table. | The fault of an answer. |

The faults are in `docs/intern/cla/cla.h.md`, *The faults*.
The `<reason>` of an event is `no` and the path of the first value that `cla` needs and cannot read, for example `no issue.number`.
An event that is not JSON gives no value, so its reason names the first value too.

## Functions

| Function | Result |
| --- | --- |
| `cla_read_event` | `true` and the pull request, or `false` and the fault. |
| `read_pull` | The author, the number and the last commit of a pull request. |
| `read_comment` | The author and the text of the comment, or no bytes. |
