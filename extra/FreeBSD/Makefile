# Created by: Aaron Caffrey
# $FreeBSD$

PORTNAME=                    pinky-bar
PORTVERSION=                 1.0.0
CATEGORIES=                  sysutils

MAINTAINER=                  wifiextender@null.horse
COMMENT=                     Gather some system information

USE_GITHUB=                  yes
GH_ACCOUNT=                  su8
GH_PROJECT=                  pinky-bar
GH_TAGNAME=                  a875ffd

GNU_CONFIGURE=               yes
USE_XORG+=                   x11
LDFLAGS+=                    -L${LOCALBASE}/lib
CFLAGS+=                     -I${LOCALBASE}/include
CONFIGURE_ARGS=              --without-pci --without-sensors --without-ncurses --without-alsa
CONFIGURE_ARGS+=             --prefix=/usr/local icons=/usr/local/share/icons/xbm_icons
CONFIGURE_ARGS+=             api_key='28459ae16e4b3a7e5628ff21f4907b6f'
LIB_DEPENDS=                 libargp.so:devel/argp-standalone
BUILD_DEPENDS=               git:devel/git tar:archivers/gtar gzip:archivers/gzip
BUILD_DEPENDS+=              gm4:devel/m4 libtool:devel/libtool autoconf:devel/autoconf 
BUILD_DEPENDS+=              automake:devel/automake

OPTIONS_DEFINE=              X11 ALSA OSS NET DVD MPD COLOURS NCURSES WEATHER PYTHON PERL RUBY LUA LISP OCAML
OPTIONS_DEFAULT=             OSS
X11_CONFIGURE_WITH=          x11 
ALSA_CONFIGURE_WITH=         alsa  
OSS_CONFIGURE_WITH=          oss
NET_CONFIGURE_WITH=          net
DVD_CONFIGURE_WITH=          dvd
MPD_CONFIGURE_WITH=          mpd
NCURSES_CONFIGURE_WITH=      ncurses
COLOURS_CONFIGURE_WITH=      colours
WEATHER_CONFIGURE_WITH=      weather
PYTHON_CONFIGURE_WITH=       python2
PERL_CONFIGURE_WITH=         perl
RUBY_CONFIGURE_WITH=         ruby
LUA_CONFIGURE_WITH=          lua
LISP_CONFIGURE_WITH=         lisp
OCAML_CONFIGURE_WITH=        ocaml

X11_DESC=                    Enable it if you are using dwm
ALSA_DESC=                   To get the sound volume level  
OSS_DESC=                    The default way to get the sound volume level
NET_DESC=                    Enable the internet related options
DVD_DESC=                    To get the cdrom/dvdrom vendor and model names
MPD_DESC=                    To see the currently played song name
NCURSES_DESC=                Output the data to the terminal using ncurses
COLOURS_DESC=                Colorize the output data
WEATHER_DESC=                Show the temperature outside
PYTHON_DESC=                 Extend the program with python
PERL_DESC=                   Extend the program with perl
RUBY_DESC=                   Extend the program with ruby
LUA_DESC=                    Extend the program with lua
LISP_DESC=                   Extend the program with lisp
OCAML_DESC=                  Extend the program with ocaml

X11_LIB_DEPENDS=             libX11.so:x11/xorg
ALSA_LIB_DEPENDS=            libasound.so:audio/alsa-lib
DVD_LIB_DEPENDS=             libcdio.so:sysutils/libcdio libcddb.so:audio/libcddb
NCURSES_LIB_DEPENDS=         libncurses.so:devel/ncurses
MPD_LIB_DEPENDS=             libmpdclient.so:audio/libmpdclient
WEATHER_LIB_DEPENDS=         libcurl.so:ftp/curl

.include <bsd.port.mk>
