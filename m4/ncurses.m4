dnl 09/03/2016

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


dnl TEST_NCURSES() function in configure.ac
dnl
dnl Test for the presence of the ncurses library
dnl and substitute macro to determine whether the
dnl program to be compiled with/out colours
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
          ERR([Missing core ncurses function.])
        ])
    ])
  ])
  AC_DEFINE_UNQUOTED([WITH_NCURSES],[$WITH_NCURSES],[Where to output the data])

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

])
