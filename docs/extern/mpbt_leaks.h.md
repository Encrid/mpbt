# include/mpbt_leaks.h

`include/mpbt_leaks.h` gives the types of the count of `test --leaks`: `mpbt:Leaks`, `mpbt:LeakPair`, `mpbt:LeakKind` and `mpbt:LeakException`.

## test --leaks

`test --leaks` builds each file `.c` of `src` with a count of the resources.
It runs each case one time. Then it names each case that keeps a resource.
Each resource has a kind. A function of the code takes a resource of a kind, and a function gives it back.

- `memory`: `malloc` and `calloc` take it, `free` gives it back, and `realloc` changes a block of it.
- Each function of `memory` of `[leaks]` takes memory too.
- Each pair of `pairs` is a kind, with the name of the function that takes it.
- Each table of `kinds` is a kind, whose functions take and give back at places: *The places*.

A take adds 1 when its value is not zero, and a give takes away 1 when its value is not zero.
A value is not zero when one of its bytes is not zero.
`realloc` with 0 bytes is a fault, because C23 does not define it.
The count changes the program, thus the verdicts of the claims do not count.

## [leaks]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `memory` | list | `[]` | The functions that take memory, which the code gives back with `free`. |
| `pairs` | table | `{}` | A key is a function that takes a resource, and its value is the function that gives it back. |
| `kinds` | table | `{}` | The kinds. Each kind has `takes` and `gives`: tables from a function to a place, or to a list of places. |
| `with` | list | `[]` | Files with more `memory`, `pairs` and `kinds`, each in a table `[leaks]`, for example `{bridge_os}/leaks.toml`. |

A function of a pair gives a pointer, and the function that gives it back gets that pointer as its first argument.
A `typedef` of a pointer is a pointer.

```toml
[leaks]
memory = ["os_path_whole"]

[leaks.pairs]
os_reserve = "os_release"

[leaks.kinds.wasmtime_module]
takes = { wasmtime_module_new = "*4" }
gives = { wasmtime_module_delete = "1" }
```

## The places

| Place | Value |
| --- | --- |
| `result` | The result of the function. |
| `<n>` | The argument `n`, from 1. |
| `*<n>` | The value that the argument `n` points to, when the argument is not null. |
| `*<n>.<field>` | The field of the struct that the argument `n` points to, when the argument is not null. |

- A take is at `result`, at `*<n>` or at `*<n>.<field>`. It counts after the call.
- A take at `<n>` is a function of `src` that a library calls with a resource at the argument `n`. It counts after the call.
- A give at `<n>` or at `*<n>` reads its value before the call.
- A give at `result` is a function of `src` that gives its result to a library. It counts after the call.

## [[leaks.exception]]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `case` | text | none | The name of the case. It can hold `*`. |
| `kind` | text | none | The kind: `memory`, the function that takes the resource of a pair, or a kind of `kinds`. |
| `why` | text | none | The reason that the case keeps the resource. |
| `system` | text | each system | `posix` or `windows`. |

An exception excuses a resource that a case keeps by design.
Each exception needs a `why`, and must excuse a kept resource, else it is a fault.
With `--part`, only the exceptions whose `case` matches a case of the parts count.

## mpbt:Leaks

`mpbt:Leaks` holds `memory`, with the functions of each file of `with`. `mpbt:Leaks` is a singleton: the settings of the count.
`mpbt_leaks_t` takes 8 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `memory` | `bridge_text_t` | 0 | The functions that take memory, each on its own line. |

## mpbt:LeakPair

Each pair is an entity with `mpbt:LeakPair`.
`mpbt_leak_pair_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `take` | `bridge_text_t` | 0 | The function that takes the resource. |
| `give` | `bridge_text_t` | 8 | The function that gives it back. |

## mpbt:LeakKind

Each kind of `kinds` is an entity with `mpbt:LeakKind`.
`mpbt_leak_kind_t` takes 24 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | The name of the kind. |
| `takes` | `bridge_text_t` | 8 | A map: each function, then the list of its places. |
| `gives` | `bridge_text_t` | 16 | A map: each function, then the list of its places. |

Its maps: `docs/extern/mpbt_project.h.md`, *Lists and maps*.

## mpbt:LeakException

Each exception is an entity with `mpbt:LeakException`.
`mpbt_leak_exception_t` takes 28 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `case_name` | `bridge_text_t` | 0 | `case`. |
| `kind` | `bridge_text_t` | 8 | `kind`. |
| `why` | `bridge_text_t` | 16 | `why`, or no bytes. |
| `system` | `mpbt_system_t` | 24 | `system`: `docs/extern/mpbt_target.h.md`, *mpbt:mpbt_system_t*. |

Bytes 25 to 27 hold no field.

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Leaks` | `mpbt_leaks_t` | `mpbt_leaks_t_desc` | `MPBT_LEAKS_FIELDS` |
| `mpbt:LeakPair` | `mpbt_leak_pair_t` | `mpbt_leak_pair_t_desc` | `MPBT_LEAK_PAIR_FIELDS` |
| `mpbt:LeakKind` | `mpbt_leak_kind_t` | `mpbt_leak_kind_t_desc` | `MPBT_LEAK_KIND_FIELDS` |
| `mpbt:LeakException` | `mpbt_leak_exception_t` | `mpbt_leak_exception_t_desc` | `MPBT_LEAK_EXCEPTION_FIELDS` |

```text
{ bridge_text_t memory; }
{ bridge_text_t take; bridge_text_t give; }
{ bridge_text_t name; bridge_text_t takes; bridge_text_t gives; }
{ bridge_text_t case_name; bridge_text_t kind; bridge_text_t why; mpbt_system_t system; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Leaks` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:LeakPair` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:LeakKind` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:LeakException` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare `mpbt:mpbt_system_t` first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Leaks` | `read`, from the settings | The count. Each other module with a grant. |
| Each other type | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `[leaks] with: <path> is not there` | A file of `with` is not there. |
| `[leaks.kinds.<kind>]: a kind has no key <keys>` | A kind has a key other than `takes` and `gives`. |
| `[leaks.kinds.<kind>]: <name> cannot <verb> at <place>` | A place does not fit: *The places*. `<verb>` is `take` or `give back`. |
| `<name> takes a resource, and does not give a pointer` | A function of `memory` or of a pair gives no pointer. |
| `<name> gives back a resource, and does not get a pointer first` | The function that gives back a resource of a pair gets no pointer first. |
| `[leaks.kinds.<kind>]: <name> gives no result` | A place `result` names a function with no result. |
| `<name> has no argument <number>` | A place names an argument that the function does not have. |
| `<name> does not get a pointer as argument <number>` | A place `*<n>` names an argument that is not a pointer. |
| `<name> takes a list of arguments of no fixed length` | The count cannot wrap a function with `...`. |
| `<file>: a line of <name> does not match its counts` | A line of the counts of a case does not fit the kinds. |
| `leaks: <name> keeps <count> <kind>` | At its end, a case holds a resource that the code took. |
| `leaks: <name> gives back <count> <kind> that it did not take` | The code gives back a resource that code with no count took. |
| `leaks: <name> calls realloc with 0 bytes` | A case calls `realloc` with 0 bytes. |
| `leaks: the exemption of <case> for <kind> states no reason` | An exception has no `why`. |
| `leaks: the exemption of <case> for <kind> excuses no kept resource` | An exception excuses nothing. |
| `leaks: <cases> cases, <balanced> give back what they take` | The run ends. Then `, <exempt> exempt` follows if an exception excuses a case. |
| `cases that do not give back what they take: <cases>; exemptions that are faults: <faults>` | A case keeps a resource, or an exception is a fault. |
| `the tree of <source> cannot be read:` | zig cannot give the syntax of a source. The errors of zig follow. |
| `the tree of <source> is not JSON` | The syntax that zig gives is not JSON. |
