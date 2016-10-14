dwm

![](img/pic.png)

xmonad

![](img/pic5.png)

![](img/pic7.png)

ncurses

![](img/pic6.png)


Gather some system information and show it in this statusbar program, not tied to any Window Manager, terminal multiplexer, etc.

Please note that the program won't detect fans connected via molex connetor(s) or external fan controller. Also I have not tested it with fan splitter(s) either.

The program is smart enough to detect whether some of your fan(s) blades are spinning, or the particular fan have been removed. Hold down some of your fan blades and you'll see that the program won't include this fan and it's RPM, release the blades and you'll see the fan and it's RPM in the statusbar. Try simulating real fan hardware failure by holding down all system fan blades and watch what the program will show you, just try not to slice your cheesy fingers open in the process.

If you compile your kernel from source code make sure to include your cpu and motherboard sensors as **modules** and not inlined.

**Just an example if you use BSD - acpi/aibs, coretemp/amdtemp.**

![](img/cpu-temp.png)

![](img/mobo-temp.png)

---

## Bandwidth measurment

pinky-bar supplies bandwitdh/network throughput measurment to satisfy those users that pay for overpriced 3G/mobile internet, and want to monitor every single megabit/megabyte.

## Program options

The order of supplied options will dictate how, where and what system information to be shown.

| short option | long option | Descrtiption                                                       |
|--------------|-------------|--------------------------------------------------------------------|
| -M           | --mpd       | The song filename                                                  |
| -W           | --mpdtrack  | The song track name  (not available in cmus)                       |
| -x           | --mpdartist | The song artist(s) name(s)                                         |
| -X           | --mpdtitle  | The song title                                                     |
| -y           | --mpdalbum  | The song album name                                                |
| -Y           | --mpddate   | The song date                                                      |
| -c           | --cpu       | The current cpu load (summed up all cores/threads)                 |
| -L           | --coresload | Show the load regarding each individual cpu core/thread            |
| -T           | --cputemp   | The current cpu temperature                                        |
| -C           | --cpuspeed  | Show your maximum cpu clock speed in MHz, regardless of the used governor. Uses assembly. |
| -I           | --cpuinfo   | Detect your CPU vendor, stepping, family, clflush, l1/l2 cache and line size, physical cores, physical and virtual bits. Uses assembly. |
| -r           | --ramperc   | The used ram in percentage                                         |
| -J           | --ramtotal  | The total ram                                                      |
| -K           | --ramfree   | The free ram                                                       |
| -l           | --ramshared | The shared ram                                                     |
| -o           | --rambuffer | The buffer ram (not available in OpenBSD)                          |
| -s           | --driveperc | The used drive storage in percentage                               |
| -n           | --drivetotal| The total drive storage                                            |
| -N           | --drivefree | The free drive storage                                             |
| -O           | --driveavail| The available drive storage (total - used)                         |
| -g           | --battery   | The remaining battery charge                                       |
| -z           | --dvdstr    | The vendor and model name of your cdrom/dvdrom                     |
| -S           | --statio    | Read and written MBs to the drive so far [argument - sda]          |
| -p           | --packages  | The number of installed packages                                   |
| -P           | --kernsys   | The kernel name                                                    |
|              | --kernode   | The network node hostname                                          |
| -Q           | --kernrel   | The kernel release                                                 |
| -R           | --kernver   | The kernel version                                                 |
| -u           | --kernarch  | The machine architecture                                           |
| -k           | --kernel    | Combined kernel name and version                                   |
| -q           | --weather   | Show the temperature outside (some details must be provided)       |
| -U           | --uptime    | The system uptime                                                  |
| -w           | --loadavg   | The system average load for past 1, 5 and 15 minutes               |
| -v           | --voltage   | The system voltage                                                 |
| -f           | --fans      | All system fans and their speed in RPM                             |
| -m           | --mobo      | Show the motherboard name and vendor                               |
| -d           | --mobotemp  | The motherboard temperature                                        |
| -V           | --volume    | The sound volume level                                             |
| -t           | --time      | The current time                                                   |
| -a           | --ipaddr    | The local ip address [argument - eth0]                             |
| -b           | --bandwitdh | The consumed internet bandwidth so far [argument - eth0]           |
| -i           | --iface     | The current download and upload speed [argument - eth0]            |
| -A           | --ipmac     | The NIC mac address [argument - eth0]                              |
| -B           | --ipmask    | The NIC subnet mask [argument - eth0]                              |
| -D           | --ipcast    | The NIC broadcast address [argument - eth0]                        |
| -E           | --iplookup  | Mini website IP lookup [website argument - google.com]             |

Be aware of the options that mention **Uses assembly** are tested only on AMD and Intel CPUs (starting from pentium 4 onwards).

The following options are available only in Linux:

| short option | long option | Descrtiption                                                       |
|--------------|-------------|--------------------------------------------------------------------|
| -F           | --drivemodel| The vendor name of your drive [argument - sda]                     |
| -G           | --nicinfo   | The NIC vendor and model [argument - eth0]                         |
|              | --nicdrv    | The NIC driver [argument - eth0]                                   |
| -H           | --nicver    | The NIC version [argument - eth0]                                  |
| -e           | --iplink    | The NIC link speed (useful for wireless/wifi) [argument - eth0]    |
| -j           | --nicfw     | The NIC firmware [argument - eth0]                                 |
| -h           | --wifiname  | The name of currently connected wifi/wireless network [argument - wlan0]  |

The following options are available only to FreeBSD and OpenBSD:

| short option | long option | Descrtiption                                                       |
|--------------|-------------|--------------------------------------------------------------------|
| -j           | --nicgw     | The NIC gateway address [argument - re0]                           |
| -Z           | --swapused  | The used drive swap in MB                                          |
| -F           | --swaperc   | The used drive swap in percentage                                  |
| -h           | --swaptotal | The total drive swap                                               |
| -H           | --swapavail | The available drive swap (total - used)                            |

The following options are available only in OpenBSD:

| short option | long option | Descrtiption                                                       |
|--------------|-------------|--------------------------------------------------------------------|
| -l           | --ramused   | The used ram in MB                                                 |

---

## GNU Build System (configure) options

Before the source code is passed to the compiler, you can enable/disable the following **configure** options 
that will increase/reduce the number of dependencies required to compile the program.

It's up to you to decide which features suit you best.

| To include     | Not to include      | Descrtiption                                                                               |
|----------------|---------------------|--------------------------------------------------------------------------------------------|
| --with-x11     | --without-x11       | Enable it if you are using dwm.                                                            |
| --with-alsa    | --without-alsa      | To get the sound volume level.                                                             |
| --with-oss     | --without-oss       | To get the sound volume level in \*BSD.                                                    |
| --with-net     | --without-net       | Enable the internet related options.                                                       |
| --with-libnl   | --without-libnl     | Enable the wifi related options regarding chipsets supporting the cfg80211/mac80211 modules (linux only).  |
| --with-pci     | --without-pci       | To get the NIC vendor and model in linux                                                   |
| --with-dvd     | --without-dvd       | To get the cdrom/dvdrom vendor and model                                                   |
| --with-sensors | --without-sensors   | Alternative way to get the sensors values (linux only)                                     |
| --with-apm     | --without-apm       | APM power and resource management for laptops (FreeBSD only)                               |
| --with-ncurses | --without-ncurses   | Output the data to the terminal using the ncurses library, can be colorized                |
| --with-weather | --without-weather   | The temperature outside  (some details must be provided)                                   |
| api\_town='London,uk'              | | Town and country code to use for temperature monitoring                                    |
| api\_key='123458976'               | | API key obtained after registering yourself in the weather website                         |
| --with-colours | --without-colours   | Colorize the output data.                                                                  |
| icons=/tmp     |                     | xbm icons that can be used by dzen2 for example. Discarded when **--with-x11** is used     |
| --with-mpd     | --without-mpd       | To see the currently played song name (if any).                                            |
| --prefix=/tmp  |                     | The directory where the program will be installed                                          |
| mobo\_sensor='dev.aibs.0'  |         | FreeBSD motherboard sensor module name to use in the sysctl calls. Read the FreeBSD installation below  |
| cpu\_sensor='dev.cpu.0.temperature' |  | FreeBSD cpu temperature module name to use in the sysctl calls . Read the FreeBSD installation below  |

By default, if **no** options are passed, the program will be compiled with/without:

```bash
--without-alsa --without-x11 --without-mpd --with-colours --with-net --with-pci --without-dvd --without-sensors --without-ncurses --without-weather
```

Affects only FreeBSD users with laptops, **--without-apm** will compile the program with acpi support to obtain the current battery life.

**--without-mpd** will compile the program with cmus support, the options syntax stays as is.

The pci and sensors configure options will be discarded in \*BSD. If you supplied **--with-alsa** and **--with-oss** or used the port package with the ncurses dialogue, alsa will have higher precedence over OSS. By default the port package will have OSS selected and alsa unselected.

Affects only linux, **--with-pci** and or **--with-sensors** will substitute -O0 flag to mitigate bugs in GCC caused by -O2 optimizations. -O0 will optimize the compiled binary for file size, while -O2 will optimize it for speed. So don't be shocked to find out that **--without-pci --without-sensors** will cause the compiled binary to double it's size. If things doesn't improve with upcomining GCC releases I will temporary drop -O2.

Affects only linux users with wifi/wireless chipsets, run `lsmod|grep 802` and see whether your chipset uses cfg80211/mac80211. If that's so you can rely on libnl and enable **--with-libnl** configure options, otherwise your chipset probably still uses we/wext, so type **--without-libnl**.

**--with-weather** is using [dis url](http://openweathermap.org/current), register yourself there, create a new [API key](https://home.openweathermap.org/api\_keys) and supply them like dis to **configure**.

Don't just rush to register yourself, read carefully what the "Free" account limits are and take in account how often the program should call their api service. I'm not responsible if you exceeded the limits, you've been warned.

```bash
# Make sure it's working first
# curl 'http://api.openweathermap.org/data/2.5/weather?q=London,uk&units=metric&APPID=28459ae16e4b3a7e5628ff21f4907b6f'

# what to pass to configure
--with-weather api_town='London,uk' api_key='28459ae16e4b3a7e5628ff21f4907b6f'
```

---

## Installation for dwm

```bash
bash bootstrap distro
./configure --prefix=$HOME/.cache --with-x11 --with-alsa
make
make install
```

To see the currently played song name add **--with-mpd** to configure.

To disable the colours you can add **--without-colours** to configure.

Put the following in your **xinitrc** or the script used to start dwm.

```bash
# Execute the "statusbar" program every 5 secs
while true; do
  # scroll a few lines up to see the rest options
  "$HOME/.cache/bin/pinkybar" -LTrspkvfmdVt
  sleep 5
done &
```

## Installation for xmonad (or other WM)

```bash
# Copy the xbm icons
mkdir -p --mode=700 $HOME/.xmonad/icons
cp -r xbm_icons/*.xbm $HOME/.xmonad/icons

bash bootstrap distro

# disable X11, point the location to the icons
./configure --prefix=$HOME/.cache --without-x11 --with-alsa icons=$HOME/.xmonad/icons

# compile 'n install
make
make install
```

To see the currently played song name add **--with-mpd** to configure.

Put the following in your **xinitrc** or the script used to start xmonad.

```bash
# Execute the "statusbar" program every 2 secs
while true; do
  # scroll a few lines up to see the rest options
  "$HOME/.cache/bin/pinkybar" -LTrspkvfmdVt
  sleep 2
done | dzen2 -w 1800 -x 130 -ta r -fn '-*-dejavusans-*-r-*-*-11-*-*-*-*-*-*-*' &
```

## Installation in FreeBSD

FreeBSD has no other way than using the module specific convention to query sysctl and obtain data from the sensors. Maintaining a list with all the possible module names and performing expensive sysctl calls in a loop to determine that X module is loaded into your system is no-go. Be prepared to spend a minute or two to find out some system information.

Let's say you are using dwm:

Determine the motherboard sensor module name.

```bash
sysctl -a|grep 'aibs'

dev.aibs.0.volt.0: 1356 850 1600
dev.aibs.0.volt.1: 3344 2970 3630
dev.aibs.0.volt.2: 5040 4500 5500
dev.aibs.0.volt.3: 12278 10200 13800
dev.aibs.0.temp.0: 39.0C 60.0C 95.0C
dev.aibs.0.temp.1: 38.0C 45.0C 75.0C
dev.aibs.0.fan.0: 1053 600 7200
dev.aibs.0.fan.1: 1053 600 7200
```

Copy only 'dev.MODULE.NUMBER' (if there is any number at all) and paste it into the **mobo\_sensor** option below.

Do the same for your cpu temperature, copy and paste the variable as is. **dev.cpu.0.temperature** below is provied as example.

```bash
bash bootstrap freebsd
./configure --prefix=$HOME/.cache --with-x11 --without-alsa --with-oss mobo_sensor='dev.aibs.0' cpu_sensor='dev.cpu.0.temperature'
make
make install
```

Send a request to the FreeBSD mail list and request the OpenBSD sensors API to be ported.


## Installation in OpenBSD

Before even executing the **bootstrap** script, you'll have to do this:

```bash
# To detect the newer compiler that you are
# about to install
sed -i 's/#AC_PROG_CC(/AC_PROG_CC(/g' bootstrap

ls /usr/local/bin/automake-*
ls /usr/local/bin/autoconf-*

# Then replace the numbers below
export AUTOCONF_VERSION=2.69
export AUTOMAKE_VERSION=1.15

# Your call, gcc or llvm ?
pkg_add gcc
```

## pinky curses installation

```bash
bash bootstrap distro

# disable X11, enable the colours and ncurses opts.
./configure --prefix=$HOME/.cache --without-x11 --with-alsa --with-colours --with-ncurses

# compile 'n install
make all ncurses
make install
```

Put the following in your shell config as function or alias.

```bash
pinky() {
  location="${HOME}/.cache/bin"

  while true; do
    # scroll a few lines up to see the rest options
    "${location}"/pinkybar -LTrspkvfmdVt
    sleep 2
  done | "${location}"/ncurses
}
```

Test it:

```bash
pinky  # Press CTRL + C to stop the program
```

Put the following in **~/.Xresources**

```bash
! Xft --------------------------------------------------------------------
Xft.dpi:        96
Xft.antialias:  true
Xft.rgba:       rgb
Xft.hinting:    true
Xft.hintstyle:  hintslight
Xft.autohint:   false
Xft.lcdfilter:  lcddefault


! urxvt conf --------------------------------------------------------------------
URxvt.buffered                  : true
URxvt.cursorBlink               : false
URxvt.cursorUnderline           : false
URxvt.pointerBlank              : false
URxvt.geometry                  : 80x24
URxvt.font                      : xft:DejaVu Sans Mono:bold:pixelsize=11
URxvt.boldfont                  : xft:DejaVu Sans Mono:bold:pixelsize=11
URxvt.letterSpace               : -1
URxvt.termName                  : rxvt-256color
URxvt.iso14755                  : false
URxvt.iso14755_52               : false
URxvt.cursorColor               : #ffffff
URxvt.colorIT                   : #87af5f
URxvt.colorBD                   : #d7d7d7
URxvt.colorUL                   : #87afd7
URxvt.urgentOnBell              : false
URxvt.mapAlert                  : false
URxvt.visualBell                : false
URxvt.saveLines                 : 10000
URxvt.scrollBar                 : false
URxvt.scrollBar_right           : false
URxvt.scrollBar_floating        : false
URxvt.scrollstyle               : rxvt
URxvt.Depth                     : 32
URxvt.loginShell                : false
URxvt.insecure                  : false
URxvt.pastableTabs              : false
URxvt.utmpInhibit               : false
URxvt.reverseVideo              : false
URxvt.skipBuiltinGlyphs         : true


! urxvt colours --------------------------------------------------------------------
*.foreground:   #c5c8c6
*.background:   #222222
*.cursorColor:  #ffffff

! black
*.color0:       #222222
*.color8:       #373b41

! red
*.color1:       #ef2929
*.color9:       #ef2929

! green
*.color2:       #8ae234
*.color10:      #8ae234

! yellow
*.color3:       #c2a000
*.color11:      #fce94d

! blue
*.color4:       #5f819d
*.color12:      #81a2be

! magenta
*.color5:       #85678f
*.color13:      #a97fa8

! cyan
*.color6:       #5e8d87
*.color14:      #34e2e2

! white
*.color7:       #ffffff
*.color15:      #ffffff


! xterm conf -----------------------------------------------------------
XTerm.vt100.geometry:   80x24
XTerm*faceName:     DejaVu Sans Book
XTerm*faceSize:     9
XTerm*toolBar:      off

xterm*termName: xterm-256color
XTerm*locale: true
xterm*cursorColor: #FFFFFF
xterm*toolBar: false
xterm*scrollBar: false
xterm*rightScrollBar: false
xterm*background: #222222
xterm*foreground: #999999
xterm*faceName: DejaVu Sans Book:pixelsize=12
xterm*allowBoldFonts: false
xterm*geometry: 80x24
```

Force your non xterm/urxvt terminal emulator to use the newer xterm/urxvt colours. You'll have to kill Xorg (simply logout and log back in), experienced people are using xrdb instead killing Xorg each time they do changes to such files.

pinky\_curses is standalone program not tied to pinky-bar.

```bash
# ^B - Blue , ^M - Magenta , ^Y - Yellow
while true; do echo "^BOh ^Mhello ^Ydear";sleep 1;done | ./pinky_curses
```

## Installation for anything else

pinky-bar is no longer tied to Window Managers only. With the addition of "without colours", the output can be shown in any program, just bear in mind that the more options you've supplied the more system information will be shown.

![](img/pic4.png)

The installation steps:

```bash
bash bootstrap distro
./configure --prefix=$HOME/.cache --without-x11 --without-colours
make
make install
```

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

Cannot list the \*BSD flavours as "distros", so they deserve own options:

- [x] freebsd
- [x] openbsd

---

## Linux Mandatory requirements

* gcc/clang
* glibc
* autoconf
* automake
* m4
* gawk

## \*BSD Mandatory requirements

* gcc/clang
* bash
* autoconf
* automake
* autoconf-wrapper
* automake-wrapper
* autoconf-archive
* argp-standalone
* libtool
* m4
* gawk

Some llvm and gcc versions will not check for headers and libraries in /usr/local, if that's the case for you, you should export the following environment variables:

```bash
export LDFLAGS='-L/usr/local/lib'
export CFLAGS='-I/usr/local/include'
```

After editing the wrong prototype I managed to stumbled upon a bug in OpenBSD's own libc.

**Warning !!! OpenBSD users !!!**

OpenBSD stdint.h:

```cpp
/* machine/_types.h */
/* 7.18.1.1 Exact-width integer types */
typedef	unsigned int		__uint32_t;

/* 7.18.1.3 Fastest minimum-width integer types */
typedef	__uint32_t		__uint_fast16_t;

/* stdint.h */
typedef	__uint_fast16_t		uint_fast16_t;

/* inttypes.h */
#define	PRIuFAST16		"u"		/* uint_fast16_t */
#define	SCNuFAST16		"hu"		/* uint_fast16_t */
```

The bug was submitted.

```cpp
Synopsis:      Fixed integer mismatch definition
Category:      libc
Environment:
  System      : OpenBSD 6.0
  Details     : OpenBSD 6.0 (GENERIC.MP) #2319: Tue Jul 26 13:00:43 MDT 2016
                   deraadt@amd64.openbsd.org:/usr/src/sys/arch/amd64/compile/GENERIC.MP

  Architecture: OpenBSD.amd64
  Machine     : amd64
Description:
  The header file inttypes.h defines different format specifiers for the fixed width uint_fast16_t integer which causes the compilers to issue warning.

How-To-Repeat:

/* test.c
egcc -Wall -Wextra -std=c99 -pedantic -Wconversion -O2 test.c -o /tmp/test
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void) {
  char elo[] = "1337";
  uint_fast16_t x = 0;

  if (EOF == (sscanf(elo, "%"SCNuFAST16, &x))) {
    return EXIT_FAILURE;
  }
  printf("%"PRIuFAST16 "\n", x);

  return EXIT_SUCCESS;
}


Fix:

From
#define	SCNuFAST16		"hu"		/* uint_fast16_t */

To
#define	SCNuFAST16		"u"		/* uint_fast16_t */
```

## Opt-in requirements

Linux camp:

The internet related options rely on headers provided iproute2.
By default the program will try to compile with those headers included.
If for any reason you would like to compile the program without internet related options, then pass **--without-net** to configure.

* iproute2

wifi/wireless chipsets supporting mac80211/cfg80211:

* libnl (>= 3.0)
* pkg-config

Then pass **--with-libnl** to configure.

To get the NIC vendor and model names:

* pciutils

Alternative way to obtain data from the sensors:

* lm\_sensors

Linux camp end.

To get the sound volume level:

* alsa-utils
* alsa-lib

Then pass **--with-alsa** to configure.

\*BSD users can use the baked OSS instead, pass **--without-alsa --with-oss** to configure instead.

To output the data to the terminal using the ncurses library:

* ncurses

To get the vendor and model name of your cdrom/dvdrom/blu-ray:

* libcdio
* libcddb

In linux **--without-dvd** will still compile the program with dvd support. Except it will be limited only to dvd support, it will try to parse the sr0 vendor and model name detected by the kernel.

The weather related options, please go back and read **Don't just rush to register yourself**:

* curl
* gzip

**Warning, I'm not responsible for any lawsuit towards you, neither encourage you to pirate content that is not licensed as free and/or for fair use.**

To see the currently played song name **--with-mpd**:

  Server side:

  * libmpdclient
  * mpd (can be build with soundcloud support)

  Client side:

  * libmpdclient
  * mpc/ncmpc/ncmpcpp, [and the rest](http://mpd.wikia.com/wiki/Clients)

To see the currently played song name **--without-mpd**:

* cmus

The "soundcloud" alternative that is supported in cmus and your mpd client will be to download **.m3u/.pls** files according to the [radio stream station](https://www.internet-radio.com) that you are interested to listen.

The FreeBSD users will notice that "mpd" is named "musicpd".

Here's an example of my **/etc/mpd.conf** (linux)

```nginx
music_directory "/home/frost/music"
playlist_directory "/home/frost/music"
db_file "/tmp/mpddb"
log_file "/tmp/mpdlog"
state_file "/tmp/mpdstate"
pid_file "/tmp/mpdpid"
log_level "default"
user "mpd"

audio_output {
  type "alsa"
  name "My sound card"
  mixer_type "software"
}

port "6600"
bind_to_address "127.0.0.1"
```

FreeBSD conf, same as the Linux one, you'll have to add the "musicpd" daemon user on your own:

```nginx
user "musicpd"

audio_output {
  type "oss"
  name "My sound card"
  mixer_type "software"
}
```

OpenBSD conf, same as the FreeBSD one, just replace audio\_output with:

```nginx
audio_output {
  type "ao"
  name "My sound card"
  mixer_type "software"
}
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

* dwm compiled with statuscolor patch. The colours in use are specified in your dwm config.h

## Wish list

As top priority:

It would be great if I had \*BSD compatible usb wifi dongle to add wifi options in pinky-bar.

---

With the help from the gcc documentation, this wish list option has been solved.

~~Per core/thread CPU frequency detection: Can add it at any time if there is enough demand, but needs some consideration first.~~

~~The kernels cpu frequency governor "performance" will always run at the highest possible clock rate regardless of it's use/idle. The only side effect of this is higher temps when on idle (true if the cpu has multiple cores and or threads).~~

~~The "powersaving" governor will always run at the lowest possible clock rate regardless of it's use/idle. The side effect - slower machine no matter what you do.~~

~~The "ondemand" governor does what it says - ondemand scaling. With it you get the best performance when you need to, powersaving and lower temps when on idle.~~

~~For example I manually turn off the cpu frequency governor in my kernel builds, which sets it to performance.~~

~~The cpu frequency detection is easy, but it poses a roadblock by assuming that the "ondemand" is set and/or is enabled in the user kernel.~~

~~Decision 1: On a multicore/thread cpu, the detection for each core/thread will produce up to 8 digit number, thus 4 core and 4 thread cpu will produce: 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678 1234.5678, without including MHz for each core/thread, which will take a lot of space in the final statusbar output. This way the user will know for how long and which core/thread is under some load.~~

~~Decision 2: On other hand it will be lame on a multi core/thread system to show the overall (not per core/thread) cpu frequency that have been summed up, which will beat the purpose of cpu frequency detection in first place, as the user will not be aware that some core/thread is running at full cpu clock speed as the load will be spread equally when summing the numbers up.~~

---

GPU temperature, voltage, fan(s) and used RAM: hard, but not impossible.

It would be nice to have decent gpu temperature, voltage, fan(s) speed and used RAM detection regarding SLI, single and dual gpu cards that doesn't require X, MESA and **/sys/kernel/debug/dri**

Using assembly is strongly no-go.

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

Show the idle time in seconds/minutes: easy to be added via [XScreenSaverQueryInfo](http://linux.die.net/man/3/xscreensaverqueryinfo), but will discriminate the users that have compiled the program **--without-x11**.

---

Show the CapsLock/NumLock/ScrollLock indicator status for keyboard without LEDs: easy to be added via [XkbGetIndicatorState](http://linux.die.net/man/3/xkbgetindicatorstate), but will discriminate the users that have compiled the program **--without-x11**.
