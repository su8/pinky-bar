/*
   09/03/2016

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
#include <stdint.h>
#include <ctype.h>

#include <unistd.h>
#include <signal.h>

#include <ncurses.h>

#define VLA 1000

void unuglify(char *);
void sighandler(int num);

void sighandler(int num) {
  endwin();
  fprintf(stderr, "\n%s\n", "See you later");
  exit(EXIT_FAILURE);
}

void unuglify(char *str1) {
  WINDOW *win = stdscr;
  uint8_t iclr = 0;
  char *ptr = str1, cclr[1];

  wmove(win, 0, 0);
  wclrtoeol(win);

  for (; *ptr; ptr++) {
    if ('&' == *ptr)  {
      cclr[0] = *(++ptr);
      switch(toupper((unsigned char) *ptr)) {
        case 'B':
          iclr = COLOR_BLUE;
          break;
        case 'M':
          iclr = COLOR_MAGENTA;
          break;
        case 'Y':
          iclr = COLOR_YELLOW;
          break;
        default:
          waddch(win, (chtype)cclr[0]);
          break;
      }
      wattrset(win, COLOR_PAIR(COLORS + iclr + 8));  /* | A_BOLD */
    } else {
      waddch(win, (chtype)*ptr);
    }
  }
  wrefresh(win);
}

int main(void) {
  signal(SIGINT, sighandler);

  WINDOW *win = stdscr;
  int16_t color_pair = 1, fg = 1, bg = 1, x = 0, z = 0;
  int32_t old_x = 0, old_y = 0, new_y = 0, new_x = 0;
  char buf[VLA];

  initscr();
  noecho();
  nocbreak();
  nodelay(win, TRUE);
  nonl();
  intrflush(win, FALSE);
  curs_set(FALSE);

  if(FALSE == (has_colors())) {
    endwin();
    return EXIT_FAILURE;
  }
  start_color();
  for (x = 0; x < COLORS; x++ ) {
    for (z = 0; z < COLORS; z++ ) {
      init_pair((x * COLORS) + z, x, z);
    }
  }
  pair_content(color_pair, &fg, &bg);
  getmaxyx(win, old_y, old_x);

  while (1) {
    getmaxyx(win, new_y, new_x);
    if (old_y != new_y || old_x != new_x) {
      old_y = new_y;
      old_x = new_x;
      werase(win);
      wrefresh(win);
    }
    if (NULL != (fgets(buf, VLA, stdin))) {
      unuglify(buf);
    }
  }
  endwin();
  return EXIT_SUCCESS;
}
