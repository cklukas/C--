# Ensure autoconf version is 2.71 or newer.
AC_PREREQ([2.71])

# Initialize autoconf for package 'searchui' version 1.0.
AC_INIT([searchui], [1.0])

# Check if --enable-searcht option is provided
AC_ARG_ENABLE([searcht],
  AS_HELP_STRING([--enable-searcht], [enable the searcht feature]),
  [enable_searcht=$enableval], [enable_searcht=no])
AM_CONDITIONAL([BUILD_SEARCHT], [test "$enable_searcht" = "yes"])

# Specify the source directory for autoconf.
# This macro will check if the specified source file exists.
AC_CONFIG_SRCDIR([src/searchui.cpp])

AM_INIT_AUTOMAKE([subdir-objects])

# Set up the C++ compiler.
AC_PROG_CXX

# Add -g and -fsanitize=address to CXXFLAGS for full debug symbols and array checks.
CXXFLAGS="$CXXFLAGS -g -Og -fsanitize=address -fno-omit-frame-pointer -fstack-protector-strong"

# Detect the ranlib tool for generating index to archive.
AC_PROG_RANLIB

# Check for the presence of the ncurses library and the main function within it.
# Replace 'main' with a function in the ncurses library.
AC_CHECK_LIB([ncurses], [main])

# Check for the presence of the stdbool.h header file.
AC_CHECK_HEADER_STDBOOL

# Check for the presence and size of size_t.
AC_TYPE_SIZE_T

# Check for the presence of the strerror function.
AC_CHECK_FUNCS([strerror])

# Set up a configuration header file (src/config.h in this case).
AC_CONFIG_HEADERS([src/config.h])

# List the files to be configured. The Makefile will be generated in the src directory.
AC_CONFIG_FILES([Makefile src/Makefile])

# Generate the output files.
AC_OUTPUT
