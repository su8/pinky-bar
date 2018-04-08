dnl 08/03/2016

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


dnl TEST_SQLITE() function in configure.ac
dnl
dnl Substitute the linker flags -lsqlite3 to the
dnl the variable 'SQLITE_LIBS' if the user enabled
dnl the --with-sqlite switch
AC_DEFUN([TEST_SQLITE],[
  SQLITE_LIBS=""
  SQLITE_DB=""
  WITH_SQLITE=0

  AC_ARG_WITH([sqlite],
    AS_HELP_STRING([--with-sqlite],
      [Connect to sqlite db and perform SELECT operation]),
    [],
    [with_sqlite=no]
  )

  AC_ARG_VAR(sqlite_db, [sqlite db])
  if [[ ! -z "${sqlite_db}" ]]
  then
    SQLITE_DB=\""${sqlite_db}"\"
    AC_DEFINE_UNQUOTED([SQLITE_DB],[$SQLITE_DB],[sqlite db])
  fi

  AS_IF([test "x$with_sqlite" = "xyes"], [
    AC_CHECK_HEADERS([sqlite3.h], [
      SQLITE_LIBS="-lsqlite3"
      ],[
        ERR_MUST_INSTALL([sqlite])
    ])
    WITH_SQLITE=1

    m4_foreach([LiB], [
        sqlite3_open_v2              ,
        sqlite3_exec                 ,
        sqlite3_errmsg               ,
        sqlite3_free                 ,
        sqlite3_close_v2
      ],[
        AC_CHECK_LIB(sqlite3,LiB,[],[
          MISSING_FUNC()
        ])
    ])
  ])

  AC_SUBST(SQLITE_LIBS)
  AC_DEFINE_UNQUOTED([WITH_SQLITE],[$WITH_SQLITE],[Connect to sqlite db and perform SELECT operation])

  AS_IF([test "x$with_sqlite" = "xyes"], [
    AC_LINK_IFELSE([
      AC_LANG_SOURCE([[
        #include <stdio.h>
        #include <stdlib.h>
        #include <sqlite3.h>
        int main(void) {
          sqlite3 *db;
          char *zErrMsg = 0;
          int rc;

          rc = sqlite3_open("test.db", &db);

          if( rc ) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return(-1);
          } else {
            fprintf(stderr, "Opened database successfully\n");
          }
          sqlite3_close(db);
          return 0;
        }
      ]])
    ],[],[
        LINK_FAILED([sqlite3])
      ]
    )
  ])

])
