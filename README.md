# Place items in a binary section

Cribbed from [SO](https://stackoverflow.com/questions/17669593/how-to-get-a-pointer-to-a-binary-section-in-mac-os-x);
how to place items in a [labeled section](https://stackoverflow.com/questions/18347122/attribute-sectionname-usage) of
your binary (and get a pointer to it).

This repo demos defining statics in separate compilation units and then having them end up in the same "array".
It is called "Linker hax" because this functionality relies on the linker.

## Gory details

There are three translation/compilation units here ([main.c](main.c), [tu1.c](tu1.c), and [tu2.c](tu2.c))
that each individually/independently define/declare statics (`x`, `y`, and `z`) and each annotate them to be placed in a
special section
of the compiled object file called `MY_SECTION`[^1]. Since they're compiled individually (as the word "unit" implies),
after compilation, each
object file (`main.c.o`, `tu1.c.o`, and `tu2.c.o`) will have *its own such* `MY_SECTION`.
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

## Compiler/linker tests

Mac OS

[![macos-gcc-ld](https://github.com/makslevental/linker_hax/actions/workflows/macos-gcc-ld.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/macos-gcc-ld.yml)
[![macos-clang-ld](https://github.com/makslevental/linker_hax/actions/workflows/macos-clang-ld.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/macos-clang-ld.yml)

Ubuntu

[![ubuntu-gcc-ld](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-ld.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-ld.yml)
[![ubuntu-gcc-lld](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-lld.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-lld.yml)
[![ubuntu-gcc-mold](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-mold.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-mold.yml)
[![ubuntu-gcc-gold](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-gold.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-gcc-gold.yml)
[![ubuntu-clang-ld](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-ld.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-ld.yml)
[![ubuntu-clang-lld](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-lld.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-lld.yml)
[![ubuntu-clang-mold](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-mold.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-mold.yml)
[![ubuntu-clang-gold](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-gold.yml/badge.svg)](https://github.com/makslevental/linker_hax/actions/workflows/ubuntu-clang-gold.yml)

[^1]: The exact magical incantation that effects/effectualizes this desire differs by compiler/linker (
see top of [section.h](linker_hax/blob/main/section.h)).
[^2]: Must have something to do with spelling or whatever order the linker links in because I am consistently
seeing `4`, `10`, and then `12` print out. Ultimately it's an implementation of the linker and the order can't be relied
on (hence "random").
[^3]: "A rose is a rose is a rose is a rose..."