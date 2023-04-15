# C++ sample programs

## Command `search`

**search - (c) 2023 by C. Klukas**

Searches for text files that contain a specific search term and prints the file names to the console.
Errors when trying to traverse into a directory are ignored.

A call `search /path/to/search .txt example` is similar to the Linux command `grep -r --include "*.txt" "example" /path/to/search`.

`Usage: ./search <folder> <extension> [<search_text>]`

You may also specifify multiple search terms. To search case-insensitive, use the `-i` option, it applies to the search terms but also to the file extension. By default multiple search terms are combined with the logical AND operator. Specify the `-o` option to use the logical OR operator.

To search all Python files in the user home directory with the search term "hello" *and* "world", use this command:

```bash
$ search ~ .py hello world
```

To make the search case-insensitive, use the `-i` option:

```bash
$ search ~ .py -i hello world
```

To search for either "hello" *or* "world", use the `-o` option:

```bash
$ search ~ .py -o hello world
```

To search for .jpg and .JPG files in the home directory or below, use the `-i` option:

```bash
$ search ~ .jpg -i
```

**Requirements**

The command uses the C++17 standard library and is compiled with the g++ compiler command (see `Makefile`). 
The program has been tested on MacOS X (Ventura 13.3). Compatibility with other operating systems will be tested later.

**Compilation**

```bash
$ make
```

The executable `./search` is created.

**Installation**

```bash
$ sudo make install
```

The `search` command is copied to `/usr/bin/search` and then available for execution by typing `search` in the command line.

**Example calls**

Search all sh files in the user home directory:

```bash
$ search ~ .sh
```


Search all txt or TXT files in the user home directory:

```bash
$ search ~ .txt -i
```


Search all Python files in the user home directory with the search term "example":

```bash
$ search ~ .py example
```