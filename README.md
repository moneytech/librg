<div align="center">
    <a href="https://github.com/zpl-c/librg"><img src="https://user-images.githubusercontent.com/2182108/83804073-40d23c80-a6b6-11ea-8bee-52a42ed45bed.png" alt="librg" /></a>
</div>

<div align="center">
    <a href="https://github.com/zpl-c/librg/actions"><img src="https://img.shields.io/github/workflow/status/zpl-c/librg/tests?label=Tests&style=for-the-badge" alt="build status" /></a>
    <img src="https://img.shields.io/github/package-json/v/zpl-c/librg?style=for-the-badge" alt="version" /></a>
    <a href="https://discord.gg/2fZVEym"><img src="https://img.shields.io/discord/354670964400848898?color=7289DA&style=for-the-badge" alt="discord" /></a>
    <a href="LICENSE"><img src="https://img.shields.io/github/license/zpl-c/librg?style=for-the-badge" alt="license" /></a>
</div>

<br />

<div align="center">
  Making multi-player gamedev simpler since 2017. Single-header cross-platform world replication library in pure C99.
</div>

<div align="center">
  <sub>
    Built with love using <a href="https://github.com/zpl-c/zpl"><strong>zpl</strong></a>
    &bull; Brought to you by <a href="https://github.com/inlife">@inlife</a>,
    <a href="https://github.com/zaklaus">@zaklaus</a>
    and other <a href="https://github.com/zpl-c/librg/graphs/contributors">contributors</a>
  </sub>
</div>

## Introduction

**librg** is a lightweight library that serves as a middleware between data-transferring libraries (networking, file-streaming, etc.) and core application/game logic.

Main responsibilities of the library include:
 * entity tracking (tracks which entity belongs to what world, and what states do they have)
 * owner tracking (tracks which participant owns what entity)
 * area of interest management (controls what can and cannot be seen a participant)
 * world replication (re-creates a limited representation in a destination world of what is considered visible to a participant in the source world)

The library was born to solve complexities of setting up and managing the flow of multi-player games and dedicated game servers.
It came a long way of stripping out things that were non-essential, slowly sculpting into its current form, which you are able to see and use today.

## Features

 * cross-platform support
 * lightweight, single-header
 * compile- and run-time configurable
 * written in C99 (portability reasons)
 * no external dependencies
 * built-in unit test coverage

## F.A.Q.

> **Question**: Is this a networking library?

**Answer**: Not really, no. It is intended to be used with netwoking in mind, but it does not have any networking capabilities on its own.

> **Question**: Can I use any networking library with it?

**Anwser**: Yes. All you need is an ability to read data to and from the buffer, and most libraries do support that.

> **Question**: The repository contains a bunch of `*.h` and `*.c` files, and yet you suggest it is a single-header library, how is that possible?

**Answer**: The library is spread into multiple files so it is easier to work with it while developing, however each time a new release is created, a "bundled" version of the header file is created and pushed directly to the [releases](https://github.com/zpl-c/librg/releases) page.

> **Question**: Does librg offer an entity system?

**Answer**: No, the library does not manage nor actually create its own entities, it rather expects you to provide your own entity/object handle to attach some internal data onto it, which in context of the library is called "tracking". 

## Documentation

To read detailed documentation about the library, see examples and quick start guide, please visit our [documentation page](https://zpl-c.github.io/librg/#/quickstart).

Additionally you can check [code/apps](code/apps) folder for actual code examples.

## Migration

If you've used the library before version `v6.0.0`, it is recommended to read the migration guide [located here](https://zpl-c.github.io/librg/#/migration).

## Support

We are testing the library for various platforms. This table provides some sort of description for compatibility.
If you have tested it, and your result is different from the one in the table, please feel free to describe the issue in the [issues](https://github.com/zpl-c/librg/issues).


|  Platform / Result | Windows       | macOS         | Linux         | iOS           | Android       | Raspberry Pi  | OpenBSD       | FreeBSD       | Emscripten    |
|:------------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|
| ❔                 |               |               |               | clang         | clang         | gcc, clang    | gcc, clang    | gcc, clang    |               |
| ✅                 | msvc, mingw   | gcc, clang    | gcc, clang    |               |               |               |               |               | emcc          |

#### Legend:

* ❔ - Library was not tested on this platform/compiler yet
* ✅ - Library successfully compiles and all tests are executed properly


## Development

If you wish to contribute, add new feature, optimizations, or overall improvements, here are the instructions on how to do that:

1. Clone the repo, f.e.: `git clone https://github.com/zpl-c/librg.git`
2. Run `make` to build all projects, and verify everything works
3. Develop a feature, add tests for it in `code/tests/`
4. And eventually run `make test` again to check

In case you are working from **Windows**, and/or are not able to use `make`, you can also use built-in `cmake` config file to generate a Visual Studio solution, to do that:

1. `mkdir build`
2. `cd build`
3. `cmake ../misc -G"Visual Studio 16 2019"` (or any configuration you have)
4. `cmake --open .` (opens VS with the solution)
5. And repeat steps from above

