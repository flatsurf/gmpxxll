dnl @synopsis AX_CXX_CHECK_LIB(libname, prologue, body, action-if, action-if-not)
dnl
dnl Result:
dnl Just as the usual AX_CXX_CHECK_LIB - defines HAVE_LIBCGICC 
dnl and adds the libraries to the default library path (and
dnl uses internally the normal ac_check_lib cache symbol
dnl like ac_cv_lib_cgicc_cgicc__Cgicc)
dnl
dnl Footnote: The C++ language is not good at creating stable library
dnl interfaces at the binary level - a lot of functionality is usually being 
dnl given as inline functions plus there is hardly a chance to create opaque 
dnl types. Therefore most C++ library tests will only do compile tests using
dnl the header files. Doing a check_lib is however good to check the link
dnl dependency before hitting it as an error in the build later.
dnl
dnl @category C++
dnl @author Guido U. Draheim
dnl @vesion 2006-12-18
dnl @author Julian Rüth
dnl @version 2019-03-01

AC_DEFUN([AX_CXX_CHECK_LIB],
[m4_ifval([$3], , [AH_CHECK_LIB([$1])])dnl
AS_LITERAL_IF([$1],
	      [AS_VAR_PUSHDEF([ac_Lib], [ac_cv_lib_$1_$3])],
	      [AS_VAR_PUSHDEF([ac_Lib], [ac_cv_lib_$1''_$3])])dnl
AC_CACHE_CHECK([for lib$1], ac_Lib,
[ac_check_lib_save_LIBS=$LIBS
LIBS="-l$1 $6 $LIBS"
AC_LINK_IFELSE([AC_LANG_PROGRAM([$2], [$3])],
	       [AS_VAR_SET(ac_Lib, yes)],
	       [AS_VAR_SET(ac_Lib, no)])
LIBS=$ac_check_lib_save_LIBS])
AS_IF([test AS_VAR_GET(ac_Lib) = yes],
      [m4_default([$4], [AC_DEFINE_UNQUOTED(AS_TR_CPP(HAVE_LIB$1))
  LIBS="-l$1 $LIBS"
])],
      [$5])dnl
AS_VAR_POPDEF([ac_Lib])dnl
])# AC_CHECK_LIB
