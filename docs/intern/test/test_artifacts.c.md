# src/test/test_artifacts.c

This file gives the file of an item that a case copies, and checks that the cases have each artifact that they need.

## The file of an item

An item of `folders` or of a step `put` is the name of an artifact, or a path from the root: `docs/extern/mpbt_case.h.md`, *[[case]]*.

1. The item gets the variables of the copy.
2. If it is the name of an artifact of the run, it gives the file of that artifact in `outputs`.
3. Else `path_join` gives the path of the item in `{root}`.

A case of the run `fail` gets the artifacts of that run. Thus the copy of a program is the program with the layer.

## The linked artifacts

`test_check_linked` reads whether each artifact of the run is linked.
In a plain run, `linked` of `mpbt:Built` tells it. In a changed run, the build of the copies tells it: `test_changed.c`.
If one or more is not linked, one finding names them all, with its message of `docs/extern/mpbt_artifact.h.md`, *Messages*.
The run then stops, because a case of such an artifact would test a file that is not there.

## Functions

| Function | Result |
| --- | --- |
| `test_find_item` | The file of an item, or `false` after a finding of its variables. |
| `test_check_linked` | `true`, or `false` after the finding. |
| `find_output` | The file of the artifact of a name, or none. |
