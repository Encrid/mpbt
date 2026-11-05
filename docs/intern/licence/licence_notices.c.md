# src/licence/licence_notices.c

This file checks the notice of each source of `third_party`, the file `cla.md`, and the names that the readme gives.

## The sources

A source is each name `<source>` of a path `third_party/<source>/<path>`.
The files are in the order of their paths, so the files of one source come one after the other.

## The steps

1. Each source needs the file `third_party/<source>/license`.
2. The project needs `cla.md`.
3. `readme.md` names `cla.md`, and the notice of each source.
4. The readme names a file if it holds the path of the file in a code span.

A project with no `readme.md` names nothing, so each name gets a finding.

## Functions

| Function | Result |
| --- | --- |
| `licence_check_notices` | A finding for each notice that is not there, for `cla.md`, and for each name that the readme does not give. |
| `check_source` | The findings of one source. |
| `has_span` | Whether the readme holds a path in a code span. |
