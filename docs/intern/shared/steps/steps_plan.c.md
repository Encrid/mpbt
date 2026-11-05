# src/shared/steps/steps_plan.c

This file gives the variables of one artifact, so that the steps of its kind can run: `docs/extern/mpbt_kind.h.md`, *Steps*.

## The steps

The kind of the artifact is the row of `mpbt:Kind` whose `name` is the `kind` of the artifact.

1. A `variables_t` gets the variables of the project, and the keys of the target that the artifact names.
2. `{name}` is the name of the artifact, and `{target}` is the name of its target.
3. `{out}` is the folder `out` of the place.
4. `glob_files` finds the sources below the folder of the project.
5. If no file matches, the plan stops with its fault of `docs/extern/mpbt_artifact.h.md`, *Messages*.
6. `{output}` is the folder `out`, then `folder` of the artifact, then `output` of the kind with its variables replaced.
7. `{work}` is the folder `obj` in the folder `out`, then the name of the artifact.
8. `{defines}` puts `-D` before each item of `defines`, and `{include}` puts `-I` before each folder.
9. `{sources}`, `{link}` and `{manifest}` hold the items of their lists, with no change.
10. `{flags}` comes last: `flags` of the kind with its variables replaced, then `flags` of the artifact.
11. `variables_sort` sorts the entries again, since the artifact added its own.
12. `os_path_entry` looks for each file of `link`, in the order of the list. The first one that is not there is `missing`.

The texts of the artifact got their variables in the phase `read`. Here only the texts of the kind get them.

## The tree

A place can name a tree: a copy of `src` and of `include`, for example with the probes of `docs/extern/mpbt_branches.h.md`, *test --branches*.
Then `add_moved` puts a source or a folder of `include` in `src` or in `include` below the tree, at the same place. Each other path stays as it is.

## Functions

| Function | Result |
| --- | --- |
| `steps_plan` | The plan of one artifact, or 1 after a fault. |
| `add_list` | Adds a list variable, with a prefix before each item. |
| `add_text` | Adds a text variable. |
| `add_moved` | Adds a path, or its copy in the tree. |
| `find_missing` | The first file of `link` that is not there, or none. |
