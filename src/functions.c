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
 * Do not add any -Wno cflags just to mute the compilers snafus
 * */

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <glob.h>
#include <unistd.h>
/* #include <arpa/inet.h> */
/* #include <netdb.h> */
#include <sys/socket.h>
#include <ifaddrs.h>
#include <linux/if_link.h>

/* Auto-generated */
#include "config.h"

#if defined (HAVE_X11_XLIB_H)
#include <X11/Xlib.h>
#endif

#if defined (HAVE_MPD_CLIENT_H)
#include <mpd/client.h>
#endif

#if defined (HAVE_ALSA_ASOUNDLIB_H)
#include <alsa/asoundlib.h>
#endif

#include "main_constants.h"
#include "functions_constants.h"
#include "functions_prototypes.h"

static void get_temp(const char *, char *);
static uint_fast16_t glob_packages(const char *);
static void exit_with_err(const char *, const char *);

static void
exit_with_err(const char *str1, const char *str2) {
  printf("%s %s\n", str1, str2);
  exit(EXIT_FAILURE);
}


static void
get_temp(const char *str1, char *str2) {
  uintmax_t temp;

  FILE *fp = fopen(str1, "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, str1);
  }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(fp, FMT_UINT, &temp);
#pragma GCC diagnostic pop
  fclose(fp);

  temp /= (uintmax_t)1000;

  FILL_UINT_ARR(str2, temp);
}


void 
get_cpu(char *str1) {
  static uintmax_t previous_total = 0, previous_idle = 0;
  uintmax_t x, percent, diff_total, diff_idle, cpu_active[10];
  uintmax_t total = 0;

  memset(cpu_active, 0, sizeof(cpu_active));

  FILE *fp = fopen("/proc/stat", "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, "/proc/stat");
  }

  /* Some kernels will produce 7, 8 and 9 columns
   * We rely on 10, refer to `man proc' for more details */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  if (fscanf(fp, "%*s " FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT,
    &cpu_active[0], &cpu_active[1], &cpu_active[2], &cpu_active[3],
    &cpu_active[4], &cpu_active[5], &cpu_active[6], &cpu_active[7],
    &cpu_active[8], &cpu_active[9]) == EOF) {
      fclose(fp);
      exit_with_err(ERR,"Upgrade to a newer kernel");
  }
#pragma GCC diagnostic pop
  fclose(fp);

  for (x = 0; x < 10; x++)
    total += cpu_active[x];

  diff_total     = total - previous_total;
  diff_idle      = cpu_active[3] - previous_idle;

  previous_total = total;
  previous_idle  = cpu_active[3];

  percent        = (uintmax_t)sysconf(_SC_CLK_TCK) *
                    (diff_total - diff_idle) / diff_total;

  FILL_UINT_ARR(str1, percent);
}


void
get_cores_load(char *str1) {
  static uintmax_t previous_total[MAX_CORES], previous_idle[MAX_CORES];
  static uintmax_t test_flag = 0;
  uintmax_t x = 0, y = 0, z = 0;
  uintmax_t percent[MAX_CORES], diff_total[MAX_CORES], core_active[MAX_CORES][10];
  uintmax_t diff_idle[MAX_CORES], total[MAX_CORES];
  char buf[VLA], temp[VLA];
  char *all = temp;

  memset(percent, 0, sizeof(percent));
  memset(diff_total, 0, sizeof(diff_total));
  memset(diff_idle, 0, sizeof(diff_idle));
  memset(total, 0, sizeof(total));
  memset(core_active, 0, sizeof(core_active));

  if (0 == test_flag) {
    memset(previous_idle, 0, sizeof(previous_idle));
    memset(previous_total, 0, sizeof(previous_total));
  }

  FILE *fp = fopen("/proc/stat", "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, "/proc/stat");
  }

  if (NULL == fgets(buf, VLA, fp)) {
    fclose(fp);
    exit_with_err(ERR, "reached /proc/stat EOF");
  }

  for (x = 0; x < MAX_CORES; x++) {
    if (NULL == fgets(buf, VLA, fp)) {
      fclose(fp);
      exit_with_err(ERR, "reached /proc/stat EOF");
    }

    if (buf[0] != 'c' && buf[1] != 'p' && buf[2] != 'u') {
      break;
    }

    if (sscanf(buf, "%*s " FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT,
      &core_active[x][0], &core_active[x][1], &core_active[x][2], &core_active[x][3],
      &core_active[x][4], &core_active[x][5], &core_active[x][6], &core_active[x][7],
      &core_active[x][8], &core_active[x][9]) == EOF) {
        fclose(fp);
        exit_with_err(ERR,"Upgrade to a newer kernel");
    }
  }
  fclose(fp);

  z = x;
  for (x = 0; x < z; x++) {
    for (y = 0; y < 10; y++) {
      total[x] += core_active[x][y];
    }

    diff_total[x]     = total[x] - previous_total[x];
    diff_idle[x]      = core_active[x][3] - previous_idle[x];

    previous_total[x] = total[x];
    previous_idle[x]  = core_active[x][3];

    percent[x]        = (uintmax_t)sysconf(_SC_CLK_TCK) *
                      (diff_total[x] - diff_idle[x]) / diff_total[x];

    GLUE2(all, FMT_UINT"%% ", percent[x]);
  }

  test_flag = 1;

  FILL_STR_ARR(1, str1, temp);
}


void
get_cpu_temp(char *str1) {
  get_temp(CPU_TEMP_FILE, str1);
}


void 
get_ram(char *str1) {
  uintmax_t used = 0, total = 0, percent = 0;
  struct sysinfo mem;

  if (-1 == (sysinfo(&mem))) {
    exit_with_err(ERR, "sysinfo() failed");
  }

  total   = (uintmax_t) mem.totalram / MB;
  used    = (uintmax_t) (mem.totalram - mem.freeram -
                   mem.bufferram - mem.sharedram) / MB;
  percent = (used * 100) / total;

  FILL_UINT_ARR(str1, percent);
}


void 
get_ssd(char *str1) {
  uintmax_t percent = 0;
  struct statvfs ssd;

  if (-1 == (statvfs(getenv("HOME"), &ssd))) {
    exit_with_err(ERR, "statvfs() failed");
  }
  percent = ((ssd.f_blocks - ssd.f_bfree) * ssd.f_bsize) / GB;

  FILL_UINT_ARR(str1, percent);
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
get_kernel(char *str1) {
  struct utsname KerneL;
  if (-1 == (uname(&KerneL))) {
    exit_with_err(ERR, "uname() failed");
  }
  FILL_STR_ARR(2, str1, KerneL.sysname, KerneL.release);
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
  char vendor[VLA], name[VLA];

  FILE *fp = fopen(MOBO_VENDOR, "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, MOBO_VENDOR);
  }
  /* use %[^\n] to get the whole line */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(fp, "%s", vendor);
#pragma GCC diagnostic pop
  fclose(fp);

  if (NULL == (fp = fopen(MOBO_NAME, "r"))) {
    exit_with_err(CANNOT_OPEN, MOBO_NAME);
  }
  /* use %[^\n] to get the whole line */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(fp, "%s", name);
#pragma GCC diagnostic pop
  fclose(fp);

  FILL_STR_ARR(2, str1, vendor, name);
}


void
get_mobo_temp(char *str1) {
  get_temp(MOBO_TEMP_FILE, str1);
}


#if defined (HAVE_ALSA_ASOUNDLIB_H)
/* http://www.alsa-project.org/alsa-doc/alsa-lib/group___mixer.html 
 * http://www.alsa-project.org/alsa-doc/alsa-lib/group___simple_mixer.html 
 * for the return values */
void 
get_volume(char *str1) {
  snd_mixer_t *handle = NULL;
  snd_mixer_elem_t *elem = NULL;
  snd_mixer_selem_id_t *s_elem = NULL;
  long int vol, max, min, percent;

  if (0 < (snd_mixer_open(&handle, 0))) {
    exit_with_err(ERR, "alsa failed");
  }

  if (0 < (snd_mixer_attach(handle, "default"))) {
    goto error;
  }

  if (0 < (snd_mixer_selem_register(handle, NULL, NULL))) {
    goto error;
  }

  if (0 < (snd_mixer_load(handle))) {
    goto error;
  }

  snd_mixer_selem_id_malloc(&s_elem);
  if (NULL == s_elem) {
    goto error;
  }

  snd_mixer_selem_id_set_name(s_elem, "Master");
  if (NULL == (elem = snd_mixer_find_selem(handle, s_elem))) {
    goto error;
  }

  if (0 < (snd_mixer_selem_get_playback_volume(elem, 0, &vol))) {
    goto error;
  }
  snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

  percent = (vol * 100) / max;

  snd_mixer_selem_id_free(s_elem);
  snd_mixer_close(handle);

  FILL_ARR(str1, "%ld", percent);
  return;

error:
  if (NULL != s_elem) {
    snd_mixer_selem_id_free(s_elem);
    s_elem = NULL;
  }
  if (NULL != handle) {
    snd_mixer_close(handle);
    handle = NULL;
  }
  exit_with_err(ERR, "alsa failed");
}
#endif


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


#if defined (HAVE_MPD_CLIENT_H)
void
get_song(char *str1) {
  struct mpd_connection *conn = NULL;
  struct mpd_song *song;

  if (NULL == (conn = mpd_connection_new(NULL, 0, 0))) {
    return;
  }
  if (!(mpd_send_command(conn, "currentsong", NULL)) ||
      0 != (mpd_connection_get_error(conn))) {
    goto error;
  }
  if (NULL == (song = mpd_recv_song(conn))) {
    goto error;
  }
  mpd_connection_free(conn);

  FILL_STR_ARR(1, str1, mpd_song_get_uri(song));
  return;

error:
  if (NULL != conn) {
    mpd_connection_free(conn);
    conn = NULL;
  }
  return;
}
#endif


/* Thanks to http://www.matisse.net/bitcalc/?source=print */
void
get_net(char *str1, char *str2, bool measure_speed) {
  struct ifaddrs *ifaddr, *ifa;
  struct rtnl_link_stats *stats;
  static uintmax_t prev_recv = 0, prev_sent = 0;
  uintmax_t cur_recv, cur_sent;

  if (-1 == getifaddrs(&ifaddr)) {
    exit_with_err(ERR, "getifaddrs() failed");
  }

  for (ifa = ifaddr; NULL != ifa; ifa = ifa->ifa_next) {
    if (NULL == ifa->ifa_addr) {
      continue;
    }
    if (ifa->ifa_addr->sa_family == AF_PACKET &&
        NULL != ifa->ifa_data) {
      if (!(strcmp(str2, ifa->ifa_name))) {
        stats = ifa->ifa_data;

        if (measure_speed) {
          cur_recv = (uintmax_t)stats->rx_bytes - prev_recv;
          cur_sent = (uintmax_t)stats->tx_bytes - prev_sent;

          FILL_ARR(str1, "Down " FMT_UINT " KB, Up " FMT_UINT " KB",
            (cur_recv / KB), (cur_sent / KB));

          prev_recv = cur_recv;
          prev_sent = cur_sent;
        } else {
  
          FILL_ARR(str1, "Down " FMT_UINT " MB, Up " FMT_UINT " MB",
            ((uintmax_t)stats->rx_bytes / MB),
            ((uintmax_t)stats->tx_bytes / MB));
        }
        break;
      }
    }
  }
  freeifaddrs(ifaddr);
}


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


/*  Taken from the gcc documentation
 *  https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html
 *
 *  other useful resources:
 *  http://www.felixcloutier.com/x86/RDTSC.html 
 *  http://ref.x86asm.net/coder32.html#x0F31 
*/

/* Not going to test for i486 and i586 */
#if defined(__i386__) || defined(__i686__)
static __inline__ uintmax_t 
rdtsc(void) {
  uintmax_t x;
  __asm__ __volatile__ (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}

void
get_cpu_clock_speed(char *str1) {
  uintmax_t x, y, z[2];

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec start = {0}, stop = {0}, tc = {0};
#pragma GCC diagnostic pop

  tc.tv_nsec = sysconf(_SC_CLK_TCK) * 1000000L;

  x = rdtsc();
  clock_gettime(CLOCK_MONOTONIC, &start);
  z[0] = (uintmax_t)(start.tv_nsec - start.tv_sec);

  if (-1 == (nanosleep(&tc, NULL))) {
    exit_with_err(ERR, "nanosleep() failed");
  }

  y = rdtsc();
  clock_gettime(CLOCK_MONOTONIC, &stop);
  z[1] = (uintmax_t)(stop.tv_nsec - stop.tv_sec);

  FILL_ARR(str1, FMT_UINT " MHz",
    (1000 * (y - x) / (z[1] - z[0])));
}


#elif defined(__x86_64__)
static __inline__ uintmax_t 
rdtsc(void) {
  unsigned int tickhi, ticklo;
  __asm__ __volatile__ ("rdtsc" : "=a"(ticklo), "=d"(tickhi));
  return (((uintmax_t)tickhi << 32) | (uintmax_t)ticklo);
}

void
get_cpu_clock_speed(char *str1) {
  uintmax_t x, z;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  tc.tv_nsec = sysconf(_SC_CLK_TCK) * 1000000L;

  x = rdtsc();
  if (-1 == (nanosleep(&tc, NULL))) {
    exit_with_err(ERR, "nanosleep() failed");
  }
  z = rdtsc();

  FILL_ARR(str1, FMT_UINT " MHz", ((z - x) / 100000));
}
#endif


#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
void
get_cpu_info(char *str1) {
  char buffer[VLA], vend_id[13];
  char *all = buffer;
  uintmax_t vend = 0, num = 0, vend_str = 0, x = 0, z = 0;
  uintmax_t eax = 0, ecx = 0, edx = 0, ebx = 0, eax_old = 0;

  CPU_VENDOR(0, vend);
  if (0 == vend) {
    FILL_STR_ARR(1, str1, "Null");
    return;
  }
  CPU_FEATURE(1, eax_old);

  switch(vend) {
    case AmD:
      num = 0;
      break;

    case InteL:
      num = 1;
      break;
  }

  /* Dont have intel cpu to verify the following code
     It works fine on both of my primary amd systems.
     I'm also aware of linking against assembly object file,
     wanted to learn more assembly by back porting it to C */
  if (0 == num) {
    CPU_FEATURE(0x80000000, vend_str);                /* movl $0x80000000, %eax */
    if (0 != vend_str) {

      for (x = 0x80000002; x <= 0x80000004; x++) {    /* movl $0x80000002, %esi */
        CPU_STR2(x, eax, ebx, ecx, edx);              /* cmpl $0x80000004, %eax */
        char vend_chars[17]; /* 12 + 4 */

        for (z = 0; z < 4; z++) {
          vend_chars[z] = (char)(eax >> (z * 8));     /* movl %eax */
          vend_chars[z+4] = (char)(ebx >> (z * 8));   /* movl %ebx, 4 */
          vend_chars[z+8] = (char)(ecx >> (z * 8));   /* movl %ecx, 8 */
          vend_chars[z+12] = (char)(edx >> (z * 8));  /* movl %edx, 12 */
        }
        vend_chars[16] = '\0';
        GLUE2(all, "%s", vend_chars);
      }

      CPU_ID_STR(0, ebx, ecx, edx);                   /* mov $0, %eax */
      for (z = 0; z < 4; z++) {
        vend_id[z] = (char)(ebx >> (z * 8));          /* movl %ebx, 0 */
        vend_id[z+4] = (char)(edx >> (z * 8));        /* movl %edx, 4 */
        vend_id[z+8] = (char)(ecx >> (z * 8));        /* movl %ecx, 8 */
      }
      vend_id[12] = '\0';

      FILL_ARR(str1, "%s ID %s Stepping " FMT_UINT " Family " FMT_UINT " Model " FMT_UINT,
        buffer, vend_id, BIT_SHIFT(eax_old),
        BIT_SHIFT(eax_old >> 8), BIT_SHIFT(eax_old >> 4));
      return;
    }
  }

  FILL_ARR(str1, "%s Stepping " FMT_UINT " Family " FMT_UINT " Model " FMT_UINT,
    (0 == num ? "AMD" : "Intel"), BIT_SHIFT(eax_old),
    BIT_SHIFT(eax_old >> 8), BIT_SHIFT(eax_old >> 4));
}
#endif
