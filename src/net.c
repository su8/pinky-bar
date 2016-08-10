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

/* #if WITH_PCI == 1 */
/* #include <pci/pci.h> */
/* #endif /1* WITH_PCI *1/ */

#endif /* WITH_NET */

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
    FUNC_FAILED("getifaddrs()");
  }
  FILL_STR_ARR(1, str1, "Null");

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

          if (2 == num) { /* upload and download speeds */
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
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


/* Not using exit_with_err to freeifaddrs */
void
get_link_speed(char *str1, char *str2) {
#if WITH_NET == 1

  struct ethtool_cmd ecmd;
  struct ifreq ifr;
  int sock = 0;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (-1 == sock) {
    return;
  }

  ecmd.cmd = ETHTOOL_GSET;
  ifr.ifr_data = (char *)&ecmd;
  snprintf(ifr.ifr_name, IF_NAMESIZE, "%s", str2);

  if (0 < (ioctl(sock, SIOCETHTOOL, &ifr))) {
    return;
  }
  FILL_ARR(str1, "%d%s", ecmd.speed, "Mbps");

#else
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


void
get_ip_lookup(char *str1, char *str2) {
#if WITH_NET == 1

  struct addrinfo *rp = NULL, *result = NULL;
  struct addrinfo hints;
  void *temp_void = NULL;
  char temp[VLA];
  int err = 0;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0; /* udp | tcp */

  err = getaddrinfo(str2, NULL, &hints, &result);
  if (0 != err) {
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
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


/* void */
/* get_nic_info(char *str1, char *str2) { */
/* #if WITH_PCI == 1 */

/*   uintmax_t vendor = 0, model = 0; */
/*   char temp[VLA]; */
/*   struct pci_access *pacc = NULL; */
/*   struct pci_dev *dev; */

/*   NIC_VEND(temp, str2); */
/*   FILE *fp = fopen(temp, "r"); */
/*   if (NULL == fp) { */
/*     exit_with_err(CANNOT_OPEN, temp); */
/*   } */

/* #pragma GCC diagnostic push */
/* #pragma GCC diagnostic ignored "-Wunused-result" */
/*   fscanf(fp, FMT_UINTX, &vendor); /1* hex *1/ */
/* #pragma GCC diagnostic pop */
/*   fclose(fp); */

/*   NIC_MODEL(temp, str2); */
/*   if (NULL == (fp = fopen(temp, "r"))) { */
/*     exit_with_err(CANNOT_OPEN, temp); */
/*   } */

/* #pragma GCC diagnostic push */
/* #pragma GCC diagnostic ignored "-Wunused-result" */
/*   fscanf(fp, FMT_UINTX, &model); /1* hex *1/ */
/* #pragma GCC diagnostic pop */
/*   fclose(fp); */

/*   pacc = pci_alloc(); */
/*   if (NULL == pacc) { */
/*     goto error; */
/*   } */

/*   pci_init(pacc); */
/*   if (NULL == pacc) { */
/*     goto error; */
/*   } */
/*   pci_scan_bus(pacc); */

/*   for (dev = pacc->devices; NULL != dev; dev = dev->next) { */
/*     pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS); */

/*     if ((uintmax_t)vendor == (uintmax_t)dev->vendor_id && */
/*         (uintmax_t)model == (uintmax_t)dev->device_id) { */

/*       pci_lookup_name(pacc, temp, VLA, */
/*         PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE, */
/*         (uintmax_t)vendor, (uintmax_t)model); */

/*       FILL_STR_ARR(1, str1, temp); */
/*       break; */
/*     } */
/*   } */

/* error: */
/*   if (NULL != pacc) { */
/*     pci_cleanup(pacc); */
/*   } */
/*   return; */

/* #else */
/*   RECOMPILE_WITH("pci"); */
/* #endif /1* WITH_PCI *1/ */
/* } */
