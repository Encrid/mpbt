# src/shared/variables/variables.h

This header declares the variables of one target, and the functions that replace them in a text or in a list.
The rules are those of `docs/extern/mpbt/project.h.md`, *Variables*.

## variables_t

A module makes a `variables_t` from the entities of `mpbt:Variable`.
It takes each variable of the project, and each variable of the target of its work.

| Field | Value |
| --- | --- |
| `entries` | The variables, in the order of their names. |
| `count` | The count of the entries. |

An entry holds a name, a kind and a value: a text, or the items of a list.

## Functions

| Function | Result |
| --- | --- |
| `variables_sort` | Sorts the entries by name. |
| `variables_find` | Gives the entry of a name. |
| `variables_expand` | Gives a text with its variables replaced. |
| `variables_expand_items` | Gives the items of a list with their variables replaced. |
