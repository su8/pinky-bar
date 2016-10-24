dnl 10/24/2016

dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
dnl MA 02110-1301, USA.

dnl TEST_PERL() function in configure.ac
dnl
dnl Substitute perl related linker and
dnl cflags to the variables PERL_CF and
dnl PERL_LZ if the user enabled the
dnl --with-perl switch
AC_DEFUN([TEST_PERL],[
  PERL_LZ=""
  PERL_CF=""
  WITH_PERL=0
  UZER_ZCRIPT=""

  AC_ARG_WITH([perl],
    AS_HELP_STRING([--with-perl],
      [Extend the program via perl scripts]),
    [],
    [with_perl=no]
  )

  AS_IF([test "x$with_perl" = "xyes"], [
    CHECK_CFLAGZ([-O0])
    AC_PATH_PROG(PERL, perl)

    PERL_LZ=`$PERL -MExtUtils::Embed -e ldopts`
    PERL_CF=`$PERL -MExtUtils::Embed -e ccopts`

    AC_ARG_VAR(perl_script, [user perl script])
    if [[ ! -z "${perl_script}" ]]
    then
      UZER_ZCRIPT=\""${perl_script}"\"
    fi

    WITH_PERL=1
  ])

  AC_SUBST(PERL_LZ)
  AC_SUBST(PERL_CF)
  AC_DEFINE_UNQUOTED([WITH_PERL],[$WITH_PERL],[Extend the program via perl scripts])
  AC_DEFINE_UNQUOTED([UZER_ZCRIPT],[$UZER_ZCRIPT],[Extend the program via perl scripts])

])


dnl TEST_python() function in configure.ac
dnl
dnl Substitute python related linker and
dnl cflags to the variables PYTHON_CF and
dnl PYTHON_LZ if the user enabled the
dnl --with-python switch
AC_DEFUN([TEST_PYTHON],[
  PYTHON_LZ=""
  PYTHON_CF=""
  WITH_PYTHON=0
  UZER_ZCRIPT2=""
  UZER_PAHT=""

  AC_ARG_WITH([python],
    AS_HELP_STRING([--with-python],
      [Extend the program via python scripts]),
    [],
    [with_python=no]
  )

  AS_IF([test "x$with_python" = "xyes"], [
    CHECK_CFLAGZ([-O0])
    AC_PATH_PROG(PYFON, python-config-2.7)

    PYTHON_LZ=`$PYFON --ldflags`
    PYTHON_CF=`$PYFON --cflags`

    AC_ARG_VAR(python_script, [user python script])
    if [[ ! -z "${python_script}" ]]
    then
      dnl  ... PYTHONPATH ...
      modulez_paht=`python2 -c 'import sys;print(":".join([x for x in sys.path]))'`

      just_script="${python_script##*/}"
      UZER_ZCRIPT2=\""${just_script%.*}"\"
      UZER_PAHT=\""${python_script%/*}${modulez_paht}"\"
    fi

    WITH_PYTHON=1
  ])

  AC_SUBST(PYTHON_LZ)
  AC_SUBST(PYTHON_CF)
  AC_DEFINE_UNQUOTED([WITH_PYTHON],[$WITH_PYTHON],[Extend the program via python scripts])
  AC_DEFINE_UNQUOTED([UZER_ZCRIPT2],[$UZER_ZCRIPT2],[Extend the program via python scripts])
  AC_DEFINE_UNQUOTED([UZER_PAHT],[$UZER_PAHT],[Extend the program via python scripts])

])
