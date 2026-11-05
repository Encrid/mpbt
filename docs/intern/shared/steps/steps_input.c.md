# src/shared/steps/steps_input.c

This file makes the input of one artifact from its row of `mpbt:Artifact`. Thus `build` and `test` read the row of an artifact in one way.

## The steps

1. Each text of the row gives a `lists_item_t` that points at its bytes in the shared memory.
2. `lists_get_count` counts the items of each of the 7 lists.
3. One `malloc` takes the room for the items of all the lists.
4. `lists_get_item` gives each item of a list, and `read_list` puts it at its place in that room.
5. `unstamped` comes from the row as it is.

The items point into the shared memory. Thus an input stays good only until the next barrier, as its row does.
`steps_free_input` gives the room back with `free`.

## Functions

| Function | Result |
| --- | --- |
| `steps_read_input` | `true` after it filled the input, or `false` if `malloc` gave no room. |
| `steps_free_input` | Frees the room of the items of an input. |
| `read_list` | Puts the items of one list into the room. |
