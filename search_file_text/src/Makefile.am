# Specify the program that will be built.
bin_PROGRAMS = searchui

if BUILD_SEARCHT
bin_PROGRAMS += searcht
endif

# Specify the source files for 'searchui'.
searchui_SOURCES = searchui.cpp ui.cpp ui.hpp

# Specify the source files for 'searcht' (if enabled).
if BUILD_SEARCHT
searcht_SOURCES = \
    system_info_window.cpp \
    system_info_window.hpp searcht.cpp \
	modules/SystemInfo.hpp \
	modules/load/SystemLoad.hpp \
	modules/load/SystemLoad.cpp \
	modules/cpu/CpuLoad.hpp \
	modules/cpu/CpuLoad.cpp
endif

# Specify the libraries for 'searchui'.
searchui_LDADD = -lncurses

# Specify the libraries for 'searcht' (if enabled).
if BUILD_SEARCHT
searcht_LDADD = -ltvision
endif

# Specify any additional flags for the C++ compiler.
AM_CPPFLAGS = -Wall -std=c++17

# Set up the installation directory
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
