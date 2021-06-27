# Base Namer

This is an implementation of [jan Misali](https://www.youtube.com/channel/UCJOh5FKisc0hUlEeWFBlD-w)'s [base-neutral base naming scheme](https://www.seximal.net/names-of-other-bases), which was featured in a [video](https://www.youtube.com/watch?v=7OEF3JD-jYo). In short it takes in a base number and returns a name constructed of roots that is unique to that base. Any integer can be used, including negative values. The scheme does support rational numbers, but that is out-of-scope for this implementation.

It generates fun things like `binbinbinbinbinbinoctelevenary` for base 5758, or `unpentahexabisuboptimal` for 1021.

There are actually 3 programs in this repository; `name`, `hyphenate`, and `parse`. `name` generates base names from decimal integers. `hyphenate` parses base names and prints them out with hyphens in between each root. `parse` parses base names and converts them into decimal integers.

The purpose of the project is to see how fast it can reasonably be made without platform-specific optimizations like SIMD, GPU, or parallelization.

## Compiling and usage

To compile just run `$ make`.

`name` will convert all of its integral decimal arguments into base names, separated by newlines.

`hyphenate` will convert all of its base name arguments into hyphen-separated roots, separated by newlines.

`parse` will convert all of its base name arguments into integral decimal base numbers.


## Theory of operation

### `name`

`name` follows the rules described by jan Misali.

At the moment there are factorization differences. The differences are likely caused by the speed considerations this implementation makes. In this implementation a factorizer that uses the factor pair with one of the elements closest to *sqrt(n)* is used, with an exception for 100. In jan Misali's implementation a factorizer that chooses the shortest roots is used. I'm not sure how well it works though as jan Misali's implementation factorizes 200 as *10x20* for `decavigesimal`, whereas this implementation factorizes it as *2x100* for `bicentesimal`, which is 1 character shorter.

The general operation is as follows, for base *n*:

1. If *n* is a simple factor--one that has a defined root--return the root
2. Factorize *n*, choosing the two factors which are closest
3. Recurse for each factor

While *n* is decomposed into roots there are medial elements that are added.
These dictate how vowel reduction will be performed.

Finally, to produce the string, each element is catenated to the final output, skipping the first and/or last character if the medials specify to do so.

### `hyphenate`

For any name *n'*:

1. Parse *n'* into its component roots
2. Print each root's full name, followed by a hyphen-minus unless it is the final root

### `parse`

For any name *n'*:

1. Parse *n'* into its component roots
2. Initialize an accumulator *a* with 1
3. Starting at the final root, perform the following:
    - If the root is sna, recurse (to step number 2)
    - If the root is hen, add 1 to the accumulator and return
    - If the root is un, add 1 to the accumulator
    - Otherwise, multiply the accumulator with the root

### Parsing names

Parsing a name into roots is required for two of the three programs. For any name *n'*:

1. Convert *n'* into uppercase, stripping all non-alphabetic characters, as well as AEOU, and I not preceded by B
2. For each character in *n'*
    1. Add character to an internal string
    2. Attempt to index a precomputed trie, if accepts return the value, otherwise continue
    3. If the string is an impossible index, throw an error

Removing vowels (except for I preceded by B) prevents vowel reduction from interfering with parsing. I preceded by B is kept to parse `biker's dozenal`.

Since the accumulation algorithm doesn't care about order for the most part, and since the trie is simple enough, nonstandard roots can be supported very easily, permitting the bases `nonbinary`, `sexer's dozenal`/`hexer's dozenal`, and others.

The actual implementation is slightly different. Instead of indexing a trie, the algorithm is implemented inside of a trie. Inside the trie there are multiple pop and peek calls, which get a character from the string. These commands perform the capitalization and stripping. The trie function attempts to greedily accept just one root. If it cannot accept any root, it returns an invalid root.

Special consideration must be made for certain finals like binary and hex, since they can be ambiguous. Binary converts to BINRY, which looks a lot like BIN for bi-un. To alleviate this there are additional checks for length of the remaining string to see of there is enough space to expect the rest of the root, RY for binary's case.

The trie used in the algorithm is described in [basetrie](basetrie).

Overall the algorithm has a lookahead of 1 character as well as the length remaining in the string, with a time complexity of O(2n) since it has to compute the length of the string, and actually parse it. As for space complexity, it's O(1). When considering the element reconstruction with the stack, the space complexity is not exactly O(n), as each character does not have a 1 to 1 correspondance with the roots. Instead it's somewhere more like O(n/3).


## Usage rights

Unlicense, see UNLICENSE for details.
