# src/prose/prose_readme.c

This file checks `readme.md` against the rules of Standard Readme that a program can check: https://github.com/RichardLitt/standard-readme.

## The rules

1. The first line is `#`, a space, and `name` of `mpbt:Project`, with no other byte.
2. The first line with text after the title is the description. A heading there is no description.
3. The count of the characters of the description is at most `description` of `mpbt:ProseCheck`. A character of UTF-8 counts one time.
4. Each heading of level 2 is a section. The sections follow the ranks of *The order*.
5. The readme has the 4 sections Install, Usage, Contributing and License.

The file keeps the last section that was in the right order. A section with a lower rank than that section gives a finding.
A section with a title that is not in the table is an extra section, with the rank 5.
With no `name` in `mpbt:Project`, the title is not checked. Then the finding is the one of `docs/extern/mpbt_project.h.md`, *Messages*, for `[project] name`, with the path `.toolchain/project.toml`.

## The order

| Section | Rank |
| --- | --- |
| Table of Contents | 0 |
| Security | 1 |
| Background | 2 |
| Install | 3 |
| Usage | 4 |
| An extra section | 5 |
| API | 6 |
| Maintainer, Maintainers | 7 |
| Thanks, Credits, Acknowledgements | 8 |
| Contributing | 9 |
| License | 10 |

The messages are in `docs/extern/mpbt_check.h.md`, *prose*.

## Functions

| Function | Result |
| --- | --- |
| `prose_check_readme` | A finding for each fault of the readme. |
| `get_rank` | The rank of the title of a section. |
