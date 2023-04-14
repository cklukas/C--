# C++ sample programs

## Command `search`

**search - (c) 2023 by C. Klukas**

Searches for text files that contain a specific search term and prints the file names to the console.
Errors when trying to traverse into a directory are ignored.

A call `search /path/to/search .txt example` is similar to the Linux command `grep -r --include "*.txt" "example" /path/to/search`.

`Usage: ./search <folder> <extension> [<search_text>]`

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

Search all txt files in the user home directory:

```bash
$ search ~ .txt
```


Search all Python files in the user home directory with the search term "example":

```bash
$ search ~ .py example
```