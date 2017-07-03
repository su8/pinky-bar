/*
   07/03/2017

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

#if WITH_TCL == 1
#include "include/headers.h"
#include <tcl.h>
#endif /* WITH_TCL */

#include "prototypes/tcl.h"

#if WITH_TCL == 1
/* Tcl_VarEval based on:
 * https://github.com/zacheryph/examples/blob/master/c-cpp/tcl/example_tcl.c */
void
get_tcl(char *str1, char *str2) {
  Tcl_Interp *interp = NULL;
  int x = 0;

  FILL_STR_ARR(1, str1, "0");

  interp = Tcl_CreateInterp();
  Tcl_Init(interp);

  Tcl_EvalFile(interp, str2);

  x = Tcl_VarEval(interp, (char *)"uzer_func", NULL, 0);
  if (TCL_ERROR == x) {
    return;
  }

  FILL_STR_ARR(1, str1, Tcl_GetStringResult(interp));
}
#else
char *tcl9;
#endif /* WITH_TCL */
