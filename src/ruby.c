/*
   11/18/2016

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

#include "config.h" /* Auto-generated */

#if WITH_RUBY == 1

#include <ruby.h>
#include "include/headers.h"

#endif /* WITH_RUBY */

#include "prototypes/ruby.h"

#if WITH_RUBY == 1
static VALUE catch_snap(VALUE dummy);

static VALUE catch_snap(VALUE dummy) {
  (void)dummy;
  VALUE obj = rb_funcall(rb_gv_get("$!"), rb_intern("uzer_func"), 0);

  return obj;
}

/*
  Docs:
   https://silverhammermba.github.io/emberb/c/

  Other resources that helped me:
   https://www.ruby-forum.com/topic/184811  
   https://opensource.apple.com/source/vim/vim-6/vim/src/if_ruby.c
*/
void
get_ruby(char *str1, char *str2) {
  int status = 0, state = 0;

  FILL_STR_ARR(1, str1, "0");

  ruby_init();
  ruby_init_loadpath();

  VALUE src = rb_str_new_cstr(str2), obj;
  rb_load_protect(src, 0, &status);

  if (0 == status) {
    obj = rb_protect(catch_snap, (VALUE)"dummy", &state);
    if (0 == state) {
      if (T_STRING == (TYPE(obj))) {
        FILL_STR_ARR(1, str1, (StringValuePtr(obj)));
      }
    }
  }
  ruby_cleanup(0);
}
#else
char *ruby6;
#endif /* WITH_RUBY */
