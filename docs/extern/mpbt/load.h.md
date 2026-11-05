# include/mpbt/load.h

`include/mpbt/load.h` gives `mpbt:Load`: a module of Bridge that mpbt loads into its run, beside its own modules.
Thus a project adds its own steps and checks to mpbt.

## [[load]]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `artifact` | text | none | The name of an artifact of the project that is a module. |
| `file` | text | none | The file of a module that the project does not build, for example a module of a source. |
| `phases` | table | `{}` | A key is a phase of the module, and its value is a phase of mpbt. A phase with no key keeps its name. |
| `config` | table | `{}` | The settings of the module. A key is a setting, and its value is a text, a number, `true` or `false`. |
| Each other key | | the manifest | A key of a module of the deployment of Bridge-Host, for example `read` or `write`. |

A table names one module, with `artifact` or with `file`, and not with both.
For an artifact of the project, `artifact = "<name>"` is enough: the manifest of the module gives the defaults.

```toml
[[load]]
artifact = "deps_check"
write = ["mpbt:Finding"]
phases = { look = "check" }
```

Each other key has the meaning that Bridge-Host gives it: https://github.com/Encrid/Bridge-Host/blob/v0.4.1/readme.md#the-modules.
The manifest of a module gives a default for each key, and for each setting: https://github.com/Encrid/Bridge-Host/blob/v0.4.1/readme.md#the-manifest-of-a-module.
A key that no table and no manifest gives stops mpbt.

## The modules of a project

Before the first phase of each command, mpbt builds each artifact of `[[load]]`, for the target of this machine and not for `--target`.
mpbt loads a native module with BB-Native, and a module of wasm with BB-Wasm.
A native module can use the OS. A module of wasm can only read and write components.

A module joins the phases of mpbt: `docs/extern/mpbt/command.h.md`, *The phases*.
It reads the types of mpbt that its grants name, and it can write a finding: `docs/extern/mpbt/finding.h.md`.
The headers of mpbt and of Bridge are in `{toolchain}/include`.

## mpbt:Load

Each table `[[load]]` is an entity with `mpbt:Load`.
`mpbt_load_t` takes 44 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `artifact` | `bridge_text_t` | 0 | With `MPBT_LOAD_ARTIFACT`: `artifact`. |
| `file` | `bridge_text_t` | 8 | With `MPBT_LOAD_FILE`: `file`. |
| `keys` | `bridge_text_t` | 16 | A map: each other key, then its value as a text of TOML, for example `["mpbt:Finding"]`. |
| `phases` | `bridge_text_t` | 24 | A map: each phase of the module, then its phase of mpbt. |
| `config` | `bridge_text_t` | 32 | A map: each setting, then its value as a text of TOML, for example `true` or `"word"`. |
| `from` | `mpbt_load_from_t` | 40 | Where the module comes from. |

Bytes 41 to 43 hold no field. Its maps: `docs/extern/mpbt/project.h.md`, *Lists and maps*.

### mpbt:mpbt_load_from_t

`mpbt_load_from_t` is an enum of `uint8_t`.

| Constant | Value | The module is |
| --- | --- | --- |
| `MPBT_LOAD_ARTIFACT` | 1 | An artifact of the project. |
| `MPBT_LOAD_FILE` | 2 | A file. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:mpbt_load_from_t` | `mpbt_load_from_t` | `mpbt_load_from_t_desc` | `MPBT_LOAD_FROM_VALUES` |
| `mpbt:Load` | `mpbt_load_t` | `mpbt_load_t_desc` | `MPBT_LOAD_FIELDS` |

```text
uint8_t { MPBT_LOAD_ARTIFACT = 1, MPBT_LOAD_FILE = 2 }
{ bridge_text_t artifact; bridge_text_t file; bridge_text_t keys; bridge_text_t phases; bridge_text_t config; mpbt_load_from_t from; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:mpbt_load_from_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Load` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare the enum first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Load` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `[[load]] names no artifact and no file` | A table has neither `artifact` nor `file`. |
| `[[load]] names the artifact <artifact> and the file <file>` | A table has both. |
| `[[load]]: no artifact <artifact>` | `artifact` names no artifact of the project. |
| `[[load]]: <file> is not there` | `file` names no file. |
| `<module>: not stated: <key>` | No table and no manifest gives a key of the module. |
| `<module>: <phase> is not a phase of mpbt` | `phases` maps a phase of the module to a phase that mpbt does not run. |
