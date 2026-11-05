# src/read/read_config.c

This file reads the files of the config into one `toml_doc_t`, over the values that mpbt holds: `docs/extern/mpbt_project.h.md`, *The files of the config*.
It also reads the files of a key `with`, and each file of TOML of the cases.

## The steps

1. `toml_doc_read` reads `src/read/values.toml`, which the module holds with `#embed`, as the document `mpbt`.
2. `read_toml_file` reads `.toolchain/project.toml` of the root, and `toml_doc_merge` merges it into that document. With no such file, nothing goes in.
3. `glob_files` of `src/shared/glob/glob.h` gives the files of the glob `.toolchain/config/**/*.toml`, in the order of their paths.
4. Each of these files goes into the document in the same way, in the order of the list.

A file that is not TOML gives the finding of `toml_doc_read`. Each clash gives the finding of `toml_doc_merge`.
The merge goes on after a clash, so one run gives each clash. The messages are in `docs/extern/mpbt_project.h.md`, *Messages*.

## A file of TOML

`read_toml_file` gives a path of the root to `path_join` and to `path_read` of `src/shared/path/path.h`. Then `toml_doc_read` reads the bytes.
The document takes as its name the path from the root, for the messages.
A file that is not there gives no document, and the caller decides whether that is a fault.
If `path_read` gives 1 for a file that `os_path_entry` finds, the read stops: `docs/extern/mpbt_command.h.md`, *Messages*.

## The tables of with

`read_with_tables` gives the table of a name, for example `[leaks]`, then the table of that name in each file of its key `with`.
A path of `with` gets the values of its variables, and `read_toml_file` starts it in `{root}` if it is not whole.
A file of `with` that is not there gives the finding of the header of the table: `docs/extern/mpbt_leaks.h.md`, *Messages*, or `docs/extern/mpbt_fail.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `read_config` | `true` and the config, or `false` after a finding. |
| `read_toml_file` | The document of one file, no document if the file is not there, or a finding. |
| `read_with_tables` | The table of a name, and the same table of each file of its `with`, or a finding. |
