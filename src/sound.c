/*
   08/06/2016

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

#if defined (HAVE_MPD_CLIENT_H)
#include <mpd/client.h>
#endif /* HAVE_MPD_CLIENT_H */

#if defined (HAVE_ALSA_ASOUNDLIB_H)
#include <alsa/asoundlib.h>
#endif /* HAVE_ALSA_ASOUNDLIB_H */

#if defined(HAVE_SYS_SOUNDCARD_H) || defined(HAVE_SOUNDCARD_H)
#include <fcntl.h>
#include <sys/ioctl.h>

#if defined(HAVE_SOUNDCARD_H)
#include <soundcard.h>
#else
#include <sys/soundcard.h>
#endif /* HAVE_SOUNDCARD_H */

#endif /* HAVE_SYS_SOUNDCARD_H || HAVE_SOUNDCARD_H */

#include "include/headers.h"
#include "prototypes/sound.h"

#if defined (HAVE_ALSA_ASOUNDLIB_H)
/* http://www.alsa-project.org/alsa-doc/alsa-lib/group___mixer.html 
 * http://www.alsa-project.org/alsa-doc/alsa-lib/group___simple_mixer.html 
 * for the return values */
void 
get_volume(char *str1) {
  snd_mixer_t *handle = NULL;
  snd_mixer_elem_t *elem = NULL;
  snd_mixer_selem_id_t *s_elem = NULL;
  long int vol = 0L, max = 0L, min = 0L, percent = 0L;

  if (0 != (snd_mixer_open(&handle, 0))) {
    FUNC_FAILED("alsa");
  }

  if (0 != (snd_mixer_attach(handle, "default"))) {
    goto error;
  }

  if (0 != (snd_mixer_selem_register(handle, NULL, NULL))) {
    goto error;
  }

  if (0 != (snd_mixer_load(handle))) {
    goto error;
  }

  snd_mixer_selem_id_malloc(&s_elem);
  if (NULL == s_elem) {
    goto error;
  }

  snd_mixer_selem_id_set_name(s_elem, "Master");
  if (NULL == (elem = snd_mixer_find_selem(handle, s_elem))) {
    goto error;
  }

  if (0 != (snd_mixer_selem_get_playback_volume(elem, 0, &vol))) {
    goto error;
  }
  snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

  percent = 0L;
  if (0 != max) {
    percent = (vol * 100) / max;
  }

  snd_mixer_selem_id_free(s_elem);
  snd_mixer_close(handle);

  FILL_ARR(str1, "%ld", percent);
  return;

error:
  if (NULL != s_elem) {
    snd_mixer_selem_id_free(s_elem);
  }
  if (NULL != handle) {
    snd_mixer_close(handle);
  }
  FUNC_FAILED("alsa");
}
#endif /* HAVE_ALSA_ASOUNDLIB_H */


#if defined(HAVE_SYS_SOUNDCARD_H) || defined(HAVE_SOUNDCARD_H)
/* Used the following resource:
    sources.freebsd.org/RELENG_9/src/usr.sbin/mixer/mixer.c
*/
void 
get_volume(char *str1) {
  int devmask = 0, volume = 0, fd = 0;

  if (-1 == (fd = open("/dev/mixer", O_RDONLY))) {
    exit_with_err(CANNOT_OPEN, "/dev/mixer");
  }
  if (-1 == (ioctl(fd, SOUND_MIXER_READ_DEVMASK, &devmask))) {
    close(fd);
    exit_with_err(ERR, "SOUND_MIXER_READ_DEVMASK");
  }
  if (-1 == (ioctl(fd, MIXER_READ(0), &volume))) {
    close(fd);
    exit_with_err(ERR, "MIXER_READ()");
  }
  close(fd);

  FILL_ARR(str1, "%d", ((volume >> 8) & 0x7f));
}
#endif /* HAVE_SYS_SOUNDCARD_H || HAVE_SOUNDCARD_H */


#if defined (HAVE_MPD_CLIENT_H)
void
get_song(char *str1, uint8_t num) {

  struct mpd_connection *conn = NULL;
  struct mpd_song *song = NULL;

  if (NULL == (conn = mpd_connection_new(NULL, 0, 0))) {
    return;
  }
  if (!(mpd_send_command(conn, "currentsong", NULL)) ||
      0 != (mpd_connection_get_error(conn))) {
    goto error;
  }
  if (NULL == (song = mpd_recv_song(conn))) {
    goto error;
  }

  /* You can add more TAGs to be obtained,
   * look at /usr/include/mpd/tag.h
   */
  switch(num) {
    case 1:
      FILL_STR_ARR(1, str1, mpd_song_get_tag(song, MPD_TAG_TRACK, 0));
      break;
    case 2:
      FILL_STR_ARR(1, str1, mpd_song_get_tag(song, MPD_TAG_ARTIST, 0));
      break;
    case 3:
      FILL_STR_ARR(1, str1, mpd_song_get_tag(song, MPD_TAG_TITLE, 0));
      break;
    case 4:
      FILL_STR_ARR(1, str1, mpd_song_get_tag(song, MPD_TAG_ALBUM, 0));
      break;
    case 5:
      FILL_STR_ARR(1, str1, mpd_song_get_tag(song, MPD_TAG_DATE, 0));
      break;
    case 6:
      FILL_STR_ARR(1, str1, mpd_song_get_uri(song));
      break;
  }

error:
  if (NULL != song) {
    mpd_song_free(song);
  }
  if (NULL != conn) {
    mpd_connection_free(conn);
  }
  return;
}

#else

void
get_song(char *str1, uint8_t num) {
  FILE *fp;
  uint8_t found_it = 0;
  char buf[100], temp[100], *ptr;
  const char *tagz[] = { "artist", "title", "album", "date" };
  const char *idx_tagz = ((6 != num) ? tagz[num-2] : "ohsnap");

  if (NULL == (fp = popen("cmus-remote -Q 2> /dev/null", "r"))) {
    return;
  }

  while (true) {
    if (NULL == (fgets(buf, 99, fp)) || 1 == found_it) {
      break;
    }
    if (6 == num) {
      if ('f' == buf[0] && 'i' == buf[1] && 'l' == buf[2]) {
        CHECK_SSCANF(buf, "%*s %[^\n]", temp);
        if (NULL != (ptr = strrchr(temp, '/'))) {
          for (; *ptr; ptr++) {
            if ('/' != *ptr) {
              *str1++ = *ptr;
            }
          }
          *str1 = '\0';
        }
        found_it = 1;
      }
    } else {
      if ('t' == buf[0] && 'a' == buf[1] && 'g' == buf[2]) {
        CHECK_SSCANF(buf, "%*s %s", temp);
        if (STREQ(idx_tagz, temp)) {
          CHECK_SSCANF(buf, "%*s %*s %[^\n]", str1);
          found_it = 1;
        }
      }
    }
  }

  if (-1 == (pclose(fp))) {
    exit_with_err(CANNOT_CLOSE, "popen()");
  }
}
#endif /* HAVE_MPD_CLIENT_H */