# src/cla/cla_record.c

This file adds the author of a pull request to the record. The first time, it makes the branch of the record.

## The branch

1. `cla_call` sends `GET` for the reference of `CLA_BRANCH`. A 404 tells that the branch is not there yet.
2. Then `make_branch` reads `default_branch` of the repository, and `object.sha` of the reference of that branch.
3. `make_branch` sends `POST` for a new reference `refs/heads/cla-signatures` at that commit.

An answer with no `default_branch` or no `object.sha` gives the fault of an answer: `docs/intern/cla/cla.h.md`, *The faults*.

## The new record

1. `get_today` gives the day in UTC as `YYYY-MM-DD`, with `time`, `gmtime_r` and `strftime`.
2. The new item holds the author, the day and the number of the pull request, after the old items.
3. `json_write_list_start`, `json_write_object` for each item, and `json_write_list_end` write the list.
4. A line end follows the list. `cla_base64_encode` turns the file into its text.
5. `write_record` sends `PUT` for `CLA_FILE`, with this body:

| Key of the body | Value |
| --- | --- |
| `message` | The message of the commit: `docs/extern/mpbt_command.h.md`, *The agreement*. |
| `branch` | `CLA_BRANCH` |
| `content` | The text of the file, in base64. |
| `sha` | The version of the record. A first record has no `sha`. |

`json_write_object` sorts the keys of each object: `docs/intern/shared/json/json_write.c.md`.
The number of the pull request stays a number of JSON in the record.

## Functions

| Function | Result |
| --- | --- |
| `cla_record` | `true` after the commit of the record, or `false` and the fault. |
| `make_branch` | Makes the branch of the record from the last commit of the default branch. |
| `get_today` | The day in UTC. |
| `write_record` | The text of the record, and the request `PUT`. |
