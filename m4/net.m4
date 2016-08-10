dnl Copyright 08/10/2015
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


dnl TEST_NET() function in configure.ac
dnl
dnl Allow the user to compile the program
dnl without net related functions, thus
dnl decreasing the required dependencies.
dnl
dnl Did not included tests for some of the Net
dnl headers as they fail to compile just by including
dnl them in gcc, but pass the tests in clang. Is there
dnl are any _POSIX_SOURCE m4 alternative to compile a
dnl test case on the fly ?
AC_DEFUN([TEST_NET],[
  WITH_NET=1
  dnl WITH_PCI=1
  dnl PCI_LIBS=""

  AC_ARG_WITH([net],
    AS_HELP_STRING([--with-net],
      [Net funcs]),
    [],
    [with_net=yes]
  )

  AS_IF([test "x$with_net" = "xno"], [
    WITH_NET=0
  ])

  AS_IF([test "x$with_net" = "xyes"], [

    AC_CHECK_HEADERS([    \
      linux/if_link.h     \
      ifaddrs.h           \
      arpa/inet.h         \
      netpacket/packet.h  \
      sys/socket.h        \
      net/if.h            \
      sys/ioctl.h         \
      linux/sockios.h     \
      linux/ethtool.h     \
      netdb.h             \
    ],[],[
      ERR([Missing core header files.])
    ])

    AC_CHECK_FUNCS([ \
      getifaddrs     \
      freeifaddrs    \
      getaddrinfo    \
      freeaddrinfo   \
      socket         \
      ioctl          \
      inet_ntop      \
    ],[],[
      ERR([Missing core library functions.])
    ])

    NOTIFY([getifaddrs])
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
      COMPILE_FAILED([getifaddrs])
      ]
    )

  ])

  dnl AC_ARG_WITH([pci],
  dnl   AS_HELP_STRING([--with-pci],
  dnl     [PCI funcs]),
  dnl   [],
  dnl   [with_pci=yes]
  dnl )

  dnl AS_IF([test "x$with_pci" = "xno"], [
  dnl   WITH_PCI=0
  dnl AC_SUBST(PCI_LIBS)
  dnl ])

  dnl AS_IF([test "x$with_pci" = "xyes"], [
  dnl   PCI_LIBS="-lpci"

  dnl   AC_CHECK_HEADERS([    \
  dnl     pci/pci.h           \
  dnl   ],[],[
  dnl     ERR([Missing core header files.])
  dnl   ])

  dnl ])

  dnl AC_SUBST(PCI_LIBS)
  AC_DEFINE_UNQUOTED([WITH_NET],[$WITH_NET],[Net funcs])
  dnl AC_DEFINE_UNQUOTED([WITH_PCI],[$WITH_PCI],[PCI funcs])

])
