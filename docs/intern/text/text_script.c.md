# src/text/text_script.c

This file checks a script of Python: its legal notice, its comments and its string statements.

## The legal notice

A script starts with the notice of `mpbt:Project`, with the mark `#` before each line.
`notice_match` tells whether the script starts with it, and gives the offset after it: `docs/intern/shared/notice/notice.c.md`.
The line ends before that offset give the last line of the notice.
With no notice, the script gets a finding at line 1, and each of its comments is a fault.

## The statements

A statement starts at the start of the script, and after a line end or a `;` that is in no bracket.
A string statement holds one string or more, and no other token than strings, `(` and `)`.
Each of its strings is plain: `docs/intern/text/text_script_tokens.c.md`, *The strings*. A string of bytes or a format string makes a different value.
The finding of a string statement has the line of the first token of the statement.

## The comments

Each comment after the last line of the notice gets a finding, with its line.
A comment is no token of a statement. Thus a string with a comment after it is still a string statement.

## The limits

A string after the `:` of a compound statement, on the same line, is not found, for example `def f(): "text"`.
The parser of Python reads the whole grammar, and finds it. This file reads only the tokens.

## Functions

| Function | Result |
| --- | --- |
| `text_check_script` | A finding for the notice, for each comment and for each string statement of a script. |
| `take_token` | The state of the statement after one more token. |
| `end_statement` | A finding if the statement that ends is a string statement. |
