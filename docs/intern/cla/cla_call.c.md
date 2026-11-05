# src/cla/cla_call.c

This file sends one request to the API of GitHub for the repository, with the program `curl`.
The token goes into the input of `curl`, and never into its arguments. Thus a list of the processes does not show it.

## The steps

1. `os_env_get` gives `GITHUB_REPOSITORY` and `GITHUB_TOKEN`.
2. `os_path_find` finds `curl` on the path, and `put_config` makes the config of the request.
3. `run_command` runs `curl --silent --show-error --config -` to its end, with the config as its input.
4. `read_answer` takes the last line of the output of `curl` as the status of HTTP.
5. The bytes before that line are the body of the answer.

`curl` reads all of its config before it sends the request. Thus a config that is larger than a pipe does not block the input.

## The config

| Option | Value |
| --- | --- |
| `url` | `https://api.github.com/repos/`, then the repository and the path of the request. |
| `request` | The method: `GET`, `POST` or `PUT`. |
| `header` | `Authorization: Bearer`, a space and the token. |
| `header` | `Accept: application/vnd.github+json` |
| `header` | `X-GitHub-Api-Version: 2022-11-28` |
| `write-out` | A line end, then the status of HTTP. |
| `data-binary` | The body of JSON, for a request that has one. |

`put_quoted` puts each value between quotes, as the config of `curl` needs. Inside them, `\` becomes `\\`, and `"` becomes `\"`.
A line end becomes `\n`, a carriage return becomes `\r`, and a tab becomes `\t`.

## The answer

| Status of HTTP | Result |
| --- | --- |
| 200 to 299 | `true` and the body. |
| 404 | `true` and the code. Thus the caller knows that the thing is not there. |
| Each other status | `false`, and the fault of an answer. The body of the answer is the text of its message. |

## The faults

A variable of step 1 that is not there gives the fault of the environment.
A `curl` that is not on the path, that does not start, or whose status is not 0, gives the fault of `curl`.
The faults are in `docs/intern/cla/cla.h.md`, *The faults*. Each message names the path after the repository.
A `curl` that does not start gets the general message of a program that did not start: `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `cla_call` | `true` and the answer, or `false` and the fault. |
| `put_config` | The lines of the config of one request. |
| `put_quoted` | One value of the config, between quotes. |
| `read_answer` | The status of HTTP and the body, from the output of `curl`. |
