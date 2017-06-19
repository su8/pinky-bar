/*
   06/19/2017

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

#if WITH_ECL == 1

#include <ecl/ecl.h>
#include "include/headers.h"

#endif /* WITH_ECL */

#include "prototypes/ecl.h"

/* Based on:
 *  https://gist.github.com/vwood/662109
 *  https://stackoverflow.com/questions/41915795/getting-ecl-symbol-name-as-string-in-c */
#if WITH_ECL == 1
static cl_object ecl_call(char *);

static cl_object
ecl_call(char *call) {
  return cl_safe_eval(c_string_to_object(call), Cnil, Cnil);
}


void
get_ecl(char *str1, char *str2) {
  char temp[VLA], *temp2[] = { (char *)"pinkybar" };

  cl_boot(1, temp2);

  FILL_ARR(temp, "(load \"%s\")", str2);
  ecl_call(temp);

  cl_object from_str = ecl_call((char *)"(uzer_func)");
  ecl_base_char *to_str = from_str->base_string.self;

  FILL_STR_ARR(1, str1, to_str);
  cl_shutdown();
}
#else
char *ecl9;
#endif /* WITH_ECL */
