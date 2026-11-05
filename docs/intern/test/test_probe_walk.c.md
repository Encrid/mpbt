# src/test/test_probe_walk.c

This file walks a node of a tree, and finds where the probes go: each function, each label of a `switch` and each condition.
What the probes measure is in `docs/extern/mpbt_branches.h.md`, *test --branches*.

## The walk

`walk_node` gets a node, whether it is in the body of a function, and its depth.

1. `is_unmeasured` stops the walk at a constant part, with each node below it.
2. A `FunctionDecl` goes to `probe_function`.
3. In a body, a node of the table *The conditions* gives its child at its place to `test_probe_condition`.
4. In a body, a `BinaryOperator` with `&&` or `||` gives each of its 2 operands to `test_probe_condition`, one level deeper.
5. In a body, a `CaseStmt` or a `DefaultStmt` goes to `probe_label`.
6. Then the walk goes on with each child, one level deeper.

The constant parts are the kinds `ConstantExpr`, `UnaryExprOrTypeTraitExpr`, `GenericSelectionExpr`, `StaticAssertDecl` and `EnumDecl`, and a `VarDecl` that is `static` or `constexpr`.

## The conditions

| Kind | Place of the condition in `inner` |
| --- | --- |
| `IfStmt` | 0 |
| `WhileStmt` | 0 |
| `DoStmt` | 1 |
| `ConditionalOperator` | 0 |
| `ForStmt` | 2 |

## A function and a label

- `probe_function` takes the `CompoundStmt` child. Its probe goes after the `{`, and the report shows the place of the name of the function.
- `probe_function` then traces the body with `test_trace_body`, and walks it.
- `probe_label` shows the start of the label. The probe goes after the `:` that follows the value of a `case`, or that follows `default`.
- A body or a label whose place is in a macro gets no probe. The writer keeps it as a branch that is not measured.
- A function of a file of a different project gets no probe, so its body is not walked.

## Functions

| Function | Result |
| --- | --- |
| `test_walk_probes` | The probes of one node at the top, added to the probes of the run. |
| `walk_node` | The probes of a node and of each node below it. |
| `is_unmeasured` | Whether a node is a constant part. |
| `probe_function` | The probe of a function, and the walk of its body. |
| `probe_label` | The probe of a `case` or of a `default`. |
