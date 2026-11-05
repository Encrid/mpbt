# src/pack/pack.h

This header holds the state of a call of `pack`, and the functions that the files of the module share.

## pack_state_t

| Field | Value |
| --- | --- |
| `command` | The value of `mpbt:Command`. |
| `project` | The value of `mpbt:Project`. |
| `rows` | The rows of `mpbt:Deliverable`, `mpbt:Part`, `mpbt:Package`, `mpbt:Artifact` and `mpbt:Built`. |
| `steps` | The `steps_t` of `src/shared/steps/steps.h`, for the proof. Its `fault` is the fault of the call. |

## Functions

| Function | File |
| --- | --- |
| `pack_declare` | `pack_world.c` |
| `pack_read_world` | `pack_world.c` |
| `pack_scan_files` | `pack_machine.c` |
| `pack_write_zip` | `pack_zip.c` |
| `pack_prove` | `pack_proof.c` |
| `pack_unpack` | `pack_unpack.c` |
