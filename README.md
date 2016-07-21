![](img/pic.png)
![](img/pic2.png)

Statusbar program for ~~dwm and xmonad~~ any WM that I've written in my very first day as dwm user.

Please note that the program won't detect fans connected via molex connetor(s) or external fan controller. Also I have not tested it with fan splitter(s) either.

The program is smart enough to detect whether some of your fan(s) blades are spinning, or the particular fan have been removed. Hold down some of your fan blades and you'll see that the program won't include this fan and it's RPM, release the blades and you'll see the fan and it's RPM in the statusbar. Try simulating real fan hardware failure by holding down all system fan blades and watch what the program will show you.

If you compile your kernel from source code make sure to include your cpu and motherboard sensors as **modules** and not inlined.

![](img/cpu-temp.png)
![](img/mobo-temp.png)

## Installation for dwm

```bash
bash bootstrap distro
./configure --prefix=$HOME/.cache --with-x11
make -j$(grep -c '^processor' /proc/cpuinfo)
make install
```

Put the following in your **xinitrc** or the script used to start dwm.

```bash
# Execute the "statusbar" program every 5 secs
while true; do
  "$HOME/.cache/bin/dwmbar"
  sleep 5
done &
```

## installation for xmonad (or other WM)

```bash
# Copy the xbm icons
mkdir -p --mode=700 $HOME/.xmonad/icons
cp -r xbm_icons/*.xbm $HOME/.xmonad/icons

# rename the program
sed -i 's/dwmbar/xmonadbar/g' bootstrap

bash bootstrap distro

# disable X11, point the location to the icons
./configure --prefix=$HOME/.cache --without-x11 icons=$HOME/.xmonad/icons

# compile 'n install
make -j$(grep -c '^processor' /proc/cpuinfo)
make install
```

Put the following in your **xinitrc** or the script used to start xmonad.

```bash
# Execute the "statusbar" program every 2 secs
while true; do
  "$HOME/.cache/bin/xmonadbar"
  sleep 2
done | dzen2 -w 1800 -x 130 -ta r -fn '-*-dejavusans-*-r-*-*-11-*-*-*-*-*-*-*' &
```

---

Replace **distro** with archlinux, debian, gentoo, slackware, rhel, frugalware, angstrom. Here's some short distros list of some popular distros that are based on another one:

- [x] archlinux based distros: parabola, chakra, manjaro
- [x] debian based distros: ubuntu, linux mint, trisquel, back track, kali linux, peppermint linux, solusos, crunchbang, deepin, elementary os, and the rest \*buntu based distros
- [x] gentoo based distros: funtoo, sabayon, calculate linux
- [x] slackware
- [x] rhel based distros: opensuse (uses rpm), fedora, fuduntu, mandriva, mandrake, viperr, mageia
- [x] frugalware
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

requirements for xmonad or other non-dwm WM:

* dzen2

dwm specific requirements:

* libx11
* xorg-server
* dwm compiled with [statuscolor](https://github.com/wifiextender/dwm-fork/blob/master/patches/statuscolours.diff) patch. The colors in use are specified in your [config.h](https://github.com/wifiextender/dwm-fork/blob/master/config.h#L6)

## Want xinitrc template ?

Take a look in my [xinitrc](https://github.com/wifiextender/dotfiles/blob/master/gentoo/home/frost/.config/misc/xinitrc) and [dwm-start](https://github.com/wifiextender/dotfiles/blob/master/gentoo/home/frost/.config/dwm_scripts/dwm-start).
