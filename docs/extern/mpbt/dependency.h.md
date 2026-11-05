# include/mpbt/dependency.h

`include/mpbt/dependency.h` gives `mpbt:Dependency`, a folder of files that a different project makes, and `mpbt:Agree`, a rule between dependencies.

## [[dependency]]

A dependency has a list of its files. A line of the list is `<key> <value>`, or `<digest>  <file>`.
The `package.txt` of a different project is such a list: `docs/extern/mpbt/compose.h.md`, *package.txt*.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `name` | text | none | The name. The variable `{<name>}` is the folder `into`. |
| `from` | text | none | The folder that holds the files. |
| `list` | text | none | The list of the files, in `from`. |
| `into` | text | none | The folder that gets the copies. |
| `make` | list | `[]` | A command that runs before mpbt reads the list. |
| `optional` | bool | `false` | With `true`, a list that is not there skips the dependency. |

```toml
[[dependency]]
name = "sdk"
from = "../sdk/build/{home}"
list = "package.txt"
into = "{build}/taken/sdk"
```

In the phase `take`, mpbt copies the files of each dependency into its folder `into`.
It copies a file only if the copy is not there, or if the copy is different.
It changes no file if a file does not have the digest of the list, or if 2 dependencies do not agree.

## [[agree]]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `keys` | list | none | The keys that must have one value, as `<dependency>.<key>`. A dependency that mpbt did not take does not count. |
| `length` | integer | none | The number of characters at the start of each value that mpbt compares. |

## mpbt:Dependency

Each dependency is an entity with `mpbt:Dependency`.
`mpbt_dependency_t` takes 44 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | `name`. |
| `from` | `bridge_text_t` | 8 | `from`. |
| `list` | `bridge_text_t` | 16 | `list`. |
| `into` | `bridge_text_t` | 24 | `into`. |
| `make` | `bridge_text_t` | 32 | A list: the command of `make`, or no item. |
| `optional` | `bool` | 40 | `optional`. |

Bytes 41 to 43 hold no field.

## mpbt:Agree

Each rule is an entity with `mpbt:Agree`.
`mpbt_agree_t` takes 12 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `keys` | `bridge_text_t` | 0 | A list: `keys`. |
| `length` | `uint32_t` | 8 | `length`. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Dependency` | `mpbt_dependency_t` | `mpbt_dependency_t_desc` | `MPBT_DEPENDENCY_FIELDS` |
| `mpbt:Agree` | `mpbt_agree_t` | `mpbt_agree_t_desc` | `MPBT_AGREE_FIELDS` |

```text
{ bridge_text_t name; bridge_text_t from; bridge_text_t list; bridge_text_t into; bridge_text_t make; bool optional; }
{ bridge_text_t keys; uint32_t length; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Dependency` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Agree` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Dependency` | `read` | Each module with a grant. |
| `mpbt:Agree` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `<list> is not there` | The list of a dependency is not there, and `optional` is `false`. |
| `not taken: <list> is not there` | The same, with `optional` at `true`. mpbt skips the dependency. |
| `<file> is not there` | A file of the list is not in `from`. |
| `refused: <file> is not what <list> states` | A file does not have the digest of the list. |
| `refused: the dependencies do not agree: <values>` | The values of a rule differ. `<values>` gives each `<dependency>.<key> <value>`, with commas between them. |
| `taken: <name>, <values>` | mpbt took a dependency. `<values>` gives the keys of its list. |
