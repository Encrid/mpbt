# include/mpbt_file.h

`include/mpbt_file.h` gives `mpbt:File`: a file of the project, with its bytes, for the checks.

## The files of the project

The files of the project are each file that git tracks, and each file that git does not ignore.
If the root is not the top folder of a repository of git, they are each file under the root, except the files of `{build}`.
The files of `tests` are among them: `xref` checks a path of `tests` that a document cites, and `text` reads their words.
Each other check skips them, because their bytes can be the data of a case.
In the phase `read` of `check` and of `test`, mpbt writes an entity with `mpbt:File` for each file of the project.
Thus a module of wasm can check a file with no access to the OS.

## mpbt:File

`mpbt_file_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `path` | `bridge_text_t` | 0 | The path of the file, from the root, with `/`. |
| `bytes` | `bridge_text_t` | 8 | The bytes of the file. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:File` | `mpbt_file_t` | `mpbt_file_t_desc` | `MPBT_FILE_FIELDS` |

```text
{ bridge_text_t path; bridge_text_t bytes; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:File` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:File` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `git ls-files: <error>` | git cannot list the files of the project. |
| `<path>: <error>` | mpbt cannot read a file of the project. |
