# src/shared/glob/glob.h

This header declares the match of a path with a glob. It also declares the walk of the disk that gives the files of a list of globs.
A glob is a path that can hold `*`, for example `src/**/*.c`. Its rules are in `docs/extern/mpbt_project.h.md`, *Globs*.

The check `text` matches the paths of `[check] unicode`, and the check `style` the path of each `[[style.exception]]`.
`test` matches the exceptions of the branches and of the leaks. `read` finds the files of its lists with `glob_files`.

## Functions

| Function | Result |
| --- | --- |
| `glob_match` | Whether a path matches a glob. |
| `glob_files` | Each file of the disk that a glob of the list matches, in order, and one time. |
