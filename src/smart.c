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

#if defined(__linux__)
#if WITH_DRIVETEMP == 1 || WITH_DRIVETEMP_LIGHT == 1
#include <ctype.h>

#if WITH_DRIVETEMP_LIGHT == 1
#include <netdb.h>
#include <sys/socket.h>
#else
#include <curl/curl.h>
#endif /* WITH_DRIVETEMP_LIGHT */

#endif /* WITH_DRIVETEMP || WITH_DRIVETEMP_LIGHT */
#endif /* __linux__ */

#include "include/headers.h"
#include "prototypes/smart.h"

#if defined(__linux__) && (WITH_DRIVETEMP == 1 || WITH_DRIVETEMP_LIGHT == 1)
static size_t read_temp_data_cb(char *, size_t size, size_t nmemb, char *);
/*
 * The data that we parse:
 * |/dev/sda|Corsair Force GT|26|C||/dev/sdc|Hitachi HDS721616PLA380|34|C| */
static size_t
read_temp_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  static char buf[VLA];
  static char *ptr2 = buf;
  size_t sz = size * nmemb, x = 0;
  static int z = 0;

  for (; *ptr; ptr++, x++) {
    if ((x+2) < sz) {

      if ('|' == *ptr) {
        if (0 != (isdigit((unsigned char) *(ptr+1)))) {
          if (VLA-4 > z) {
            *ptr2++ = *(ptr+1);
            z++;
            if (0 != (isdigit((unsigned char) *(ptr+2)))) {
              *ptr2++ = *(ptr+2);
              z++;
            }
            *ptr2++ = 'C';
            *ptr2++ = ' ';
            z++;
            z++;
          }
        }
      }

    }
  }

  FILL_STR_ARR(1, str1, buf);

  return sz;
}
#endif /* __linux__ && (WITH_DRIVETEMP || WITH_DRIVETEMP_LIGHT) */


#if defined(__linux__) && WITH_DRIVETEMP == 1
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
  str1[strlen(str1)-1] = '\0';
  return;
}


#elif defined(__linux__) && WITH_DRIVETEMP_LIGHT == 1
/*
 * hddtemp/daemon.c
 * void daemon_send_msg(struct disk *ldisks, int cfd) {
 *   struct disk * dsk;
 *   daemon_update(ldisks, 0);
 *   for(dsk = ldisks; dsk; dsk = dsk->next) {
 *     char msg[128];
 *
 * We know what the max msg size might be.
*/
void
get_drivetemp(char *str1) {
  struct addrinfo *rp = NULL, *result = NULL, hints;
  int sock = 0;
  char buf[VLA];
  ssize_t len = 0;

  FILL_STR_ARR(1, str1, "0");
  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (0 != (getaddrinfo("127.0.0.1", DRIVE_PORT, &hints, &result))) {
    FUNC_FAILED("getaddrinfo()");
  }

  for (rp = result; NULL != rp; rp = rp->ai_next) {
    sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (-1 == sock) {
      continue;
    }
    if (NULL == rp->ai_addr) {
      CLOSE_FD2(sock, result);
      continue;
    }
    if (0 == (connect(sock, rp->ai_addr, rp->ai_addrlen))) {
     /* len, bytes received or -1 on err
      * We intentionally do not call
      * recv() in a loop, read the
      * comment in the curl version
      * of get_drivetemp
      */
      len = recv(sock, buf, sizeof(buf), 0);
      CLOSE_FD2(sock, result);

      if (0 < len) {
        /* the 3rd arg is dummy placeholder */
        read_temp_data_cb(buf, (size_t)len, 1, str1);
      }
      break;
    }
    CLOSE_FD2(sock, result);
  }

  if (NULL != result) {
    freeaddrinfo(result);
  }
  str1[strlen(str1)-1] = '\0';
}


#else

void
get_drivetemp(char *str1) {
  FILE *fp = NULL;
  char buf[VLA];
  const char *const pinkytemp = "/tmp/pinkytemp";

  FILL_STR_ARR(1, str1, "0");
  if (NULL == (fp = fopen(pinkytemp, "r"))) {
    return;
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_FSCANF(fp, "%[^\n]", buf);
#pragma GCC diagnostic pop
  CLOSE_FP(fp);

  FILL_STR_ARR(1, str1, buf);
}

#endif /* __linux__ && WITH_DRIVETEMP || __linux__ && WITH_DRIVETEMP_LIGHT || with smartemp */
