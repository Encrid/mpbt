# src/commits/commits.c

The module `commits` has its exports in this file. Its system checks the message of each commit of `--commits`, or of the last commit.
The messages are in `docs/extern/mpbt_check.h.md`, *commits*.

## The manifest

`mpbt:commits@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

The descriptors come from `include/mpbt_command.h` and `include/mpbt_finding.h`, and `world_declare` takes the types in the order of the table.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.
The enum and the bitmask come before `mpbt:Command`, as `docs/extern/mpbt_command.h.md`, *The declarations*, tells.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `commits` | `check` | `mpbt:Command`, with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

The changes of `commits` name `mpbt:Finding`.

## The steps

1. `bridge_native_get_single` gives `mpbt:Command`.
2. `commits_find_git` gives the path of git, or the finding of a machine with no git.
3. If the `options` of `mpbt:Command` hold `MPBT_OPTION_COMMITS`, the range is `commits`: one argument of git.
4. Else `commits_has_head` tells whether a git repository with a commit starts at the root.
5. If no such repository is there, the check has no commit, and it passes. Thus a copy of the project that is no repository passes.
6. Else the range is the 2 arguments `-1 HEAD`: the last commit.
7. `commits_read_log` gives the commits of the range, or its finding.
8. `commits_check_log` checks the message of each commit.

The root is `root` of `mpbt:Command`, or `.` when `root` holds no bytes.
Each finding has the check `commits`. `finding_write` and `finding_format` write the findings: `docs/intern/shared/finding/finding.h.md`.
No memory gives the status 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0, or the status of the refusal. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_commits` | 0, also after a finding. |
| `get_root` | The folder in which git runs. |
