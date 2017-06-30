/*
   06/30/2017

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

#if WITH_SLANG == 1
#include "include/headers.h"
#include <slang.h>
#endif /* WITH_SLANG */

#include "prototypes/slang.h"

#if WITH_SLANG == 1
/* Used the following sources:
    https://sourceforge.net/p/unicon/discussion/contributions/thread/3f579d7b/c494/attachment/slang.c
    http://www.jedsoft.org/slang/doc/pdf/cslang.pdf
    http://www.jedsoft.org/slang/doc/html/cref-5.html
*/
void
get_slang(char *str1, char *str2) {
  char *src = NULL;

  FILL_STR_ARR(1, str1, "0");

  if (-1 == SLang_init_slang())
    return;

  if (-1 == SLang_load_file(str2)) {
    SLang_restart(1);
  }

  if (-1 == SLang_load_string((char *)"uzer_function")) {
    return;
  }

  if (-1 == SLpop_string(&src)) {
    return;
  }

  FILL_STR_ARR(1, str1, src);
  SLfree(src);
}
#else
char *slang9;
#endif /* WITH_SLANG */
