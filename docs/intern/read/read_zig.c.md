# src/read/read_zig.c

This file gives `{zig}`, the zig that each command uses: `docs/extern/mpbt_source.h.md`, *zig*.

## The steps

1. `get_beside` makes the path that `fetch` gives zig: the folder `zig` beside the program, then `zig{exe}`.
2. If `is_zig` finds the version of mpbt in that zig, it is `{zig}`.
3. Else `os_path_find` looks for `zig` on the path. If `is_zig` finds the version in it, it is `{zig}`.
4. Else `{zig}` is the path of step 1, where `fetch` puts zig.

The version is `ZIG_VERSION` of `src/shared/zig/zig.h`, so `read` and `fetch` compare one value.
`is_zig` runs `<zig> version` with `run_command` of `src/shared/run/run.h`, with `apart`. It compares the output with no line end to the version.
`{exe}` is the key of `{home}`, because zig runs on this machine. With no `{home}`, it is the key of the target of the run.
A program that does not start is not the zig of mpbt, and neither is a program with a status other than 0.

## The commands that need zig

In a command that builds, step 4 gives a finding in place of a path: `docs/extern/mpbt_source.h.md`, *Messages*.
These commands build: `build`, `pack` and `test`, and each command whose `[[load]]` names an artifact.
The other commands go on with the path of step 4. `fetch` puts zig there, and no other command runs zig.

## Functions

| Function | Result |
| --- | --- |
| `read_zig` | `true` after `{zig}`, or `false` and a finding. |
| `get_beside` | The path of the zig beside the program, with `/`. |
| `is_zig` | Whether a program is the zig of the version of mpbt. |
