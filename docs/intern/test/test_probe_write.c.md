# src/test/test_probe_write.c

This file gives the text of a file with its probes, and the line and the column of each probe for the report.

## The probes in the text

1. The probes get their numbers from 0, in the order of their first byte, then of their kind.
2. A condition gets `<prefix>((` at its start, and `), <number>)` at its end. The probe gives the value of the condition.
3. A function or a label gets ` <prefix>hit_(<number>);` at its byte.
4. The block of the layer of a source goes at its byte, before each probe at the same byte.
5. At one byte, the ends of conditions come first, then the starts, then the hits.
6. Of 2 starts at one byte, the outer one comes first. Of 2 ends, the inner one comes first.

`get_line` gives the line and the column of the byte that each probe shows, from 1, in the bytes of the source.

## The parts around the text

| File | Its new text |
| --- | --- |
| A source `.c` | The top part, `#line 1`, the text, a line end, the end of the layer, then the map part. |
| A header | A guard of its own, with the top part and the map part in it, `#line 1`, then the text. |

`write_top` writes the top part: an array of `_Atomic unsigned char` with 2 bytes for each probe, a pointer `<prefix>at` to the array, and 2 functions.

- `<prefix>(c, id)` sets the byte `2 * id + 1` if `c` is true, else the byte `2 * id`, and gives `c`.
- `<prefix>hit_(id)` sets the byte `2 * id + 1`.
- A probe writes its byte only while the byte is 0. After that, it only reads the byte.

`write_map` writes the map part: a `[[gnu::constructor]]` that maps the part of the file of `C23_BRANCHES` that belongs to the file.
It uses `mmap` with `MAP_SHARED` on Linux and on macOS, and `CreateFileMappingA` and `MapViewOfFile` on Windows.
The constructor copies the bytes that the probes set before it ran. Then `<prefix>at` points into the mapped part.
The system keeps the bytes of a mapped file when the program ends, also with `_Exit` or `abort`.
On Windows, the constructor declares the 2 calls with names of its own, so that `windows.h` does not come into the file.

## Functions

| Function | Result |
| --- | --- |
| `test_write_probed` | The new text of a file, and the rows of its probes. |
| `sort_pieces` | The order of the texts that go into the file. |
| `write_top` | The array and the 2 functions of the probes. |
| `write_map` | The constructor that maps the part of the file. |
| `get_line` | The line and the column of a byte. |
