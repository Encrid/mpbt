# src/take/take_agree.c

This file checks the rules of `[[agree]]` between the dependencies that `take` took: `docs/extern/mpbt_dependency.h.md`, *[[agree]]*.

## The steps

For each rule, in the order of the rows:

1. Each item of `keys` is `<dependency>.<key>`. It is cut at its first `.`.
2. An item whose dependency is not taken does not count.
3. `get_value` gives the value of the key in the list of the dependency. A key that the list does not give has no bytes.
4. Only the first `length` characters of each value count.
5. If 2 values of the rule differ, the run stops. The finding gives each item and its value, with `, ` between 2 items.

The message is in `docs/extern/mpbt_dependency.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `take_agree` | `true` if each rule holds, or `false` and a finding. |
| `get_value` | The value of a key of a list, with no bytes if the list does not give it. |
