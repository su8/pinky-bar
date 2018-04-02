dnl Copyright 07/06/2015, 08/03/2016

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
  WITH_COLOURS=0
  WITH_KEYBOARD=0
  WITH_DWM=0
  WITH_MOUSE=0

  AC_ARG_WITH([dwm],
    AS_HELP_STRING([--with-dwm],
      [X11 linker flag for dwm support]),
    [],
    [with_dwm=no]
  )

  AC_ARG_WITH([keyboard],
    AS_HELP_STRING([--with-keyboard],
      [X11 linker flag for keyboard layout support]),
    [],
    [with_keyboard=no]
  )

  AC_ARG_WITH([mouse],
    AS_HELP_STRING([--with-mouse],
      [X11 linker flag for mouse speed support]),
    [],
    [with_mouse=no]
  )

  AC_ARG_WITH([colors],
    AS_HELP_STRING([--with-colors],
      [Colorize the output]),
    [],
    [with_colors=no]
  )

  AC_ARG_VAR(icons, [path to xbm icons for non-dwm WM])

  AS_IF([test "x$with_colors" = "xyes"], [
    WITH_COLOURS=1
  ])

  AS_IF([test "x$with_dwm" = "xyes" || test "x$with_keyboard" = "xyes" || test "x$with_mouse" = "xyes"], [
    AC_CHECK_HEADERS([X11/Xlib.h X11/XKBlib.h], [
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
          MISSING_FUNC()
        ])
    ])
  ])

  dnl xbm icons for non-dwm window manager
  if [[ ! -z "${icons}" ]]
  then
    dnl Da stupid shell expansion only works on "UNQUOTED"
    ICONZ=\""${icons}"\"
    AC_DEFINE_UNQUOTED([ICONS_DIR],[$ICONZ],[xbm icons for non-dwm WM])
  fi

  AS_IF([test "x$with_keyboard" = "xyes"], [
    WITH_KEYBOARD=1
  ])

  AS_IF([test "x$with_mouse" = "xyes"], [
    WITH_MOUSE=1
  ])

  AS_IF([test "x$with_dwm" = "xyes"], [
    WITH_DWM=1
  ])

  AC_SUBST(X_LIBS)
  AC_DEFINE_UNQUOTED([WITH_COLOURS],[$WITH_COLOURS],[Colorize the output])
  AC_DEFINE_UNQUOTED([WITH_KEYBOARD],[$WITH_KEYBOARD],[Query xorg to get the currently used kb layout])
  AC_DEFINE_UNQUOTED([WITH_MOUSE],[$WITH_MOUSE],[Query xorg to get the current mouse speed])
  AC_DEFINE_UNQUOTED([WITH_DWM],[$WITH_DWM],[Output the data to the root window])

  AS_IF([test "x$with_dwm" = "xyes" || test "x$with_keyboard" = "xyes" || test "x$with_mouse" = "xyes"], [
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

  AS_IF([test "x$with_dwm" = "xno"], [
    TEST_NCURSES()
  ])

])


dnl Test for the presence of the ncurses library
dnl and substitute macro to determine whether the
dnl program to be compiled with/out ncurses colours
AC_DEFUN([TEST_NCURSES], [
  WITH_NCURSES=0

  AC_ARG_WITH([ncurses],
    AS_HELP_STRING([--with-ncurses],
      [Output the data to your terminal using the ncurses library.]),
    [],
    [with_ncurses=no]
  )

  AS_IF([test "x$with_ncurses" = "xyes"], [
    AC_CHECK_HEADERS([ncurses.h], [
      WITH_NCURSES=1
      ],[
        ERR_MUST_INSTALL([ncurses])
    ])

    m4_foreach([LiB], [
        initscr        ,
        noecho         ,
        cbreak         ,
        halfdelay      ,
        nonl           ,
        intrflush      ,
        curs_set       ,
        start_color    ,
        init_pair      ,
        refresh        ,
        clear          ,
        endwin         ,
        has_colors     ,
        pair_content   ,
        wattrset       ,
        waddch
      ],[
        AC_CHECK_LIB(ncurses,LiB,[],[
          MISSING_FUNC()
        ])
    ])
  ])

  AS_IF([test "x$with_ncurses" = "xyes"], [
    AC_LINK_IFELSE([
      AC_LANG_SOURCE([[
        #include <ncurses.h>
        int main(void) {
          initscr();
          printw("elo");
          refresh();
          endwin();
          return 0;
        }
      ]])
    ],[],[
        LINK_FAILED([ncurses])
      ]
    )

    AC_COMPILE_IFELSE([
      AC_LANG_SOURCE([[
        #include <stdlib.h>
        #include <unistd.h>
        #include <signal.h>
        void sighandler(int num);
        void sighandler(int num) {
          exit(1);
        }
        int main(void) {
          signal(SIGINT, sighandler);
          return 0;
        }
      ]])
    ],[],[
      COMPILE_FAILED([signal])
      ]
    )

  ])

  AC_DEFINE_UNQUOTED([WITH_NCURSES],[$WITH_NCURSES],[Where to output the data])

])
