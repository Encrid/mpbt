# src/pseudo/pseudo_statement.c

This file reads a line that is not a clause, and a clause of a `CASE`.

## Statements

A line that is not a clause has one of these forms. A word in angle brackets is a part that the other files of `src/pseudo` read.

```text
DECLARE <name> : <type>
CONSTANT <name> = <literal>
TYPE <name>
NEXT <name>
<target> <- <expression>
IF <expression> THEN
CASE OF <target>
FOR <name> <- <expression> TO <expression>
FOR <name> <- <expression> TO <expression> STEP <expression>
WHILE <expression>
UNTIL <expression>
RETURN <expression>
PROCEDURE <name>(<parameters>)
FUNCTION <name>(<parameters>) RETURNS <type>
CALL <name>(<expressions>)
```

A word of `alone` is a line by itself: `docs/intern/pseudo/pseudo_words.c.md`, *The words*.
`CONSTANT` takes a literal, with a `-` before it if necessary.
A target is a name, then its fields and its elements, with no call.
`<parameters>` and `<expressions>` are 0 items or more, with a comma between 2 items.

## Clauses

```text
<expression> : <statement>
<expression> TO <expression> : <statement>
OTHERWISE : <statement>
```

The statement of a clause is an assignment, a `CALL` or a `RETURN`. Thus the token after `:` is no other keyword.

## Functions

| Function | Result |
| --- | --- |
| `pseudo_read_statement` | `true` after a statement. |
| `pseudo_read_clause` | `true` after a clause. |
| `read_constant` | `true` after a `CONSTANT`. |
| `read_for` | `true` after a `FOR`. |
| `read_routine` | `true` after a `PROCEDURE`, a `FUNCTION` or a `CALL`. |
