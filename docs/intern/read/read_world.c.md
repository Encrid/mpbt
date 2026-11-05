# src/read/read_world.c

This file is the side of `read` that faces the world of Bridge. It reads the settings, and it puts texts and lists into the persistent arena.

## Texts and lists

- `read_put_text` asks `alloc` for room for the bytes, copies them there, and gives their `bridge_text_t`. A text with no bytes takes no `alloc`.
- `read_put_list` gives the items to `lists_get_size`, takes one `alloc` of that size, and lets `lists_write` fill it.
- A map has the same form, with the key before the value. A value that is a list goes into the arena first, as `docs/intern/shared/lists/lists_write.c.md` tells.
- `read_put_lines` joins the items into one text, with `\n` after each item. That is the form of a list of a setting: `docs/extern/mpbt_project.h.md`, *Lists and maps*.

An item of `read_put_lines` that holds a line end gives the finding of `docs/extern/mpbt_project.h.md`, *Messages*, with the key of the config as `<setting>`.

## The findings

Each file of `read` writes a fault with `finding_write` or `finding_format` of `src/shared/finding/finding.h`, and with `finding` of `read_t`.
The whole message is the text. `path`, `line` and `column` hold nothing, because a message of `read` names its place itself.
After each finding, the file adds 1 to `findings` of `read_t`.

## The settings

`read_get_arguments` reads the kept cell of `mpbt:Arguments`, through the readers of BB-Native.
The texts of the settings stay in the arena of `read`, so `read_t` keeps their `bridge_text_t` and copies no byte.

## Functions

| Function | Result |
| --- | --- |
| `read_put_text` | The `bridge_text_t` of the bytes in the arena. |
| `read_put_list` | The `bridge_text_t` of a list or of a map in the arena. |
| `read_put_lines` | `true` and one text with a line for each item, or `false` and a finding. |
| `read_get_arguments` | The settings of `read`. |
