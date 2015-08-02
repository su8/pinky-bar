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

#ifndef CONSTANTS2_H_
#define CONSTANTS2_H_

#define MB 1048576
#define GB 1073741824

#define FMT_UINT "%"PRIuMAX
#define UFINT "%"PRIuFAST16

/* stay away from va_list */
#define FILL_ARR(x, z, ...) (snprintf(x, VLA, z, __VA_ARGS__))
#define FILL_UINT_ARR(x, z) (FILL_ARR(x, FMT_UINT, z))
#define FILL_STR_ARR(x, z, ...) (FILL_ARR(z, (1 == x ? "%s" : "%s %s"), __VA_ARGS__))
#define STREQ(x, z) (!strcmp(x, z))

#define HWMON_DIR "/sys/class/hwmon/hwmon0/"
#define CPU_TEMP_FILE HWMON_DIR"temp1_input"
#define MOBO_TEMP_FILE HWMON_DIR"temp2_input"
#define DMI_DIR "/sys/class/dmi/id/"
#define MOBO_NAME DMI_DIR"board_name"
#define MOBO_VENDOR DMI_DIR"board_vendor"

#endif /* CONSTANTS2_H_ */
