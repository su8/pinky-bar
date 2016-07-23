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
#include <string.h>
#include <getopt.h>

#include <unistd.h>

#include "main_constants.h"
#include "functions.h"

void help_msg(void);

int main(int argc, char *argv[]) {

  if (1 == argc) {
    help_msg();
    exit(EXIT_FAILURE);
  }

  if (-1 == (sysconf(_SC_CLK_TCK))) {
    printf("%s\n", "Error: sysconf() failed");
    return EXIT_FAILURE;
  }

  struct timespec tc = {0};
  tc.tv_nsec = sysconf(_SC_CLK_TCK) * 1000000L;

  char song[VLA] = "";
  char combine[WHOLE_MAIN_ARR_LEN] = "";
  char *all = combine;
  char packs[VLA], mobo[VLA], cpu[VLA], ram[VLA], ssd[VLA];
  char kern[VLA], volume[VLA], Time[VLA];
  char voltage[VLA], cpu_temp[VLA], mobo_temp[VLA], fans[VLA];

  const struct option options[] = {
		{ "mpd",          no_argument, NULL, 'M' },
		{ "cpu",          no_argument, NULL, 'c' },
		{ "ram",          no_argument, NULL, 'r' },
		{ "storage",      no_argument, NULL, 's' },
		{ "packages",     no_argument, NULL, 'p' },
		{ "kernel",       no_argument, NULL, 'k' },
		{ "voltage",      no_argument, NULL, 'v' },
		{ "fans",         no_argument, NULL, 'f' },
		{ "mobo",         no_argument, NULL, 'm' },
		{ "volume",       no_argument, NULL, 'V' },
		{ "time",         no_argument, NULL, 't' },
		{ "help",         no_argument, NULL, 'h' },
		{ NULL,           NULL,        NULL, NULL} 
	};

	char c;
	short int index = 0;
	while ((c = getopt_long(argc, argv, "McrspkvfmVth", options, &index)) != -1) {
		switch (c) {
      case 'M':
#if defined (HAVE_MPD_CLIENT_H)
        get_song(song);
        all += GLUE(all, FMT_SONG, song);
#else
        printf("%s\n", "recompile the program --with-mpd");
#endif
        break;

			case 'c':
        get_cpu(cpu, cpu_temp);
        if (-1 == (nanosleep(&tc, NULL))) {
          printf("%s\n", "Error: nanosleep() failed");
          return EXIT_FAILURE;
        }
        get_cpu(cpu, cpu_temp);
        all += GLUE(all, FMT_CPU, CPU_STR, cpu, cpu_temp);
				break;

			case 'r':
        get_ram(ram);
        all += GLUE(all, FMT_RAM, RAM_STR, ram);
				break;

			case 's':
        get_ssd(ssd);
        all += GLUE(all, FMT_SSD, SSD_STR, ssd);
				break;

			case 'p':
        get_packs(packs);
        all += GLUE(all, FMT_PKGS, PKG_STR, packs);
				break;

			case 'k':
        get_kernel(kern);
        all += GLUE(all, FMT_KERN, kern);
				break;

			case 'v':
        get_voltage(voltage);
        all += GLUE(all, FMT_VOLT, VOLT_STR, voltage);
				break;

			case 'f':
        get_fans(fans);
        all += GLUE(all, FMT_FANS, FANS_STR, fans);
			  break;

			case 'm':
        get_mobo(mobo, mobo_temp);
        all += GLUE(all, FMT_MOBO, MOBO_STR, mobo, mobo_temp);
			  break;

			case 'V':
        get_volume(volume);
        all += GLUE(all, FMT_VOL, VOL_STR, volume);
			  break;

			case 't':
        get_time(Time);
        all += GLUE(all, FMT_TIME, TIME_STR, Time);
			  break;

			case 'h':
			  help_msg();
			  return EXIT_SUCCESS;

			default:
			  help_msg();
				return EXIT_FAILURE;
		}
	}

#if defined (HAVE_X11_XLIB_H)
  set_status(combine);
#else
  printf("%s\n", combine);
#endif

  return EXIT_SUCCESS;
}


void help_msg(void) {
	printf("%s\n",
	    "Available options:\n"
			"  -M, --mpd\t Output the currently played song name (if any).\n"
			"  -c, --cpu\t Output the current cpu load and temperature.\n"
			"  -r, --ram\t Output the used ram.\n"
			"  -s, --storage\t Output the used drive storage.\n"
			"  -p, --packages Output the number of installed packages.\n"
			"  -k, --kernel\t Output the kernel version.\n"
			"  -v, --voltage\t Output the system voltage.\n"
			"  -f, --fans\t Output all system fans.\n"
			"  -m, --mobo\t Show the motherboard name, vendor and temperature.\n"
			"  -V, --volume\t Output the volume.\n"
			"  -t, --time\t Output the current time.\n"
  );
}
