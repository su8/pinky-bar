/*
   Copyright 07/06/2015, 07/18/2016
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

/* The pragma directives are here
 * to mute the gcc twisted vision,
 * and clangs inabillity to distinguish
 * C from C++
 *
 * https://llvm.org/bugs/show_bug.cgi?id=21689 
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66425
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25509
 *
 * Do not add any -Wno flags just to mute the compilers snafus
 * */

#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <glob.h>

#include "config.h" /* Auto-generated */

#if defined (HAVE_X11_XLIB_H)
#include <X11/Xlib.h>
#endif

#include "include/headers.h"

static uint_fast16_t glob_packages(const char *);

void 
get_ram(char *str1, unsigned char num) {
  uintmax_t used = 0, total = 0;
  struct sysinfo mem;

  if (-1 == (sysinfo(&mem))) {
    FUNC_FAILED("sysinfo()");
  }

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)mem.totalram / MB, "MB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)mem.freeram / MB, "MB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)mem.sharedram / MB, "MB");
      break;
    case 4:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)mem.bufferram / MB, "MB");
      break;
    case 5:
      {
        total   = (uintmax_t) mem.totalram / MB;
        used    = (uintmax_t) (mem.totalram - mem.freeram -
                         mem.bufferram - mem.sharedram) / MB;
        FILL_UINT_ARR(str1, (used * 100) / total);
      }
      break;
  }

}


void 
get_ssd(char *str1, unsigned char num) {
  uintmax_t val = 0;
  struct statvfs ssd;

  if (-1 == (statvfs(getenv("HOME"), &ssd))) {
    FUNC_FAILED("statvfs()");
  }

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)(ssd.f_blocks * ssd.f_bsize) / GB, "GB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)(ssd.f_bfree * ssd.f_bsize) / GB, "GB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)(ssd.f_bavail * ssd.f_bsize) / GB, "GB");
      break;
    case 4:
      {
        val = (uintmax_t)((
          ssd.f_blocks - ssd.f_bfree) * ssd.f_bsize) / GB;
        FILL_UINT_ARR(str1, val);
      }
      break;
  }

}


void
get_ssd_model(char *str1, char *str2) {
  FILE *fp;
  char model[VLA];
  FILL_ARR(model, "%s%s%s", "/sys/block/", str2, "/device/model");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, model, "%[^\n]", model);
#pragma GCC diagnostic pop

  FILL_STR_ARR(1, str1, model);

}


/* Source (my improved screenfetch-c fork):
 * https://github.com/wifiextender/screenfetch-c/blob/master/src/plat/linux/detect.c */
static uint_fast16_t 
glob_packages(const char *str1) {
  uint_fast16_t packs_num = 0;
  glob_t gl;

  if (0 == (glob(str1, GLOB_NOSORT, NULL, &gl)))
    packs_num = gl.gl_pathc;

  else {
    exit_with_err("Could not traverse", str1);
  }

  globfree(&gl);

  return packs_num;
}


/* Let the compiler strip the code
 * instead conditionally checking 
 * each time the program is executed */
void 
get_packs(char *str1) {
  uint_fast16_t packages = 0;

#if DISTRO == ARCHLINUX
  packages = glob_packages("/var/lib/pacman/local/*");

#elif DISTRO == FRUGALWARE
  FILE *pkgs_file = popen("pacman-g2 -Q 2> /dev/null | wc -l", "r");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(pkgs_file, "%"SCNuFAST16, &packages);
#pragma GCC diagnostic pop

  pclose(pkgs_file);

#elif DISTRO == DEBIAN
  packages = glob_packages("/var/lib/dpkg/info/*.list");

#elif DISTRO == SLACKWARE
  packages = glob_packages("/var/log/packages/*");

#elif DISTRO == GENTOO
  packages = glob_packages("/var/db/pkg/*/*");

#elif DISTRO == RHEL
  FILE *pkgs_file = popen("rpm -qa 2> /dev/null | wc -l", "r");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(pkgs_file, "%"SCNuFAST16, &packages);
#pragma GCC diagnostic pop

  pclose(pkgs_file);

#elif DISTRO == ANGSTROM
  FILE *pkgs_file = popen("opkg list-installed 2> /dev/null | wc -l", "r");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(pkgs_file, "%"SCNuFAST16, &packages);
#pragma GCC diagnostic pop

  pclose(pkgs_file);

#endif

  FILL_ARR(str1, "%"PRIuFAST16, packages);
}


void 
get_kernel(char *str1, unsigned char num) {
  struct utsname KerneL;
  if (-1 == (uname(&KerneL))) {
    FUNC_FAILED("uname()");
  }

  switch(num) {
    case 1:
      FILL_STR_ARR(1, str1, KerneL.sysname);
      break;
    case 2:
      FILL_STR_ARR(1, str1, KerneL.nodename);
      break;
    case 3:
      FILL_STR_ARR(1, str1, KerneL.release);
      break;
    case 4:
      FILL_STR_ARR(1, str1, KerneL.version);
      break;
    case 5:
      FILL_STR_ARR(1, str1, KerneL.machine);
      break;
    case 6:
      FILL_STR_ARR(2, str1, KerneL.sysname, KerneL.release);
      break;
  }

}


void
get_loadavg(char *str1) {
  struct sysinfo up;
  if (-1 == (sysinfo(&up))) {
    FUNC_FAILED("sysinfo()");
  }
  FILL_ARR(str1, "%.2f %.2f %.2f",
    (float)up.loads[0] / 65535.0,
    (float)up.loads[1] / 65535.0,
    (float)up.loads[2] / 65535.0);
}


void
get_uptime(char *str1) {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  uintmax_t now = 0;
  if (-1 == (clock_gettime(CLOCK_BOOTTIME, &tc))) {
    FUNC_FAILED("clock_gettime()");
  }

  now = (uintmax_t)tc.tv_sec;
  if ((0 != (now / 86400))) { /* days */
    FILL_ARR(str1, FMT_UINT "d " FMT_UINT "h " FMT_UINT "m",
      (now / 86400),
      ((now / 3600) % 24),
      ((now / 60) % 60));
    return;
  }
  if (59 < (now / 60)) { /* hours */
    FILL_ARR(str1, FMT_UINT "h " FMT_UINT "m",
      ((now / 3600) % 24),
      ((now / 60) % 60));
    return;
  }

  FILL_ARR(str1, FMT_UINT "m", ((now / 60) % 60));
}


void 
get_voltage(char *str1) {
  float voltage[4];
  FILE *fp;
  uint_fast16_t x = 0;

  const char *voltage_files[] = {
    VOLTAGE_FILE("0"),
    VOLTAGE_FILE("1"),
    VOLTAGE_FILE("2"),
    VOLTAGE_FILE("3")
  };

  for (x = 0; x < 4; x++) {
    if (NULL == (fp = fopen(voltage_files[x], "r"))) {
      exit_with_err(CANNOT_OPEN, voltage_files[x]);
    }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    fscanf(fp, "%f", &voltage[x]);
#pragma GCC diagnostic pop
    fclose(fp);

    voltage[x] /= (float)1000.0;
  }
  FILL_ARR(str1, "%.2f %.2f %.2f %.2f",
    voltage[0], voltage[1], voltage[2], voltage[3]);
}


void 
get_fans(char *str1) {
  FILE *fp;
  bool found_fans = true;
  char tempstr[VLA], buffer[VLA];
  char *all_fans = buffer;
  uint_fast16_t x = 0, y = 0, z = 0, rpm[21];

  for (x = 1; x < 20; x++, z++) {
    FILL_ARR(tempstr, FAN_FILE, x);

    if (NULL == (fp = fopen(tempstr, "r")) && x > 1)
      break;
    else if (NULL == fp) { /* no system fans */
      FILL_STR_ARR(1, str1, NOT_FOUND);
      found_fans = false;
      break;
    }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    fscanf(fp, UFINT, &rpm[z]);
#pragma GCC diagnostic pop
    fclose(fp);
  }

  if (found_fans) {
    for (x = 0; x < z; x++) {
      if (0 < rpm[x])
        GLUE2(all_fans, UFINT" ", rpm[x]);
      else
        ++y; /* non-spinning | removed | failed fan */
    }
    FILL_STR_ARR(1, str1, (y != x ? buffer : NOT_FOUND));
  }
}


void 
get_mobo(char *str1) {
  FILE *fp;
  char vendor[VLA], name[VLA];

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, MOBO_VENDOR, "%s", vendor);
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, MOBO_NAME, "%s", name);
#pragma GCC diagnostic pop

  FILL_STR_ARR(2, str1, vendor, name);
}


void
get_mobo_temp(char *str1) {
  get_temp(MOBO_TEMP_FILE, str1);
}


/* The `strftime' man page showed potential bugs */
void 
get_taim(char *str1) {
  char time_str[VLA];
  time_t t;
  struct tm *taim;

  if (-1 == (t = time(NULL)) || 
      NULL == (taim = localtime(&t)) ||
      0 == (strftime(time_str, VLA, "%I:%M %p", taim))) {
    exit_with_err(ERR, "time() or localtime() or strftime() failed");
  }
  FILL_STR_ARR(1, str1, time_str);
}


#if defined (HAVE_X11_XLIB_H)
void 
set_status(const char *str1) {
  Display *display = XOpenDisplay(NULL);

  if (display) {
    XStoreName(display, DefaultRootWindow(display), str1);
    XSync(display, 0);
    XCloseDisplay(display);

  } else {
    exit_with_err(CANNOT_OPEN, "X server");
  }
}
#endif


void 
get_statio(char *str1, char *str2) {
  uintmax_t statio[7];
  char stat_file[VLA];
  FILL_ARR(stat_file, "%s%s%s", "/sys/block/", str2, "/stat");

  memset(statio, 0, sizeof(statio));

  FILE *fp = fopen(stat_file, "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, stat_file);
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  if (fscanf(fp, FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT,
    &statio[0], &statio[1], &statio[2], &statio[3],
    &statio[4], &statio[5], &statio[6]) == EOF) {
      fclose(fp);
      exit_with_err(ERR, "reading the stat file failed");
  }
#pragma GCC diagnostic pop
  fclose(fp);

  FILL_ARR(str1, "Read " FMT_UINT " MB, Written " FMT_UINT " MB",
    BYTES_TO_MB(statio[2]), BYTES_TO_MB(statio[6]));
}


/* Thanks to https://bugzilla.kernel.org/show_bug.cgi?id=83411 */
void
get_battery(char *str1) {
  uintmax_t used = 0, total = 0, percent = 0, num = 0;
  char temp[VLA];
  BATTERY_TOTAL(temp, num);

  FILE *fp = fopen(temp, "r");
  if (NULL == fp) {
    num = 1;
    BATTERY_TOTAL(temp, num);

    if (NULL == (fp = fopen(temp, "r"))) {
      exit_with_err(CANNOT_OPEN, "BAT0 and BAT1");
    }
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(fp, FMT_UINT, &total);
#pragma GCC diagnostic pop
  fclose(fp);

  BATTERY_USED(temp, num);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, temp, FMT_UINT, &used);
#pragma GCC diagnostic pop

  percent = (used * 100) / total;
  FILL_UINT_ARR(str1, percent);
}
