# src/cla/cla_find.c

This file finds the values of a path of keys in a document of JSON, with the reader of `src/shared/json/json.h`.
The event and the answers of GitHub are such documents.

## A path

A path is the names of the keys from the top, with `.` between 2 names, for example `pull_request.head.sha`.
An item of a list adds no name. Thus the path `body` reaches the `body` of each item of a list of comments.

## The steps

1. `json_open` starts a reader on the bytes, and `fill_memory` gives all of them at the first call.
2. `descend` reads one value. In an object, a key that is the next name of the path leads one level down.
3. `json_skip` skips the value of each other key.
4. In a list, each item gets the same path.
5. A text or a number at the end of the path goes to the function of the caller. That function can stop the walk.
6. `JSON_FAULT` stops the walk.

`cla_get_text` gives the first value of a path, and stops the walk there.

## Functions

| Function | Result |
| --- | --- |
| `cla_find` | `true` after the walk, or `false` for a document that is not JSON. |
| `cla_get_text` | `true` and the first value of a path, or `false` for a document with no such value. |
| `descend` | Walks one value, with the rest of the path. |
| `fill_memory` | The bytes of the document, for the reader. |
