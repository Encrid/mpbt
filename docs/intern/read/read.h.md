# src/read/read.h

This private header declares the settings of `read`, the state of a run of its system, and the functions that the files of `src/read` share.

## mpbt:Arguments

`read_arguments_t` is the type `mpbt:Arguments`: the settings of `read`. `src/host/host_arguments.c` gives one setting for each field.
Bridge fills the struct after `bridge_init`: https://github.com/Encrid/Bridge/blob/v0.4.1/docs/extern/bridge.h.md#the-settings-of-a-module.
`read_arguments_t` takes 96 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `root` | `bridge_text_t` | 0 | The folder of `--root`. |
| `target` | `bridge_text_t` | 8 | The target of `--target`. |
| `out` | `bridge_text_t` | 16 | The folder of `--out`. |
| `parts` | `bridge_text_t` | 24 | Each value of `--part`, as one line. |
| `tag` | `bridge_text_t` | 32 | The tag of `--tag`. |
| `sets` | `bridge_text_t` | 40 | Each value of `--set`, as one line. |
| `leave` | `bridge_text_t` | 48 | The name of `--leave`. |
| `filter` | `bridge_text_t` | 56 | The text of `-k`. |
| `commits` | `bridge_text_t` | 64 | The range of `--commits`. |
| `decide` | `bridge_text_t` | 72 | Each value of `--decide`, as one line. |
| `copies` | `uint32_t` | 80 | The number of `--copies`. |
| `rounds` | `uint32_t` | 84 | The number of `--rounds`. |
| `options` | `mpbt_options_t` | 88 | The bit of each option that the line gives. |
| `name` | `mpbt_command_name_t` | 92 | The command. |

Bytes 93 to 95 hold no field.
Each field has the name, the type and the offset of the field of `mpbt:Command` with the same name.
Only a list is different: a setting holds it as lines, `docs/extern/mpbt_project.h.md`, *Lists and maps*.

`READ_ARGUMENTS_FIELDS` gives the text of the fields. Thus the type and its descriptor come from one text, as for each type of `include`.

```text
{ bridge_text_t root; bridge_text_t target; bridge_text_t out; bridge_text_t parts; bridge_text_t tag; bridge_text_t sets; bridge_text_t leave; bridge_text_t filter; bridge_text_t commits; bridge_text_t decide; uint32_t copies; uint32_t rounds; mpbt_options_t options; mpbt_command_name_t name; }
```

## read_type_t

`read_type_t` is an enum of `uint32_t`. It has a constant for each row of `docs/intern/read/read.c.md`, *The components*, in the order of that table.
`declare` gives each type its slot in that order, from 0. Thus the constant of a type is its slot, and the module keeps no slot between 2 calls.
`READ_TYPE_COUNT` comes last, and counts the types.

## read_t

`read_t` is the state of one run of `bridge_read`. It lives until the system returns.

| Field | Value |
| --- | --- |
| `api` | The table that BB-Native gives to each export. |
| `arguments` | The settings of `read`, from the kept cell of `mpbt:Arguments`. |
| `config` | The values of mpbt and the files of the config, as one `toml_doc_t`. |
| `home` | The target of this machine, or none. |
| `target` | The target of the run. |
| `variables` | Each variable of the run: *read_variables_t*. |
| `run_variables` | The `variables_t` of the target of the run, which most texts use. |
| `rows` | The rows of the artifacts, in the order of the config: *read_row_t*. |
| `parts` | The names of the parts of the config, for the check of the part of a table. |
| `calls` | `malloc`, `calloc` and `realloc`, then the functions of `[fail.calls]` and of each file of its `with`. |
| `finding` | The place of the findings of `read`: its slot of `mpbt:Finding`, and the check `read`. |
| `findings` | How many findings the run wrote. A step that gives `false` with no finding ran out of memory. |

## read_variables_t

`read_variables_t` holds each variable of the run. A value stays as the config writes it, with its variables.

| Field | Value |
| --- | --- |
| `project` | The entries of the variables with `MPBT_SCOPE_PROJECT`. |
| `targets` | For each target, its name and the entries of its keys. |

A `variables_t` holds one entry for each name, so it holds the keys of one target only.
`read_get_variables` makes the `variables_t` of one target, and `variables_expand` replaces the variables of a value only when it reads the value.
Thus an entry can name a variable that comes later, and a key of a target gets the values of its own target.

## read_row_t

A row is one artifact, as up to 3 tables of the config. A key comes from the first table that has it.

| Field | Value |
| --- | --- |
| `variant` | The table of a variant, or none. |
| `row` | The table of `[[artifact]]` or of `[[modules]]`. |
| `module` | `[module]` for a row of `[[modules]]`, or none. |
| `name` | The name of the artifact, with its variables replaced. |
| `order` | The place of the row in `rows`, from 0. It becomes `order` of `mpbt:Artifact`. |

## Functions

| Function | File |
| --- | --- |
| `read_put_text`, `read_put_list`, `read_put_lines`, `read_get_arguments` | `read_world.c` |
| `read_copy_text`, `read_copy_list`, `read_copy_map`, `read_get_number`, `read_get_flag` | `read_keys.c` |
| `read_need_keys`, `read_add_missing`, `read_check_kind`, `read_check_value` | `read_key_rules.c` |
| `read_command` | `read_command.c` |
| `read_config`, `read_toml_file`, `read_with_tables` | `read_config.c` |
| `read_project`, `read_own`, `read_tools`, `read_write_variables` | `read_project.c` |
| `read_targets`, `read_write_targets` | `read_targets.c` |
| `read_variables`, `read_add_variable`, `read_get_variables`, `read_free_variables` | `read_variables.c` |
| `read_zig` | `read_zig.c` |
| `read_add_sources`, `read_sources`, `read_dependencies`, `read_agrees` | `read_sources.c` |
| `read_kinds` | `read_kinds.c` |
| `read_get_rows`, `read_artifacts` | `read_artifacts.c` |
| `read_paths` | `read_paths.c` |
| `read_check_parts`, `read_parts`, `read_check_part`, `read_compose`, `read_packages` | `read_compose.c` |
| `read_loads` | `read_load.c` |
| `read_settings` | `read_settings.c` |
| `read_checks`, `read_style_exceptions`, `read_branch_exceptions`, `read_get_system` | `read_checks.c` |
| `read_leaks`, `read_leak_exceptions` | `read_leaks.c` |
| `read_fail`, `read_is_listed` | `read_fail.c` |
| `read_tests` | `read_tests.c` |
| `read_case` | `read_case.c` |
| `read_write_run` | `read_case_run.c` |
| `read_write_claims` | `read_claims.c` |
| `read_write_script` | `read_script.c` |
| `read_files` | `read_files.c` |
