/*
   Copyright 08/06/2016
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

#include "config.h"

#if WITH_NET == 1

#include <arpa/inet.h>
/* #include <netdb.h> */
/* #include <sys/types.h> */
#include <sys/socket.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if.h>

#endif

#include "include/headers.h"
#include "net.h"

/* Thanks to http://www.matisse.net/bitcalc/?source=print */
void
get_net(char *str1, char *str2, unsigned char num) {
#if WITH_NET == 1

  struct ifaddrs *ifaddr = NULL, *ifa = NULL;
  struct rtnl_link_stats *stats;
  struct sockaddr_ll *mac;
  static uintmax_t prev_recv = 0, prev_sent = 0;
  uintmax_t cur_recv, cur_sent;
  void *temp_void = NULL;
  char temp[VLA];

  if (-1 == getifaddrs(&ifaddr)) {
    exit_with_err(ERR, "getifaddrs() failed");
  }

  for (ifa = ifaddr; NULL != ifa; ifa = ifa->ifa_next) {
    if (NULL == ifa->ifa_addr) {
      continue;
    }
    if (3 == num || 5 == num || 6 == num) { /* ip | netmask | broadcast */
      if (ifa->ifa_addr->sa_family == AF_INET) {
        if (0 == (strcmp(str2, ifa->ifa_name))) {
          switch(num) {
            case 3:
              temp_void = ifa->ifa_addr;
              break;
            case 5:
              temp_void = ifa->ifa_netmask;
              break;
            case 6:
              temp_void = ifa->ifa_broadaddr;
              break;
          }
          inet_ntop(AF_INET, &(((struct sockaddr_in *)temp_void)->sin_addr),
              temp, INET_ADDRSTRLEN); 
          FILL_STR_ARR(1, str1, temp);
          break;
        }
      }
    } else if (ifa->ifa_addr->sa_family == AF_PACKET &&
        NULL != ifa->ifa_data) {
        if (0 == (strcmp(str2, ifa->ifa_name))) {
          stats = ifa->ifa_data;

          if (2 == num) { /* upload | download speeds */
            cur_recv = (uintmax_t)stats->rx_bytes - prev_recv;
            cur_sent = (uintmax_t)stats->tx_bytes - prev_sent;

            FILL_ARR(str1, "Down " FMT_UINT " KB, Up " FMT_UINT " KB",
              (cur_recv / KB), (cur_sent / KB));

            prev_recv = cur_recv;
            prev_sent = cur_sent;
          } else if (1 == num){ /* consumed internet so far */
    
            FILL_ARR(str1, "Down " FMT_UINT " MB, Up " FMT_UINT " MB",
              ((uintmax_t)stats->rx_bytes / MB),
              ((uintmax_t)stats->tx_bytes / MB));
          } else if (4 == num) { /* mac address */

            temp_void = ifa->ifa_addr;
            mac = (struct sockaddr_ll *)temp_void;
            if (6 != mac->sll_halen) {
              FILL_STR_ARR(1, str1, "Null");
              break;
            }
            FILL_ARR(str1, "%02x:%02x:%02x:%02x:%02x:%02x",
                mac->sll_addr[0], mac->sll_addr[1],
                mac->sll_addr[2], mac->sll_addr[3],
                mac->sll_addr[4], mac->sll_addr[5]);
          } else if (7 == num) { /* link speed */

            get_link_speed(str1, str2);
          }
          break;
        }
    }
  }
  if (NULL != ifaddr) {
    freeifaddrs(ifaddr);
  }

#else
  exit_with_err(ERR, "recompile the program --with-net");
#endif
}


void get_link_speed(char *str1, char *str2) {
#if WITH_NET == 1

  struct ethtool_cmd ecmd;
  struct ifreq ifr;
  int sock = 0;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (-1 == sock) {
    exit_with_err(ERR, "socket() failed");
  }

  ecmd.cmd = ETHTOOL_GSET;
  ifr.ifr_data = (char *)&ecmd;
  snprintf(ifr.ifr_name, IF_NAMESIZE, "%s", str2);

  if (0 < (ioctl(sock, SIOCETHTOOL, &ifr))) {
    exit_with_err(ERR, "ioctl() failed");
  }

  FILL_ARR(str1, "%d%s", ecmd.speed, (999 > ecmd.speed ? "Mbps" : "Gbps"));

#else
  exit_with_err(ERR, "recompile the program --with-net");
#endif
}
