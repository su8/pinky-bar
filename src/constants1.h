/*
   Copyright 07/29/2015 Aaron Caffrey https://github.com/wifiextender

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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define VLA 100

/* main.c constants */
#define FMT       "\x0a%s \x0b%s%%%c "
#define FMT_TIME  "\x0a%s \x0b%s"
#define TEMP      "\x09%sC\x0b%c "
#define FMT_MOBO  FMT_TIME" "TEMP
#define FMT_CPU   FMT_TIME"%% "TEMP
#define FMT_RAM   FMT
#define FMT_SSD   FMT
#define FMT_PKGS  FMT_TIME"%c "
#define FMT_VOLT  FMT_PKGS
#define FMT_FANS  FMT_TIME
#define FMT_KERN  "\x09%s%c "
#define FMT_VOL   FMT
#define COMMA     ','
#define WHOLE_MAIN_ARR_LEN VLA*14

#endif /* CONSTANTS_H_ */
