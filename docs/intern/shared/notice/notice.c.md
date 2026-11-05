# src/shared/notice/notice.c

This file tells whether a text starts with the legal notice of the project, with a mark before each line: `docs/contributing/coding_style.md`, *G1 - The legal notice*.
The notice is the text of `.toolchain/header.txt`, which `notice` of `mpbt:Project` holds.

## The lines

1. A line end of the notice is `\n` or `\r\n`. A line end after its last line adds no empty line.
2. Each line of the notice gives one line of the text: the mark, a space, and the line.
3. That line keeps no white space at its end. Thus an empty line of the notice gives the mark alone.
4. Each such line of the text ends with `\n` or `\r\n`, also the last one.

The mark is `#` for a script, and `**` for a file of C.
The caller checks what comes before and after the notice, for example the `/*` and the `*/` of a file of C.

## The marks of the notice

| Mark | It matches |
| --- | --- |
| `<year>` | A year of 4 digits, or a range of 2 such years with a `-` between them. |
| `<holder>` | One byte or more, up to the line end. |
| Each other byte | The same byte. |

The line of the notice with `<holder>` can repeat. It takes each next line of the text that matches it, so each holder of the rights has a line of its own.
A repeat takes all the lines that match, and gives none back.

## Functions

| Function | Result |
| --- | --- |
| `notice_match` | `true` and the offset after the notice in the text, or `false`. |
| `match_line` | The offset after one line of the text that matches one line of the notice, or none. |
| `match_year` | How many bytes a year takes at an offset, or 0. |
