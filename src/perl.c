/*
   10/07/2016

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
/* EXTERN_C void boot_Socket (pTHX_ CV* cv); */
static void xs_init (pTHX);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

EXTERN_C void
xs_init(pTHX) {
  char *file = __FILE__;
  /* DynaLoader is a special case */
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
  /* newXS("Socket::bootstrap", boot_Socket, file); */
}

void
call_user_subroutine(char *str1) {
   SV *sva = NULL;
   STRLEN len = 0;

   dSP;                            /* initialize stack pointer      */
   ENTER;                          /* everything created after here */
   SAVETMPS;                       /* ...is a temporary variable.   */

   PUSHMARK(SP);                   /* remember the stack pointer    */
   PUTBACK;                        /* make local stack pointer global */

   call_pv("uzer_func", G_SCALAR); /* call the function             */
   SPAGAIN;                        /* refresh stack pointer         */
                                 

   sva = POPs;                     /* pop the return value from stack */
   if (NULL != sva) {
    FILL_STR_ARR(1, str1, (char *)SvPV(sva, len));
   }

   PUTBACK;
   FREETMPS;                       /* free that return value        */
   LEAVE;                          /* ...and the XPUSHed "mortal" args.*/
}


void 
get_perl(char *str1) {
  const char *my_argv[] = { "", UZER_ZCRIPT };
  static PerlInterpreter *my_perl = NULL;

  PERL_SYS_INIT3((int *)NULL, (char ***)NULL, (char ***)NULL);

  my_perl = perl_alloc();
  if (NULL == (my_perl)) {
    return -1;
  }
  *str1 = '\0';

  perl_construct(my_perl);
  perl_parse(my_perl, xs_init, 2, my_argv, (char **)NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
  perl_run(my_perl);

  call_user_subroutine(str1);

  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();
}
#else
char *p3rL;
#endif /* WITH_PERL */
