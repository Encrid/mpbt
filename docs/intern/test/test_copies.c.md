# src/test/test_copies.c

This file runs the copies of one case at the same time, on threads, and gives the verdict of the case.
The verdict of a case is in `docs/extern/mpbt_case.h.md`, *Verdicts*.

## The steps

1. The case runs 1 copy if `alone` is `true`, else the copies of the run.
2. Each copy gets a `test_copy_t`: its number, its folder, and the use that `test_get_use` gives.
3. `os_thread_start` starts a thread for each copy, with a stack of 16 MiB, as the main thread of mpbt has.
4. The thread of a copy runs `run_copy`: `test_add_variables`, `test_run_case`, then `test_judge`.
5. `os_thread_join` waits for each thread, in the order of the copies.
6. `choose_verdict` gives the verdict of the case.

A thread of a copy calls no entry of Bridge, and writes no line. The thread of the system writes the lines after the join.
The copies compete for the processors and the memory. Thus a fault that comes only under load can show.

## The folder of a copy

The folder is `<out>/cases/<group>/<index>`. With 2 copies or more, each copy adds `/<copy>`, from 0.
`<out>` is the `{out}` of the run of the copy. A case that states `fail` in a plain run takes the run `fail`.

## The verdict of the case

If each copy passed, the verdict is that of the first copy.
Else it is the verdict of the first copy that failed. With 2 copies or more, the count of the copies that failed follows it, as `docs/extern/mpbt_case.h.md`, *Messages*, writes it.

## Functions

| Function | Result |
| --- | --- |
| `test_run_copies` | The verdict of a case, and its copy for the lines. |
| `run_copy` | Runs one copy, on its thread. |
| `get_folder` | The folder of a copy. |
| `choose_verdict` | The verdict of a case from the verdicts of its copies. |
