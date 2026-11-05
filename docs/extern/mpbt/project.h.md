# include/mpbt/project.h

`include/mpbt/project.h` gives `mpbt:Project` and `mpbt:Variable`: the name of the project, its legal notice and its variables.
This document also gives the rules that each type of mpbt follows.

## The files of the config

The config of a project is `.toolchain/project.toml`, then each file `.toml` of `.toolchain/config` and of its folders, in the order of their paths.
Each file is TOML 1.1. mpbt reads all the files as one config, over the values that mpbt holds:

- A table of one file adds its keys to the table with the same name in a different file.
- When 2 files give one list of tables, for example `[[artifact]]`, the list holds the tables of both.
- A key that 2 files give stops mpbt. A key that sets a value of mpbt stops it too.

## The types of mpbt

Each type of mpbt is in the namespace `mpbt` of Bridge.
A component has a short name, for example `mpbt:Source`.
An enum and a bitmask have the name of their C type, for example `mpbt:mpbt_scope_t`.
Thus a field can name its type with no namespace: https://github.com/Encrid/Bridge/blob/v0.4.1/docs/extern/bridge_schema.h.md#the-type-set.

- A module that reads or writes a type of mpbt needs a grant for it: https://github.com/Encrid/Bridge/blob/v0.4.1/docs/extern/bridge_abi.h.md#grants.
- Each module that declares a type states its own `on_unload`, because Bridge does not compare it.
- An entity that belongs to a different entity holds the id of its owner in the field `owner`.
- The constants of each enum start at 1. A bit of a bitmask that tells which fields hold a value comes before the fields it names.

## Lists and maps

A list or a map in a component is a `bridge_text_t` whose bytes are an array of `bridge_text_t`.
Item `i` of the list is the `bridge_text_t` at `at + 8 * i`, and the list has `len / 8` items.
A map is the same array, with each key followed by its value. A value that is a list is an array of its own.
The module that writes the list puts the array and its items in one `alloc`.
Thus the share of the array also holds the items: https://github.com/Encrid/Bridge/blob/v0.4.1/docs/extern/bridge_abi.h.md#alloc.

A list in the settings of a module is one text, because a setting of Bridge holds one text: https://github.com/Encrid/Bridge/blob/v0.4.1/docs/extern/bridge.h.md#the-settings-of-a-module.
Each item of such a list ends with `\n`, and mpbt refuses an item that holds a line end.

## Variables

A text of the config can hold variables. A variable is a name in braces, for example `{root}`.
A value can hold variables too, and mpbt replaces them in the same way.

| Variable | Value |
| --- | --- |
| `{root}` | The folder of the project. |
| `{build}` | The output folder: `--out`, or the folder `build` of the root. |
| `{dist}` | The deliverable of the target: `<build>/<target>`, or `<build>/<target>-debug` with `--debug`. |
| `{out}` | The scratch folder of the target, `<dist>/scratch`. It holds each artifact. |
| `{target}` | The name of the target of the run. |
| `{home}` | The name of the target of this machine. |
| `{zig}` | The zig program, which `fetch` puts into the folder `zig` beside the program mpbt. |
| `{toolchain}` | The folder `toolchain` beside the program mpbt. It holds the files that mpbt gives to a build, for example the sources of the key `runtime` of a target. |
| `{paths}` | A list: a `*_PATH` macro for each artifact with `path = true`, then `BUILT_DIR` and `BUILT_SUFFIX`: `docs/extern/mpbt/artifact.h.md`, *The macros of the paths*. |

These values are variables too:

- each key of the target, for example `{exe}`: `docs/extern/mpbt/target.h.md`;
- each key of `[variables]`;
- each source, each dependency and each tool, with its folder or its program.

A path in a variable uses `/` on each system.
A list variable that is a full item of a list gives all its items there.
A list variable inside a longer text needs a separator after a colon, for example `{manifest:\0}`.

In the phase `read`, mpbt replaces the variables of each text of the config.
The texts of the steps of a kind and the texts of the cases keep their variables. The build and the test replace them later, with the variables of the artifact or of the case.

## [project]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `name` | text | none | The name of the project. The title of `readme.md`, `package.txt` and the zips take it. |

## [variables]

Each key of `[variables]` is a variable, with a text or a list of texts.
A key must not have the name of a variable that mpbt gives, or of a key of a target.
`--set <name>=<value>` replaces the value of a key, also of a key that mpbt gives.

mpbt gives 4 keys. With `--debug`, `optimize` and `strip` take their values of debug.

| Key | Value | With `--debug` |
| --- | --- | --- |
| `language` | `-std=c23`, `-pedantic-errors`, `-Wall`, `-Wextra`, `-Werror` | The same. |
| `optimize` | `-O2`, `-DNDEBUG`, `-g0`, `-s`, `-fno-sanitize=undefined`, `-fno-stack-protector`, `-fno-omit-frame-pointer` | `-O0`, `-g`, `-fsanitize=undefined`, `-fno-sanitize=vptr`, `-fno-sanitize=function`, `-fstack-protector-strong`, `-fno-omit-frame-pointer` |
| `float` | `-ffp-contract=on`, `-fno-fast-math`, `-fno-rounding-math` | The same. |
| `strip` | `-fstrip` | `-fno-strip` |

`-s` drops the debug information when the linker runs, also of the objects that zig builds for the C library. Without it, a program of Linux holds the folder of the project.

## [tools]

Each key of `[tools]` is the name of a program, and its value is its path with no extension.
mpbt finds the program with the extension of this machine. The key is then a variable, with the path of the program.
A Python tool of a project is a key such as `python = "python"`.

## .toolchain/header.txt

`.toolchain/header.txt` holds the legal notice that starts each file of code, as `docs/contributing/coding_style.md`, *G1 - The legal notice*, tells.
mpbt reads it into `mpbt:Project`.

## mpbt:Project

`mpbt:Project` holds the values of the project. It is a singleton.
`mpbt_project_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | `[project] name`. |
| `notice` | `bridge_text_t` | 8 | The text of `.toolchain/header.txt`. |

## mpbt:Variable

Each variable is an entity with `mpbt:Variable`.
`mpbt_variable_t` takes 28 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | The name, with no braces. |
| `target` | `bridge_text_t` | 8 | With `MPBT_SCOPE_TARGET`: the name of the target that has the key. With `MPBT_SCOPE_PROJECT`: no bytes. |
| `value` | `bridge_text_t` | 16 | The text, or the list: *Lists and maps*. Its own variables are replaced. |
| `kind` | `mpbt_value_kind_t` | 24 | A text or a list. |
| `scope` | `mpbt_scope_t` | 25 | One value for each target, or the value of one target. |

Bytes 26 and 27 hold no field.

### mpbt:mpbt_value_kind_t

`mpbt_value_kind_t` is an enum of `uint8_t`.

| Constant | Value | The value is |
| --- | --- | --- |
| `MPBT_VALUE_TEXT` | 1 | A text. |
| `MPBT_VALUE_LIST` | 2 | A list of texts. |

### mpbt:mpbt_scope_t

`mpbt_scope_t` is an enum of `uint8_t`.

| Constant | Value | The variable has |
| --- | --- | --- |
| `MPBT_SCOPE_PROJECT` | 1 | One value for each target. |
| `MPBT_SCOPE_TARGET` | 2 | The value of the target that `target` names. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Project` | `mpbt_project_t` | `mpbt_project_t_desc` | `MPBT_PROJECT_FIELDS` |
| `mpbt:mpbt_value_kind_t` | `mpbt_value_kind_t` | `mpbt_value_kind_t_desc` | `MPBT_VALUE_KIND_VALUES` |
| `mpbt:mpbt_scope_t` | `mpbt_scope_t` | `mpbt_scope_t_desc` | `MPBT_SCOPE_VALUES` |
| `mpbt:Variable` | `mpbt_variable_t` | `mpbt_variable_t_desc` | `MPBT_VARIABLE_FIELDS` |

```text
{ bridge_text_t name; bridge_text_t notice; }
uint8_t { MPBT_VALUE_TEXT = 1, MPBT_VALUE_LIST = 2 }
uint8_t { MPBT_SCOPE_PROJECT = 1, MPBT_SCOPE_TARGET = 2 }
{ bridge_text_t name; bridge_text_t target; bridge_text_t value; mpbt_value_kind_t kind; mpbt_scope_t scope; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Project` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_value_kind_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_scope_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Variable` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare the 2 enums first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Project` | `read` | Each module with a grant. |
| `mpbt:Variable` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `<path>:<line>: <reason>` | A file of the config is not TOML 1.1. `<reason>` is the reason of tomlc17. |
| `<file> states <key>, and <file> states it too` | 2 files give one key, and the key holds no table and no list of tables. |
| `.toolchain/project.toml: write the name of the project in [project] name` | `name` is not there, or is empty, and a step needs it. |
| `no variable {<name>} for <text>` | A text names a variable with no value. |
| `{<name>} is a list inside a text: write {<name>:<separator>}` | A list variable inside a longer text has no separator. |
| `[variables] names a built-in variable or a key of a target: <names>` | A key of `[variables]` has the name of a variable that mpbt gives. |
| `--set <name>=<value>: [variables] has no <name>` | `--set` names no key of `[variables]`. |
| `the tool <name> is not at <path>` | A text names a tool, and the program is not there. |
| `<setting> holds a line end, and a setting holds one line for each item` | An item of a list in the settings of a module holds a line end. |
