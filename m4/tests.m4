dnl Author: Aaron Caffrey

dnl Be Loud when ErRo0rZ are detected
AC_DEFUN([ERR],[
  AC_MSG_ERROR($1)
])


dnl TEST_ALSA() function in configure.ac
dnl
dnl Check for the presence of ALSA headers and
dnl substitute the linker flags -lasound to the
dnl the variable 'ALSA_LIBS' if they are available.
AC_DEFUN([TEST_ALSA],[
  AC_CHECK_HEADERS([alsa/asoundlib.h], [
    ALSA_LIBS="-lasound"
    AC_SUBST(ALSA_LIBS)
  ],[
    ERR([Install alsa-utils and alsa-lib in order to compile the program.])
  ])

])


dnl TEST_X11() function in configure.ac
dnl
dnl Check for the presence of X11 headers and
dnl substitute the linker flags -lX11 to the
dnl the variable 'X_LIBS' if they are available.
AC_DEFUN([TEST_X11],[
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
        ERR([Install xorg and libx11 in order to compile the program.])
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


dnl Internal function to perform
dnl explicit data check type
AC_DEFUN([CHECK_TYPEZ],[
  AC_CHECK_TYPES([$1],[],[
    AC_MSG_WARN([Some C data type failed, checking which one.])
    m4_foreach([tYpe], [$1],[
      AC_CHECK_SIZEOF(tYpe)
    ])dnl
    ERR([Your compiler does not understand C data types.])
  ])
])

dnl TEST_TYPEZ() function in configure.ac
dnl
dnl Check for the presence of all used
dnl library functions, their header files
dnl and some int types. 64bit is not
dnl mandatory since uintmax makes it 
dnl easy for us.
AC_DEFUN([TEST_TYPEZ],[

  CHECK_TYPEZ([
    size_t,
    float,
    double,
    signed char,
    unsigned char,
    signed short int,
    signed int,
    signed long int,
    intmax_t,
    unsigned short int,
    unsigned int,
    unsigned long int,
    uintmax_t
  ])

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
    ERR([Some header files are missing.])
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
    ERR([Missing core library functions.])
  ])

])
