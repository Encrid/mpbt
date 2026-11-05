# mpbt

Builds, tests and checks a project in C23 with zig, as one program for each target.

## Install

Each release of mpbt holds a program for each target. Its `sha256.txt` gives the digest of each program.
Download the program of the target of your machine, and compare its digest with `sha256.txt`.
mpbt needs `curl` and `git` on the path. The command `fetch` gets zig.

## Usage

```sh
mpbt <command> [<option> ...]
```

Run `fetch` first in the folder of a project, then `build`, `test` or `check`.
`docs/extern/mpbt/command.h.md` gives the 10 commands, their options and their phases.
mpbt reads the config of a project from `.toolchain/project.toml` and `.toolchain/config`.

## API

mpbt is a host of Bridge, and each of its steps and checks is a module.
The headers of `include/mpbt` declare the components that these modules share, and a module of a project can read and write them: `docs/extern/mpbt/load.h.md`.

| Header | Types of |
| --- | --- |
| `include/mpbt/command.h` | The command and its options. |
| `include/mpbt/project.h` | The project, its variables and the common rules. |
| `include/mpbt/target.h` | The targets. |
| `include/mpbt/source.h` | The sources that `fetch` gets. |
| `include/mpbt/dependency.h` | The dependencies and their rules. |
| `include/mpbt/kind.h` | The kinds of artifact and their steps. |
| `include/mpbt/artifact.h` | The artifacts and what the build made. |
| `include/mpbt/compose.h` | The deliverable, the parts and the proof. |
| `include/mpbt/case.h` | The tests and the cases. |
| `include/mpbt/check.h` | The settings and exceptions of the checks. |
| `include/mpbt/branches.h` | The exceptions of the branches. |
| `include/mpbt/leaks.h` | The count of the resources. |
| `include/mpbt/fail.h` | The calls that a case makes fail. |
| `include/mpbt/ci.h` | The needs of a runner. |
| `include/mpbt/load.h` | The modules of a project. |
| `include/mpbt/file.h` | The files that the checks read. |
| `include/mpbt/finding.h` | The faults and the report. |

## Contributing

| Document | Content |
| --- | --- |
| `docs/contributing/needs.md` | The needs that each decision meets. |
| `docs/contributing/decisions.md` | The steps of a decision. |
| `docs/contributing/coding_style.md` | How to write the code. |
| `docs/contributing/documentation_style.md` | How to write the documents. |
| `docs/contributing/tests.md` | How to write the tests. |
| `docs/contributing/commits.md` | How to write a commit. |
| `docs/contributing/pull_request.md` | How to write a pull request. |
| `docs/contributing/agreement.md` | The agreement `cla.md`, which each contributor signs. |

## License

The GNU Affero General Public License, version 3 only. The file `license` holds the text.
Each source of third-party code has its notice in `third_party/<source>/license`.
