/*
   06/22/2017

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

#if WITH_RUST == 1
#include "include/headers.h"
#endif /* WITH_RUST */

#include "prototypes/rust.h"

#if WITH_RUST == 1
extern char *uzer_func(void);
extern void Rfree(char *);

void
get_rust(char *str1) {
  char *str = uzer_func();
  FILL_STR_ARR(1, str1, str);
  Rfree(str);
}
#else
char *rust9;
#endif /* WITH_RUST */
