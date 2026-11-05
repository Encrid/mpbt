# src/style/style_exceptions.c

This file reads the exceptions of the style, tells whether one of them excuses a fault, and reports each exception that has no use.
`docs/contributing/coding_style.md`, *Exceptions*, gives their rules, and `docs/extern/mpbt_check.h.md`, *mpbt:StyleException*, their fields.

## The exceptions

`world_rows` gives each `mpbt:StyleException` to `keep_exception`, which keeps it in `exceptions`.
`keep_exception` cuts `path` at its first `:`. The bytes before it are the glob of the file, and the bytes after it name the function.
An exception with no bytes in `why` gives a finding at once, with its message of `docs/extern/mpbt_check.h.md`, *Messages*.
Such an exception does not go into `exceptions`, so it excuses no fault.

## The match

An exception excuses a fault if each of these is true:

1. The rule of the exception is the rule of the fault.
2. `glob_match` of `src/shared/glob/glob.h` accepts the path of the file with the glob of the exception.
3. The exception names no function, or the function of the fault has the name.

Each exception that excuses a fault counts it, also when another exception excuses the same fault.

## The end of the run

After the last file, `style_end_exceptions` gives a finding for each exception with a count of 0, with its message of `docs/extern/mpbt_check.h.md`, *Messages*.
`finding_format` writes the findings of the exceptions, so that no exception can excuse them. The 2 messages name the whole `path` of the exception.
The text of these findings starts with the rule of the exception, as each text of the style does.
These findings have no path, no line and no column, because `mpbt:StyleException` does not tell the file of the config.

## Functions

| Function | Result |
| --- | --- |
| `style_read_exceptions` | `true` and `exceptions`, or `false` if the list cannot grow. |
| `keep_exception` | Keeps one exception, or writes its finding. |
| `style_is_excused` | `true` if an exception excuses a fault. |
| `style_end_exceptions` | Gives a finding for each exception that excused nothing. |
