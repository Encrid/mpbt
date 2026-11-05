# src/test/test_variables.c

This file makes the `variables_t` of a run and of each copy of a case, for `variables_expand` and `variables_expand_items`.
The variables of a case are in `docs/extern/mpbt_case.h.md`, *[[case]]*.

## The variables of a run

1. Each `mpbt:Variable` with `MPBT_SCOPE_PROJECT` gives an entry.
2. The value of `{target}` names the target of the run. Each variable of that target with `MPBT_SCOPE_TARGET` gives an entry too.
3. A changed run replaces `{out}` with `<build>/<run>/<target>`, where `<run>` is `fail`, `branches` or `leaks`.
4. `variables_sort` sorts the entries, so that `variables_find` can search them.

An entry points to the bytes of its `mpbt:Variable`. Thus the entries copy no value.

## The variables of a copy

`test_add_variables` copies the entries of the run, and adds `{case}`: the folder of the copy, with `/`.
If a text of the use or of the claims holds `{port}`, it adds `{port}` too, with the number that `os_get_free_port` gives.
Each copy asks for its own port. A case with no `{port}` gets none, so a value that names `{port}` stops its expansion with a finding.

## Functions

| Function | Result |
| --- | --- |
| `test_make_variables` | The variables of a run, or `false` with no memory. |
| `test_add_variables` | The variables of a copy, or `false` if no port or no memory comes. |
| `test_free_variables` | Gives the memory of the entries back. |
| `has_port` | Whether a text of a case names `{port}`. |
| `set_entry` | Adds an entry, or replaces the entry of the same name. |
