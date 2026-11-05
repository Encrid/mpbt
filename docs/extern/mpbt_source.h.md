# include/mpbt_source.h

`include/mpbt_source.h` gives `mpbt:Source`: an archive of files of a different maker, which `fetch` gets, for example a release of a library.

## [[source]]

Put the patches of a source and its licence into `third_party/<source>`.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `name` | text | none | The name. The variable `{<name>}` is the folder `top` in the folder `into`. |
| `url` | text | none | The address of the archive. A text with no `://` names a file of the project. |
| `sha256` | text | none | The SHA-256 digest of the archive. |
| `into` | text | none | The folder that gets the files, for example `{build}/third_party/<source>`. |
| `top` | text | no text | The folder of the archive that holds the files, for example `{target}`. |
| `patches` | list | `[]` | The patches, as files of the project, in the order that `fetch` applies them. |

```toml
[[source]]
name = "sample"
url = "https://example.org/sample-1.0.tar.gz"
sha256 = "<digest>"
into = "{build}/third_party/sample"
top = "sample-1.0"
patches = ["third_party/sample/fix.patch"]
```

## fetch

For each source, `fetch` does these steps:

1. It removes the folder `into`, makes it again, and downloads the archive into it.
2. It stops if the digest of the archive is not `sha256`, and removes the archive.
3. It unpacks the archive, and removes it.
4. It applies each patch to the files of `top`, in the order of the list.
5. It writes `fetched.txt` into `into`, with the digest of the archive and of each patch.

`fetch` does not download a source again if its `fetched.txt` holds these digests.
`build`, `pack` and `test` download nothing. They stop if a `fetched.txt` does not hold the digests of the config.

An archive is a zip, a tar, or a tar with gzip or xz: its name ends with `.zip`, `.tar`, `.tar.gz` or `.tar.xz`.
mpbt keeps the files, the folders, the links and the execute bits of an archive.
On Windows, a link needs the Developer Mode or the rights of an administrator. Without them, mpbt copies the target of the link to its path.
It refuses a path of an archive that leaves the folder `into`.

A patch has a part for each file, from its line `diff --git`, and names the file in its line `+++ b/<file>`.
A part applies only if each line of its context is in the file, at the line that the part gives.
A patch can end its lines as Windows does, or as Linux does.

The release of a part has a folder for each target, in one zip: `docs/extern/mpbt_compose.h.md`, *The release*.
With `top = "{target}"`, one source with one digest takes that zip for each target.

## zig

`fetch` also gets zig, when zig is not there. Its zig goes beside the program mpbt, in the folder `zig`.
Each command uses that zig, or else the zig on the path, if its version is the version of mpbt.

The version is `0.17.0`, and the address is `https://ziglang.org/download/0.17.0/zig-<host>-0.17.0.<format>`.

| Target of this machine | `<host>` | `<format>` | SHA-256 |
| --- | --- | --- | --- |
| `x86_64-windows-gnu` | `x86_64-windows` | `zip` | `b5663f69581dcf391293fbf16c06cb80d81d806545ce618b4d0bab7f0eb8c428` |
| `x86_64-linux-gnu` | `x86_64-linux` | `tar.xz` | `1cbe9df9f27e6b78d14ccbca43b6703a404ef79ef1c463de901d7f088d4e2026` |
| `aarch64-macos` | `aarch64-macos` | `tar.xz` | `b607e9b9234790a008116ae5bdb71c6243b84b9fb42a53a9e70fde41c06c536a` |
| `aarch64-linux-gnu` | `aarch64-linux` | `tar.xz` | `9e8d11661d4ae3bd57702a3832781e23ad151dde5798e16a5ccd503f65234ff8` |
| `x86_64-macos` | `x86_64-macos` | `tar.xz` | `4f9a1c5269aa17ebda5e6d3c2b89d6cbf36f7d2b22a0306e9ab98f25f95529c6` |
| `aarch64-windows-gnu` | `aarch64-windows` | `zip` | `0a59d91fa1cb40cf068e9b0954434ce973500c7a2ea749f1e01af62cdab52d26` |

mpbt downloads with the program `curl`, and checks each digest itself.

## mpbt:Source

Each source is an entity with `mpbt:Source`.
`mpbt_source_t` takes 48 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `name` | `bridge_text_t` | 0 | `name`. |
| `url` | `bridge_text_t` | 8 | `url`. |
| `sha256` | `bridge_text_t` | 16 | `sha256`. |
| `into` | `bridge_text_t` | 24 | `into`. |
| `top` | `bridge_text_t` | 32 | `top`, or no bytes. |
| `patches` | `bridge_text_t` | 40 | A list: `patches`. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Source` | `mpbt_source_t` | `mpbt_source_t_desc` | `MPBT_SOURCE_FIELDS` |

```text
{ bridge_text_t name; bridge_text_t url; bridge_text_t sha256; bridge_text_t into; bridge_text_t top; bridge_text_t patches; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Source` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Source` | `read` | Each module with a grant. |

## Messages

| Message | When |
| --- | --- |
| `a source: a source has no key <keys>` | A table `[[source]]` has a key that the table above does not give. |
| `<name> is not fetched as project.toml states: run fetch` | A command other than `fetch` finds no `fetched.txt` with the digests of the config. |
| `<archive> is not what the maker publishes: its sha256 is <digest>` | An archive has a different digest. |
| `<patch> does not apply to <name>` | A part of a patch does not match its file. |
| `<path> leaves the folder of <name>` | A path of an archive is outside the folder `into`. |
| `<url> is not there: curl ended with <status>` | `curl` cannot download the archive. |
| `curl is not on the path, and fetch needs it` | This machine has no `curl`. |
| `zig is fetched on a machine that runs a target` | No target runs on this machine. |
| `the archive holds no zig <version>` | The archive of zig holds no zig of the version of mpbt. |
| `zig <version> is neither fetched nor on the path` | No zig of the version of mpbt is there. |
| `<zig>` | `fetch` writes the path of zig. |
