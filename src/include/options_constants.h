/*
   07/29/2015, 07/18/2016

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

#if WITH_PY3STATUS == 1 && WITH_COLOURS == 1
# define ENT "]"
#elif WITH_AWESOMEWM == 1 && WITH_COLOURS == 1
# define ENT "</span>"
#elif WITH_XMOBAR == 1 && WITH_COLOURS == 1
# define ENT "</fc>"
#else
# define ENT ""
#endif /* WITH_PY3STATUS */

#define STR_SPEC "%s"
#define SONG_ORIG STR_SPEC ENT " "
#define KERN_ORIG STR_SPEC ENT " "

#ifndef WITH_NCURSES
#define WITH_NCURSES 6
#endif /* WITH_NCURSES */

#if defined(HAVE_X11_XLIB_H) && WITH_DWM == 1
#include "colours/x11_colours.h"

#elif WITH_NCURSES == 1
#include "colours/ncurses_colours.h"

#elif WITH_PY3STATUS == 1
#include "colours/py3status_colours.h"

#elif WITH_AWESOMEWM == 1
#include "colours/awesomewm_colours.h"

#elif WITH_XMOBAR == 1
#include "colours/xmobar_colours.h"

#elif WITH_LEMONBAR == 1
#include "colours/lemonbar_colours.h"

#elif WITH_TMUX == 1
#include "colours/tmux_colours.h"

#else
#include "colours/dzen2_colours.h"

#endif /* HAVE_X11_XLIB_H && WITH_DWM */


/* options.c format constants */
#define FMT           NAME_VAL"%%" ENT " "                    /* STR1 10%             */
#define FMT_TIME      NAME_VAL ENT                            /* Time 10:00 PM        */
#define FMT_MOBO      FMT_TIME" "                             /* VEND NAME            */
#define FMT_CPU       NAME_VAL"%%" ENT " "                    /* CPU 10%              */
#define FMT_CORES     FMT_TIME                                /* CPU varying          */
#define FMT_RAM       FMT                                     /* RAM 10%              */
#define FMT_RAM2      FMT_TIME" "                             /* RAM 10MB             */
#define FMT_SSD       FMT                                     /* SSD 10%              */
#define FMT_SSD2      FMT_RAM2                                /* SSD 10MB             */
#define FMT_PKGS      FMT_TIME" "                             /* Pkgs 123             */
#define FMT_VOLT      FMT_PKGS                                /* Voltage 1 2 3 4      */
#define FMT_FANS      FMT_TIME                                /* Fans varying         */
#define FMT_VOL       FMT                                     /* Volume 10%           */
#define FMT_NET       FMT_PKGS                                /* Down 123 Up 123      */
#define FMT_STATIO    FMT_NET                                 /* Read 123 Written 123 */
#define FMT_CPUSPEED  PINK STR_SPEC ENT " "                   /* 1234 MHz             */
#define FMT_TEMP      TEMP                                    /* 32C                  */
#define FMT_BATT      FMT                                     /* BATT 10%             */
#define FMT_UP        FMT_TIME" "                             /* Up 10 min            */
#define FMT_LOAD      FMT_TIME" "                             /* Load/avg 0.01 0.01 0.01       */

#define FMT_PINK PINK STR_SPEC ENT " "

#endif /* CONSTANTS_H_ */
