dnl Process this file with autoconf to produce a configure script.

dnl We need at least autoconf 2.69 for this configure.ac to work.
AC_PREREQ([2.69])
AC_INIT([gmpxxll], [1.0.1], [julian.rueth@fsfe.org])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([1.14.1 tar-pax foreign])

AC_CANONICAL_HOST

dnl Find C++ Compiler
AC_PROG_CXX

dnl Set INSTALL or use install-sh.
AC_PROG_INSTALL

dnl We run the valgrind test-suite in make check-valgrind
AX_VALGRIND_DFLT([sgcheck], [off])
AX_VALGRIND_DFLT([drd], [off])
AX_VALGRIND_DFLT([helgrind], [off])
AX_VALGRIND_CHECK()

dnl Check for required libraries
AC_LANG([C++])

dnl We use some C++17 features such as if constexpr
AX_CXX_COMPILE_STDCXX(17)

AC_CHECK_HEADERS([gmpxx.h], , AC_MSG_ERROR([GMP++ headers not found]))
AX_CXX_CHECK_LIB([gmpxx], [
#include <iostream>
#include <gmpxx.h>
], [std::cout << mpz_class()],  [have_gmpxx=yes], AC_MSG_ERROR([GMP library for C++ not found]), [-lgmp])

dnl Our benchmarks use Google's C++ benchmark library.
dnl We fail if they cannot be found but let the user disable it explicitly.
AC_ARG_WITH([benchmark], AS_HELP_STRING([--without-benchmark], [Do not build C++ benchmarks that require google/benchmark]))
AS_IF([test "x$with_benchmark" != "xno"],
      [
       with_benchmark=yes
       AC_CHECK_HEADERS([benchmark/benchmark.h], , AC_MSG_ERROR([benchmark headers not found; run --without-benchmark to disable building of benchmark/]))
      ], [])
AM_CONDITIONAL([HAVE_BENCHMARK], [test "x$with_benchmark" = "xyes"])

AC_ARG_WITH([doc], AS_HELP_STRING([--without-doc], [Do not build the e-antic documentation]))
AS_IF([test "x$with_doc" != "xno"], [AC_CONFIG_SUBDIRS([doc])])

AC_CONFIG_HEADERS([gmpxxll/config.h])
AC_CONFIG_FILES([Makefile test/Makefile benchmark/Makefile])

AC_OUTPUT
