/*
   06/16/2017

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

#if WITH_R == 1

#include <Rinternals.h>
#include <Rembedded.h>
#include "include/headers.h"

#endif /* WITH_R */

#include "prototypes/R.h"

/* Based on:
 * https://github.com/parkerabercrombie/call-r-from-c */
#if WITH_R == 1
void
get_r(char *str1, char *str2) {
  SEXP env, strret, add1_call;
  char *r_argv[] = { (char *)"R", (char *)"--silent" };

  Rf_initEmbeddedR(2, r_argv);

  PROTECT(env = lang2(install("source"), mkString(str2)));
  R_tryEval(env, R_GlobalEnv, NULL);
  UNPROTECT(1);

  PROTECT(add1_call = lang1(install("uzer_func")));
  strret = R_tryEval(add1_call, R_GlobalEnv, NULL);

  FILL_STR_ARR(1, str1, CHAR(STRING_ELT(strret,0)));

  UNPROTECT(2);
  Rf_endEmbeddedR(0);
}
#else
char *R;
#endif /* WITH_R */
