/*
   10/07/2016

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

#ifndef WEATHER_H_
#define WEATHER_H_

#if WITH_WEATHER == 1

#define PARSE_FIRST_TWO_NUMS(str, ptr1, num1, num2, flag) \
  if (0 != (isdigit((unsigned char) *(ptr1+num1)))) { \
    *str++ = *(ptr1+num1); \
    if (0 != (isdigit((unsigned char) *(ptr1+num2)))) { \
      *str++ = *(ptr1+num2); \
    } \
    flag = 1; \
  }

#define PARSE_NEXT_TWO_NUMS(str, ...) \
  *str++ = ' '; \
  PARSE_FIRST_TWO_NUMS(str, __VA_ARGS__);

size_t read_curl_data_cb(char *, size_t size, size_t nmemb, char *);
void get_weather(char *);
#endif /* WITH_WEATHER */

#endif /* WEATHER_H_ */
