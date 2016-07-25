dwm

![](img/pic.png)

xmonad

![](img/pic2.png)

With MPD

![](img/pic3.png)

Statusbar program for anything (Window Manager, terminal multiplexer, etc..) that I've written in my very first day as dwm user.

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

To see the currently played song name add **--with-mpd** to configure.

To disable the colours you can add **--without-colours** to configure.

Put the following in your **xinitrc** or the script used to start dwm.

```bash
# Execute the "statusbar" program every 5 secs
while true; do
  # short program options   crspkvfmVt
  "$HOME/.cache/bin/dwmbar" --cpu --ram --storage --packages --kernel --voltage --fans --mobo --volume --time
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

To see the currently played song name add **--with-mpd** to configure.

Put the following in your **xinitrc** or the script used to start xmonad.

```bash
# Execute the "statusbar" program every 2 secs
while true; do
  # short program options   crspkvfmVt
  "$HOME/.cache/bin/xmonadbar" --cpu --ram --storage --packages --kernel --voltage --fans --mobo --volume --time
  sleep 2
done | dzen2 -w 1800 -x 130 -ta r -fn '-*-dejavusans-*-r-*-*-11-*-*-*-*-*-*-*' &
```

## Installation for anything else

pinky-bar is no longer tied to Window Managers only. With the addition of "without colours", the output can be shown in any program, just bear in mind that the more options you've supplied the more system information will be shown.

![](img/pic4.png)

Here's the Installation steps:

```bash
bash bootstrap distro
./configure --prefix=$HOME/.cache --without-x11 --without-colours
make -j$(grep -c '^processor' /proc/cpuinfo)
make install
```

Will mention that you can add **--with-mpd** too, but scroll a few lines up, re-read **Installation for anything else** and see the tmux snapshot.

Choosing this 3rd method of installation it is up to you where, how to start and use the system information that's produced by pinky-bar.

---

Replace **distro** with archlinux, debian, gentoo, slackware, rhel, frugalware, angstrom. Here's some short distros list of some popular distros that are based on another one:

- [x] archlinux based distros: parabola, chakra, manjaro
- [x] debian based distros: ubuntu, linux mint, trisquel, back track, kali linux, peppermint linux, solusos, crunchbang, deepin, elementary os, and the rest \*buntu based distros
- [x] gentoo based distros: funtoo, sabayon, calculate linux
- [x] slackware
- [x] rhel based distros: opensuse (uses rpm), fedora, fuduntu, mandriva, mandrake, viperr, mageia
- [x] frugalware
- [x] angstrom

## Mandatory requirements

* gcc/clang
* glibc
* autoconf
* automake
* m4
* gawk
* alsa-utils
* alsa-lib

## Opt-in requirements

To see the currently played song name:

* libmpdclient
* mpd (with properly configured config)

Here's an example of my **/etc/mpd.conf**

```nginx
music_directory "/home/frost/music"
playlist_directory "/home/frost/music"
db_file "/tmp/mpddb"
log_file "/tmp/mpdlog"
state_file "/tmp/mpdstate"
pid_file "/tmp/mpdpid"
user "mpd"
log_level "default"


audio_output {
  type "alsa"
  name "My sound card"
  mixer_type "software"
}

audio_output {
  type "httpd"
  name "HTTP Stream"
  encoder "vorbis"
  port "8000"
  bitrate "128"
  format "44100:16:1"
}

bind_to_address "127.0.0.1"
```

Keep an eye on the **log file size** if you are using raspberry pi (or equivalent device) that streams the music, make sure that it's deleted automatically if it exceeds some pre-defined size.

---

## WM specific requirements

If you would like the output to be shown in your Window Manager, those are the following requirements:

for non-dwm WM:

* dzen2

for dwm:

* libx11
* xorg-server

use **--without-colours** to skip the following step:

* dwm compiled with [statuscolor](https://github.com/wifiextender/dwm-fork/blob/master/patches/statuscolours.diff) patch. The colours in use are specified in your [config.h](https://github.com/wifiextender/dwm-fork/blob/master/config.h#L6)

---

## Want xinitrc template ?

Take a look in my [xinitrc](https://github.com/wifiextender/dotfiles/blob/master/gentoo/home/frost/.config/misc/xinitrc) and [dwm-start](https://github.com/wifiextender/dotfiles/blob/master/gentoo/home/frost/.config/dwm_scripts/dwm-start).
