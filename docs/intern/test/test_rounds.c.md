# src/test/test_rounds.c

This file runs the chosen cases group by group, one round after the other, and writes the lines of the groups.
The lines are those of `docs/extern/mpbt_case.h.md`, *Messages*.

## The steps of a round

1. With 2 rounds or more, the round starts with its line `round`.
2. For each chosen case, `test_run_copies` runs its copies and gives its verdict. `test_say_case` writes it.
3. After the last case of a group, `test_say_group` writes the count of its cases, and how many passed.
4. In a full run, `add_said` keeps the output of the command and of the helper of each verdict.
5. After the last group, `write_said` writes the outputs into `{out}/said.txt` with `test_write_file`, with a line end between 2 outputs.

`rounds` of `mpbt:Command` gives the number of rounds with `--rounds`. Else the run has 1 round.
`said.txt` comes also after a round in which a case failed. Thus a person can read it.

Before the first round, a `timeout` of 0 in `mpbt:Tests` stops the run, and no case runs. The module `read` writes 0 when `[test]` gives no `timeout`.
The finding is that of a key that mpbt needs: `docs/extern/mpbt_project.h.md`, *Messages*.
Each of the 3 runs comes here before its first case. Thus a run with no case needs no `timeout`.

## A case that failed

After a round in which a case failed, one finding names each case that failed, and the next round does not start.
With `--break`, the finding is the message for the cases that stayed as written. Else it is the message for the cases that were not as written.
In the runs `branches` and `leaks`, a case that fails gives no finding. The probes and the counts change the program, so the verdict only informs.
A copy that keeps a `fault` stops the rounds at once, with that fault as the finding.

## Functions

| Function | Result |
| --- | --- |
| `test_run_rounds` | `true` if each case passed in each round, or `false`. |
| `run_round` | One round of the chosen cases. |
| `note_failed` | The finding that names the cases that failed. |
| `add_said` | Keeps the outputs of one verdict. |
| `write_said` | Writes `said.txt`. |
