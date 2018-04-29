/*
   04/02/2018

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

#if WITH_GMAIL == 1 || WITH_YAHOO == 1

#include <ctype.h>
#include <curl/curl.h>
#include "include/headers.h"

#endif /* WITH_GMAIL || WITH_YAHOO */

#include "prototypes/mail.h"

#if WITH_GMAIL == 1
static size_t read_gmail_data_cb(char *, size_t , size_t , char *);

/*
 *
 * The data that we are parsing (hint: fullcount):
    <?xml version="1.0" encoding="UTF-8"?><feed version="0.3" xmlns="http://purl.org/atom/ns#"><title>Gmail - Inbox for wifiextender2@gmail.com</title><tagline>New messages in your Gmail Inbox</tagline><fullcount>1</fullcount><link rel="alternate" href="https://mail.google.com/mail" type="text/html"/><modified>2018-04-01T21:34:38Z</modified><entry><title>test</title><summary>test 2018-04-01 23:06 GMT+02:00 aaron caffrey &lt;wifiextender2@gmail.com&gt;: test</summary><link rel="alternate" href="https://mail.google.com/mail?account_id=wifiextender2@gmail.com&amp;message_id=16283089938ead40&amp;view=conv&amp;extsrc=atom" type="text/html"/><modified>2018-04-01T21:06:41Z</modified><issued>2018-04-01T21:06:41Z</issued><id>tag:gmail.google.com,2004:1596579435347094848</id><author><name>me</name><email>wifiextender2@gmail.com</email></author></entry></feed>

  You can parse anything in the above example.
*/
static size_t
read_gmail_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  static char buf[VLA];
  static char *ptr2 = buf;
  size_t sz = nmemb * size, x = 0;

  for (; *ptr; ptr++, x++) {
    if ((x+17) < sz) { /* Verifying up to *(ptr+17) */

      if ('f' == *ptr) { /* fullcount */
        if ('u' == *(ptr+1) && 'l' == *(ptr+2) && 'l' == *(ptr+3)) {
          *ptr2++ = *(ptr+10); /* 1 email */
          if (0 != (isdigit((unsigned char) *(ptr+11)))) {
            *ptr2++ = *(ptr+11); /* 10 emails */
          }
          if (0 != (isdigit((unsigned char) *(ptr+12)))) {
            *ptr2++ = *(ptr+12); /* 100 emails */
          }
          if (0 != (isdigit((unsigned char) *(ptr+13)))) {
            *ptr2++ = *(ptr+13); /* 1000 emails */
          }
          if (0 != (isdigit((unsigned char) *(ptr+14)))) {
            *ptr2++ = *(ptr+14); /* 10 000 emails */
          }
          if (0 != (isdigit((unsigned char) *(ptr+15)))) {
            *ptr2++ = *(ptr+15); /* 100 000 emails */
          }
          break;
        }
      }

    }
  }

  FILL_STR_ARR(1, str1, buf);
  return sz;
}


/*
  cURL related docs and examples
   https://curl.haxx.se/libcurl/c/curl_easy_setopt.html
   https://github.com/curl/curl/tree/master/docs/examples
*/
void 
get_gmail(char *str1) {
  const char *const da_url = "https://mail.google.com/mail/feed/atom";

  CURL *curl = NULL;
  CURLcode res;

  FILL_STR_ARR(1, str1, "0");
  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_USERNAME, GMAIL_ACC);
  curl_easy_setopt(curl, CURLOPT_PASSWORD, GMAIL_PASS);
  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_gmail_data_cb);
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


#elif WITH_YAHOO == 1
static size_t read_yahoo_data_cb(char *, size_t , size_t , char *);

/* The data that we parse:
 *   1 12519
 *   2 22134
 *   3 13792 
 * */
static size_t
read_yahoo_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  static size_t z = 0;
  static char one_run = 0;
  size_t sz = nmemb * size, x = 0;

  if (0 == one_run) {
    for (; *ptr; ptr++, x++) {
      if ('\n' == *ptr) {
        z++;
      }
    }
    FILL_ARR(str1, "%zu", z);
    one_run = 1;
  }
  return sz;
}

void 
get_yahoo(char *str1) {
  const char *const da_url = "pop3s://pop.mail.yahoo.com";

  CURL *curl = NULL;
  CURLcode res;

  FILL_STR_ARR(1, str1, "0");
  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_USERNAME, YAHOO_ACC);
  curl_easy_setopt(curl, CURLOPT_PASSWORD, YAHOO_PASS);
  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_yahoo_data_cb);
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

#else
char *l33t2;
#endif /* WITH_GMAIL */
