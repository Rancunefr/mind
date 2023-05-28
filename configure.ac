# Process this file with autoconf to create configure.

AC_PREREQ([2.68])

# ====================
# Version informations
# ====================

AC_INIT([mind], [0.1])

mind_version="AC_PACKAGE_VERSION"
mind_version_major="`echo AC_PACKAGE_VERSION | awk -F. '{print $1}'`"
mind_version_major="`echo AC_PACKAGE_VERSION | awk -F. '{printf("%d\n",$2);}'`"


# =============
# Automake init
# =============

AM_INIT_AUTOMAKE( [foreign 1.13])


# ===========================
# Find required base packages
# ===========================

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
PKG_PROG_PKG_CONFIG([0.20])


# ======================
# Check system functions
# ======================

AC_SEARCH_LIBS(pow, m)
dnl Checks for string functions.
AC_CHECK_FUNCS(strdup strlcat strlcpy)


# ========================
# Check for system headers
# ========================

AC_CHECK_HEADERS([math.h])


# =================
# Check for Poppler
# =================

PKG_CHECK_MODULES([POPPLER], [poppler-glib >= 0.18])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.0])


# =====================
# Prepare all .in files
# =====================

AC_CONFIG_FILES([Makefile src/Makefile])

# =====================
# Options
# =====================

AC_ARG_ENABLE([werror],
	[AS_HELP_STRING([--enable-werror], [Treat all warnings as errors, useful for development.])],
	[enable_werror="$enableval"],
	[enable_werror=no]
)
AS_IF([test x"$enable_werror" = "xyes"], [
	CFLAGS="$CFLAGS -Werror"
])

# ==============================================
# Display final informations about configuration
# ==============================================

CFLAGS=" -Wall -Werror -Og -g"

AC_MSG_NOTICE([
==============================================================================
Environment settings:
	CFLAGS:                                    ${CFLAGS}
	LDFLAGS:                                   ${LDFLAGS}
Build configuration:
	werror:          ${enable_werror}
==============================================================================
])


AC_CONFIG_SRCDIR([src/main.c])
AC_OUTPUT
