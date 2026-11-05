# src/layout/layout_paths.c

This file checks the place of each file of the project, and the files and the folder that each project needs: `docs/extern/mpbt_check.h.md`, *layout*.
`glob_match` matches a path with each glob of the tables: `docs/intern/shared/glob/glob_match.c.md`.

## The needed paths

| Path | Content |
| --- | --- |
| `.github/workflows/ci.yml`, `.github/workflows/release.yml`, `.github/workflows/cla.yml` | The workflows. |
| `.gitattributes`, `.gitignore` | The settings of git. |
| `cla.md`, `license` | The agreement and the licence. |
| `project.py`, `readme.md` | The entry of the tools, and the readme. |
| `.toolchain/project.toml` | The first file of the config. |
| `docs/contributing/<guide>.md` | The 8 guides: `agreement`, `coding_style`, `commits`, `decisions`, `documentation_style`, `needs`, `pull_request` and `tests`. |

The folder `.toolchain/tools` holds the tools of the toolchain. It needs one file or more: a file that `.toolchain/tools/**` matches.

## The allowed paths

| Glob | Content |
| --- | --- |
| Each needed path | The files that each project needs. |
| `docs/contributing/<name>`, for each line of `guides` | A guide that the project adds. |
| `architecture.md` | The map of the project. |
| `docs/extern/**/*.md`, `docs/intern/**/*.md`, `docs/tools/**/*.md` | The documents: `layout_documents.c`. |
| `include/**/*.h` | The public headers. |
| `src/**`, `tools/**` | The sources, the other inputs of a build, and the tools. |
| `tests/**`, `third_party/**` | Each file, with each name. No rule of the layout applies to it. |
| `.toolchain/tools/*.py` | A tool of the toolchain. |
| `.toolchain/toolchain.toml`, `.toolchain/header.txt` | The values and the legal notice of the toolchain. |
| `.toolchain/config/**/*.toml` | A file of the config. |
| `.toolchain/docs/*.md` | A document of the toolchain. |
| `.toolchain/presets/*/*.toml` | A file of a preset. |
| `.toolchain/runtime/*.c`, `.toolchain/runtime/*.h` | A source that the toolchain adds to the libraries of a target. |
| `.gitkeep` in `docs/extern`, `docs/intern` or `include` | An empty file that keeps an empty folder in git. |

`lists_get_line` gives each line of `guides`.

## The files that a build makes

The last name of a path must not match one of these globs:

- `*.o`, `*.obj`, `*.a`, `*.so`, `*.dll`, `*.dylib`, `*.exe`, `*.gch`, `*.d` and `*.pyc`: the files that a build makes;
- `*~` and `#*#`: the files that an editor makes;
- `a.out`.

## The steps

1. Each needed path that `files_find` does not find gets a finding.
2. If no file is in `.toolchain/tools`, the folder gets a finding.
3. The next steps skip each file of `tests` and of `third_party`.
4. Each other file that no allowed glob matches gets a finding.
5. Each other file whose last name matches a glob of a build gets a finding.

## Functions

| Function | Result |
| --- | --- |
| `layout_check_paths` | A finding for each needed path that is not there, and for each path that the layout refuses. |
| `is_allowed` | Whether a path is a needed path, a guide, or a path that an allowed glob matches. |
| `is_guide` | Whether a path is `docs/contributing/<name>` for a line of `guides`. |
| `is_made` | Whether a last name matches a glob of a build. |
