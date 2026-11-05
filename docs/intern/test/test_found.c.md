# src/test/test_found.c

This file is a visitor of the tree of one source. It finds the functions of a list that the source uses, and their declarations.
Both the layer and the count give such a function a new name: `test_rename.c`.

## The steps

`test_find_used` gets each node that the reader keeps, and `walk_used` goes through it and each node below it:

1. A `DeclRefExpr` of a name of the list, with its `begin` in the source itself, is a use.
2. A `TypedefDecl` gives the type of its name. The first one of a name counts.
3. A `FunctionDecl` of a name of the list gives its declaration with `get_declaration`. The first one counts.
4. A `FunctionDecl` with a `CompoundStmt` child, whose `loc` is in the source, is a definition.
5. A definition keeps the byte of its end: `end` of `range`, or its expansion in a macro.

`test_get_used` then gives the names that the source uses, but not the names that it defines, except a callback.
A use in a function of a header does not count, because its `begin` is in the header. The new name changes only the source.

## A declaration

`get_declaration` reads the type of a `FunctionDecl`, as `plain` gives it, for example `void *(unsigned long)`.

- The result is the text before the first `(`, with no white space at its ends. A name of a `typedef` gives the type of that `typedef`.
- Each `ParmVarDecl` child gives the type of a parameter, as `plain` gives it.
- `get_spelled` also gives the type of each parameter as the code spells it, from `type`, for the start of a new function.
- The declaration is `variadic` if its type holds `...`.

A builtin such as `malloc` also has a declaration that the compiler makes, with `isImplicit`. The reader skips it, because its types use the names of the compiler, such as `__size_t`.
`get_spelled` takes away the marks `_Nonnull`, `_Nullable`, `_Nullable_result` and `_Null_unspecified`, and the conventions `cdecl`, `stdcall`, `fastcall` and `thiscall`.
Such a convention changes nothing on x86_64 and on aarch64. Thus a `typedef` with a convention, such as `LPTHREAD_START_ROUTINE`, keeps its name.

## Functions

| Function | Result |
| --- | --- |
| `test_find_used` | Adds the facts of one node at the top to the `test_used_t` of the source. |
| `test_get_used` | The names that the source uses, with their declarations and the ends of the callbacks. |
| `walk_used` | The facts of a node and of its children, down to the leaves. |
| `get_declaration` | The `test_decl_t` of a `FunctionDecl`. |
| `get_spelled` | A type with no mark of nullability and no convention, and with one space between its words. |
