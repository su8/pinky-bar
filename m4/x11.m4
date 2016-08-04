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

    m4_foreach([LiB], [
        XOpenDisplay,
        XStoreName,
        XSync,
        XCloseDisplay
      ],[
        AC_CHECK_LIB(X11,LiB,[],[
          ERR([Missing core X11 function.])
        ])
    ])dnl
  ])

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

  AS_IF([test "x$with_x11" = "xyes"], [
    AC_LINK_IFELSE([
      AC_LANG_SOURCE([[
        #include <X11/Xlib.h>
        int main(void) {
          Display *display;
          Window window;
          XEvent evt;
          return 0;
        }
      ]])
    ],[],[
        LINK_FAILED([X11])
      ]
    )
  ])

])
