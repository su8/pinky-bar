The code doesn't age, neither it has expiration date.

## Table of Contents
- [Installation for dwm](#installation-for-dwm)
- [Installation for py3status](#installation-for-py3status)
- [Installation for tmux](#installation-for-tmux)
- [Installation for xmonad/other WM](#installation-for-xmonad-or-other-wm)
- [Installation for lemonbar](#installation-for-lemonbar)
- [Installation in FreeBSD](#installation-in-freebsd)
- [Installation in OpenBSD](#installation-in-openbsd)
- [Installation for anything else](#installation-for-anything-else)
- [Configure Options](#gnu-build-system-configure-options)
- [Program Options](#program-options)
- [Supported Linux Distributions](#supported-linux-distributions)
- [Configuration File](#configuration-file)
- [Linux Mandatory Requirements](#linux-mandatory-requirements)
- [BSD Mandatory Requirements](#bsd-mandatory-requirements)
- [Opt-in Requirements](#opt-in-requirements)
- [Execute Scripts](#execute-scripts)
- [WM Specific Requirements](#wm-specific-requirements)
- [Void Linux](#void-linux)
- [Tiny Core Linux](#tiny-core-linux)
- [Wish List](#wish-list)
- [History](#history)

---

dwm

![](img/pic.png)

xmonad

![](img/pic5.png)

![](img/pic7.png)

ncurses

![](img/pic6.png)

py3status

![](img/py3status.png)

tmux

![](img/tmux.png)

lemonbar

![](img/lemonbar.png)

Gather some system information and show it in this program, not tied to any Window Manager, terminal multiplexer, etc.

Please note that the program won't detect fans connected via Molex connectors or external fan controllers. Also I have not tested it with fan splitters either.

The program is smart enough to detect whether some of your fan blades are spinning, or the particular fan have been removed. Hold down some of your fan blades and you'll see that the program won't include this fan and its RPM, release the blades and you'll see the fan and its RPM in the statusbar. Try simulating real fan hardware failure by holding down all system fan blades and watch what the program will show you, just try not to slice your cheesy fingers open in the process.

You can extend pinky-bar with Perl/Python/Ruby/Lua/R/Assembly/Lisp/OCaml/Rust/Go/C++/Slang/Tcl scripts.

If you compile your kernel from source code make sure to include your CPU and motherboard sensors as **modules** and not inlined.

**Just an example if you use BSD - acpi/aibs, coretemp/amdtemp.**

![](img/cpu-temp.png)

![](img/mobo-temp.png)

---

## Installation for dwm

```bash
perl set.pl "distro"
autoreconf --install --force

./configure --prefix=$HOME/.cache --with-dwm --with-colors
make
make install
```

---

## Installation for py3status

```bash
perl set.pl "distro"
autoreconf --install --force

./configure --prefix=$HOME/.cache --with-py3status --with-colors
make
make install
```

---

## Installation for tmux

```bash
perl set.pl "distro"
autoreconf --install --force

./configure --prefix=$HOME/.cache --with-tmux --with-colors
make
make install
```
```bash
# ~/.tmux.conf
set -g status-style 'bg=black'
set -g status-right '#(~/.cache/bin/pinkybar)'
```

---

## Installation for xmonad (or other WM)

```bash
perl set.pl "distro"
autoreconf --install --force

# here you can specify --with-awesomewm or --with-xmobar
./configure --prefix=$HOME/.cache --with-colors

# compile 'n install
make
make install
```

Copy the code from extra/scripts/xmonad.sh or `exec` it from **xinitrc** or the script used to start xmonad.

---

## Installation for lemonbar

```bash
perl set.pl "distro"
autoreconf --install --force

./configure --prefix=$HOME/.cache --with-lemonbar --with-colors
make
make install
```

```bash
#!/usr/bin/env bash
while true; do
    echo -n "%{r}"
    ~/.cache/bin/pinkybar
    sleep 2
done
```

```bash
~/script.sh | lemonbar -p
```

One-liner.

```bash
while true; do echo -n "%{r}" ; ~/.cache/bin/pinkybar ; sleep 2; done | lemonbar -p
```

---

## Installation in FreeBSD

FreeBSD has no other way than using the module specific convention to query sysctl and obtain data from the sensors. Maintaining a list with all the possible module names and performing expensive sysctl calls in a loop to determine that X module is loaded into your system is no-go. Be prepared to spend a minute or two to find out some system information.

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

Do the same for your CPU temperature, copy and paste the variable as is. **dev.cpu.0.temperature** below is provided as example.

```bash
perl set.pl "freebsd"
autoreconf --install --force

./configure --prefix=$HOME/.cache --without-alsa --with-oss mobo_sensor='dev.aibs.0' cpu_sensor='dev.cpu.0.temperature'
make
make install
```

Send a request to the FreeBSD mailing list and request the OpenBSD sensors API to be ported.

---

## Installation in OpenBSD

Before proceeding, you'll have to:

```bash
# detect the newer compiler that you are about to install
sed -i 's/#AC_PROG_CC(/AC_PROG_CC(/g' configure.ac

ls /usr/local/bin/automake-*
ls /usr/local/bin/autoconf-*

# then replace the numbers below
export AUTOCONF_VERSION=2.69
export AUTOMAKE_VERSION=1.15

pkg_add gcc

# after that:
perl set.pl "openbsd"
autoreconf --install --force

./configure --prefix=$HOME/.cache --without-alsa --with-oss
make
make install
```

---

## Installation for anything else

pinky-bar is no longer tied to Window Managers only. With the addition of "without colors", the output can be shown in any program, just bear in mind that the more options you've supplied the more system information will be shown.

The tmux status bar in action:

![](img/pic4.png)

The installation steps:

```bash
perl set.pl "distro"
autoreconf --install --force

./configure --prefix=$HOME/.cache --without-colors
make
make install
```

By choosing this 3rd installation method it is up to you where, how to start and use the system information that's produced by pinky-bar.

---

## GNU Build System (configure) options

Before the source code is passed to the compiler, you can enable/disable the following **configure** options that will increase/reduce the number of dependencies required to compile the program.

It's up to you to decide which features suit you best.

| Build With | Without | Description                                                                                |
|----------------|:---------------------:|--------------------------------------------------------------------------------------------|
| `--with-dwm`     | `--without-dwm`       | Output data to the root window for dwm.<br /> Can be colorized with **--with-colors**|
| `--with-ncurses` | `--without-ncurses`   | Output data to the terminal using ncurses library.<br />Can be colorized with **--with-colors**|
| `--with-py3status` | `--without-py3status` | Output data in different format for py3status.<br />Can be colorized with **--with-colors**             |
| `--with-tmux`  | `--without-tmux`    | Output data in different format for tmux.<br />Can be colorized with **--with-colors**                  |
| `--with-awesomewm` | `--without-awesomewm` | Output data in different format for awesomewm.<br />Can be colorized with **--with-colors**             |
| `--with-xmobar`  | `--without-xmobar`    | Output data in different format for xmobar.<br />Can be colorized with **--with-colors**                  |
| `--with-lemonbar`  | `--without-lemonbar`    | Output data in different format for lemonbar.<br />Can be colorized with **--with-colors**                  |
| `--with-colors`  | `--without-colors`    | Colorize the output |
| `--with-alsa`    | `--without-alsa`      | Enable sound volume |
| `--with-oss`     | `--without-oss`       | Enable sound volume (\*BSD)                                                     |
| `--with-net`     | `--without-net`       | Enable Internet related options                                                        |
| `--with-libnl`   | `--without-libnl`     | Enable WiFi related options regarding chipsets supporting<br />the cfg80211/mac80211 modules (Linux only)|
| `--with-pci`     | `--without-pci`       | Enable NIC vendor and model in linux with pciutils                          |
| `--with-dvd`     | `--without-dvd`       | Enable CD-ROM/DVD-ROM vendor and model                                                 |
| `--with-sensors` | `--without-sensors`   | Get sensor readings with lm_sensors instead of kernel (Linux only)|
| `--with-apm`     | `--without-apm`       | Enable APM power and resource management for laptops<br />(FreeBSD only)                               |
| `--with-perl`    | `--without-perl`      | Build pinkybar with Perl support                              |
| `--with-lua`     | `--without-lua`       | Build pinkybar with Lua support                               |
| `--with-ruby`    | `--without-ruby`      | Build pinkybar with Ruby support                             |
| `--with-python2` | `--without-python2`   | Build pinkybar with Python 2 support                         |
| `--with-python3` | `--without-python3`   | Build pinkybar with Python 3 support                         |
| `--with-r`       | `--without-r`         | Build pinkybar with R support                                |
| `--with-assembly`| `--without-assembly`  | Build pinkybar with Assembly support
| `--with-lisp`    | `--without-lisp`      | Build pinkybar with Lisp support                              |
| `--with-ocaml`   | `--without-ocaml`     | Build pinkybar with OCaml support                            |
| `--with-rust`    | `--without-rust`      | Build pinkybar with Rust support                             |
| `--with-go`      | `--without-go`        | Build pinkybar with Go support                               |
| `--with-cpp`     | `--without-cpp`       | Build pinkybar with C++ support
| `--with-slang`   | `--without-slang`     | Build pinkybar with Slang support
| `--with-tcl`     | `--without-tcl`       | Build pinkybar with Tcl support |
| `--with-weather` | `--without-weather`   | Enable weather from OpenWeatherMap |
| &emsp;&#8627;`api_key='123458976'`               | | Required OpenWeatherMap API key, must be combined **--with-weather**  |
| `--with-smartemp` | `--without-smartemp`   | Enable drive temperature from *S.M.A.R.T.* (cross-platform)<br />with smartmontools|
| `--with-drivetemp` | `--without-drivetemp`   | Enable drive temperature from *S.M.A.R.T.* (Linux only)<br />with curl |
| `--with-drivetemp-light` | `--without-drivetemp-light`   | Enable drive temperature from *S.M.A.R.T.* (Linux only). Light version does not use curl nor will it force `-O0 CFLAG`. |
| &emsp;&#8627;`drive_port='7634'`  |                | Optional listening TCP port for drive temperature, default is 7634, must be combined **--with-drivetemp** or **--with-drivetemp-light**   |
| `--with-mpd`     | `--without-mpd`       | Enable MPD support for songs currently playing in mpd
| `--with-keyboard` | `--without-keyboard` | Enable Xorg support for keyboard layouts                                     |
| `--with-mouse`   | `--without-mouse`     | Enable Xorg support for mouse speed, in percentage |
| `--with-lock-keys` | `--without-lock-keys` | Enable Xorg support for Num Lock, Caps Lock and Scroll Lock |
| `--with-ip`      | `--without-ip`        | Enable External IP address (IPv4).                                                    |
| `--with-gmail`    | `--without-gmail`      | Enable Gmail for a number of unread emails, must be combined with **gmail_account** and **gmail_password**  |
| &emsp;&#8627;`gmail_account=foo`  |                | Required Gmail account, must be combined **--with-gmail**                            |
| &emsp;&#8627;`gmail_password=bar` |                | Required Gmail password, must be combined **--with-gmail**                   |
| `--with-yahoo`    | `--without-yahoo`      | Enable Yahoo for a number of unread emails, must be combined with **yahoo_account** and **yahoo_password**  |
| &emsp;&#8627;`yahoo_account=foo`  |                | Required Yahoo account, must be combined **--with-yahoo**                            |
| &emsp;&#8627;`yahoo_password=bar` |                | Required Yahoo password, must be combined **--with-yahoo**                   |
| `--with-github`  | `--without-github`    | Enable GitHub for a number of unread notifications                                           |
| &emsp;&#8627;`github_token=foo`  |                 | Required GitHub token [Generate token for specific scope](https://github.com/settings/tokens/new?scopes=notifications&description=pinky-bar), must be combined **--with-github**  |
| `--with-reddit`  | `--without-reddit`    | Enable Reddit for a number of unread notifications|
| &emsp;&#8627;`reddit_feed=`<br />`https://...`  |                  | Required Reddit URL ![](img/reddit.png)[Copy and Paste JSON URL](https://www.reddit.com/prefs/feeds/), must be combined **--with-reddit**  |
| `--with-pingtime` | `--without-pingtime` | Perform a GET request and measure the round trip time                                      |
| `--with-sqlite`  | `--without-sqlite`    | Enable SQLite support to query a statement on a database file              |
| &emsp;&#8627;`sqlite_db=foo` |                     | Location of a SQLite database file                                                      |
| `--prefix=`<br />`$HOME/.cache`  |                     | Install `pinkybar` to this directory |
| `mobo_sensor=`<br />`'dev.aibs.0'`  |         | FreeBSD motherboard sensor module name to use in the sysctl calls. Read the FreeBSD installation below  |
| `cpu_sensor=`<br />`'dev.cpu.0.temperature'` |  | FreeBSD CPU temperature module name to use in the sysctl calls. Read the FreeBSD installation below  |

If no options are passed, the program will be compiled with:

```bash
# --with-pci is discarded in *BSD
--with-net --with-pci --with-alsa
```

Affects **--with-gmail**. If you get error 403 unauthorized, then allow [less secure apps](https://myaccount.google.com/lesssecureapps) to access your account.

Affects **--with-yahoo**. If you get error 403 unauthorized, then allow [less secure apps](https://login.yahoo.com/account/security#less-secure-apps) to access your account.

Affects only FreeBSD users with laptops, **--without-apm** will compile the program with ACPI support to obtain the current battery life.

**--without-mpd** will compile the program with cmus support, the options syntax stays as is.

The PCI and sensors configure options will be discarded in \*BSD.

Affects only linux users with WiFi/wireless chipsets, run `lsmod|grep 802` and see whether your chipset uses cfg80211/mac80211. If that's so you can rely on libnl and enable **--with-libnl** configure options, otherwise your chipset probably still uses we/wext, so type **--without-libnl**.

Affects only linux users, **--with-drivetemp** pretty much locks you down to hddtemp. You can adjust **extra/scripts/drive-temperature.sh** and compile the program **--with-smartemp**, so you can switch between hddtemp and smartmontools at any time without the need recompile pinkybar with different options. **--with-smartemp** only cares for the existence of /tmp/pinkytemp file.

**--with-weather** is using [this URL](http://openweathermap.org/current), register yourself there, create a new [API key](https://home.openweathermap.org/api\_keys).

Don't just rush to register yourself, read carefully what the "Free" account limits are and take in account how often the program should call their API service. I'm not responsible if you exceeded the limits, you've been warned.

```bash
# Make sure it's working first
# curl 'http://api.openweathermap.org/data/2.5/weather?q=London,uk&units=metric&APPID=28459ae16e4b3a7e5628ff21f4907b6f'

# what to pass to configure
--with-weather api_key='28459ae16e4b3a7e5628ff21f4907b6f'
```

---

## Program Options

The order of supplied options will dictate how, where and what system information to be shown.

|Opt| Option | Description                                                        |
|:---|---------------|--------------------------------------------------------------------|
|`-M`| `--mpd`            | Print song filename                                                  |
|`-W`| `--mpdtrack`       | Print song track name (not available in cmus)                        |
|`-x`| `--mpdartist`      | Print song artist name                                               |
|`-X`| `--mpdtitle`       | Print song title                                                     |
|`-y`| `--mpdalbum`       | Print song album name                                                |
|`-Y`| `--mpddate`        | Print song date                                                      |
|`-c`| `--cpu-percent`    | Print current CPU percent for system-wide utilization                |
|`-L`| `--cpu-percent-all`| Print current CPU percent for each core and thread                   |
|`-T`| `--cputemp`        | Print current CPU temperature                                        |
|`-C`| `--cpuspeed`       | Print maximum CPU clock speed in MHz, regardless of the used governor. **Assembly.**|
|`-I`| `--cpuinfo`        | Print CPU vendor, stepping, family, clflush, l1/l2 cache and line size, physical cores, physical and virtual bits. **Assembly.**|
|`-r`| `--ramperc`        | Print used RAM, in percentage                                        |
|`-J`| `--ramtotal`       | Print total RAM                                                      |
|`-K`| `--ramfree`        | Print free RAM                                                       |
|`-l`| `--ramshared`      | Print shared RAM                                                     |
|`-o`| `--rambuffer`      | Print buffer RAM (not available in OpenBSD)                          |
|`-s`| `--driveperc`      | Print used drive storage in percentage                               |
|`-n`| `--drivetotal`     | Print total drive storage                                            |
|`-N`| `--drivefree`      | Print free drive storage                                             |
|`-O`| `--driveavail`     | Print available drive storage (total - used)                         |
|    | `--drivetemp`      | Print current drive temperature from *S.M.A.R.T.*                    |
|`-g`| `--battery`        | Print remaining battery charge                                       |
|`-z`| `--dvdstr`         | Print vendor and model name of CD-ROM/DVD-ROM                        |
|`-S`| `--statio=sda`     | Print read and written MBs to the drive                              |
|`-p`| `--packages`       | Print number of installed packages                                   |
|`-P`| `--kernsys`        | Print kernel name                                                    |
|    | `--kernode`        | Print network node host name                                         |
|`-Q`| `--kernrel`        | Print kernel release                                                 |
|`-R`| `--kernver`        | Print kernel version                                                 |
|`-u`| `--kernarch`       | Print machine architecture                                           |
|`-k`| `--kernel`         | Print kernel name and kernel version (combined)                      |
|    | `--keyboard`       | Print current keyboard layout                                        |
|    | `--mouse`          | Print current mouse speed, in percentage                             |
|    | `--numlock`        | Print current state of Num Lock                                      |
|    | `--capslock`       | Print current state of Caps Lock                                     |
|    | `--scrolllock`     | Print current state of Scroll Lock                                   |
|    | `--gmail`          | Print number of unread emails                                        |
|    | `--yahoo`          | Print number of unread emails                                        |
|    | `--github`         | Print number of unread notifications                                 |
|    | `--reddit`         | Print number of unread notifications                                 |
|    | `--password=20`    | Generate random password                                             |
|    | `--shell whoami` | Execute shell command (Configuration file only)<br/> *Example:* `--shell uptime --pretty`|
|    | `--title=RAM`      | Display a static string                                              |
|    | `--perl`           | Execute scripts written in Perl                                          |
|    | `--python`         | Execute scripts written in Python                                        |
|    | `--ruby`           | Execute scripts written in Ruby                                          |
|    | `--lua`            | Execute scripts written in Lua                                           |
|    | `--R`              | Execute scripts written in R                                             |
|    | `--asm`            | Execute scripts written in Assembly                                      |
|    | `--lisp`           | Execute scripts written in Lisp                                          |
|    | `--ocaml`          | Execute scripts written in OCaml                                         |
|    | `--rust`           | Execute scripts written in Rust                                          |
|    | `--go`             | Execute scripts written in Go                                            |
|    | `--cpp`            | Run programs written in C++                                          |
|    | `--slang`          | Run programs written in Slang                                        |
|    | `--tcl`            | Run programs written in Tcl                                          |
|    | `--fmt`         | Format the output data for different WM/terminal multiplexer            |
|    | `--color1`         | Color for the `--title`                                              |
|    | `--color2`         | Color for the above/below options                                    |
|    | `--color3`         | Color for the kernel/misc                                            |
|    | `--sqlite="SELECT`<br />` * from COMPANY`<br />`where ID=1"` | Query a statement on a database file|
|`-q`| `--weather=`<br />`London,UK` | Print current weather temperature                         |
|`-U`| `--uptime`          | Print system uptime                                                 |
|`-w`| `--load-1min`       | Print system load average for past 1 minutes                        |
|    | `--load-5min`       | Print system load average for past 5 minutes                        |
|    | `--load-15min`      | Print system load average for past 15 minutes                       |
|`-v`| `--voltage`         | Print system voltage                                                |
|`-f`| `--fans`            | Print system fans and speeds in RPM                                 |
|`-m`| `--mobo`            | Print motherboard name and vendor                                   |
|`-d`| `--mobotemp`        | Print motherboard temperature                                       |
|`-V`| `--volume`          | Print current volume                                                |
|`-t`| `--time`            | Print current time                                                  |
|    | `--ip`              | Print external IP address (IPv4).                                   |
|`-a`| `--ipaddr=eno1`     | Print local IP address                                              |
|`-b`| `--bandwidth=eno1`  | Print Internet bandwidth                                            |
|`-i`| `--iface=eno1`      | Print current download and upload speed                             |
|`-A`| `--ipmac=eno1`      | Print NIC MAC address                                               |
|`-B`| `--ipmask=eno1`     | Print NIC subnet mask                                               |
|`-D`| `--ipcast=eno1`     | Print NIC broadcast address                                         |
|`-E`| `--iplookup=`<br />`google.com` | Perform a IP lookup on a domain name                    |
|    | `--pingtime=`<br />`https://google.com` | Perform a GET request and measure the round trip time    |

Options mentioning **Assembly** are tested only on AMD and Intel CPUs (starting from pentium 4 onwards).

The following options are available only in Linux:

|Opt| Option | Description                                                 |
|:---:|--------------------|-----------------------------------------------|
|    | `--ramused`        | Print used RAM, in MB                          |
|`-F`| `--drivemodel=sda` | Print drive vendor                             |
|`-G`| `--nicinfo=eth0`   | Print NIC vendor and model with pciutils       |
|    | `--nicdrv=eth0`    | Print NIC driver                               |
|`-H`| `--nicver=eth0`    | Print NIC version                              |
|`-e`| `--iplink=eth0`    | Print NIC link speed (useful for wireless/WiFi)|
|`-j`| `--nicfw=eth0`     | Print NIC firmware                             |
|`-h`| `--wifiname=wlan0` | Print name of WiFi/wireless network            |

The following options are available only in Arch Linux, Debian, Gentoo, RHEL, FreeBSD (w/ ports tree):

|Opt| Option | Description                                |
|------|-------------|------------------------------------|
|      | `--updates` |  Print number of available updates |

The following options are available only to FreeBSD and OpenBSD:

|Opt| Option | Description                                       |
|:---:|---------------|------------------------------------------|
|`-j`| `--nicgw=re0` | Print NIC gateway address                 |
|`-Z`| `--swapused`  | Print used drive swap, in MB              |
|`-F`| `--swaperc`   | Print used drive swap, in percentage      |
|`-h`| `--swaptotal` | Print total drive swap                    |
|`-H`| `--swapavail` | Print available drive swap (total - used) |
|    | `--wifiname=wlan0` | Print name of WiFi/wireless network  |

The following options are available only in OpenBSD:

|Opt| Option | Description                           |
|:---:|-------------|--------------------------------|
|`-l`| `--ramused` | Print used RAM, in MB           |

---

## Supported Linux Distributions

Replace **distro** with the following [bases](https://en.wikipedia.org/wiki/List_of_Linux_distributions):

- [x] archlinux based distros: parabola, chakra, manjaro
- [x] debian based distros: ubuntu, linux mint, trisquel, back track, kali linux, peppermint linux, solus, crunchbang, deepin, elementary os, and the rest \*buntu based distros
- [x] gentoo based distros: funtoo, sabayon, calculate linux
- [x] slackware
- [x] rhel based distros: opensuse (uses rpm), fedora, fuduntu, mandriva, mandrake, viperr, mageia
- [x] frugalware
- [x] angstrom
- [x] voidlinux
- [x] crux
- [x] alpinelinux
- [x] slitaz
- [x] tinycorelinux
- [x] nixos
- [x] paldo
- [x] dragora
- [x] guixsd

Cannot list the \*BSD flavours as "distros", so they deserve their own options:

- [x] freebsd
- [x] openbsd

---

## Configuration File

**~/.pinky** is the location of the configuration file. You can specify different config location via the `--conf` option.

If any option depends on argument, don't put any space between the option and the argument. Only true if you are not using the `--shell` option.

Use one option per line. Contrary to your shell, the "parser" won't expand `~/my_script.pl` to `/home/User/my_script.pl`.

Execute the program without supplying any command line options and it will parse the configuration file. Optionally you can use different location for the configuration file, thus if you have tmux and lemonbar configs they won't clash. Here's how to use different config `pinkybar --conf ~/.config/pinky-tmux.conf`

```bash
/*
*
* Example configuration file
* comments can start with:
*   // comment, /* comment */
*   # comment, ;; comment
*
*/

;; town followed by country code
--weather=London,uk

/*
* In dzen2 you can replace title with
* the desired xbm icon from extra/xbm_icons/*.xbm
*/

--title=CPU
--cpu-percent-all

--cputemp

--title=RAM
--ramperc

--title=HDD
--driveperc

--title=Pkgs
--packages

--kernel

--title=Volatage
--voltage

--title=Fans/RPM
--fans

--title=Mobo
--mobo

--mobotemp


# perl script to run
--title=Script
--perl=/home/User/my_script.pl

// shell command to run
--shell echo 'hi'
```

---

## Linux Mandatory Requirements

* gcc/clang/pcc
* g/libc
* autoconf
* automake
* m4
* gawk
* perl
* pkg-config
* **as** from binutils

## \*BSD Mandatory Requirements

* gcc/clang/pcc
* autoconf
* automake
* autoconf-wrapper
* automake-wrapper
* autoconf-archive
* argp-standalone
* libtool
* m4
* gawk
* perl
* pkg-config
* **as** from binutils

Some llvm and gcc versions will not check for headers and libraries in `/usr/local`, and you might get something like **ld cannot find -largp**, if that's the case for you, you should export the following environment variables:

```bash
export LDFLAGS='-L/usr/local/lib'
export CFLAGS='-I/usr/local/include'
```

It seems that OpenBSD 6.3 clang compiler fails to find **-largp** even with the above environment variables. You are advised to install gcc.

After editing the wrong prototype I managed to stumble upon a bug in OpenBSD's own libc.

**Warning !!! OpenBSD users !!!**

The majority of SCN\* macros differs from their PRI\* cousins. And I cannot guarantee the accuracy of fixed width integers when OpenBSD own libc managed to use different format specifiers. Read extra/misc/openbsd\_bugs.md for more details.

## Opt-in Requirements

*Start linux camp:*

The Internet related options rely on headers provided by iproute2.
By default, the program will try to compile with those headers included.
If you want to use this program without Internet related options, configure **--without-net**.

* iproute2

WiFi/wireless chipsets supporting mac80211/cfg80211:

* libnl *(>= 3.0)*
* pkg-config

In Gentoo, there are two versions of pkg-config. The first one is `dev-util/pkgconfig` and the second one is `dev-ruby/pkg-config`. In order to use the first one, you'll have to export pkg-config path to the following environment variable:

```bash
export PKG_CONFIG_PATH=/usr/bin/pkg-config
```

You also have to edit **m4/extend.m4** and edit the line `PKG_CHECK_MODULES([RUBY],
[ruby-2.2 >= 2.2]` to point to the correct ruby version that you have installed. Finally, configure with **--with-libnl**.


To read drive temperature from *S.M.A.R.T*.:

* The **--with-drivetemp** requires `curl`.
* The **--with-drivetemp-light** does not rely on `curl`, and will not force `-O0 CFLAGS`.

    ```bash
    # --with-drivetemp
    0.01s user 0.00s system 72% cpu 0.008

    # --with-drivetemp-light
    0.00s user 0.00s system 15% cpu 0.006
    ```
* The **--with-smartemp** requires `smartmontools` *(not mandatory in OpenBSD, `atactl` does the same job.)*

    Execute the following command `visudo` as root and append:

    ```bash
    # 'frost' is my computer username
    frost ALL=NOPASSWD:/usr/sbin/smartctl
    ```

    Copy the code from **extra/scripts/drive-temperature.sh** or `exec` it from **xinitrc** or the script used to start your DE/WM.


Try running hddtemp to see if it detects your drive, depending if it has temperature sensor in first place:

```bash
sudo hddtemp /dev/sda

WARNING: Drive /dev/sda doesn't appear in the database of supported drives
WARNING: But using a common value, it reports something.
WARNING: Note that the temperature shown could be wrong.
WARNING: See --help, --debug and --drivebase options.
WARNING: And don't forget you can add your drive to hddtemp.db
/dev/sda: Corsair Force GT:  23°C or °F
```

The message is pretty clear "don't forget to add your drive to hddtemp.db", first run the debug command to see which field is responsible to report your drive temperature, it should be in the range of 190 - 200:

```bash
sudo hddtemp --debug /dev/sda

================= hddtemp 0.3-beta15 ==================
Model: Corsair Force GT    # COPY THIS LINE

field(1)         = 0
field(5)         = 0
field(9)         = 253
field(12)        = 237
field(171)       = 0
field(172)       = 0
field(174)       = 147
field(177)       = 1
field(181)       = 0
field(182)       = 0
field(187)       = 0
field(194)       = 22    # THIS FIELD SEEMS CORRECT
field(195)       = 0
field(196)       = 0
field(201)       = 0
field(204)       = 0
field(230)       = 100
field(231)       = 0
field(233)       = 130
field(234)       = 216
field(241)       = 216
field(242)       = 151
```

Open up **/usr/share/hddtemp/hddtemp.db** and append the Model: line that you copied earlier with the correct field that reports your drive temperature.

```bash
"Corsair Force GT" 194 C "Corsair Force GT 120GB SSD"
```

Next run hddtemp in daemon mode so we can request the temperature back:

```bash
sudo hddtemp -d /dev/sda
```

Open up your browser and navigate to 127.0.0.1:7634 and you'll get instant temperature report back to you.

The "init" lock-in for those of you that cannot choose between udev or eudev puts me in position not rely on libatasmart, regardless how neat the library is. There is stripped example program in extra/misc/skdump.c if you are curious to check and test libatasmart.

*End of linux camp.*

To get the sound volume level:

* alsa-utils
* alsa-lib

Then pass **--with-alsa** to configure.

\*BSD users can use the baked OSS instead, pass **--without-alsa --with-oss** to configure instead.

Output data to the terminal using the ncurses library:

* ncurses

To get the vendor and model name of your CD-ROM/DVD-ROM/Blu-ray:

* libcdio
* libcddb

In linux **--without-dvd** will still compile the program with DVD support. Except it will be limited only to DVD support, it will try to parse the sr0 vendor and model name detected by the kernel.

The weather related options, please go back and read **Don't just rush to register yourself**:

* curl
* gzip

**Warning, I'm not responsible for any lawsuit towards you, neither encourage you to pirate content that is not licensed as free and/or for fair use.**

To see the currently played song name **--with-mpd**:

  Server side:

  * mpd (can be built with soundcloud support)

  Client side:

  * libmpdclient
  * mpc/ncmpc/ncmpcpp, [and the rest](http://mpd.wikia.com/wiki/Clients)

To see the currently played song name **--without-mpd**:

* cmus

The "soundcloud" alternative that is supported in cmus and your mpd client will be to download **.m3u/.pls** files according to the [radio stream station](https://www.internet-radio.com) that you are interested to listen.

The FreeBSD users will notice that "mpd" is named "musicpd".

If you've never used mpd before, copy the example configuration from extra/mpd according to your OS.

Keep an eye on the **log file size** if you are using raspberry pi (or equivalent device) that streams the music, make sure that it's deleted automatically if it exceeds some pre-defined size.

---

## Execute Scripts

You can execute scripts of the following languages: *Perl/Python/Ruby/Lua/R/Assembly/Lisp/OCaml/Rust/Go/C++/Slang/Tcl* and you can also simultaneously execute all of them at same time too.

**--with-python2** *(==2.7)* / **--with-python3** *(>=3.3)*

Example script `getloadavg.py`
```python
#!/usr/bin/env python
from os import getloadavg

                ↶ # VIF: VERY IMPORTANT FUNCTION
def uzer_func():
    return ', '.join([format(x) for x in getloadavg()])
```

Please do **not** export or set `PYTHONPATH` on its own line.

```bash
# export PYTHONPATH=~/script_dir  # WRONG, DO NOT EXPORT PYTHONPATH ON ITS OWN LINE
# pinkybar --python getloadavg
```
```bash
# PYTHONPATH=~/script_dir  # WRONG, DO NOT SET PYTHONPATH ON ITS OWN LINE
# pinkybar --python getloadavg
```
```bash
# python2
PYTHONPATH=~/scripts_dir ~/.cache/bin/pinkybar --python getloadavg  # CORRECT
PYTHONPATH=~/scripts_dir ~/.cache/bin/pinkybar --python getloadavg.py  # WRONG
```
```bash
# python3
# executed once
ONETIME=$(python3 -c 'import sys;print(":".join([x for x in sys.path]))')

# executed in a loop
PYTHONPATH=$ONETIME:~/scripts_dir ~/.cache/bin/pinkybar --python getloadavg
```

**--with-perl**
```bash
~/pinkybar --perl src/pinky.pl
```

**--with-ruby** *(>= 2.0 and pkg-config required)*
```bash
~/pinkybar --ruby extra/scripts/pinky.rb
```

**--with-lua** *(>= 5.1)*
```bash
~/pinkybar --lua extra/scripts/pinky.lua  # non byte-compiled script
```
```bash
luac -o pinky.luac pinky.lua  # compiled code
~/pinkybar --lua ~/scripts_dir/pinky.luac # <-- .luac and not .lua
```

**--with-r**
```bash
~/pinkybar --R extra/scripts/pinky.R
```

**--with-assembly** *(**as** from binutils required)*

The source code that you should edit is in **extra/scripts/pinky.s**,<br />
but you'll have to edit **src/Makefail.skel** to add the following at the end:

```bash
# src/Makefail.skel
pinkybar_SOURCES = ../extra/scripts/pinky.s \
```
```bash
~/pinkybar --asm  # no example code?
```

**--with-lisp** *(esl for lisp required)*
```bash
~/pinkybar --lisp extra/scripts/pinky.lisp
```

**--with-ocaml**

Before invoking any of the installation commands, you'll have to edit
**src/Makefail.skel**<br />to add the following at the end:
```bash
# src/Makefail.skel
pinkybar_SOURCES = pinky.ml \
```

```bash
# ocaml source: src/pinky.ml
~/pinkybar --ocaml  # no path
```

**--with-rust**

The source code that you should edit is in **extra/scripts/pinky.rs**,<br />
but you'll have to edit **src/Makefail.skel** to add the following at the end:

```bash
# src/Makefail.skel
pinkybar_LDADD = pinky.a
```
```bash
# rust source: extra/scripts/pinky.rs
~/pinkybar --rust  # no path
```

**--with-go**

The source code that you should edit is in **extra/scripts/pinky.go**,<br />
but you'll have to edit **src/Makefail.skel** to add the following at the end:

```bash
# src/Makefail.skel
pinkybar_LDADD = pinky2.a
```
```bash
~/pinkybar --go extra/scripts/pinky2.go
```

**--with-cpp** *(C++)*
```bash
# cpp source: src/c++.cpp
~/pinkybar --cpp  # no path
```

**--with-slang**
```bash
~/pinkybar --slang extra/scripts/pinky.sl
```

**--with-tcl**
```bash
~/pinkybar --tcl extra/scripts/pinky.tcl
```

## WM Specific Requirements

If you would like the output to be shown in your Window Manager, those are the following requirements:

For non-dwm WM:

* dzen2
* py3status
* awesomewm
* xmobar
* lemonbar

For dwm:

* libx11
* xorg-server

Use **--without-colors** to skip the following step:

* dwm compiled with statuscolor patch. The colors are specified in your dwm config.h

## Void Linux

```bash
# install the dependencies
xbps-install -S pkg-config libtool automake autoconf m4 make  # and gcc/llvm/clang
```

Packages `alsa-utils`, `alsa-lib` does not ship with **asoundlib.h**.<br />
If you want to use **--with-alsa**, you'll have to compile the library manually:

```bash
wget ftp://ftp.alsa-project.org/pub/plugins/alsa-plugins-1.1.5.tar.bz2
bzip2 --decompress alsa-plugins-1.1.5.tar.bz2
tar -xvf alsa-plugins-1.1.5.tar
cd alsa-plugins-1.1.5
./configure --prefix=/usr
make
sudo make install
```

## Tiny Core Linux

```bash
# install the dependencies
tce-load -wi sed.tcz pkg-config.tcz libtool.tcz grep.tcz glibc_base-dev.tcz \
gcc.tcz m4.tcz perl5.tcz gawk.tcz make.tcz autoconf.tcz automake.tcz

# run this next
libtoolize --force
aclocal
autoheader
automake --force-missing --add-missing
autoconf
./configure --without-net --without-alsa --without-pci
make
make install
```

## Wish List

It would be great if we can add NetBSD support.

## History

The project began (on February 22, 2015) as simple Conky replacement written in 3 days when I switched from Openbox to dwm, here's some history:

*I had 8 wonderful months with Openbox and the time to try and learn something new has come.*

*I was wondering these days what to do, either write some lengthy tutorial or do some new changes to my Openbox configuration files. And then a link to someone's laptop made me to change my mind.*

*The guy was running dwm, which in turn is dynamic window manager (hence the name). I was impressed by his desktop screenshot and decided to delay my plans and give 'dwm' a try.*

*The picture below represents my 3rd day with dwm.*

![](img/openbox-2-dwm.jpg)

*Since it is written and configured in C, I had no trouble getting it running, patched and configured they way I want to in the very first day.*

*My first day was all around to get dwm working, and deprecate **Conky** with my own version written in C that depends entirely on the standard library and doesn't call any 3rd party program. And that is how [dwm-bar.c](https://github.com/su8/dotfiles/blob/master/archlinux/home/frost/.config/dwm_scripts/dwm-bar.c) was born.*

*Later on saw that in the dwm website there was **dwmstatus** examples and borrowed the code that sets the root window name (the colored ram, drive, kernel, volume and time), so edited my program to output the data to the root window, instead using xsetroot in addition with my first dwm-bar.c version. I have cloned and pushed my program to their git, so by the time you read this post it will be merged.*

*On the second day I wanted to add some colorization and icons to the status bar without using dzen2 or any other 3rd party program. There was enormous number of patches in the dwm website, and to be honest the colorization patch posted there was broken and incomplete. Thankfully to GitHub's searching functions I managed to find different colorization patches, I have tried the ones with pango and cairo, but my system gpu is too weak to handle all the different effects.*

*I don't have to mention that almost every patch I came across in Internet was broken or incomplete, and it was up to me to fix it.*

*On third day (today) my primary task was to add only colorization and I did it. Here is a link to my dwm fork and patches* [dwm-fork](https://github.com/su8/dwm-fork)
