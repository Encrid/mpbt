# src/read/read_claims.c

This file attaches the claims of a case as `mpbt:Claims`, or the claims of a helper as `mpbt:HelperClaims`: `docs/extern/mpbt_case.h.md`, *Claims*.

## The steps

1. `read_write_claims` gets a table of claims, and the slot of the type to attach.
2. `get_stated` sets a bit of `mpbt_claim_keys_t` for each key that the table gives.
3. The lists, `output` and the map `files` keep their variables. A claim that is not there gets no bytes.
4. `status` and `status_not` take the integer of their key, or 0.
5. `attach` puts the value on the case, or on its false variant.

`stated` tells which claims hold a value, so a `status` of 0 and no `status` stay apart.
The two types have one layout, so one function writes both.

## Functions

| Function | Result |
| --- | --- |
| `read_write_claims` | `true` after the attach of the claims, or `false` with no memory. |
| `get_stated` | The bits of the keys of a table of claims. |
