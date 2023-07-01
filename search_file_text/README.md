# Building the software with Autotools

You can prepare a build in the "build" directory by following these steps:

## 1. Generate `Makefile.in` files and configure script

Run `autoreconf --install` from the root directory of your project to generate the necessary build scripts, including the `configure` script and the `Makefile.in` files.

```bash
autoreconf --install
```

## 2. Build your project

```bash
./configure                    # build only command line tool (search)
./configure --enable-searcht   # build also command-line GUI client (tsearch)
```

### Run `make`

```bash
make
```

The binaries are created in the subdir `src`.

You can call the program:

```bash
src/search
src/searcht # (if configured)
```

The resulting binary can be installed to the location specified by `--prefix` when you run `make install` (the `--prefix` default value is `/usr/local`).

## Extra steps

Download GNU Binutils

Mac:

```zsh
brew install binutils
```

```zsh
PATH="/opt/homebrew/opt/binutils/bin:$PATH" objcopy
```