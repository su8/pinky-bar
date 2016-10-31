# This file is processed by autoconf to create a configure script
AC_INIT([pinkybar], [1.0.0])
AC_CONFIG_AUX_DIR([temp_dir])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([src/config.h])
# -Werror -Wportability
AM_INIT_AUTOMAKE([1.13 -Wall no-define foreign subdir-objects dist-xz no-dist-gzip std-options])

AM_SILENT_RULES([yes])
{perl will replace this line}

# With the addition of more runtime compile and
# link tests, this option is no longer necessary.
# Any compiler and C library succeeding to pass the
# tests will be able to compile and run the
# program flawlessly.
# If you use OpenBSD uncomment the AC_PROG_CC([])
# line below. Make sure that you have the latest gcc/llvm
# AC_PROG_CC([egcc clang llvm-gcc gcc])

AC_PROG_CC_C99
AC_C_CONST
AC_HEADER_STDC
AM_PROG_CC_C_O

# AM_EXTRA_RECURSIVE_TARGETS([ncurses])

# The linker flags tests in m4 dir
TEST_SOME_FUNCS
TEST_NET
TEST_PCI
TEST_X11
TEST_ALSA
TEST_MPD
TEST_DVD
TEST_SENSORS
TEST_TYPEZ
TEST_WEATHER
TEST_PERL
TEST_PYTHON
TEST_CFLAGZ

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])

AC_OUTPUT

echo
echo 'Now type \"make\" and \"make install\" afterwards'
echo
