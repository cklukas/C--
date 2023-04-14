# C++ sample programs

## Command `search`

```
search - (c) 2023 by C. Klukas
Searches for text files that contain a specific search term and prints the file names to the console.
Errors, e.g. when reading a file, or when traversing into a directory (e.g. access denied) are ignored.
A call 'search /path/to/search .txt example' is similar to the Linux command 'grep -r --include "*.txt" "example" /path/to/search'.
Usage: ./search <folder> <extension> [<search_text>]
```

**Compilation**

```bash
make
```

The executable `./search` is created.

**Installation**

```bash
sudo make install
```

The `search` command is copied to `/usr/bin/search` and then available for execution by typing `search` in the command line.
