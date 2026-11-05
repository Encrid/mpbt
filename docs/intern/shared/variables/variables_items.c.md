# src/shared/variables/variables_items.c

This file replaces the variables of each item of a list, for example the command of a step.

## The rule of a whole item

An item that is only `{<name>}` of a list variable, with no separator, gives all the items of that list, each expanded in its turn.
Each other item gives one item: the item, through `variables_expand`.
Thus `["{zig}", "cc", "{flags}"]` gives zig, `cc`, then each flag as its own item.

## Functions

| Function | Result |
| --- | --- |
| `variables_expand_items` | `true` and the items, or `false` and a finding. |
| `is_whole_list` | Whether an item is one list variable. |
