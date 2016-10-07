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

#include "config.h" /* Auto-generated */

#if WITH_WEATHER == 1

#include <ctype.h>
#include <curl/curl.h>
#include "include/headers.h"

#endif /* WITH_WEATHER */

#include "prototypes/weather.h"

#if WITH_WEATHER == 1
size_t
read_curl_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  uintmax_t x = 0;
  char *ptr = NULL;
  size_t sz = nmemb * size;

  for (ptr = data; *ptr; ptr++, x++) {
    if (*ptr == 't') {
      if ((x+1) < sz && (x+2) < sz && (x+3) < sz) {
        if (*(ptr+1) == 'e' && *(ptr+2) == 'm' && *(ptr+3) == 'p') {
          if ((x+6) < sz && (x+7) < sz) {
            if ((isdigit((unsigned char) *(ptr+6))) &&
             (isdigit((unsigned char) *(ptr+7)))) {
              *str1++ = *(ptr+6);
              *str1++ = *(ptr+7);
            }
          }
          *str1 = '\0';
          break;
        }
      }
    }
  }
  return sz;
}


/*
  API docs - http://openweathermap.org/current
  Register yourself, create a new API key:
   https://home.openweathermap.org/api_keys
  add it after APPID=
*/
void get_weather(char *str1) {
  const char *da_url = "http://api.openweathermap.org/data/2.5/weather?q="
    API_TOWN "&units=metric&APPID=" API_KEY;
  /* const char *da_url = "http://api.openweathermap.org/data/2.5/weather?q=London,uk&units=metric&APPID=28459ae16e4b3a7e5628ff21f4907b6f"; */

  CURL *curl = NULL;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);
  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_curl_data_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, str1);

  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    goto error;
  }

error:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return;
}
#endif /* WITH_WEATHER */
