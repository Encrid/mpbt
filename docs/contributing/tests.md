# Tests

`python project.py test` builds the project, then runs the cases of `tests/cases`.
`docs/extern/mpbt_case.h.md` gives the form of a case: its keys, its claims, its scripts and its variables.
`tests` can also hold other files, for example the data that the cases read. No check reads `tests`.

## Write a case

1. Select a behavior that a document of the project describes.
2. Write the command that shows the behavior.
3. Write the claims: what the command must do.
4. Write the false variant: a change of the command or of its input that makes the claims false.
5. Run `python project.py test`. The case must pass.
6. Run `python project.py test --break`. The case must fail.

For example, the program `greet` writes `hello, <name>` for the name that it gets:

```toml
[[case]]
name = "greet writes the name that it gets"
run = ["{out}/greet{exe}", "Ada"]
claims = { status = 0, line = ["hello, Ada"] }
false = { run = ["{out}/greet{exe}", "Bob"] }
```

With `Bob`, the output has no line `hello, Ada`. Thus the claims of the false variant are false, and the case can fail.

- A case checks one behavior. Its name tells the behavior.
- Each behavior that a document describes has a case.
- The false variant changes the command or its input. It cannot change the claims.
- The false variant runs the code that does the behavior, with one input changed. A command that the program refuses before that code runs is not a false variant, for example an unknown name.
- A case writes its files only into its folder, `{case}`.

## The break run

The break run shows that each case can fail: `docs/extern/mpbt_case.h.md`, *The false variant*.
A case whose false variant still passes makes the break run fail.
`test` refuses a case that has no false variant, also without `--break`.

## The branches

Each branch of the code must run in a case: `docs/extern/mpbt_branches.h.md`.
For each branch that `python project.py test --branches` writes, write a case that runs the branch, or remove the branch.
A condition in an argument or in the body of a macro cannot get a probe. Thus write such a condition outside the macro.

## The leaks

Each case must give back each resource that the code takes, also on the paths of the errors: `docs/extern/mpbt_leaks.h.md`.
For each line that `python project.py test --leaks` writes, make the code give the resource back.
If a case keeps a resource by design, write an exemption with its reason.

## Failed calls

A case can make a call of the code fail, so that the case runs the path of the error: `docs/extern/mpbt_fail.h.md`.
In this case, the second call of `malloc` gives `nullptr`:

```toml
[[case]]
name = "greet writes an error when it has no memory"
run = ["{out}/greet{exe}", "Ada"]
fail = { malloc = 2 }
claims = { status = 1, line = ["greet: no memory"] }
false = { fail = {} }
```

The false variant states no `fail`, or a different number.

## Run the tests

| Command | Result |
| --- | --- |
| `python project.py test` | Runs each case. |
| `python project.py test --break` | Runs the false variant of each case. Each case must fail. |
| `python project.py test --branches` | Runs each case one time on a build with probes. Each branch must run. |
| `python project.py test --leaks` | Runs each case one time on a build with counts. Each case must give back what the code takes. |
| `python project.py test -k <text>` | Runs only the cases whose name contains `<text>`. |
| `python project.py test --part <part>` | Builds the part and the parts that it uses, then runs only the groups of the part. |
| `python project.py test --copies <number>` | Runs this number of copies of each case at the same time. Each copy must pass. |
| `python project.py test --rounds <number>` | Runs all the cases this number of times, one round after the other. |

The copies of a case compete for the processors and the memory. Thus they find a fault that shows only under load.

## Variables

A text of a case can hold variables, for example `{out}`: `docs/extern/mpbt_case.h.md`, *[[case]]*.

## The settings

`[test]` of `.toolchain/project.toml` holds the settings of the tests: `docs/extern/mpbt_case.h.md`, *[test]*.

## The messages of the code


When `[test] writers` names functions, a case must write each message of the code, and a document must quote it: `docs/extern/mpbt_case.h.md`, *The messages of the code*.
`docs/contributing/documentation_style.md`, *The messages of the code* tells how a document quotes a message.
