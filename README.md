# Base Namer

This is an implementation of [jan Misali](https://www.youtube.com/channel/UCJOh5FKisc0hUlEeWFBlD-w)'s [base-neutral base naming scheme](https://www.seximal.net/names-of-other-bases), which was featured in a [video](https://www.youtube.com/watch?v=7OEF3JD-jYo). In short it takes in a base number and returns a name constructed of roots that is unique to that base. Any integer can be used. The scheme does support rational numbers, but that is out-of-scope for this implementation.

It generates fun things like `binbinbinbinbinbinoctelevenary` for base 5758, or `unpentahexabisuboptimal` for 1021.

The purpose of the project is to see how fast it can be made without platform-specific optimizations like SIMD or GPU.


## Usage rights

Unlicense, see UNLICENSE for details.
