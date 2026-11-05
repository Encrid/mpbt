# src/test/test_count.c

This file runs `test --leaks`. It counts the resources of the code in a copy, and names each case that keeps one.
The behavior is in `docs/extern/mpbt_leaks.h.md`, *test --leaks*.

## The run

1. The cases are chosen and checked first, with `test_pick_cases` and `test_check_patterns`.
2. `test_run_changed` makes the run `leaks`, with `test_write_counts` as its writer.
3. `os_path_remove` empties `{out}/cases`. Thus the file of the lines of each case starts empty.
4. `test_run_rounds` runs each chosen case once. `C23_LEAKS` names the folder of the case, then `.leaks`.
5. `test_report_leaks` reads the file of each case, and writes the report.

The host refuses `--break`, `--copies`, `--rounds` and `--branches` with `--leaks`.
With `--part`, `glob_match` must match a chosen case with the `case` of an exception. Else the exception does not count.

## The writer of the counts

1. `test_list_effects` gives what each counted function does, and the kinds in their order.
2. `find_callbacks` gives each function with a give at `result`, or a take at an argument `<n>`.
3. Each source goes through `test_dump_all`, and `test_find_used` looks for the calls, the counted functions and the callbacks.
4. `write_source` gives each source that uses one of them its layer and its count.

The layer of `test_write_layer` holds the count of `test_write_counted`. Its block comes first, and its end comes last.
Thus the function that counts calls the function of the layer, and a failed call takes nothing.

## Functions

| Function | Result |
| --- | --- |
| `test_run_leaks` | `true`, or `false` after a finding. |
| `test_write_counts` | The new text of each counted source, and the kinds. |
| `find_callbacks` | The names of the callbacks. |
| `write_source` | The new text of one source. |
