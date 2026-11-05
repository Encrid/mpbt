# src/test/test_probe_trace.c

This file traces the calls of macros in the body of a function. A condition that cuts such a call in two then gets no probe.
For example, `x == y` in `x == PICK(y) + 1`, with `#define PICK(c) c ? 0 : 1`, holds a part of the call `PICK(y)`.

## The trace of a body

`test_trace_body` goes through each node below the body. For each end of its `range` in a macro, `add_ends` keeps 2 facts:

- the call: the file and the offset of the expansion of the end;
- the token: the file and the offset of the spelling of the end.

Thus the trace gives, for each call, the nodes with an end in the call, and the tokens of those ends.

## A condition that holds a part

`test_is_partial` traces the condition in the same way, and joins the tokens of each call that the condition touches.
The condition is partial if a node of such a call is not below the condition, and one of these is true:

1. The node does not hold the condition: `is_above` does not find it among the parents of the condition.
2. The node holds the condition, but it has a token in the call that the condition does not have.

A probe of a partial condition would cut a call of a macro in two. Thus the condition is a branch that is not measured, at the name of the call.

## Functions

| Function | Result |
| --- | --- |
| `test_trace_body` | The calls of the macros of a body, with their nodes and their tokens. |
| `test_is_partial` | Whether a condition leaves out a node of a call that it touches. |
| `add_ends` | The calls and the tokens of the 2 ends of one node. |
| `is_above` | Whether a node holds the condition. |
