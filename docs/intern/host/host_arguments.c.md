# src/host/host_arguments.c

This file reads the command line of mpbt into the settings of the module `read`: `docs/extern/mpbt_command.h.md`, *The options*.

## The steps

1. The first argument names the command. Each other argument is an option, or the value of the option before it.
2. Each option must be an option of the command, and each option that takes a value must get its value.
3. `--copies` and `--rounds` take a whole number from 1. `--tag` takes the form of a tag.
4. `--branches` and `--leaks` refuse the options that `docs/extern/mpbt_command.h.md`, *The options*, names.
5. Each option goes into one setting of `read`, which fills `mpbt:Command` from it:
   - a text for `--root`, `--target`, `--out`, `--tag`, `--leave`, `--commits` and `-k`;
   - a list of lines for `--part`, `--set` and `--decide`;
   - an integer for `--copies` and `--rounds`;
   - the bits of `mpbt_options_t` for each option of the line, and the name of the command.

A wrong line writes its message of `docs/extern/mpbt_command.h.md`, *Messages*, and the host ends with 2.

## Functions

| Function | Result |
| --- | --- |
| `host_arguments` | The settings of `read`, or 2 after a message. |
| `take_option` | Takes one option, and its value if it has one. |
| `take_number` | Takes a whole number from 1, or refuses the value. |
