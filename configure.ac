# This file is processed by autoconf to create a configure script
  AC_INIT([dwmbar], [1.0.0])
  AC_CONFIG_AUX_DIR([temp_dir])
  AC_CONFIG_MACRO_DIR([m4])
  AM_INIT_AUTOMAKE([1.11 -Wall no-define foreign subdir-objects dist-xz no-dist-gzip std-options])

  AM_SILENT_RULES([yes])
  # Favour clang and fallback to gcc
  AC_PROG_CC([clang llvm-gcc gcc])
  AC_PROG_CC_C99
  AC_C_CONST
  AC_HEADER_STDC
  AM_PROG_CC_C_O

  # The linker flags tests in m4 dir
  TEST_X11
  TEST_ALSA
  TEST_MPD
  TEST_TYPEZ

  AC_CONFIG_FILES([
  Makefile
  src/Makefile
  ])

  AC_OUTPUT

  echo
  echo 'Now type "make" and "make install" afterwards'
  echo
