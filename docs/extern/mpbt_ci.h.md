# include/mpbt_ci.h

`include/mpbt_ci.h` gives `mpbt:Ci`: what the cases of a project need from a runner of the workflows, for example a display.

## [ci]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `needs` | list | `[]` | The needs of the cases: `display`, `vulkan` or `gl`. |

```toml
[ci]
needs = ["display", "vulkan"]
```

## runner

The workflows `ci` and `release` run `mpbt runner --target <target>`, and give its output to `bash -e`, before the step that fetches.
`runner` writes the commands for the target, from the system and the processor of its `runs_on`.
With no need, or with no need on that system, it writes nothing.

| Need | Linux | Windows | macOS |
| --- | --- | --- | --- |
| `display` | Xvfb on the display `:99`, with Openbox on it, then the server of Wayland weston, with no screen. | Nothing: the runner has a desktop. | Nothing: the runner has a desktop. |
| `vulkan` | The packages `libvulkan1` and `mesa-vulkan-drivers`, which give lavapipe on the processor. | Nothing: WARP, the Direct3D 12 of the processor, is part of Windows. | Nothing: Metal is part of macOS. |
| `gl` | The packages `libgl1`, `libglx-mesa0` and `libgl1-mesa-dri`. | `opengl32.dll` of Mesa 26.2.5, from the releases of `mmozeiko/build-mesa`, with its digest checked. | Nothing: OpenGL is part of macOS. |

On Linux, the commands run `sudo apt-get update`, then one `sudo apt-get install -y` with the packages of all the needs, in the order of their names.
The display puts `DISPLAY`, `WAYLAND_DISPLAY` and `XDG_RUNTIME_DIR` into the environment of the next steps.
On Windows, `gl` puts the full path of `opengl32.dll` into `SDL_OPENGL_LIBRARY`.
Windows finds the `opengl32.dll` of `System32` before the folders of `PATH`, so a library that loads OpenGL needs that path.

## mpbt:Ci

`mpbt:Ci` holds `[ci]`. `mpbt:Ci` is a singleton: the settings of `runner`.
`mpbt_ci_t` takes 1 byte. Its alignment is 1.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `needs` | `mpbt_needs_t` | 0 | The needs. |

### mpbt:mpbt_needs_t

`mpbt_needs_t` is a bitmask of `uint8_t`. A bit is set if `needs` holds its need.

| Constant | Value | Need |
| --- | --- | --- |
| `MPBT_NEED_DISPLAY` | `0x1` | `display` |
| `MPBT_NEED_VULKAN` | `0x2` | `vulkan` |
| `MPBT_NEED_GL` | `0x4` | `gl` |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:mpbt_needs_t` | `mpbt_needs_t` | `mpbt_needs_t_desc` | `MPBT_NEEDS_VALUES` |
| `mpbt:Ci` | `mpbt_ci_t` | `mpbt_ci_t_desc` | `MPBT_CI_FIELDS` |

```text
uint8_t { MPBT_NEED_DISPLAY = 0x1, MPBT_NEED_VULKAN = 0x2, MPBT_NEED_GL = 0x4 }
{ mpbt_needs_t needs; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:mpbt_needs_t` | `BRIDGE_BITMASK` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Ci` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |

Declare the bitmask first.

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Ci` | `read`, from the settings | `runner`. Each other module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `[ci] needs: <need> is not a need: display gl vulkan` | `needs` holds an unknown need. |
| `<commands>` | `runner` writes its commands, one on each line. |
