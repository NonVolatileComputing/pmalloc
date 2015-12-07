
AC_INIT([libpmalloc], [0.2], [gang1.wang@intel.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIR([m4])
if test -z $CFLAGS; then
    CFLAGS="-O0 -ggdb3"
fi
AC_GNU_SOURCE
AC_DEFINE([_FILE_OFFSET_BITS], [64], [enable 64bits offset])
AC_PROG_CC_C99
AC_PROG_LIBTOOL
AC_FUNC_MMAP
AC_CONFIG_HEADERS([config.h])
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile perf/Makefile])
#AC_CHECK_LIB([pmalloc],[])
AC_OUTPUT

