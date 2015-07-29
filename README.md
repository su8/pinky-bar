## dwm-bar.c
<img src="img/pic.png" alt="" />

Statusbar program for dwm that I've written in my very first day as dwm user.

Please note that the program won't detect fans connected via molex connetor(s) or external fan controller. Also I have not tested it with fan splitter(s) either.

The program is smart enough to detect whether some of your fan(s) blades are spinning, or the particular fan have been removed. Hold down some of your fan blades and you'll see that the program won't include this fan and it's RPM, release the blades and you'll see the fan and it's RPM in the statusbar.

## Installation

    bash bootstrap distro
    ./configure --prefix=$HOME/.cache
    make && make install

Replace **distro** with:

- [x] archlinux
- [x] fedora
- [x] linuxmint
- [x] lmde
- [x] ubuntu/lubuntu/xubuntu
- [x] fedora
- [x] debian
- [x] crunchbang
- [x] gentoo
- [x] funtoo
- [x] opensuse
- [x] mandriva/mandrake
- [x] slackware
- [x] rhel
- [x] frugalware
- [x] peppermint
- [x] solusos
- [x] mageia
- [x] parabola
- [x] viperr
- [x] linuxdeepin
- [x] chakra
- [x] fuduntu
- [x] trisquel
- [x] manjaro
- [x] elementary
- [x] backtrack
- [x] kali
- [x] sabayon
- [x] angstrom

## Requirements

* gcc/clang
* glibc
* autoconf
* automake
* m4
* gawk
* alsa-utils
* alsa-lib
* libx11
* xorg-server
* dwm compiled with [statuscolor](https://github.com/wifiextender/dwm-fork/blob/master/patches/statuscolours.diff) patch. The colors in use are specified in your [config.h](https://github.com/wifiextender/dwm-fork/blob/master/config.h#L6)

## Now what ?

Take a look in my [xinitrc](https://github.com/wifiextender/dotfiles/blob/master/archlinux-openbsd/home/frost/.config/misc/xinitrc) and [dwm-start](https://github.com/wifiextender/dotfiles/blob/master/archlinux-openbsd/home/frost/.config/dwm_scripts/dwm-start).
