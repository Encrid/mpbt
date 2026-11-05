# src/test/test_timer.c

This file is the timer of one command: a thread that kills the command when its time ends, as `timeout` of `docs/extern/mpbt_case.h.md`, *[test]*, asks.
The reads and the waits of a command stop at the deadline by themselves. Only a write of mosl can wait with no limit, while the pipe of the input is full.

## The steps

1. `test_timer_start` makes an `os_event_t`, and starts the thread `watch`, with a stack of 64 KiB.
2. `watch` waits for the event with `os_event_wait`, for the time of `timeout`.
3. If the time passes first, `watch` sets `late`, and kills the command with `os_process_kill`.
4. `test_timer_stop` sets the event, joins the thread, and frees the event.

A kill closes the pipes of the command. Thus a write that waits gives -1, and the copy goes on to the end of the command.

## The rule of the threads

The timer can kill the command while the thread of the copy reads its output or writes its input.
The next version of mosl states this rule: `os_process_kill` can come from a second thread while a read or a write of the process waits.
Its document of the processes then holds the rule: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-processes.
The thread of the copy stops the timer before `os_process_wait`. Thus no kill comes after the wait, when the system can give the number of the process to a new one.

## Functions

| Function | Result |
| --- | --- |
| `test_timer_start` | `true` and the timer that runs, or `false`. |
| `test_timer_stop` | Whether the timer killed the command. |
| `watch` | The thread of the timer. |
