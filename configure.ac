#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([test], [0.1], [SamuelGfroerer@googlemail.com])

AC_CONFIG_SRCDIR([test.c])

AC_CONFIG_AUX_DIR([build-aux])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile])

# use AUTOMAKE
# (which will generate a Makefile.in from Makefile.ac):
# -Wall -Werror: force correct Makefile.am
# foreign: dont complain if files missing for GNU standards
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_OUTPUT
