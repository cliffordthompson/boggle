# boggle
Solve Boggle Puzzles without using the STL.

# Background

Boggle is played with 16 dice, each of which has a letter of the alphabet on each face.
The dice are thrown and then arranged into a 4x4 grid. At this point players attempt to
construct words by connecting letters with their neighbours. Letters which are adjacent
within a word must also be adjacent within the grid. Diagonal letter are considered to
be adjacent. Each instance of a letter may only be used once within each word. Words can
contain any number of letters but duplicates do no count towards the player's score.

# Build

You do a basic build of the program using:
`% make boggler`

To add debugging information using:
`% make debug`

Clean up the build artifacts using:
`%make clean`

# Usage

Executing the Boggler requires the input puzzle and the a dictionary:

`% boggler <puzzle> <file>`

For example:

`% boggler ahpmltorvsewmcdu wordlist.txt`
