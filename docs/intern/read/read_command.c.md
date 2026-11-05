# src/read/read_command.c

This file writes `mpbt:Command` from the settings of `read`: `docs/extern/mpbt_command.h.md`, *mpbt:Command*.

## The steps

1. Each text, `copies`, `rounds`, `options` and `name` goes into the field with the same name, as it is.
2. `put_parts` makes an item of each line of `parts`.
3. A tag with a part, `<part>-v<major>.<minor>.<patch>`, adds `<part>` as the last item of `parts`.
4. `put_sets` makes 2 items of each line of `sets`: the text before the first `=`, and the text after it.
5. Each line of `decide` becomes an item of `decide`.
6. `attach` gives `mpbt:Command` its value, with the id 0.

A line with no `=` gives the whole line as the name, and a value with no bytes.
`src/host/host_arguments.c` refused each wrong command line before the world was there. Thus this file writes no finding.

## Functions

| Function | Result |
| --- | --- |
| `read_command` | `true` after the attach of `mpbt:Command`, or `false` with no memory. |
| `put_parts` | The list of the parts of `--part` and of `--tag`. |
| `put_sets` | The map of `--set`: each name, then its value. |
