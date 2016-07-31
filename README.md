dwm

![](img/pic.png)

xmonad

![](img/pic2.png)

With MPD

![](img/pic3.png)

Gather some system information and show it in this statusbar program, not tied to any Window Manager, terminal multiplexer, etc.

Please note that the program won't detect fans connected via molex connetor(s) or external fan controller. Also I have not tested it with fan splitter(s) either.

The program is smart enough to detect whether some of your fan(s) blades are spinning, or the particular fan have been removed. Hold down some of your fan blades and you'll see that the program won't include this fan and it's RPM, release the blades and you'll see the fan and it's RPM in the statusbar. Try simulating real fan hardware failure by holding down all system fan blades and watch what the program will show you.

If you compile your kernel from source code make sure to include your cpu and motherboard sensors as **modules** and not inlined.

![](img/cpu-temp.png)
![](img/mobo-temp.png)

---

## Bandwidth measurment

pinky-bar supplies bandwitdh/network throughput measurment to satisfy those users that pay for overpriced 3G/mobile internet, and want to monitor every single megabit/megabyte.

## Program options

The order of supplied options will dictate how, where and what system information to be shown.

| short option | long option | Descrtiption                                                       |
|--------------|-------------|--------------------------------------------------------------------|
| -M           | --mpd       | The currently played song name (if any)                            |
| -c           | --cpu       | The current cpu load and temperature                               |
| -C           | --cpuspeed  | Show your maximum cpu clock speed in MHz, regardless of the used governor |
| -I           | --cpuinfo   | Detect your CPU vendor, stepping and family from low level assembly access |
| -r           | --ram       | The used ram                                                       |
| -s           | --storage   | The used drive storage                                             |
| -p           | --packages  | The number of installed packages                                   |
| -k           | --kernel    | The kernel version                                                 |
| -v           | --voltage   | The system voltage                                                 |
| -f           | --fans      | All system fans and their speed in RPM                             |
| -m           | --mobo      | Show the motherboard name, vendor and temperature                  |
| -V           | --volume    | The volume                                                         |
| -t           | --time      | The current time                                                   |
| -b           | --bandwitdh | The consumed internet bandwidth so far [argument - eth0]           |
| -i           | --iface     | The current download and upload speed [argument - eth0]            |
| -S           | --statio    | Read and written MBs to the drive so far [argument - sda]          |

---

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
  # scroll a few lines up to see the rest options
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
  # scroll a few lines up to see the rest options
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

By choosing this 3rd installation method it is up to you where, how to start and use the system information that's produced by pinky-bar.

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

## Wish list

With the help from the gcc documentation, this wish list option has been solved.

~~Per core/thread CPU frequency detection: Can add it at any time if there is enough demand, but needs some consideration first.~~

~~The kernels cpu frequency governor "performance" will always run at the highest possible clock rate regardless of it's use/idle. The only side effect of this is higher temps when on idle (true if the cpu has multiple cores and or threads).~~

~~The "powersaving" governor will always run at the lowest possible clock rate regardless of it's use/idle. The side effect - slower machine no matter what you do.~~

~~The "ondemand" governor does what it says - ondemand scaling. With it you get the best performance when you need to, powersaving and lower temps when on idle.~~

~~For example I manually turn off the cpu frequency governor in my kernel builds, which sets it to performance.~~

~~The cpu frequency detection is easy, but it poses a roadblock by assuming that the "ondemand" is set and/or is enabled in the user kernel.~~

~~Decision 1: On a multicore/thread cpu, the detection for each core/thread will produce up to 8 digit number, thus 4 core and 4 thread cpu will produce: 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678, without including MHz for each core/thread, which will take a lot of space in the final statusbar output. This way the user will know for how long and which core/thread is under some load.~~

~~Decision 2: On other hand it will be lame on a 10/16 core/thread system to show the overall (not per core/thread) cpu frequency that have been summed up, which will beat the purpose of cpu frequency detection in first place, as the user will not be aware that some core/thread is running at full cpu clock speed as the load will be spread equally when summing the numbers up.~~

---

GPU temperature, voltage, fan(s) and used RAM: hard, but not impossible.

It would be nice to have decent gpu temperature, voltage, fan(s) speed and used RAM detection. Should we detect multiple gpus (SLI,single dual gpu card), how to detect which of the multiple gpu cards is actually the one used for **this** monitor in case the program is compiled **--without-x11** and/or xinerama ? What about hybrid combination and some gpu manufactor that is not supported by MESA ? My legacy gpu only shows it's vendor name, model and used ram (in MESA) because it's onboard gpu.

---

[Currently played filename in VLC](https://github.com/videolan/vlc/blob/master/src/libvlc.c): easy to be added.

Unless MPRIS is replaced with sockets, I am not willing to add dbus as dependency to pinky-bar.

```cpp
// The "MPRIS_BUS_NAME" macro from libvlc
dbus_message_new_method_call(
  "org.mpris.MediaPlayer2.vlc",
  "/org/mpris/MediaPlayer2",
  "org.mpris.MediaPlayer2.Player",
  "Metadata");
// results in:  'xesam:url': <'file:///home/frost/music/Summer_Sixteen.mp3'> 
```

---

## Want xinitrc template ?

Take a look in my [xinitrc](https://github.com/wifiextender/dotfiles/blob/master/gentoo/home/frost/.config/misc/xinitrc) and [dwm-start](https://github.com/wifiextender/dotfiles/blob/master/gentoo/home/frost/.config/dwm_scripts/dwm-start).
