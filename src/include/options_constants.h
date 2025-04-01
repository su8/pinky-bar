/*
   07/29/2015, 07/18/2016, 04/01/2025

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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define VLA 200
#define WHOLE_MAIN_ARR_LEN VLA*16
#define GLUE(x, z, ...) (x+=snprintf(x, WHOLE_MAIN_ARR_LEN, z, __VA_ARGS__))

#if defined(__FreeBSD__)
/* The clock ticks in FreeBSD are 133 */
#define TICKZ 100
#else
#define TICKZ sysconf(_SC_CLK_TCK)
#endif

#include "options_generator.h"

#define STR_SPEC "%s"

#define SONG_ORIG mk_str("%s%s%s", STR_SPEC, ENT, " ")
#define KERN_ORIG mk_str("%s%s%s", STR_SPEC, ENT, " ")

#ifndef WITH_NCURSES
#define WITH_NCURSES 6
#endif /* WITH_NCURSES */

#define NAME_VAL  PINK, STR_SPEC                              /* STR1 STR2       */
#define TEMP      mk_str("%s%s%s%s", YELLOW, STR_SPEC "C", ENT, " ") /* 32C             */
#define FMT_KERN  mk_str("%s%s%s", YELLOW, STR_SPEC, ENT, " ")           /* Kernel Version  */
#define FMT_SONG  mk_str("%s%s%s", PINK, STR_SPEC, ENT, " ")             /* Song            */

/* options.c format constants */
#define FMT           mk_str("%s%s%s%s", NAME_VAL"%%", ENT, " ")                    /* STR1 10%             */
#define FMT_TIME      mk_str("%s%s%s", NAME_VAL, ENT)                            /* Time 10:00 PM        */
#define FMT_MOBO      mk_str("%s%s%s%s", NAME_VAL, ENT, " ")                             /* VEND NAME            */
#define FMT_CPU       mk_str("%s%s%s%s", NAME_VAL"%%", ENT, " ")                    /* CPU 10%              */
#define FMT_CORES     FMT_TIME                                /* CPU varying          */
#define FMT_RAM       FMT                                     /* RAM 10%              */
#define FMT_RAM2      FMT_MOBO                                /* RAM 10MB             */
#define FMT_SSD       FMT                                     /* SSD 10%              */
#define FMT_SSD2      FMT_RAM2                                /* SSD 10MB             */
#define FMT_PKGS      FMT_MOBO                                /* Pkgs 123             */
#define FMT_VOLT      FMT_PKGS                                /* Voltage 1 2 3 4      */
#define FMT_FANS      FMT_TIME                                /* Fans varying         */
#define FMT_VOL       FMT                                     /* Volume 10%           */
#define FMT_NET       FMT_PKGS                                /* Down 123 Up 123      */
#define FMT_STATIO    FMT_NET                                 /* Read 123 Written 123 */
#define FMT_CPUSPEED  mk_str("%s%s%s%s", NAME_VAL, ENT, " ")                   /* 1234 MHz             */
#define FMT_TEMP      TEMP                                    /* 32C                  */
#define FMT_BATT      FMT                                     /* BATT 10%             */
#define FMT_UP        FMT_MOBO                                /* Up 10 min            */
#define FMT_LOAD      FMT_MOBO                                /* Load/avg 0.01 0.01 0.01       */

#define FMT_PINK mk_str("%s%s%s%s", NAME_VAL, ENT, " ")

#endif /* CONSTANTS_H_ */
