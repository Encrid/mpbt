# include/mpbt/artifact.h

`include/mpbt/artifact.h` gives `mpbt:Artifact`, a file that the build makes, and `mpbt:Built`, the files that the build made for it.

## [[artifact]]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `name` | text | none | The name of the artifact. It can hold variables, for example `{system}`. |
| `kind` | text | none | The kind: `docs/extern/mpbt/kind.h.md`. |
| `sources` | list | none | The patterns of the sources, from the folder of the project. An item that is a list variable gives the items of the list. |
| `include` | list | `[]` | The folders of the headers. |
| `defines` | list | `[]` | The macros, with no `-D`. |
| `flags` | list | `[]` | More flags of the compiler, for example `-lm`. They come after the flags of the kind. |
| `link` | list | `[]` | The files that the artifact links. |
| `beside` | list | `[]` | The files to copy into the folder of the artifact. |
| `manifest` | list | `[]` | The texts that the variable `{manifest}` gives to the steps. |
| `folder` | text | no text | The folder of the artifact, in `{out}`. |
| `target` | text | the target of the run | The target of the artifact. It gets the keys of that target, and its name as `{target}`. |
| `variants` | list of tables | `[]` | The variants: *Variants*. |
| `test` | bool | `false` | `true` for an artifact that only the tests use. Only `test` makes it, and `package.txt` does not list it. |
| `path` | bool | `false` | `true` for a library of the folder `built` that a case loads by its macro: *The macros of the paths*. |
| `part` | text | none | In a project with parts: the part of the artifact: `docs/extern/mpbt/compose.h.md`, *[parts]*. |

```toml
[[artifact]]
name = "hello"
kind = "program"
sources = ["src/*.c"]
```

An artifact with a `target` stays in `{out}` of the run. Thus a build for one target can make a file for a different target, for example a library for each system.

## Variants

A variant is a copy of the artifact with its own `name`, and with keys that replace the keys of the artifact.
A variant can also state `unstamped = true`: then it does no `section` of its kind.
Each variant is an artifact of its own, after the artifact that it copies.

## [module] and [[modules]]

`[module]` holds the keys that the modules of the tests share. Each row of `[[modules]]` is an artifact over these keys.
A row states its `name`, and only the keys that differ, for example `sources`, `defines` or `path = true`.
A row can have `variants`. The modules come before the artifacts of `[[artifact]]`.

## The macros of the paths

The variable `{paths}` gives a macro for each library of the folder `built` with `path = true`, and for each library of the folder `backends`.
The name of the macro is the name of the artifact in upper case, with `_` for each `-`, then `_PATH`.
A `bridge_` at the start of the name of the artifact does not go into the macro.
Its value is `"{out}/<folder>/<name>{library}"`.
`{paths}` also gives `BUILT_DIR="{out}/built"` and `BUILT_SUFFIX="{library}"`.
An item `{paths}` of `defines` gives all the macros.

## The build

For each artifact, the build does these steps:

1. It finds the sources. It stops if no file matches the patterns.
2. It makes the folder of the output, and the folder `obj`.
3. If a file of `link` is not there, it does the `unlinked` steps of the kind.
4. Else it does the `steps` of the kind, and copies the files of `beside` into the folder of the output.

The texts of the artifact have their variables replaced in the phase `read`, with the keys of the target of the artifact.
`build` and `pack` make only the artifacts that ship. `test` makes them all, and stops if one of them is not linked.

## mpbt:Artifact

Each artifact and each variant is an entity with `mpbt:Artifact`.
`mpbt_artifact_t` takes 100 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | `name`. |
| `kind` | `bridge_text_t` | 8 | The name of the kind. |
| `sources` | `bridge_text_t` | 16 | A list: the patterns of `sources`. |
| `include` | `bridge_text_t` | 24 | A list: `include`. |
| `defines` | `bridge_text_t` | 32 | A list: `defines`. |
| `flags` | `bridge_text_t` | 40 | A list: `flags`. |
| `link` | `bridge_text_t` | 48 | A list: `link`. |
| `beside` | `bridge_text_t` | 56 | A list: `beside`. |
| `manifest` | `bridge_text_t` | 64 | A list: `manifest`. |
| `folder` | `bridge_text_t` | 72 | `folder`, or no bytes. |
| `target` | `bridge_text_t` | 80 | The name of the target of the artifact. |
| `part` | `bridge_text_t` | 88 | The part, or no bytes in a project with no parts. |
| `test` | `bool` | 96 | `test`. |
| `path` | `bool` | 97 | `path`. |
| `unstamped` | `bool` | 98 | `unstamped` of a variant. |

Byte 99 holds no field. Its lists: `docs/extern/mpbt/project.h.md`, *Lists and maps*.

## mpbt:Built

The build attaches `mpbt:Built` to the entity of each artifact that it made.
`mpbt_built_t` takes 20 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `output` | `bridge_text_t` | 0 | The file of the artifact, as `{output}` gives it. |
| `files` | `bridge_text_t` | 8 | A list: the output and the copies of `beside`. It has no item if `linked` is `false`. |
| `linked` | `bool` | 16 | `false` if the build did the `unlinked` steps. |

Bytes 17 to 19 hold no field.

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Artifact` | `mpbt_artifact_t` | `mpbt_artifact_t_desc` | `MPBT_ARTIFACT_FIELDS` |
| `mpbt:Built` | `mpbt_built_t` | `mpbt_built_t_desc` | `MPBT_BUILT_FIELDS` |

```text
{ bridge_text_t name; bridge_text_t kind; bridge_text_t sources; bridge_text_t include; bridge_text_t defines; bridge_text_t flags; bridge_text_t link; bridge_text_t beside; bridge_text_t manifest; bridge_text_t folder; bridge_text_t target; bridge_text_t part; bool test; bool path; bool unstamped; }
{ bridge_text_t output; bridge_text_t files; bool linked; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Artifact` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Built` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Artifact` | `read` | Each module with a grant. |
| `mpbt:Built` | `build` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `no file matches the sources of <name>` | No file matches the patterns of `sources`. |
| `the cases need what is linked: <names>` | `test` finds an artifact that is not linked. |
| `<paths>` | `build` and `pack` write the output of each artifact that ships, one path on each line. |
