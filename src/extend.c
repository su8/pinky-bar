/*
   10/24/2016

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

#include "include/headers.h"

#if WITH_PYTHON == 1
#include <Python.h>
#endif /* WITH_PYTHON */

#if WITH_ECL == 1
#include <ecl/ecl.h>
#endif /* WITH_ECL */

#if WITH_LUA == 1
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#endif /* WITH_LUA */

#if WITH_OCAML == 1
#include <caml/alloc.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#endif /* WITH_OCAML */

#if WITH_PERL == 1
#include <EXTERN.h>
#include <perl.h>
#endif /* WITH_PERL */

#if WITH_R == 1
#include <Rinternals.h>
#include <Rembedded.h>
#endif /* WITH_R */

#if WITH_RUBY == 1
#include <ruby.h>
#endif /* WITH_RUBY */

#if WITH_SLANG == 1
#include <slang.h>
#endif /* WITH_SLANG */

#if WITH_TCL == 1
#include <tcl.h>
#endif /* WITH_TCL */

#include "prototypes/extend.h"

#if WITH_PYTHON == 1
/*
 * Huge thanks to:
 *  https://wiki.blender.org/index.php/Dev:2.5/Source/Python/API/Py3.1_Migration
*/
void
get_python(char *str1, char *str2) {
  PyObject *pName = NULL, *pModule = NULL;
  PyObject *pFunc = NULL, *pValue = NULL;

  FILL_STR_ARR(1, str1, "0");
  if (NULL == (char *)Py_GetPath()) {
    return;
  }

  Py_Initialize();

#if WITH_PYTHON2 == 1
  pName = PyString_FromString(str2);
#else
  pName = PyUnicode_DecodeFSDefault(str2);
#endif /* WITH_PYTHON2 */

  if (NULL == pName) {
    goto error;
  }

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);
  if (NULL == pModule) {
    goto error;
  }

  pFunc = PyObject_GetAttrString(pModule, (char *)"uzer_func");
  if (NULL == pFunc || 0 == PyCallable_Check(pFunc)) {
    goto error;
  }

  pValue = PyObject_CallObject(pFunc, NULL);
  if (NULL != pValue) {
    FILL_STR_ARR(1, str1, RET_PY_STR(pValue));
  }

error:
  if (NULL != pValue) {
    Py_XDECREF(pValue);
  }
  if (NULL != pFunc) {
    Py_XDECREF(pFunc);
  }
  if (NULL != pModule) {
    Py_XDECREF(pModule);
  }

  Py_Finalize();
  return;
}
#else
char *py7h0n;
#endif /* WITH_PYTHON */


/* Based on:
 *  https://gist.github.com/vwood/662109
 *  https://stackoverflow.com/questions/41915795/getting-ecl-symbol-name-as-string-in-c */
#if WITH_ECL == 1
static cl_object ecl_call(char *);

static cl_object
ecl_call(char *call) {
  return cl_safe_eval(c_string_to_object(call), Cnil, Cnil);
}

void
get_ecl(char *str1, char *str2) {
  char temp[VLA], *temp2[] = { (char *)"pinkybar" };

  cl_boot(1, temp2);

  FILL_ARR(temp, "(load \"%s\")", str2);
  ecl_call(temp);

  cl_object from_str = ecl_call((char *)"(uzer_func1)");
  ecl_base_char *to_str = from_str->base_string.self;

  FILL_STR_ARR(1, str1, to_str);
  cl_shutdown();
}
#endif /* WITH_ECL */


#if WITH_GO == 1
void
get_go(char *str1) {
  char *str = uzer_func4();
  FILL_STR_ARR(1, str1, str);
  Gfree(str);
}
#endif /* WITH_GO */


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
#endif /* WITH_LUA */


#if WITH_OCAML == 1
/* Based on: 
 *  https://github.com/gmcabrita/embed-ocaml-c */
void
get_ocaml(char *str1) {
  char *dummy[] = {(char *)"pinkybar", NULL};

  caml_startup(dummy);
  CAMLparam0();
  CAMLlocal1(res);

  value *func = caml_named_value("uzer_func");
  if (NULL == func) {
    FILL_STR_ARR(1, str1, "0");
    return;
  }

  res = caml_callback(*func, Val_unit);
  FILL_STR_ARR(1, str1, String_val(res));
}
#endif /* WITH_OCAML */


#if WITH_PERL == 1
static void xs_init(pTHX);
static void call_user_subroutine(char *);
extern void boot_DynaLoader(pTHX_ CV* cv);

/* Update with:
 *  perl -MExtUtils::Embed -e xsinit -- -o sample.c
*/
static void
xs_init(pTHX) {
  static const char file[] = __FILE__;
  dXSUB_SYS;
  PERL_UNUSED_CONTEXT;
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

static void
call_user_subroutine(char *str1) {
  SV *sva = NULL;
  STRLEN len = 0;
  int count = 0;

  dSP;                            /* initialize stack pointer      */
  ENTER;                          /* everything created after here */
  SAVETMPS;                       /* ...is a temporary variable.   */

  PUSHMARK(SP);                   /* remember the stack pointer    */
  PUTBACK;                        /* make local stack pointer global */

  count = call_pv("uzer_func", G_SCALAR); /* call the function      */
  SPAGAIN;                        /* refresh stack pointer         */

  if (1 == count) {               /* the Adder returned 1 item */
    sva = POPs;                   /* pop the return value from stack */
    if (NULL != sva) {
      FILL_STR_ARR(1, str1, (char *)SvPV(sva, len)); /* SvPVutf8 needs some testing */
    }
  }

  PUTBACK;                        /* leave the Perl stack in a consistent state */
  FREETMPS;                       /* free that return value        */
  LEAVE;                          /* ...and the XPUSHed "mortal" args.*/
}


/* Docs:
 *  http://perldoc.perl.org/perlembed.html
 *  http://perldoc.perl.org/perlcall.html
 *  http://docstore.mik.ua/orelly/perl/prog3/ch21_04.htm
 */
void 
get_perl(char *str1, char *str2) {
  /* The 4th arg to perl_parse is not const */
  char *my_argv[] = { (char *)"", str2 };
  static PerlInterpreter *my_perl = NULL;
  int status = 0;

  FILL_STR_ARR(1, str1, "0");
  PERL_SYS_INIT3((int *)NULL, (char ***)NULL, (char ***)NULL);

  my_perl = perl_alloc();
  if (NULL == my_perl) {
    PERL_SYS_TERM();
    return;
  }

  perl_construct(my_perl);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  status = perl_parse(my_perl, xs_init, 2, my_argv, (char **)NULL);
  if (0 != status) {
    goto error;
  }

  status = perl_run(my_perl);
  if (0 != status) {
    goto error;
  }
  call_user_subroutine(str1);

error:
  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();
  return;
}
#endif /* WITH_PERL */


/* Based on:
 * https://github.com/parkerabercrombie/call-r-from-c */
#if WITH_R == 1
void
get_r(char *str1, char *str2) {
  SEXP env, strret, add1_call;
  char *r_argv[] = { (char *)"R", (char *)"--silent" };

  Rf_initEmbeddedR(2, r_argv);

  PROTECT(env = lang2(install("source"), mkString(str2)));
  R_tryEval(env, R_GlobalEnv, NULL);
  UNPROTECT(1);

  PROTECT(add1_call = lang1(install("uzer_func")));
  strret = R_tryEval(add1_call, R_GlobalEnv, NULL);

  FILL_STR_ARR(1, str1, CHAR(STRING_ELT(strret,0)));

  UNPROTECT(2);
  Rf_endEmbeddedR(0);
}
#endif /* WITH_R */


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
#endif /* WITH_RUBY */


#if WITH_RUST == 1
extern char *uzer_func(void);
extern void Rfree(char *);

void
get_rust(char *str1) {
  char *str = uzer_func2();
  FILL_STR_ARR(1, str1, str);
  Rfree(str);
}
#endif /* WITH_RUST */


#if WITH_SLANG == 1
/* Used the following sources:
    https://sourceforge.net/p/unicon/discussion/contributions/thread/3f579d7b/c494/attachment/slang.c
    http://www.jedsoft.org/slang/doc/pdf/cslang.pdf
    http://www.jedsoft.org/slang/doc/html/cref-5.html
*/
void
get_slang(char *str1, char *str2) {
  char *src = NULL;

  FILL_STR_ARR(1, str1, "0");

  if (-1 == SLang_init_slang())
    return;

  if (-1 == SLang_load_file(str2)) {
    SLang_restart(1);
  }

  if (-1 == SLang_load_string((char *)"uzer_function")) {
    return;
  }

  if (SLANG_STRING_TYPE == SLang_peek_at_stack()) {
    if (-1 == SLpop_string(&src)) {
      return;
    }
    FILL_STR_ARR(1, str1, src);
    SLfree(src);
  }
}
#endif /* WITH_SLANG */


#if WITH_TCL == 1
/* Tcl_VarEval based on:
 * https://github.com/zacheryph/examples/blob/master/c-cpp/tcl/example_tcl.c */
void
get_tcl(char *str1, char *str2) {
  Tcl_Interp *interp = NULL;
  int x = 0;

  FILL_STR_ARR(1, str1, "0");

  interp = Tcl_CreateInterp();
  Tcl_Init(interp);

  Tcl_EvalFile(interp, str2);

  x = Tcl_VarEval(interp, (char *)"uzer_func", NULL, 0);
  if (TCL_ERROR == x) {
    return;
  }

  FILL_STR_ARR(1, str1, Tcl_GetStringResult(interp));
}
#endif /* WITH_TCL */


#if WITH_ASSEMBLY == 1
void
get_assembly(char *str1) {
  FILL_STR_ARR(1, str1, uzer_func3());
}
#endif /* WITH_ASSEMBLY */
