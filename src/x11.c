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

/* Functions shared between different operating
 * zyztemz or are short enough that doesn't meet the
 * 100 lines requirement to be put in standalone module */

#include "config.h" /* Auto-generated */

#if defined (HAVE_X11_XLIB_H)
#include <X11/Xlib.h>

#if WITH_KEYBOARD == 1 && defined(HAVE_X11_XKBLIB_H)
#include <X11/XKBlib.h>
#endif /* WITH_KEYBOARD && HAVE_X11_XKBLIB_H */

#endif /* HAVE_X11_XLIB_H */

#include "include/headers.h"
#include "prototypes/x11.h"

#if defined(HAVE_X11_XLIB_H)

#if WITH_DWM == 1 && defined(HAVE_X11_XLIB_H)
void 
set_status(const char *str1) {
  Display *display = XOpenDisplay(NULL);

  if (display) {
    XStoreName(display, DefaultRootWindow(display), str1);
    XSync(display, 0);
    XCloseDisplay(display);

  } else {
    exit_with_err(CANNOT_OPEN, "X server");
  }
}
#endif /* HAVE_X11_XLIB_H && WITH_DWM == 1 */


/* Based on:
 * https://gist.github.com/fikovnik/ef428e82a26774280c4fdf8f96ce8eeb  */
#if WITH_KEYBOARD == 1 && defined(HAVE_X11_XKBLIB_H)
void
get_keyboard(char *str1) {
  Display *display = XOpenDisplay(NULL);
  char *group = NULL;
  XkbStateRec state;

  if (NULL == display) {
    exit_with_err(CANNOT_OPEN, "X server");
  }

  XkbGetState(display, XkbUseCoreKbd, &state);
  XkbDescPtr desc = XkbGetKeyboard(display, XkbAllComponentsMask, XkbUseCoreKbd);
  group = XGetAtomName(display, desc->names->groups[state.group]);

  FILL_STR_ARR(1, str1, (group != NULL ? group : "unknown"));

  XFree(group);
  XCloseDisplay(display);
}
#endif /* WITH_KEYBOARD && HAVE_X11_XKBLIB_H */


/* Based on xset.c */
#if WITH_MOUSE == 1 && defined(HAVE_X11_XLIB_H)
void
get_mouse(char *str1) {
  Display *display = XOpenDisplay(NULL);
  int acc_num = 0, acc_denom = 0, threshold = 0;

  if (NULL == display) {
    exit_with_err(CANNOT_OPEN, "X server");
  }

  XGetPointerControl(display, &acc_num, &acc_denom, &threshold);
  FILL_ARR(str1, "%d", (110 - threshold));
  XCloseDisplay(display);
}

#endif /* WITH_MOUSE && HAVE_X11_XLIB_H */


#if WITH_NUMLOCK == 1 && defined(HAVE_X11_XLIB_H)
void
get_numlock(char *str1) {
  Display *display = XOpenDisplay(NULL);
  XKeyboardState x;

  if (NULL == display) {
    exit_with_err(CANNOT_OPEN, "X server");
  }

  XGetKeyboardControl(display, &x);
  XCloseDisplay(display);

  FILL_ARR(str1, "Num %s", (x.led_mask & 2 ? "On" : "Off"));
}

void
get_capslock(char *str1) {
  Display *display = XOpenDisplay(NULL);
  XKeyboardState x;

  if (NULL == display) {
    exit_with_err(CANNOT_OPEN, "X server");
  }

  XGetKeyboardControl(display, &x);
  XCloseDisplay(display);

  FILL_ARR(str1, "Caps %s", (x.led_mask & 1 ? "On" : "Off"));
}
#endif /* WITH_NUMLOCK && HAVE_X11_XLIB_H */

#else
char *x11;
#endif /* HAVE_X11_XLIB_H */
