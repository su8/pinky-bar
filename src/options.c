/*
   Copyright 08/08/2016
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
#include "prototypes/cpu.h"
#include "prototypes/sound.h"
#include "prototypes/net.h"
#include "prototypes/options.h"

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
  { .name = "ramperc",      .key = 'r',                .doc = "The used ram in percentage."                              },
  { .name = "ramtotal",     .key = 'J',                .doc = "The total ram."                                           },
  { .name = "ramfree",      .key = 'K',                .doc = "The free ram."                                            },
  { .name = "ramshared",    .key = 'l',                .doc = "The shared ram."                                          },
  { .name = "rambuffer",    .key = 'o',                .doc = "The buffered ram."                                        },
  { .name = "driveperc",    .key = 's',                .doc = "The used drive storage in percentage."                    },
  { .name = "drivetotal",   .key = 'n',                .doc = "The total drive storage."                                 },
  { .name = "drivefree",    .key = 'N',                .doc = "The free drive storage."                                  },
  { .name = "driveavail",   .key = 'O',                .doc = "The available drive storage."                             },
  { .name = "battery",      .key = 'g',                .doc = "The remaining battery charge."                            },
  { .name = "drivemodel",   .key = 'F', .arg = "sda",  .doc = "The vendor name of your drive."                           },
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
  { .name = "nicinfo",      .key = 'G', .arg = "eth0", .doc = "The NIC vendor and model."                                },
  { .name = "nicdrv",       .key = 'h', .arg = "eth0", .doc = "The NIC driver."                                          },
  { .name = "nicver",       .key = 'H', .arg = "eth0", .doc = "The NIC version."                                         },
  { .name = "nicfw",        .key = 'j', .arg = "eth0", .doc = "The NIC firmware."                                        },
  { .name = "statio",       .key = 'S', .arg = "sda",  .doc = "Read and written MBs to the drive so far."                },
  { .doc = NULL }
};
struct arguments {
  char *all;
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  struct arguments *arguments = state->input;
  switch(key) {
    case 'M':
#if defined (HAVE_MPD_CLIENT_H)
      {
        char song[VLA] = "";
        GET_N_FMT(song, arguments->all, FMT_SONG, song);
      }
      break;
#else
      printf("%s\n", "recompile the program --with-mpd");
      return ARGP_KEY_ERROR;
#endif

    NEW_CPU_LABEL('c', char cpu[VLA], cpu, FMT_CPU, CPU_STR);

    NEW_CPU_LABEL('L', char cores_load[VLA], cores_load, FMT_CORES, CPU_STR);

    NEW_LABEL('T', char cpu_temp[VLA], cpu_temp, FMT_TEMP);

    NEW_RAM_LABEL('J', char ram_total[VLA], ram_total, 1, FMT_RAM2, RAM_STR);

    NEW_RAM_LABEL('K', char ram_free[VLA], ram_free, 2, FMT_RAM2, RAM_STR);

    NEW_RAM_LABEL('l', char ram_shared[VLA], ram_shared, 3, FMT_RAM2, RAM_STR);

    NEW_RAM_LABEL('o', char ram_buffer[VLA], ram_buffer, 4, FMT_RAM2, RAM_STR);

    NEW_RAM_LABEL('r', char ram_perc[VLA], ram_perc, 5, FMT_RAM, RAM_STR);

    NEW_SSD_LABEL('n', char ssd_total[VLA], ssd_total, 1, FMT_SSD2, SSD_STR);

    NEW_SSD_LABEL('N', char ssd_free[VLA], ssd_free, 2, FMT_SSD2, SSD_STR);

    NEW_SSD_LABEL('O', char ssd_avail[VLA], ssd_avail, 3, FMT_SSD2, SSD_STR);

    NEW_SSD_LABEL('s', char ssd_perc[VLA], ssd_perc, 4, FMT_SSD, SSD_STR);

    NEW_LABEL('g', char battery[VLA], battery, FMT_BATT, BATT_STR);

    NEW_ARG_LABEL('F', char ssd_model[VLA], ssd_model, FMT_KERN);

    NEW_LABEL('p', char packs[VLA], packs, FMT_PKGS, PKG_STR);

    NEW_LABEL('k', char kernel[VLA], kernel, FMT_KERN);

    NEW_LABEL('v', char voltage[VLA], voltage, FMT_VOLT, VOLT_STR);

    NEW_LABEL('f', char fans[VLA], fans, FMT_FANS, FANS_STR);

    NEW_LABEL('m', char mobo[VLA], mobo, FMT_MOBO, MOBO_STR);

    NEW_LABEL('d', char mobo_temp[VLA], mobo_temp, FMT_TEMP);

    case 'V':
#if defined (HAVE_ALSA_ASOUNDLIB_H)
      {
        char volume[VLA];
        GET_N_FMT(volume, arguments->all, FMT_VOL, VOL_STR, volume);
      }
      break;
#else
      printf("%s\n", "recompile the program --with-alsa");
      return ARGP_KEY_ERROR;
#endif

    NEW_LABEL('t', char taim[VLA], taim, FMT_TIME" ", TIME_STR);

    NEW_NET_LABEL('b', char net[VLA], net, 1, FMT_NET, NET_STR);

    NEW_NET_LABEL('i', char net_speed[VLA], net_speed, 2, FMT_NET, SPEED_STR);

    NEW_NET_LABEL('a', char net_addr[VLA], net_addr, 3, FMT_KERN);

    NEW_NET_LABEL('A', char mac[VLA], mac, 4, FMT_KERN);

    NEW_NET_LABEL('B', char mask[VLA], mask, 5, FMT_KERN);

    NEW_NET_LABEL('D', char net_cast[VLA], net_cast, 6, FMT_KERN);

    NEW_NET_LABEL('e', char link_speed[VLA], link_speed, 7, FMT_KERN);

    NEW_NET_LABEL('h', char nic_drv[VLA], nic_drv, 8, FMT_KERN);

    NEW_NET_LABEL('H', char nic_ver[VLA], nic_ver, 9, FMT_KERN);

    NEW_NET_LABEL('j', char nic_info[VLA], nic_info, 10, FMT_KERN);

    NEW_ARG_LABEL('G', char nic_info[VLA], nic_info, FMT_KERN);

    NEW_ARG_LABEL('E', char ip_lookup[VLA], ip_lookup, FMT_KERN);

    NEW_ARG_LABEL('S', char statio[VLA], statio, FMT_STATIO, STATIO_STR);

    case 'C':
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
      {
        char cpu_clock_speed[VLA];
        GET_N_FMT(cpu_clock_speed, arguments->all, FMT_CPUSPEED, cpu_clock_speed);
      }
      break;
#else
      printf("%s\n", "This option is not supported "
                "by your CPU architecture");
      return ARGP_KEY_ERROR;
#endif

    case 'I':
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
      {
        char cpu_info[VLA];
        GET_N_FMT(cpu_info, arguments->all, FMT_CPUSPEED, cpu_info);
      }
      break;
#else
      printf("%s\n", "This option is not supported "
                "by your CPU architecture");
      return ARGP_KEY_ERROR;
#endif

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return EXIT_SUCCESS;
}


void
parse_opts(int argc, char *argv[], char *combined) {
  struct arguments arguments;
  arguments.all = combined;

  static const struct argp arg_parser = {
    .parser = parse_opt,
    .options = options,
    .doc = doc
  };
  argp_parse(&arg_parser, argc, argv, ARGP_IN_ORDER, NULL, &arguments);
}
