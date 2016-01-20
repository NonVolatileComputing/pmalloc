
AC_INIT([libpmalloc], [0.2], [gang1.wang@intel.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
#if test -z $CFLAGS; then
#    CFLAGS="-O0 -ggdb3"
#fi
AC_CONFIG_MACRO_DIR([m4])
m4_pattern_allow([AM_PROG_AR])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_GNU_SOURCE
AC_DEFINE([_FILE_OFFSET_BITS], [64], [enable 64bits offset])
AC_PROG_CC_C99
AC_PROG_LIBTOOL
AC_FUNC_MMAP
case "$host_os" in
  darwin*)
  ;;
  *)
  AC_CHECK_FUNCS([clock_gettime], [CLOCK_LIB=],
    [AC_CHECK_LIB([rt], [clock_gettime], [CLOCK_LIB=-lrt],
    [AC_MSG_ERROR([Couldn't find clock_gettime])])])
  AC_SUBST([CLOCK_LIB])
  ;;
esac
AM_PROG_CC_C_O
AC_CONFIG_HEADERS([config.h])
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile perf/Makefile])
AC_OUTPUT

