## Run autoconf on this file to produce configure.in
#=============================================================================
#
# libvmod-lang/configure.ac: autoconf configuration file
#
#=============================================================================

#-----------------------------
#           Init:
#-----------------------------
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright 2014-2021 Byteworks GmbH])
AC_INIT([libvmod-lang], [1.0.0])
AC_CONFIG_AUX_DIR([.])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(src/vmod_lang.vcc)
AC_CANONICAL_SYSTEM
AC_LANG(C)
AC_GNU_SOURCE
AM_INIT_AUTOMAKE([foreign])

#-----------------------------
#         Programs:
#-----------------------------
AC_PROG_CC
AC_PROG_CC_C99
AS_IF([test "x$ac_cv_prog_cc_c99" = "xno"],[
	AC_MSG_ERROR([Could not find a C99 compatible compiler])
])
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Check for rst utilities
AC_ARG_VAR([MD2MAN],
    [path to the m2dman tool used to build man pages (optional)])
AC_PATH_PROG(MD2MAN, [md2man-roff],[no])
AS_IF([test "x$MD2MAN" == "xno"],[
	AC_MSG_WARN([md2man not found - not building man pages])
])
AM_CONDITIONAL([HAVE_MD2MAN], [test "x$MD2MAN" != "xno"])

# Check for pkg-config
PKG_PROG_PKG_CONFIG

# Check for python
AC_CHECK_PROGS([PYTHON],
	[python3 python3.1 python3.2 python2.7 python2.6 python2.5 python2 python],
	[AC_MSG_ERROR([Python is needed to build this vmod. Please install python.])
	])

#-----------------------------
#           Headers:
#-----------------------------
AC_CHECK_HEADERS([stdlib.h string.h])
AC_HEADER_STDC
AC_CHECK_HEADERS([sys/stdlib.h])

#-----------------------------
#           Types:
#-----------------------------
AC_C_INLINE
AC_TYPE_SIZE_T

#-----------------------------
#       Function Checks:
#-----------------------------
AC_CHECK_FUNCS([strchr])

#-----------------------------
#           Varnish:
#-----------------------------
AX_CHECK_VARNISH_VMOD_DEV([
    AC_MSG_NOTICE([Varnish build environment okay.])
],[
   AC_MSG_ERROR([Unable to find required Varnish build environment.])
])

AC_DEFINE_UNQUOTED(
    [VARNISH_API_MAJOR],
    [$VARNISH_API_MAJOR],
    [Varnish API major version])

AM_CONDITIONAL([VARNISHSRC_3_X],[test "x$VARNISH_API_MAJOR" = "x3"])
AM_CONDITIONAL([VARNISHSRC_4_X],[test "x$VARNISH_API_MAJOR" = "x4"])
AM_CONDITIONAL([VARNISHSRC_5_X],[test "x$VARNISH_API_MAJOR" = "x5"])


#-----------------------------
#          Output:
#-----------------------------
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT

## EOF

