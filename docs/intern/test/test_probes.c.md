# src/test/test_probes.c

This file runs `test --branches`. It writes the probes into a copy of the code, and reports each branch that no case reached.
The behavior is in `docs/extern/mpbt_branches.h.md`, *test --branches*.

## The run

1. As a plain run does, `test_pick_cases` and `test_check_patterns` come first.
2. `test_run_changed` makes the run `branches`, with `test_write_probes` as its writer.
3. `test_write_hits` writes `{out}/hits.bin`, with a byte 0 for each outcome. The variable `C23_BRANCHES` names it.
4. Through `test_run_rounds`, each chosen case runs one time, in a single copy.
5. `test_report_branches` reads the hits, and writes the report.

The host refuses `--break`, `--copies` and `--rounds` with `--branches`: `docs/intern/host/host_arguments.c.md`.
With `--part`, an exception counts only if `glob_match` matches its `path` with a file that has probes.

## The writer of the probes

1. `test_dump_all` gives each kept node to `visit`. It runs `test_walk_probes`, and `test_find_used` with the names of the calls.
2. `merge_edits` puts the probes of each tree into the probes of their file, by their key. A header gets the probes of each tree that includes it.
3. `test_write_layer` gives each source `.c` its layer. Thus a case with `fail` reaches the branch of the failed call.
4. A source `.c` gets the prefix `c23b_`. The header at place `n` in the order of the paths gets `c23b_h<n>_`.
5. `test_get_parts` gives the part of each file in the hits, and `test_write_probed` gives its new text.

The writer also keeps each branch that cannot get a probe, with its line and its column, for the report.

## Functions

| Function | Result |
| --- | --- |
| `test_run_branches` | `true`, or `false` after a finding. |
| `test_write_probes` | The new text of each file with probes, the rows of its probes, and the branches with no probe. |
| `merge_edits` | The probes of one tree, added to those of their files. |
| `visit` | The probes and the uses of one node at the top. |
