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
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include <unistd.h>

#include "config.h" /* auto-generated */
#include "main_constants.h"
#include "functions_prototypes.h"

void help_msg(void);

int main(int argc, char *argv[]) {

  if (1 == argc) {
    help_msg();
    return EXIT_FAILURE;
  }

  if (-1 == (sysconf(_SC_CLK_TCK))) {
    printf("%s\n", "Error: sysconf() failed");
    return EXIT_FAILURE;
  }

/* They should rename clang to C++ Lang */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  char song[VLA] = "";
  char combined[WHOLE_MAIN_ARR_LEN] = "";
  char *all = combined;
  char packs[VLA], mobo[VLA], cpu[VLA], ram[VLA], ssd[VLA], net_speed[VLA];
  char kernel[VLA], volume[VLA], taim[VLA], fans[VLA], statio[VLA];
  char voltage[VLA], cpu_temp[VLA], mobo_temp[VLA], net[VLA];
  char cores_load[VLA], cpu_clock_speed[VLA], cpu_info[VLA];

  const struct option options[] = {
    { "mpd",          no_argument,       NULL, 'M' },
    { "cpu",          no_argument,       NULL, 'c' },
    { "coresload",    no_argument,       NULL, 'L' },
    { "cpuspeed",     no_argument,       NULL, 'C' },
    { "cpuinfo",      no_argument,       NULL, 'I' },
    { "cputemp",      no_argument,       NULL, 'T' },
    { "ram",          no_argument,       NULL, 'r' },
    { "storage",      no_argument,       NULL, 's' },
    { "packages",     no_argument,       NULL, 'p' },
    { "kernel",       no_argument,       NULL, 'k' },
    { "voltage",      no_argument,       NULL, 'v' },
    { "fans",         no_argument,       NULL, 'f' },
    { "mobo",         no_argument,       NULL, 'm' },
    { "volume",       no_argument,       NULL, 'V' },
    { "time",         no_argument,       NULL, 't' },
    { "help",         no_argument,       NULL, 'h' },
    { "iface",        required_argument, NULL, 'i' },
    { "bandwidth",    required_argument, NULL, 'b' },
    { "statio",       required_argument, NULL, 'S' },
    { NULL,           0,                 NULL,  0  }
  };

  int ch = 0;
  while (0 < (ch = getopt_long(argc, argv, "McCLTIrspkvfmdVthi:S:b:", options, NULL))) {
    switch (ch) {
      case 'M':
#if defined (HAVE_MPD_CLIENT_H)
        GET_N_FMT(song, all, FMT_SONG, song);
        break;
#else
        printf("%s\n", "recompile the program --with-mpd");
        return EXIT_FAILURE;
#endif

      case 'c':
        get_cpu(cpu);
        SLEEP_SLEEP_BABY(sysconf(_SC_CLK_TCK) * 1000000L);
        GET_N_FMT(cpu, all, FMT_CPU, CPU_STR, cpu);
        break;

      case 'L':
        get_cores_load(cores_load);
        SLEEP_SLEEP_BABY(sysconf(_SC_CLK_TCK) * 1000000L);
        GET_N_FMT(cores_load, all, FMT_CORES, CPU_STR, cores_load);
        break;

      case 'T':
        GET_N_FMT(cpu_temp, all, FMT_TEMP, cpu_temp);
        break;

      case 'r':
        GET_N_FMT(ram, all, FMT_RAM, RAM_STR, ram);
        break;

      case 's':
        GET_N_FMT(ssd, all, FMT_SSD, SSD_STR, ssd);
        break;

      case 'p':
        GET_N_FMT(packs, all, FMT_PKGS, PKG_STR, packs);
        break;

      case 'k':
        GET_N_FMT(kernel, all, FMT_KERN, kernel);
        break;

      case 'v':
        GET_N_FMT(voltage, all, FMT_VOLT, VOLT_STR, voltage);
        break;

      case 'f':
        GET_N_FMT(fans, all, FMT_FANS, FANS_STR, fans);
        break;

      case 'm':
        GET_N_FMT(mobo, all, FMT_MOBO, MOBO_STR, mobo);
        break;

      case 'd':
        GET_N_FMT(mobo_temp, all, FMT_TEMP, mobo_temp);
        break;

      case 'V':
#if defined (HAVE_ALSA_ASOUNDLIB_H)
        GET_N_FMT(volume, all, FMT_VOL, VOL_STR, volume);
        break;
#else
        printf("%s\n", "recompile the program --with-alsa");
        return EXIT_FAILURE;
#endif

      case 't':
        GET_N_FMT(taim, all, FMT_TIME" ", TIME_STR, taim);
        break;

      case 'b':
        get_net(net, optarg, false);
        GLUE(all, FMT_NET, NET_STR, net);
        break;

      case 'i':
        get_net(net_speed, optarg, true);
        SLEEP_SLEEP_BABY(850000000L);
        get_net(net_speed, optarg, true);
        GLUE(all, FMT_NET, SPEED_STR, net_speed);
        break;

      case 'S':
        get_statio(statio, optarg);
        GLUE(all, FMT_STATIO, STATIO_STR, statio);
        break;

      case 'C':
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
        GET_N_FMT(cpu_clock_speed, all, FMT_CPUSPEED, cpu_clock_speed);
        break;
#else
        printf("%s\n", "This option is not supported "
                  "by your CPU architecture");
        return EXIT_FAILURE;
#endif

      case 'I':
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
        GET_N_FMT(cpu_info, all, FMT_CPUSPEED, cpu_info);
        break;
#else
        printf("%s\n", "This option is not supported "
                  "by your CPU architecture");
        return EXIT_FAILURE;
#endif

      case 'h':
        help_msg();
        return EXIT_SUCCESS;

      default:
        help_msg();
        return EXIT_FAILURE;
    }
  }

#if defined (HAVE_X11_XLIB_H)
  set_status(combined);
#else
  printf("%s\n", combined);
#endif

  return EXIT_SUCCESS;
}


void help_msg(void) {
  printf("%s\n",
      "Available options:\n"
      "  -M, --mpd\t The currently played song name (if any).\n"
      "  -c, --cpu\t The current cpu load (summed up all cores/threads).\n"
      "  -L, --coresload Show the load regarding each individual cpu core/thread.\n"
      "  -T, --cputemp\t The current cpu temperature.\n"
      "  -C, --cpuspeed Show your maximum cpu clock speed in MHz.\n"
      "  -I, --cpuinfo\t Detect your CPU vendor, stepping, family.\n"
      "  -r, --ram\t The used ram.\n"
      "  -s, --storage\t The used drive storage.\n"
      "  -p, --packages The number of installed packages.\n"
      "  -k, --kernel\t The kernel version.\n"
      "  -v, --voltage\t The system voltage.\n"
      "  -f, --fans\t All system fans and their speed in RPM.\n"
      "  -m, --mobo\t Show the motherboard name and vendor.\n"
      "  -m, --mobotemp The motherboard temperature.\n"
      "  -V, --volume\t The volume.\n"
      "  -t, --time\t The current time.\n"
      "  -b, --bandwidth The consumed internet bandwidth so far [argument - eth0].\n"
      "  -i, --iface\t The current download and upload speed [argument - eth0].\n"
      "  -S, --statio\t Read and written MBs to the drive so far [argument - sda].\n"
  );
}
