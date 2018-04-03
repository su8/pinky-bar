/*
   04/03/2018

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

#ifndef X11_H_
#define X11_H_

#if defined (HAVE_X11_XLIB_H) && WITH_DWM == 1
void set_status(const char *);
#endif /* HAVE_X11_XLIB_H  && WITH_DWM */

#if WITH_KEYBOARD == 1 && defined(HAVE_X11_XKBLIB_H)
void get_keyboard(char *);
#endif /* WITH_KEYBOARD && HAVE_X11_XKBLIB_H */

#if WITH_MOUSE == 1 && defined(HAVE_X11_XLIB_H)
void get_mouse(char *);
#endif /* WITH_MOUSE && HAVE_X11_XLIB_H */

#if WITH_NUMLOCK == 1 && defined(HAVE_X11_XLIB_H)
void get_numlock(char *);
void get_capslock(char *);
void get_scrolllock(char *);
#endif /* WITH_NUMLOCK && HAVE_X11_XLIB_H */

#endif /* X11_H_ */
