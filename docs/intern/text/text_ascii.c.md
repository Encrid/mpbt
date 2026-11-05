# src/text/text_ascii.c

This file finds each line of a file that holds a byte that is not ASCII.

## The lines

A line ends at `\n`. A byte of 128 or more is not ASCII, and each character of UTF-8 that is not ASCII has such bytes.
Each such line gets one finding, with its number. The files that `unicode` names get no check: `text_file.c`.

## Functions

| Function | Result |
| --- | --- |
| `text_check_ascii` | A finding for each line with a byte that is not ASCII. |
