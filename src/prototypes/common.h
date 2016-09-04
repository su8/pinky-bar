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

#ifndef COMMON_H_
#define COMMON_H_

void exit_with_err(const char *, const char *);
void get_ssd(char *, uint8_t num);
void get_kernel(char *, uint8_t num);
void get_packs(char *);
void get_taim(char *);
void get_uptime(char *);

#if !defined(HAVE_SENSORS_SENSORS_H)
void get_fans(char *);
#endif /* !HAVE_SENSORS_SENSORS_H */

#if defined(__linux__)
void get_temp(const char *, char *);
#else
void get_temp(char *, uint_least32_t temp);
#endif /* __linux__ */

#if defined (HAVE_X11_XLIB_H)
void set_status(const char *);
#endif

#if defined(HAVE_CDIO_CDIO_H) || defined(__linux__)
void get_dvd(char *);
#endif /* HAVE_CDIO_CDIO_H || __linux__ */

#endif /* COMMON_H_ */
