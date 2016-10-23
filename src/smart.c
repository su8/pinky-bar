/*
   10/23/2016

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

#if defined(__linux__) && WITH_DRIVETEMP == 1
#include <ctype.h>
#include <curl/curl.h>
#endif /* __linux__ && WITH_DRIVETEMP */

#include "include/headers.h"
#include "prototypes/smart.h"

#if defined(__linux__) && WITH_DRIVETEMP == 1
static size_t read_temp_data_cb(char *, size_t size, size_t nmemb, char *);

/*
 * The data that we parse:
 * |/dev/sda|Corsair Force GT|24|C| */
static size_t
read_temp_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  static uint8_t one_run = 0, cols = 0;
  char *ptr = data;
  size_t sz = size * nmemb, x = 0;

  if (0 == one_run) {
    for (; *ptr; ptr++, x++) {
      if ((x+4) < sz) {

        if ('|' == *ptr) {
          ++cols;
          if (('C' == *(ptr+3) || 'C' == *(ptr+4)) && 3 == cols) {
            if (0 != (isdigit((unsigned char) *(ptr+1)))) {
              *str1++ = *(ptr+1);
              if (0 != (isdigit((unsigned char) *(ptr+2)))) {
                *str1++ = *(ptr+2);
              }
            }
            *str1 = '\0';
            break;
          }
        }

      }
    }

    one_run = 1;
    if ('\0' != *str1) {
      *str1++ = '\0';
    }
  }

  return sz;
}


/* Most of the time it takes 32 bytes to complete,
 * except sometimes the connection gets terminated
 * when only 31 bytes was received, so we dont check
 * the curl_easy_perform return value for that purpose.
 * Due to that, the call back function is called twice to
 * finish the left 1 byte, but we already have parsed the 
 * drive temperature.
*/
void 
get_drivetemp(char *str1) {
  const char *da_url = "http://127.0.0.1:" DRIVE_PORT;
  CURL *curl = NULL;

  FILL_STR_ARR(1, str1, "0");
  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_temp_data_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, str1);

  curl_easy_perform(curl);

error:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return;
}

#else

void
get_drivetemp(char *str1) {
  FILE *fp = NULL;
  uint_fast16_t temp = 0;
  const char *pinkytemp = "/tmp/pinkytemp";

  FILL_STR_ARR(1, str1, "0");

  if (NULL == (fp = fopen(pinkytemp, "r"))) {
    return;
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_FSCANF(fp, SCAN_UFINT, &temp);
#pragma GCC diagnostic pop

  CLOSE_X(fp);

  FILL_ARR(str1, UFINT, temp);
}
#endif /* __linux__ && WITH_DRIVETEMP */
