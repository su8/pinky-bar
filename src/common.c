/*
   Copyright 08/06/2016
   Aaron Caffrey https://github.com/wifiextender

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

#include "config.h"
#include "include/headers.h"

void
exit_with_err(const char *str1, const char *str2) {
  printf("%s %s\n", str1, str2);
  exit(EXIT_FAILURE);
}


void
get_temp(const char *str1, char *str2) {
  uintmax_t temp;
  FILE *fp;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, str1, FMT_UINT, &temp);
#pragma GCC diagnostic pop

  temp /= (uintmax_t)1000;

  FILL_UINT_ARR(str2, temp);
}
