# src/shared/archive/archive_stream.c

This file gives the bytes of the tar inside a `.tar.gz` or a `.tar.xz`, into a `buffer_t`. Then `read_tar` reads them.

## gzip

The format is RFC 1952: https://www.rfc-editor.org/rfc/rfc1952.

1. The header starts with the bytes `1f 8b` and the method 8. Its flags tell which fields of names and comments follow, and `gunzip` skips them.
2. `tinfl_decompress` of miniz inflates the deflate stream into the buffer, as it grows.
3. The last 8 bytes hold the CRC-32 and the length of the bytes. A different value stops with a finding.

## xz

XZ Embedded decodes the stream: https://github.com/tukaani-project/xz-embedded/archive/refs/tags/v20240322.tar.gz.

1. `xz_crc32_init` and `xz_crc64_init` make the tables of the checks.
2. `xz_dec_init` with `XZ_DYNALLOC` starts a decoder that takes the memory of the dictionary as the stream needs it.
3. `xz_dec_run` takes the bytes and fills the buffer, until it gives `XZ_STREAM_END`. Each other end stops with a finding.
4. `xz_dec_end` gives the memory of the decoder back.

## Functions

| Function | Result |
| --- | --- |
| `gunzip` | The bytes inside a gzip, or a finding. |
| `unxz` | The bytes inside an xz, or a finding. |
| `skip_gzip_header` | The offset of the deflate stream. |
