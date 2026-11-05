# src/runner/runner_commands.c

This file writes the commands of the needs for the system and the processor of a machine: `docs/extern/mpbt_ci.h.md`, *runner*.
`say` writes each command as one line, and `say_format` writes each command that holds a value.

## Linux

1. With a package to install, `say` writes `sudo apt-get update`.
2. `write_install` writes one line `sudo apt-get install -y`, with each package of each need of `needs`.
3. With `MPBT_NEED_DISPLAY`, `write_lines` writes the commands of *The display*.

`PACKAGES` holds each package with its need, in the order of the names. Thus the line needs no sort.
`write_install` makes the line in an array of 128 bytes. The command and the 8 names take at most 110 bytes, so the line needs no allocation.

| Package | Need |
| --- | --- |
| `libgl1` | `MPBT_NEED_GL` |
| `libgl1-mesa-dri` | `MPBT_NEED_GL` |
| `libglx-mesa0` | `MPBT_NEED_GL` |
| `libvulkan1` | `MPBT_NEED_VULKAN` |
| `mesa-vulkan-drivers` | `MPBT_NEED_VULKAN` |
| `openbox` | `MPBT_NEED_DISPLAY` |
| `weston` | `MPBT_NEED_DISPLAY` |
| `xvfb` | `MPBT_NEED_DISPLAY` |

## The display

`DISPLAY` holds these commands, in this order:

1. Xvfb starts on the display `:99`, with a screen of 1920 by 1080 pixels and 24 bits.
2. A wait of at most 10 seconds for its socket in `/tmp/.X11-unix`, then Openbox starts on `:99`.
3. `mkdir` makes the folder `$RUNNER_TEMP/wayland`, which only its owner can read, write and open.
4. weston starts in that folder: backend `headless`, renderer `pixman`, socket `wayland-1`, and `--no-config`.
5. A wait of at most 10 seconds for the socket of weston.
6. `DISPLAY`, `WAYLAND_DISPLAY` and `XDG_RUNTIME_DIR` go into `$GITHUB_ENV`, for the next steps of the job.

The 3 servers run in the background, with their output in `/dev/null`. A wait that ends with no socket fails the step.

## Windows

With `MPBT_NEED_GL`, `write_mesa` writes the commands of `GL`:

1. `curl` downloads `mesa-llvmpipe-<arch>-26.2.5.7z` of the release `26.2.5` of `mmozeiko/build-mesa` into `$RUNNER_TEMP/mesa`.
2. `sha256sum` compares the digest of the archive with the digest of `MESA`.
3. The `tar.exe` of `System32` unpacks `opengl32.dll`. The `tar` of Git cannot unpack a `.7z`.
4. The whole path of the file goes into `SDL_OPENGL_LIBRARY`, through `$GITHUB_ENV`.

`MESA` gives the archive of each processor of Windows:

| Processor | `<arch>` | SHA-256 |
| --- | --- | --- |
| `AMD64` | `x64` | `d1b713ca2a7fba47a50c058099f13c435ddb76a16a422c334e4d787f9755a31d` |
| `ARM64` | `arm64` | `e7df75398d50e07a68bbffa5cff2ece4c85e5f8ef8bda497f560dd04fe60cbbd` |

The targets of Windows run on `AMD64` and on `ARM64`: `docs/extern/mpbt_target.h.md`, *The targets*.
`write_mesa` writes nothing for a processor that `MESA` does not hold.
`MPBT_NEED_DISPLAY` and `MPBT_NEED_VULKAN` give no command on Windows, because the runner has a desktop and WARP.

## macOS

`Darwin` gets no command, because its runner has each need.

## The line ends

`bash` reads a carriage return as a part of a command. Thus each line must end with `\n` alone, also on Windows.
`say` gives each line that end on each system: `docs/intern/shared/say/say.c.md`.

## Functions

| Function | Result |
| --- | --- |
| `runner_write_commands` | Writes the commands for one machine. |
| `write_install` | Writes the line of `apt-get install`, if a need has a package. |
| `write_lines` | Writes each line of a list. |
| `write_mesa` | Writes the commands of `GL`, with the archive of the processor. |
