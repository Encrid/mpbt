# src/report/report_sort.c

This file puts the findings in the order of `docs/extern/mpbt_finding.h.md`, *The report*.

## The keys

`qsort` sorts the rows with `compare_rows`, which compares these keys in turn:

1. `path`, byte by byte. A path that starts a longer path comes first.
2. `line`, then `column`, as numbers.
3. `rank`: the place of `check` in `CHECKS_NAMES` of `src/shared/checks/checks.h`. Each other name gets `CHECKS_COUNT`.
4. `index`, so that 2 findings with the same keys keep the order of the walk.

`qsort` does not keep the order of equal rows. The last key makes each row different, so 2 runs give one order.

## The order of the phases

A run of `report` sees the findings of one phase: `docs/intern/report/report.c.md`, *One time for each finding*.
Thus the order of the phases needs no key. The rank only orders 2 findings at one place, for example 2 checks on one line.
A name of a different phase, or of a module of a project, comes after the 12 checks.

## Functions

| Function | Result |
| --- | --- |
| `report_sort` | The rows, in the order of the report. |
| `compare_rows` | Below 0, 0 or above 0, as `qsort` needs. |
| `get_rank` | The place of a name in `CHECKS_NAMES`, or `CHECKS_COUNT`. |
