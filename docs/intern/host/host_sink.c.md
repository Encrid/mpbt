# src/host/host_sink.c

This file is the sink of the world: it writes each record of Bridge as a line, with `say`.

## The lines

- A record of a module gives the line of `docs/extern/mpbt_finding.h.md`, *The report*: its module first, then its text.
- A record at the level of an error sets the status of the host to 1.
- Bridge calls the sink on the thread of the host, after the systems of a phase return. So the sink needs no lock.

## Functions

| Function | Result |
| --- | --- |
| `host_sink` | Writes one record as a line. |
