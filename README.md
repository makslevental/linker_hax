# Get a pointer to a binary section

Cribbed from [SO](https://stackoverflow.com/questions/17669593/how-to-get-a-pointer-to-a-binary-section-in-mac-os-x);
how to get a pointer to a [labeled section](https://stackoverflow.com/questions/18347122/attribute-sectionname-usage) in
your binary.

This repo demos defining statics in separate compilation units and then having them end up in the same "array".
It is called "Linker hax" because this functionality relies on the linker.

## Gory details

There are three translation/compilation units here ([main.c](main.c), [tu1.c](tu1.c), and [tu2.c](tu2.c))
that each individually/independently define/declare statics (`x`, `y`, and `z`) and each annotate them to be placed in a
special section
of the compiled object file called `MY_SECTION`[^1]. Since they're compiled individually (as the word "unit" implies),
after compilation, each
object file (`main.c.o`, `tu1.c.o`, and `tu2.c.o`) will have *its own such `MY_SECTION`*.
Thus, the values assigned to the statics (`4`, `10`, `22`) are actually compiled into distinct
places/locations/universes.

But when linker reconciles all such identically labeled `MY_SECTION`s and then builds the final unified `MY_SECTION` in
the executable, the statics are linear in memory (but randomly ordered[^2]) and thus addressable as if they were in an
array[^3]. Furthermore, the size of `MY_SECTION` is known statically and thus the length of the array is known
statically.

## Build and run

To build just do the standard CMake dance `mkdir -p build && cd build && cmake .. && make`.
Then after running you should see 🤞

```shell
Section size is 3
4
10
22
```

Tested with GNU 9.4.0 (on Ubuntu 20.04.2/x86) and AppleClang 13.1.6.13160021 (on macOS 12.6/arm64).

[^1]: The exact magical incantation that effects/effectualizes this desire differs by compiler/linker (
see top of [main.c](main.c)).
[^2]: Must have something to do with spelling or whatever order the linker links in because I am consistently
seeing `4`, `10`, and then `12` print out. Ultimately it's an implementation of the linker and the order can't be relied
on (hence "random").
[^3]: "A rose is a rose is a rose is a rose..."