# Author: Aaron Caffrey
# TEST_X11() function in configure.ac
#
# Check for the presence of X11 headers and
# substitute the linker flags -lX11 to the
# the variable 'X_LIBS' if they are available.
AC_DEFUN([TEST_X11],
[
  X_LIBS=""
  xorg_here="no"

  AC_CHECK_HEADERS([X11/Xlib.h], [
    X_LIBS="-lX11"
    xorg_here="yes"
    AC_SUBST(X_LIBS)
  ])


  if [[ "${xorg_here}" == "no" ]]
  then
    AC_MSG_ERROR([Install xorg and libx11 in order to compile the program.])
  fi

])
