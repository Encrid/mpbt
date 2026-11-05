# src/cla/cla.h

This private header declares the data of the agreement, and the functions that the files of `src/cla` share.

## The constants

| Constant | Value |
| --- | --- |
| `CLA_SENTENCE` | The sentence that signs: `docs/extern/mpbt_command.h.md`, *The agreement*. |
| `CLA_BRANCH` | `cla-signatures`, the branch of the record. |
| `CLA_FILE` | `signatures.json`, the file of the record on that branch. |

## cla_pull_t

| Field | Value |
| --- | --- |
| `author` | The login of the author of the pull request. |
| `number` | The number of the pull request, as the text of its number of JSON. |
| `tip` | The SHA of the last commit of the pull request. |
| `by`, `said` | The login of the author of the comment, and its text. Both hold no bytes for an event with no comment. |

## cla_record_t

| Field | Value |
| --- | --- |
| `signers`, `count` | The items of the record, in their order. An item holds `name`, `day` and `pull_request`, each as a text. |
| `version` | The SHA of the file of the record, or no bytes when the file is not there. |

## cla_answer_t

| Field | Value |
| --- | --- |
| `code` | The status of HTTP of the answer. |
| `body` | The bytes of the answer. |

## cla_decision_t

| Field | Value |
| --- | --- |
| `action` | A `cla_action_t`, an enum of `uint8_t`: `CLA_ACTION_NOTHING` is 1, `CLA_ACTION_RECORD` is 2, and `CLA_ACTION_ASK` is 3. |
| `passes` | `true` if the pull request passes. |
| `reason` | The reason. It is also the description of the status `cla`. |

Each text of these types is a `buffer_t`.

## The faults

A function of the module that can fail gives `false`, and puts the text of its fault into a `buffer_t` of its caller.
`bridge_cla` writes the text as one finding. Each text is a message of `docs/extern/mpbt_command.h.md`, *Messages*:

| Fault | When |
| --- | --- |
| The fault of the environment | `os_env_get` finds no `GITHUB_EVENT_PATH`, `GITHUB_REPOSITORY` or `GITHUB_TOKEN`. |
| The fault of the event file | `path_read` cannot read the file of the event. |
| The fault of the event | The file is not JSON, or a value that `cla` needs is not in it. |
| The fault of `curl` | `curl` is not on the path, does not start, or ends with a status that is not 0. |
| The fault of an answer | The status of HTTP is an error other than 404, or the body lacks a value that `cla` needs. |

A fault with no text comes from a call with no message of its own, for example a `malloc` with no memory.
Then `bridge_cla` gives 1, and Bridge stops the world: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## Functions

| Function | File |
| --- | --- |
| `cla_decide` | `cla_decide.c` |
| `cla_write_decision` | `cla_decide.c` |
| `cla_settle` | `cla_settle.c` |
| `cla_read_event` | `cla_event.c` |
| `cla_call` | `cla_call.c` |
| `cla_find` | `cla_find.c` |
| `cla_get_text` | `cla_find.c` |
| `cla_get_signatures` | `cla_signatures.c` |
| `cla_has_signer` | `cla_signatures.c` |
| `cla_free_record` | `cla_signatures.c` |
| `cla_record` | `cla_record.c` |
| `cla_base64_encode` | `cla_base64.c` |
| `cla_base64_decode` | `cla_base64.c` |
