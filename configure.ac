#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.52])
AC_INIT([snyder], [0.1.0], [d@unwiredcouch.com])
AM_INIT_AUTOMAKE([0.1.0 foreign subdir-objects])
LT_INIT
AC_CONFIG_SRCDIR([include/snyder/metrics_registry.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# FIXME: Replace `main' with a function in `-lgtest':
AC_CHECK_LIB([gtest], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for C++11 support
AX_CXX_COMPILE_STDCXX_11

AC_CONFIG_FILES([Makefile])
AC_ARG_ENABLE(coverage,
    AC_HELP_STRING([--enable-coverage],[Enable code coverage]), [CXXFLAGS="-std=gnu++11 -O0 -g -ftest-coverage -fprofile-arcs"])
AC_OUTPUT
