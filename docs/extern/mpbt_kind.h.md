# include/mpbt_kind.h

`include/mpbt_kind.h` gives `mpbt:Kind` and `mpbt:Step`: the kinds of artifact, and the steps that make an artifact of a kind.

## [kinds.\<kind\>]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `output` | text | none | The name of the file of an artifact. |
| `steps` | list of steps | none | The steps that make an artifact. |
| `unlinked` | list of steps | none | The steps when a file of `link` is not there. With no `unlinked`, such an artifact stops mpbt. |
| `flags` | list | `[]` | The flags of the compiler that the kind gives to each artifact, before the flags of the artifact. |

mpbt gives 4 kinds. A project can add more.

| Kind | `output` | Steps |
| --- | --- | --- |
| `program` | `{name}{exe}` | `zig cc` compiles the sources, and links them with the files of `link`. |
| `library` | `{name}{library}` | `zig cc -shared` compiles the sources and `runtime` into a shared library. |
| `archive` | `{name}.a` | `zig build-lib -static` compiles the sources into a static library, with `{strip}`. |
| `file` | `{name}` | It copies the one source to the output. |

A program gets no `runtime`. The kind `archive` gives `{strip}` to zig, because zig reads no flag after `-cflags`.
Without `-fstrip`, zig asks the compiler for CodeView, and each object of an archive of Windows holds its own path.

## Steps

A step does its actions in this order: `run`, `section`, `contains`, `copy`, `rename`.

| Key | Action |
| --- | --- |
| `run` | Runs the command, in the folder of the project or in `cwd`. |
| `cwd` | The folder of `run`. A relative path starts from the folder of the project. |
| `section`, `text` | Adds to the end of a WebAssembly artifact a custom section with this name and this text. |
| `contains` | Stops mpbt if the bytes of the artifact do not hold this text. |
| `copy` | Copies the first file to the second file. |
| `rename` | Moves the first file to the second file. |

With `cwd`, `{sources}`, each folder of `{include}` and the caches of zig are full paths. Each other relative path of the command starts from `cwd`.
A variant with `unstamped = true` does no `section`: `docs/extern/mpbt_artifact.h.md`, *[[artifact]]*.

The texts of a kind keep their variables. For each artifact, the build replaces them with these variables, and with the keys of its target:

| Variable | Value |
| --- | --- |
| `{name}` | The name of the artifact. |
| `{output}` | The file of the artifact. |
| `{work}` | The start of the name of a temporary file, in `<dist>/obj`. |
| `{sources}` | The files that match the patterns of `sources`. |
| `{defines}` | Each item of `defines`, after `-D`. |
| `{include}` | Each folder of `include`, after `-I`. |
| `{flags}` | The items of `flags` of the kind, then those of the artifact. |
| `{link}` | The files of `link`. |
| `{manifest}` | The items of `manifest`. |

A section is the byte 0, the size of its content, then the content: the size of the name, the name, then the text.
Each size is an unsigned LEB128.

## mpbt:Kind

Each kind is an entity with `mpbt:Kind`.
`mpbt_kind_t` takes 24 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | The name of the kind. |
| `output` | `bridge_text_t` | 8 | `output`, with its variables. |
| `flags` | `bridge_text_t` | 16 | A list: `flags`, with their variables. |

## mpbt:Step

Each step is an entity with `mpbt:Step`. Its owner is the entity of its kind.
`mpbt_step_t` takes 72 bytes. Its alignment is 8.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `owner` | `uint64_t` | 0 | The id of the entity of the kind. |
| `run` | `bridge_text_t` | 8 | With `MPBT_STEP_RUN`: a list, the command. |
| `cwd` | `bridge_text_t` | 16 | With `MPBT_STEP_RUN`: the folder, or no bytes. |
| `section` | `bridge_text_t` | 24 | With `MPBT_STEP_SECTION`: the name of the section. |
| `text` | `bridge_text_t` | 32 | With `MPBT_STEP_SECTION`: the text of the section. |
| `contains` | `bridge_text_t` | 40 | With `MPBT_STEP_CONTAINS`: the text. |
| `copy` | `bridge_text_t` | 48 | With `MPBT_STEP_COPY`: a list of 2 files. |
| `rename` | `bridge_text_t` | 56 | With `MPBT_STEP_RENAME`: a list of 2 files. |
| `order` | `uint32_t` | 64 | The place of the step in its list, from 0. |
| `list` | `mpbt_step_list_t` | 68 | The list of the step. |
| `actions` | `mpbt_step_actions_t` | 69 | The actions of the step. |

Bytes 70 and 71 hold no field. Each text keeps its variables.
Its lists: `docs/extern/mpbt_project.h.md`, *Lists and maps*.

### mpbt:mpbt_step_list_t

`mpbt_step_list_t` is an enum of `uint8_t`.

| Constant | Value | The step is in |
| --- | --- | --- |
| `MPBT_STEP_LIST_STEPS` | 1 | `steps`. |
| `MPBT_STEP_LIST_UNLINKED` | 2 | `unlinked`. |

### mpbt:mpbt_step_actions_t

`mpbt_step_actions_t` is a bitmask of `uint8_t`. Each bit stands for one action of the step.

| Constant | Value | Action |
| --- | --- | --- |
| `MPBT_STEP_RUN` | `0x1` | `run` |
| `MPBT_STEP_SECTION` | `0x2` | `section` and `text` |
| `MPBT_STEP_CONTAINS` | `0x4` | `contains` |
| `MPBT_STEP_COPY` | `0x8` | `copy` |
| `MPBT_STEP_RENAME` | `0x10` | `rename` |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Kind` | `mpbt_kind_t` | `mpbt_kind_t_desc` | `MPBT_KIND_FIELDS` |
| `mpbt:mpbt_step_list_t` | `mpbt_step_list_t` | `mpbt_step_list_t_desc` | `MPBT_STEP_LIST_VALUES` |
| `mpbt:mpbt_step_actions_t` | `mpbt_step_actions_t` | `mpbt_step_actions_t_desc` | `MPBT_STEP_ACTIONS_VALUES` |
| `mpbt:Step` | `mpbt_step_t` | `mpbt_step_t_desc` | `MPBT_STEP_FIELDS` |

```text
{ bridge_text_t name; bridge_text_t output; bridge_text_t flags; }
uint8_t { MPBT_STEP_LIST_STEPS = 1, MPBT_STEP_LIST_UNLINKED = 2 }
uint8_t { MPBT_STEP_RUN = 0x1, MPBT_STEP_SECTION = 0x2, MPBT_STEP_CONTAINS = 0x4, MPBT_STEP_COPY = 0x8, MPBT_STEP_RENAME = 0x10 }
{ uint64_t owner; bridge_text_t run; bridge_text_t cwd; bridge_text_t section; bridge_text_t text; bridge_text_t contains; bridge_text_t copy; bridge_text_t rename; uint32_t order; mpbt_step_list_t list; mpbt_step_actions_t actions; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Kind` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_step_list_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_step_actions_t` | `BRIDGE_BITMASK` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Step` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare the enum and the bitmask first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Kind` | `read` | Each module with a grant. |
| `mpbt:Step` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `<kind>: a step has no key <keys>` | A step has a key that the table *Steps* does not give. |
| `<folder> is not there, and a step of <name> runs in it` | The folder `cwd` of a step is not there. |
| `<command>` | A command of a step, of a `make` or of a proof does not end with 0. mpbt writes the command, then the next 2 lines. |
| `  ended with <status>` | The status: the number, then the number in hexadecimal between parentheses. |
| `<output>` | The output of the command. mpbt also writes it when the command ends with 0. |
| `<output> does not hold <text>` | The bytes of an artifact do not hold the text of `contains`. |
| `<file> is not there, and <name> is linked with it` | A file of `link` is not there, and the kind has no `unlinked`. |
| `compiled, not linked: <name>: <file> is not there` | A file of `link` is not there, and the kind runs its `unlinked` steps. |
