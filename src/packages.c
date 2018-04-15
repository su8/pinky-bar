/*
   04/13/2018

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

#include "config.h" /* Auto-generated */

#if defined(__linux__)
#include <glob.h>
#endif /* __linux__ */

#include "include/headers.h"
#include "prototypes/packages.h"

#if defined(__linux__)
static uint_fast16_t glob_packages(const char *);
/* Source (my improved screenfetch-c fork):
 * https://github.com/wifiextender/screenfetch-c/blob/master/src/plat/linux/detect.c */
static uint_fast16_t 
glob_packages(const char *str1) {
  uint_fast16_t packs_num = 0;
  glob_t gl;

  if (0 == (glob(str1, GLOB_NOSORT, NULL, &gl))) {
    packs_num = gl.gl_pathc;
  } else {
    exit_with_err("Could not traverse", str1);
  }
  globfree(&gl);

  return packs_num;
}
#endif /* __linux__ */


void 
get_packs(char *str1) {
  uint_fast16_t packages = 0;
  FILE *pkgs_file = NULL;

#if defined(ARCHLINUX)
  packages = glob_packages("/var/lib/pacman/local/*");

#elif defined(FRUGALWARE)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "pacman-g2 -Q 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(DEBIAN)
  packages = glob_packages("/var/lib/dpkg/info/*.list");

#elif defined(SLACKWARE)
  packages = glob_packages("/var/log/packages/*");

#elif defined(GENTOO)
  packages = glob_packages("/var/db/pkg/*/*");

#elif defined(DRAGORA)
  packages = glob_packages("/var/db/pkg/*");

#elif defined(GUIXSD)
  packages = glob_packages("/guix/store/*");

#elif defined(RHEL)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "rpm -qa 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(ANGSTROM)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "opkg list-installed 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(VOIDLINUX)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "xbps-query -l 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(CRUX)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "pkginfo -i 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(ALPINELINUX)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "apk info 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(SLITAZ)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "tazpkg list 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(TINYCORELINUX)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "tce-status -i 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(NIXOS)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "nix-env -q 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(PALDO)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "upkg-list 2> /dev/null | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(FREEBSD)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "pkg info | wc -l", &packages);
#pragma GCC diagnostic pop

#elif defined(OPENBSD)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(pkgs_file, "pkg_info | wc -l", &packages);
#pragma GCC diagnostic pop


#endif

  FILL_ARR(str1, UFINT, packages);
}


void 
get_updates(char *str1) {
#if defined(ARCHLINUX) || defined(GENTOO) || \
  defined(RHEL) || defined(FREEBSD) || defined(DEBIAN)
  uint_fast16_t updates = 0;
  FILE *updates_file = NULL;

#if defined(ARCHLINUX)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(updates_file, "pacman -Qu 2> /dev/null | wc -l", &updates);
#pragma GCC diagnostic pop

#elif defined(GENTOO)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(updates_file, "eix -cu --world 2> /dev/null | wc -l", &updates);
#pragma GCC diagnostic pop
  updates = (0 == updates ? 0 : updates - 1);

#elif defined(RHEL)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(updates_file, "dnf check-update 2> /dev/null | wc -l", &updates);
#pragma GCC diagnostic pop

#elif defined(FREEBSD)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(updates_file, "pkg version -vIL= | wc -l", &updates);
#pragma GCC diagnostic pop

#elif defined(DEBIAN)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  CHECK_POPEN(updates_file, "apt list --upgradable | wc -l", &updates);
#pragma GCC diagnostic pop
  updates = (0 == updates ? 0 : updates - 1);

#endif /* ARCHLINUX */

  FILL_ARR(str1, "%s "UFINT, "Updates", updates);
  
#else
  FILL_STR_ARR(1, str1, "Updates 0");
#endif /* ARCHLINUX */
}
