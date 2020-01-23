dnl Process this file with autoconf to produce a configure script.

dnl We need at least autoconf 2.69 for this configure.ac to work.
AC_PREREQ([2.69])
AC_INIT([gmpxxll], [0.0.1], [julian.rueth@fsfe.org])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([1.14.1 subdir-objects])

AC_CANONICAL_HOST

dnl Find C++ Compiler
AC_PROG_CXX

dnl Set INSTALL or use install-sh.
AC_PROG_INSTALL

dnl Check for required libraries
AC_LANG([C++])

dnl We use some C++17 features such as if constexpr
AX_CXX_COMPILE_STDCXX(17)

# GMPXX does not contain anything that we can check for with AX_CXX_CHECK_LIB
# so we just check for something from the standard library, i.e., that -lgmpxx
# goes through
AX_CXX_CHECK_LIB([gmpxx], [std::runtime_error::what () const], [have_gmpxx=yes], AC_MSG_ERROR([GMP library for C++ not found]), [-lgmp -lmpfr -lflint])

AC_CONFIG_HEADERS([gmpxxll/config.h])
AC_CONFIG_FILES([Makefile test/Makefile])

AC_OUTPUT
