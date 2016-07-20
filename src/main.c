/*
   Copyright 02/22/2015, 07/18/2016
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

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "constants1.h"
#include "functions.h"

int main(void) {
  if (-1 == (sysconf(_SC_CLK_TCK))) {
    printf("%s\n", "Error: sysconf() failed");
    return EXIT_FAILURE;
  }

  struct timespec tc = {0};
  tc.tv_nsec = sysconf(_SC_CLK_TCK) * 1000000L;

  char packs[VLA], mobo[VLA], cpu[VLA], ram[VLA], ssd[VLA];
  char kern[VLA], volume[VLA], Time[VLA], combine[WHOLE_MAIN_ARR_LEN];
  char voltage[VLA], cpu_temp[VLA], mobo_temp[VLA], fans[VLA];

  get_cpu(cpu, cpu_temp);

  if (-1 == (nanosleep(&tc, NULL))) {
    printf("%s\n", "Error: nanosleep() failed");
    return EXIT_FAILURE;
  }

  get_cpu(cpu, cpu_temp);
  get_ram(ram);
  get_ssd(ssd);
  get_packs(packs);
  get_kernel(kern);
  get_voltage(voltage);
  get_fans(fans);
  get_mobo(mobo, mobo_temp);
  get_volume(volume);
  get_time(Time);

  snprintf(combine, WHOLE_MAIN_ARR_LEN,
    /* formatting specifiers */
    FMT_CPU FMT_RAM FMT_SSD FMT_PKGS FMT_KERN
    FMT_VOLT FMT_FANS FMT_MOBO FMT_VOL FMT_TIME,

    /* the data */
    CPU_STR, cpu, cpu_temp, COMMA,
    RAM_STR, ram, COMMA,
    SSD_STR, ssd, COMMA,
    PKG_STR, packs, COMMA,
    kern, COMMA,
    VOLT_STR, voltage, COMMA,
    FANS_STR, fans,
    MOBO_STR, mobo, mobo_temp, COMMA,
    VOL_STR, volume, COMMA,
    TIME_STR, Time);

#if defined (HAVE_X11_XLIB_H)
  set_status(combine);
#else
  printf("%s\n", combine);
#endif

  return EXIT_SUCCESS;
}
