# Author: Aaron Caffrey
# TEST_TYPEZ() function in configure.ac
#
# Check for the presence of all used
# library functions, their header files
# and some int types
AC_DEFUN([TEST_TYPEZ],
[

  AC_TYPE_SIZE_T
  AC_TYPE_INT8_T
  AC_TYPE_INT16_T
  AC_TYPE_INT32_T
  AC_TYPE_INT64_T
  AC_TYPE_INTMAX_T
  AC_TYPE_UINT8_T
  AC_TYPE_UINT16_T
  AC_TYPE_UINT32_T
  AC_TYPE_UINT64_T
  AC_TYPE_UINTMAX_T

  AC_CHECK_HEADERS([time.h stdio.h stdbool.h])
  AC_CHECK_HEADERS([string.h inttypes.h glob.h])
  AC_CHECK_HEADERS([sys/statvfs.h sys/sysinfo.h])
  AC_CHECK_HEADERS([sys/utsname.h unistd.h])

  AC_CHECK_FUNCS([memset printf snprintf])
  AC_CHECK_FUNCS([nanosleep sysconf sysinfo])
  AC_CHECK_FUNCS([strcmp fscanf fclose])
  AC_CHECK_FUNCS([fopen statvfs getenv])
  AC_CHECK_FUNCS([glob globfree popen])
  AC_CHECK_FUNCS([uname strftime])

])
