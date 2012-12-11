#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([libtag], [0.1], [superruzafa@gmail.com])
AM_INIT_AUTOMAKE
LT_INIT
AC_CONFIG_SRCDIR([src/list.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([check], [suite_create], [CHECK_LIBS=-lcheck; CHECK_LDFLAGS=-pthread])
AC_SUBST([CHECK_LIBS])
AC_SUBST([CHECK_LDFLAGS])

# Checks for header files.
AC_CHECK_HEADERS([malloc.h]) 
AC_CHECK_HEADERS([check.h],
	[
		AC_DEFINE([HAVE_CHECK], 1, [Define to 1 if you have the <check.h> header file.])
	])
AC_SUBST([CHECK_CFLAGS])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile include/Makefile src/Makefile tests/Makefile])
AC_OUTPUT
