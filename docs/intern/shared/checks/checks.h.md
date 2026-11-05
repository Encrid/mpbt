# src/shared/checks/checks.h

This header lists the checks by name, as `docs/extern/mpbt_check.h.md`, *The checks*, orders them.
The host orders the systems of the checks with it, and `report` orders the findings of the phase `check` with it.

## The constants

| Constant | Type | Value |
| --- | --- | --- |
| `CHECKS_COUNT` | `size_t` | 12, the count of the checks. |
| `CHECKS_NAMES` | `char [CHECKS_COUNT][10]` | The name of each check, in its order, with a zero byte after it. |

Each constant is a `constexpr`. A `constexpr` of C23 cannot hold a pointer that is not null, so each name is an array of `char`.
The longest name, `workflows`, takes 9 bytes and the zero byte.
A file that includes the header gets the names with no file of code to link. Thus the host and a module use the same list.

## Functions

The header declares no function.
