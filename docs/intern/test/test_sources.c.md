# src/test/test_sources.c

This file gives each file `.c` of `src` that the build of this target compiles, with the command that dumps its syntax tree.

## The sources

1. An artifact counts if its `target` is the target of the run. With `--part`, its `part` must also be in `parts` of `mpbt:Command`.
2. `steps_read_input` reads its row, and `steps_plan` gives its plan in the place of the run, with no tree.
3. Each file of `{sources}` of the plan in `src` whose name ends with `.c` is a source of the dump.
4. A source counts one time, with the plan of the first artifact that compiles it.
5. `os_folder_make` makes the folder of `{work}` of that plan, because the dump writes a file there.

The plan has no tree, because the dump reads the files of the project: the copies are not there yet.
With `--part`, the files of the other parts get no change. They come into the tree as they are, and their artifacts build from them.

## The command

`make_dump` gives the command with `variables_expand_items`, the variables of the plan, and `{source}`:

```text
{zig} cc -target {triple} -mcpu={cpu} {optimize} {float} {errno} {language}
  -Wno-unused-command-line-argument {define} {defines} {include} {flags}
  -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -fsyntax-only -Xclang -ast-dump=json -o {work}.dump {source}
```

`-fsyntax-only` makes no object, so zig ends with an error about the file of `-o`: `test_dump.c`.
`_FORTIFY_SOURCE` is 0, so that a call that the system fortifies, such as `snprintf`, is a call and not a macro.
The variables of a plan are those of the steps of a kind: `docs/extern/mpbt_kind.h.md`, *Steps*.

## Functions

| Function | Result |
| --- | --- |
| `test_find_sources` | The sources and their commands, or `false` after a finding. |
| `make_dump` | The command that dumps one source. |
