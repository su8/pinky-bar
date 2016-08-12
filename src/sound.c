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

#if defined (HAVE_MPD_CLIENT_H)
#include <mpd/client.h>
#endif

#if defined (HAVE_ALSA_ASOUNDLIB_H)
#include <alsa/asoundlib.h>
#endif

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
  long int vol, max, min, percent;

  if (0 < (snd_mixer_open(&handle, 0))) {
    FUNC_FAILED("alsa");
  }

  if (0 < (snd_mixer_attach(handle, "default"))) {
    goto error;
  }

  if (0 < (snd_mixer_selem_register(handle, NULL, NULL))) {
    goto error;
  }

  if (0 < (snd_mixer_load(handle))) {
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

  if (0 < (snd_mixer_selem_get_playback_volume(elem, 0, &vol))) {
    goto error;
  }
  snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

  percent = (vol * 100) / max;

  snd_mixer_selem_id_free(s_elem);
  snd_mixer_close(handle);

  FILL_ARR(str1, "%ld", percent);
  return;

error:
  if (NULL != s_elem) {
    snd_mixer_selem_id_free(s_elem);
    s_elem = NULL;
  }
  if (NULL != handle) {
    snd_mixer_close(handle);
    handle = NULL;
  }
  FUNC_FAILED("alsa");
}
#endif


void
get_song(char *str1, unsigned char num) {
#if defined (HAVE_MPD_CLIENT_H)

  struct mpd_connection *conn = NULL;
  struct mpd_song *song;

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
  mpd_connection_free(conn);

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
  return;

error:
  if (NULL != conn) {
    mpd_connection_free(conn);
    conn = NULL;
  }
  return;
#else
  RECOMPILE_WITH("mpd");
#endif
}
