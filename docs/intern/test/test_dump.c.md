# src/test/test_dump.c

This file runs the dump of each source, 8 at a time. The visitor of the run gets each tree while zig writes it.
A tree of zig can hold some hundred MB, so no step holds a whole tree: `docs/intern/shared/json/json_next.c.md`, *The window*.

## The steps

1. The run starts as many threads as `os_get_processor_count` gives, from 1 to 8, each with a stack of 16 MiB.
2. Each thread takes the next source under an `os_mutex_t`, until no source is left.
3. `dump_one` starts the command in `{root}` with `os_process_start`, with `errors_apart`, and with the caches of `steps_get_caches` in `env`.
4. `json_open` starts a reader on `fill`, and `test_read_tree` gives each node that it keeps to the visitor.
5. After the end of the tree, `os_process_wait` waits for zig, and `check_errors` reads the errors.
6. The system thread joins the threads, and writes the fault of each source, in the order of the sources.

The reader and the walks of a tree recurse on its depth, so a thread gets the stack of the main thread of mpbt.
The visitor keeps its result in the slot of its source, beside the fault of the source. Thus no 2 threads write the same memory.
`run_command` keeps all the output in memory, so a dump does not use it: `docs/intern/shared/run/run.h.md`.

## fill

`fill` gives the reader the bytes of each read of `OS_OUTPUT`. It adds the bytes of `OS_ERRORS` to the errors, and reads again.
A read that gives 0 ends the document. A read that gives -1 is a fault of the call, and the run gives 1.
Each read waits with `OS_FOREVER`, because zig ends by itself, as the steps of a kind do.

## The errors of zig

zig makes no object with `-fsyntax-only`, so it ends with an error whose line ends with `FileNotFound`. That error does not count.
Each other line of the errors that holds ` error: ` is an error of the source.
Then one finding holds its message of `docs/extern/mpbt_leaks.h.md`, *Messages*, and each such line after it.

A fault of the reader gives the finding about JSON of the same table. The status of zig does not count.
If zig does not start, the finding names `{zig}`, as `docs/extern/mpbt_command.h.md`, *Messages*, writes it.

## Functions

| Function | Result |
| --- | --- |
| `test_dump_all` | The result of the visitor for each source, or `false` after a finding. |
| `dump_thread` | Dumps sources until none is left. |
| `dump_one` | The tree of one source, given to the visitor. |
| `fill` | The next bytes of the output of zig. |
| `check_errors` | `true`, or the fault of the errors of zig. |
