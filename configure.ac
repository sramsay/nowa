
AC_PREREQ([2.69])
AC_INIT([nowa], [0.3.0], [https://github.com/sramsay/nowa/issues])
AC_CONFIG_SRCDIR([src/nowa.c])
AC_DEFINE([COPYRIGHT_DATES], ["2020"], [current copyright dates])
AC_CONFIG_AUX_DIR([build-aux])


# Checks for programs
AC_PROG_CC
AC_PROG_CC_C99

# Check compiler abilities
AC_C_RESTRICT

# Checks for libc abilities
AC_FUNC_STRTOD
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIZE_T

# Check for libraries
AC_CHECK_LIB([curl],[curl_easy_setopt])
AX_PATH_LIB_PCRE

# Checks for library functions
AC_CHECK_FUNCS([localeconv])
AC_CHECK_FUNCS([memset])

# Checks for library headers
AC_CHECK_HEADER([check.h])
AC_CHECK_HEADER([getopt.h])
AC_CHECK_HEADERS([limits.h])
AC_CHECK_HEADERS([locale.h])
AC_CHECK_HEADERS([stddef.h])


AM_INIT_AUTOMAKE([-Wall subdir-objects foreign])

# Output files
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
