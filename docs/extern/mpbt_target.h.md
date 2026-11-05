# include/mpbt_target.h

`include/mpbt_target.h` gives `mpbt:Target`, the targets that mpbt can build for, and `mpbt_system_t`, the families of systems.

## The targets

mpbt gives 6 targets: three systems on two kinds of processor.
A run builds for one target: `--target`, or the target of this machine.
`fetch` always uses the target of this machine, and `test` refuses a target that does not run here.

| Target | `runs_on` | `system` | `triple` | `cpu` |
| --- | --- | --- | --- | --- |
| `x86_64-windows-gnu` | `Windows`, `AMD64` | `windows` | `x86_64-windows.win10...win11_dt-gnu` | `x86_64` |
| `x86_64-linux-gnu` | `Linux`, `x86_64` | `posix` | `x86_64-linux.5.10.0...6.19.0-gnu.2.31.0` | `x86_64` |
| `aarch64-macos` | `Darwin`, `arm64` | `posix` | `aarch64-macos.13.0.0...15.6.0` | `apple_m1` |
| `aarch64-linux-gnu` | `Linux`, `aarch64` | `posix` | `aarch64-linux.5.10.0...6.19.0-gnu.2.31.0` | `generic` |
| `x86_64-macos` | `Darwin`, `x86_64` | `posix` | `x86_64-macos.13.0.0...15.6.0` | `core2` |
| `aarch64-windows-gnu` | `Windows`, `ARM64` | `windows` | `aarch64-windows.win10...win11_dt-gnu` | `generic` |

## The keys of a target

Each key of a target is a variable with `MPBT_SCOPE_TARGET`: `docs/extern/mpbt_project.h.md`, *mpbt:Variable*.

| Key | Value |
| --- | --- |
| `runs_on` | The name of the system and of the processor of a machine of the target. |
| `system` | The family of the system: `posix` or `windows`. |
| `triple` | The target for zig, with the range of the versions of the system. |
| `cpu` | The model of the processor. |
| `exe` | The extension of a program: `.exe` on Windows, else no text. |
| `library` | The extension of a shared library: `.dll`, `.so` or `.dylib`. |
| `define` | The macros that the system needs: `-D_DEFAULT_SOURCE` on Linux. |
| `pic` | The flags for the code of a shared library: `-fPIC`, except on Windows. |
| `rpath` | The flags that tell a program to find a library in its own folder. |
| `soname` | The flags that give a shared library its name, with no folder. |
| `stack` | The flag of the linker for a stack of 16 MiB. |
| `errno` | The flag that tells whether the math library sets `errno`. |
| `runtime` | The sources that each shared library of the target adds. Only `x86_64-windows-gnu` has them, in `{toolchain}/runtime`. |

A table `[targets.<target>]` of the project can add keys to a target, for example a digest of a source.
It cannot give a key that mpbt gives.

## mpbt:Target

Each target is an entity with `mpbt:Target`.
`mpbt_target_t` takes 12 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | The name of the target. |
| `here` | `bool` | 8 | `true` if the `runs_on` of the target names this machine. |

Bytes 9 to 11 hold no field.

## mpbt:mpbt_system_t

`mpbt_system_t` is an enum of `uint8_t`. An exception of a check names the systems where it applies with it.

| Constant | Value | The exception applies |
| --- | --- | --- |
| `MPBT_SYSTEM_EVERY` | 1 | On each system. |
| `MPBT_SYSTEM_POSIX` | 2 | On Linux and on macOS. |
| `MPBT_SYSTEM_WINDOWS` | 3 | On Windows. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Target` | `mpbt_target_t` | `mpbt_target_t_desc` | `MPBT_TARGET_FIELDS` |
| `mpbt:mpbt_system_t` | `mpbt_system_t` | `mpbt_system_t_desc` | `MPBT_SYSTEM_VALUES` |

```text
{ bridge_text_t name; bool here; }
uint8_t { MPBT_SYSTEM_EVERY = 1, MPBT_SYSTEM_POSIX = 2, MPBT_SYSTEM_WINDOWS = 3 }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Target` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:mpbt_system_t` | `BRIDGE_ENUM` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Target` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `no target runs on <system> <machine>: name one` | No target runs on this machine, and the run gives no `--target`. |
| `no target runs here: name one` | No target runs on this machine, and a command needs one: `join` or `clean` with no `--target`, or `load` with a `[[load]]`. |
| `no target <target>; the targets: <targets>` | `--target` names no target. |
| `<target> does not run here: build it, and test it where it runs` | `test` gets a target of a different machine. |
| `fetch runs on a machine of a target` | `fetch` runs on a machine of no target. |
| `no machine runs the target <target>` | `runner` gets a target that no machine runs. |
