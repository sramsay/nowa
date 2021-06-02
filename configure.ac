
AC_PREREQ([2.69])
AC_INIT([nowa],[0.18.7],[https://github.com/sramsay/nowa/issues])
AC_DEFINE([COPYRIGHT_DATES], ["2020-2021"], [current copyright dates])
AC_CONFIG_SRCDIR([src/nowa.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

# Checks for programs
AC_PROG_CC

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_RESTRICT
AC_TYPE_SIZE_T


# Checks for libc abilities
AC_FUNC_STRTOD
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_MKTIME
AC_TYPE_SIZE_T

# Checks for header files.
AC_CHECK_HEADERS([float.h limits.h locale.h stddef.h stdlib.h string.h])

# Checks for library headers
AC_CHECK_HEADERS([getopt.h limits.h locale.h stddef.h float.h])
AC_CHECK_HEADER([check.h])

# Check for libraries
AC_CHECK_LIB([curl],[curl_easy_setopt])
AC_CHECK_LIB([pcre2-8],[pcre2_compile_8])

# Checks for library functions
AC_CHECK_FUNCS([localeconv localtime_r memset modf tzset])

# Checks for header signatures
AC_CHECK_HEADER_STDBOOL

AM_INIT_AUTOMAKE([-Wall subdir-objects foreign])

# Output files
AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
