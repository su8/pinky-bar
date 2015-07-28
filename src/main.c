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
#define TEMP      "\x09%sC\x0b%c "
#define FMT_MOBO  FMT_TIME" "TEMP
#define FMT_CPU   FMT_TIME"%% "TEMP
#define FMT_RAM   FMT
#define FMT_SSD   FMT
#define FMT_PKGS  FMT_TIME"%c "
#define FMT_VOLT  FMT_PKGS
#define FMT_FANS  FMT_TIME
#define FMT_KERN  "\x09%s%c "
#define FMT_VOL   FMT
#define COMMA     ','
#define WHOLE_MAIN_ARR_LEN VLA*14

int main(void)
{
    char packs[VLA] = GIVEN_DISTRO;
    char mobo[VLA*2], cpu[VLA], ram[VLA], ssd[VLA];
    char kern[VLA], volume[VLA], Time[VLA], combine[WHOLE_MAIN_ARR_LEN];
    char voltage[VLA], cpu_temp[VLA], mobo_temp[VLA], fans[VLA*2];

    get_cpu(cpu, cpu_temp);

    sleep(1);

    get_cpu(cpu, cpu_temp);
    get_ram(ram);
    get_ssd(ssd);
    get_packs(packs);
    get_kernel(kern);
    get_voltage(voltage);
    get_fans(fans);
    get_mobo(mobo, mobo_temp);
    get_volume(volume);
    get_time(Time);

    snprintf(combine, WHOLE_MAIN_ARR_LEN,
        FMT_CPU FMT_RAM FMT_SSD FMT_PKGS FMT_KERN
        FMT_VOLT FMT_FANS FMT_MOBO FMT_VOL FMT_TIME,
        "CPU", cpu, cpu_temp, COMMA,
        "RAM", ram, COMMA,
        "SSD", ssd, COMMA,
        "Pkgs", packs, COMMA,
        kern, COMMA,
        "Voltage", voltage, COMMA,
        "Fans/RPM", fans,
        "Mobo", mobo, mobo_temp, COMMA,
        "Volume", volume, COMMA,
        "Time", Time);

    set_status(combine);

    return EXIT_SUCCESS;
}
