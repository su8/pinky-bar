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

#if WITH_OCAML == 1

#include <caml/alloc.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include "include/headers.h"

#endif /* WITH_OCAML */

#include "prototypes/ocaml.h"

#if WITH_OCAML == 1
void
get_ocaml(char *str1) {
  char *dummy[] = {(char *)"pinkybar", NULL};

  caml_startup(dummy);
  CAMLparam0();
  CAMLlocal1(res);

  value *func = caml_named_value("uzer_func");
  if (NULL == func) {
    FILL_STR_ARR(1, str1, "0");
  }

  res = caml_callback(*func, Val_unit);
  FILL_STR_ARR(1, str1, String_val(res));
}
#else
char *ocaml9;
#endif /* WITH_OCAML */
