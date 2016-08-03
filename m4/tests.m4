dnl Copyright 07/06/2015, 08/03/2016
dnl Aaron Caffrey https://github.com/wifiextender

dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
dnl MA 02110-1301, USA.


dnl Internal function to show
dnl error message when smth is wrong
AC_DEFUN([ERR],[
  AC_MSG_ERROR($1)
])

dnl Internal function to show what must to
dnl be installed in order to compile the program.
AC_DEFUN([ERR_MUST_INSTALL],[
  ERR([Install $1 in order to compile the program.])
])


dnl TEST_ALSA() function in configure.ac
dnl
dnl Check for the presence of ALSA headers and
dnl substitute the linker flags -lasound to the
dnl the variable 'ALSA_LIBS' if they are available.
AC_DEFUN([TEST_ALSA],[
  ALSA_LIBS=""

  AC_ARG_WITH([alsa],
    AS_HELP_STRING([--with-alsa],
      [ALSA linker flag for sound support]),
    [],
    [with_alsa=no]
  )

  AS_IF([test "x$with_alsa" = "xyes"], [
    AC_CHECK_HEADERS([alsa/asoundlib.h], [
      ALSA_LIBS="-lasound"
      ],[
        ERR_MUST_INSTALL([alsa-utils and alsa-lib])
      ])
  ])

  AC_SUBST(ALSA_LIBS)

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
        ERR_MUST_INSTALL([xorg and libx11])
      ])
  ])

  dnl dwm/terminal multiplexer
  WITH_COLOURS=0
  AC_ARG_WITH([colours],
    AS_HELP_STRING([--with-colours],
      [Colorize the output]),
    [],
    [with_colours=yes]
  )
  AS_IF([test "x$with_colours" = "xyes"], [
    WITH_COLOURS=1
  ])
  AC_DEFINE_UNQUOTED([WITH_COLOURS],[$WITH_COLOURS],[Colorize the output])


  dnl xbm icons for non-dwm window manager
  AC_ARG_VAR(icons, [path to xbm icons for non-dwm WM])
  if [[ ! -z "${icons}" ]]
  then
    dnl Da stupid shell expansion only works on "UNQUOTED"
    ICONZ=\""${icons}"\"
    AC_DEFINE_UNQUOTED([ICONS_DIR],[$ICONZ],[xbm icons for non-dwm WM])
  fi

  AC_SUBST(X_LIBS)

])


dnl TEST_MPD() function in configure.ac
dnl
dnl Substitute the linker flags -lmpdclient to the
dnl the variable 'MPD_LIBS' if the user enabled
dnl the --with-mpd switch
AC_DEFUN([TEST_MPD],[
  MPD_LIBS=""

  AC_ARG_WITH([mpd],
    AS_HELP_STRING([--with-mpd],
      [mpd linker flag to show the current playing song]),
    [],
    [with_mpd=no]
  )

  AS_IF([test "x$with_mpd" = "xyes"], [
    AC_CHECK_HEADERS([mpd/client.h], [
      MPD_LIBS="-lmpdclient"
      ],[
        ERR_MUST_INSTALL([libmpdclient])
      ])
    ]
  )

  AC_SUBST(MPD_LIBS)

])


dnl Internal function to perform
dnl explicit compiler CFLAGS support test
AC_DEFUN([CHECK_CFLAGZ],[
  m4_foreach([tYpe], [$1], [
    AX_CHECK_COMPILE_FLAG(
      [tYpe],
      AX_APPEND_FLAG([tYpe], [CFLAGS]),
      ERR([Your compiler does not understand the above cflag])
    )
  ])dnl
])

dnl Internal function to check
dnl the compiler for assembly support
AC_DEFUN([TEST_ASSEMBLY],[

  AC_MSG_CHECKING([for assembly support])

  AC_COMPILE_IFELSE([
    AC_LANG_PROGRAM([[
      #include <stdint.h>]],[[
      uintmax_t x;
      __asm__ __volatile__ (".byte 0x0f, 0x31" : "=A" (x));
    ]])
  ],[supportz_assembly=yes],[supportz_assembly=no])

  AC_MSG_RESULT([$supportz_assembly])

  AS_IF([test "x$supportz_assembly" = "xno"], [
      ERR([Your compiler does not support assembly])
    ]
  )

])

dnl TEST_CFLAGZ() function in configure.ac
dnl
dnl Check for the presence and whether
dnl the given FLAG will work flawlessly
dnl with the currently used compiler.
dnl Will Substitute each successful flag
dnl and bail out with pre-defined error msg
dnl when some FLAG is unsupported.
AC_DEFUN([TEST_CFLAGZ],[

  CHECK_CFLAGZ([
    -O2,
    -pipe,
    -std=c99,
    -Wextra,
    -Wall,
    -pedantic,
    -Wundef,
    -Wshadow,
    -w,
    -Wwrite-strings,
    -Wcast-align,
    -Wstrict-overflow=5,
    -Wconversion,
    -Wpointer-arith,
    -Wstrict-prototypes,
    -Wformat=0,
    -Wsign-compare,
    -Wdeclaration-after-statement,
    -Wendif-labels,
    -Wredundant-decls,
    -Wmissing-prototypes,
    -Wno-unused-result,
    -Wno-unused-function,
    -Wno-missing-field-initializers
  ])

  TEST_ASSEMBLY()

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
    time_t,
    float,
    double,
    signed char,
    unsigned char,
    signed short int,
    int8_t,
    signed int,
    int16_t,
    signed long int,
    int32_t,
    intmax_t,
    unsigned short int,
    uint8_t,
    unsigned int,
    uint16_t,
    unsigned long int,
    uint32_t,
    uintmax_t,
    int_least8_t,
    int_least16_t,
    int_least32_t,
    uint_least8_t,
    uint_least16_t,
    uint_least32_t,
    int_fast8_t,
    int_fast16_t,
    int_fast32_t,
    uint_fast8_t,
    uint_fast16_t,
    uint_fast32_t
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
    getopt.h         \
    sys/socket.h     \
    linux/if_link.h  \
    ifaddrs.h        \
  ],[],[
    ERR([Missing core header files.])
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
    getopt          \
    getopt_long     \
    getifaddrs      \
    freeifaddrs     \
  ],[],[
    ERR([Missing core library functions.])
  ])

])
