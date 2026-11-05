# src/test/test_changed.c

This file does the steps that the 3 changed runs share: `fail`, `branches` and `leaks`. Each one runs the cases on a changed copy of the code.
What each run writes into the copy is in `test_fail_run.c`, `test_probes.c` and `test_count.c`.

## The steps

1. `test_make_variables` gives the run its own `{out}`: `<build>/<run>/<target>`.
2. The writer of the run gives the new text of each file that it changes.
3. `test_write_copies` writes the copies of `src` and `include` into `<build>/<run>/tree`.
4. `make_copies` makes each artifact again from the copies, and puts its file into `outputs` of the run.
5. `test_check_linked` stops the run if an artifact of the copies is not linked.

## The copies

`test_write_copies` removes the tree with `os_path_remove`, then writes each `mpbt:File` of `src` and of `include` into it.
A file that the run changes gets its new text. Each other file keeps its bytes.
Thus the copy holds the bytes of the phase `read`: the same bytes that zig read for the syntax tree.

## The build of the copies

The run makes each artifact that has `mpbt:Built`, because the module `build` made that set for this command, with `--part` too.
`steps_read_input` gives the input of each one from its row of `mpbt:Artifact`. `steps_make` then makes it, with the `steps_t` of the world and the place of the run.
`steps_free_input` gives the room of the input back after the build of the artifact.
The place has the `{out}` of the run as `out`, and the tree as `tree`: `docs/intern/shared/steps/steps.h.md`, *steps_place_t*.
Then the plan reads each source and each folder of `include` below `src` or `include` from the tree: `docs/intern/shared/steps/steps_plan.c.md`, *The tree*.

`steps_make` gives the values of `mpbt:Built` of each artifact. Its output goes into `outputs`, and `linked` goes to `test_check_linked`.
A fault of the steps stops the run: `finding_write` writes the text of `fault` of the `steps_t`.

## Functions

| Function | Result |
| --- | --- |
| `test_run_changed` | `true` and the run with its artifacts, or `false` after a finding. |
| `test_write_copies` | `true` after the copies, or `false`. |
| `make_copies` | The output and the state of each artifact of the run. |
