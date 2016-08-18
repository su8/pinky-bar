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

void get_ram(char *, unsigned char num);
void get_ssd(char *, unsigned char num);
void get_packs(char *);
void get_kernel(char *, unsigned char num);
void get_loadavg(char *);
void get_uptime(char *);
void get_taim(char *);
void get_voltage(char *);
void get_mobo(char *);
void get_mobo_temp(char *);

#if defined(__linux__)
void get_ssd_model(char *, char *);
void get_fans(char *);
void get_statio(char *, char *);
void get_battery(char *);
#endif

#if defined (HAVE_X11_XLIB_H)
void set_status(const char *);
#endif

#endif /* FUNCTIONS_H_ */
