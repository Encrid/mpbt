# include/mpbt/case.h

`include/mpbt/case.h` gives the types of the tests: `mpbt:Tests`, `mpbt:TestRule`, and the types of a case and of its false variant.
A case runs a command, and makes claims about its exit status, its output and its files.

## [test]

`[test]` gives the settings of the tests.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `timeout` | integer | none | The longest time of a command of a case, in seconds. Then mpbt stops the command, and the case fails, also with `--break`. |
| `copies` | integer | none | The copies of each case that run at one time. `--copies` replaces it. |
| `cases` | text | `tests/cases` | The folder of the files of the cases. |
| `writers` | list | `[]` | The functions that write the messages of the code: *The messages of the code*. |
| `rule` | list of tables | `[]` | The rules of the groups: *Rules*. |

## Groups

A group is a file `.toml` in the folder of the cases, or in one of its folders.
The name of the group is the path of the file in that folder, with no `.toml`.
In a project with parts, the groups of a part are in the folder of the part, below the folder of the cases.

## Rules

Each `[[test.rule]]` adds a claim to each case: the output does not hold the text `lacks`.
It does not apply to the groups of its list `exempt`.

## [[case]]

| Key | Type | Value |
| --- | --- | --- |
| `name` | text | The behavior that the case checks. Needed. |
| `run` | list | The command. Needed. |
| `env` | table | Changes of the environment of the command. A value is a text, or `false`, which removes the variable. |
| `stdin` | text | The text that mpbt writes to the command, after the script. Then mpbt closes the input. |
| `script` | list of tables | The steps that mpbt does while the command runs: *Scripts*. |
| `ignore` | list | `["interrupt"]`: the command starts with the interrupt ignored. |
| `helper` | table | A second command that runs at the same time: *Helpers*. |
| `files` | table | The texts that mpbt writes before the command starts. A key is a path, and its value is the text. |
| `folders` | table | The folders that mpbt makes before the command starts. A key is a path, and its value lists the artifacts and files that mpbt copies into it. |
| `fail` | table | The calls that fail: a key is a function, and its value is the number of the call. `docs/extern/mpbt/fail.h.md` tells it. |
| `claims` | table | The claims: *Claims*. A case needs one claim or more. |
| `false` | table | The false variant: *The false variant*. Each case needs one. |
| `alone` | bool | `true` if no copy of the case can run at the same time. Then the case runs one time with `--copies`. |

Each case starts in an empty folder, `{case}`: `<out>/cases/<group>/<number>`, then `/<copy>` for a copy.
The command runs in the folder of the project, with the timer of `timeout`.
A copy of `folders` or of a step `put` keeps the permissions of its file. Thus a copy of a program can run.

A text of a case can hold each variable of the build, and these 2 variables:

| Variable | Value |
| --- | --- |
| `{case}` | The folder of the case. |
| `{port}` | A free port of this machine. Only a case with `{port}` in a text gets it, and each such case gets a new port. |

mpbt runs a case in these steps:

1. It empties the folder of the case, and writes the files and the folders.
2. If the case has a helper, it starts the helper, and waits for its text `wait`.
3. It starts the command, and does the steps of the script.
4. It writes `stdin`, and waits for the end of the command.
5. If the case has a helper, it writes the `stdin` of the helper, and waits for its end.

## Claims

The output of a command is what it writes to its output and to its errors, with no `\r`.

| Key | Type | The claim is true if |
| --- | --- | --- |
| `status` | integer | The command ends with this status. |
| `status_not` | integer | The command does not end with this status. |
| `line` | list | Each text is a full line of the output. |
| `has` | list | The output holds each text. |
| `lacks` | list | The output holds no text of the list. |
| `matches` | list | mpbt finds each pattern in the output. A `.` also matches a line end. |
| `matches_not` | list | mpbt finds no pattern of the list in the output. |
| `order` | list | Each text is a line of the output, in this order. The spaces at the two ends of a line do not count. |
| `output` | text | The output is the text of this file of the project. |
| `files` | table | After the command, each file holds its text. A key is a path, and its value is the text. |

A pattern can use only these forms:

- a character, `.`, `[...]` and `[^...]`;
- `\d`, `\w`, `\s`, `\D`, `\W` and `\S`;
- `^`, `$` and `\b`;
- `(...)` and `|`;
- `*`, `+`, `?` and `{m,n}`.
mpbt finds each pattern in a time that grows only with the length of the output.
Before the first case, mpbt refuses each pattern with a different form.

## Scripts

Each step of a `script` does its actions in this order:

1. `wait`: it waits for a line of the output that holds this text. With no `wait`, the step acts at once.
2. `put`: it copies files. A key is a path, and its value is an artifact or a file.
3. `remove`: it removes the files of the list.
4. `type`: it writes this text and a line end to the command.
5. `close`: its one value is `"output"`. It closes the output of the command, so that each later write fails.
6. `signal`: it sends `interrupt`, `termination` or `hang-up`.
7. `pause`: it waits this number of seconds.

If the output ends before the text of a `wait`, mpbt stops the steps.
On Linux and on macOS, the signals are `SIGINT`, `SIGTERM` and `SIGHUP`.
On Windows, a command that gets a signal runs on a console of its own. The signals are ctrl-c, ctrl-break and the close of the console.
On each system, mpbt refuses a script with an interrupt and a termination, and a script with a signal after a hang-up.

## Helpers

A `helper` has a command `run`, a text `wait`, a text `stdin` and its own `claims`.
The claims of the helper must also be true. An empty table `helper` means no helper, so a false variant can remove the helper.

## The false variant

`false` can hold `run`, `env`, `stdin`, `script`, `helper`, `files`, `folders`, `fail` and `ignore`.
Each key of `false` replaces the key of the case. In `files` and in `folders`, each path of `false` replaces only that path.
`test --break` runs the false variant of each case. Its claims are the claims of the case, and they must then be false.

## Verdicts

| Run | The claims | Verdict | The case |
| --- | --- | --- | --- |
| `test` | true | `as written` | Passes. |
| `test` | false | `differs` | Fails. |
| `test --break` | false | `fails, as it must` | Passes. |
| `test --break` | true | `still as written` | Fails. |
| Both | A command does not end in time. | `did not end in <timeout> seconds` | Fails. |

A case passes only if each of its copies passes.

## The messages of the code

When `writers` names functions, a full `test` also checks the messages of the code, after each case passed.
A message is the text of a call of a writer, in a file `.c` or `.h` of `src` or of `include`.
A text with fewer than 6 characters that are not a conversion is no message.
A case must write each message, and `readme.md` or a document of `docs/extern` must quote it.
mpbt reads the output of all the cases from `{out}/said.txt`, which a full `test` writes.
A full `test` has no `--break`, no `-k` and no `--part`.

## mpbt:Tests

`mpbt:Tests` holds `[test]`. `mpbt:Tests` is a singleton: the settings of the tests.
`mpbt_tests_t` takes 24 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `cases` | `bridge_text_t` | 0 | `cases`. |
| `writers` | `bridge_text_t` | 8 | `writers`, with each name on its own line. |
| `timeout` | `uint32_t` | 16 | `timeout`. |
| `copies` | `uint32_t` | 20 | `copies`. |

## mpbt:TestRule

Each rule is an entity with `mpbt:TestRule`.
`mpbt_test_rule_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `lacks` | `bridge_text_t` | 0 | `lacks`. |
| `exempt` | `bridge_text_t` | 8 | A list: the names of the groups of `exempt`. |

## mpbt:Case

Each case is an entity with `mpbt:Case`, `mpbt:Run` and `mpbt:Claims`. A case with a helper also has `mpbt:HelperClaims`.
`mpbt_case_t` takes 24 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `group` | `bridge_text_t` | 0 | The name of the group. |
| `name` | `bridge_text_t` | 8 | `name`. |
| `index` | `uint32_t` | 16 | The place of the case in its group, from 0. |
| `alone` | `bool` | 20 | `alone`. |

Bytes 21 to 23 hold no field.

## mpbt:Run

`mpbt:Run` holds the command of a case, or of its false variant, with the inputs that mpbt gives to it.
`mpbt_run_t` takes 84 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `run` | `bridge_text_t` | 0 | A list: the command. |
| `env` | `bridge_text_t` | 8 | A map: each variable of `env` with a text, then the text. |
| `unset` | `bridge_text_t` | 16 | A list: each variable of `env` with `false`. |
| `input` | `bridge_text_t` | 24 | `stdin`. |
| `files` | `bridge_text_t` | 32 | A map: each path of `files`, then its text. |
| `folders` | `bridge_text_t` | 40 | A map: each path of `folders`, then the list of what mpbt copies there. |
| `fail` | `bridge_text_t` | 48 | A map: each function of `fail`, then the number of its call in decimal. |
| `helper_run` | `bridge_text_t` | 56 | A list: the command of the helper. It has no item if the case has no helper. |
| `helper_wait` | `bridge_text_t` | 64 | `wait` of the helper. |
| `helper_input` | `bridge_text_t` | 72 | `stdin` of the helper. |
| `ignore_interrupt` | `bool` | 80 | `true` if `ignore` holds `interrupt`. |

Bytes 81 to 83 hold no field. Each text keeps its variables: the test replaces them for each copy.
Its lists and maps: `docs/extern/mpbt/project.h.md`, *Lists and maps*.

## mpbt:FalseVariant

The false variant of a case is an entity of its own, with `mpbt:FalseVariant` and `mpbt:Run`.
Its `mpbt:Run` holds the values of the case, with the keys of `false` over them. It has `mpbt:HelperClaims` if its run has a helper.
`mpbt_false_variant_t` takes 8 bytes. Its alignment is 8.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `owner` | `uint64_t` | 0 | The id of the entity of the case. |

## mpbt:Claims and mpbt:HelperClaims

`mpbt:Claims` holds the claims of a case. `mpbt:HelperClaims` holds the claims of a helper, on the entity of its run.
`mpbt_claims_t` and `mpbt_helper_claims_t` take 76 bytes each. Their alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `line` | `bridge_text_t` | 0 | A list: `line`. |
| `has` | `bridge_text_t` | 8 | A list: `has`. |
| `lacks` | `bridge_text_t` | 16 | A list: `lacks`, with no text of the rules. |
| `matches` | `bridge_text_t` | 24 | A list: `matches`. |
| `matches_not` | `bridge_text_t` | 32 | A list: `matches_not`. |
| `order` | `bridge_text_t` | 40 | A list: `order`. |
| `output` | `bridge_text_t` | 48 | `output`. |
| `files` | `bridge_text_t` | 56 | A map: each path of `files`, then its text. |
| `status` | `int32_t` | 64 | `status`. |
| `status_not` | `int32_t` | 68 | `status_not`. |
| `stated` | `mpbt_claim_keys_t` | 72 | The claims that the table states. A field of a claim that it does not state holds no bytes, or 0. |

Bytes 74 and 75 hold no field.

### mpbt:mpbt_claim_keys_t

`mpbt_claim_keys_t` is a bitmask of `uint16_t`. A bit is set if the table of the claims states its key.

| Constant | Value | Key |
| --- | --- | --- |
| `MPBT_CLAIM_STATUS` | `0x1` | `status` |
| `MPBT_CLAIM_STATUS_NOT` | `0x2` | `status_not` |
| `MPBT_CLAIM_LINE` | `0x4` | `line` |
| `MPBT_CLAIM_HAS` | `0x8` | `has` |
| `MPBT_CLAIM_LACKS` | `0x10` | `lacks` |
| `MPBT_CLAIM_MATCHES` | `0x20` | `matches` |
| `MPBT_CLAIM_MATCHES_NOT` | `0x40` | `matches_not` |
| `MPBT_CLAIM_ORDER` | `0x80` | `order` |
| `MPBT_CLAIM_OUTPUT` | `0x100` | `output` |
| `MPBT_CLAIM_FILES` | `0x200` | `files` |

## mpbt:ScriptStep

Each step of a script is an entity with `mpbt:ScriptStep`. Its owner is the entity of the case, or of the false variant.
`mpbt_script_step_t` takes 56 bytes. Its alignment is 8.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `owner` | `uint64_t` | 0 | The id of the entity of the case, or of the false variant. |
| `wait` | `bridge_text_t` | 8 | With `MPBT_SCRIPT_WAIT`: the text. |
| `put` | `bridge_text_t` | 16 | With `MPBT_SCRIPT_PUT`: a map, each path then its artifact or file. |
| `remove` | `bridge_text_t` | 24 | With `MPBT_SCRIPT_REMOVE`: a list of files. |
| `type` | `bridge_text_t` | 32 | With `MPBT_SCRIPT_TYPE`: the text. |
| `pause` | `double` | 40 | With `MPBT_SCRIPT_PAUSE`: the seconds. |
| `order` | `uint32_t` | 48 | The place of the step in its script, from 0. |
| `signal` | `mpbt_signal_t` | 52 | With `MPBT_SCRIPT_SIGNAL`: the signal. |
| `actions` | `mpbt_script_actions_t` | 53 | The actions of the step. |

Bytes 54 and 55 hold no field.

### mpbt:mpbt_signal_t

`mpbt_signal_t` is an enum of `uint8_t`.

| Constant | Value | Signal |
| --- | --- | --- |
| `MPBT_SIGNAL_INTERRUPT` | 1 | `interrupt` |
| `MPBT_SIGNAL_TERMINATION` | 2 | `termination` |
| `MPBT_SIGNAL_HANG_UP` | 3 | `hang-up` |

### mpbt:mpbt_script_actions_t

`mpbt_script_actions_t` is a bitmask of `uint8_t`. A bit is set if the step does its action.

| Constant | Value | Action |
| --- | --- | --- |
| `MPBT_SCRIPT_WAIT` | `0x1` | `wait` |
| `MPBT_SCRIPT_PUT` | `0x2` | `put` |
| `MPBT_SCRIPT_REMOVE` | `0x4` | `remove` |
| `MPBT_SCRIPT_TYPE` | `0x8` | `type` |
| `MPBT_SCRIPT_CLOSE` | `0x10` | `close` |
| `MPBT_SCRIPT_SIGNAL` | `0x20` | `signal` |
| `MPBT_SCRIPT_PAUSE` | `0x40` | `pause` |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Tests` | `mpbt_tests_t` | `mpbt_tests_t_desc` | `MPBT_TESTS_FIELDS` |
| `mpbt:TestRule` | `mpbt_test_rule_t` | `mpbt_test_rule_t_desc` | `MPBT_TEST_RULE_FIELDS` |
| `mpbt:Case` | `mpbt_case_t` | `mpbt_case_t_desc` | `MPBT_CASE_FIELDS` |
| `mpbt:Run` | `mpbt_run_t` | `mpbt_run_t_desc` | `MPBT_RUN_FIELDS` |
| `mpbt:FalseVariant` | `mpbt_false_variant_t` | `mpbt_false_variant_t_desc` | `MPBT_FALSE_VARIANT_FIELDS` |
| `mpbt:mpbt_claim_keys_t` | `mpbt_claim_keys_t` | `mpbt_claim_keys_t_desc` | `MPBT_CLAIM_KEYS_VALUES` |
| `mpbt:Claims` | `mpbt_claims_t` | `mpbt_claims_t_desc` | `MPBT_CLAIMS_FIELDS` |
| `mpbt:HelperClaims` | `mpbt_helper_claims_t` | `mpbt_helper_claims_t_desc` | `MPBT_CLAIMS_FIELDS` |
| `mpbt:mpbt_signal_t` | `mpbt_signal_t` | `mpbt_signal_t_desc` | `MPBT_SIGNAL_VALUES` |
| `mpbt:mpbt_script_actions_t` | `mpbt_script_actions_t` | `mpbt_script_actions_t_desc` | `MPBT_SCRIPT_ACTIONS_VALUES` |
| `mpbt:ScriptStep` | `mpbt_script_step_t` | `mpbt_script_step_t_desc` | `MPBT_SCRIPT_STEP_FIELDS` |

```text
{ bridge_text_t cases; bridge_text_t writers; uint32_t timeout; uint32_t copies; }
{ bridge_text_t lacks; bridge_text_t exempt; }
{ bridge_text_t group; bridge_text_t name; uint32_t index; bool alone; }
{ bridge_text_t run; bridge_text_t env; bridge_text_t unset; bridge_text_t input; bridge_text_t files; bridge_text_t folders; bridge_text_t fail; bridge_text_t helper_run; bridge_text_t helper_wait; bridge_text_t helper_input; bool ignore_interrupt; }
{ uint64_t owner; }
uint16_t { MPBT_CLAIM_STATUS = 0x1, MPBT_CLAIM_STATUS_NOT = 0x2, MPBT_CLAIM_LINE = 0x4, MPBT_CLAIM_HAS = 0x8, MPBT_CLAIM_LACKS = 0x10, MPBT_CLAIM_MATCHES = 0x20, MPBT_CLAIM_MATCHES_NOT = 0x40, MPBT_CLAIM_ORDER = 0x80, MPBT_CLAIM_OUTPUT = 0x100, MPBT_CLAIM_FILES = 0x200 }
{ bridge_text_t line; bridge_text_t has; bridge_text_t lacks; bridge_text_t matches; bridge_text_t matches_not; bridge_text_t order; bridge_text_t output; bridge_text_t files; int32_t status; int32_t status_not; mpbt_claim_keys_t stated; }
uint8_t { MPBT_SIGNAL_INTERRUPT = 1, MPBT_SIGNAL_TERMINATION = 2, MPBT_SIGNAL_HANG_UP = 3 }
uint8_t { MPBT_SCRIPT_WAIT = 0x1, MPBT_SCRIPT_PUT = 0x2, MPBT_SCRIPT_REMOVE = 0x4, MPBT_SCRIPT_TYPE = 0x8, MPBT_SCRIPT_CLOSE = 0x10, MPBT_SCRIPT_SIGNAL = 0x20, MPBT_SCRIPT_PAUSE = 0x40 }
{ uint64_t owner; bridge_text_t wait; bridge_text_t put; bridge_text_t remove; bridge_text_t type; double pause; uint32_t order; mpbt_signal_t signal; mpbt_script_actions_t actions; }
```

`mpbt:Claims` and `mpbt:HelperClaims` have one descriptor, from one macro.

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Tests` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:TestRule` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Case` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Run` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:FalseVariant` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_claim_keys_t` | `BRIDGE_BITMASK` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Claims` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:HelperClaims` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_signal_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_script_actions_t` | `BRIDGE_BITMASK` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:ScriptStep` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare the enums and the bitmasks first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Tests` | `read`, from the settings | The tests. Each other module with a grant. |
| Each other type | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `<path>: a case has no key <keys>` | A case has a key that the table *[[case]]* does not give. |
| `<path>: a false has no key <keys>` | A false variant has a key that *The false variant* does not give. |
| `<path>: a helper has no key <keys>` | A helper has a key other than `run`, `wait`, `stdin` and `claims`. |
| `<path>: a script has no key <keys>` | A step of a script has a key that *Scripts* does not give. |
| `a case: a claims has no key <keys>` | A table of claims has a key that *Claims* does not give. |
| `<path>: the case <name> claims nothing` | A case has no claim. |
| `<path>: the case <name> has no false variant` | A case has no `false`. |
| `<path>: the case <name> ignores <signals>, and only interrupt can be ignored` | `ignore` holds a signal other than `interrupt`. |
| `<path>: the case <name> waits for a line after it closes the output` | A step `wait` comes after a step `close`. |
| `<path>: the case <name> closes <what>, and only the output can close` | `close` is not `"output"`. |
| `<path>: the case <name> sends <signal>, and the signals are interrupt, termination and hang-up` | `signal` names a different signal. |
| `<path>: the case <name> sends a signal after a hang-up, and on Windows a hang-up ends the console` | A signal comes after a hang-up. |
| `<path>: the case <name> pauses <pause>, and a pause is a number of seconds above 0` | `pause` is not a number above 0. |
| `<path>: the case <name> sends an interrupt and a termination, and on Windows a termination turns off the interrupt` | A script sends both. |
| `<path>: the case <name> uses <form> in a pattern, which mpbt does not have` | A pattern has a form that *Claims* does not give. |
| `<path>: the case <name> has a pattern of more than 65536 steps` | The repeats of a pattern make it too long. |
| `no case: <folder> holds no case` | The folder of the cases holds no case. `test` then ends with 0. |
| `no case has <text> in its name` | `-k` matches no case. |
| `.toolchain/project.toml: write [test] copies` | No `--copies`, and no `copies`. |
| `<call> failed: error <code>` | Windows refused to make the console of a command. |
| `GenerateConsoleCtrlEvent failed: error <code>` | Windows refused to send a termination. |
| `<case>: <verdict>` | mpbt writes the verdict of each case. With `--break`, `<case>, made false: <verdict>`. |
| `<verdict> in <failed> of <copies> copies` | The verdict of a case when some of its copies failed. |
| `  ended with <status>, and printed:` | A case failed: the status of its command, then the output. For the helper, `  the helper ended with <status>, and printed:`. |
| `<group>: <count> cases: <passed> as written` | mpbt writes the result of each group. |
| `<group>: <count> claims made false: <failed> cases failed` | The same, with `--break`. |
| `round <round> of <rounds>` | mpbt starts a round of `--rounds`. |
| `not as written: <cases>` | Cases failed. |
| `still as written with their claims made false: <cases>` | Cases passed with `--break`. |
| `<said> is not there: run test first` | The messages of the code are checked with no `said.txt`. |
| `<path>:<line>: no case wrote: <message>` | No case wrote a message of the code. |
| `<path>:<line>: no document quotes: <message>` | No document quotes a message of the code. |
