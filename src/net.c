/*
   08/06/2016

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

#if WITH_NET == 1

#if defined(__linux__)
#include <netdb.h>
/* #include <sys/types.h> */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if.h>

#if WITH_PCI == 1
#include <pci/pci.h>
#endif /* WITH_PCI */

#endif /* __linux__ */

#if defined(__FreeBSD__)
#include <netdb.h>
/* #include <sys/types.h> */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <ifaddrs.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <netinet/in.h>
#endif /* __FreeBSD__ */

#endif /* WITH_NET */

#include "include/headers.h"
#include "prototypes/net.h"

#if defined(__FreeBSD__)
#include "include/freebzd.h"
#endif /* __FreeBSD__ */

/* Thanks to http://www.matisse.net/bitcalc/?source=print
 * and `man netdevice' */
void
get_net(char *str1, char *str2, uint8_t num) {
#if WITH_NET == 1

#if defined(__linux)
  struct rtnl_link_stats *stats = NULL;
  struct sockaddr_ll *mac = NULL;
#else
  struct if_data *stats = NULL;
  struct sockaddr_dl *mac = NULL;
#endif /* __linux__ */

  struct ifaddrs *ifaddr = NULL, *ifa = NULL;
  static uintmax_t prev_recv = 0, prev_sent = 0;
  uintmax_t cur_recv = 0, cur_sent = 0;
  unsigned char *umac = NULL;
  void *temp_void = NULL;
  char temp[VLA];

  if (-1 == getifaddrs(&ifaddr)) {
    FUNC_FAILED("getifaddrs()");
  }
  FILL_STR_ARR(1, str1, "Null");

  for (ifa = ifaddr; NULL != ifa; ifa = ifa->ifa_next) {
    if ((IFF_UP | IFF_BROADCAST) != (ifa->ifa_flags & (
      IFF_UP | IFF_BROADCAST | IFF_POINTOPOINT |
       IFF_LOOPBACK | IFF_NOARP))) {
      continue;
    }
    if (NULL == ifa->ifa_addr) {
      continue;
    }
    if (3 == num || 5 == num || 6 == num) { /* ip | netmask | broadcast */
      if (ifa->ifa_addr->sa_family == AF_INET) {
        if (STREQ(str2, ifa->ifa_name)) {
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
#if defined(__linux__)
    } else if (ifa->ifa_addr->sa_family == AF_PACKET &&
        NULL != ifa->ifa_data) {
#else
    } else if (ifa->ifa_addr->sa_family == AF_LINK &&
        NULL != ifa->ifa_data) {
#endif /* __linux__ */
        if (STREQ(str2, ifa->ifa_name)) {

#if defined(__linux__)
          stats = ifa->ifa_data;
#else
          stats = (struct if_data *)ifa->ifa_data;
#endif /* __linux__ */

          if (2 == num) { /* upload and download speeds */
#if defined(__linux__)
            cur_recv = (uintmax_t)stats->rx_bytes - prev_recv;
            cur_sent = (uintmax_t)stats->tx_bytes - prev_sent;
#else
            cur_recv = (uintmax_t)stats->ifi_ibytes - prev_recv;
            cur_sent = (uintmax_t)stats->ifi_obytes - prev_sent;
#endif /* __linux__ */
            FILL_ARR(str1, "Down " FMT_UINT " KB, Up " FMT_UINT " KB",
              (cur_recv / KB), (cur_sent / KB));

            prev_recv = cur_recv;
            prev_sent = cur_sent;
          } else if (1 == num) { /* consumed internet so far */

#if defined(__linux__)
            FILL_ARR(str1, "Down " FMT_UINT " MB, Up " FMT_UINT " MB",
              ((uintmax_t)stats->rx_bytes / MB),
              ((uintmax_t)stats->tx_bytes / MB));
#else
            FILL_ARR(str1, "Down " FMT_UINT " MB, Up " FMT_UINT " MB",
              ((uintmax_t)stats->ifi_ibytes / MB),
              ((uintmax_t)stats->ifi_obytes / MB));
#endif /* __linux__ */

#if defined(__linux__)
          } else if (4 == num) { /* mac address */

            temp_void = ifa->ifa_addr;
            mac = (struct sockaddr_ll *)temp_void;
            /*
              6 == ether
              20 == infiniband
            */
            if (6 != mac->sll_halen) {
              break;
            }
            FILL_ARR(str1, "%02x:%02x:%02x:%02x:%02x:%02x",
                mac->sll_addr[0], mac->sll_addr[1],
                mac->sll_addr[2], mac->sll_addr[3],
                mac->sll_addr[4], mac->sll_addr[5]);
          } else if (7 == num || 8 == num || 9 == num ||
              10 == num) { /* link speed | driver | version | firmware */

            get_nic_info2(str1, str2, (uint8_t)(num - 6));
          }
#else
          } else if (4 == num) { /* mac address */
            temp_void = ifa->ifa_addr;
            mac = (struct sockaddr_dl *)temp_void;
            /*
              6 == ether
              20 == infiniband
            */
            if (6 != mac->sdl_alen) {
              break;
            }
            umac = (unsigned char *)LLADDR(mac);
            FILL_ARR(str1, "%02x:%02x:%02x:%02x:%02x:%02x",
                *umac, *(umac + 1), *(umac + 2),
                *(umac + 3), *(umac + 4), *(umac + 5));
          } else if (7 == num) { /* gateway */
            get_nic_info(str1, str2);
          }
#endif /* __linux__ */
          break;
        }
    }
  }
  if (NULL != ifaddr) {
    freeifaddrs(ifaddr);
  }

#else
  (void)str1;
  (void)str2;
  (void)num;
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


void
get_ip_lookup(char *str1, char *str2) {
#if WITH_NET == 1

  struct addrinfo *rp = NULL, *result = NULL, hints;
  void *temp_void = NULL;
  char temp[VLA];

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0; /* udp | tcp */

  if (0 != (getaddrinfo(str2, NULL, &hints, &result))) {
    FUNC_FAILED("getaddrinfo()");
  }

  for (rp = result; NULL != rp; rp = rp->ai_next) {
    if (NULL == rp->ai_addr) {
      continue;
    }
    /* check ipv4 again, despite the "hints" */
    if (rp->ai_family == AF_INET) {
      temp_void = rp->ai_addr;

      inet_ntop(AF_INET, &(((struct sockaddr_in *)temp_void)->sin_addr),
        temp, INET_ADDRSTRLEN);
      FILL_STR_ARR(1, str1, temp);

      break;
    }
  }
  if ('\0' == str1[0]) {
    FILL_STR_ARR(1, str1, "Null");
  }
  if (NULL != result) {
    freeaddrinfo(result);
  }

#else
  (void)str1;
  (void)str2;
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


/* It's so nice that the FreeBSD kernel
   does all the heavy lifting for us.
   In Linux you get only the hex numbers.

sysctl -a | grep 'dev.re.0'

dev.re.0.wake: 0
dev.re.0.int_rx_mod: 65
dev.re.0.stats: -1
dev.re.0.%parent: pci2
dev.re.0.%pnpinfo: vendor=0x10ec device=0x8168 subvendor=0x1043 subdevice=0x8432 class=0x020000
dev.re.0.%location: pci0:2:0:0 handle=\_SB_.PCI0.PCE4.RLAN
dev.re.0.%driver: re
dev.re.0.%desc: RealTek 8168/8111 B/C/CP/D/DP/E/F/G PCIe Gigabit Ethernet */


#if defined(__linux__)
/* Not using exit_with_err to freeifaddrs */
void
get_nic_info2(char *str1, char *str2, uint8_t num) {
#if WITH_NET == 1

  struct ethtool_cmd ecmd;
  struct ethtool_drvinfo drvinfo;
  struct ifreq ifr;
  int sock = 0;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (-1 == sock) {
    return;
  }

  switch(num) {
    case 1:
      ecmd.cmd = ETHTOOL_GSET;
      ifr.ifr_data = (char *)&ecmd;
      break;
    case 2:
    case 3:
    case 4:
      drvinfo.cmd = ETHTOOL_GDRVINFO;
      ifr.ifr_data = (char *)&drvinfo;
      break;
  }
  snprintf(ifr.ifr_name, IF_NAMESIZE, "%s", str2);

  if (0 != (ioctl(sock, SIOCETHTOOL, &ifr))) {
    return;
  }

  /* The `ethtool_cmd_speed' negotiation concept
   * is great, but the `SPEED_X' macros are not.
   * They are constants representing the link speed
   * from 10 Mbps up to 100 Gbps, but as we know,
   * the wifi/wireless "things" suffer from various
   * degradations, thus those macros are only reliable
   * to detect wired NIC that doesn't tend to change
   * it's link speed from various real-life factors.
  */
  switch(num) {
    case 1:
      FILL_ARR(str1, "%d%s", ecmd.speed, "Mbps");
      break;
    case 2:
      FILL_STR_ARR(1, str1, drvinfo.driver);
      break;
    case 3:
      FILL_STR_ARR(1, str1, drvinfo.version);
      break;
    case 4:
      FILL_STR_ARR(1, str1, drvinfo.fw_version);
      break;
  }

#else
  (void)str1;
  (void)str2;
  (void)num;
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


/* 
 Quick spot the bug game.
 code begin:
  struct pci_access *pacc= NULL;
  pacc = pci_alloc();
  pci_init(pacc);
  pci_cleanup(pacc);
 code end;
  Spotted the bug - no ? Well,
  GCC -O2 hangs on pci_init,
  while -O0 executes flawlessly.
  Disclaimer: the code is perfectly valid.
*/
void
get_nic_info(char *str1, char *str2) {
#if WITH_PCI == 1

  uintmax_t vendor = 0, model = 0;
  char temp[VLA];
  struct pci_access *pacc = NULL;
  struct pci_dev *dev = NULL;
  FILE *fp;

  FILL_STR_ARR(1, str1, "Null");
  NIC_VEND(temp, str2);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, temp, SCAN_UINTX, &vendor); /* hex */
#pragma GCC diagnostic pop

  NIC_MODEL(temp, str2);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  OPEN_X(fp, temp, SCAN_UINTX, &model); /* hex */
#pragma GCC diagnostic pop

  pacc = pci_alloc();
  if (NULL == pacc) {
    goto error;
  }

  pci_init(pacc);
  if (NULL == pacc) {
    goto error;
  }
  pci_scan_bus(pacc);

  for (dev = pacc->devices; NULL != dev; dev = dev->next) {
    pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);

    if ((uintmax_t)vendor == (uintmax_t)dev->vendor_id &&
        (uintmax_t)model == (uintmax_t)dev->device_id) {

      pci_lookup_name(pacc, temp, VLA,
        PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE,
        (uintmax_t)vendor, (uintmax_t)model);

      FILL_STR_ARR(1, str1, temp);
      break;
    }
  }

error:
  if (NULL != pacc) {
    pci_cleanup(pacc);
  }
  return;

#else
  (void)str1;
  (void)str2;
  RECOMPILE_WITH("pci");
#endif /* WITH_PCI */
}

#endif /* __linux__ */



#if defined(__FreeBSD__)
#define ROUNDUP(x) ((x) > 0 ? \
  (1 + (((x) - 1) | (sizeof(long) - 1))) : sizeof(long))

/* Based on:
 http://fossies.org/linux/misc/old/mrt-2.2.2a-src.tar.gz/mrt-2.2.2a/src/lib/kernel/bsd.c
 https://svn.nmap.org/nmap/libdnet-stripped/src/route-bsd.c
*/
void
get_nic_info(char *str1, char *str2) {
#if WITH_NET == 1

  struct rt_msghdr *rtm = NULL;
  struct sockaddr *sa = NULL, *addrs[RTAX_MAX];
  char *buf = NULL, *next = NULL, *lim = NULL, temp[VLA];
  uint8_t x = 0;
  size_t needed;
  void *temp_void = NULL;

  /* No, it's not Men In Black acronym */
  int mib[] = { CTL_NET, PF_ROUTE, 0, 0, NET_RT_DUMP, 0 };
  if (0 != (sysctl(mib, 6, NULL, &needed, NULL, 0))) {
    return;
  }

  buf = (char *)malloc(needed);
  if (NULL == buf) {
    return;
  }
  if (0 != (sysctl(mib, 6, buf, &needed, NULL, 0))) {
    goto error;
  }

  lim = buf + needed;
  for (next = buf; next < lim; next += rtm->rtm_msglen) {
    rtm = (struct rt_msghdr *)(void *)next;
    sa = (struct sockaddr *)(rtm + 1);
    if (NULL == sa || NULL == rtm) {
      continue;
    }
    if (sa->sa_family == AF_INET) {
      for (x = 0; x < RTAX_MAX; x++) {
        if (rtm->rtm_addrs & (1 << x)) {
          addrs[x] = sa;
          sa = (struct sockaddr *)((char *)sa + ROUNDUP(sa->sa_len));
        } else {
          addrs[x] = NULL;
        }
      }
      if (((rtm->rtm_addrs & (RTA_DST|RTA_GATEWAY)) == (RTA_DST|RTA_GATEWAY))
           && addrs[RTAX_DST]->sa_family == AF_INET
           && addrs[RTAX_GATEWAY]->sa_family == AF_INET) {

        temp_void = addrs[RTAX_GATEWAY];
        inet_ntop(AF_INET, &(((struct sockaddr_in *)temp_void)->sin_addr),
          temp, INET_ADDRSTRLEN);
        FILL_STR_ARR(1, str1, temp);
        break;
      }
    }
  }

error:
  if (NULL != buf) {
    free(buf);
  }
  return;

#else
  (void)str1;
  (void)str2;
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}
#endif /* __FreeBSD__ */
