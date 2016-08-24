/*
   Copyright 07/06/2015, 07/18/2016
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

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void get_ram(char *, uint8_t num);
void get_loadavg(char *);
void get_voltage(char *);
void get_mobo(char *);
void get_mobo_temp(char *);
void get_statio(char *, char *);
void get_battery(char *);

#if defined(__linux__)
void get_ssd_model(char *, char *);
#endif

/* Restricted to Linux.
 * If lm_sensors are ported to support
 * BSD will update the code. */
#if defined(HAVE_SENSORS_SENSORS_H)
void get_fans(char *);
void match_feature(char *, uint8_t num);
#endif /* HAVE_SENSORS_SENSORS_H */

#endif /* FUNCTIONS_H_ */
