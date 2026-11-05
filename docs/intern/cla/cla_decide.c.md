# src/cla/cla_decide.c

This file decides about the agreement, as the table of `docs/extern/mpbt_command.h.md`, *The agreement*, tells.

## The decision

1. An author that the record names gives `CLA_ACTION_NOTHING`, and the pull request passes.
2. Else, a comment of the author that holds only `CLA_SENTENCE` gives `CLA_ACTION_RECORD`, and the pull request passes.
3. Else, the decision is `CLA_ACTION_ASK`, and the pull request fails.

A comment of a different person does not sign for the author.
`is_sentence` ignores each space, tab and line end before and after the text of the comment.
The reason of each decision is its message of `docs/extern/mpbt_command.h.md`, *Messages*.

## --decide

`cla_write_decision` reads the 2 or 4 values of `decide` in `mpbt:Command` with `lists_get_item`:

1. The first value is the author, and the second value holds the names of the record.
2. `has_name` cuts the second value at each comma, and skips an empty name.
3. The third value is the author of a comment, and the fourth value is its text.
4. With 2 values, the decision has no comment.
5. `say_format` writes the action, the verdict and the reason, as the message of `--decide` tells.

The action is `nothing`, `record` or `ask`, and the verdict is `passes` or `fails`.
`--decide` changes nothing on GitHub, and writes no finding.

## Functions

| Function | Result |
| --- | --- |
| `cla_decide` | The action, the verdict and the reason. |
| `cla_write_decision` | Writes the decision of `--decide`. |
| `has_name` | Whether a list of names with commas holds the author. |
| `is_sentence` | Whether a comment is the sentence, with no other text. |
