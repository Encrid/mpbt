# src/take/take.h

This private header declares `take_t`, `take_dependency_t`, and the functions that the files of `src/take` share.

## take_t

`take_t` is the state of one run of `bridge_take`. It lives until the system returns.

| Field | Value |
| --- | --- |
| `api` | The table of the backend, as `bridge_take` gets it. |
| `root` | The value of `{root}`, from the rows of `mpbt:Variable`. |
| `dependencies` | The rows of `mpbt:Dependency`, in their order: *take_dependency_t*. |
| `agrees` | The rows of `mpbt:Agree`, in their order. |
| `copies` | The pairs of a file and its copy to write, after each check passed. |
| `finding` | The place of the findings of `take`: its slot of `mpbt:Finding`, and the check `take`. |
| `findings` | 0 until the run writes a finding. Then it counts the findings. |

## take_dependency_t

| Field | Value |
| --- | --- |
| `name`, `make`, `optional` | The fields of the row. |
| `from`, `into` | The folders of the row, after `{root}` if they are not whole. |
| `list` | The path of the list: `from`, `/`, then `list` of the row. |
| `keys` | The lines `<key> <value>` of the list, as pairs of texts, in their order. |
| `files` | The lines `<digest>  <file>` of the list, as pairs of texts, in their order. |
| `taken` | `true` if the list was there. A dependency that is not taken does not count in a rule. |

## Functions

| Function | File |
| --- | --- |
| `take_get_world`, `take_free_world` | `take_world.c` |
| `take_make` | `take_make.c` |
| `take_read_list` | `take_list.c` |
| `take_agree` | `take_agree.c` |
| `take_check_copies`, `take_write_copies` | `take_copies.c` |
