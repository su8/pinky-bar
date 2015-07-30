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

#define MB 1048576
#define GB 1073741824
#define VLA 100

#define FMT_UINT "%"PRIuMAX
#define UFINT "%"PRIuFAST16

#define FILL_UINT_ARR(x, z) (snprintf(x, VLA, FMT_UINT, z))
#define FILL_STR_ARR(x, z) (snprintf(x, VLA*2, "%s", z))
#define FILL_STR2_ARR(x, y, z) (snprintf(x, VLA*2, "%s %s", y, z))
#define STREQ(x, z) (!strcmp(x, z))

#define HWMON_DIR "/sys/class/hwmon/hwmon0/"
#define CPU_TEMP_FILE HWMON_DIR"temp1_input"
#define MOBO_TEMP_FILE HWMON_DIR"temp2_input"
#define DMI_DIR "/sys/class/dmi/id/"
#define MOBO_NAME DMI_DIR"board_name"
#define MOBO_VENDOR DMI_DIR"board_vendor"

#endif /* CONSTANTS_H_ */
