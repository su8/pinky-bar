/*
   08/16/2016

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

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/param.h>
#include <vm/vm_param.h>
#include <devstat.h>

#include "include/headers.h"
#include "include/freebzd.h"

/* bsdhwmon is nowhere closer to lm_sensors,
 * which unfortunately is not supported in BSD.
 *
 * My initial attempt was to add alternative via lm_sensors
 * to the FreeBSD users, because the unpredictable sensors 
 * and their specific naming which has to be used in order to obtain the
 * sensors values in FreeBSD pretty much restricts some of the code only
 * to ASUS motherboards.
 *
 * In linux regardless of the modules, their names, the sensors reports will
 * always be stored in same filename in the virtual filesystem. Now you
 * understand how hard it is to make general assumption how to obtain such
 * values in FreeBSD.
*/

void 
get_ram(char *str1, uint8_t num) {
  u_int total = 0, freeram = 0, inactive = 0, pagesize = 0;
  u_int cache = 0, bufferram = 0, dummy = 0;
  uintmax_t utotal = 0, used = 0, pz = 0;
  size_t len = sizeof(dummy);

  SYSCTLVAL("vm.stats.vm.v_page_size", &pagesize);
  SYSCTLVAL("vm.stats.vm.v_page_count", &total);
  SYSCTLVAL("vm.stats.vm.v_inactive_count", &inactive);
  SYSCTLVAL("vm.stats.vm.v_free_count", &freeram);
  SYSCTLVAL("vm.stats.vm.v_cache_count", &cache);
  SYSCTLVAL("vfs.bufspace", &bufferram);

  pz = (uintmax_t)pagesize;
  used = ((uintmax_t)total * pz - (uintmax_t)freeram * pz
          - (uintmax_t)inactive * pz
          - (uintmax_t)cache * pz - (uintmax_t)bufferram) / MB;
  utotal = ((uintmax_t)total * pz) / MB;

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT "%s", utotal, "MB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT "%s",
        ((uintmax_t)freeram * pz) / MB, "MB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT "%s",
        ((uintmax_t)inactive * pz) / MB, "MB");
      break;
    case 4:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)bufferram / MB, "MB");
      break;
    case 5:
      FILL_UINT_ARR(str1, (used * 100) / utotal);
      break;
  }

}


void
get_loadavg(char *str1) {
  double up[3];
  if (-1 == getloadavg(up, 3)) {
  	FUNC_FAILED("getloadavg()");
  }
  FILL_ARR(str1, "%.2f %.2f %.2f",
    (float)up[0], (float)up[1], (float)up[2]);
}


/* 
  sysctl -a|grep 'aibs'
  dev.aibs.0.volt.0: 1356 850 1600
  dev.aibs.0.volt.1: 3344 2970 3630
  dev.aibs.0.volt.2: 5040 4500 5500
  dev.aibs.0.volt.3: 12278 10200 13800
  dev.aibs.0.temp.0: 39.0C 60.0C 95.0C
  dev.aibs.0.temp.1: 38.0C 45.0C 75.0C
  dev.aibs.0.fan.0: 1053 600 7200
  dev.aibs.0.fan.1: 1053 600 7200
  dev.aibs.0.%parent: acpi0
  dev.aibs.0.%pnpinfo: _HID=ATK0110 _UID=16843024
  dev.aibs.0.%location: handle=\_SB_.PCI0.SBRG.ASOC
  dev.aibs.0.%driver: aibs
  dev.aibs.0.%desc: ASUSTeK AI Booster (ACPI ASOC ATK0110)
*/
void
get_voltage(char *str1) {
  u_int  vol0[3], vol1[3], vol2[3], vol3[3];
  
  memset(vol0, 0, sizeof(vol0));
  memset(vol1, 0, sizeof(vol1));
  memset(vol2, 0, sizeof(vol2));
  memset(vol3, 0, sizeof(vol3));

  size_t len = sizeof(vol0);
  
  SYSCTLVAL(VOLTAGE_FILE("0"), &vol0);
  SYSCTLVAL(VOLTAGE_FILE("1"), &vol1);
  SYSCTLVAL(VOLTAGE_FILE("2"), &vol2);
  SYSCTLVAL(VOLTAGE_FILE("3"), &vol3);

  FILL_ARR(str1, "%.2f %.2f %.2f %.2f",
    (float)vol0[0] / 1000.0f,
    (float)vol1[0] / 1000.0f,
    (float)vol2[0] / 1000.0f,
    (float)vol3[0] / 1000.0f);
}


void
get_mobo_temp(char *str1) {
  u_int  temp[3];
  memset(temp, 0, sizeof(temp));
  size_t len = sizeof(temp);

  SYSCTLVAL("dev.aibs.0.temp.1", &temp);
  get_temp(str1, (uint_least32_t)temp[0]);
}


void
get_mobo(char *str1) {
  char temp[VLA];
  size_t len = sizeof(temp);

  SYSCTLVAL("dev.aibs.0.%desc", &temp);
  FILL_STR_ARR(1, str1, temp);
}


/*
  Couldn't add this option on my own.
  Used the following resources to make this function happen:
    http://ftp.stu.edu.tw/FreeBSD/branches/3.0-stable/src/libexec/rpc.rstatd/rstat_proc.c
    https://github.com/giampaolo/psutil/blob/master/psutil/arch/bsd/freebsd.c
    http://opensource.apple.com/source/net_snmp/net_snmp-16/net-snmp/agent/mibgroup/ucd-snmp/diskio.c
    https://searchcode.com/codesearch/view/29835031/
    http://fossies.org/linux/pcp/src/pmdas/freebsd/disk.c
  Had to use Valgrind since we allocate memory with malloc.
*/
void
get_statio(char *str1, char *str2) {
  struct statinfo stats;
  struct device_selection *dev_select = NULL;
  struct devstat *d = NULL;
  long int select_generation = 0;
  int x = 0, num_devices = 0, num_selected = 0, num_selections = 0;

  FILL_STR_ARR(1, str1, "Null");
  if(0 != devstat_checkversion(NULL)) {
    return;
  }

  memset(&stats, 0, sizeof(stats));
  stats.dinfo = (struct devinfo *)malloc(sizeof(struct devinfo));
  if (NULL == stats.dinfo) {
    return;
  }

  if(-1 == devstat_getdevs(NULL, &stats)) {
    goto error;
  }

  num_devices = stats.dinfo->numdevs;
  if (-1 == devstat_selectdevs(&dev_select, &num_selected, &num_selections,
    &select_generation, stats.dinfo->generation, stats.dinfo->devices, num_devices,
    NULL, 0, NULL, 0, DS_SELECT_ADD, 16, 0)) {
    goto error;
  }

  for (x = 0; x < 16; x++) {
    d = &stats.dinfo->devices[x];
    if (STREQ(str2, d->device_name)) {

      if (d->device_type != DEVSTAT_TYPE_DIRECT &&
        d->device_type != DEVSTAT_TYPE_IF_SCSI &&
        d->device_type != DEVSTAT_TYPE_IF_IDE) {
        break;
      }

      FILL_ARR(str1, "Read " FMT_UINT " MB, Written " FMT_UINT " MB",
        (uintmax_t)d->bytes[DEVSTAT_READ] / MB,
        (uintmax_t)d->bytes[DEVSTAT_WRITE] / MB);
      break;
    }
  }

error:
  if (NULL != dev_select) {
    free(dev_select);
  }
  if (NULL != stats.dinfo) {
    if (stats.dinfo->mem_ptr) {
      free(stats.dinfo->mem_ptr);
    }
    free(stats.dinfo);
  }
  return;
}


/*
 Looks like acpi is the only way
 in FreeBSD to obtain battery information.
  hw.acpi.acline: 1
  hw.acpi.battery.life: 100
  hw.acpi.battery.time: -1
  hw.acpi.battery.state: 0
  hw.acpi.battery.units: 1
*/
void 
get_battery(char *str1) {
  u_int dummy = 0;
  uint_least32_t perc = 0;
  size_t len = sizeof(dummy);
  SYSCTLVAL("hw.acpi.battery.life", &dummy);

  perc = (uint_least32_t)dummy;
  FILL_ARR(str1, ULINT, (101 < perc ? 0 : perc));
}


void
get_swapp(char *str1, uint8_t num) {
  struct xswdev xsw;
  u_int pagesize = 0, dummy = 0;
  uintmax_t total = 0, used = 0, pz = 0;
  int mib[20];
  memset(mib, 0, sizeof(mib));
  size_t mibi = sizeof(mib) / sizeof(mib[0]);
  size_t len = sizeof(dummy), sisi = sizeof(struct xswdev);

  FILL_STR_ARR(1, str1, "0 MB");
  SYSCTLVAL("vm.stats.vm.v_page_size", &pagesize);
  pz = (uintmax_t)pagesize;

  if (0 != (sysctlnametomib("vm.swap_info", mib, &mibi))) {
    return;
  }
  if (0 != (sysctl(mib, (u_int)(mibi + 1), &xsw, &sisi, NULL, 0))) {
    return;
  }
  if (xsw.xsw_version != XSWDEV_VERSION) {
    return;
  }
  used  = (uintmax_t)xsw.xsw_used;
  total = (uintmax_t)xsw.xsw_nblks;

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT" %s", ((total * pz) / MB), "MB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT" %s",
        (((total - used) * pz) / MB), "MB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT" %s", ((used * pz) / MB), "MB");
      break;
    case 4:
      {
        if (0 != total) {
          FILL_ARR(str1, FMT_UINT"%%", (used * 100) / total);
        } else {
          FILL_STR_ARR(1, str1, "0 %");
        }
      }
      break;
  }
}
