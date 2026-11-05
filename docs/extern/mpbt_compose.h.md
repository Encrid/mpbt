# include/mpbt_compose.h

`include/mpbt_compose.h` gives `mpbt:Compose`, `mpbt:Part`, `mpbt:Package` and `mpbt:Deliverable`.
These are what the deliverable holds, the parts of a project, the proof of its package, and the files of the deliverable.

## [compose]

Each table `[compose.<name>]` adds files to the deliverable, beside the artifacts that ship.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `from` | text | the folder of the project | The folder that the patterns of `headers` start from, for example the folder of a source. |
| `headers` | list | `[]` | The patterns of the public headers. Each header keeps its path below `from`. |
| `into` | text | the top of the deliverable | The folder of the deliverable that gets the headers. |
| `assets` | list | `[]` | Files of `{out}` to put at the top of the deliverable, for example a file of a step. |
| `part` | text | none | The part that owns the table, in a project with parts. |

```toml
[compose.video]
from = "include/video"
headers = ["*.h"]
into = "include"
```

This table puts `include/video/<name>.h` into the deliverable as `include/<name>.h`.

## [parts]

A project can have parts, for example a family of modules in one repository.
Each part builds, tests, packs and releases alone, with `--part <part>`. The name `<part>` is in snake case.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `name` | text | none | The name of the zips of the part, in place of `[project] name`. |
| `folder` | text | none | The folder of the part in `src`, `include`, `docs/extern`, `docs/intern` and `tests`, for example `media/video`. |
| `uses` | list | none | The parts whose artifacts the part uses. A build of the part makes them first. Write `[]` for no part. |
| `third_party` | list | none | The folders of `third_party` whose licence the zip of the part holds. Write `[]` for no folder. |
| `package` | table | none | The proof of the part, with the keys of `[package]`. |

In a project with parts, each artifact and each table of `[compose]` states its `part`.
A build makes the artifacts of a part after those of the parts of its `uses`. In a part, the order is the order of the config.
With no `--part`, `build` and `test` act on each part, `pack` writes the zip of each part, and `join` joins nothing.

## [package]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `proof` | text | no proof | A source that uses only the package. After a `pack`, mpbt builds it, and runs it if the target runs here. |
| `link` | list | `[]` | More files that the proof links, after the archives of the package, for example an archive of a source. |
| `include` | list | `[]` | More folders for the headers of the proof, after those of the package. |

## The deliverable

In the phase `compose`, mpbt copies into `{dist}`:

1. the output of each artifact that ships, and its files of `beside`, at the top;
2. each header of each table of `[compose]`, in its folder `into`, at its path below `from`;
3. each file of `assets`, at the top;
4. `license`, and the `license` of each folder of `third_party`, at their paths from the root.

The deliverable of a part holds only the licences of its folders of `third_party`.
Each copy keeps the mode of its file, so that a program keeps its execute bits. A copy changes only when its file changes.
With `--leave <name>`, mpbt does not copy the file `<name>`. Thus the false variant of a case can make a zip that lacks a file.

## package.txt

`{out}/package.txt` lists each file that the build made, except the artifacts with `test = true`:

```text
package <project>
target <target>
<digest>  <file>
```

Each `<file>` is a path from `{out}`, and `<digest>` is its SHA-256 digest.
A different project can take these files as a dependency: `docs/extern/mpbt_dependency.h.md`.

## The zip

`pack` writes `<build>/<name>-<target>.zip`. `<name>` is `[project] name`, or the name of the part.
The zip holds each file of the deliverable, at its path from `{dist}`, with its mode.
Before it writes the zip, mpbt refuses a file of the deliverable that holds a folder of this machine.
That folder is the folder of the project or of the build, with `/` or with `\`.
Thus a package does not depend on the machine that built it.

After the zip, mpbt proves the package with `proof`:

1. It unpacks the zip into `{out}/proof`.
2. It builds the proof as a program, with the headers and the archives of the package, and with `link`.
3. It runs the program if the target runs here. The program must end with 0.

## The release

`join` writes `<build>/<name>.zip` for each part of `--part`. Each file of `<build>/<name>-<target>.zip` of each target goes into the folder `<target>`.
The release of a project holds the zip of each target, and `sha256.txt` with the digest of each zip.
The release of a part holds `<name>.zip` and its `sha256.txt`.
The output of `join` holds only the path of each zip that it writes, one on each line. Thus the workflow `release` reads the paths.

## mpbt:Compose

Each table of `[compose]` is an entity with `mpbt:Compose`.
`mpbt_compose_t` takes 48 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | The name of the table. |
| `from` | `bridge_text_t` | 8 | `from`. |
| `headers` | `bridge_text_t` | 16 | A list: `headers`. |
| `into` | `bridge_text_t` | 24 | `into`. |
| `assets` | `bridge_text_t` | 32 | A list: `assets`. |
| `part` | `bridge_text_t` | 40 | `part`. A project with no parts gives no bytes. |

## mpbt:Part

Each part is an entity with `mpbt:Part`.
`mpbt_part_t` takes 40 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `part` | `bridge_text_t` | 0 | The name `<part>` of the table. |
| `name` | `bridge_text_t` | 8 | `name`. |
| `folder` | `bridge_text_t` | 16 | `folder`. |
| `uses` | `bridge_text_t` | 24 | A list: `uses`. |
| `third_party` | `bridge_text_t` | 32 | A list: `third_party`. |

## mpbt:Package

`[package]`, and each table `[parts.<part>.package]`, is an entity with `mpbt:Package`.
`mpbt_package_t` takes 32 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `part` | `bridge_text_t` | 0 | The part of the table, or no bytes for `[package]`. |
| `proof` | `bridge_text_t` | 8 | `proof`, or no bytes. |
| `link` | `bridge_text_t` | 16 | A list: `link`. |
| `include` | `bridge_text_t` | 24 | A list: `include`. |

Its lists: `docs/extern/mpbt_project.h.md`, *Lists and maps*.

## mpbt:Deliverable

`compose` writes an entity with `mpbt:Deliverable` for each part, or one in a project with no parts. `pack` reads it.
`mpbt_deliverable_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `part` | `bridge_text_t` | 0 | The part of the deliverable. A project with no parts gives no bytes. |
| `files` | `bridge_text_t` | 8 | A list: the path of each file of the deliverable from `{dist}`, after `--leave`. |

Its list: `docs/extern/mpbt_project.h.md`, *Lists and maps*.

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Compose` | `mpbt_compose_t` | `mpbt_compose_t_desc` | `MPBT_COMPOSE_FIELDS` |
| `mpbt:Part` | `mpbt_part_t` | `mpbt_part_t_desc` | `MPBT_PART_FIELDS` |
| `mpbt:Package` | `mpbt_package_t` | `mpbt_package_t_desc` | `MPBT_PACKAGE_FIELDS` |
| `mpbt:Deliverable` | `mpbt_deliverable_t` | `mpbt_deliverable_t_desc` | `MPBT_DELIVERABLE_FIELDS` |

```text
{ bridge_text_t name; bridge_text_t from; bridge_text_t headers; bridge_text_t into; bridge_text_t assets; bridge_text_t part; }
{ bridge_text_t part; bridge_text_t name; bridge_text_t folder; bridge_text_t uses; bridge_text_t third_party; }
{ bridge_text_t part; bridge_text_t proof; bridge_text_t link; bridge_text_t include; }
{ bridge_text_t part; bridge_text_t files; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Compose` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Part` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Package` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Deliverable` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Compose` | `read` | Each module with a grant. |
| `mpbt:Part` | `read` | Each module with a grant. |
| `mpbt:Package` | `read` | Each module with a grant. |
| `mpbt:Deliverable` | `compose` | `pack`. Each other module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `<name> states no part, and the project has parts` | An artifact or a table of `[compose]` has no `part` in a project with parts. |
| `<name> states the part <part>, and [parts] does not have it` | An artifact or a table of `[compose]` names a part that is not there. |
| `[parts.<part>] states no <key>` | A part has no `name`, `folder`, `uses` or `third_party`. |
| `[parts.<part>]: a part has no key <keys>` | A part has a key that the table does not give. |
| `no part <part>; the parts: <parts>` | `--part`, `--tag` or `uses` names a part that is not there. |
| `the uses of the parts make a cycle: <parts>` | A part uses itself, directly or through a different part. |
| `no case group is in the parts <parts>` | `test --part` finds no group of cases in the folders of the parts. |
| `<license> is not there, and the deliverable needs it` | A folder of `third_party` has no `license`. |
| `--leave <name>: the deliverable holds no <name>` | `--leave` names no file of the deliverable. |
| `<file> holds <path>, a path of the machine that built it` | A file of the deliverable holds the folder of the project or of the build. |
| `package proof: <project> ran` | The proof ran, and ended with 0. |
| `package proof: <project> built` | The proof was built, and its target does not run here. |
| `<zip> is not there: pack <part> for <target> first` | `join` finds no zip of a target. |
| `<names>` | `build` writes each file of the deliverable, and `pack` writes the zip, then each name in it. |
