# src/shared/steps/steps_make.c

This file makes one artifact by the steps of `docs/extern/mpbt_artifact.h.md`, *The build*, and gives the values of `mpbt:Built`.

## The steps

1. `steps_plan` gives the variables of the artifact, and `missing`.
2. `os_folder_make` makes the 2 folders: of the output, and of `{work}`.
3. If `missing` names a file and the kind has no `unlinked` steps, a fault stops the build.
4. If `missing` names a file, `say` writes the line of an artifact that is not linked.
5. Then `steps_do` does the `unlinked` steps of the kind. The result has no file.
6. Else `steps_do` does the `steps` of the kind.
7. Then `copy_file` copies each file of `beside` to the folder that holds the output.
8. The files of the result are the output, then the copies of `beside`.

A file of `beside` that does not read is a fault. So is a folder or a copy that the system does not let mpbt write.
The messages are in `docs/extern/mpbt_kind.h.md`, *Messages*, and in `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `steps_make` | The values of `mpbt:Built`, or 1 after a fault. |
| `copy_besides` | The copies of the files of `beside`, or 1 after a fault. |
