# include/mpbt/branches.h

`include/mpbt/branches.h` gives `mpbt:BranchException`: a branch that no case can reach, which `test --branches` excuses.

## test --branches

`test --branches` builds the code of `src` and of `include` with probes, runs each case one time, and writes each outcome that no case reaches:

- a condition that no case makes true, or that no case makes false;
- a `case` or a `default` of a `switch` that no case reaches;
- a function that no case calls.

A condition is the test of an `if`, a `while`, a `do`, a `for` or a `?:`, or an operand of `&&` or `||`.
Parentheses, casts and `!` do not change a condition.
A constant part gets no probe: `static_assert`, `sizeof`, `_Generic`, a label of `case`, an `enum`, and the value of a variable `static` or `constexpr`.
A condition that holds only a part of the call of a macro cannot get a probe, and the run writes it as not measured.
The probes change the program, so the run does not judge the claims.

## [[branches.exception]]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `path` | text | none | The path of the file. It can hold `*`. |
| `line` | integer | none | The line of the branch. |
| `col` | integer | none | The column of the branch. |
| `side` | text | none | `true`, `false`, `function` or `case`. |
| `why` | text | none | The reason that no case can reach the branch. |
| `system` | text | each system | `posix` or `windows`, for a branch that only one system has. |

```toml
[[branches.exception]]
path = "src/backends/wasm/wasm_own.c"
line = 23
col = 9
side = "true"
why = "A wasm32 memory holds at most 65536 pages, which is the reserve, so a grow never exceeds it."
```

An exception excuses the outcome that it names. An exception with no `why`, or that excuses no outcome, is a fault.
Thus an exception goes when a case reaches its branch again. With `--part`, the run reads only the exceptions of the files of the parts.

## mpbt:BranchException

Each exception is an entity with `mpbt:BranchException`.
`mpbt_branch_exception_t` takes 28 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `path` | `bridge_text_t` | 0 | `path`. |
| `why` | `bridge_text_t` | 8 | `why`, or no bytes. |
| `line` | `uint32_t` | 16 | `line`. |
| `col` | `uint32_t` | 20 | `col`. |
| `side` | `mpbt_side_t` | 24 | `side`. |
| `system` | `mpbt_system_t` | 25 | `system`: `docs/extern/mpbt/target.h.md`, *mpbt:mpbt_system_t*. |

Bytes 26 and 27 hold no field.

### mpbt:mpbt_side_t

`mpbt_side_t` is an enum of `uint8_t`.

| Constant | Value | The outcome that no case reaches |
| --- | --- | --- |
| `MPBT_SIDE_TRUE` | 1 | The condition is true. |
| `MPBT_SIDE_FALSE` | 2 | The condition is false. |
| `MPBT_SIDE_FUNCTION` | 3 | A call of the function. |
| `MPBT_SIDE_CASE` | 4 | The `case` or the `default`. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:mpbt_side_t` | `mpbt_side_t` | `mpbt_side_t_desc` | `MPBT_SIDE_VALUES` |
| `mpbt:BranchException` | `mpbt_branch_exception_t` | `mpbt_branch_exception_t_desc` | `MPBT_BRANCH_EXCEPTION_FIELDS` |

```text
uint8_t { MPBT_SIDE_TRUE = 1, MPBT_SIDE_FALSE = 2, MPBT_SIDE_FUNCTION = 3, MPBT_SIDE_CASE = 4 }
{ bridge_text_t path; bridge_text_t why; uint32_t line; uint32_t col; mpbt_side_t side; mpbt_system_t system; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:mpbt_side_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:BranchException` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare `mpbt:mpbt_side_t` and `mpbt:mpbt_system_t` first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:BranchException` | `read` | Each module with a grant. |

## Messages

Each line of an outcome starts with `<path>:<line>:<column>: `.

| Message | When |
| --- | --- |
| `no case makes this condition true` | No case makes the condition true. |
| `no case makes this condition false` | No case makes the condition false. |
| `no case reaches this case` | No case reaches the `case` or the `default`. |
| `no case calls this function` | No case calls the function. |
| `this <outcome> is in a macro, and is not measured` | A condition, a `case` or a function in a macro has no probe. |
| `this exemption states no reason` | An exception has no `why`. |
| `this exemption excuses no unreached outcome` | No outcome of the exception is unreached. |
| `branches: <outcomes> outcomes, <reached> reached` | The run ends. With an excused outcome, `, <exempt> exempt` follows. |
| `outcomes not reached: <missed>; branches not measured: <macros>` | An outcome is unreached, a branch is not measured, or an exception is a fault. |
