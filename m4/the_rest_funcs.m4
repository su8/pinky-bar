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


dnl TEST_SOME_FUNCS() function in configure.ac
dnl
dnl The tests are simple enough, just to
dnl see whether the compiler will fail to
dnl compile them and show to the user 
dnl which of those tests have failed.
dnl The used library functions should not fail
dnl to compile such simple tests, but you
dnl never know which C library the user might
dnl have installed (musl, uclibc) etc..
AC_DEFUN([TEST_SOME_FUNCS],[

  AC_MSG_NOTICE([performing strftime compile test])
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
    ERR([Failed to compile the strftime test.])
    ]
  )


  AC_MSG_NOTICE([performing statvfs compile test])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <stdlib.h>
      #include <sys/statvfs.h>
      int main(void) {
        struct statvfs ssd;
        statvfs(getenv("HOME"), &ssd);
        return 0;
      }
    ]])
  ],[],[
    ERR([Failed to compile the statvfs storage test.])
    ]
  )


  AC_MSG_NOTICE([performing uname compile test])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <sys/utsname.h>
      int main(void) {
        struct utsname KerneL;
        uname(&KerneL);
        return 0;
      }
    ]])
  ],[],[
    ERR([Failed to compile the uname Kernel test.])
    ]
  )


  AC_MSG_NOTICE([performing sysinfo compile test])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <sys/sysinfo.h>
      int main(void) {
        struct sysinfo mem;
        sysinfo(&mem);
        return 0;
      }
    ]])
  ],[],[
    ERR([Failed to compile the sysinfo RAM test.])
    ]
  )


  AC_MSG_NOTICE([performing openNreadFile compile test])
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
    ERR([Failed to compile the openNreadFile test.])
    ]
  )


  AC_MSG_NOTICE([performing memset compile test])
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
    ERR([Failed to compile the memset test.])
    ]
  )


  AC_MSG_NOTICE([performing glob compile test])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <glob.h>
      int main(void) {
        glob_t gl;
        return 0;
      }
    ]])
  ],[],[
    ERR([Failed to compile the glob test.])
    ]
  )


  AC_MSG_NOTICE([performing getifaddrs compile test])
  AC_COMPILE_IFELSE([
    AC_LANG_SOURCE([[
      #include <ifaddrs.h>
      int main(void) {
        struct ifaddrs *ifaddr;
        if (-1 == getifaddrs(&ifaddr)) {
          return 0;
        }
        freeifaddrs(ifaddr);
        return 0;
      }
    ]])
  ],[],[
    ERR([Failed to compile the getifaddrs test.])
    ]
  )

])
