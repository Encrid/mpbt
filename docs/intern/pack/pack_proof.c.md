# src/pack/pack_proof.c

This file proves the package of one deliverable with its `proof`: `docs/extern/mpbt_compose.h.md`, *[package]*.

## The steps

The package of a deliverable is the `mpbt:Package` whose `part` is its part, with no bytes for the project. With no `proof`, `pack_prove` does nothing.

1. `os_path_remove` removes `{out}/proof`, and `pack_unpack` unpacks the zip into it. A refused removal stops the proof.
2. The proof is an artifact of the kind `program` with the name `proof`. Its one source is the file of `proof`.
3. Its `include` holds `{out}/proof/include`, each folder below it in the order of the paths, then `include` of the package.
4. Its `link` holds each archive of the deliverable in `{out}/proof`, then `link` of the package.
5. `steps_make` builds it for the target of the run, in the place of the proof.
6. If the target has `here` at `true`, `run_command` runs the program in the folder of the project.
7. A status that is not 0 is a fault, which `run_add_fault` writes. With 0, `say` writes the output.
8. `say` then writes the line of a proof that ran, or of a proof that was built.

The place is in `docs/intern/shared/steps/steps.h.md`, *steps_place_t*. The lines are in `docs/extern/mpbt_compose.h.md`, *Messages*.
A refused removal gives the fault of a folder that mpbt cannot write: `docs/extern/mpbt_command.h.md`, *Messages*.
An archive of the deliverable is the output of an artifact of the kind `archive` that ships. The zip holds it at the top, so its path in `{out}/proof` is its name.

## Functions

| Function | Result |
| --- | --- |
| `pack_prove` | 0 when the proof ran or was built, or 1 after a fault. |
| `add_includes` | Adds the folders of the headers of the proof. |
| `add_folders` | Adds each folder below a folder, in the order of the paths. |
| `add_links` | Adds the archives of the deliverable, then `link` of the package. |
| `run_proof` | Runs the program of the proof, and writes its output or its fault. |
