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

#define KB 1024
#define MB 1048576     /* 1024 * 1024     */
#define GB 1073741824  /* MB * 1024       */
#define Mb 131072      /* 1024 * 1024 / 8 */
#define BYTES_TO_MB(x) (x/2/1024) /* block bytes */

#define FMT_UINT "%"PRIuMAX
#define FMT_UINTX "%"PRIxMAX
#define UFINT "%"PRIuFAST16

/* stay away from va_list */
#define FILL_ARR(x, z, ...) (snprintf(x, VLA, z, __VA_ARGS__))
#define FILL_UINT_ARR(x, z) (FILL_ARR(x, FMT_UINT, z))
#define FILL_STR_ARR(x, z, ...) (FILL_ARR(z, (1 == x ? "%s" : "%s %s"), __VA_ARGS__))
#define GLUE2(x, z, ...) (x+=snprintf(x, VLA, z, __VA_ARGS__))

/* temperature sensors */
#define HWMON_DIR "/sys/class/hwmon/hwmon0"
#define TEMPERATURE(x) (HWMON_DIR"/temp"x"_input")
#define CPU_TEMP_FILE TEMPERATURE("1")
#define MOBO_TEMP_FILE TEMPERATURE("2")

/* motherboard model and vendor */
#define MOTHERBOARD(x) ("/sys/class/dmi/id/board_"x)
#define MOBO_NAME MOTHERBOARD("name")
#define MOBO_VENDOR MOTHERBOARD("vendor")

/* voltage and fans */
#define VOLTAGE_FILE(x) (HWMON_DIR"/in"x"_input")
#define FAN_FILE HWMON_DIR"/fan"UFINT"_input"

/* battery reports */
#define BATTERY_NUM(x, y, z) (FILL_ARR(x, "%s"FMT_UINT"%s%s", \
  "/sys/class/power_supply/BAT", y, "/charge_", z))
#define BATTERY_USED(x, z)  (BATTERY_NUM(x, z, "now"))
#define BATTERY_TOTAL(x, z) (BATTERY_NUM(x, z, "full"))

/* NIC model and vendor */
#define NIC_NUM(x, y, z) (FILL_ARR(x, "%s%s%s%s", \
  "/sys/class/net/", y, "/device/", z))
#define NIC_VEND(x, z)  (NIC_NUM(x, z, "vendor"))
#define NIC_MODEL(x, z) (NIC_NUM(x, z, "device"))

/* exit with error */
#define CANNOT_OPEN "Could not open"
#define ERR "Error:"
#define NOT_FOUND "Not found, "
#define FUNC_FAILED(x) (exit_with_err(ERR, x " failed"))
#define RECOMPILE_WITH(x) (exit_with_err(ERR, "recompile the program --with-" x))

/* Let the preprocessor Do Repeat Myself */
#define OPEN_X(fp, x, y, z) \
  if (NULL == (fp = fopen(x, "r"))) { \
    exit_with_err(CANNOT_OPEN, x); \
  } \
  fscanf(fp, y, z); \
  fclose(fp);

#endif /* CONSTANTS2_H_ */
