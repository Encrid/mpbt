# src/runner/runner_machine.c

This file finds the machine of the target of the run in the rows of `mpbt:Variable`, which `world_rows` gives: `docs/extern/mpbt_target.h.md`, *The keys of a target*.

## The steps

1. `find_value` gives the variable `target` of `MPBT_SCOPE_PROJECT`, which names the target of this run.
2. `find_value` gives the variable `runs_on` of `MPBT_SCOPE_TARGET` whose `target` field holds that name.
3. `lists_get_item` gives item 0 of `runs_on` as the system, and item 1 as the processor.
4. A target with no `runs_on`, or with fewer than 2 items in it, has no machine.

The run gives the target with `--target`, or else the target of this machine. The phase `read` puts its name into `target`.

## Functions

| Function | Result |
| --- | --- |
| `runner_get_machine` | `true` and the machine, or `false` and the name of the target. |
| `find_value` | The value of a variable, by its name and the target that it names. |
