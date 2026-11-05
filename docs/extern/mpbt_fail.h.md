# include/mpbt_fail.h

`include/mpbt_fail.h` gives `mpbt:FailCall`: a function that a case can make fail.

## The calls that fail

A case with the key `fail` makes a call fail: `docs/extern/mpbt_case.h.md`, *[[case]]*.
Thus the case runs the path of an error, for example the branch of `if (!p)`.
`malloc`, `calloc` and `realloc` can always fail, with the value `nullptr`.

mpbt builds a copy of the code of `src`, in which each listed function that a file uses can fail.
Each call of such a function adds 1 to its count. At the number that the case gives, the call fails.
The files of one program, or of one library, share one count.
`test` runs each case with `fail` on that copy, and judges its claims. `test --branches` and `test --leaks` make the calls fail too.

## [fail]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `calls` | table | `{}` | Each function, with the value of C that its failed call gives. |
| `with` | list | `[]` | Files with more `calls`, each in a table `[fail]`, for example `{bridge_os}/fail.toml`. |

```toml
[fail]
with = ["{bridge_os}/fail.toml"]

[fail.calls]
os_commit = "-1"
os_lib_open = "nullptr"
```

Each file that calls the function must compile its value. A function is in the list one time.

## mpbt:FailCall

Each function of `calls`, and of each file of `with`, is an entity with `mpbt:FailCall`.
`mpbt_fail_call_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `function` | `bridge_text_t` | 0 | The name of the function. |
| `value` | `bridge_text_t` | 8 | The value of a failed call, as a text of C. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:FailCall` | `mpbt_fail_call_t` | `mpbt_fail_call_t_desc` | `MPBT_FAIL_CALL_FIELDS` |

```text
{ bridge_text_t function; bridge_text_t value; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:FailCall` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:FailCall` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `[fail] with: <path> is not there` | A file of `with` is not there. |
| `[fail.calls] lists <name> two times` | A table names a function of the list again. |
| `<path>: the case <name> makes <call> fail, and [fail.calls] does not list it` | A case makes a function fail that is not in the list. |
| `<name> gives no result` | A listed function that the code uses has no result. |
