AC_INIT([searchui], [1.0])
AC_CONFIG_SRCDIR([searchui.cpp])
AC_PROG_CXX
AC_PROG_RANLIB
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS([src/config.h])
AC_CHECK_LIB([ncurses], [main])
AC_CONFIG_FILES([Makefile])


AC_PREREQ([2.71])
# AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/ui.cpp])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lncurses':
AC_CHECK_LIB([ncurses], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])


AC_OUTPUT
