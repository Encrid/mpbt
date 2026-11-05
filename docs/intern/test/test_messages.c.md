# src/test/test_messages.c

This file finds the messages of one file of the code with the tokens of `src/shared/c_tokens`: each text of a call of a writer.

## The steps

1. `test_find_messages` starts a scan of the bytes of the file with `c_tokens_start`, and gives it to `scan_calls`.
2. `scan_calls` reads the tokens with `c_tokens_next_code`, so spaces, line ends and comments do not count.
3. A name that `is_writer` finds in the writers, with `(` after it, starts a call. Its line is the line of the message.
4. `find_format` goes through the arguments of the call, and counts the parentheses that open and close.
5. The first string before the `)` that closes the call starts the message. With no string, the call gives no message.
6. `c_tokens_decode` joins that string and the strings right after it, with their escapes replaced.
7. The white space at the 2 ends of the text goes.

For a directive, `c_tokens_start_directive` starts a scan of its bytes after the `#`, and `scan_calls` reads it too.
Thus a call in the body of a macro gives its message, at the line of the directive.
A call with no string is, for example, the declaration of the writer, or a call that gives its format in a variable.
A string or a comment that holds the name of a writer is one token, so it gives no call.

## Functions

| Function | Result |
| --- | --- |
| `test_find_messages` | Gives each message of a file and its line to a function of the caller. |
| `scan_calls` | The calls of the writers in one scan. |
| `find_format` | The text of the first strings of the arguments of a call, or none. |
| `is_writer` | Whether a name is a line of `writers`. |
