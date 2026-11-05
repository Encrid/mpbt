# src/test/test_count_report.c

This file adds up the lines that the code of each case wrote, and names each case that keeps a resource, for `test --leaks`.
The texts are those of `docs/extern/mpbt_leaks.h.md`, *Messages*.

## The lines of a case

`add_lines` reads the file of a case with `path_read`. A case that wrote no line has no file, and keeps no resource.
A file that `os_path_entry` finds, and that `path_read` cannot read, gives the finding of `docs/extern/mpbt_command.h.md`, *Messages*.

1. A line is a path, a space, then the counts with a space between 2 counts.
2. A line of a path that the run did not count does not count.
3. The other lines need one integer for each kind, then one integer for `realloc` with a size of 0.
4. A line with a different form stops the report, with its finding.
5. The counts of the lines add up, kind by kind.

## The steps of the report

1. `report_case` takes each kind of a case. A sum above 0 is a kept resource, unless `is_excused` finds an exception for it.
2. A sum below 0 is a resource that the case gave back but did not take.
3. If the last count is not 0, the case called `realloc` with a size of 0.
4. A case with no fault and no excuse gives back what it takes. A case with an excuse and no fault is exempt.
5. `note_stale` checks each exception of the leaks for this system: it needs a `why`, and it must excuse a resource.
6. `finding_format` writes each fault. `say_format` then writes the line of the counts.
7. If a fault came, one more finding gives 2 counts. They are the cases with a kept resource, and the exceptions that are faults.

`is_excused` matches an exception of `mpbt:LeakException` whose `why` has bytes, and whose `kind` is the kind.
`glob_match` of `src/shared/glob/glob.h` must match the case with its `case_name`, as `docs/extern/mpbt_project.h.md`, *Globs*, tells.
Its `system` is `MPBT_SYSTEM_EVERY`, or the system of `{system}`. Each match counts.

## Functions

| Function | Result |
| --- | --- |
| `test_report_leaks` | `true`, or `false` when a line does not fit. |
| `add_lines` | The sums of the counts of one case. |
| `report_case` | The faults and the excuses of one case. |
| `is_excused` | Whether an exception excuses a kept resource. |
| `note_stale` | The faults of the exceptions of the leaks. |
