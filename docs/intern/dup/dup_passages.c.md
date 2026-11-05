# src/dup/dup_passages.c

This file joins the runs that 2 documents share into passages, and gives the finding of each passage to `finding_write`.

## The steps

1. A run is shared if its places name 2 documents or more.
2. In each sentence, the shared runs that follow or overlap each other make one passage.
3. The places of a passage are the places of its runs. Thus a document can be there 2 times.
4. A passage is a quote if one code span holds it at each of its places.
5. The code spans of 2 places of a quote are different. Else the passage is no quote.
6. A quote gives no finding. Thus 2 different messages that share 8 words give no finding.
7. A longer passage can hold a passage and each of its places. Then the shorter passage gives no finding.
8. Each other passage gives one finding. The findings follow the order of their places.

Thus one message in 2 documents gives a finding, and so does a sentence that repeats the words of a quote.

## The text of a finding

The text is each place as `<document>:<line>`, with `, ` between 2 places, then `: ` and the passage.
The passage is its words with a space between 2 words, in lower case and with no punctuation.

## Functions

| Function | Result |
| --- | --- |
| `dup_find_passages` | A finding for each passage of the scope. |
| `is_quote` | `true` if each place holds the passage in its own code span. |
| `is_inside` | `true` if a longer passage holds the passage and each of its places. |
| `write_text` | The text of the finding of a passage, in a `buffer_t`. |
