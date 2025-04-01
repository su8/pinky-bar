/*
   08/08/2016, 04/01/2025

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
#include <limits.h>

static char BLUE[64] = {'\0'};
static char PINK[64] = {'\0'};
static char YELLOW[64] = {'\0'};
static char ENT[64] = {'\0'};

#include "config.h" /* Auto-generated */
#include "include/headers.h"
#include "prototypes/cpu.h"
#include "prototypes/sound.h"
#include "prototypes/net.h"
#include "prototypes/options.h"
#include "prototypes/weather.h"
#include "prototypes/mail.h"
#include "prototypes/smart.h"
#include "prototypes/cpp.hpp"
#include "prototypes/extend.h"
#include "prototypes/x11.h"
#include "prototypes/curl.h"
#include "prototypes/sqlite.h"
#include "prototypes/packages.h"

/* Because we ran out of a-z A-Z options,
 * only long ones will be supported from now on.
 * The enumerated argp_option keys below will be used as 
 * case labels by the parse_opt switch */
enum {
  NICDRV = CHAR_MAX + 1,
  KERNODE,
  DRIVETEMP,
  PERLSCRIPT,
  PYTHONSCRIPT,
  LUASCRIPT,
  RUBYSCRIPT,
  RSCRIPT,
  ASSEMBLY,
  LISP,
  OCAML,
  RUST,
  GO,
  CPP,
  SLANG,
  TCL,
  WIFINAME,
  KEYBOARD,
  GMAIL,
  IP,
  MOUSE,
  NUMLOCK,
  CAPSLOCK,
  SCROLLLOCK,
  PASSWORD,
  GITHUB,
  REDDIT,
  PING,
  SQLITEE,
  UPDATES,
  RAMUSED,
  LOADAVG5,
  LOADAVG15,
  TITLE,
  YAHOO,
  CLR1,
  CLR2,
  CLR3,
  FORMA7,
  BULLSHIFT
};
const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = "https://github.com/su8/pinky-bar ";
static const char doc[] = "Statusbar program for anything (Window Manager, terminal multiplexer, etc..)";
static const struct argp_option options[] = {
  { .doc = "Available options:" },
  { .name = "mpd",          .key = 'M',                .doc = "The song filename."                                       },
  { .name = "mpdartist",    .key = 'x',                .doc = "The song artist(s) name(s)."                              },
  { .name = "mpdtitle",     .key = 'X',                .doc = "The song title."                                          },
  { .name = "mpdalbum",     .key = 'y',                .doc = "The song album name."                                     },
  { .name = "mpddate",      .key = 'Y',                .doc = "The song date."                                           },
  { .name = "cpu-percent",  .key = 'c',                .doc = "The current cpu load (summed up all cores/threads)."      },
  { .name = "cpu-percent-all", .key = 'L',             .doc = "Show the load regarding each individual cpu core/thread." },
  { .name = "cpuspeed",     .key = 'C',                .doc = "The current cpu temperature."                             },
  { .name = "cpuinfo",      .key = 'I',                .doc = "Show your maximum cpu clock speed in MHz."                },
  { .name = "cputemp",      .key = 'T',                .doc = "Detect your CPU vendor, stepping, family."                },
  { .name = "ramperc",      .key = 'r',                .doc = "The used ram in percentage."                              },
  { .name = "ramtotal",     .key = 'J',                .doc = "The total ram."                                           },
  { .name = "ramfree",      .key = 'K',                .doc = "The free ram."                                            },
  { .name = "driveperc",    .key = 's',                .doc = "The used drive storage in percentage."                    },
  { .name = "drivetotal",   .key = 'n',                .doc = "The total drive storage."                                 },
  { .name = "drivefree",    .key = 'N',                .doc = "The free drive storage."                                  },
  { .name = "driveavail",   .key = 'O',                .doc = "The available drive storage."                             },
  { .name = "drivetemp",    .key = DRIVETEMP,          .doc = "Read the drive temperature from S.M.A.R.T"                },
  { .name = "dvdstr",       .key = 'z',                .doc = "The vendor and model name of your cdrom/dvdrom."          },
  { .name = "battery",      .key = 'g',                .doc = "The remaining battery charge."                            },
  { .name = "packages",     .key = 'p',                .doc = "The number of installed packages."                        },
  { .name = "kernsys",      .key = 'P',                .doc = "The kernel name."                                         },
  { .name = "kernode",      .key = KERNODE,            .doc = "The network node hostname."                               },
  { .name = "kernrel",      .key = 'Q',                .doc = "The kernel release."                                      },
  { .name = "kernver",      .key = 'R',                .doc = "The kernel version."                                      },
  { .name = "kernarch",     .key = 'u',                .doc = "The machine architecture."                                },
  { .name = "kernel",       .key = 'k',                .doc = "Combined kernel name and version."                        },
  { .name = "uptime",       .key = 'U',                .doc = "The system uptime"                                        },
  { .name = "load-1min",    .key = 'w',                .doc = "The system average load for past 1 minutes"               },
  { .name = "load-5min",    .key = LOADAVG5,           .doc = "The system average load for past 5 minutes"               },
  { .name = "load-15min",   .key = LOADAVG15,          .doc = "The system average load for past 15 minutes"              },
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
  { .name = "iplookup",     .key = 'E', .arg = "site", .doc = "Mini website IP lookup."                                  },
  { .name = "statio",       .key = 'S', .arg = "sda",  .doc = "Read and written MBs to the drive so far."                },
  { .name = "password",     .key = PASSWORD, .arg = "num",  .doc = "Generate 20 character long password."                },
  { .name = "updates",      .key = UPDATES,            .doc = "Number all pending system updates."                       },
  { .name = "title",        .key = TITLE, .arg = "Do Stuff",  .doc = "Static string that's displayed to you, could be a title or header to prefix other option." },
  { .name = "color1",       .key = CLR1, .arg = "hex color",  .doc = "Color for the title."                              },
  { .name = "color2",       .key = CLR2, .arg = "hex color",  .doc = "Color for the option."                             },
  { .name = "color3",       .key = CLR3, .arg = "hex color",  .doc = "Kernel/misc color."                                },
  { .name = "fmt",          .key = FORMA7, .arg = "tmux",  .doc = "Use different format for the output data."            },

#if WITH_SQLITE == 1
  { .name = "sqlite",       .key = SQLITEE, .arg = "string", .doc = "Connect to sqlite db and perform SELECT operation." },
#endif /* WITH_SQLITE */

#if WITH_PING == 1
  { .name = "pingtime",     .key = PING, .arg = "url", .doc = "Perform a GET request and measure the round trip."        },
#endif /* WITH_PING */

#if WITH_REDDIT == 1
  { .name = "reddit",       .key = REDDIT,             .doc = "Query reddit and number all unread notifications."        },
#endif /* WITH_REDDIT */

#if WITH_GITHUB == 1
  { .name = "github",       .key = GITHUB,             .doc = "Query GitHub and number all unread notifications."        },
#endif /* WITH_GITHUB */

#if WITH_IP == 1
  { .name = "ip",           .key = IP,                 .doc = "Return your external ip address (ipv4)."                  },
#endif /* WITH_IP */

#if WITH_GMAIL == 1
  { .name = "gmail",        .key = GMAIL,              .doc = "Count all unread gmail emails."                           },
#endif /* WITH_GMAIL */

#if WITH_YAHOO == 1
  { .name = "yahoo",        .key = YAHOO,              .doc = "Count all unread gmail emails."                           },
#endif /* WITH_YAHOO */

#if WITH_PERL == 1
  { .name = "perl",  .key = PERLSCRIPT, .arg = "script", .doc = "Extend the program with perl, read README."             },
#endif /* WITH_PERL */

#if WITH_LUA == 1
  { .name = "lua",   .key = LUASCRIPT,  .arg = "script", .doc = "Extend the program with lua, read README."              },
#endif /* WITH_LUA */

#if WITH_RUBY == 1
  { .name = "ruby", .key = RUBYSCRIPT,  .arg = "script", .doc = "Extend the program with ruby, read README."             },
#endif /* WITH_RUBY */

#if WITH_PYTHON == 1
  { .name = "python",  .key = PYTHONSCRIPT, .arg = "script", .doc = "Extend the program with python, read README."       },
#endif /* WITH_PYTHON */

#if WITH_R == 1
  { .name = "R",  .key = RSCRIPT, .arg = "script", .doc = "Extend the program with R, read README."                      },
#endif /* WITH_R */

#if WITH_ASSEMBLY == 1
  { .name = "asm",         .key = ASSEMBLY,                .doc = "Extend the program with assembly, read README."       },
#endif /* WITH_ASSEMBLY */

#if WITH_ECL == 1
  { .name = "lisp",         .key = LISP,   .arg = "script",    .doc = "Extend the program with lisp, read README."       },
#endif /* WITH_ECL */

#if WITH_OCAML == 1
  { .name = "ocaml",         .key = OCAML,                 .doc = "Extend the program with ocaml, read README."          },
#endif /* WITH_OCAML */

#if WITH_RUST == 1
  { .name = "rust",         .key = RUST,                   .doc = "Extend the program with rust, read README."           },
#endif /* WITH_RUST */

#if WITH_GO == 1
  { .name = "go",         .key = GO,                       .doc = "Extend the program with go, read README."             },
#endif /* WITH_GO */

#if WITH_CPP == 1
  { .name = "cpp",         .key = CPP,                     .doc = "Extend the program with c++, read README."            },
#endif /* WITH_CPP */

#if WITH_SLANG == 1
  { .name = "slang",         .key = SLANG,    .arg = "script",    .doc = "Extend the program with slang, read README."   },
#endif /* WITH_SLANG */

#if WITH_TCL == 1
  { .name = "tcl",         .key = TCL,    .arg = "script",    .doc = "Extend the program with tcl, read README."         },
#endif /* WITH_TCL */

#if WITH_WEATHER == 1
  { .name = "weather", .key = 'q', .arg = "London,uk", .doc = "The temperature outside."                                 },
#endif /* WITH_WEATHER */

#if defined(HAVE_MPD_CLIENT_H)
  { .name = "mpdtrack",     .key = 'W',                .doc = "The song track name."                                     },
#endif /* HAVE_MPD_CLIENT_H */

#if WITH_KEYBOARD == 1 && defined(HAVE_X11_XKBLIB_H)
  { .name = "keyboard",     .key = KEYBOARD,           .doc = "Query xorg and show the currently used keyboard layout."  },
#endif /* WITH_KEYBOARD && HAVE_X11_XKBLIB_H */

#if WITH_MOUSE == 1 && defined(HAVE_X11_XLIB_H)
  { .name = "mouse",        .key = MOUSE,              .doc = "Query xorg to get the current mouse speed."               },
#endif /* WITH_MOUSE && HAVE_X11_XLIB_H */

#if WITH_NUMLOCK == 1 && defined(HAVE_X11_XLIB_H)
  { .name = "numlock",      .key = NUMLOCK,            .doc = "Query xorg to get the current state of numlock."          },
  { .name = "capslock",     .key = CAPSLOCK,           .doc = "Query xorg to get the current state of capslock."         },
  { .name = "scrolllock",   .key = SCROLLLOCK,         .doc = "Query xorg to get the current state of capslock."         },
#endif /* WITH_MOUSE && HAVE_X11_XLIB_H */

#if !defined(__OpenBSD__)
  { .name = "ramshared",    .key = 'l',                .doc = "The shared ram."                                          },
  { .name = "rambuffer",    .key = 'o',                .doc = "The buffered ram."                                        },
#endif /* !__OpenBSD__ */


#if defined(__OpenBSD__)
  { .name = "ramused",      .key = 'l',                .doc = "The used ram in MB."                                      },
#endif /* __OpenBSD__ */

#if defined(__linux__)
  { .name = "nicfw",        .key = 'j', .arg = "eth0", .doc = "The NIC firmware."                                        },
  { .name = "drivemodel",   .key = 'F', .arg = "sda",  .doc = "The vendor name of your drive."                           },
  { .name = "nicdrv",    .key = NICDRV, .arg = "eth0", .doc = "The NIC driver."                                          },
  { .name = "nicver",       .key = 'H', .arg = "eth0", .doc = "The NIC version."                                         },
  { .name = "iplink",       .key = 'e', .arg = "eth0", .doc = "The NIC link speed (useful for wireless/wifi)."           },
  { .name = "nicinfo",      .key = 'G', .arg = "eth0", .doc = "The NIC vendor and model."                                },
  { .name = "wifiname",     .key = 'h', .arg = "wlan0", .doc = "The name of currently connected wireless/wifi network."  },
  { .name = "ramused",      .key = RAMUSED,            .doc = "The used ram in MB."                                      },
#endif /* __linux__ */

#if defined(__FreeBSD__) || defined(__OpenBSD__)
  { .name = "swapused",     .key = 'Z',                .doc = "The used drive swap in MB."                               },
  { .name = "swaperc",      .key = 'F',                .doc = "The used drive swap in percentage."                       },
  { .name = "swaptotal",    .key = 'h',                .doc = "The total drive swap."                                    },
  { .name = "swapavail",    .key = 'H',                .doc = "The available drive swap."                                },
  { .name = "nicgw",        .key = 'j', .arg = "re0",  .doc = "The NIC gateway address."                                 },
  { .name = "wifiname",     .key = WIFINAME, .arg = "wlan0", .doc = "The name of currently connected wireless/wifi network."   },
#endif /* __FreeBSD__ || __OpenBSD__ */

  { .doc = NULL }
};
struct arguments {
  char *all;
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {

  struct timespec tc = {0L, 0L};

  struct arguments *arguments = state->input;
  switch(key) {

    NEW_MPD_LABEL('x', char song_artist[VLA], song_artist, 2, FMT_SONG);

    NEW_MPD_LABEL('X', char song_title[VLA], song_title, 3, FMT_SONG);

    NEW_MPD_LABEL('y', char song_album[VLA], song_album, 4, FMT_SONG);

    NEW_MPD_LABEL('Y', char song_date[VLA], song_date, 5, FMT_SONG);

    NEW_MPD_LABEL('M', char song[VLA], song, 6, FMT_SONG);

    NEW_CPU_LABEL('c', char cpu[VLA], cpu, FMT_CPU);

    NEW_CPU_LABEL('L', char cores_load[VLA], cores_load, FMT_CORES);

    NEW_LABEL('T', char cpu_temp[VLA], cpu_temp, FMT_TEMP);

    NEW_RAM_LABEL('J', char ram_total[VLA], ram_total, 1, FMT_RAM2);

    NEW_RAM_LABEL('K', char ram_free[VLA], ram_free, 2, FMT_RAM2);

    NEW_RAM_LABEL('l', char ram_shared[VLA], ram_shared, 3, FMT_RAM2);

    NEW_RAM_LABEL('r', char ram_perc[VLA], ram_perc, 5, FMT_RAM);

    NEW_SSD_LABEL('n', char ssd_total[VLA], ssd_total, 1, FMT_SSD2);

    NEW_SSD_LABEL('N', char ssd_free[VLA], ssd_free, 2, FMT_SSD2);

    NEW_SSD_LABEL('O', char ssd_avail[VLA], ssd_avail, 3, FMT_SSD2);

    NEW_SSD_LABEL('s', char ssd_perc[VLA], ssd_perc, 4, FMT_SSD);

    NEW_LABEL('p', char packs[VLA], packs, FMT_PKGS);

    NEW_KERNEL_LABEL('P', char kernel_sys[VLA], kernel_sys, 1, FMT_KERN);

    NEW_KERNEL_LABEL(KERNODE, char kernel_node[VLA], kernel_node, 2, FMT_KERN);

    NEW_KERNEL_LABEL('Q', char kernel_rel[VLA], kernel_rel, 3, FMT_KERN);

    NEW_KERNEL_LABEL('R', char kernel_ver[VLA], kernel_ver, 4, FMT_KERN);

    NEW_KERNEL_LABEL('u', char kernel_arch[VLA], kernel_arch, 5, FMT_KERN);

    NEW_KERNEL_LABEL('k', char kernel[VLA], kernel, 6, FMT_KERN);

    NEW_LABEL('U', char uptime[VLA], uptime, FMT_UP);

    NEW_LOADAVG_LABEL('w', char loadavg_1min[VLA], loadavg_1min, 0, FMT_PINK);

    NEW_LOADAVG_LABEL(LOADAVG5, char loadavg_5min[VLA], loadavg_5min, 1, FMT_PINK);

    NEW_LOADAVG_LABEL(LOADAVG15, char loadavg_15min[VLA], loadavg_15min, 2, FMT_PINK);

    NEW_LABEL('v', char voltage[VLA], voltage, FMT_VOLT);

    NEW_LABEL('m', char mobo[VLA], mobo, FMT_MOBO);

    NEW_LABEL('d', char mobo_temp[VLA], mobo_temp, FMT_TEMP);

    NEW_LABEL('f', char fans[VLA], fans, FMT_FANS);

    NEW_LABEL('t', char taim[VLA], taim, FMT_MOBO);

    NEW_NET_LABEL('b', char net[VLA], net, 1, FMT_NET);

    NEW_NET_LABEL('i', char net_speed[VLA], net_speed, 2, FMT_NET);

    NEW_NET_LABEL('a', char net_addr[VLA], net_addr, 3, FMT_PINK);

    NEW_NET_LABEL('A', char mac[VLA], mac, 4, FMT_PINK);

    NEW_NET_LABEL('B', char mask[VLA], mask, 5, FMT_PINK);

    NEW_NET_LABEL('D', char net_cast[VLA], net_cast, 6, FMT_PINK);

    NEW_ARG_LABEL('E', char ip_lookup[VLA], ip_lookup, FMT_PINK);

    NEW_LABEL('g', char battery[VLA], battery, FMT_BATT);

    NEW_ARG_LABEL('S', char statio[VLA], statio, FMT_STATIO);

    NEW_LABEL(DRIVETEMP, char drivetemp[VLA], drivetemp, FMT_PINK);

    NEW_ARG_LABEL(PASSWORD, char password[VLA], password, FMT_PINK);

    NEW_LABEL(UPDATES, char updates[VLA], updates, FMT_PINK);

    NEW_ARG_LABEL(TITLE, char title[VLA], title, mk_str("%s%s%s%s", BLUE, STR_SPEC, ENT, " "));

    case CLR1:
      snprintf(BLUE, 64, "%s", arg);
      break;

    case CLR2:
      snprintf(PINK, 64, "%s", arg);
      break;

    case CLR3:
      snprintf(YELLOW, 64, "%s", arg);
      break;

    case FORMA7:
    {
      if (STREQ(arg, "py3status")) {
        snprintf(ENT, 64, "%s", "]");
      }
      else if (STREQ(arg, "awesomewm")) {
        snprintf(ENT, 64, "%s", "</span>");
      }
      else if (STREQ(arg, "xmobar")) {
        snprintf(ENT, 64, "%s", "</fc>");
      }
      break;
    }

#if WITH_SQLITE == 1
    NEW_ARG_LABEL(SQLITEE, char sqlite[VLA], sqlite, FMT_PINK);
#endif /* WITH_SQLITE */


#if WITH_PING == 1
    NEW_ARG_LABEL(PING, char ping[VLA], ping, FMT_PINK);
#endif /* WITH_PING */


#if WITH_REDDIT == 1
    NEW_LABEL(REDDIT, char reddit[VLA], reddit, FMT_PINK);
#endif /* WITH_REDDIT */


#if WITH_GITHUB == 1
    NEW_LABEL(GITHUB, char github[VLA], github, FMT_PINK);
#endif /* WITH_GITHUB */


#if WITH_IP == 1
    NEW_LABEL(IP, char ip[VLA], ip, FMT_PINK);
#endif /* WITH_IP */


#if WITH_GMAIL == 1
    NEW_LABEL(GMAIL, char gmail[VLA], gmail, FMT_TIME);
#endif /* WITH_GMAIL */


#if WITH_YAHOO == 1
    NEW_LABEL(YAHOO, char yahoo[VLA], yahoo, FMT_TIME);
#endif /* WITH_YAHOO */


#if WITH_PERL == 1
    NEW_ARG_LABEL(PERLSCRIPT, char perl[VLA], perl, FMT_PINK);
#endif /* WITH_PERL */


#if WITH_LUA == 1
    NEW_ARG_LABEL(LUASCRIPT, char lua[VLA], lua, FMT_PINK);
#endif /* WITH_LUA */


#if WITH_RUBY == 1
    NEW_ARG_LABEL(RUBYSCRIPT, char ruby[VLA], ruby, FMT_PINK);
#endif /* WITH_RUBY */


#if WITH_PYTHON == 1
    NEW_ARG_LABEL(PYTHONSCRIPT, char python[VLA], python, FMT_PINK);
#endif /* WITH_PYTHON */


#if WITH_R == 1
    NEW_ARG_LABEL(RSCRIPT, char r[VLA], r, FMT_PINK);
#endif /* WITH_R */


#if WITH_ASSEMBLY == 1
    NEW_LABEL(ASSEMBLY, char assembly[VLA], assembly, FMT_PINK);
#endif /* WITH_ASSEMBLY */


#if WITH_ECL == 1
    NEW_ARG_LABEL(LISP, char ecl[VLA], ecl, FMT_PINK);
#endif /* WITH_ECL */


#if WITH_OCAML == 1
    NEW_LABEL(OCAML, char ocaml[VLA], ocaml, FMT_PINK);
#endif /* WITH_OCAML */


#if WITH_RUST == 1
    NEW_LABEL(RUST, char rust[VLA], rust, FMT_PINK);
#endif /* WITH_RUST */


#if WITH_GO == 1
    NEW_LABEL(GO, char go[VLA], go, FMT_PINK);
#endif /* WITH_GO */


#if WITH_CPP == 1
    NEW_LABEL(CPP, char cpp[VLA], cpp, FMT_PINK);
#endif /* WITH_CPP */


#if WITH_SLANG == 1
    NEW_ARG_LABEL(SLANG, char slang[VLA], slang, FMT_PINK);
#endif /* WITH_SLANG */


#if WITH_TCL == 1
    NEW_ARG_LABEL(TCL, char tcl[VLA], tcl, FMT_PINK);
#endif /* WITH_TCL */


#if WITH_WEATHER == 1
    NEW_ARG_LABEL('q', char weather[VLA], weather, FMT_PINK);
#endif /* WITH_WEATHER */


#if defined(HAVE_MPD_CLIENT_H)
    NEW_MPD_LABEL('W', char song_track[VLA], song_track, 1, FMT_SONG);
#endif /* HAVE_MPD_CLIENT_H */


#if WITH_KEYBOARD == 1 && defined(HAVE_X11_XKBLIB_H)
    NEW_LABEL(KEYBOARD, char keyboard[VLA], keyboard, FMT_PINK);
#endif /* WITH_KEYBOARD && HAVE_X11_XKBLIB_H */


#if WITH_MOUSE == 1 && defined(HAVE_X11_XLIB_H)
    NEW_LABEL(MOUSE, char mouse[VLA], mouse, FMT);
#endif /* WITH_MOUSE && HAVE_X11_XLIB_H */


#if WITH_NUMLOCK == 1 && defined(HAVE_X11_XLIB_H)
    NEW_LABEL(NUMLOCK, char numlock[VLA], numlock, FMT_PINK);

    NEW_LABEL(CAPSLOCK, char capslock[VLA], capslock, FMT_PINK);

    NEW_LABEL(SCROLLLOCK, char scrolllock[VLA], scrolllock, FMT_PINK);
#endif /* WITH_NUMLOCK && HAVE_X11_XLIB_H */


#if defined(HAVE_CDIO_CDIO_H) || defined(__linux__)
    NEW_LABEL('z', char dvd[VLA], dvd, FMT_PINK);
#endif /* HAVE_CDIO_CDIO_H || __linux__ */


#if !defined(__OpenBSD__)
    NEW_RAM_LABEL('o', char ram_buffer[VLA], ram_buffer, 4, FMT_RAM2);
#endif /* !__OpenBSD__ */


#if defined(__FreeBSD__) || defined(__OpenBSD__)
    NEW_SWAPP_LABEL('h', char swapp_total[VLA], swapp_total, 1, FMT_SSD2);

    NEW_SWAPP_LABEL('H', char swapp_avail[VLA], swapp_avail, 2, FMT_SSD2);

    NEW_SWAPP_LABEL('Z', char swapp_used[VLA], swapp_used, 3, FMT_SSD2);

    NEW_SWAPP_LABEL('F', char swapp_perc[VLA], swapp_perc, 4, FMT_SSD2);

    NEW_NET_LABEL('j', char nic_info[VLA], nic_info, 7, FMT_PINK);

    NEW_NET_LABEL(WIFINAME, char wifiname[VLA], wifiname, 11, FMT_PINK);
#endif /* __FreeBSD__ || __OpenBSD__ */


#if defined(__linux__)
    NEW_NET_LABEL('j', char nic_info[VLA], nic_info, 10, FMT_PINK);

    NEW_NET_LABEL('h', char wifiname[VLA], wifiname, 11, FMT_PINK);

    NEW_ARG_LABEL('F', char ssd_model[VLA], ssd_model, FMT_PINK);

    NEW_NET_LABEL(NICDRV, char nic_drv[VLA], nic_drv, 8, FMT_PINK);

    NEW_NET_LABEL('H', char nic_ver[VLA], nic_ver, 9, FMT_PINK);

    NEW_ARG_LABEL('G', char nic_info[VLA], nic_info, FMT_PINK);

    NEW_NET_LABEL('e', char link_speed[VLA], link_speed, 7, FMT_PINK);

    NEW_RAM_LABEL(RAMUSED, char ram_used[VLA], ram_used, 6, FMT_RAM2);
#endif /* __linux__ */


    case 'V':
#if defined(HAVE_ALSA_ASOUNDLIB_H) || defined(HAVE_SYS_SOUNDCARD_H) || \
    defined(HAVE_SOUNDCARD_H)
      {
        char volume[VLA];
        GET_N_FMT(volume, arguments->all, FMT_VOL, volume);
      }
      break;
#else
      FPRINTF("%s\n", "pinkybar 1.00.00: recompile the program --with-alsa or --with-oss");
      return ARGP_KEY_ERROR;
#endif /* HAVE_ALSA_ASOUNDLIB_H || HAVE_SYS_SOUNDCARD_H || HAVE_SOUNDCARD_H */

    case 'C':
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
      {
        char cpu_clock_speed[VLA];
        GET_N_FMT(cpu_clock_speed, arguments->all, FMT_CPUSPEED, cpu_clock_speed);
      }
      break;
#else
      FPRINTF("%s\n", "This option is not supported "
                "by your CPU architecture");
      return ARGP_KEY_ERROR;
#endif /* __i386__ || __i686__ || __x86_64__ */

    case 'I':
#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
      {
        char cpu_info[VLA];
        GET_N_FMT(cpu_info, arguments->all, FMT_CPUSPEED, cpu_info);
      }
      break;
#else
      FPRINTF("%s\n", "This option is not supported "
                "by your CPU architecture");
      return ARGP_KEY_ERROR;
#endif /* __i386__ || __i686__ || __x86_64__ */

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


void
parse_opts(int argc, char *argv[], char *combined) {
  struct arguments arguments = {
    .all = combined
  };
  argp_parse(&arg_parser, argc, argv, ARGP_IN_ORDER, NULL, &arguments);
}


void
parse_konf(char *combined, const char *user_config) {
  FILE *fp = NULL, *fp2 = NULL;
  char *ptr = NULL;
  char *ello[] = { (char *)PACKAGE_STRING, NULL };
  char buf[VLA], conf[VLA], temp[VLA], cmd[VLA], output[VLA];
  const char *const home = getenv("HOME") ? getenv("HOME") : "empty";
  struct arguments arguments = {
    .all = combined
  };

  if (NULL == user_config) {
    snprintf(conf, VLA-1, "%s%s", home, "/.pinky");
  }
  else {
    snprintf(conf, VLA-1, "%s", user_config);
  }
  if (NULL == (fp = fopen(conf, "r"))) {
    exit_with_err(ERR,
      mk_str("%s %s", conf, "doesn't exist or $HOME is unset"));
  }

  while (NULL != (fgets(buf, VLA-1, fp))) {
    if (EOF == (sscanf(buf, "%[^\n]", temp))) {
      CLOSE_FP(fp);
      exit_with_err(ERR, "Reached EOF.");
    }
    ptr = temp;
    while (0 != (isspace((unsigned char) *ptr))) {
      ptr++;
    }
    if ('-' == *ptr && '-' == *(ptr+1)) {
      if ('s' == *(ptr+2) && 'e' == *(ptr+4)) {
        if (EOF == (sscanf(ptr, "%*s %[^\n]", cmd))) {
          CLOSE_FP(fp);
          exit_with_err(ERR, "The shell requires argument, e.g: --shell echo 'hi'.");
        }
        if (NULL == (fp2 = popen(cmd, "r"))) {
          continue;
        }
        CHECK_FSCANF(fp2, "%[^\n]", output);
        GLUE(arguments.all, FMT_PINK, output);
        if (-1 == (pclose(fp2))) {
          exit_with_err(CANNOT_CLOSE, "popen()");
        }
        continue;
      }
    }
    if ('#' == *ptr || '/' == *ptr || ';' == *ptr || 
        '*' == *ptr || '\0' == *(ptr+1) || '\0' == *ptr) {
      continue;
    }
    ello[1] = ptr;
    argp_parse(&arg_parser, 2, ello, ARGP_IN_ORDER, NULL, &arguments);
    temp[0] = '\0';
  }
  CLOSE_FP(fp);
}
