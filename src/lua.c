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

#if WITH_LUA == 1

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "include/headers.h"

#endif /* WITH_LUA */

#include "prototypes/lua.h"

#if WITH_LUA == 1
/*
 Docs:
  http://www.lua.org/manual/
  http://www.dcc.ufrj.br/~fabiom/lua/

 Books:
  http://www.lua.org/pil/index.html

 The first edition is free to be read:
  http://www.lua.org/pil/contents.html

 "isfunction":
  http://www.lua.org/pil/25.3.html
*/
void
get_lua(char *str1, char *str2) {
  const char *temp = NULL;
  lua_State *L = NULL;

  FILL_STR_ARR(1, str1, "0");

#if LUA_VERSION_NUM < 501 
  if (NULL == (L = lua_open())) {
    return;
  }
#else
  if (NULL == (L = luaL_newstate())) {
    return;
  }
#endif /* LUA_VERSION_NUM < 501 */

  luaL_openlibs(L);
  if (0 != (luaL_loadfile(L, str2))) {
    goto error;
  }

  if (0 != (lua_pcall(L, 0, 0, 0))) {
    goto error;
  }

  lua_getglobal(L, "uzer_func");
  if (0 != (lua_pcall(L, 0, 1, 0))) {
    goto error;
  }

  if (NULL != (temp = lua_tostring(L, -1))) {
    FILL_STR_ARR(1, str1, temp);
  }

error:
  if (NULL != L) {
    lua_pop(L, 1);
    lua_close(L);
  }
  return;
}
#else
char *lua5;
#endif /* WITH_LUA */
