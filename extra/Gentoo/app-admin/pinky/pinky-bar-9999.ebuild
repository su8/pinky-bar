# Copyright 1999-2016 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Id$

EAPI=6

EGIT_REPO_URI="https://gitlab.com/void0/pinky-bar.git"

inherit git-r3

DESCRIPTION="Gather some system information and show it in this statusbar program"
HOMEPAGE="https://gitlab.com/void0/pinky-bar"

LICENSE="GPL-2"
SLOT="0"
IUSE="x11 alsa net libnl pci dvd sensors ncurses colours weather mpd"

DEPEND="
	sys-devel/m4
	sys-apps/gawk
	sys-devel/autoconf
	>=sys-devel/automake-1.14.1
"
RDEPEND="
	alsa? ( media-libs/alsa-lib )
	x11? ( x11-libs/libX11 )
	net? ( sys-apps/iproute2 )
	libnl? ( >=dev-libs/libnl-3.2.27 dev-util/pkgconfig )
	pci? ( sys-apps/pciutils )
	dvd? ( dev-libs/libcdio )
	sensors? ( sys-apps/lm_sensors )
	ncurses? ( sys-libs/ncurses )
	weather? ( net-misc/curl app-arch/gzip )
	mpd? ( media-sound/mpd media-libs/libmpdclient )
"

src_prepare() {
	default

	einfo 'Generating Makefiles and will run autoconf afterwards'
	chmod +x bootstrap
	./bootstrap 'gentoo'
}

src_configure() {
	export PKG_CONFIG_PATH=/usr/bin/pkg-config

	econf \
		$(use_with x11) \
		$(use_with alsa) \
		$(use_with net) \
		$(use_with libnl) \
		$(use_with pci) \
		$(use_with dvd) \
		$(use_with sensors) \
		$(use_with ncurses) \
		$(use_with colours) \
		$(use_with weather) \
		$(use_with mpd) \
		api_town='London,uk' \
		api_key='28459ae16e4b3a7e5628ff21f4907b6f' \
		icons=$HOME/.xmonad/icons
}

pkg_postinst() {
	einfo 'Please read the program man page'
}
