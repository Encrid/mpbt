# src/licence/licence_text.c

This file checks that `license` holds the GNU AGPL, version 3, as its authors publish it.

## The digest

The published text is https://www.gnu.org/licenses/agpl-3.0.txt. It has 661 lines and 34523 bytes, with the line ends of Linux.
The digest of `license` comes from `sha256_start`, `sha256_add`, `sha256_end` and `sha256_get_hex`. It must be this text:

```text
0d96a4ff68ad6d4b6f1f30f713b18d5184912ba8dd389f86aa7710db079abcb0
```

`.gitattributes` keeps the line ends of Linux on each system. Thus `license` has the same digest on each system.

## Functions

| Function | Result |
| --- | --- |
| `licence_check_text` | A finding if `license` is not there, or if its digest is different. |
