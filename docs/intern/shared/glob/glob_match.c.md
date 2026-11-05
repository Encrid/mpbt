# src/shared/glob/glob_match.c

This file tells whether a path matches a glob, by the rules of `docs/extern/mpbt_project.h.md`, *Globs*. It works on the bytes, and reads no file.

## Examples

- `src/**/*.c` matches `src/host/main.c` and `src/shared/say/say.c`.
- `docs/*.md` does not match `docs/extern/mpbt_file.h.md`, because a `*` stops at a `/`.
- `SRC/*.C` does not match `src/host/main.c`, also on Windows and on macOS, where the file system ignores the case of a letter.

## The steps

1. The match goes through the glob and the path name by name.
2. At a name `**`, it keeps that place. First, `**` takes no name of the path.
3. If a later name does not match, `**` takes one more name, and the match goes on.
4. In a name, a `*` keeps its place in the same way. It takes one more byte when a later byte does not match.

Thus the match goes back only to the last `**` or `*`. Its time grows at most with the length of the glob times the length of the path.

## Functions

| Function | Result |
| --- | --- |
| `glob_match` | Whether the path matches the glob. |
| `match_name` | Whether one name of a path matches one name of a glob. |
| `next_name` | The next name of a path or of a glob, from an offset. |
