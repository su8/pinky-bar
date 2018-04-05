/*
   04/04/2018

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

#if defined(HAVE_CURL_CURL_H)
# include <curl/curl.h>
#endif /* HAVE_CURL_CURL_H */

#include "include/headers.h"
#include "prototypes/curl.h"

/* If you need to parse some news related website
 * there is a neat website that offers 30 000 news
 * related websites and exposes json api:
 *   https://newsapi.org 
 * Register yourself for free and get api key, then do
 * your parsing here. */

#if WITH_IP == 1
static size_t read_ip_data_cb(char *, size_t, size_t, char *);
#endif /* WITH_IP */

#if WITH_GITHUB == 1
static size_t read_github_data_cb(char *, size_t, size_t, char *);
#endif /* WITH_GITHUB */

#if WITH_REDDIT == 1
static size_t read_reddit_data_cb(char *, size_t, size_t, char *);
#endif /* WITH_REDDIT */

#if defined(HAVE_CURL_CURL_H)

#if WITH_IP == 1
static size_t
read_ip_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  FILL_STR_ARR(1, str1, data);

  return (nmemb * size);
}

void
get_ip(char *str1) {
  const char *const provider1 = "https://api.ipify.org";
  /* const char *const provider2 = "https://ipv4bot.whatismyipaddress.com"; */
  /* const char *const provider3 = "https://ident.me"; */
  /* const char *const provider4 = "https://wtfismyip.com/text"; */

  CURL *curl = NULL;
  CURLcode res;

  FILL_STR_ARR(1, str1, "0");
  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, provider1);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); 
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_ip_data_cb);
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
#endif /* WITH_IP */


#if WITH_GITHUB == 1
static size_t
read_github_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  size_t sz = nmemb * size, z = 0;
  static size_t x = 0;

  for (; *ptr; ptr++) {
    if ((z+4) < sz) { /* Verifying up to *(ptr+4) */

      if ('u' == *ptr) { /* unread */
        if ('n' == *(ptr+1) && 'r' == *(ptr+2) && 'e' == *(ptr+3)) {
          x++;
        }
      }

    }
  }

  FILL_ARR(str1, "GitHub %zu", x);
  return sz;
}

/* Idea taken from "polybar" */
void
get_github(char *str1) {
  const char *const github_url = "https://api.github.com/notifications?access_token=" GITHUB_TOKEN;

  CURL *curl = NULL;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, github_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "pinky-bar/1.0");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_github_data_cb);
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
#endif /* WITH_GITHUB */


#if WITH_REDDIT == 1
static size_t
read_reddit_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  size_t sz = nmemb * size, z = 0;
  static size_t x = 0;

  for (; *ptr; ptr++) {
    if ((z+7) < sz) { /* Verifying up to *(ptr+7) */

      if ('n' == *ptr) { /* "new": true */
        if ('e' == *(ptr+1) && 'w' == *(ptr+2) && 't' == *(ptr+6)) {
          x++;
        }
      }

    }
  }

  FILL_ARR(str1, "reddit %zu", x);
  return sz;
}

void
get_reddit(char *str1) {
  const char *const reddit_url = REDDIT_FEED;

  CURL *curl = NULL;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, reddit_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "pinky-bar/1.0");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_reddit_data_cb);
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
#endif /* WITH_REDDIT */

#else
char *cu7l;
#endif /* HAVE_CURL_CURL_H */
