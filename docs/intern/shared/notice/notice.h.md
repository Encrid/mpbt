# src/shared/notice/notice.h

This header declares the match of the legal notice at the start of a text.
The check `text` uses it for a script, and the check `style` uses it for a file of C.

## Functions

| Function | Result |
| --- | --- |
| `notice_match` | `true` and the offset after the notice, or `false` if the text does not start with the notice. |
