# src/cla/cla_signatures.c

This file reads the record of the authors who signed: the file `CLA_FILE` on the branch `CLA_BRANCH`.

## The steps

1. `cla_call` sends `GET` for the contents of `CLA_FILE`, at the reference `CLA_BRANCH`.
2. A 404 gives an empty record with no version, because no author signed yet.
3. `cla_get_text` gives `content` and `sha` of the answer. `sha` is the version of the file.
4. `cla_base64_decode` turns `content` into the bytes of the file.
5. `read_items` reads the list with `json_next`, and `read_item` reads each object of it.
6. An object gives `name`, `day` and `pull_request`, and `json_skip` skips each other key.

The record keeps the order of its items.
`cla_has_signer` compares the author with the `name` of each item, byte by byte.

## The faults

An answer that lacks `content` or `sha` is a fault. So is a `content` that is not base64, or a file that is not a list of objects.
Each of them is the fault of an answer: `docs/intern/cla/cla.h.md`, *The faults*.

## Functions

| Function | Result |
| --- | --- |
| `cla_get_signatures` | `true` and the record, or `false` and the fault. |
| `cla_has_signer` | Whether the record names the author. |
| `cla_free_record` | Gives the memory of the record back. |
| `read_items` | The items of the list. |
| `read_item` | The 3 keys of one item. |
