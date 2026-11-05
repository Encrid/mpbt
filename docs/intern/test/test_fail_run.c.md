# src/test/test_fail_run.c

This file makes the run `fail` of a plain run: a copy of the code with the layer, for the cases that state `fail`.
`docs/extern/mpbt_fail.h.md` gives the behavior. The module `read` already refused each call of a case that is not listed.

## The run fail

`test_needs_fail` tells whether the use of a chosen case states `fail`. With `--break`, the use is that of the false variant.
Then `test_run_fail` does the steps of `test_changed.c` with the run `fail`, and with `write_layers` as its writer:

1. `test_dump_all` dumps each source, and `test_find_used` visits it with the names of the calls.
2. For each source that uses a listed function, `test_write_layer` gives its layer.
3. The new text is the bytes before the byte of the layer, the block, the other bytes, then the end.

A line end comes before the end of the layer.
In a plain run, a case whose use states `fail` runs on the artifacts of this run. Each other case runs on the build of the phase `build`.
The runs `branches` and `leaks` write the layer into their own copies: `test_probes.c` and `test_count.c`.

## Functions

| Function | Result |
| --- | --- |
| `test_needs_fail` | Whether a chosen case needs the run `fail`. |
| `test_run_fail` | The run `fail`, or `false` after a finding. |
| `write_layers` | The text of each source with its layer. |
