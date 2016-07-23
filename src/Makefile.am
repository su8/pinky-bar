AM_CPPFLAGS = \
      -D_POSIX_C_SOURCE=200112L \
      -DICONS_DIR=\"$(ICONZ)\" \
      -DWITH_COLOURS=$(WITH_COLOURS) \
      -DDISTRO=2 \
      -DARCHLINUX=0 -DDEBIAN=1 -DGENTOO=2 -DSLACKWARE=3 -DRHEL=4 -DFRUGALWARE=5 -DANGSTROM=6

  bin_PROGRAMS = \
    dwmbar

  # clang will not append std=bar
  # on its own which gcc does
  dwmbar_CFLAGS = \
    -O2 -std=c99 -Wextra -Wall -pedantic -Wundef -Wshadow \
    -w -Wwrite-strings -Wcast-align -Wstrict-overflow=5 \
    -Wconversion -Wpointer-arith -Wstrict-prototypes \
    -Wformat=0 -Wmissing-prototypes -Wno-unused-result \
    -Wno-unused-function -Wno-missing-field-initializers

  dwmbar_LDADD = $(X_LIBS) $(ALSA_LIBS) $(MPD_LIBS)

  dwmbar_SOURCES = main.c functions.c functions.h main_constants.h functions_constants.h
  
