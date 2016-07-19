dnl Author: Aaron Caffrey

dnl TEST_ALSA() function in configure.ac
dnl
dnl Check for the presence of ALSA headers and
dnl substitute the linker flags -lasound to the
dnl the variable 'ALSA_LIBS' if they are available.
AC_DEFUN([TEST_ALSA],
[
  AC_CHECK_HEADERS([alsa/asoundlib.h], [
    ALSA_LIBS="-lasound"
    AC_SUBST(ALSA_LIBS)
  ],[
    AC_MSG_ERROR([Install alsa-utils and alsa-lib in order to compile the program.])
  ])

])


dnl TEST_X11() function in configure.ac
dnl
dnl Check for the presence of X11 headers and
dnl substitute the linker flags -lX11 to the
dnl the variable 'X_LIBS' if they are available.
AC_DEFUN([TEST_X11],
[
  X_LIBS=""

  AC_ARG_WITH([x11],
    AS_HELP_STRING([--with-x11],
      [X11 linker flag for dwm support]),
    [],
    [with_x11=yes]
  )

  AS_IF([test "x$with_x11" = "xyes"], [
    AC_CHECK_HEADERS([X11/Xlib.h], [
      X_LIBS="-lX11"
      ],[
        AC_MSG_ERROR([Install xorg and libx11 in order to compile the program.])
      ])
    ]
  )

  dnl xbm icons for non-dwm window manager
  AC_ARG_VAR(icons, [path to xbm icons for non-dwm WM])
  if [[ ! -z "${icons}" ]]
  then
    ICONZ="${icons}"
    AC_SUBST(ICONZ)
  fi

  AC_SUBST(X_LIBS)

])


dnl TEST_TYPEZ() function in configure.ac
dnl
dnl Check for the presence of all used
dnl library functions, their header files
dnl and some int types. 64bit is not
dnl mandatory since uintmax makes it 
dnl easy for us.
AC_DEFUN([TEST_TYPEZ],
[

  AC_TYPE_SIZE_T
  AC_TYPE_INT8_T
  AC_TYPE_INT16_T
  AC_TYPE_INT32_T
  AC_TYPE_INTMAX_T
  AC_TYPE_UINT8_T
  AC_TYPE_UINT16_T
  AC_TYPE_UINT32_T
  AC_TYPE_UINTMAX_T

  AC_CHECK_HEADERS([ \
    time.h           \
    stdio.h          \
    stdbool.h        \
    string.h         \
    inttypes.h       \
    glob.h           \
    sys/statvfs.h    \
    sys/sysinfo.h    \
    sys/utsname.h    \
    unistd.h         \
  ],[],[
    AC_MSG_ERROR([Some header files are missing.])
  ])

  AC_CHECK_FUNCS([  \
    memset          \
    printf          \
    snprintf        \
    nanosleep       \
    sysconf         \
    sysinfo         \
    strcmp          \
    fscanf          \
    fclose          \
    fopen           \
    statvfs         \
    getenv          \
    glob            \
    globfree        \
    popen           \
    uname           \
    strftime        \
    exit            \
  ],[],[
    AC_MSG_ERROR([Missing core library functions.])
  ])

])
