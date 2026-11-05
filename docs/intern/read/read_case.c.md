# src/read/read_case.c

This file checks one table `[[case]]`, and writes the entities of the case and of its false variant: `docs/extern/mpbt_case.h.md`.

## The checks

`check_case` stops the read at the first fault of the case, with its message of `docs/extern/mpbt_case.h.md`, *Messages*:

1. `toml_doc_check_keys` checks the keys of the case, of `false`, of each `helper` and of each table of claims.
2. A case with no `name` or no `run` is a fault: `read_need_keys`. So is a case with no claim, or with no `false`.
3. `ignore` holds no item, or only `interrupt`.
4. Each function of `fail`, of the case and of `false`, is in `[fail.calls]`, as `read_is_listed` tells.

Its last message is in `docs/extern/mpbt_fail.h.md`, *Messages*.
`read_write_script` checks the steps of each script, of the case and of its false variant.

## The entity of the case

1. `spawn` gives the id of the case.
2. `mpbt:Case` gets the name of the group, `name`, the place of the case in its file, and `alone`.
3. `read_write_run` attaches `mpbt:Run`, from the case alone.
4. `read_write_claims` attaches `mpbt:Claims`, and `mpbt:HelperClaims` if the case has a helper.
5. `read_write_script` writes the steps of `script`, with the id of the case as their owner.

## The false variant

`write_false` writes the false variant as an entity of its own:

1. `spawn` gives its id, and `mpbt:FalseVariant` gets the id of the case as `owner`.
2. `read_write_run` attaches `mpbt:Run`, from the case and from `false`: `docs/intern/read/read_case_run.c.md`, *The false variant*.
3. If that run has a helper, `read_write_claims` attaches the claims of its helper as `mpbt:HelperClaims`.
4. `read_write_script` writes the steps of `script` of `false`. If `false` states no `script`, it copies the steps of the case.

Thus the false variant owns its whole script, and `script = []` in `false` gives no step.
In the same way, the claims of its helper come from `helper` of `false` if `false` states `helper`, else from the helper of the case.
The false variant has no `mpbt:Claims`, because the test judges it with the claims of its case.

## Functions

| Function | Result |
| --- | --- |
| `read_case` | `true` after the entities of one case, or `false` and a finding. |
| `check_case` | `true` for a case that passes *The checks*, or `false` and the first finding. |
| `write_false` | `true` after the entities of the false variant, or `false` and a finding. |
