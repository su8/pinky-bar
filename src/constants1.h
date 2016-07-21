/*
   Copyright 07/29/2015, 07/18/2016
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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define VLA 200

/*
 * dwm colours
 * the colours in use are
 * specified in your dwm config.h
*/
#if defined (HAVE_X11_XLIB_H)

#define NAME_VAL  "\x0a%s \x0b%s"   /* STR1 STR2        */
#define TEMP      "\x09%sC\x0b%c "  /* 32C,             */
#define FMT_KERN  "\x09%s%c "       /* Kernel Version,  */

#define CPU_STR    "CPU"
#define RAM_STR    "RAM"
#define SSD_STR    "SSD"
#define PKG_STR    "Pkgs"
#define VOLT_STR   "Voltage"
#define FANS_STR   "Fans/RPM"
#define MOBO_STR   "Mobo"
#define VOL_STR    "Volume"
#define TIME_STR   "Time"



/* dzen colours and xbm icons for xmonad */
#else

#define XBM_ICON(given_icon) ("^i("ICONS_DIR"/"given_icon")")
#define YELLOW   "^fg(#f0c674)"
#define BLUE     "^fg(#1793D1)"
#define PINK     "^fg(#b294bb)"

#define NAME_VAL  BLUE"%s "PINK"%s"   /* STR1 STR2        */
#define TEMP      YELLOW"%s^i("ICONS_DIR"/temp.xbm)"PINK"%c "  /* 32C, */
#define FMT_KERN  YELLOW"%s%c "       /* Kernel Version,  */

#define CPU_STR    XBM_ICON("cpu.xbm")
#define RAM_STR    XBM_ICON("mem.xbm")
#define SSD_STR    XBM_ICON("diskette.xbm")
#define PKG_STR    XBM_ICON("arch.xbm")
#define VOLT_STR   XBM_ICON("voltage.xbm")
#define FANS_STR   XBM_ICON("fan.xbm")
#define MOBO_STR   XBM_ICON("mobo.xbm")
#define VOL_STR    XBM_ICON("vol.xbm")
#define TIME_STR   XBM_ICON("clock.xbm")

#endif /* dwm/xmonad colours */


/*
   main.c constants
*/
#define FMT       NAME_VAL"%%%c "   /* STR1 10%,        */
#define FMT_TIME  NAME_VAL          /* Time 10:00 PM    */
#define FMT_MOBO  FMT_TIME" "TEMP   /* VEND NAME 32C,   */
#define FMT_CPU   FMT_TIME"%% "TEMP /* CPU 10% 32C,     */
#define FMT_RAM   FMT               /* RAM 10%,         */
#define FMT_SSD   FMT               /* SSD 10%,         */
#define FMT_PKGS  FMT_TIME"%c "     /* Pkgs 123,        */
#define FMT_VOLT  FMT_PKGS          /* Voltage 1 2 3 4, */
#define FMT_FANS  FMT_TIME          /* Fans varying     */
#define FMT_VOL   FMT               /* Volume 10%,      */
#define COMMA     ','
#define WHOLE_MAIN_ARR_LEN VLA*14


/* functions.c constants */
#define CANNOT_OPEN "Could not open"
#define ERR "Error:"

#endif /* CONSTANTS_H_ */
