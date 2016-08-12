dnl Copyright 07/06/2015, 08/03/2016
dnl Aaron Caffrey https://github.com/wifiextender

dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
dnl MA 02110-1301, USA.


dnl Internal function to let the user know
dnl when some of the compile tests is about to begin
AC_DEFUN([NOTIFY],[
  AC_MSG_NOTICE([performing $1 compile test.])
])


dnl TEST_SOME_FUNCS() function in configure.ac
dnl
dnl The tests are simple enough, just to
dnl catch misbehaving compiler and/or
dnl installed C libraries.
AC_DEFUN([TEST_SOME_FUNCS],[

  NOTIFY([strftime])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <time.h>
      int main(void) {
        char test[200];
        time_t t = time(NULL);
        strftime(test, 190, "%I:%M %p", localtime(&t));
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([strftime])
    ]
  )


  NOTIFY([statvfs])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <stdlib.h>
      #include <sys/statvfs.h>
      int main(void) {
        struct statvfs ssd;
        statvfs(getenv("HOME"), &ssd);
        ssd.f_blocks;
        ssd.f_bsize;
        ssd.f_bavail;
        ssd.f_bfree;
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([statvfs storage])
    ]
  )


  NOTIFY([uname])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <sys/utsname.h>
      int main(void) {
        struct utsname KerneL;
        uname(&KerneL);
        KerneL.sysname;
        KerneL.nodename;
        KerneL.release;
        KerneL.version;
        KerneL.machine;
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([uname Kernel])
    ]
  )


  NOTIFY([sysinfo])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <sys/sysinfo.h>
      int main(void) {
        struct sysinfo inf;
        sysinfo(&inf);
        inf.totalram;
        inf.freeram;
        inf.sharedram;
        inf.bufferram;
        inf.loads[0];
        inf.loads[1];
        inf.loads[2];
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([sysinfo RAM and average load])
    ]
  )


  NOTIFY([openNreadFile])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <stdio.h>
      int main(void) {
        FILE *test = fopen("/proc/stat", "r");
        if (NULL == test) {
          return 0;
        }
        fclose(test);
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([openNreadFile])
    ]
  )


  NOTIFY([memset])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <string.h>
      #include <stdint.h>
      int main(void) {
        uintmax_t test[5];
        memset(test, 0, sizeof(test));
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([memset])
    ]
  )


  NOTIFY([glob])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <glob.h>
      int main(void) {
        glob_t gl;
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([glob])
    ]
  )


  NOTIFY([sysconf])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <time.h>
      #include <unistd.h>
      int main(void) {
        if (-1 == (sysconf(_SC_CLK_TCK))) {
          return 0;
        }
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([sysconf])
    ]
  )


  NOTIFY([snprintf])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <stdio.h>
      int main(void) {
        char test[10];
        snprintf(test, 8, "%s", "hi");
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([snprintf])
    ]
  )


  NOTIFY([getopt])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <getopt.h>
      #define NULL ((void *)0)
      int main(void) {
        const struct option options[] = {
          { "mpd",          no_argument,       NULL, 'M' },
          { "statio",       required_argument, NULL, 'S' },
          { NULL,           0,                 NULL,  0  }
        };

        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([getopt])
    ]
  )


  NOTIFY([timespec])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <time.h>
      int main(void) {
        struct timespec tc = {0};
        tc.tv_nsec = 85000L;
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([timespec])
    ]
  )


  NOTIFY([popen])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <stdio.h>
      int main(void) {
        char hi[30];
        FILE *test = popen("echo elo", "r");
        fscanf(test, "%s", hi);
        pclose(test);
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([popen])
    ]
  )


  NOTIFY([clock_gettime])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <time.h>
      int main(void) {
        struct timespec tc1 = {0}, tc2 = {0};
        clock_gettime(CLOCK_MONOTONIC, &tc1);
        clock_gettime(CLOCK_BOOTTIME, &tc2);
        return 0;
      }
    ]])
  ],[],[
    COMPILE_FAILED([clock_gettime])
    ]
  )

])
