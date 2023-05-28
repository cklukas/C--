# Specify the subdirectory where source files are located.
SUBDIRS = src

# Specify the program that will be built.
bin_PROGRAMS = search searchui

# Specify the source files for 'searchui'.
searchui_SOURCES = search.cpp searchui.cpp ui.cpp ui.hpp

# Specify the libraries for 'searchui'.
searchui_LDADD = -lncurses

# Specify any additional flags for the C++ compiler.
AM_CPPFLAGS = -Wall -std=c++17