# src/test/test.h

This private header declares the types that the files of `src/test` share, and the functions that one file gives to the others.

## test_world_t

What one invocation of the system reads from the world. The values stay in the shared memory, because no barrier comes before the system returns.

| Field | Value |
| --- | --- |
| `command`, `tests`, `leaks` | The singletons `mpbt:Command`, `mpbt:Tests` and `mpbt:Leaks`. `leaks` is none if the world has no `mpbt:Leaks`. |
| `rows` | A `test_rows_t` for each type of a table that the system reads, from `world_rows`. |
| `files`, `file_count` | The rows of `mpbt:File` as `files_item_t` of `src/shared/files`, in the order of `files_sort`. |
| `steps` | The `steps_t` of `src/shared/steps`, for the plans and the builds of the changed runs. |
| `cases`, `case_count` | The cases, linked and sorted by `test_link_cases`. |

`test_rows_t` holds the rows of one type: `ids`, the id of each entity, and `values`, where the value of each one is.
An artifact keeps its `mpbt:Built` beside its `mpbt:Artifact`, because the build attaches it to the same entity.
`files_find` gives the bytes of a file by its path.

## test_case_t and test_use_t

| Field of `test_case_t` | Value |
| --- | --- |
| `id`, `item` | The entity of the case, and its `mpbt:Case`. |
| `claims` | Its `mpbt:Claims`. A false variant has the same claims. |
| `use` | What a run of the case uses: a `test_use_t`. |
| `broken` | What a run of its false variant uses: a `test_use_t`. |
| `chosen` | `true` if `--part` and `-k` keep the case. |

| Field of `test_use_t` | Value |
| --- | --- |
| `id`, `run` | The entity of the case or of its false variant, and its `mpbt:Run`. |
| `helper_claims` | Its `mpbt:HelperClaims`, or none. |
| `steps`, `step_count` | The steps of its script, in the order of the field `order`. |

## test_t

One run of the cases. A plain `test` makes one, and a second one for the run `fail` if it needs it.

| Field | Value |
| --- | --- |
| `world` | The `test_world_t` of the invocation. |
| `kind` | `TEST_PLAIN`, `TEST_FAIL`, `TEST_BRANCHES` or `TEST_LEAKS`, items of `enum test_kind : uint8_t` from 1. |
| `name` | The name of the folder of a changed run in `{build}`: `fail`, `branches` or `leaks`. A plain run has none. |
| `out`, `variables` | The folder `{out}` of the run, and the variables of the run with that `{out}`. |
| `outputs` | The file of each artifact of the run, by the name of the artifact. |
| `broken`, `copies` | `true` with `--break`, and the copies of each case. |
| `failing` | The run `fail` of a plain run, or none. |
| `hits` | The file of the hits of the run `branches`, or none. |
| `said` | The outputs of the verdicts, for `said.txt`. |
| `finding` | The `finding_t` of `src/shared/finding/finding.h`: the slot of `mpbt:Finding`, and the check `test`. |
| `failed` | `true` if a call failed that has no message of its own. Then the system gives 1. |

## test_copy_t, test_end_t and test_running_t

| Field of `test_copy_t` | Value |
| --- | --- |
| `test`, `item`, `use` | The run, the case, and what the copy uses. |
| `number` | The number of the copy, from 0. |
| `folder`, `variables` | The folder `{case}`, and the variables of the run with `{case}`, and `{port}` if a text of the case names it. |
| `ends` | The end of the command and the end of the helper: 2 items of `test_end_t`. |
| `fault`, `failed` | The text of a fault that stops the test, in a `buffer_t`, and whether a call failed with no message. |
| `verdict`, `passed` | The verdict of the copy, and whether the copy passes. |

`test_end_t` holds the end of one command: `status`, an `int64_t`, `late`, `true` if the timer stopped the command, and `output` in a `buffer_t`.
`test_running_t` holds a command that runs: its `os_process_t`, its `test_timer_t`, its output, and `seen`, the bytes of the output that a step `wait` checked.
`test_timer_t` holds the thread of the timer, its `os_event_t`, the process, and `late`, an `atomic_bool`.

## The faults

On the thread of the system, a fault goes at once to `finding_write`, or to `finding_format` for a text with values.
Each fault with a place sets its path, its line and its column in `finding` first.
A thread of a copy or of a dump calls no entry of Bridge. It keeps its fault in its own slot, and the system writes it after the join.
Each function that can stop the run gives `false` to stop it, after its finding or after it set `failed`.

## The syntax tree

| Field of `test_loc_t` | Value |
| --- | --- |
| `offset`, `tok_len` | The byte of the location in its file, and the length of its token. |
| `has_offset` | `false` for a location with no `offset`. |
| `file` | The path that `test_get_path` gives, or none outside `src` and `include`. |
| `spelling`, `expansion` | For a location in a macro: the two locations of `spellingLoc` and `expansionLoc`. |
| `is_macro_arg` | `true` if `isMacroArgExpansion` marks the expansion. |

| Field of `test_node_t` | Value |
| --- | --- |
| `kind`, `name`, `opcode` | The keys `kind`, `name` and `opcode` of the node. |
| `type`, `plain` | `qualType` of its type, and `desugaredQualType`, or `qualType` if the dump gives no `desugaredQualType`. |
| `referenced` | The name of `referencedDecl`. |
| `storage`, `implicit`, `constant` | `storageClass`, `isImplicit` and `constexpr`. |
| `loc`, `begin`, `end` | `loc`, and the two ends of `range`. |
| `children`, `child_count` | The items of `inner`. An empty object stays as a child with no node, so each child keeps its place. |
| `parent` | The node that holds this one in `inner`. |

`test_visit_t` is the function that `test_read_tree` calls for each node that it keeps at the top of a tree, and the value of that function.

## The rewrite

| Type | Value |
| --- | --- |
| `test_decl_t` | A declaration: the type of the result, the plain and the spelled type of each parameter, and `variadic`. |
| `test_used_t` | The functions of a list that one file uses, the `test_decl_t` of each, and the end of each callback that the file defines. |
| `test_edit_t` | A probe: its kind, its bytes in the file, its depth, and the byte that the report shows. |
| `test_effect_t` | What a counted function does: take, give or move, the kind, the place, and whether the place must be a pointer. |

## Functions

| Function | File |
| --- | --- |
| `test_read_world`, `test_free_world` | `test_world.c` |
| `test_link_cases`, `test_get_use` | `test_cases.c` |
| `test_make_variables`, `test_add_variables`, `test_free_variables` | `test_variables.c` |
| `test_pick_cases` | `test_groups.c` |
| `test_run_plain` | `test_plain.c` |
| `test_find_item`, `test_check_linked` | `test_artifacts.c` |
| `test_run_rounds` | `test_rounds.c` |
| `test_run_copies` | `test_copies.c` |
| `test_run_case` | `test_case.c` |
| `test_place`, `test_write_file` | `test_place.c` |
| `test_make_env`, `test_free_env` | `test_env.c` |
| `test_start`, `test_read`, `test_wait_line`, `test_type`, `test_end` | `test_process.c` |
| `test_timer_start`, `test_timer_stop` | `test_timer.c` |
| `test_do_script` | `test_script.c` |
| `test_hold_claims` | `test_claims.c` |
| `test_hold_output`, `test_hold_files` | `test_claims_files.c` |
| `test_check_patterns`, `test_hold_patterns` | `test_patterns.c` |
| `test_make_said_pattern` | `test_said_pattern.c` |
| `test_judge`, `test_say_case`, `test_say_group` | `test_verdict.c` |
| `test_check_said` | `test_said.c` |
| `test_find_messages` | `test_messages.c` |
| `test_run_changed`, `test_write_copies` | `test_changed.c` |
| `test_find_sources` | `test_sources.c` |
| `test_dump_all` | `test_dump.c` |
| `test_read_tree` | `test_tree_read.c` |
| `test_get_path`, `test_is_macro`, `test_get_child`, `test_free_tree` | `test_tree.c` |
| `test_find_used`, `test_get_used` | `test_found.c` |
| `test_find_included` | `test_included.c` |
| `test_write_rename`, `test_write_pops`, `test_write_signed`, `test_write_line` | `test_rename.c` |
| `test_get_calls`, `test_write_layer` | `test_fail.c` |
| `test_needs_fail`, `test_run_fail` | `test_fail_run.c` |
| `test_run_branches`, `test_write_probes` | `test_probes.c` |
| `test_walk_probes` | `test_probe_walk.c` |
| `test_probe_condition`, `test_get_place` | `test_probe_condition.c` |
| `test_trace_body`, `test_is_partial` | `test_probe_trace.c` |
| `test_write_probed` | `test_probe_write.c` |
| `test_get_parts`, `test_write_hits`, `test_read_hits` | `test_hits.c` |
| `test_report_branches` | `test_probe_report.c` |
| `test_run_leaks`, `test_write_counts` | `test_count.c` |
| `test_list_effects`, `test_fit_effects` | `test_effects.c` |
| `test_write_counted` | `test_count_write.c` |
| `test_report_leaks` | `test_count_report.c` |
