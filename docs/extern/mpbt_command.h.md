# include/mpbt_command.h

`include/mpbt_command.h` gives `mpbt:Command`: the command of a run of mpbt, and its options.
This document also gives the phases that each command runs.

## The commands

```sh
mpbt <command> [<option> ...]
```

| Command | Phases | Result |
| --- | --- | --- |
| `fetch` | `read`, `fetch`, `take`, `report` | Gets zig and each source, then takes each dependency. |
| `build` | `read`, `load`, `take`, `build`, `compose`, `report` | Builds the artifacts that ship, then composes the deliverable. |
| `pack` | `read`, `load`, `take`, `build`, `compose`, `pack`, `report` | Builds as `build` does, then writes the zip and proves the package. |
| `join` | `read`, `load`, `join`, `report` | Joins the zips of all the targets of a part into one zip. |
| `test` | `read`, `load`, `take`, `build`, `test`, `report` | Builds each artifact, also those of the tests, then runs the cases. |
| `check` | `read`, `load`, `check`, `report` | Runs each check of the project. |
| `clean` | `read`, `clean`, `report` | Removes what the build made, but keeps the folder of mpbt and the sources. |
| `distclean` | `read`, `clean`, `report` | Removes the output folder, with all that it holds. |
| `cla` | `read`, `cla`, `report` | Decides whether the author of a pull request signed `cla.md`. |
| `runner` | `read`, `runner`, `report` | Writes the commands that give a runner of GitHub the needs of `[ci]`. |

mpbt ends with 0 if no phase writes a finding, and else with 1: `docs/extern/mpbt_finding.h.md`.
It also ends with 1 when Bridge refuses a call, after the record that tells why, and when a signal stops it.
A command line that *The options* refuses writes its message, and mpbt ends with 2.

## The options

| Option | Commands | Result |
| --- | --- | --- |
| `--root <folder>` | All but `cla` | The folder of the project. The default is the current folder. |
| `--target <target>` | All but `cla` | The target of the run: `docs/extern/mpbt_target.h.md`, *The targets*. |
| `--part <part>` | `build`, `pack`, `test`, `join` | Acts on this part, and on each part that it uses. It can come more than one time. |
| `--tag <tag>` | `build`, `pack`, `test`, `join` | A tag `<part>-v<major>.<minor>.<patch>` gives `--part <part>`. A tag `v<major>.<minor>.<patch>` gives no part. |
| `--debug` | All but `cla` | Builds with the values of debug: `docs/extern/mpbt_project.h.md`, *[variables]*. |
| `--out <folder>` | All but `cla` | The output folder, `{build}`. The default is the folder `build` of the root. |
| `--set <name>=<value>` | All but `cla` | Gives a key of `[variables]` this value. It can come more than one time. |
| `--leave <name>` | `build`, `pack` | Leaves the file `<name>` out of the deliverable and out of its zip. |
| `--break` | `test` | Runs the false variant of each case. Each case must then fail. |
| `-k <text>` | `test` | Runs only the cases whose name holds `<text>`. |
| `--copies <number>` | `test` | The copies of each case that run together, in place of `[test] copies`. |
| `--rounds <number>` | `test` | The number of rounds of all the cases, one after the other. |
| `--branches` | `test` | Writes each branch that no case reaches: `docs/extern/mpbt_branches.h.md`. |
| `--leaks` | `test` | Writes each case that keeps a resource: `docs/extern/mpbt_leaks.h.md`. |
| `--commits <range>` | `check` | Checks the messages of the commits of this range of git. |
| `--decide <author> <signed> [<by> <said>]` | `cla` | Writes the decision, and changes nothing. `<signed>` holds the names of the record, with commas between them. `<by>` is the author of a comment, and `<said>` is its text. |

`--branches` and `--leaks` run each case one time. Thus they refuse `--break`, `--copies` and `--rounds`, and `--leaks` also refuses `--branches`.

## The phases

A module of a project can join each phase after `load`: `docs/extern/mpbt_load.h.md`.

| Phase | Work |
| --- | --- |
| `read` | Writes `mpbt:Command`, then reads the config into its components. In `test`, it also reads the cases. In `cla`, it writes only `mpbt:Command`. |
| `load` | Builds each artifact of `[[load]]` for this machine, then loads each module of `[[load]]`. With no `[[load]]`, it does nothing. |
| `fetch` | Gets zig and the sources. |
| `take` | Takes the dependencies. |
| `build` | Builds the artifacts. |
| `compose` | Writes `package.txt`, and composes the deliverable. |
| `pack` | Writes the zip, and proves the package. |
| `join` | Joins the zips of the targets. |
| `test` | Runs the cases, then checks the messages of the code. |
| `check` | Runs the checks. |
| `clean` | Removes the output. |
| `cla` | Decides about the agreement. |
| `runner` | Writes the commands for the runner. |
| `report` | Writes each finding, and sets the exit status. |

After a phase that writes a finding, mpbt runs `report` and stops.

## The agreement

The workflow `cla` runs `mpbt cla` when a pull request opens or changes, and when a person writes a comment on it.
mpbt reads the pull request from the event of GitHub, as data, and runs no code of it.

| Author | Action | The pull request |
| --- | --- | --- |
| A name of the record | Nothing | Passes. |
| An author whose comment is only the sentence | Record | Passes. |
| Each other author | Ask | Fails. |

The sentence is `I have read cla.md and I sign it.`, with no other text in the comment.
The record is `signatures.json` on the branch `cla-signatures`: a list of items with the keys `name`, `day` and `pull_request`.
The commit of a record is `docs: record the agreement of <author>`. The first record makes the branch from the default branch.
mpbt asks one time in each pull request, with this comment:

```text
Thank you for this pull request.
Before we can merge it, @<author> must sign the agreement cla.md at the root of this repository.
The agreement is a licence. You keep the copyright of your work.
The holder can also sell the project under different terms, and these terms can include your contribution.
Read cla.md before you sign it.
To sign it, write a comment that contains only this sentence:

    I have read cla.md and I sign it.
```

## mpbt:Command

`mpbt:Command` holds the command line of the run. It is a singleton.
`mpbt_command_t` takes 96 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `root` | `bridge_text_t` | 0 | The folder of `--root`. |
| `target` | `bridge_text_t` | 8 | The target of `--target`. |
| `out` | `bridge_text_t` | 16 | The folder of `--out`. |
| `parts` | `bridge_text_t` | 24 | A list: each part of `--part`, and the part of `--tag`. |
| `tag` | `bridge_text_t` | 32 | The tag of `--tag`. |
| `sets` | `bridge_text_t` | 40 | A map: each name of `--set`, then its value. |
| `leave` | `bridge_text_t` | 48 | The name of `--leave`. |
| `filter` | `bridge_text_t` | 56 | The text of `-k`. |
| `commits` | `bridge_text_t` | 64 | The range of `--commits`. |
| `decide` | `bridge_text_t` | 72 | A list: the 2 or 4 values of `--decide`. |
| `copies` | `uint32_t` | 80 | The number of `--copies`. |
| `rounds` | `uint32_t` | 84 | The number of `--rounds`. |
| `options` | `mpbt_options_t` | 88 | The options that the command line gives. |
| `name` | `mpbt_command_name_t` | 92 | The command. |

Bytes 93 to 95 hold no field.
A field of an option that the command line does not give holds no bytes, or 0.
Its lists and maps: `docs/extern/mpbt_project.h.md`, *Lists and maps*.

### mpbt:mpbt_command_name_t

`mpbt_command_name_t` is an enum of `uint8_t`.

| Constant | Value | Command |
| --- | --- | --- |
| `MPBT_COMMAND_FETCH` | 1 | `fetch` |
| `MPBT_COMMAND_BUILD` | 2 | `build` |
| `MPBT_COMMAND_PACK` | 3 | `pack` |
| `MPBT_COMMAND_JOIN` | 4 | `join` |
| `MPBT_COMMAND_TEST` | 5 | `test` |
| `MPBT_COMMAND_CHECK` | 6 | `check` |
| `MPBT_COMMAND_CLEAN` | 7 | `clean` |
| `MPBT_COMMAND_DISTCLEAN` | 8 | `distclean` |
| `MPBT_COMMAND_CLA` | 9 | `cla` |
| `MPBT_COMMAND_RUNNER` | 10 | `runner` |

### mpbt:mpbt_options_t

`mpbt_options_t` is a bitmask of `uint32_t`. A bit is set if the command line gives its option.

| Constant | Value | Option |
| --- | --- | --- |
| `MPBT_OPTION_ROOT` | `0x1` | `--root` |
| `MPBT_OPTION_TARGET` | `0x2` | `--target` |
| `MPBT_OPTION_PART` | `0x4` | `--part` |
| `MPBT_OPTION_TAG` | `0x8` | `--tag` |
| `MPBT_OPTION_DEBUG` | `0x10` | `--debug` |
| `MPBT_OPTION_OUT` | `0x20` | `--out` |
| `MPBT_OPTION_SET` | `0x40` | `--set` |
| `MPBT_OPTION_LEAVE` | `0x80` | `--leave` |
| `MPBT_OPTION_BREAK` | `0x100` | `--break` |
| `MPBT_OPTION_FILTER` | `0x200` | `-k` |
| `MPBT_OPTION_COPIES` | `0x400` | `--copies` |
| `MPBT_OPTION_ROUNDS` | `0x800` | `--rounds` |
| `MPBT_OPTION_BRANCHES` | `0x1000` | `--branches` |
| `MPBT_OPTION_LEAKS` | `0x2000` | `--leaks` |
| `MPBT_OPTION_COMMITS` | `0x4000` | `--commits` |
| `MPBT_OPTION_DECIDE` | `0x8000` | `--decide` |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | `mpbt_command_name_t` | `mpbt_command_name_t_desc` | `MPBT_COMMAND_NAME_VALUES` |
| `mpbt:mpbt_options_t` | `mpbt_options_t` | `mpbt_options_t_desc` | `MPBT_OPTIONS_VALUES` |
| `mpbt:Command` | `mpbt_command_t` | `mpbt_command_t_desc` | `MPBT_COMMAND_FIELDS` |

```text
uint8_t { MPBT_COMMAND_FETCH = 1, MPBT_COMMAND_BUILD = 2, MPBT_COMMAND_PACK = 3, MPBT_COMMAND_JOIN = 4, MPBT_COMMAND_TEST = 5, MPBT_COMMAND_CHECK = 6, MPBT_COMMAND_CLEAN = 7, MPBT_COMMAND_DISTCLEAN = 8, MPBT_COMMAND_CLA = 9, MPBT_COMMAND_RUNNER = 10 }
uint32_t { MPBT_OPTION_ROOT = 0x1, MPBT_OPTION_TARGET = 0x2, MPBT_OPTION_PART = 0x4, MPBT_OPTION_TAG = 0x8, MPBT_OPTION_DEBUG = 0x10, MPBT_OPTION_OUT = 0x20, MPBT_OPTION_SET = 0x40, MPBT_OPTION_LEAVE = 0x80, MPBT_OPTION_BREAK = 0x100, MPBT_OPTION_FILTER = 0x200, MPBT_OPTION_COPIES = 0x400, MPBT_OPTION_ROUNDS = 0x800, MPBT_OPTION_BRANCHES = 0x1000, MPBT_OPTION_LEAKS = 0x2000, MPBT_OPTION_COMMITS = 0x4000, MPBT_OPTION_DECIDE = 0x8000 }
{ bridge_text_t root; bridge_text_t target; bridge_text_t out; bridge_text_t parts; bridge_text_t tag; bridge_text_t sets; bridge_text_t leave; bridge_text_t filter; bridge_text_t commits; bridge_text_t decide; uint32_t copies; uint32_t rounds; mpbt_options_t options; mpbt_command_name_t name; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_options_t` | `BRIDGE_BITMASK` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Command` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare the enum and the bitmask first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Command` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `name a command: fetch build pack join test check clean distclean cla runner` | The command line names no command of the table. |
| `<option> is not an option of <command>` | The command takes no such option. |
| `<option> needs a value` | The command line ends after an option that takes a value. |
| `<option> takes a whole number from 1: <value>` | `--copies` or `--rounds` gets a different value. |
| `the tag <tag> is not v<major>.<minor>.<patch> or <part>-v<major>.<minor>.<patch>` | `--tag` has a different form. |
| `--branches runs each case one time: it takes no --break, --copies or --rounds` | `--branches` comes with one of these options. |
| `--leaks runs each case one time: it takes no --break, --copies, --rounds or --branches` | `--leaks` comes with one of these options. |
| `usage: mpbt cla --decide <author> <signed> [<by> <said>]` | `--decide` gets a number of values that is not 2 or 4. |
| `nothing to clean: <folder> is not there` | `clean` or `distclean` finds no output folder. |
| `cleaned <folder>` | `clean` or `distclean` removed the files. |
| `clean refuses <folder>, which holds the root` | `--out` names the root of the project, or a folder above it. `clean` and `distclean` remove nothing. |
| `clean cannot remove <path>` | The system refuses to remove a file or a folder of the output. |
| `clean cannot read <folder>` | The system refuses to list a folder of the output. |
| `<author> has signed cla.md` | The record names the author. The pull request passes. |
| `<author> signs cla.md` | The author wrote the sentence of the agreement. mpbt records the author, and the pull request passes. |
| `<author> has not signed cla.md` | mpbt asks the author to sign. The pull request fails. |
| `<action>, <verdict>: <reason>` | `--decide` writes the action, `passes` or `fails`, and the reason. |
| `<method> <path> answered <code>: <text>` | The API of GitHub answers with an error that is not 404, or with an answer that lacks a value that `cla` reads. |
| `<name> is not set, and cla needs it` | The environment lacks `GITHUB_EVENT_PATH`, `GITHUB_REPOSITORY` or `GITHUB_TOKEN`. |
| `cla cannot read the event <path>` | The file of the event of GitHub does not read. |
| `<path> is not the JSON of an event of GitHub: <reason>` | The event is not JSON, or lacks a key that `cla` reads. Then `<reason>` is `no` and the key, for example `no issue.number`. |
| `curl is not on the path, and cla needs it` | This machine has no `curl`. |
| `<method> <path>: curl ended with <status>` | `curl` gives no answer of the API of GitHub. |
| `<program> did not start` | The system did not start a program, for example a step of a kind, a tool, or a case. The program can be absent. |
| `mpbt cannot read <path>` | The system refuses to read a file that a phase needs. |
| `mpbt cannot write <path>` | The system refuses to write a file or make a folder that a phase needs. |
| `a signal came: mpbt stops after this phase` | An interrupt, a termination or a hang-up came. A second signal ends mpbt at once, with 1. |
| `mpbt cannot write its modules into <folder>` | The folder `{toolchain}/modules` does not take a file. |
