# Author: Aaron Caffrey
# TEST_ALSA() function in configure.ac
#
# Check for the presence of ALSA headers and
# substitute the linker flags -lasound to the
# the variable 'ALSA_LIBS' if they are available.
AC_DEFUN([TEST_ALSA],
[
  ALSA_LIBS=""
  ALSA_here="no"

  AC_CHECK_HEADERS([alsa/asoundlib.h], [
    ALSA_LIBS="-lasound"
    ALSA_here="yes"
    AC_SUBST(ALSA_LIBS)
  ])


  if [[ "${ALSA_here}" == "no" ]]
  then
    AC_MSG_ERROR([Install alsa-utils and alsa-lib in order to compile the program.])
  fi

])
