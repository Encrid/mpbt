# src/read/read_settings.c

This file writes the singletons of the tables `[test]`, `[check]`, `[style]`, `[prose]` and `[ci]`: `mpbt:Tests`, `mpbt:TextCheck`, `mpbt:LayoutCheck`, `mpbt:StyleCheck`, `mpbt:ProseCheck` and `mpbt:Ci`.
`read_leaks` writes `mpbt:Leaks`, because it also reads the files of `[leaks] with`.

## The singletons

| Singleton | Table | Fields |
| --- | --- | --- |
| `mpbt:Tests` | `[test]` | `cases` is `tests/cases` if the table does not give it. `writers` is lines. `timeout` and `copies` are 0 if the table does not give them. |
| `mpbt:TextCheck` | `[check]` | `unicode` and `refuse` are lines. |
| `mpbt:LayoutCheck` | `[check]` | `guides` is lines. |
| `mpbt:StyleCheck` | `[style]` | Each limit, or its default: `docs/extern/mpbt_check.h.md`, *[style]*. |
| `mpbt:ProseCheck` | `[prose]` | Each limit, or its default: `docs/extern/mpbt_check.h.md`, *[prose]*. |
| `mpbt:Ci` | `[ci]` | `needs` is the bit of each need. |

These singletons are plain components that `read` writes in the phase `read`. No module gets them as settings of Bridge.
A list of lines comes from `read_put_lines`: `docs/intern/read/read_world.c.md`, *Texts and lists*.
`run_variables` gives the values of the variables of each text and of each item.
`attach` gives each singleton its value, with the id 0. In `test`, `read_need_keys` checks `timeout` of `[test]`, because each case needs it.

## The needs of a runner

`put_ci` sets `MPBT_NEED_DISPLAY` for `display`, `MPBT_NEED_VULKAN` for `vulkan` and `MPBT_NEED_GL` for `gl`.
Each other need stops the read, with its message of `docs/extern/mpbt_ci.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `read_settings` | `true` after the 6 singletons, or `false` and a finding. |
| `put_tests` | `true` and the value of `mpbt:Tests`, or `false` and a finding. |
| `put_checks` | `true` and the values of `mpbt:TextCheck` and `mpbt:LayoutCheck`, or `false` and a finding. |
| `put_limits` | The values of `mpbt:StyleCheck` and `mpbt:ProseCheck`. |
| `put_ci` | `true` and the value of `mpbt:Ci`, or `false` and a finding. |
