# src/build/build_order.c

This file chooses the artifacts that the system `build` makes in a run, and puts them in the order of `docs/extern/mpbt_compose.h.md`, *[parts]*.

## The artifacts of a run

- The command `test` builds each artifact. The commands `build` and `pack` build only the artifacts with `test` at `false`.
- With `--part`, a run builds only the artifacts of the parts that it needs.
- The parts that a run needs are the parts of `parts` of `mpbt:Command`, and each part that they use, directly or through a different part.

## The order

1. `rank_parts` gives each part a rank, so that a part ranks after each part that it uses.
2. Between 2 parts with no order, the part with the first artifact in the config gets the lower rank.
3. `read` refused a cycle of the uses, so each part gets a rank.
4. The artifacts sort by the rank of their part, then by `order`, their place in the config.
5. In a project with no parts, the artifacts sort by `order` alone.

The build does not use the order of the rows, which Bridge does not keep.
Thus an artifact comes after the artifacts of the parts that its part uses, and can link their archives.

## Functions

| Function | Result |
| --- | --- |
| `build_order` | The chosen artifacts, in their order. |
| `get_needed` | The parts of `--part`, and each part that they use. |
| `is_chosen` | Whether the run builds an artifact. |
| `rank_parts` | The rank of each part. |
| `compare_artifacts` | The order of 2 artifacts, for `qsort`. |
