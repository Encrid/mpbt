# include/mpbt_check.h

`include/mpbt_check.h` gives the settings of the checks and their exceptions: `mpbt:TextCheck`, `mpbt:LayoutCheck`, `mpbt:StyleCheck`, `mpbt:ProseCheck`, `mpbt:Retired`, `mpbt:Make` and `mpbt:StyleException`.

## The checks

`check` runs these checks, in this order, on the files of the project: `docs/extern/mpbt_file.h.md`.
The guides of `docs/contributing` give their rules.

| Check | What it checks |
| --- | --- |
| `layout` | The files and the folders that a project needs and allows, and the document of each file of `include`, `src` and `tools`. |
| `workflows` | The targets of the matrix of each workflow. |
| `text` | The legal notice and the comments of the scripts, the characters, the retired words and the refused calls. |
| `prose` | The sentences, the paragraphs, the tags of the blocks of code and the readme. |
| `pseudo` | The pseudo code. |
| `xref` | The paths and the headings that the documents cite. |
| `dup` | A passage of 8 words or more in 2 documents. |
| `cover` | Each public name of a header, in a code span of its document. |
| `licence` | `license`, `cla.md`, and the licence of each source of `third_party`. |
| `commits` | The messages of the commits of `--commits`, or of the last commit. |
| `style` | The coding style of the code. |
| `c23` | The older spellings that C23 replaces. |

## [check]

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `unicode` | list | `[]` | The paths of the files that can hold text that is not ASCII. A path can hold `*`. |
| `guides` | list | `[]` | The guides that the project adds to `docs/contributing`, beside the 8 guides, for example `timings.md`. |
| `retired` | table | `{}` | The retired words. A key is a word, and its value is the word to write, or no text. |
| `makes` | table | `{}` | The macros whose call makes a public name of their first argument. A value is the end that the name gets, or no text. |
| `refuse` | list | `[]` | The paths of lists of the calls that the code must not make, with one name on each line. |

```toml
[check]
unicode = ["docs/extern/names.md"]
refuse = ["{sample}/gaps.txt"]

[check.retired]
utilise = "use"

[check.makes]
SAMPLE_MAKE_TYPE = ""
SAMPLE_MAKE_DESC = "_desc"
```

## [[style.exception]]

An exception lets one file break one rule of the style: `docs/contributing/coding_style.md`, *Exceptions*, gives its keys.
`check` refuses an exception with no `why`, as `test --branches` and `test --leaks` do for their exceptions.

## [style]

`[style]` holds the limits of `docs/contributing/coding_style.md`, each with the rule that it bounds.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `columns` | integer | 80 | The most columns of a line: F3. |
| `lines` | integer | 20 | The most lines of the body of a function: F4. |
| `functions` | integer | 5 | The most functions of a file: O3. |
| `arguments` | integer | 4 | The most arguments of a function: F5. |
| `branches` | integer | 3 | The most branches of a chain of `if` and `else`: C1. |
| `depth` | integer | 2 | The most levels of conditional branches inside each other: C1. |

## [prose]

`[prose]` gives the limits of the rules of `docs/contributing/documentation_style.md`, *Simplified Technical English*.

| Key | Type | Default | Value |
| --- | --- | --- | --- |
| `sentence` | integer | 25 | The most words of a sentence. |
| `step` | integer | 20 | The most words of a sentence of a numbered list. |
| `paragraph` | integer | 6 | The most sentences of a paragraph. |
| `description` | integer | 119 | The most characters of the description of the readme. |

## mpbt:TextCheck

`mpbt:TextCheck` holds `unicode` and `refuse`. `mpbt:TextCheck` is a singleton: the settings of the check `text`.
`mpbt_text_check_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `unicode` | `bridge_text_t` | 0 | `unicode`, with each path on its own line. |
| `refuse` | `bridge_text_t` | 8 | `refuse`, with each path on its own line. |

## mpbt:LayoutCheck

`mpbt:LayoutCheck` holds `guides`. `mpbt:LayoutCheck` is a singleton: the settings of the check `layout`.
`mpbt_layout_check_t` takes 8 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `guides` | `bridge_text_t` | 0 | `guides`, with each name on its own line. |

## mpbt:StyleCheck

`mpbt:StyleCheck` holds the keys of `[style]`. It is a singleton: the limits of the check `style`.
`mpbt_style_check_t` takes 24 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `columns` | `uint32_t` | 0 | `columns`. |
| `lines` | `uint32_t` | 4 | `lines`. |
| `functions` | `uint32_t` | 8 | `functions`. |
| `arguments` | `uint32_t` | 12 | `arguments`. |
| `branches` | `uint32_t` | 16 | `branches`. |
| `depth` | `uint32_t` | 20 | `depth`. |

## mpbt:ProseCheck

`mpbt:ProseCheck` holds the keys of `[prose]`. It is a singleton: the limits of the check `prose`.
`mpbt_prose_check_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `sentence` | `uint32_t` | 0 | `sentence`. |
| `step` | `uint32_t` | 4 | `step`. |
| `paragraph` | `uint32_t` | 8 | `paragraph`. |
| `description` | `uint32_t` | 12 | `description`. |

## mpbt:Retired

Each retired word is an entity with `mpbt:Retired`.
`mpbt_retired_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `word` | `bridge_text_t` | 0 | The retired word. |
| `text` | `bridge_text_t` | 8 | The word to write, or no bytes. |

## mpbt:Make

Each macro of `makes` is an entity with `mpbt:Make`.
`mpbt_make_t` takes 16 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `macro` | `bridge_text_t` | 0 | The name of the macro. |
| `suffix` | `bridge_text_t` | 8 | The end of the public name, or no bytes. |

## mpbt:StyleException

Each exception of the style is an entity with `mpbt:StyleException`.
`mpbt_style_exception_t` takes 24 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `rule` | `bridge_text_t` | 0 | The rule, for example `F4`. |
| `path` | `bridge_text_t` | 8 | The path, with `:` and a function at its end if it names one. |
| `why` | `bridge_text_t` | 16 | The reason. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:TextCheck` | `mpbt_text_check_t` | `mpbt_text_check_t_desc` | `MPBT_TEXT_CHECK_FIELDS` |
| `mpbt:LayoutCheck` | `mpbt_layout_check_t` | `mpbt_layout_check_t_desc` | `MPBT_LAYOUT_CHECK_FIELDS` |
| `mpbt:StyleCheck` | `mpbt_style_check_t` | `mpbt_style_check_t_desc` | `MPBT_STYLE_CHECK_FIELDS` |
| `mpbt:ProseCheck` | `mpbt_prose_check_t` | `mpbt_prose_check_t_desc` | `MPBT_PROSE_CHECK_FIELDS` |
| `mpbt:Retired` | `mpbt_retired_t` | `mpbt_retired_t_desc` | `MPBT_RETIRED_FIELDS` |
| `mpbt:Make` | `mpbt_make_t` | `mpbt_make_t_desc` | `MPBT_MAKE_FIELDS` |
| `mpbt:StyleException` | `mpbt_style_exception_t` | `mpbt_style_exception_t_desc` | `MPBT_STYLE_EXCEPTION_FIELDS` |

```text
{ bridge_text_t unicode; bridge_text_t refuse; }
{ bridge_text_t guides; }
{ uint32_t columns; uint32_t lines; uint32_t functions; uint32_t arguments; uint32_t branches; uint32_t depth; }
{ uint32_t sentence; uint32_t step; uint32_t paragraph; uint32_t description; }
{ bridge_text_t word; bridge_text_t text; }
{ bridge_text_t macro; bridge_text_t suffix; }
{ bridge_text_t rule; bridge_text_t path; bridge_text_t why; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:TextCheck` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:LayoutCheck` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:StyleCheck` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:ProseCheck` | `BRIDGE_STRUCT` | `BRIDGE_SINGLETON` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Retired` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:Make` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |
| `mpbt:StyleException` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:TextCheck` | `read`, from `[check]` | The check `text`. Each other module with a grant. |
| `mpbt:LayoutCheck` | `read`, from `[check]` | The check `layout`. Each other module with a grant. |
| `mpbt:StyleCheck` | `read`, from `[style]` | The check `style`. Each other module with a grant. |
| `mpbt:ProseCheck` | `read`, from `[prose]` | The check `prose`. Each other module with a grant. |
| Each other type | `read` | Each module with a grant. |

## Messages

`check` writes a finding for each fault, with the name of its check: `docs/extern/mpbt_finding.h.md`.

| Message | When |
| --- | --- |
| `every check passes` | No check found a fault. |
| `failed: <checks>` | These checks found faults. |
| `[check] refuse: <path> is not there` | A list of `refuse` is not there. |
| `the exception for '<path>' excuses nothing` | An exception of the style matches no fault. |
| `the exception for '<path>' states no reason` | An exception of the style has no `why`. |

### layout

| Message | When |
| --- | --- |
| `<path>: the layout needs this file` | A file that each project needs is not there. |
| `<folder>/: the layout needs this folder` | `.toolchain/tools` holds no file. |
| `<path>: the layout does not allow this file` | The layout has no place for the file. |
| `<path>: a compiled or temporary file` | git tracks a file that a build makes. |
| `<path>: '<name>' is not in snake_case` | A name of the path is not in snake case. |
| `<path>: no document <document>` | A file of `include`, `src` or `tools` has no document. |
| `<document>: no file has this document` | A document names no file. |
| `<document>: the first line is not # <path>` | A document starts with a different line. |

### workflows

| Message | When |
| --- | --- |
| `<path>: the matrix does not build <target>` | The matrix of a workflow lacks a target. |
| `<path>: <name> is not a target of the toolchain` | The matrix names an unknown target. |

### text

| Message | When |
| --- | --- |
| `the file does not start with the legal notice` | A script starts with a different text. |
| `a comment` | A script, a file `.toml` or `.yml`, or a document holds a comment. |
| `a string statement` | A script holds a text that is a statement. |
| `a character that is not ASCII` | A file that `unicode` does not name holds such a character. |
| `'<word>' is retired: write '<new>'` | A file holds a retired word. |
| `'<word>' is retired` | The same, for a word with no new word. |
| `'<name>' is refused by <list>` | The code calls a refused function. |

### prose

| Message | When |
| --- | --- |
| `the tag '<tag>' is not one of pseudo c toml sh text mermaid` | A block of code has a different tag. |
| `<words> words in a sentence, and <most> is the most` | A sentence is too long. |
| `<count> sentences in a paragraph, and <most> is the most` | A paragraph is too long. |
| `the title is not # <name>` | The first line of the readme is not the name of the project. |
| `no description after the title` | The readme has no description. |
| `<count> characters in the description, and <most> is the most` | The description is too long. |
| `the section <title> must come before <title>` | The sections of the readme are not in their order. |
| `no section <title>` | The readme has no Install, Usage, Contributing or License. |

### pseudo

| Message | When |
| --- | --- |
| `the profile refuses <form>` | The pseudo code uses a form that the profile refuses. |
| `indented by <indent>, and its level needs <need>` | A line has a different indent. |
| `a TYPE holds only DECLARE lines` | A `TYPE` holds a different line. |
| `a clause after OTHERWISE` | A clause comes after `OTHERWISE`. |
| `the keyword <word> is not in upper case` | A keyword is not in upper case. |
| `not a line of the profile` | A line has no form of the profile. |
| `<key> does not match the open block: <block>` | The end of a block does not match its start. |
| `<word> is not closed` | A block has no end. |

### xref

| Message | When |
| --- | --- |
| `<path> is not a file of the project` | A document cites a path that names no file. |
| `<path> has no heading <heading>` | A document cites a heading that is not there. |
| `this document has no heading <heading>` | A document cites a heading of its own that is not there. |

### dup, cover and licence

| Message | When |
| --- | --- |
| `<places>: <passage>` | `dup` finds a passage in 2 documents. |
| `<header>: <name> is not in <document>` | A public name of a header is not in a code span of its document. |
| `license is not there` | The project has no `license`. |
| `license is not the published text of the licence` | `license` is not the text of the GNU AGPL, version 3. |
| `says that all rights are reserved` | A file says that all rights are reserved. |
| `<notice> is not there` | A source of `third_party` has no `license`. |
| `cla.md is not there` | The project has no `cla.md`. |
| `readme.md does not name <name>` | The readme does not name `cla.md`, or a licence of `third_party`. |

### commits

The text of each finding of `commits` starts with the short name of the commit, then `: `. Its path is empty, so the report keeps the order of `git log`.

| Message | When |
| --- | --- |
| `the message has more than 1 line` | The message of a commit has 2 lines or more. |
| `the line is not type(scope): description` | The line has a different form. |
| `the type <type> is not in the list` | The type is not one of `docs/contributing/commits.md`. |
| `the description has <words> words, and 20 is the most` | The description is too long. |
| `git log <range>: <error>` | git cannot read the commits. |
| `git is not on the path, and commits needs it` | This machine has no `git`. |

### style

Each fault of the style names its rule of `docs/contributing/coding_style.md`.

| Rule | Message |
| --- | --- |
| F3 | `the line is <columns> columns, and <most> is the most` |
| L2 | `a tabulation is used for indentation` |
| L3 | `the line ends in white space` |
| L3 | `no space after a comma` |
| L3 | `no space after a keyword` |
| L3 | `sizeof is a unary operator: no space after it, sizeof(x)` |
| L3 | `a space between the name '<name>' and its parenthesis` |
| L3 | `a space between a unary operator and what it is applied to` |
| L3 | `no space on both sides of '<operator>'` |
| L3 | `a binary operator with no space on both sides` |
| V3 | `the pointer symbol is attached to the type, and belongs on the name` |
| V3 | `the pointer symbol stands apart from the name it belongs to` |
| H4 | `the macro '<name>' does not put each item of its text on its own line` |
| G1 | `the file does not start with the legal notice` |
| F6 | `a comment other than the legal notice` |
| O3 | `the file has <count> functions, and <most> is the most` |
| G2 | `<count> empty lines after a function, and it is one` |
| G3 | `the directive is not indented to its level, which is <level>` |
| V1 | `the macro '<name>' is not in UPPER_CASE` |
| H3 | `the macro '<name>' is a constant` |
| H3 | `the macro '<name>' is more than one statement` |
| H1 | `the macro '<name>' is defined in a source file` |
| H2 | `the header is not protected from double inclusion` |
| V1 | `the type '<name>' does not end with _t` |
| H1 | `a type is declared in a source file` |
| H1 | `a function is declared in a source file` |
| G4 | `'<name>' is a global variable that is not constant` |
| V1 | `the global constant '<name>' is not in UPPER_CASE` |
| V1 | `'<name>', of an enum, is not in UPPER_CASE` |
| H1 | `'<name>' is defined in a header and is not static inline` |
| H1 | `'<name>' is static inline in a source file` |
| G5 | `'<name>' is used in this file alone, and is not static` |
| F5 | `a function that takes nothing takes void` |
| F5 | `<count> arguments, and <most> is the most` |
| F2 | `the function '<name>' is not in snake_case` |
| F4 | `the body is <lines> lines, and <most> is the most` |
| L4 | `a function's opening bracket is alone on its line` |
| L4 | `a function's closing bracket is alone on its line` |
| L2 | `indented by <column>, and its level is <level>` |
| L1 | `more than one statement on the line` |
| L4 | `a closing bracket is not first on its line` |
| L2 | `a closing bracket is not at the level of what it closes` |
| L4 | `a closing bracket is followed by something that is not an else` |
| L1 | `a condition and an assignment on one line` |
| C2 | `nested or chained ternaries` |
| C1 | `more than <most> branchings in one if` |
| C1 | `conditional branchings nested <depth> deep, and <most> is the most` |
| L4 | `an opening bracket is at the end of the line it belongs to` |
| L4 | `an opening bracket is not at the end of its line` |
| L1 | `a condition and its statement share a line` |
| C3 | `goto` |
| L5 | `a variable is declared after the beginning of the function` |
| L5 | `more than one variable declared on a line` |
| V1 | `'<name>' is not in snake_case` |
| L1 | `several statements joined by a comma` |
| L1 | `several assignments on one line` |
| C2 | `a ternary used to control the flow` |
| L6 | `an empty line inside a function` |
| L6 | `no empty line after the declarations` |

### c23

Each fault of `c23` is the older spelling, then `  ->  ` and the newer spelling of `docs/contributing/coding_style.md`, *C23*.

| Older spelling | Message |
| --- | --- |
| `NULL` | `nullptr` |
| `#include <stdbool.h>` | `nothing: bool, true and false are keywords` |
| `_Bool` | `bool` |
| `_Alignof` | `alignof` |
| `_Alignas` | `alignas` |
| `_Static_assert` | `static_assert` |
| `_Thread_local`, `THREAD_LOCAL` | `thread_local` |
| `_Noreturn` | `[[noreturn]]` |
| `__attribute__`, `__declspec` | `an attribute in brackets: [[gnu::...]], [[clang::...]]` |
| An `enum` with no name | `a named enum with its width: enum name : uint32_t {` |
| An `enum` with no width | `the enum with its width stated: enum name : uint32_t {` |
| `(void)name;` | `[[maybe_unused]] where the parameter is declared` |
| `= {0};` | `= {}` |
| A macro for a number | `a typed constexpr` |
