# src/read/read_tests.c

In the command `test` only, this file writes the rules of the groups, and reads each group of cases: `docs/extern/mpbt_case.h.md`, *Groups*.
The other commands run no case: `docs/extern/mpbt_command.h.md`, *The phases*.

## The rules

Each table of `[[test.rule]]` gives an entity with `mpbt:TestRule`: the text `lacks`, which it needs, and the list of the groups of `exempt`.
A rule is a table of the config, so its texts get their values from `run_variables`.
The test adds each rule to the claims of each case, so `read` does not add it to `mpbt:Claims`.

## The groups

1. The folder of the cases is `cases` of `mpbt:Tests`, a path from the root.
2. `glob_files` gives the files of the glob `<cases>/**/*.toml`, in the order of their paths.
3. `read_group` reads each file with `read_toml_file`, apart from the config.
4. The group takes its name from the path below the folder of the cases, with no `.toml`.
5. Each table of the list `case` goes to `read_case`, with its place in the file from 0.
6. `toml_doc_free` gives the memory of the file back after its last case.

A folder that is not there holds no group. The test writes the line of a folder with no case.
The texts of a case keep their variables, so `read` reads the cases with no `variables_t`.

## Functions

| Function | Result |
| --- | --- |
| `read_tests` | `true` after the rules and the cases of each group, or `false` and a finding. |
| `read_group` | `true` when each case of a group is written, or `false` and its finding. |
| `write_rules` | `true` after each entity of `mpbt:TestRule`, or `false` and a finding. |
