/*
   04/08/2018

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#include "config.h" /* Auto-generated */

#if WITH_SQLITE == 1
# include <sqlite3.h>
# include "include/headers.h"
#endif /* WITH_SQLITE */

#include "prototypes/sqlite.h"

#if WITH_SQLITE == 1
static int read_sqlite_data_cb(void *, int, char **, char **);

static int
read_sqlite_data_cb(void *str1, int count, char **data, char **coloums) {
  size_t len = ((size_t)count * VLA);
  char *buf = (char *)malloc(len);
  char *all = buf;
  int x = 0;

  if (NULL == buf) {
    return EXIT_FAILURE;
  }

  for (; x < count; x++) {
    GLUE2(all, "%s %s ", coloums[x], (data[x] ? data[x] : "NULL"));
  }
  *(--all) = '\0';

  FILL_STR_ARR(1, str1, buf);
  free(buf);
  return EXIT_SUCCESS;
}


/*
  Based on:
    https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
*/
void 
get_sqlite(char *str1, char *str2) {
  sqlite3 *db = NULL;
  char *err = "empty";

  if ((sqlite3_open_v2(SQLITE_DB, &db, SQLITE_OPEN_READONLY, NULL))) {
    exit_with_err(ERR, sqlite3_errmsg(db));
  }
  if (SQLITE_OK != (sqlite3_exec(db, str2, read_sqlite_data_cb, str1, &err))) {
    exit_with_err(ERR, err);
  }

  sqlite3_free(err);
  sqlite3_close_v2(db);
}

#else
char *l33t3;
#endif /* WITH_SQLITE */
