# src/prose/prose.h

This private header declares `prose_t`, what the check `prose` holds while it reads one document, and the functions of `src/prose`.

## prose_t

| Field | Value |
| --- | --- |
| `api` | The `bridge_api_t` of BB-Native. |
| `check` | The name `prose` of `CHECKS_NAMES`, for the findings. |
| `path` | The `path` of the document, from `mpbt:File`. |
| `doc` | The document, from `markdown_read`. |
| `name` | `name` of `mpbt:Project`, for the title of the readme. |
| `limits` | The `mpbt_prose_check_t` of `mpbt:ProseCheck`. |

## Functions

| Function | File |
| --- | --- |
| `prose_check_tags` | `prose_tags.c` |
| `prose_check_units` | `prose_units.c` |
| `prose_check_readme` | `prose_readme.c` |
