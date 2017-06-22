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

#if WITH_GO == 1
#include "include/headers.h"
#include "pinky2.h"
#endif /* WITH_GO */

#include "prototypes/go.h"

#if WITH_GO == 1
void
get_go(char *str1) {
  char *str = uzer_func4();
  FILL_STR_ARR(1, str1, str);
  Gfree(str);
}
#else
char *go9;
#endif /* WITH_GO */
