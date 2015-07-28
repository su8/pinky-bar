/*
   Copyright 07/06/2015 Aaron Caffrey https://github.com/wifiextender

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
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <glob.h>

#include <X11/Xlib.h>
#include <alsa/asoundlib.h>

#include "functions.h"

void get_temp(char *, char *);
void get_temp(char *str1, char *str2)
{
    uintmax_t temp;

    FILE *fp = fopen(str1, "r");
    if (NULL == fp)
        exit(EXIT_FAILURE);

    fscanf(fp, FMT_UINT, &temp);
    fclose(fp);

    temp /= (uintmax_t)1000;

    snprintf(str2, VLA, FMT_UINT, temp);
}

void get_voltage(char *str1)
{
    float voltage[4];
    FILE *fp;
    uint_fast16_t x = 0;

    char *voltage_files[] =
    {
        HWMON_DIR"in0_input",
        HWMON_DIR"in1_input",
        HWMON_DIR"in2_input",
        HWMON_DIR"in3_input"
    };

    for (x = 0; x < 4; x++)
    {
        if(!(fp = fopen(voltage_files[x], "r")))
            exit(EXIT_FAILURE);

        fscanf(fp, "%f", &voltage[x]);
        fclose(fp);

        voltage[x] /= (float)1000.0;
    }

    snprintf(str1, VLA, "%.2f %.2f %.2f %.2f",
            voltage[0], voltage[1], voltage[2], voltage[3]);
}

void get_mobo(char *str1, char *str2)
{
    char vendor[VLA], name[VLA];

    FILE *fp = fopen(MOBO_VENDOR, "r");
    if (NULL == fp)
        exit(EXIT_FAILURE);

    /* use %[^\n] to get the whole line */
    fscanf(fp, "%s", vendor);
    fclose(fp);

    if (!(fp = fopen(MOBO_NAME, "r")))
        exit(EXIT_FAILURE);

    /* use %[^\n] to get the whole line */
    fscanf(fp, "%s", name);
    fclose(fp);

    get_temp(MOBO_TEMP_FILE, str2);

    snprintf(str1, VLA*2, "%s %s", vendor, name);
}

void get_cpu(char *str1, char *str2)
{
    static uintmax_t previous_total = 0, previous_idle = 0;
    uintmax_t x, percent, diff_total, diff_idle, cpu_active[10];
    uintmax_t total = 0;

    memset(cpu_active, 0, sizeof(cpu_active));

    FILE *fstat = fopen("/proc/stat", "r");
    if (NULL == fstat)
        exit(EXIT_FAILURE);

    /* Some kernels will produce 7, 8 and 9 columns
     * We rely on 10, refer to `man proc' for more details */
    if (fscanf(fstat, "%*s " FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT,
        &cpu_active[0], &cpu_active[1], &cpu_active[2], &cpu_active[3],
        &cpu_active[4], &cpu_active[5], &cpu_active[6], &cpu_active[7],
        &cpu_active[8], &cpu_active[9]) == EOF)
    {
            fclose(fstat);
            exit(EXIT_FAILURE);
    }

    fclose(fstat);

    for (x = 0; x < 10; x++)
        total += cpu_active[x];

    diff_total     = total - previous_total;
    diff_idle      = cpu_active[3] - previous_idle;

    previous_total = total;
    previous_idle  = cpu_active[3];

    percent        = (1000 * (diff_total - diff_idle) / diff_total + 5) / 10;

    get_temp(CPU_TEMP_FILE, str2);

    FILL_ARR(str1, percent);
}

void get_ram(char *str1)
{
    uintmax_t used = 0, total = 0, percent = 0;

    struct sysinfo mem;
    sysinfo(&mem);

    total   = (uintmax_t) mem.totalram / MB;
    used    = (uintmax_t) (mem.totalram - mem.freeram -
                     mem.bufferram - mem.sharedram) / MB;
    percent = (used * 100) / total;

    FILL_ARR(str1, percent);
}


void get_ssd(char *str1)
{
    uintmax_t percent = 0;

    struct statvfs ssd;
    statvfs(getenv("HOME"), &ssd);

    percent = ((ssd.f_blocks - ssd.f_bfree) * ssd.f_bsize) / GB;

    FILL_ARR(str1, percent);
}


/* Source (my improved screenfetch-c fork):
 * https://github.com/wifiextender/screenfetch-c/blob/master/src/plat/linux/detect.c */
static uint_fast16_t glob_packages(char *);

static uint_fast16_t glob_packages(char *str1)
{
    uint_fast16_t packs_num = 0;
    glob_t gl;

    if (!(glob(str1, GLOB_NOSORT, NULL, &gl)))
        packs_num = gl.gl_pathc;

    else
        exit(EXIT_FAILURE);

    globfree(&gl);

    return packs_num;
}

void get_packs(char *str1)
{
    FILE *pkgs_file;
    uint_fast16_t packages = 0;

    if (STREQ(str1, "archlinux")
        || STREQ(str1, "parabola")
        || STREQ(str1, "chakra") || STREQ(str1, "manjaro"))

        packages = glob_packages("/var/lib/pacman/local/*");

    else if (STREQ(str1, "frugalware"))
    {
        pkgs_file = popen("pacman-g2 -Q 2> /dev/null | wc -l", "r");
        fscanf(pkgs_file, "%"SCNuFAST16, &packages);
        pclose(pkgs_file);
    }

    else if (STREQ(str1, "ubuntu") || STREQ(str1, "lubuntu")
            || STREQ(str1, "xubuntu") || STREQ(str1, "linuxmint")
            || STREQ(str1, "solusos") || STREQ(str1, "debian")
            || STREQ(str1, "lmde") || STREQ(str1, "crunchbang")
            || STREQ(str1, "peppermint")
            || STREQ(str1, "linuxdeepin")	|| STREQ(str1, "trisquel")
            || STREQ(str1, "elementary")
            || STREQ(str1, "backtrack")
            || STREQ(str1, "kali"))
        packages = glob_packages("/var/lib/dpkg/info/*.list");

    else if (STREQ(str1, "slackware"))
        packages = glob_packages("/var/log/packages/*");

    else if (STREQ(str1, "gentoo") || STREQ(str1, "sabayon")
            || STREQ(str1, "funtoo"))
        packages = glob_packages("/var/db/pkg/*/*");

    else if (STREQ(str1, "fuduntu") || STREQ(str1, "fedora")
            || STREQ(str1, "opensuse")
            || STREQ(str1, "rhel")
            || STREQ(str1, "mandriva") || STREQ(str1, "mandrake")
            || STREQ(str1, "mageia") || STREQ(str1, "viperr"))
    {
        pkgs_file = popen("rpm -qa 2> /dev/null | wc -l", "r");
        fscanf(pkgs_file, "%"SCNuFAST16, &packages);
        pclose(pkgs_file);
    }

    else if (STREQ(str1, "angstrom"))
    {
        pkgs_file = popen("opkg list-installed 2> /dev/null | wc -l", "r");
        fscanf(pkgs_file, "%"SCNuFAST16, &packages);
        pclose(pkgs_file);
    }

    else
        exit(EXIT_FAILURE);

    snprintf(str1, VLA, "%"PRIuFAST16, packages);
}


void get_kernel(char *str1)
{
    struct utsname KerneL;
    uname(&KerneL);

    snprintf(str1, VLA, "%s %s", KerneL.sysname, KerneL.release);
}


void get_time(char *str1)
{
    char time_str[VLA];
    time_t t = time(NULL);

    strftime(time_str, VLA, "%I:%M %p", localtime(&t));

    snprintf(str1, VLA, "%s", time_str);
}


void get_volume(char *str1)
{
    snd_mixer_t *handle;
    snd_mixer_elem_t *elem;
    snd_mixer_selem_id_t *s_elem;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, "default");
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);
    snd_mixer_selem_id_malloc(&s_elem);
    snd_mixer_selem_id_set_name(s_elem, "Master");

    elem = snd_mixer_find_selem(handle, s_elem);

    if (NULL == elem)
    {
        snd_mixer_selem_id_free(s_elem);
        snd_mixer_close(handle);

        exit(EXIT_FAILURE);
    }

    long int vol, max, min, percent;

    snd_mixer_handle_events(handle);
    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_get_playback_volume(elem, 0, &vol);

    percent = (vol * 100) / max;

    snd_mixer_selem_id_free(s_elem);
    snd_mixer_close(handle);

    snprintf(str1, VLA, "%ld", percent);
}


void set_status(const char *str1)
{
    Display *display = XOpenDisplay(NULL);

    if (display)
    {
        XStoreName(display, DefaultRootWindow(display), str1);
        XSync(display, 0);

        XCloseDisplay(display);
    }

    else
        exit(EXIT_FAILURE);
}
