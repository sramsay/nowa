
AC_PREREQ([2.69])
AC_INIT([nowa], [0.2.0], [https://github.com/sramsay/nowa/issues])
AC_CONFIG_SRCDIR([src/nowa.c])
AC_DEFINE([COPYRIGHT_DATES], ["2020"], [current copyright dates])
AC_CONFIG_AUX_DIR([build-aux])

# Checks for programs
AC_PROG_CC
AC_PROG_CC_C99

AC_CHECK_LIB([curl],[curl_easy_setopt])

# Checks for library headers
AC_CHECK_HEADER([check.h])
AC_CHECK_HEADER([getopt.h])

# Checks for library functions
AC_FUNC_STRTOD

AM_INIT_AUTOMAKE([-Wall subdir-objects foreign])

# Output files
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
