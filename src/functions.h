/*
   Copyright 07/06/2015 Aaron Caffrey https://github.com/wifiextender

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

void get_cpu(char *, char *);
void get_ram(char *);
void get_ssd(char *);
void get_packs(char *);
void get_kernel(char *);
void get_voltage(char *);
void get_fans(char *);
void get_mobo(char *, char *);
void get_time(char *);
void get_volume(char *);
void set_status(const char *);

#endif /* FUNCTIONS_H_ */
