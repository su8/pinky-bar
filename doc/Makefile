# 10/29/2016

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.

define pandora_snap
	-sed -e '15r ../README.md' 'man_template.pdc' | \
		sed -e '15,50d' | pandoc -s -S $(1) - -o pinkybar.$(2)
endef

man:
	$(call pandora_snap,-f markdown -t man,1)

info: pinkybar.info

pinkybar.info:
	$(call pandora_snap, ,texi)
	-sed -i '2i @setfilename pinkybar.info' pinkybar.texi
	$(MAKEINFO) --no-validate --no-warn --force pinkybar.texi

.PHONY: man info pinkybar.info
