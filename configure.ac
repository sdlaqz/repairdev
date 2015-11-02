#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(repairdev, 0.1, http://bugs.isoft-linux.org)
AM_INIT_AUTOMAKE([1.11 no-dist-gzip dist-xz tar-ustar])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_SED

# Checks for libraries.
LIBPCI_REQUIRED=3.3.1
PKG_CHECK_MODULES(PCI, libpci >= $LIBPCI_REQUIRED)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

AC_CONFIG_FILES([
Makefile
data/Makefile
src/Makefile
pci.d/Makefile
])

AC_OUTPUT
