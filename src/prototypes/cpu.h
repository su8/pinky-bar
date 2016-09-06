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

#ifndef CPU_H_
#define CPU_H_

/* Inspired from  https://en.wikipedia.org/wiki/CPUID and
 * llvm Host.cpp */
#define CPU_VENDOR(x, z) __asm__("cpuid": "=b" (z) : "a" (x))
#define CPU_FEATURE(x, z) __asm__("cpuid": "=a" (z) : "a" (x))
#define CPU_STR2(regizter, a, b, c, d) __asm__( \
  "cpuid": \
    "=a" (a), \
    "=b" (b), \
    "=c" (c), \
    "=d" (d) \
    : "a" (regizter) \
)
#define CPU_ID_STR(regizter, b, c, d) __asm__( \
  "cpuid": \
    "=b" (b), \
    "=c" (c), \
    "=d" (d) \
    : "a" (regizter) \
)

#define BIT_SHIFT(x) ((x) & 0xf)
#define AmD    0x68747541
#define InteL  0x756e6547


/* --coresload related constant to determine
 * how many cpu cores/threads to try for detection */
#define MAX_CORES 40

void get_cpu(char *);
void get_cores_load(char *);

#if !defined(HAVE_SENSORS_SENSORS_H)
void get_cpu_temp(char *);
#endif /* HAVE_SENSORS_SENSORS_H */

#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
void get_cpu_clock_speed(char *);
void get_cpu_info(char *);
#endif


#endif /* CPU_H_ */
