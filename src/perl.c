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

#if WITH_PERL == 1

#include <EXTERN.h>
#include <perl.h>

#include "include/headers.h"

#endif /* WITH_PERL */

#include "prototypes/perl.h"

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
#else
char *p3rL;
#endif /* WITH_PERL */
