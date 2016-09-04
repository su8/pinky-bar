dnl 08/03/2016

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


dnl Internal function to show
dnl error message when smth is wrong
AC_DEFUN([ERR],[
  AC_MSG_ERROR($1)
])

dnl Internal function to show what have to
dnl be installed in order to compile the program.
AC_DEFUN([ERR_MUST_INSTALL],[
  ERR([Install $1 in order to compile the program.])
])

dnl Internal function to show error msg when
dnl compiling and linking some of tests failed
AC_DEFUN([LINK_FAILED], [
  ERR([Failed to compile and link the $1 test.])
])

dnl Internal function to show error msg when
dnl compiling some of tests failed
AC_DEFUN([COMPILE_FAILED], [
  ERR([Failed to compile the $1 test.])
])
