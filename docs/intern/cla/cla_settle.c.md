# src/cla/cla_settle.c

This file acts on the pull request of an event: it decides, records or asks, and then sets the status `cla`.

## The steps

1. `cla_read_event` gives the pull request and the comment, and `cla_get_signatures` gives the record.
2. `cla_has_signer` tells whether the record names the author. Then `cla_decide` decides.
3. With `CLA_ACTION_RECORD`, `cla_record` adds the author to the record.
4. With `CLA_ACTION_ASK`, `ask` writes the question on the pull request: *The question*.
5. `set_status` sends `POST` for the status `cla` of the last commit, with the reason as its description.
6. `say` writes the reason as a line.

The state of the status is `success` when the pull request passes, else `failure`.
The first fault stops the steps, and `cla_settle` gives it to `bridge_cla`.

## The question

`ask` makes the question of `docs/extern/mpbt_command.h.md`, *The agreement*, with the author and `CLA_SENTENCE`.

1. `cla_call` sends `GET` for the comments of the pull request, with `per_page=100`.
2. `cla_find` gives the `body` of each comment to `has_question`, which looks for the question in it.
3. With no comment that holds the question, `cla_call` sends `POST` for a new comment with the question.

Thus the author gets the question one time in a pull request.

## The limits

The API gives at most 100 comments in one answer, and `ask` reads only that first answer.
Thus a pull request with more than 100 comments can get the question a second time.

## Functions

| Function | Result |
| --- | --- |
| `cla_settle` | `true` after the status, or `false` and the fault. |
| `ask` | Writes the question, if no comment holds it. |
| `has_question` | Stops the walk of `cla_find` at a comment that holds the question. |
| `set_status` | Sets the status `cla` of the last commit. |
