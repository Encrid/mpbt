# src/shared/steps/steps.h

This header declares the build of one artifact by the steps of its kind: `docs/extern/mpbt_artifact.h.md`, *The build*.
The module `build` makes the artifacts and the modules of `[[load]]` with it. `pack` makes its proof, and `test` makes the copies of its changed runs.

## steps_t

`steps_t` holds what the build of an artifact reads. Each caller fills it from the rows of its own call.

| Field | Value |
| --- | --- |
| `variables` | The rows of `mpbt:Variable`. |
| `targets` | The rows of `mpbt:Target`. |
| `kinds` | The rows of `mpbt:Kind`, each with the id of its entity. |
| `steps` | The rows of `mpbt:Step`. |
| `root` | `{root}`, a whole path. |
| `fault` | The text of the first fault, or no bytes. After a fault, no other work starts. |

No function of this part calls Bridge, so 3 modules can link it. The caller writes `fault` with `finding_write`.

## steps_input_t

`steps_input_t` holds the texts of one artifact, as `docs/extern/mpbt_artifact.h.md`, *mpbt:Artifact*, gives them.

| Field | Value |
| --- | --- |
| `name`, `kind`, `folder`, `target` | A `lists_item_t` for each text. |
| `sources`, `include`, `defines`, `flags`, `link`, `beside`, `manifest` | A `steps_list_t` for each list: `items`, an array of `lists_item_t`, and `count`. |
| `unstamped` | `unstamped` of the artifact. |

`steps_read_input` makes an input from a row of `mpbt:Artifact`, for `build` and for `test`. `pack` makes the input of its proof itself, since the proof has no row.

## steps_place_t

| Field | Value |
| --- | --- |
| `out` | The folder of the outputs. The steps get it as `{out}`, and `{work}` is in its folder `obj`. |
| `tree` | A copy of `src` and of `include` that the build reads, or no bytes: `docs/intern/shared/steps/steps_plan.c.md`. |

| Caller | `out` | `tree` |
| --- | --- | --- |
| The system `build` of `build` | `{out}` | No bytes. |
| The system `load_artifacts` of `build` | `<build>/load` | No bytes. |
| The proof of `pack` | `{out}/proof/host` | No bytes. |
| A changed run of `test` | `<build>/<run>/<target>` | `<build>/<run>/tree` |

## steps_plan_t

| Field | Value |
| --- | --- |
| `kind` | The row of the kind of the artifact. |
| `variables` | The `variables_t` of the artifact. |
| `output` | The file of the artifact. |
| `missing` | No bytes, or the file of `link` that the plan did not find. |

## steps_made_t

`steps_made_t` holds the 3 values of `mpbt:Built` for one artifact: `docs/extern/mpbt_artifact.h.md`, *mpbt:Built*.

## Functions

| Function | File |
| --- | --- |
| `steps_read_input` | `steps_input.c` |
| `steps_free_input` | `steps_input.c` |
| `steps_plan` | `steps_plan.c` |
| `steps_make` | `steps_make.c` |
| `steps_do` | `steps_do.c` |
| `steps_run` | `steps_run.c` |
| `steps_get_caches` | `steps_run.c` |
