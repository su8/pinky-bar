/*
   Copyright 02/22/2015 Aaron Caffrey https://github.com/wifiextender

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <unistd.h>

#include "functions.h"

#define FMT       "\x0a%s \x0b%s%%%c "
#define FMT_TIME  "\x0a%s \x0b%s"
#define FMT_CPU   FMT
#define FMT_RAM   FMT
#define FMT_SSD   FMT
#define FMT_PKGS  FMT_TIME"%c "
#define FMT_KERN  "\x09%s%c "
#define FMT_VOL   FMT
#define COMMA     ','

int main(void)
{
    char packs[VLA] = GIVEN_DISTRO;
    char cpu[VLA], ram[VLA], ssd[VLA], kern[VLA];
    char volume[VLA], Time[VLA], combine[VLA*7];

    get_cpu(cpu);

    sleep(1);

    get_cpu(cpu);
    get_ram(ram);
    get_ssd(ssd);
    get_packs(packs);
    get_kernel(kern);
    get_volume(volume);
    get_time(Time);

    snprintf(combine, VLA*7,
        FMT_CPU FMT_RAM FMT_SSD FMT_PKGS FMT_KERN FMT_VOL FMT_TIME,
        "CPU", cpu, COMMA,
        "RAM", ram, COMMA,
        "SSD", ssd, COMMA,
        "Pkgs", packs, COMMA,
        kern, COMMA,
        "Volume", volume, COMMA,
        "Time", Time);

    set_status(combine);

    return EXIT_SUCCESS;
}
