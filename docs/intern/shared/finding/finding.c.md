# src/shared/finding/finding.c

This file writes one finding: a new entity with `mpbt:Finding`, whose texts are in one `alloc` of Bridge.

## The steps

1. `finding_write` gets the bytes of the text. `finding_format` and `finding_vformat` get a format of `printf` and its values, and `vsnprintf` measures the text.
2. `take_room` takes one `alloc` for the name of the check, the path, the text, and a zero byte for `vsnprintf`.
3. It copies the name and the path into the room. Then the text is copied after them, or `vsnprintf` writes it there.
4. The 3 `bridge_text_t` of `mpbt_finding_t` give the 3 parts of the room. Thus the texts stay as long as the row.
5. `attach_finding` gets a new entity from `spawn`, and `BRIDGE_NATIVE_ATTACH` gives the finding to it.

The system that calls it names `mpbt:Finding` in its changes. The caller can free its own bytes after the call, since the row holds copies.

## The errors

The result is `false` if `vsnprintf` fails, or if Bridge refuses `alloc` or `spawn`. When Bridge refuses a call, the run of the system fails too: Bridge tells that.
The file takes no memory of the heap. Thus a module can write a finding also after `malloc` failed.

## The limits

Each finding takes one id of `spawns` of the module, and 56 bytes of its `changes`. The attach takes 24 bytes, and its value 32 bytes.
The host gives these keys, and states how many findings a module can write between 2 barriers: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## Functions

| Function | Result |
| --- | --- |
| `finding_write` | `true`, and a finding with the bytes of a text. |
| `finding_format` | `true`, and a finding with the text of a format and its values. |
| `finding_vformat` | As `finding_format`, with the values in a `va_list`, for a caller that has values of its own. |
| `take_room` | The offset of the room of the texts, with the name and the path in it, or 0. |
| `attach_finding` | `true` if Bridge gave the entity and took the attach. |
