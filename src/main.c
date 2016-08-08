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

#include <argp.h>

#include "config.h" /* auto-generated */
#include "include/headers.h"
#include "cpu.h"
#include "sound.h"
#include "net.h"


const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = "https://github.com/wifiextender/pinky-bar ";
static const char doc[] = "Statusbar program for anything (Window Manager, terminal multiplexer, etc..)";
static const struct argp_option options[] = {
  { .doc = "Available options:" },
  { .name = "mpd",          .key = 'M',                .doc = "The currently played song name (if any)."                 },
  { .name = "cpu",          .key = 'c',                .doc = "The current cpu load (summed up all cores/threads)."      },
  { .name = "coresload",    .key = 'L',                .doc = "Show the load regarding each individual cpu core/thread." },
  { .name = "cpuspeed",     .key = 'C',                .doc = "The current cpu temperature."                             },
  { .name = "cpuinfo",      .key = 'I',                .doc = "Show your maximum cpu clock speed in MHz."                },
  { .name = "cputemp",      .key = 'T',                .doc = "Detect your CPU vendor, stepping, family."                },
  { .name = "ram",          .key = 'r',                .doc = "The used ram."                                            },
  { .name = "storage",      .key = 's',                .doc = "The used drive storage."                                  },
  { .name = "drivemodel",   .key = 'F',  .arg = "sda", .doc = "The vendor name of your drive."                           },
  { .name = "packages",     .key = 'p',                .doc = "The number of installed packages."                        },
  { .name = "kernel",       .key = 'k',                .doc = "The kernel version."                                      },
  { .name = "voltage",      .key = 'v',                .doc = "The system voltage"                                       },
  { .name = "fans",         .key = 'f',                .doc = "All system fans and their speed in RPM."                  },
  { .name = "mobo",         .key = 'm',                .doc = "The motherboard vendor and model names."                  },
  { .name = "mobotemp",     .key = 'd',                .doc = "The motherboard temperature."                             },
  { .name = "volume",       .key = 'V',                .doc = "The volume."                                              },
  { .name = "time",         .key = 't',                .doc = "The current time."                                        },
  { .name = "ipaddr",       .key = 'a', .arg = "eth0", .doc = "The local IP address."                                    },
  { .name = "iface",        .key = 'i', .arg = "eth0", .doc = "The consumed internet bandwidth so far."                  },
  { .name = "bandwidth",    .key = 'b', .arg = "eth0", .doc = "The current download and upload speeds."                  },
  { .name = "ipmac",        .key = 'A', .arg = "eth0", .doc = "The NIC mac address."                                     },
  { .name = "ipmask",       .key = 'B', .arg = "eth0", .doc = "The NIC subnet mask address."                             },
  { .name = "ipcast",       .key = 'D', .arg = "eth0", .doc = "The NIC broadcast address."                               },
  { .name = "iplink",       .key = 'e', .arg = "eth0", .doc = "The NIC link speed (useful for wireless/wifi)."           },
  { .name = "iplookup",     .key = 'E', .arg = "site", .doc = "Mini website IP lookup."                                  },
  { .name = "statio",       .key = 'S', .arg = "sda",  .doc = "Read and written MBs to the drive so far."                },
  { .doc = NULL }
};
static char combined[WHOLE_MAIN_ARR_LEN];
char *all = combined;


static error_t
parse_opt(int key, char *arg, struct argp_state *state) {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  /* Keep your cheesy fingers away from :; */
  switch(key) {
    case 'M':;
#if defined (HAVE_MPD_CLIENT_H)
      char song[VLA] = "";
      GET_N_FMT(song, all, FMT_SONG, song);
      break;
#else
      printf("%s\n", "recompile the program --with-mpd");
      return ARGP_KEY_ERROR;
#endif

    case 'c':;
      char cpu[VLA];
      GET_CPU_N_FMT(cpu, all, FMT_CPU, CPU_STR, cpu);
      break;

    case 'L':;
      char cores_load[VLA];
      GET_CPU_N_FMT(cores_load, all, FMT_CORES, CPU_STR, cores_load);
      break;

    case 'T':;
      char cpu_temp[VLA];
      GET_N_FMT(cpu_temp, all, FMT_TEMP, cpu_temp);
      break;

    case 'r':;
      char ram[VLA];
      GET_N_FMT(ram, all, FMT_RAM, RAM_STR, ram);
      break;

    case 's':;
      char ssd[VLA];
      GET_N_FMT(ssd, all, FMT_SSD, SSD_STR, ssd);
      break;

    case 'F':;
      char ssd_model[VLA];
      get_ssd_model(ssd_model, arg);
      GLUE(all, FMT_KERN, ssd_model);
      break;

    case 'p':;
      char packs[VLA];
      GET_N_FMT(packs, all, FMT_PKGS, PKG_STR, packs);
      break;

    case 'k':;
      char kernel[VLA];
      GET_N_FMT(kernel, all, FMT_KERN, kernel);
      break;

    case 'v':;
      char voltage[VLA];
      GET_N_FMT(voltage, all, FMT_VOLT, VOLT_STR, voltage);
      break;

    case 'f':;
      char fans[VLA];
      GET_N_FMT(fans, all, FMT_FANS, FANS_STR, fans);
      break;

    case 'm':;
      char mobo[VLA];
      GET_N_FMT(mobo, all, FMT_MOBO, MOBO_STR, mobo);
      break;

    case 'd':;
      char mobo_temp[VLA];
      GET_N_FMT(mobo_temp, all, FMT_TEMP, mobo_temp);
      break;

    case 'V':;
#if defined (HAVE_ALSA_ASOUNDLIB_H)
      char volume[VLA];
      GET_N_FMT(volume, all, FMT_VOL, VOL_STR, volume);
      break;
#else
      printf("%s\n", "recompile the program --with-alsa");
      return ARGP_KEY_ERROR;
#endif

    case 't':;
      char taim[VLA];
      GET_N_FMT(taim, all, FMT_TIME" ", TIME_STR, taim);
      break;

    case 'b':;
      char net[VLA];
      GET_NET_N_FMT(net, arg, 1, all, FMT_NET, NET_STR, net);
      break;

    case 'i':;
      char net_speed[VLA];
      GET_NET_N_FMT(net_speed, arg, 2, all, FMT_NET, SPEED_STR, net_speed);
      break;

    case 'a':;
      char net_addr[VLA];
      GET_NET_N_FMT(net_addr, arg, 3, all, FMT_KERN, net_addr);
      break;

    case 'A':;
      char mac[VLA];
      GET_NET_N_FMT(mac, arg, 4, all, FMT_KERN, mac);
      break;

    case 'B':;
      char mask[VLA];
      GET_NET_N_FMT(mask, arg, 5, all, FMT_KERN, mask);
      break;

    case 'D':;
      char net_cast[VLA];
      GET_NET_N_FMT(net_cast, arg, 6, all, FMT_KERN, net_cast);
      break;

    case 'e':;
      char link_speed[VLA];
      GET_NET_N_FMT(link_speed, arg, 7, all, FMT_KERN, link_speed);
      break;

    case 'E':;
      char ip_lookup[VLA];
      get_ip_lookup(ip_lookup, arg);
      GLUE(all, FMT_KERN, ip_lookup);
      break;

    case 'S':;
      char statio[VLA];
      get_statio(statio, arg);
      GLUE(all, FMT_STATIO, STATIO_STR, statio);
      break;

    case 'C':;
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
      char cpu_clock_speed[VLA];
      GET_N_FMT(cpu_clock_speed, all, FMT_CPUSPEED, cpu_clock_speed);
      break;
#else
      printf("%s\n", "This option is not supported "
                "by your CPU architecture");
      return ARGP_KEY_ERROR;
#endif

    case 'I':;
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
      char cpu_info[VLA];
      GET_N_FMT(cpu_info, all, FMT_CPUSPEED, cpu_info);
      break;
#else
      printf("%s\n", "This option is not supported "
                "by your CPU architecture");
      return ARGP_KEY_ERROR;
#endif

    case ARGP_KEY_END:;
      if (1 < state->arg_num)
        argp_usage(state);
    break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return EXIT_SUCCESS;
}

static const struct argp arg_parser = {
  .parser = parse_opt,
  .options = options,
  .doc = doc
};


int main(int argc, char *argv[]) {

  if (1 == argc) {
    printf("%s\n", "Try --help or --usage for more information.");
    return EXIT_FAILURE;
  }
  if (-1 == (sysconf(_SC_CLK_TCK))) {
    printf("%s\n", "Error: sysconf() failed");
    return EXIT_FAILURE;
  }

  argp_parse(&arg_parser, argc, argv, ARGP_IN_ORDER, NULL, NULL);

#if defined (HAVE_X11_XLIB_H)
  set_status(combined);
#else
  printf("%s\n", combined);
#endif

  return EXIT_SUCCESS;
}
