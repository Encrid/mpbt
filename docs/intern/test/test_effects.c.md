# src/test/test_effects.c

This file gives what each counted function does to a resource, and checks each place against the declaration of its function.
The kinds are in `docs/extern/mpbt_leaks.h.md`, *test --leaks*. The places are in `docs/extern/mpbt_leaks.h.md`, *The places*.

## The effects

`test_list_effects` gives each counted function its list of `test_effect_t`:

| Function | Effect | Kind | Place | Must fit a pointer |
| --- | --- | --- | --- | --- |
| `malloc`, `calloc` | Take | `memory` | `result` | Yes |
| `realloc` | Move | `memory` | None | Yes |
| `free` | Give | `memory` | `1` | Yes |
| A line of `memory` of `mpbt:Leaks` | Take | `memory` | `result` | Yes |
| `take` of a `mpbt:LeakPair` | Take | The name of `take` | `result` | Yes |
| `give` of a `mpbt:LeakPair` | Give | The name of `take` | `1` | Yes |
| A key of `takes` or `gives` of a `mpbt:LeakKind` | Take or give | `name` of the kind | Each place of its list | No |

`add_kind` adds the effects of one `mpbt:LeakKind`. A function can have more than one place, and can be in more than one kind.
The module `read` refused each place of a wrong form: `docs/intern/read/read_leaks.c.md`, *A kind*.
`read_place` cuts each place into its parts: `result`, or the number `n`, whether a `*` comes first, and the name of the field.

The kinds are `memory`, then the kind of each pair, then each `mpbt:LeakKind`. A kind is in the list one time.

## The fit

`test_fit_effects` checks the effects of a function that a source uses against its `test_decl_t`, in this order:

1. A take that must fit a pointer needs a result that is a pointer, after the `typedef` names.
2. A give that must fit a pointer needs a pointer as the first parameter.
3. A place `result` needs a result that is not `void`.
4. A place `<n>` or `*<n>` needs a parameter `n`, and a place `*<n>` needs a pointer there.

The first rule that fails stops the run, with its finding of the same table. A type is a pointer if it ends with `*`.

## Functions

| Function | Result |
| --- | --- |
| `test_list_effects` | Each counted function with its effects, and the list of the kinds, or `false` after a finding. |
| `test_fit_effects` | `true` if each place fits the declaration, else `false`. |
| `add_kind` | The effects of one kind. |
| `add_effect` | Adds one effect to a function, if it does not have it yet. |
| `read_place` | The parts of one place. |
