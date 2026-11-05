# src/test/test_probe_report.c

This file reads the hits after the last case, and reports each outcome of a branch that no case reached, for `test --branches`.
The texts are those of `docs/extern/mpbt_branches.h.md`, *Messages*.

## The steps

1. `note_outcomes` reads each probe of each file, in the order of the paths. Each outcome whose byte is 0 is not reached.
2. `is_excused` looks for an exception of that outcome. A match counts as exempt, and not as a fault.
3. `note_macros` gives a fault for each branch that the writer could not probe.
4. `note_stale` gives a fault for each exception of this system that has no `why`, or that matched nothing.
5. `finding_write` writes each fault, at the path, the line and the column of its outcome or of its exception.
6. `say_format` writes the line of the counts: the outcomes, the reached ones, then the exempt ones if one is exempt.
7. After a fault, a last finding counts the outcomes that no case reached, and the branches with no probe.

A condition has the outcomes false and true, in that order. A function and a label have one outcome.

## An exception

`is_excused` matches an exception of `mpbt:BranchException` if each of these holds:

- its `why` has bytes, and its `line` and `col` are those of the outcome;
- its `side` names the outcome: `MPBT_SIDE_TRUE`, `MPBT_SIDE_FALSE`, `MPBT_SIDE_FUNCTION` or `MPBT_SIDE_CASE`;
- `glob_match` of `src/shared/glob/glob.h` matches the path of the outcome with its `path`, a glob of `docs/extern/mpbt_project.h.md`, *Globs*;
- its `system` is `MPBT_SYSTEM_EVERY`, or it names the system of the target: the variable `{system}` of the run.

An exception counts each outcome that it excuses. An exception of a different system is not a fault on this system.
The exceptions that count with `--part` are in `test_probes.c`.

## Functions

| Function | Result |
| --- | --- |
| `test_report_branches` | `true`, or `false` if the hits cannot be read. |
| `note_outcomes` | The outcomes that no case reached, and their count. |
| `note_macros` | The faults of the branches with no probe. |
| `is_excused` | Whether an exception excuses an outcome. |
| `note_stale` | The faults of the exceptions of the branches. |
