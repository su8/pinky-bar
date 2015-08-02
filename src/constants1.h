/*
   Copyright 07/29/2015 Aaron Caffrey https://github.com/wifiextender

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

/*
   main.c constants, the colors in use are
   specified in your dwm config.h
*/
#define NAME_VAL  "\x0a%s \x0b%s"   /* STR1 STR2        */
#define FMT       NAME_VAL"%%%c "   /* STR1 10%,        */
#define FMT_TIME  NAME_VAL          /* Time 10:00 PM    */
#define TEMP      "\x09%sC\x0b%c "  /* 32C,             */
#define FMT_MOBO  FMT_TIME" "TEMP   /* VEND NAME 32C,   */
#define FMT_CPU   FMT_TIME"%% "TEMP /* CPU 10% 32C,     */
#define FMT_RAM   FMT               /* RAM 10%,         */
#define FMT_SSD   FMT               /* SSD 10%,         */
#define FMT_PKGS  FMT_TIME"%c "     /* Pkgs 123,        */
#define FMT_VOLT  FMT_PKGS          /* Voltage 1 2 3 4, */
#define FMT_FANS  FMT_TIME          /* Fans varying     */
#define FMT_KERN  "\x09%s%c "       /* Kernel Version,  */
#define FMT_VOL   FMT               /* Volume 10%,      */
#define COMMA     ','
#define WHOLE_MAIN_ARR_LEN VLA*14

#endif /* CONSTANTS_H_ */
