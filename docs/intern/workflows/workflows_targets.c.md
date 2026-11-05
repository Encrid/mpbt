# src/workflows/workflows_targets.c

This file compares the names that a matrix gives with the targets of mpbt: `docs/extern/mpbt_target.h.md`, *The targets*.

## The rules

1. Each target that no line of the matrix names gets a finding.
2. Each name of the matrix that is not a target gets a finding.

Thus a new target of mpbt needs a line in each matrix.
The texts of the findings are in `docs/extern/mpbt_check.h.md`, *workflows*.

## Functions

| Function | Result |
| --- | --- |
| `workflows_check_targets` | A finding for each target that is not in the matrix, and for each name of the matrix that names no target. |
| `has_name` | Whether a list of names holds a name. |
