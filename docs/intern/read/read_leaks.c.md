# src/read/read_leaks.c

This file reads `[leaks]` and the files of its `with`, and writes the types of the count: `docs/extern/mpbt_leaks.h.md`.

## The steps

1. `read_with_tables` gives `[leaks]`, then the table `[leaks]` of each file of `with`.
2. The items of `memory` of each table, in that order, give the lines of `memory` of the singleton `mpbt:Leaks`.
3. Each key of `pairs` of each table gives an entity with `mpbt:LeakPair`.
4. Each table of `kinds` of each table gives an entity with `mpbt:LeakKind`, from `write_leak_kind`.
5. Each table of `[[leaks.exception]]` gives an entity with `mpbt:LeakException`, from `read_leak_exceptions`.

## A kind

`toml_doc_check_keys` checks that a kind has only `takes` and `gives`.
In `takes` and in `gives`, each key names a function. Its value is one place, or a list of places. One place gives a list of one item.
`check_places` checks the form of each place:

| Place | `takes` | `gives` |
| --- | --- | --- |
| `result` | Yes | Yes |
| `<n>` | Yes | Yes |
| `*<n>` | Yes | Yes |
| `*<n>.<field>` | Yes | No |

`<n>` is a whole number from 1, with no 0 first. `<field>` is a name of C.
Any other form stops the read. The messages are in `docs/extern/mpbt_leaks.h.md`, *Messages*.
The count of `test --leaks` checks the other rules of the places, because it needs the declaration of each function.

## The exceptions

`read_leak_exceptions` writes `case`, `kind` and `why` as texts. `read_need_keys` checks `case` and `kind`.
A `why` that is not there gives no bytes, and the count writes the finding.
`read_get_system` gives `system`: `docs/intern/read/read_checks.c.md`, *The enums*.

## Functions

| Function | Result |
| --- | --- |
| `read_leaks` | `true` after `mpbt:Leaks`, each pair and each kind, or `false` and a finding. |
| `write_leak_kind` | `true` after one entity of `mpbt:LeakKind`, or `false` and a finding. |
| `check_places` | `true` if each place of a function fits its verb, or `false` and a finding. |
| `read_leak_exceptions` | `true` after each entity of `mpbt:LeakException`, or `false` and a finding. |
